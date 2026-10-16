/* The OBJ attribute copies and the drawing of cells into them (oam_buffer.h). */
#include "oam_buffer.h"

#include "clean.h"

static_assert(sizeof(OamEntry) == 8, "OamEntry");

#define FX32_ONE 0x1000
#define FX32_HALF 0x800
#define SCREEN_WIDTH 0x100
#define SCREEN_HEIGHT 0xc0
#define OAM_BUFFER_SIZE (OAM_BUFFER_ENTRIES * (int) sizeof(OamEntry))
#define AFFINE_GROUP 4 /* entries per affine group */
#define OAM_HIDDEN_Y 0xc0

/* The affine mode (attribute 0 bits 8-9) as it sits in the first word of an entry. */
#define MODE_AFFINE 0x100u
#define MODE_AFFINE_DOUBLE 0x300u
/* The flips (attribute 1 bits 12-13) as they sit in the first word of an entry. */
#define WORD_FLIP_H 0x10000000u
#define WORD_FLIP_V 0x20000000u
#define WORD_FLIPS (WORD_FLIP_H | WORD_FLIP_V)
/* The shape (attribute 0 bits 14-15) and size (attribute 1 bits 14-15), kept as they are. */
#define WORD_SHAPE_SIZE 0xc000c000u
#define OBJ_MODE_BITMAP 3

/* The OBJ's affine mode (attribute 0 bits 8-9). */
#define OBJ_AFFINE_OFF 0
#define OBJ_AFFINE_ON 1
#define OBJ_AFFINE_DOUBLE 3

extern OamEntry data_021d2920[OAM_BUFFER_ENTRIES]; /* the main engine's copy */
extern OamEntry data_021d2d20[OAM_BUFFER_ENTRIES]; /* the sub engine's copy */
extern int data_021d2910;                          /* the main copy's affine entries used */
extern int data_021d2914;                          /* the main copy's OBJs used */
extern int data_021d2918;                          /* the sub copy's affine entries used */
extern int data_021d291c;                          /* the sub copy's OBJs used */
extern int data_021c8c9c;                          /* 1 when the 3D screen is the top one */
extern const int data_020d09d4[];                  /* OBJ heights by shape and size */
extern const int data_020d0a04[];                  /* OBJ widths by shape and size */
extern const fx16 FX_SinCosTable_[];

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);
extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern void DC_FlushRange(const void *start, u32 size);
extern void GX_LoadOAM(const void *src, u32 offset, u32 size);
extern void GXS_LoadOAM(const void *src, u32 offset, u32 size);

/* An int shifted left as the ARM does it (no overflow). */
static int shl(int value, int shift)
{
    return (int) ((u32) value << shift);
}

/* A 20.12 value rounded to a whole number away from zero at the half (zero rounds down). */
static int round_fx(fx32 value)
{
    return (value + (value > 0 ? FX32_HALF : -FX32_HALF)) >> 12;
}

/* A 20.12 product rounded to 20.12. */
static fx32 scaled(int sin_cos, fx32 scale)
{
    return (sin_cos * scale + FX32_HALF) >> 12;
}

static u32 obj_word(const OamEntry *obj)
{
    return obj->attr0 | (u32) obj->attr1 << 16;
}

static int obj_x(const OamEntry *obj)
{
    int x = obj->attr1 & 0x1ff;
    return x >= 0x100 ? x - 0x200 : x;
}

static int obj_y(const OamEntry *obj)
{
    return (s8) (obj->attr0 & 0xff);
}

static int obj_affine_mode(const OamEntry *obj)
{
    return (obj->attr0 >> 8) & 3;
}

static int obj_mode(const OamEntry *obj)
{
    return (obj->attr0 >> 10) & 3;
}

static int obj_last(const OamEntry *obj)
{
    return obj->affine == OAM_BUFFER_CELL_LAST;
}

/* The copy, its OBJ count and its affine count for a screen. */
typedef struct OamBufferTarget {
    OamEntry *oam;
    int *count;
    int *affine_used;
} OamBufferTarget;

static OamBufferTarget target_of(int screen)
{
    OamBufferTarget target;
    if (OamBuffer_IsMain((u32) screen)) {
        target.oam = data_021d2920;
        target.count = &data_021d2914;
        target.affine_used = &data_021d2910;
    } else {
        target.oam = data_021d2d20;
        target.count = &data_021d291c;
        target.affine_used = &data_021d2918;
    }
    return target;
}

/* Whether a box at (x, y) of `w` by `h` reaches the screen (edges included). */
static int on_screen(int x, int y, int w, int h)
{
    return x + w >= 0 && x <= SCREEN_WIDTH && y + h >= 0 && y <= SCREEN_HEIGHT;
}

/* The affine parameters for an angle and scales, with the OBJ's flips turned into signs.
 * `index` is twice the angle's step in the sine table (FX_SinCosTable_ holds sine, cosine). */
static void affine_params(OamAffine *params, const OamEntry *obj, int index, fx32 scale_x, fx32 scale_y)
{
    int cosine = FX_SinCosTable_[index + 1];
    int sine = FX_SinCosTable_[index];
    params->a = scaled(cosine, scale_x);
    params->b = scaled(sine, scale_x);
    params->c = -scaled(sine, scale_y);
    params->d = scaled(cosine, scale_y);
    if (obj_word(obj) & WORD_FLIP_H) {
        params->a = -params->a;
        params->b = -params->b;
    }
    if (obj_word(obj) & WORD_FLIP_V) {
        params->c = -params->c;
        params->d = -params->d;
    }
}

/* Writes an OBJ's attributes into `entry`: `mode` holds the affine mode and flips for the
 * first word; the affine index goes in only when `mode` is exactly an affine mode, and the
 * 256-colour bit only when the OBJ mode is not bitmap. */
static void put_obj(OamEntry *entry, const OamEntry *obj, u32 mode, int affine_index, int mode_bits, int x, int y, int palette,
                    int priority)
{
    u32 word = mode | (u32) (x & 0x1ff) << 16 | (obj_word(obj) & WORD_SHAPE_SIZE) | (u32) ((obj->attr0 >> 12) & 1) << 12 |
               (u32) mode_bits << 10 | (u32) (y & 0xff);
    if (mode == MODE_AFFINE || mode == MODE_AFFINE_DOUBLE) {
        word |= (u32) affine_index << 25;
    }
    if (mode_bits != OBJ_MODE_BITMAP) {
        word |= (u32) ((obj->attr0 >> 13) & 1) << 13;
    }
    entry->attr0 = (u16) word;
    entry->attr1 = (u16) (word >> 16);
    entry->attr2 = (u16) (shl(palette, 12) | (obj->attr2 & 0x3ff) | shl(priority, 10));
}

/* func_02088c14: whether `screen` (OAM_BUFFER_SCREEN_...) is drawn by the main engine. */
int OamBuffer_IsMain(u32 screen)
{
    switch (screen) {
        case OAM_BUFFER_SCREEN_MAIN:
            return 1;
        case OAM_BUFFER_SCREEN_SUB:
            return 0;
        case OAM_BUFFER_SCREEN_3D:
            return data_021c8c9c == 1;
        case OAM_BUFFER_SCREEN_OTHER:
            return data_021c8c9c == 0;
        default:
            return 0;
    }
}
CLEAN_AS(func_02088c14, OamBuffer_IsMain)

/* func_02088c60: the affine group of the copy `oam` that holds `params` (each taken to 8.8, as
 * 16 bits), else a new one after the `*used` entries in use; -1 when all 32 groups are used. */
int OamBuffer_FindAffine(OamEntry *oam, int *used, const OamAffine *params)
{
    u16 a = (u16) ((u32) params->a >> 4);
    u16 b = (u16) ((u32) params->b >> 4);
    u16 c = (u16) ((u32) params->c >> 4);
    u16 d = (u16) ((u32) params->d >> 4);
    int count = *used;

    for (int i = 0; i < count; i += AFFINE_GROUP) {
        const OamEntry *group = &oam[i];
        if (group[0].affine == a && group[1].affine == b && group[2].affine == c && group[3].affine == d) {
            return i >> 2;
        }
    }
    if (count < OAM_BUFFER_ENTRIES) {
        OamEntry *group = &oam[count];
        group[0].affine = a;
        group[1].affine = b;
        group[2].affine = c;
        group[3].affine = d;
        int index = *used >> 2;
        *used += AFFINE_GROUP;
        return index;
    }
    return -1;
}
CLEAN_AS(func_02088c60, OamBuffer_FindAffine)

/* func_02088cf4: the first of `count` OBJs whose box, widened by the margins on each side,
 * holds (x, y); -1 for none. */
int OamBuffer_FindObjAt(const OamEntry *objs, int count, int x, int y, int margin_x, int margin_y)
{
    for (int i = 0; i < count; i++) {
        if (OamBuffer_ObjContains(objs, x, y, margin_x, margin_y)) {
            return i;
        }
        objs++;
    }
    return -1;
}
CLEAN_AS(func_02088cf4, OamBuffer_FindObjAt)

/* func_02088d34: whether the OBJ's box, widened by the margins on each side, holds (x, y) (its
 * edges included). */
int OamBuffer_ObjContains(const OamEntry *obj, int x, int y, int margin_x, int margin_y)
{
    int left = OamBuffer_ObjX(obj) - margin_x;
    if (left > x) {
        return 0;
    }
    if (left + shl(margin_x, 1) + (int) OamBuffer_ObjWidth(obj) < x) {
        return 0;
    }
    int top = OamBuffer_ObjY(obj) - margin_y;
    if (top > y) {
        return 0;
    }
    if (top + shl(margin_y, 1) + OamBuffer_ObjHeight(obj) < y) {
        return 0;
    }
    return 1;
}
CLEAN_AS(func_02088d34, OamBuffer_ObjContains)

/* func_02088d94: the OBJ's y (-128 to 127). */
int OamBuffer_ObjY(const OamEntry *obj)
{
    return obj_y(obj);
}
CLEAN_AS(func_02088d94, OamBuffer_ObjY)

/* func_02088d9c: the OBJ's x (-256 to 255). */
int OamBuffer_ObjX(const OamEntry *obj)
{
    return obj_x(obj);
}
CLEAN_AS(func_02088d9c, OamBuffer_ObjX)

/* func_02088db8: the OBJ's height in pixels. */
int OamBuffer_ObjHeight(const OamEntry *obj)
{
    return OamBuffer_ShapeHeight(obj->attr0 >> 14, obj->attr1 >> 14);
}
CLEAN_AS(func_02088db8, OamBuffer_ObjHeight)

/* func_02088dc8: the height of an OBJ of this shape and size.
 * QUIRK: shape 3 (which the hardware forbids) reads the widths' table that follows. */
int OamBuffer_ShapeHeight(int shape, int size)
{
    return data_020d09d4[shape * 4 + size];
}
CLEAN_AS(func_02088dc8, OamBuffer_ShapeHeight)

/* func_02088dd8: the OBJ's width in pixels. */
unsigned int OamBuffer_ObjWidth(const OamEntry *obj)
{
    return (unsigned int) OamBuffer_ShapeWidth(obj->attr0 >> 14, obj->attr1 >> 14);
}
CLEAN_AS(func_02088dd8, OamBuffer_ObjWidth)

/* func_02088de8: the width of an OBJ of this shape and size. */
int OamBuffer_ShapeWidth(int shape, int size)
{
    return data_020d0a04[shape * 4 + size];
}
CLEAN_AS(func_02088de8, OamBuffer_ShapeWidth)

/* func_02088df8: the cell's OBJs drawn round (x, y), scaled by `scale_x` and `scale_y` and
 * turned by `angle` about each OBJ's own centre, until the copy is full. A palette or priority
 * of -1 keeps the OBJ's own; an `obj_mode` above 0 replaces the OBJ mode; `flip_h` and `flip_v`
 * add the flips. OBJs off the screen or without a free affine group are left out.
 *
 * Scaled or turned, each OBJ becomes an affine one: one of affine mode 0 is drawn double-size
 * (its box twice as large and its corner moved back by half its size), one of mode 1 keeps its
 * size and one of mode 3 is taken at its doubled size; its place is divided by the scales and
 * turned with rounding. Turned, the screen test takes the larger of width and height for both.
 *
 * QUIRK: the place uses the angle's low 16 bits but the affine parameters use the whole int,
 *        so an angle outside 0 to 0xffff reads another part of the sine table for them.
 * QUIRK: `flip_h` or `flip_v` on an affine OBJ makes the mode no longer exactly affine: the
 *        flip bits then stand as the top bits of the affine index (group 8, 16 or 24) and the
 *        index found is left out. */
void OamBuffer_DrawCell(int screen, const OamEntry *obj, int x, int y, int palette, int priority, fx32 scale_x, fx32 scale_y,
                        int angle, int obj_mode_override, int flip_h, int flip_v)
{
    OamBufferTarget target = target_of(screen);
    OamEntry *entry = &target.oam[*target.count];
    int affine = scale_x != FX32_ONE || scale_y != FX32_ONE || angle != 0;
    const fx16 *sine = &FX_SinCosTable_[((u16) angle >> 4) * 2];
    const fx16 *cosine = sine + 1;
    int param_index = (angle >> 4) * 2;

    for (;;) {
        if (*target.count >= OAM_BUFFER_ENTRIES) {
            break;
        }
        int was_double = affine && obj_affine_mode(obj) == OBJ_AFFINE_DOUBLE;
        int becomes_double = affine && obj_affine_mode(obj) == OBJ_AFFINE_OFF;
        int stays_size = affine && obj_affine_mode(obj) == OBJ_AFFINE_ON;

        int ox = obj_x(obj);
        int oy = obj_y(obj);
        int w = (int) OamBuffer_ObjWidth(obj);
        int h = OamBuffer_ObjHeight(obj);

        if (affine) {
            if (was_double) {
                w = shl(w, 1);
                h = shl(h, 1);
            }
            int half_w = w >> 1;
            int half_h = h >> 1;
            fx32 fx = shl(ox + half_w, 12);
            fx32 fy = shl(oy + half_h, 12);
            if (scale_x != FX32_ONE) {
                fx = FX_Div(fx, scale_x);
            }
            if (scale_y != FX32_ONE) {
                fy = FX_Div(fy, scale_y);
            }
            if (angle != 0) {
                int s = *sine;
                int c = *cosine;
                fx32 tx = FX_MulFunc(c, fx);
                tx -= FX_MulFunc(s, fy);
                fx32 ty = FX_MulFunc(c, fy);
                ty += FX_MulFunc(s, fx);
                ox = round_fx(tx) - half_w;
                oy = round_fx(ty) - half_h;
            } else {
                ox = ((fx + FX32_HALF) >> 12) - half_w;
                oy = ((fy + FX32_HALF) >> 12) - half_h;
            }
            if (becomes_double) {
                ox -= half_w;
                oy -= half_h;
                w = shl(w, 1);
                h = shl(h, 1);
            }
        }
        ox += x;
        oy += y;

        int visible;
        if (angle != 0) {
            int size = w >= h ? w : h;
            visible = on_screen(ox, oy, size, size);
        } else {
            visible = on_screen(ox, oy, w, h);
        }

        if (visible) {
            int pal = palette == -1 ? obj->attr2 >> 12 : palette;
            int prio = priority == -1 ? (obj->attr2 >> 10) & 3 : priority;
            int mode_bits = obj_mode_override > 0 ? obj_mode_override : obj_mode(obj);
            int affine_index = 0;
            u32 mode;
            if (affine) {
                OamAffine params;
                affine_params(&params, obj, param_index, scale_x, scale_y);
                affine_index = OamBuffer_FindAffine(target.oam, target.affine_used, &params);
                mode = stays_size ? MODE_AFFINE : MODE_AFFINE_DOUBLE;
            } else {
                mode = obj_word(obj) & WORD_FLIPS;
            }
            if (affine_index != -1) {
                if (flip_h != 0) {
                    mode |= WORD_FLIP_H;
                }
                if (flip_v != 0) {
                    mode |= WORD_FLIP_V;
                }
                put_obj(entry, obj, mode, affine_index, mode_bits, ox, oy, pal, prio);
                entry++;
                *target.count += 1;
            }
        }

        if (obj_last(obj)) {
            break;
        }
        obj++;
    }
}
CLEAN_AS(func_02088df8, OamBuffer_DrawCell)

/* func_02089300: one OBJ drawn at (x, y) plus its own place, scaled by `scale` and turned by
 * `angle`; the entry written, or NULL when the copy is full, the OBJ is off the screen or no
 * affine group is free. A palette or priority of -1 keeps the OBJ's own.
 *
 * Turned, the OBJ's place is turned about its centre: with `rounded`, through FX_MulFunc and
 * rounded away from zero; else by plain products, rounded down. Scaled or turned, an OBJ of
 * affine mode 1 keeps its size and any other is drawn double-size (its box twice as large and
 * its corner moved back by half its size), and the screen test of a turned one takes the
 * larger of width and height for both.
 * QUIRK: as in OamBuffer_DrawCell, the place uses the angle's low 16 bits and the affine
 *        parameters the whole int. The parameters scale both axes by `scale`. */
OamEntry *OamBuffer_DrawObjRotated(int screen, const OamEntry *obj, int x, int y, int palette, int priority, fx32 scale,
                                   int angle, int rounded)
{
    OamBufferTarget target;
    if (OamBuffer_IsMain((u32) screen)) {
        target.count = &data_021d2914;
        if (*target.count >= OAM_BUFFER_ENTRIES) {
            return NULL;
        }
        target.oam = data_021d2920;
        target.affine_used = &data_021d2910;
    } else {
        target.count = &data_021d291c;
        if (*target.count >= OAM_BUFFER_ENTRIES) {
            return NULL;
        }
        target.oam = data_021d2d20;
        target.affine_used = &data_021d2918;
    }
    OamEntry *entry = &target.oam[*target.count];

    int ox = obj_x(obj);
    int oy = obj_y(obj);
    int w = (int) OamBuffer_ObjWidth(obj);
    int h = OamBuffer_ObjHeight(obj);

    if (angle != 0) {
        int index = ((u16) angle >> 4) * 2;
        int half_w = w >> 1;
        int half_h = h >> 1;
        int cx = ox + half_w;
        int cy = oy + half_h;
        int s = FX_SinCosTable_[index];
        int c = FX_SinCosTable_[index + 1];
        if (rounded) {
            fx32 tx = FX_MulFunc(c, cx);
            tx -= FX_MulFunc(s, cy);
            fx32 ty = FX_MulFunc(c, cy);
            ty += FX_MulFunc(s, cx);
            ox = round_fx(tx) - half_w;
            oy = round_fx(ty) - half_h;
        } else {
            ox = ((cx * c - cy * s) >> 12) - half_w;
            oy = ((cy * c + cx * s) >> 12) - half_h;
        }
    }

    int affine = scale != FX32_ONE || angle != 0;
    if (affine && obj_affine_mode(obj) != OBJ_AFFINE_ON) {
        ox -= w >> 1;
        oy -= h >> 1;
        w = shl(w, 1);
        h = shl(h, 1);
    }
    ox += x;
    oy += y;

    if (angle != 0) {
        int size = w >= h ? w : h;
        if (!on_screen(ox, oy, size, size)) {
            return NULL;
        }
    } else if (!on_screen(ox, oy, w, h)) {
        return NULL;
    }

    if (palette == -1) {
        palette = obj->attr2 >> 12;
    }
    if (priority == -1) {
        priority = (obj->attr2 >> 10) & 3;
    }

    int affine_index = 0;
    u32 mode;
    if (affine) {
        OamAffine params;
        affine_params(&params, obj, (angle >> 4) * 2, scale, scale);
        affine_index = OamBuffer_FindAffine(target.oam, target.affine_used, &params);
        if (affine_index == -1) {
            return NULL;
        }
        mode = obj_affine_mode(obj) == OBJ_AFFINE_ON ? MODE_AFFINE : MODE_AFFINE_DOUBLE;
    } else {
        mode = obj_word(obj) & WORD_FLIPS;
    }

    put_obj(entry, obj, mode, affine_index, obj_mode(obj), ox, oy, palette, priority);
    *target.count += 1;
    return entry;
}
CLEAN_AS(func_02089300, OamBuffer_DrawObjRotated)

/* func_020896b8: one OBJ drawn at (x, y) plus its own place, with the
 * affine parameters `params` when it is not NULL (an OBJ of affine mode 1 keeps its size, any
 * other is drawn double-size, its box twice as large and its corner moved back by half its
 * size). A palette or priority of -1 keeps the OBJ's own. 1 when drawn; -1 when the copy is
 * full, -2 off the screen sideways, -3 off it up or down, -4 with no affine group free. */
int OamBuffer_DrawObjAffine(int screen, const OamEntry *obj, int x, int y, int palette, int priority, const OamAffine *params)
{
    OamBufferTarget target;
    if (OamBuffer_IsMain((u32) screen)) {
        target.count = &data_021d2914;
        if (*target.count >= OAM_BUFFER_ENTRIES) {
            return -1;
        }
        target.oam = data_021d2920;
        target.affine_used = &data_021d2910;
    } else {
        target.count = &data_021d291c;
        if (*target.count >= OAM_BUFFER_ENTRIES) {
            return -1;
        }
        target.oam = data_021d2d20;
        target.affine_used = &data_021d2918;
    }
    OamEntry *entry = &target.oam[*target.count];

    int ox = obj_x(obj) + x;
    int oy = obj_y(obj) + y;
    int w = (int) OamBuffer_ObjWidth(obj);
    int h = OamBuffer_ObjHeight(obj);
    if (params != NULL && obj_affine_mode(obj) != OBJ_AFFINE_ON) {
        ox -= w >> 1;
        oy -= h >> 1;
        w = shl(w, 1);
        h = shl(h, 1);
    }
    if (ox + w < 0 || ox > SCREEN_WIDTH) {
        return -2;
    }
    if (oy + h < 0 || oy > SCREEN_HEIGHT) {
        return -3;
    }

    if (palette == -1) {
        palette = obj->attr2 >> 12;
    }
    if (priority == -1) {
        priority = (obj->attr2 >> 10) & 3;
    }

    int affine_index = 0;
    u32 mode;
    if (params != NULL) {
        affine_index = OamBuffer_FindAffine(target.oam, target.affine_used, params);
        if (affine_index == -1) {
            return -4;
        }
        mode = obj_affine_mode(obj) == OBJ_AFFINE_ON ? MODE_AFFINE : MODE_AFFINE_DOUBLE;
    } else {
        mode = obj_word(obj) & WORD_FLIPS;
    }

    put_obj(entry, obj, mode, affine_index, obj_mode(obj), ox, oy, palette, priority);
    *target.count += 1;
    return 1;
}
CLEAN_AS(func_020896b8, OamBuffer_DrawObjAffine)

/* func_020898e8: both copies emptied: every entry hidden (y 192, attributes 1 and 2 zero) and
 * both counts of both copies cleared.
 * QUIRK: the first entry is set and then spread by copies that overlap their own source (one
 * word, then 32 bytes at a time), so the first entry's affine halfword is kept and repeated
 * into every entry of both copies. */
void OamBuffer_Reset(void)
{
    OamEntry *first = &data_021d2920[0];
    first->attr0 = OAM_HIDDEN_Y;
    first->attr1 = 0;
    first->attr2 = 0;
    MIi_CpuCopy32(first, &data_021d2920[1], 3 * sizeof(OamEntry));
    MIi_CpuCopyFast(first, &data_021d2920[AFFINE_GROUP], (OAM_BUFFER_ENTRIES - AFFINE_GROUP) * sizeof(OamEntry));
    MIi_CpuCopyFast(first, data_021d2d20, OAM_BUFFER_SIZE);
    data_021d2914 = 0;
    data_021d2910 = 0;
    data_021d291c = 0;
    data_021d2918 = 0;
}
CLEAN_AS(func_020898e8, OamBuffer_Reset)

/* func_02089954: both copies written back from the data cache. */
void OamBuffer_Flush(void)
{
    DC_FlushRange(data_021d2920, OAM_BUFFER_SIZE);
    DC_FlushRange(data_021d2d20, OAM_BUFFER_SIZE);
}
CLEAN_AS(func_02089954, OamBuffer_Flush)

/* func_0208997c: both copies loaded into the engines' OAM. */
void OamBuffer_Load(void)
{
    GX_LoadOAM(data_021d2920, 0, OAM_BUFFER_SIZE);
    GXS_LoadOAM(data_021d2d20, 0, OAM_BUFFER_SIZE);
}
CLEAN_AS(func_0208997c, OamBuffer_Load)
