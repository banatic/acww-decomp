/* Drawing the text boxes (text_draw.h). */
#include "text_draw.h"

#include "autoload_2/heap.h"    /* Heap_Free, Heap_Delete, ExpHeap_Create, Heap_FreeAux, ... */
#include "autoload_2/process.h" /* Process_Construct, Process_Destruct */
#include "clean.h"
#include "letter_grade.h"

static_assert(offsetof(TextDrawBox, text) == 0x10, "TextDrawBox text");
static_assert(offsetof(TextDrawBox, first_tile) == 0x18, "TextDrawBox first_tile");
static_assert(offsetof(TextDrawBox, font) == 0x28, "TextDrawBox font");
static_assert(offsetof(TextDrawBox, color) == 0x38, "TextDrawBox color");
static_assert(offsetof(TextDrawBox, mark_colors) == 0x3a, "TextDrawBox mark_colors");
static_assert(offsetof(TextDrawBox, marks) == 0x40, "TextDrawBox marks");
static_assert(offsetof(TextDrawBox, screens) == 0x50, "TextDrawBox screens");
static_assert(offsetof(TextDrawBox, pending) == 0x54, "TextDrawBox pending");
static_assert(offsetof(TextDrawBox, update_mode) == 0x58, "TextDrawBox update_mode");
static_assert(offsetof(TextDrawBox, row_bytes) == 0x60, "TextDrawBox row_bytes");
static_assert(offsetof(TextDrawBox, pen) == 0x68, "TextDrawBox pen");
static_assert(offsetof(TextDrawBox, start_color) == 0x74, "TextDrawBox start_color");
static_assert(offsetof(TextDrawBox, char_index) == 0x78, "TextDrawBox char_index");
static_assert(sizeof(TextDrawBox) == 0x7c, "TextDrawBox size");

/* The strip buffer: 32 tiles of 8x8 pixels at 4 bits per pixel, a pixel's two neighbours in a
 * byte (the even x in the low half). */
#define STRIP_TILES 32
#define TILE_BYTES 32
#define STRIP_BYTES (STRIP_TILES * TILE_BYTES)
#define STRIP_HEIGHT 8

/* The pixel row of a strip the underline is drawn in. */
#define UNDERLINE_Y 6

/* The character drawn for one the font has no glyph for. */
#define MISSING_CHAR_CODE 0xff20

/* The size of the heap the boxes are allocated in. */
#define BOX_HEAP_SIZE 0x1800

/* The box vtable's slots (the derived class's: func_020a8e04 and func_020a8db8). */
#define BOX_SLOT_DESTRUCT 0
#define BOX_SLOT_DRAW_STRIP 2
#define BOX_SLOT_MEASURE 3

/* The size of the text process (a Process with nothing of its own). */
#define TEXT_PROCESS_SIZE 0x50

/* A glyph's bitmap as read from the font's image file, at most. */
#define GLYPH_BITMAP_MAX 0x84

extern u8 data_021c8344[STRIP_BYTES]; /* the strip */
extern Heap *data_021c8194;           /* the boxes' heap, or NULL */
extern u8 data_021c81bc[];            /* the list of boxes (an NNSFndList) */
extern Heap *data_021fbe94;           /* the game's main heap */

/* The four fonts and their names. */
extern TextFont data_021c8230;     /* fontA: the one a box starts with */
extern TextFont data_021c828c;     /* fontB */
extern TextFont data_021c82e8;     /* fontC */
extern TextFont data_021c81d4;     /* fontD */
extern const char data_020dcf88[]; /* "fontA" */
extern const char data_020dcf90[]; /* "fontB" */
extern const char data_020dcf98[]; /* "fontC" */
extern const char data_020dcfa0[]; /* "fontD" */

/* The tile loaders by layer (BG0-BG3, objects; slot 5 is NULL): GX_Load...Char of the main
 * screen and GXS_Load...Char of the sub screen. */
extern const u32 data_020cb920[];
extern const u32 data_020cb938[];

/* The text process's vtable and its base class's. */
extern const u32 data_020dcf40[];
extern const u32 data_020da13c[];

extern void DC_FlushRange(const void *start, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void NNS_FndRemoveListObject(void *list, void *object);
extern void NNS_FndInitList(void *list, u16 link_offset);
extern int FS_SeekFile(void *file, u32 offset, int origin);
extern int FS_ReadFile(void *file, void *dst, u32 size);

typedef void TileLoader(const void *src, u32 offset, u32 size);
typedef void *BoxDestruct(TextDrawBox *box);
typedef void BoxDrawStrip(TextDrawBox *box);
typedef u32 BoxMeasure(TextDrawBox *box);

static uintptr_t box_slot(const TextDrawBox *box, int slot)
{
    return box->vtable[slot];
}

/* The width of the box's text, in pixels (vtable slot 3). */
static u32 measure(TextDrawBox *box)
{
    return ((BoxMeasure *) box_slot(box, BOX_SLOT_MEASURE))(box);
}

/* Pixel (x, y) of the strip set to `color`; nothing past the strip's 32 tiles. QUIRK: a colour
 * above 15 spills into the neighbouring pixel when set in the low half of a byte, and loses its
 * high bits in the high half. */
static void put_pixel(u32 x, u32 y, u8 color)
{
    u32 tile = x >> 3;
    if (tile >= STRIP_TILES) {
        return;
    }
    u8 *byte = &data_021c8344[tile * TILE_BYTES + ((y * 8 + (x & 7)) >> 1)];
    if (x & 1) {
        *byte = (u8) ((*byte & 0x0f) | (u8) (color << 4));
    } else {
        *byte = (u8) ((*byte & 0xf0) | color);
    }
}

/* The strip's first `size` bytes sent to the screens' tiles at `offset`, as `screens` says. */
static void load_tiles(TextDrawBox *box, u32 offset, u32 size)
{
    if (box->screens == TEXT_DRAW_TO_MAIN || box->screens == TEXT_DRAW_TO_BOTH) {
        ((TileLoader *) (uintptr_t) data_020cb920[box->layer])(data_021c8344, offset, size);
    }
    if (box->screens == TEXT_DRAW_TO_SUB || box->screens == TEXT_DRAW_TO_BOTH) {
        ((TileLoader *) (uintptr_t) data_020cb938[box->layer])(data_021c8344, offset, size);
    }
}

/* How far apart the destination's rows are, in bytes. */
static u32 row_stride(const TextDrawBox *box)
{
    return box->rows_full_width ? STRIP_BYTES : box->row_bytes;
}

static int in_mark(const TextDrawBox *box, int mark)
{
    const TextDrawMarkRange *range = &box->marks[mark];
    return box->char_index >= range->first && box->char_index < range->first + range->count;
}

/* func_02050e24: every box taken off the list, destructed (vtable slot 0) and freed. */
void TextDraw_FreeBoxes(void)
{
    void *box;

    while ((box = NNS_FndGetNextListObject(data_021c81bc, NULL)) != NULL) {
        NNS_FndRemoveListObject(data_021c81bc, box);
        ((BoxDestruct *) box_slot(box, BOX_SLOT_DESTRUCT))(box);
        Heap_Free(data_021c8194, box);
    }
}
CLEAN_AS(func_02050e24, TextDraw_FreeBoxes)

/* func_02050e68 */
void TextDraw_FlushGroup0(void)
{
    TextDraw_Flush(TEXT_DRAW_GROUP_0);
}
CLEAN_AS(func_02050e68, TextDraw_FlushGroup0)

/* func_02050e74: the background of the character being drawn: a mark's when it is in one (the
 * first mark wins), else the box's. */
unsigned char TextDraw_BackgroundColor(TextDrawBox *box)
{
    if (TextDraw_InMark1(box)) {
        return box->mark_colors[0].background;
    }
    if (TextDraw_InMark2(box)) {
        return box->mark_colors[1].background;
    }
    return box->background;
}
CLEAN_AS(func_02050e74, TextDraw_BackgroundColor)

/* func_02050ea8: the colour of the character being drawn, the same way. */
unsigned char TextDraw_TextColor(TextDrawBox *box)
{
    if (TextDraw_InMark1(box)) {
        return box->mark_colors[0].color;
    }
    if (TextDraw_InMark2(box)) {
        return box->mark_colors[1].color;
    }
    return box->color;
}
CLEAN_AS(func_02050ea8, TextDraw_TextColor)

/* func_02050edc: whether the character being drawn is in the second mark. QUIRK: the range's end
 * is computed in 32 bits and wraps. */
int TextDraw_InMark2(TextDrawBox *box)
{
    return in_mark(box, 1);
}
CLEAN_AS(func_02050edc, TextDraw_InMark2)

/* func_02050ef4: the same for the first mark. */
int TextDraw_InMark1(TextDrawBox *box)
{
    return in_mark(box, 0);
}
CLEAN_AS(func_02050ef4, TextDraw_InMark1)

/* func_02050f0c: the box's rows filled with its background colour at the destination, over
 * `clear_cells` tiles (all its width when 0; at most a strip). In RAM the rows start at
 * `ram_dest`; in VRAM at `first_tile`, or at offset 0 when it is -1. */
void TextDraw_ClearRows(TextDrawBox *box)
{
    TextDraw_FillBackground(box);

    u32 size = box->clear_cells == 0 ? box->row_bytes : (u32) box->clear_cells * TILE_BYTES;
    if (size > STRIP_BYTES) {
        size = STRIP_BYTES;
    }
    u32 offset = box->first_tile != -1 ? (u32) box->first_tile * TILE_BYTES : 0;

    for (u32 row = 0; row < box->rows; row++) {
        DC_FlushRange(data_021c8344, size);
        load_tiles(box, offset, size);
        if (box->screens == TEXT_DRAW_TO_RAM) {
            MI_CpuCopy8(data_021c8344, (void *) (uintptr_t) (box->ram_dest + offset), size);
        }
        offset += row_stride(box);
    }
}
CLEAN_AS(func_02050f0c, TextDraw_ClearRows)

/* func_02050fc8: the underline from x `start` to the pen, in the text's colour. */
void TextDraw_Underline(TextDrawBox *box, unsigned int start)
{
    u8 color = TextDraw_TextColor(box);

    for (u32 x = start; x < box->pen; x++) {
        put_pixel(x, UNDERLINE_Y, color);
    }
}
CLEAN_AS(func_02050fc8, TextDraw_Underline)

/* func_02051034: in a mark, the gap after a glyph (`spacing` pixels from the pen) painted with
 * the mark's background. */
void TextDraw_FillSpacing(TextDrawBox *box)
{
    if (!TextDraw_InMark1(box) && !TextDraw_InMark2(box)) {
        return;
    }
    u8 background = TextDraw_BackgroundColor(box);

    for (u32 y = 0; y < STRIP_HEIGHT; y++) {
        for (u32 i = 0; i < box->spacing; i++) {
            put_pixel(box->pen + i, y, background);
        }
    }
}
CLEAN_AS(func_02051034, TextDraw_FillSpacing)

/* func_020510c8: the strip's rows of glyph `glyph` drawn at the pen: its bitmap read from the
 * font's image file, the set pixels in the text's colour; the clear ones are painted with the
 * background only in a mark. Only the glyph's own width is drawn; returns it.
 * QUIRK: a glyph of the fallback font (top bit) is read from this font's image file, at the
 * index without the top bit.
 * REQUIRES: a glyph's bitmap is at most 0x84 bytes; BUG: in the last strip of a font whose
 * height is not a multiple of 8, the rows below the glyph read stack bytes the file read left
 * as they were. */
u32 TextDraw_DrawGlyph(TextDrawBox *box)
{
    u8 bitmap[GLYPH_BITMAP_MAX];
    TextFont *font = box->font;
    u32 width = font->header->width;
    u32 height = font->header->height;
    u32 drawn = TextFont_GlyphWidth(font, (u32) box->glyph);
    u32 glyph_bytes = ((width * height + 7) & ~7u) >> 3;

    FS_SeekFile(font->image_file, glyph_bytes * ((u32) box->glyph & ~TEXT_FONT_FALLBACK_BIT), 0);
    FS_ReadFile(font->image_file, bitmap, glyph_bytes);

    /* The bitmap's rows follow each other bit by bit, the leftmost pixel in the high bit. */
    u32 byte = (box->strip_y * width) >> 3;
    u32 mask = 0x80;
    int opaque = TextDraw_InMark1(box) || TextDraw_InMark2(box);
    u8 color = TextDraw_TextColor(box);
    u8 background = TextDraw_BackgroundColor(box);

    for (u32 y = 0; y < STRIP_HEIGHT; y++) {
        for (u32 x = 0; x < width; x++) {
            if (x < drawn) {
                int set = (bitmap[byte] & mask) != 0;
                if (set || opaque) {
                    put_pixel(box->pen + x, y, set ? color : background);
                }
            }
            mask >>= 1;
            if (mask == 0) {
                mask = 0x80;
                byte++;
            }
        }
    }
    return drawn;
}
CLEAN_AS(func_020510c8, TextDraw_DrawGlyph)

/* func_020511f8: the strip sent to its destination (at most 0x400 bytes of it, the box's width).
 * With `merge`, a pixel of the RAM destination is replaced only when it is the background
 * colour (each half of a byte on its own, the high half first). */
void TextDraw_UploadStrip(TextDrawBox *box)
{
    u32 size = box->row_bytes;
    if (size > STRIP_BYTES) {
        size = STRIP_BYTES;
    }
    DC_FlushRange(data_021c8344, size);
    load_tiles(box, box->dest_offset, size);
    if (box->screens != TEXT_DRAW_TO_RAM) {
        return;
    }

    u8 *dst = (u8 *) (uintptr_t) (box->ram_dest + box->dest_offset);
    if (box->merge) {
        u8 background = box->background;
        u8 background_high = (u8) (background << 4);
        for (u32 i = 0; i < size; i++) {
            u8 src = data_021c8344[i];
            if ((dst[i] & 0xf0) == background_high) {
                dst[i] = (u8) ((dst[i] & 0x0f) | (src & 0xf0));
            }
            if ((dst[i] & 0x0f) == background) {
                dst[i] = (u8) ((dst[i] & 0xf0) | (src & 0x0f));
            }
        }
    } else {
        MI_CpuCopy8(data_021c8344, dst, size);
    }
}
CLEAN_AS(func_020511f8, TextDraw_UploadStrip)

/* func_020512d4: character `code` drawn at the pen, which moves past it and the spacing; the
 * underline (in the last strip) runs under both. */
void TextDraw_DrawChar(TextDrawBox *box, int code)
{
    box->glyph = TextFont_FindGlyph(box->font, code);
    if (box->glyph == -1) {
        box->glyph = TextFont_FindGlyph(box->font, MISSING_CHAR_CODE);
    }
    u32 start = box->pen;
    box->pen += TextDraw_DrawGlyph(box);
    TextDraw_FillSpacing(box);
    box->pen += box->spacing;
    if (box->last_strip && box->underline) {
        TextDraw_Underline(box, start);
    }
    box->char_index++;
}
CLEAN_AS(func_020512d4, TextDraw_DrawChar)

/* func_02051340: a strip begun: cleared to the background, the colour put back, the pen at the
 * text's start. */
void TextDraw_BeginStrip(TextDrawBox *box)
{
    TextDraw_FillBackground(box);
    box->color = box->start_color;
    box->glyph = -1;
    box->pen = box->offset;
    box->char_index = 0;
}
CLEAN_AS(func_02051340, TextDraw_BeginStrip)

/* func_02051368: the box's text drawn, strip by strip, down to the font's height or the box's,
 * whichever ends first. QUIRK: with no first tile and no RAM destination, the strips start at
 * the offset the last drawing left. */
void TextDraw_Draw(TextDrawBox *box)
{
    u32 font_height = box->font->header->height;
    u32 box_height = box->rows * STRIP_HEIGHT;

    box->start_color = box->color;
    if (box->first_tile != -1) {
        box->dest_offset = (u32) box->first_tile * TILE_BYTES;
    } else if (box->ram_dest != 0) {
        box->dest_offset = 0;
    }
    box->last_strip = 0;

    for (box->strip_y = 0; box->strip_y < font_height && box->strip_y < box_height; box->strip_y += STRIP_HEIGHT) {
        u32 next = box->strip_y + STRIP_HEIGHT;
        box->last_strip = next >= font_height || next >= box_height;
        ((BoxDrawStrip *) box_slot(box, BOX_SLOT_DRAW_STRIP))(box);
        box->dest_offset += row_stride(box);
    }
}
CLEAN_AS(func_02051368, TextDraw_Draw)

/* func_02051400: the requests of the boxes in update group `update_mode` carried out: the
 * clear first, then the redraw. */
void TextDraw_Flush(int update_mode)
{
    TextDrawBox *box = NULL;

    while ((box = NNS_FndGetNextListObject(data_021c81bc, box)) != NULL) {
        if (box->update_mode != (u32) update_mode) {
            continue;
        }
        if (box->clear_cells != -1) {
            TextDraw_ClearRows(box);
            box->clear_cells = -1;
        }
        if (box->pending) {
            TextDraw_Draw(box);
            box->pending = 0;
        }
    }
}
CLEAN_AS(func_02051400, TextDraw_Flush)

/* func_02051458: the whole strip set to the box's background. */
void TextDraw_FillBackground(TextDrawBox *box)
{
    u8 background = box->background;
    MI_CpuFill8(data_021c8344, (u8) (background | (background << 4)), STRIP_BYTES);
}
CLEAN_AS(func_02051458, TextDraw_FillBackground)

/* func_02051478 */
void TextDraw_ReleaseBoxes(void)
{
    TextDraw_FreeBoxes();
}
CLEAN_AS(func_02051478, TextDraw_ReleaseBoxes)

/* func_02051480 */
void TextDraw_FlushGroup1(void)
{
    TextDraw_Flush(TEXT_DRAW_GROUP_1);
}
CLEAN_AS(func_02051480, TextDraw_FlushGroup1)

/* func_0205148c: the boxes and their heap freed, the fonts closed. */
void TextDraw_Shutdown(void)
{
    if (data_021c8194 != NULL) {
        TextDraw_FreeBoxes();
        Heap_Delete(data_021c8194);
        data_021c8194 = NULL;
    }
    TextFont_Close(&data_021c8230);
    TextFont_Close(&data_021c828c);
    TextFont_Close(&data_021c82e8);
    TextFont_Close(&data_021c81d4);
}
CLEAN_AS(func_0205148c, TextDraw_Shutdown)

/* func_020514dc: the four fonts loaded and the boxes' heap made (in the main heap); the list of
 * boxes is set up only when the heap could be made. */
void TextDraw_Init(void)
{
    TextFont_Open(&data_021c8230, data_020dcf88, NULL, NULL, 0);
    TextFont_Open(&data_021c828c, data_020dcf90, NULL, NULL, 0);
    TextFont_Open(&data_021c82e8, data_020dcf98, NULL, NULL, 0);
    TextFont_Open(&data_021c81d4, data_020dcfa0, NULL, NULL, 0);

    data_021c8194 = ExpHeap_Create(BOX_HEAP_SIZE, data_021fbe94);
    if (data_021c8194 != NULL) {
        NNS_FndInitList(data_021c81bc, offsetof(TextDrawBox, link));
    }
}
CLEAN_AS(func_020514dc, TextDraw_Init)

/* func_02051568: the end of a measured strip: nothing to send. */
void TextDraw_EndMeasureStrip(void) {}
CLEAN_AS(func_02051568, TextDraw_EndMeasureStrip)

/* func_0205156c: the pen moved past character `code` and the spacing, without drawing. */
void TextDraw_MeasureChar(TextDrawBox *box, int code)
{
    box->glyph = TextFont_FindGlyph(box->font, code);
    if (box->glyph == -1) {
        box->glyph = TextFont_FindGlyph(box->font, MISSING_CHAR_CODE);
    }
    box->pen += TextFont_GlyphWidth(box->font, (u32) box->glyph);
    box->pen += box->spacing;
}
CLEAN_AS(func_0205156c, TextDraw_MeasureChar)

/* func_020515ac: a measurement begun at x 0. */
void TextDraw_BeginMeasure(TextDrawBox *box)
{
    box->pen = 0;
    box->glyph = -1;
}
CLEAN_AS(func_020515ac, TextDraw_BeginMeasure)

/* func_020515b8: the width of the box's text in tiles, rounded up. */
unsigned int TextDraw_WidthInCells(TextDrawBox *box)
{
    return (measure(box) + 7) >> 3;
}
CLEAN_AS(func_020515b8, TextDraw_WidthInCells)

/* func_020515cc: both marks set. */
void TextDraw_SetMarks(TextDrawBox *box, unsigned char color_1, unsigned char background_1, unsigned int first_1,
                       unsigned int count_1, unsigned char color_2, unsigned char background_2, unsigned int first_2,
                       unsigned int count_2)
{
    box->mark_colors[0].color = color_1;
    box->mark_colors[0].background = background_1;
    box->marks[0].first = first_1;
    box->marks[0].count = count_1;
    box->mark_colors[1].color = color_2;
    box->mark_colors[1].background = background_2;
    box->marks[1].first = first_2;
    box->marks[1].count = count_2;
}
CLEAN_AS(func_020515cc, TextDraw_SetMarks)

/* func_02051608: the first mark set. */
void TextDraw_SetMark(TextDrawBox *box, unsigned char color, unsigned char background, int first, int count)
{
    box->mark_colors[0].color = color;
    box->mark_colors[0].background = background;
    box->marks[0].first = (u32) first;
    box->marks[0].count = (u32) count;
}
CLEAN_AS(func_02051608, TextDraw_SetMark)

/* func_02051624: the text placed against the box's right edge (at 0 when it is wider). */
void TextDraw_AlignRight(TextDrawBox *box)
{
    u32 width = measure(box);
    u32 box_width = box->cells * 8;
    box->offset = box_width > width ? box_width - width : 0;
}
CLEAN_AS(func_02051624, TextDraw_AlignRight)

/* func_02051648: the text placed in the middle of the box (at 0 when it is wider). */
void TextDraw_Center(TextDrawBox *box)
{
    u32 width = measure(box);
    u32 box_width = box->cells * 8;
    box->offset = box_width > width ? (box_width - width) >> 1 : 0;
}
CLEAN_AS(func_02051648, TextDraw_Center)

/* func_0205166c: a clear of `cells` tiles asked for (0: the whole width; -1 cancels one). */
void TextDraw_RequestClear(TextDrawBox *box, int cells)
{
    box->clear_cells = cells;
    if (box->update_mode == TEXT_DRAW_AT_ONCE && box->clear_cells != -1) {
        TextDraw_ClearRows(box);
        box->clear_cells = -1;
    }
}
CLEAN_AS(func_0205166c, TextDraw_RequestClear)

/* func_02051694: a redraw asked for. */
void TextDraw_RequestDraw(TextDrawBox *box)
{
    box->pending = 1;
    if (box->update_mode == TEXT_DRAW_AT_ONCE) {
        TextDraw_Draw(box);
        box->pending = 0;
    }
}
CLEAN_AS(func_02051694, TextDraw_RequestDraw)

/* ---- The process that owns the fonts and the boxes' heap */

/* func_02051b00 (vtable slot 3, delete): done at once. */
int TextDraw_ProcessDelete(void)
{
    TextDraw_Shutdown();
    return 1;
}
CLEAN_AS(func_02051b00, TextDraw_ProcessDelete)

/* func_02051b10 (vtable slot 6, execute): the boxes of group 1 updated. */
int TextDraw_ProcessExecute(void)
{
    TextDraw_FlushGroup1();
    return 1;
}
CLEAN_AS(func_02051b10, TextDraw_ProcessExecute)

/* func_02051b20 (vtable slot 0, create): done at once. */
int TextDraw_ProcessCreate(void)
{
    TextDraw_Init();
    LetterGrade_LoadKeywords();
    return 1;
}
CLEAN_AS(func_02051b20, TextDraw_ProcessCreate)

/* func_02051b34 (vtable slot 17): the destructor, and the object freed to the auxiliary heap.
 * The vtables are set as the class's and its base class's destructors do, in turn. */
void *TextDraw_ProcessDestructFree(void *process)
{
    *(const u32 **) process = data_020dcf40;
    *(const u32 **) process = data_020da13c;
    Process_Destruct(process);
    Heap_FreeAux(process);
    return process;
}
CLEAN_AS(func_02051b34, TextDraw_ProcessDestructFree)

/* func_02051b5c (vtable slot 16): the destructor. */
void *TextDraw_ProcessDestruct(void *process)
{
    *(const u32 **) process = data_020dcf40;
    *(const u32 **) process = data_020da13c;
    Process_Destruct(process);
    return process;
}
CLEAN_AS(func_02051b5c, TextDraw_ProcessDestruct)

/* func_02051b7c: the constructor, over the base class's. */
void *TextDraw_ProcessConstruct(void *process)
{
    Process_Construct(process);
    *(const u32 **) process = data_020da13c;
    *(const u32 **) process = data_020dcf40;
    return process;
}
CLEAN_AS(func_02051b7c, TextDraw_ProcessConstruct)

/* func_02051b9c (the profile's create, data_020dcf18): a process allocated in the auxiliary
 * heap and constructed; nothing keeps the pointer here (the ROM's code leaves it as its
 * result). */
void TextDraw_ProcessNew(void)
{
    void *process = Heap_AllocAuxZeroed(TEXT_PROCESS_SIZE);
    if (process != NULL) {
        TextDraw_ProcessConstruct(process);
    }
}
CLEAN_AS(func_02051b9c, TextDraw_ProcessNew)
