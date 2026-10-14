/* The 2D graphics engines; see gpu2d.h. Everything follows GBATEK ("DS Video", "LCD I/O")
 * unless a comment says where this model is simpler than the hardware. */
#include "gpu2d.h"

#include <string.h>

#include "frame.h"
#include "gpu3d.h"
#include "io.h"

/* Register offsets within an engine (engine B adds 0x1000). */
#define R_DISPCNT 0x000
#define R_BG0CNT 0x008
#define R_BG0HOFS 0x010
#define R_BG2PA 0x020
#define R_WIN0H 0x040
#define R_WIN0V 0x044
#define R_WININ 0x048
#define R_WINOUT 0x04a
#define R_MOSAIC 0x04c
#define R_BLDCNT 0x050
#define R_BLDALPHA 0x052
#define R_BLDY 0x054
#define R_DISPCAPCNT 0x064
#define R_MASTER_BRIGHT 0x06c
#define R_POWCNT1 0x304

/* A transparent pixel in a layer buffer; colours are 18 bits so this never collides. */
#define NONE 0xffffffffu
#define WHITE 0x3ffffu

/* Layer numbers for the colour effect targets (BLDCNT bits 0-5 and 8-13). */
#define LAYER_OBJ 4
#define LAYER_BACKDROP 5

/* Per-pixel OBJ flags. */
#define OBJ_SEMI 1   /* OBJ mode 1: semi-transparent */
#define OBJ_BITMAP 2 /* OBJ mode 3: bitmap, with its own alpha */
#define OBJ_MOSAIC 4

/* What a BG is in the current mode (GBATEK, "DS Video BG Modes"). */
enum BgKind { BG_NONE, BG_TEXT, BG_AFFINE, BG_EXTENDED, BG_LARGE, BG_3D };

typedef struct Engine {
    int index;                  /* 0 = engine A, 1 = engine B */
    uint32_t reg;               /* register offset: 0 or 0x1000 */
    uint32_t bg_base, obj_base; /* the CPU-visible addresses of the BG and OBJ VRAM regions */
    uint32_t bg_mask, obj_mask; /* their sizes minus one */
    uint32_t palette, oam;      /* offsets into palette RAM and OAM */

    /* Affine BG2 and BG3: the internal reference point (28-bit signed, 8 fractional bits),
       reloaded from BGxX/BGxY at the start of the frame and after a write to them; the
       copy mosaic repeats while inside a vertical mosaic block. */
    int32_t ref_x[2], ref_y[2];
    int ref_reload[2];
    int32_t mosaic_x[2], mosaic_y[2];

    /* The line being drawn. */
    uint32_t bg[4][GPU2D_WIDTH];
    uint8_t alpha3d[GPU2D_WIDTH]; /* the 3D layer's 5-bit alpha where BG0 is 3D */
    uint32_t obj[GPU2D_WIDTH];
    uint8_t obj_prio[GPU2D_WIDTH], obj_flags[GPU2D_WIDTH], obj_alpha[GPU2D_WIDTH], obj_window[GPU2D_WIDTH];
    uint8_t win[GPU2D_WIDTH];  /* per pixel: bits 0-3 BG0-3 shown, 4 OBJ shown, 5 effects allowed */
    uint32_t out[GPU2D_WIDTH]; /* the composed line before master brightness */

    uint32_t frame[GPU2D_HEIGHT * GPU2D_WIDTH]; /* 18-bit colours */

    /* A display capture in progress: it starts with the first line of the frame after the
       enable bit was set and runs to the end of that frame (GBATEK, "DS Video Display
       Capture"). */
    int capturing;
} Engine;

static Engine engines[2];
static uint32_t frames_done;
static uint32_t screens[2][GPU2D_HEIGHT * GPU2D_WIDTH]; /* [0] lower LCD, [1] upper LCD */

/* The main memory display FIFO (DISP_MMEM_FIFO, 0x04000068): the hardware takes 8 words
 * per 16 pixels through DMA timing 4; here the words queue in a ring and display mode 3
 * takes 128 of them per line, so a game that keeps the FIFO fed sees the same picture. */
#define FIFO_WORDS 1024
static uint32_t fifo[FIFO_WORDS];
static uint32_t fifo_head, fifo_count;

/* Register access ------------------------------------------------------------------------- */

static uint32_t reg16(const Engine *e, uint32_t offset)
{
    uint32_t v = io_reg(0x04000000u + e->reg + offset);
    return (v >> ((offset & 2) * 8)) & 0xffffu;
}

static uint32_t reg32(const Engine *e, uint32_t offset)
{
    return io_reg(0x04000000u + e->reg + offset);
}

/* VRAM and palettes ------------------------------------------------------------------------ */

static uint32_t vram8(uint32_t base, uint32_t mask, uint32_t offset)
{
    uint32_t a = base + (offset & mask);
    const uint8_t *p = io_vram_page(a);
    return p ? p[a & 0x3fffu] : 0;
}

static uint32_t vram16(uint32_t base, uint32_t mask, uint32_t offset)
{
    uint32_t a = base + (offset & mask & ~1u);
    const uint8_t *p = io_vram_page(a);
    return p ? (uint32_t) p[a & 0x3fffu] | ((uint32_t) p[(a & 0x3fffu) + 1] << 8) : 0;
}

/* A 15-bit palette colour as the 18-bit value the engine works in: each 5-bit channel is
 * doubled (GBATEK: the 2D engine extends colours to 6 bits with the low bit clear). */
static uint32_t rgb15(uint32_t c)
{
    return ((c & 0x1fu) << 1) | ((c & 0x3e0u) << 2) | ((c & 0x7c00u) << 3);
}

static uint32_t pal_colour(uint32_t palette_offset, uint32_t index)
{
    const uint8_t *p = io_palette_ram() + palette_offset + 2 * index;
    return rgb15((uint32_t) p[0] | ((uint32_t) p[1] << 8));
}

static uint32_t ext_colour(const uint8_t *slot, uint32_t index)
{
    if (slot == NULL) {
        return 0; /* an unmapped extended palette reads as zero: black */
    }
    return rgb15((uint32_t) slot[2 * index] | ((uint32_t) slot[2 * index + 1] << 8));
}

static uint32_t oam16(const Engine *e, uint32_t offset)
{
    const uint8_t *p = io_oam_ram() + e->oam + offset;
    return (uint32_t) p[0] | ((uint32_t) p[1] << 8);
}

/* Backgrounds ------------------------------------------------------------------------------ */

static enum BgKind bg_kind(const Engine *e, int bg, uint32_t dispcnt)
{
    static const enum BgKind table[8][4] = {
        {BG_TEXT, BG_TEXT, BG_TEXT, BG_TEXT},       {BG_TEXT, BG_TEXT, BG_TEXT, BG_AFFINE},
        {BG_TEXT, BG_TEXT, BG_AFFINE, BG_AFFINE},   {BG_TEXT, BG_TEXT, BG_TEXT, BG_EXTENDED},
        {BG_TEXT, BG_TEXT, BG_AFFINE, BG_EXTENDED}, {BG_TEXT, BG_TEXT, BG_EXTENDED, BG_EXTENDED},
        {BG_3D, BG_NONE, BG_LARGE, BG_NONE},        {BG_NONE, BG_NONE, BG_NONE, BG_NONE},
    };
    uint32_t mode = dispcnt & 7;
    enum BgKind kind = table[mode][bg];
    if (e->index == 1 && (kind == BG_3D || kind == BG_LARGE)) {
        return BG_NONE; /* modes 6 and the 3D layer exist on engine A only */
    }
    if (e->index == 0 && bg == 0 && kind == BG_TEXT && (dispcnt & 8)) {
        return BG_3D; /* DISPCNT bit 3: BG0 shows the 3D engine's output */
    }
    return kind;
}

static void draw_3d(Engine *e, uint32_t y)
{
    const uint16_t *line = gpu3d_line((int) y);
    const uint8_t *alpha = gpu3d_line_alpha((int) y);
    /* BG0HOFS scrolls the 3D layer horizontally; the image is 256 wide in a 512-wide space
       and the rest is transparent (the 3D layer does not wrap). */
    uint32_t hofs = reg16(e, R_BG0HOFS) & 0x1ffu;
    for (uint32_t x = 0; x < GPU2D_WIDTH; x++) {
        uint32_t sx = (x + hofs) & 0x1ffu;
        int drawn = line != NULL && sx < 256 && (line[sx] & 0x8000u);
        e->bg[0][x] = drawn ? rgb15(line[sx]) : NONE;
        e->alpha3d[x] = (uint8_t) (drawn ? (alpha != NULL ? alpha[sx] & 31u : 31u) : 0u);
    }
}

static void draw_text(Engine *e, int bg, uint32_t y, uint32_t dispcnt)
{
    uint32_t cnt = reg16(e, R_BG0CNT + 2 * (uint32_t) bg);
    uint32_t hofs = reg16(e, R_BG0HOFS + 4 * (uint32_t) bg) & 0x1ffu;
    uint32_t vofs = reg16(e, R_BG0HOFS + 2 + 4 * (uint32_t) bg) & 0x1ffu;
    uint32_t char_base = ((cnt >> 2) & 0xfu) * 0x4000u, screen_base = ((cnt >> 8) & 0x1fu) * 0x800u;
    if (e->index == 0) {
        /* engine A adds DISPCNT's 64 KiB character and screen base offsets */
        char_base += ((dispcnt >> 24) & 7) * 0x10000u;
        screen_base += ((dispcnt >> 27) & 7) * 0x10000u;
    }
    uint32_t size = cnt >> 14;
    int colours256 = (cnt & 0x80) != 0;
    const uint8_t *ext = NULL;
    if (colours256 && (dispcnt & (1u << 30))) {
        /* extended palettes: BG0 and BG1 use slot 2 and 3 instead of 0 and 1 when bit 13 is
           set (the bit that is "area overflow" for affine BGs) */
        int slot = (bg < 2 && (cnt & 0x2000)) ? bg + 2 : bg;
        ext = io_vram_bg_ext_palette(e->index, slot);
    }
    uint32_t yy = (y + vofs) & (size >= 2 ? 511u : 255u);
    uint32_t width_mask = (size & 1) ? 511u : 255u;
    uint32_t row = screen_base + ((yy >> 8) * (size == 3 ? 2u : 1u)) * 0x800u + ((yy & 255) >> 3) * 64;
    uint32_t entry = 0, tile_row = 0;
    for (uint32_t x = 0; x < GPU2D_WIDTH; x++) {
        uint32_t xx = (x + hofs) & width_mask;
        uint32_t tx = xx & 7, ty = yy & 7;
        if (x == 0 || tx == 0) {
            entry = vram16(e->bg_base, e->bg_mask, row + (xx >> 8) * 0x800u + ((xx & 255) >> 3) * 2);
            uint32_t tile = entry & 0x3ffu;
            uint32_t fy = (entry & 0x800) ? 7 - ty : ty;
            tile_row = char_base + (colours256 ? tile * 64 + fy * 8 : tile * 32 + fy * 4);
        }
        if (entry & 0x400) {
            tx = 7 - tx;
        }
        uint32_t index;
        if (colours256) {
            index = vram8(e->bg_base, e->bg_mask, tile_row + tx);
            if (index == 0) {
                e->bg[bg][x] = NONE;
                continue;
            }
            e->bg[bg][x] = ext ? ext_colour(ext, (entry >> 12) * 256 + index) : pal_colour(e->palette, index);
        } else {
            uint32_t b = vram8(e->bg_base, e->bg_mask, tile_row + (tx >> 1));
            index = (tx & 1) ? b >> 4 : b & 15;
            if (index == 0) {
                e->bg[bg][x] = NONE;
                continue;
            }
            e->bg[bg][x] = pal_colour(e->palette, (entry >> 12) * 16 + index);
        }
    }
}

/* Rotation/scaling BGs: BG2 and BG3 in the affine, extended and large bitmap kinds. The
 * current position runs along the line from the internal reference point by PA/PC per
 * pixel; PB/PD are added per line (GBATEK, "LCD I/O BG Rotation/Scaling"). */
static void draw_affine(Engine *e, int bg, uint32_t y, uint32_t dispcnt, enum BgKind kind)
{
    int i = bg - 2;
    uint32_t cnt = reg16(e, R_BG0CNT + 2 * (uint32_t) bg);
    int32_t pa = (int16_t) reg16(e, R_BG2PA + 0x10 * (uint32_t) i), pb = (int16_t) reg16(e, R_BG2PA + 2 + 0x10 * (uint32_t) i);
    int32_t pc = (int16_t) reg16(e, R_BG2PA + 4 + 0x10 * (uint32_t) i),
            pd = (int16_t) reg16(e, R_BG2PA + 6 + 0x10 * (uint32_t) i);
    uint32_t mosaic = reg16(e, R_MOSAIC);
    uint32_t mv = (cnt & 0x40) ? ((mosaic >> 4) & 15) : 0;
    if (mv == 0 || y % (mv + 1) == 0) {
        e->mosaic_x[i] = e->ref_x[i];
        e->mosaic_y[i] = e->ref_y[i];
    }
    int32_t cx = e->mosaic_x[i], cy = e->mosaic_y[i];

    uint32_t char_base = ((cnt >> 2) & 0xfu) * 0x4000u, screen_base = ((cnt >> 8) & 0x1fu) * 0x800u;
    /* a bitmap's base is BGxCNT's screen base in 16 KiB units; DISPCNT's 64 KiB character
       and screen base offsets apply to the tiled kinds only */
    uint32_t bitmap_base = ((cnt >> 8) & 0x1fu) * 0x4000u;
    if (e->index == 0) {
        char_base += ((dispcnt >> 24) & 7) * 0x10000u;
        screen_base += ((dispcnt >> 27) & 7) * 0x10000u;
    }
    uint32_t size = cnt >> 14, w, h;
    int wrap = (cnt & 0x2000) != 0;
    /* The sub-kind of an extended BG: bit 7 clear is a rotscale BG with 16-bit map entries,
       bit 7 set is a bitmap, 256 colours or direct colour by bit 2. */
    enum { ROT8, ROT16, BMP8, BMP16, LARGE } sub;
    if (kind == BG_AFFINE) {
        sub = ROT8;
        w = h = 128u << size;
    } else if (kind == BG_LARGE) {
        sub = LARGE;
        w = size == 0 ? 512 : 1024;
        h = size == 0 ? 1024 : 512;
    } else if ((cnt & 0x80) == 0) {
        sub = ROT16;
        w = h = 128u << size;
    } else {
        sub = (cnt & 4) ? BMP16 : BMP8;
        w = size == 0 ? 128 : size == 1 ? 256 : 512;
        h = size == 0 ? 128 : size == 3 ? 512 : 256;
    }
    const uint8_t *ext = (dispcnt & (1u << 30)) ? io_vram_bg_ext_palette(e->index, bg) : NULL;

    for (uint32_t x = 0; x < GPU2D_WIDTH; x++) {
        int32_t xx = cx >> 8, yy = cy >> 8;
        cx += pa;
        cy += pc;
        if (wrap) {
            xx &= (int32_t) (w - 1);
            yy &= (int32_t) (h - 1);
        } else if (xx < 0 || yy < 0 || (uint32_t) xx >= w || (uint32_t) yy >= h) {
            e->bg[bg][x] = NONE;
            continue;
        }
        uint32_t ux = (uint32_t) xx, uy = (uint32_t) yy, index, colour = NONE;
        switch (sub) {
            case ROT8: {
                uint32_t tile = vram8(e->bg_base, e->bg_mask, screen_base + (uy >> 3) * (w >> 3) + (ux >> 3));
                index = vram8(e->bg_base, e->bg_mask, char_base + tile * 64 + (uy & 7) * 8 + (ux & 7));
                if (index) {
                    /* the 8-bit map of a plain rotscale BG has no palette number, and the
                       extended palettes are for 16-bit map entries only: standard palette */
                    colour = pal_colour(e->palette, index);
                }
                break;
            }
            case ROT16: {
                uint32_t entry = vram16(e->bg_base, e->bg_mask, screen_base + ((uy >> 3) * (w >> 3) + (ux >> 3)) * 2);
                uint32_t tx = (entry & 0x400) ? 7 - (ux & 7) : ux & 7, ty = (entry & 0x800) ? 7 - (uy & 7) : uy & 7;
                index = vram8(e->bg_base, e->bg_mask, char_base + (entry & 0x3ffu) * 64 + ty * 8 + tx);
                if (index) {
                    colour = ext ? ext_colour(ext, (entry >> 12) * 256 + index) : pal_colour(e->palette, index);
                }
                break;
            }
            case BMP8:
                index = vram8(e->bg_base, e->bg_mask, bitmap_base + uy * w + ux);
                if (index) {
                    colour = pal_colour(e->palette, index); /* bitmaps use the standard palette */
                }
                break;
            case BMP16: {
                uint32_t c = vram16(e->bg_base, e->bg_mask, bitmap_base + (uy * w + ux) * 2);
                if (c & 0x8000) {
                    colour = rgb15(c);
                }
                break;
            }
            case LARGE:
                index = vram8(e->bg_base, e->bg_mask, uy * w + ux);
                if (index) {
                    colour = pal_colour(e->palette, index);
                }
                break;
        }
        e->bg[bg][x] = colour;
    }
    e->ref_x[i] += pb;
    e->ref_y[i] += pd;
}

/* Horizontal mosaic: every pixel repeats the first of its block. */
static void mosaic_line(uint32_t *line, uint32_t mh)
{
    if (mh == 0) {
        return;
    }
    for (uint32_t x = 0; x < GPU2D_WIDTH; x++) {
        line[x] = line[x - x % (mh + 1)];
    }
}

static void draw_bgs(Engine *e, uint32_t y, uint32_t dispcnt)
{
    uint32_t mosaic = reg16(e, R_MOSAIC);
    for (int bg = 0; bg < 4; bg++) {
        enum BgKind kind = bg_kind(e, bg, dispcnt);
        if (kind == BG_NONE || (dispcnt & (0x100u << bg)) == 0) {
            continue; /* its buffer is not read: compose skips disabled BGs */
        }
        uint32_t cnt = reg16(e, R_BG0CNT + 2 * (uint32_t) bg);
        uint32_t mh = (cnt & 0x40) ? mosaic & 15 : 0, mv = (cnt & 0x40) ? (mosaic >> 4) & 15 : 0;
        switch (kind) {
            case BG_3D:
                draw_3d(e, y);
                break;
            case BG_TEXT:
                /* vertical mosaic: the whole block shows its first line */
                draw_text(e, bg, y - y % (mv + 1), dispcnt);
                break;
            default:
                draw_affine(e, bg, y, dispcnt, kind);
                break;
        }
        mosaic_line(e->bg[bg], mh);
    }
}

/* Objects ---------------------------------------------------------------------------------- */

static const uint8_t obj_dims[3][4][2] = {
    {{8, 8}, {16, 16}, {32, 32}, {64, 64}},
    {{16, 8}, {32, 8}, {32, 16}, {64, 32}},
    {{8, 16}, {8, 32}, {16, 32}, {32, 64}},
};

static void draw_objs(Engine *e, uint32_t y, uint32_t dispcnt)
{
    for (uint32_t x = 0; x < GPU2D_WIDTH; x++) {
        e->obj[x] = NONE;
        e->obj_window[x] = 0;
        e->obj_flags[x] = 0;
    }
    if ((dispcnt & 0x1000) == 0 && (dispcnt & 0x8000) == 0) {
        return; /* neither OBJ display nor the OBJ window */
    }
    uint32_t mosaic = reg16(e, R_MOSAIC);
    uint32_t mh = (mosaic >> 8) & 15, mv = (mosaic >> 12) & 15;
    uint32_t boundary = 32u << ((dispcnt >> 20) & 3);
    uint32_t bitmap_1d = dispcnt & 0x40, bitmap_stride = (dispcnt & 0x20) ? 256 : 128;
    uint32_t bitmap_boundary = (dispcnt & (1u << 22)) ? 256 : 128;
    const uint8_t *ext = (dispcnt & (1u << 31)) ? io_vram_obj_ext_palette(e->index) : NULL;
    uint32_t obj_palette = e->palette + 0x200;

    /* OAM order decides between overlapping OBJs: a later OBJ only replaces an earlier one
       at a pixel when its priority number is lower, so the first OBJ at a given priority
       wins, and a BG between them cannot bring the loser back (the GBA/DS "OBJ priority"
       quirk). The hardware also runs out of drawing time with many large OBJs on a line;
       that limit is not modelled. */
    for (uint32_t i = 0; i < 128; i++) {
        uint32_t a0 = oam16(e, i * 8), a1 = oam16(e, i * 8 + 2), a2 = oam16(e, i * 8 + 4);
        int affine = (a0 & 0x100) != 0;
        if (!affine && (a0 & 0x200)) {
            continue; /* hidden */
        }
        uint32_t mode = (a0 >> 10) & 3, shape = a0 >> 14, size = a1 >> 14;
        if (shape == 3) {
            continue; /* a prohibited shape draws nothing */
        }
        if (mode == 2 && (dispcnt & 0x8000) == 0) {
            continue;
        }
        if (mode != 2 && (dispcnt & 0x1000) == 0) {
            continue;
        }
        int w = obj_dims[shape][size][0], h = obj_dims[shape][size][1];
        int bw = w, bh = h;
        if (affine && (a0 & 0x200)) {
            bw *= 2; /* double-size: the rotation area is twice the OBJ */
            bh *= 2;
        }
        int yo = (int) (a0 & 0xff);
        if (yo >= GPU2D_HEIGHT) {
            yo -= 256; /* Y wraps at 256: an OBJ at 250 is 6 lines above the top */
        }
        int xo = (int) (a1 & 0x1ff);
        if (xo >= 256) {
            xo -= 512;
        }
        int use_mosaic = (a0 & 0x1000) != 0;
        int ly = (int) (use_mosaic ? y - y % (mv + 1) : y) - yo;
        if (use_mosaic && ly < 0) {
            ly = 0; /* an OBJ starting inside a mosaic block shows its first line */
        }
        if (ly < 0 || ly >= bh || xo >= 256 || xo + bw <= 0) {
            continue;
        }
        int32_t pa = 0x100, pb = 0, pc = 0, pd = 0x100;
        if (affine) {
            uint32_t p = ((a1 >> 9) & 31) * 32;
            pa = (int16_t) oam16(e, p + 6);
            pb = (int16_t) oam16(e, p + 14);
            pc = (int16_t) oam16(e, p + 22);
            pd = (int16_t) oam16(e, p + 30);
        }
        uint32_t tile = a2 & 0x3ffu, prio = (a2 >> 10) & 3, pal = a2 >> 12;
        int colours256 = (a0 & 0x2000) != 0;
        if (mode == 3 && pal == 0) {
            continue; /* a bitmap OBJ with alpha 0 is not displayed */
        }
        int x_start = xo < 0 ? 0 : xo, x_end = xo + bw > 256 ? 256 : xo + bw;
        for (int sx = x_start; sx < x_end; sx++) {
            int lx = sx - xo, rx, ry;
            if (affine) {
                /* rotate about the centre of the (possibly doubled) area */
                int dx = lx - bw / 2, dy = ly - bh / 2;
                rx = ((pa * dx + pb * dy) >> 8) + w / 2;
                ry = ((pc * dx + pd * dy) >> 8) + h / 2;
                if (rx < 0 || rx >= w || ry < 0 || ry >= h) {
                    continue;
                }
            } else {
                rx = (a1 & 0x1000) ? w - 1 - lx : lx;
                ry = (a1 & 0x2000) ? h - 1 - ly : ly;
            }
            uint32_t ux = (uint32_t) rx, uy = (uint32_t) ry, colour, alpha = 0;
            if (mode == 3) {
                uint32_t address;
                if (bitmap_1d) {
                    address = tile * bitmap_boundary + (uy * (uint32_t) w + ux) * 2;
                } else {
                    /* 2D: the tile number's low 4 (128 wide) or 5 bits (256 wide) are the
                       column of 8 pixels, the rest the row of 8 lines */
                    uint32_t cols = bitmap_stride / 8, col = tile % cols, row = tile / cols;
                    address = (row * 8 + uy) * bitmap_stride * 2 + col * 16 + ux * 2;
                }
                uint32_t c = vram16(e->obj_base, e->obj_mask, address);
                if ((c & 0x8000) == 0) {
                    continue;
                }
                colour = rgb15(c);
                alpha = pal;
            } else if (colours256) {
                uint32_t address;
                if (dispcnt & 0x10) {
                    address = tile * boundary + ((uy >> 3) * ((uint32_t) w >> 3) + (ux >> 3)) * 64;
                } else {
                    /* 2D, 256 colours: 32 tiles of 32 bytes per row; a tile is two units */
                    address = ((tile & 0x3feu) + (uy >> 3) * 32 + (ux >> 3) * 2) * 32;
                }
                uint32_t index = vram8(e->obj_base, e->obj_mask, address + (uy & 7) * 8 + (ux & 7));
                if (index == 0) {
                    continue;
                }
                colour = ext ? ext_colour(ext, pal * 256 + index) : pal_colour(obj_palette, index);
            } else {
                uint32_t address;
                if (dispcnt & 0x10) {
                    address = tile * boundary + ((uy >> 3) * ((uint32_t) w >> 3) + (ux >> 3)) * 32;
                } else {
                    address = ((tile + (uy >> 3) * 32 + (ux >> 3)) & 0x3ffu) * 32;
                }
                uint32_t b = vram8(e->obj_base, e->obj_mask, address + (uy & 7) * 4 + (ux >> 1));
                uint32_t index = (ux & 1) ? b >> 4 : b & 15;
                if (index == 0) {
                    continue;
                }
                colour = pal_colour(obj_palette, pal * 16 + index);
            }
            if (mode == 2) {
                e->obj_window[sx] = 1;
                continue;
            }
            if (e->obj[sx] != NONE && prio >= e->obj_prio[sx]) {
                continue;
            }
            e->obj[sx] = colour;
            e->obj_prio[sx] = (uint8_t) prio;
            e->obj_alpha[sx] = (uint8_t) alpha;
            e->obj_flags[sx] =
                (uint8_t) ((mode == 1 ? OBJ_SEMI : 0) | (mode == 3 ? OBJ_BITMAP : 0) | (use_mosaic ? OBJ_MOSAIC : 0));
        }
    }
    if (mh) {
        /* horizontal OBJ mosaic, over the pixels of mosaic OBJs */
        for (uint32_t x = 0; x < GPU2D_WIDTH; x++) {
            uint32_t first = x - x % (mh + 1);
            if ((e->obj_flags[x] & OBJ_MOSAIC) && (e->obj_flags[first] & OBJ_MOSAIC)) {
                e->obj[x] = e->obj[first];
                e->obj_prio[x] = e->obj_prio[first];
                e->obj_alpha[x] = e->obj_alpha[first];
                e->obj_flags[x] = e->obj_flags[first];
            }
        }
    }
}

/* Windows ---------------------------------------------------------------------------------- */

/* Whether `v` lies in [v1, v2) as the hardware reads a WINxH/WINxV pair, where a right or
 * bottom edge below the left or top one, or past the screen, means the screen edge
 * (GBATEK, "LCD I/O Window Feature": "garbage values ... are interpreted as 240/160", 256
 * and 192 on the DS). */
static int in_range(uint32_t v, uint32_t pair, uint32_t limit)
{
    uint32_t v1 = pair >> 8, v2 = pair & 0xff;
    if (v1 > v2 || v2 > limit) {
        v2 = limit;
    }
    return v >= v1 && v < v2;
}

static void build_window(Engine *e, uint32_t y, uint32_t dispcnt)
{
    if ((dispcnt & 0xe000) == 0) {
        memset(e->win, 0x3f, sizeof(e->win)); /* no window: everything shown, effects on */
        return;
    }
    uint32_t winin = reg16(e, R_WININ), winout = reg16(e, R_WINOUT);
    memset(e->win, (int) (winout & 0x3f), sizeof(e->win));
    if (dispcnt & 0x8000) {
        for (uint32_t x = 0; x < GPU2D_WIDTH; x++) {
            if (e->obj_window[x]) {
                e->win[x] = (uint8_t) ((winout >> 8) & 0x3f);
            }
        }
    }
    /* window 1 under window 0: the lower-numbered window wins where they overlap */
    for (int w = 1; w >= 0; w--) {
        if ((dispcnt & (0x2000u << w)) == 0 || !in_range(y, reg16(e, R_WIN0V + 2 * (uint32_t) w), GPU2D_HEIGHT)) {
            continue;
        }
        uint32_t h = reg16(e, R_WIN0H + 2 * (uint32_t) w);
        uint8_t bits = (uint8_t) ((winin >> (8 * w)) & 0x3f);
        for (uint32_t x = 0; x < GPU2D_WIDTH; x++) {
            if (in_range(x, h, GPU2D_WIDTH)) {
                e->win[x] = bits;
            }
        }
    }
}

/* Composition and colour effects ----------------------------------------------------------- */

static uint32_t blend(uint32_t a, uint32_t b, uint32_t eva, uint32_t evb, uint32_t shift)
{
    uint32_t r = 0;
    for (int ch = 0; ch < 3; ch++) {
        uint32_t ca = (a >> (6 * ch)) & 63, cb = (b >> (6 * ch)) & 63;
        uint32_t c = (ca * eva + cb * evb) >> shift;
        if (c > 63) {
            c = 63;
        }
        r |= c << (6 * ch);
    }
    return r;
}

static uint32_t brightness(uint32_t a, uint32_t evy, int up)
{
    uint32_t r = 0;
    for (int ch = 0; ch < 3; ch++) {
        uint32_t c = (a >> (6 * ch)) & 63;
        c = up ? c + (((63 - c) * evy) >> 4) : c - ((c * evy) >> 4);
        r |= c << (6 * ch);
    }
    return r;
}

static void compose(Engine *e, uint32_t y, uint32_t dispcnt)
{
    (void) y;
    uint32_t bldcnt = reg16(e, R_BLDCNT), bldalpha = reg16(e, R_BLDALPHA);
    uint32_t effect = (bldcnt >> 6) & 3;
    uint32_t eva = bldalpha & 31, evb = (bldalpha >> 8) & 31, evy = reg16(e, R_BLDY) & 31;
    eva = eva > 16 ? 16 : eva;
    evb = evb > 16 ? 16 : evb;
    evy = evy > 16 ? 16 : evy;
    uint32_t backdrop = pal_colour(e->palette, 0);
    int obj_on = (dispcnt & 0x1000) != 0;
    int bg0_3d = bg_kind(e, 0, dispcnt) == BG_3D;

    /* BGs by priority, lower BG number first within a priority. */
    int order[4][4], count[4] = {0, 0, 0, 0};
    for (int bg = 0; bg < 4; bg++) {
        if ((dispcnt & (0x100u << bg)) == 0 || bg_kind(e, bg, dispcnt) == BG_NONE) {
            continue;
        }
        uint32_t p = reg16(e, R_BG0CNT + 2 * (uint32_t) bg) & 3;
        order[p][count[p]++] = bg;
    }

    for (uint32_t x = 0; x < GPU2D_WIDTH; x++) {
        uint32_t w = e->win[x];
        uint32_t top = backdrop, second = backdrop;
        int top_layer = LAYER_BACKDROP, second_layer = LAYER_BACKDROP, found = 0;
        for (uint32_t p = 0; p < 4 && found < 2; p++) {
            if (obj_on && (w & 0x10) && e->obj[x] != NONE && e->obj_prio[x] == p) {
                if (found++ == 0) {
                    top = e->obj[x];
                    top_layer = LAYER_OBJ;
                } else {
                    second = e->obj[x];
                    second_layer = LAYER_OBJ;
                    break;
                }
            }
            for (int k = 0; k < count[p] && found < 2; k++) {
                int bg = order[p][k];
                if ((w & (1u << bg)) == 0 || e->bg[bg][x] == NONE) {
                    continue;
                }
                if (found++ == 0) {
                    top = e->bg[bg][x];
                    top_layer = bg;
                } else {
                    second = e->bg[bg][x];
                    second_layer = bg;
                }
            }
        }

        uint32_t c = top;
        if (w & 0x20) {
            int first = (bldcnt >> top_layer) & 1, matched = (bldcnt >> (8 + second_layer)) & 1;
            uint8_t flags = top_layer == LAYER_OBJ ? e->obj_flags[x] : 0;
            if (flags & OBJ_SEMI) {
                /* a semi-transparent OBJ is alpha-blended with a matching second target
                   whatever the effect selected; otherwise it is an ordinary OBJ */
                if (matched) {
                    c = blend(top, second, eva, evb, 4);
                } else if (first && effect >= 2) {
                    c = brightness(top, evy, effect == 2);
                }
            } else if (flags & OBJ_BITMAP) {
                /* a bitmap OBJ blends by its own alpha (OAM attribute 2): EVA = alpha + 1 in
                   sixteenths, EVB the rest; alpha 15 is opaque */
                if (matched) {
                    c = blend(top, second, (uint32_t) e->obj_alpha[x] + 1, 15u - e->obj_alpha[x], 4);
                } else if (first && effect >= 2) {
                    c = brightness(top, evy, effect == 2);
                }
            } else if (top_layer == 0 && bg0_3d && matched) {
                /* the 3D layer over a second target blends by its own alpha, in 32nds
                   (alpha + 1 for the 3D pixel, the rest for the one below), whatever the
                   effect selected and whether or not BG0 is a first target (GBATEK, "DS
                   Video Special Effects"); alpha 31 leaves the 3D pixel as it is */
                uint32_t a = e->alpha3d[x];
                if (a < 31) {
                    c = blend(top, second, a + 1, 31 - a, 5);
                }
            } else if (effect == 1 && first && matched) {
                c = blend(top, second, eva, evb, 4);
            } else if (effect >= 2 && first) {
                c = brightness(top, evy, effect == 2);
            }
        }
        e->out[x] = c;
    }
}

/* Display modes, capture and master brightness ----------------------------------------------- */

static uint32_t fifo_pop(void)
{
    if (fifo_count == 0) {
        return 0;
    }
    uint32_t v = fifo[fifo_head];
    fifo_head = (fifo_head + 1) % FIFO_WORDS;
    fifo_count--;
    return v;
}

/* Display capture (engine A): the line's graphics or 3D output, blended with VRAM or the
 * FIFO, written as 15-bit pixels with an alpha bit into a VRAM bank (GBATEK, "DS Video
 * Capture"). */
static void capture_line(Engine *e, uint32_t y, uint32_t dispcnt, const uint16_t *line3d)
{
    uint32_t cap = reg32(e, R_DISPCAPCNT);
    if (y == 0) {
        e->capturing = (cap & (1u << 31)) != 0;
    }
    if (!e->capturing) {
        return;
    }
    static const uint16_t sizes[4][2] = {{128, 128}, {256, 64}, {256, 128}, {256, 192}};
    uint32_t cw = sizes[(cap >> 20) & 3][0], ch = sizes[(cap >> 20) & 3][1];
    if (y >= ch) {
        return;
    }
    uint32_t eva = cap & 31, evb = (cap >> 8) & 31;
    eva = eva > 16 ? 16 : eva;
    evb = evb > 16 ? 16 : evb;
    uint8_t *dst = io_vram_bank((int) ((cap >> 16) & 3));
    uint32_t write = ((cap >> 18) & 3) * 0x8000u;
    const uint8_t *src_b = io_vram_bank((int) ((dispcnt >> 18) & 3));
    uint32_t read = ((cap >> 26) & 3) * 0x8000u;
    uint32_t source = (cap >> 29) & 3;
    for (uint32_t x = 0; x < cw; x++) {
        uint32_t a, b = 0;
        if (cap & (1u << 24)) {
            a = (line3d != NULL && (line3d[x] & 0x8000)) ? line3d[x] : 0;
        } else {
            uint32_t c = e->out[x];
            a = 0x8000u | ((c >> 1) & 31) | (((c >> 7) & 31) << 5) | (((c >> 13) & 31) << 10);
        }
        if (source != 0) {
            if (cap & (1u << 25)) {
                static uint32_t word;
                if ((x & 1) == 0) {
                    word = fifo_pop();
                }
                b = (word >> (16 * (x & 1))) & 0xffffu;
            } else {
                uint32_t o = (read + (y * cw + x) * 2) & 0x1fffeu;
                b = (uint32_t) src_b[o] | ((uint32_t) src_b[o + 1] << 8);
            }
        }
        uint32_t v;
        if (source == 0) {
            v = a;
        } else if (source == 1) {
            v = b;
        } else {
            /* a source without its alpha bit contributes nothing; the result's alpha bit
               is set when either source's is */
            uint32_t ea = (a & 0x8000) ? eva : 0, eb = (b & 0x8000) ? evb : 0;
            v = ((a | b) & 0x8000u);
            for (int chn = 0; chn < 15; chn += 5) {
                uint32_t c = (((a >> chn) & 31) * ea + ((b >> chn) & 31) * eb) / 16;
                v |= (c > 31 ? 31 : c) << chn;
            }
        }
        uint32_t o = (write + (y * cw + x) * 2) & 0x1fffeu;
        dst[o] = (uint8_t) v;
        dst[o + 1] = (uint8_t) (v >> 8);
    }
}

static void finish_line(Engine *e, uint32_t y, uint32_t dispcnt)
{
    uint32_t *row = e->frame + y * GPU2D_WIDTH;
    uint32_t disp = (dispcnt >> 16) & 3;
    if (e->index == 1) {
        disp &= 1; /* engine B has display off and graphics only */
    }
    switch (disp) {
        case 0:
            for (uint32_t x = 0; x < GPU2D_WIDTH; x++) {
                row[x] = WHITE;
            }
            break;
        case 1:
            if (dispcnt & 0x80) {
                /* forced blank: the engine draws nothing and the screen shows white */
                for (uint32_t x = 0; x < GPU2D_WIDTH; x++) {
                    row[x] = WHITE;
                }
            } else {
                memcpy(row, e->out, sizeof(e->out));
            }
            break;
        case 2: { /* VRAM display: a 256x192 15-bit bitmap at the start of bank A-D */
            const uint8_t *bank = io_vram_bank((int) ((dispcnt >> 18) & 3));
            for (uint32_t x = 0; x < GPU2D_WIDTH; x++) {
                uint32_t o = (y * GPU2D_WIDTH + x) * 2;
                row[x] = rgb15((uint32_t) bank[o] | ((uint32_t) bank[o + 1] << 8));
            }
            break;
        }
        default: /* main memory display: two pixels per FIFO word */
            for (uint32_t x = 0; x < GPU2D_WIDTH; x += 2) {
                uint32_t v = fifo_pop();
                row[x] = rgb15(v & 0xffffu);
                row[x + 1] = rgb15(v >> 16);
            }
            break;
    }
    /* master brightness, applied in every display mode */
    uint32_t mb = reg16(e, R_MASTER_BRIGHT), factor = mb & 31, mode = mb >> 14;
    factor = factor > 16 ? 16 : factor;
    if ((mode == 1 || mode == 2) && factor > 0) {
        for (uint32_t x = 0; x < GPU2D_WIDTH; x++) {
            row[x] = brightness(row[x], factor, mode == 1);
        }
    }
}

/* The line and the frame ------------------------------------------------------------------- */

void gpu2d_line(uint32_t y)
{
    if (y >= GPU2D_HEIGHT) {
        return;
    }
    for (int i = 0; i < 2; i++) {
        Engine *e = &engines[i];
        uint32_t dispcnt = reg32(e, R_DISPCNT);
        if (y == 0) {
            e->ref_reload[0] = e->ref_reload[1] = 1;
        }
        for (int k = 0; k < 2; k++) {
            if (e->ref_reload[k]) {
                /* BGxX/BGxY are 28-bit signed fixed point (GBATEK: bits 0-27, sign in 27) */
                e->ref_x[k] = (int32_t) (reg32(e, 0x28 + 0x10 * (uint32_t) k) << 4) >> 4;
                e->ref_y[k] = (int32_t) (reg32(e, 0x2c + 0x10 * (uint32_t) k) << 4) >> 4;
                e->ref_reload[k] = 0;
            }
        }
        draw_bgs(e, y, dispcnt);
        draw_objs(e, y, dispcnt);
        build_window(e, y, dispcnt);
        compose(e, y, dispcnt);
        if (i == 0) {
            capture_line(e, y, dispcnt, (dispcnt & 8) ? gpu3d_line((int) y) : NULL);
        }
        finish_line(e, y, dispcnt);
    }
}

void gpu2d_frame_end(void)
{
    /* POWCNT1 bit 15: engine A on the upper LCD when set, else on the lower one. */
    int a_on_top = (io_reg(0x04000000u + R_POWCNT1) & 0x8000u) != 0;
    for (int i = 0; i < 2; i++) {
        uint32_t *dst = screens[(i == 0) == a_on_top ? 1 : 0];
        const uint32_t *src = engines[i].frame;
        for (uint32_t k = 0; k < GPU2D_HEIGHT * GPU2D_WIDTH; k++) {
            uint32_t c = src[k], r = c & 63, g = (c >> 6) & 63, b = (c >> 12) & 63;
            /* 6 bits to 8: repeat the top bits so 63 becomes 255 */
            dst[k] = (((r << 2) | (r >> 4)) << 16) | (((g << 2) | (g >> 4)) << 8) | ((b << 2) | (b >> 4));
        }
    }
    /* a display capture runs for one frame: the enable bit clears itself when it ends */
    if (engines[0].capturing) {
        engines[0].capturing = 0;
        io_reg_store(R_DISPCAPCNT, io_reg(0x04000000u + R_DISPCAPCNT) & ~(1u << 31));
    }
    frames_done++;
    frame_output(io_frame(), screens[1], screens[0]);
}

void gpu2d_register_written(uint32_t offset, uint32_t value)
{
    uint32_t o = offset & 0xfffu;
    Engine *e = &engines[offset >= 0x1000 ? 1 : 0];
    if (o >= 0x28 && o < 0x40) {
        e->ref_reload[(o - 0x28) / 0x10] = 1; /* BG2X/Y, BG3X/Y: reload before the next line */
    } else if (offset == 0x68) {
        if (fifo_count < FIFO_WORDS) {
            fifo[(fifo_head + fifo_count++) % FIFO_WORDS] = value;
        }
    }
}

uint32_t gpu2d_frames(void)
{
    return frames_done;
}

const uint32_t *gpu2d_screen(int top)
{
    return screens[top ? 1 : 0];
}

void gpu2d_init(void)
{
    memset(engines, 0, sizeof(engines));
    memset(screens, 0, sizeof(screens));
    frames_done = 0;
    fifo_head = fifo_count = 0;
    engines[0].index = 0;
    engines[0].reg = 0;
    engines[0].bg_base = 0x06000000u;
    engines[0].bg_mask = 0x7ffffu;
    engines[0].obj_base = 0x06400000u;
    engines[0].obj_mask = 0x3ffffu;
    engines[0].palette = 0x000;
    engines[0].oam = 0x000;
    engines[1].index = 1;
    engines[1].reg = 0x1000;
    engines[1].bg_base = 0x06200000u;
    engines[1].bg_mask = 0x1ffffu;
    engines[1].obj_base = 0x06600000u;
    engines[1].obj_mask = 0x1ffffu;
    engines[1].palette = 0x400;
    engines[1].oam = 0x400;
}
