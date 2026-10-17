/* The rows of names of the "menu/res/" screens (res_rows.h). */
#include "res_rows.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/message_reader.h"
#include "main/rom_file.h"
#include "main/sliding_window.h"
#include "main/text_base.h"
#include "main/town_name.h"

static_assert(sizeof(MessageWindow) == 0xcc && offsetof(ResRows, labels) == 0xcc, "window");
static_assert(sizeof(TextLabel) == 0x6c && sizeof(LayerTask) == 0x24 && offsetof(ResRows, palette_task) == 0x93c, "labels");
static_assert(offsetof(ResRows, palette_file) == 0x960 && offsetof(ResRows, palette) == 0x980, "palettes");
static_assert(offsetof(ResRows, flags) == 0x9a0 && offsetof(ResRows, label_count) == 0x9a3, "bytes");
static_assert(sizeof(ResRows) == 0x9a4, "size");

/* The cells of the screens' OBJs, eight of them (overlay 140 asks for 5-7). */
extern const u32 data_ov139_02299c60[];

/* "menu/res/obj0.bch", "...obj1.bch", "...obj.bpl", "...bg.bch", "...bg.bpl", "...bg7.bpl". */
extern const char data_ov139_02299e00[];
extern const char data_ov139_02299e14[];
extern const char data_ov139_02299e28[];
extern const char data_ov139_02299e3c[];
extern const char data_ov139_02299e4c[];
extern const char data_ov139_02299e5c[];

/* The first column's texts, static objects made once (guard bit 0 of data_ov139_02299e84 for
 * the wide one, of data_ov139_02299e80 for the 8-bit one) and registered with their
 * destructors (the game's functions) in the records at data_ov139_02299e88 and
 * data_ov139_02299e94. */
extern u32 data_ov139_02299e80;
extern u32 data_ov139_02299e84;
extern u8 data_ov139_02299e88[];
extern u8 data_ov139_02299e94[];
extern TownNameWideText data_ov139_02299ea0;
extern TownNameText data_ov139_02299ebc;
extern TownNameWideText *func_02064158(TownNameWideText *text);
extern TownNameText *func_020641b0(TownNameText *text);
extern void __register_global_object(void *object, void *destruct, void *record);

/* A label's constructor and destructor handed to __cxa_vec_ctor and __cxa_vec_cleanup (the
 * game's symbols: TextLabel_Construct, TextLabel_Destruct). */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void *func_02070c08(void *label);
extern int **func_02070be8(void *label);

#define RES_ROWS_LABEL_CONSTRUCT ((void (*)(void *))(uintptr_t) func_02070c08)
#define RES_ROWS_LABEL_DESTRUCT ((void (*)(void *))(uintptr_t) func_02070be8)

extern Heap *data_021fbe94; /* the current heap */

extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);

/* The rows' colours: row N in colour 14 - N, the background in 15; a colour of 0xff for a row
 * asks for the usual 15 on 14. */
#define RES_ROWS_ROW_COLOR(row) ((u8) (14 - (row)))
#define RES_ROWS_BACKGROUND_COLOR 15
#define RES_ROWS_DEFAULT_COLOR 0xff
#define RES_ROWS_PALETTE_NUMBER 7
#define RES_ROWS_FIRST_MESSAGE 0x66

/* The ROM's signed division (_s32_div_f): a divisor of 0 gives the numerator back, and
 * INT32_MIN / -1 gives INT32_MIN. */
static int res_rows_div(int numerator, int divisor)
{
    if (divisor == 0) {
        return numerator;
    }
    if (divisor == -1) {
        return (int) (0u - (unsigned int) numerator);
    }
    return numerator / divisor;
}

/* A label's box opened on the block's layer at `chars`, `cells` wide, in `color` on colour 15
 * (or the usual 15 on 14), and shown centred. */
static void res_rows_show_label(ResRows *self, TextLabel *label, int chars, int cells, int color)
{
    int text_color = 0xf;
    int back_color = 0xe;

    if (color != RES_ROWS_DEFAULT_COLOR) {
        text_color = color;
        back_color = 0xf;
    }
    TextLabel_OpenStyledBox2(label, self->layer, chars, cells, (u8) text_color, (u8) back_color, 0);
    TextLabel_Show(label, 1, 0);
}

/* func_ov139_022995a0 */
void ResRows_ClearFlags(ResRows *self, unsigned short mask)
{
    self->flags = (u16) (self->flags & ~mask);
}
CLEAN_AS(func_ov139_022995a0, ResRows_ClearFlags)

/* func_ov139_022995b0: answers the flags' address. */
u16 *ResRows_SetFlags(ResRows *self, unsigned short mask)
{
    self->flags = (u16) (self->flags | mask);
    return &self->flags;
}
CLEAN_AS(func_ov139_022995b0, ResRows_SetFlags)

/* func_ov139_022995c0: whether any of `mask` is set, as 0 or 1. */
int ResRows_TestFlags(const ResRows *self, unsigned short mask)
{
    return (self->flags & mask) != 0;
}
CLEAN_AS(func_ov139_022995c0, ResRows_TestFlags)

/* func_ov139_022995d8: the cells of OBJ list `index` (its first parameter, the block, unread).
 * REQUIRES: `index` is below 8, the table's size. */
unsigned int ResRows_Cells(unsigned int unused, unsigned int index)
{
    (void) unused;
    return data_ov139_02299c60[index];
}
CLEAN_AS(func_ov139_022995d8, ResRows_Cells)

/* func_ov139_022995e4: a row's second column: its six characters (none for NULL), 8 cells from
 * character 0x1d2 + 16 a row. */
void ResRows_SetSecondColumn(ResRows *self, int row, const u16 *name, int color)
{
    TextLabel *label = ResRows_TakeLabel(self);

    if (name == NULL) {
        TextBase_Clear(label);
    } else {
        TextLabel_SetFromWide(label, name, (void *) (uintptr_t) RES_ROWS_NAME_LENGTH);
    }
    res_rows_show_label(self, label, row * 16 + 0x1d2, 8, color);
}
CLEAN_AS(func_ov139_022995e4, ResRows_SetSecondColumn)

/* func_ov139_0229964c: a row's first column: menu message 0x66 with the six characters as its
 * part 0 (empty for NULL), 10 cells from character 0x11e + 20 a row. The two texts the
 * characters pass through are made the first time. */
void ResRows_SetFirstColumn(ResRows *self, int row, const u16 *name, int color)
{
    TextLabel *label = ResRows_TakeLabel(self);

    if (!(data_ov139_02299e84 & 1)) {
        TownNameWideText_Construct(&data_ov139_02299ea0);
        __register_global_object(&data_ov139_02299ea0, (void *) (uintptr_t) func_02064158, data_ov139_02299e88);
        data_ov139_02299e84 |= 1;
    }
    if (!(data_ov139_02299e80 & 1)) {
        TownNameText_Construct(&data_ov139_02299ebc);
        __register_global_object(&data_ov139_02299ebc, (void *) (uintptr_t) func_020641b0, data_ov139_02299e94);
        data_ov139_02299e80 |= 1;
    }
    if (name == NULL) {
        TextBase_Clear(label);
    } else {
        TextBase_SetWide(&data_ov139_02299ea0, name, RES_ROWS_NAME_LENGTH);
        TextBase_WideToBytes((TextBase *) (void *) &data_ov139_02299ebc, (WideTextBase *) (void *) &data_ov139_02299ea0, 0, 0);
        MessageReader_SetPart(0, (int) (uintptr_t) &data_ov139_02299ebc);
        TextLabel_LoadMenuMessage((int) (uintptr_t) label, RES_ROWS_FIRST_MESSAGE);
    }
    res_rows_show_label(self, label, row * 20 + 0x11e, 10, color);
}
CLEAN_AS(func_ov139_0229964c, ResRows_SetFirstColumn)

/* func_ov139_02299744: the next free label; with all taken, the last one again. */
TextLabel *ResRows_TakeLabel(ResRows *self)
{
    if (self->label_count >= RES_ROWS_LABELS) {
        return &self->labels[RES_ROWS_LABELS - 1];
    }
    self->label_count++;
    return &self->labels[self->label_count - 1];
}
CLEAN_AS(func_ov139_02299744, ResRows_TakeLabel)

/* func_ov139_02299770: every label free and its box closed. */
void ResRows_ReleaseLabels(ResRows *self)
{
    self->label_count = 0;
    for (int i = 0; i < RES_ROWS_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov139_02299770, ResRows_ReleaseLabels)

/* func_ov139_02299798: a row emptied, in its colour. */
void ResRows_ClearRow(ResRows *self, int row)
{
    u8 color = RES_ROWS_ROW_COLOR(row);

    ResRows_SetFirstColumn(self, row, NULL, color);
    ResRows_SetSecondColumn(self, row, NULL, color);
}
CLEAN_AS(func_ov139_02299798, ResRows_ClearRow)

/* func_ov139_022997c0: a row set from its two names (six characters each, one after the
 * other), in its colour. */
void ResRows_SetRow(ResRows *self, int row, const u16 *names)
{
    u8 color = RES_ROWS_ROW_COLOR(row);

    ResRows_SetFirstColumn(self, row, names, color);
    ResRows_SetSecondColumn(self, row, names + RES_ROWS_NAME_LENGTH, color);
}
CLEAN_AS(func_ov139_022997c0, ResRows_SetRow)

/* func_ov139_022997f0: the three headings on the sub screen's OBJs: menu messages 0x65 (from
 * character 0x93), 0xc2 (0x8d) and 0xc1 (0x99), 6 cells each, centred. */
void ResRows_MakeHeadings(ResRows *self)
{
    static const struct {
        u8 message;
        u8 chars;
    } headings[3] = {{0x65, 0x93}, {0xc2, 0x8d}, {0xc1, 0x99}};

    for (int i = 0; i < 3; i++) {
        TextLabel *label = ResRows_TakeLabel(self);
        TextLabel_LoadMenuMessage((int) (uintptr_t) label, (char) headings[i].message);
        TextLabel_OpenStyledBox2(label, LAYER_SUB_OBJ, headings[i].chars, 6, 0xf, 0, 0);
        TextLabel_Show(label, 1, 0);
    }
}
CLEAN_AS(func_ov139_022997f0, ResRows_MakeHeadings)

/* func_ov139_02299888: a row's colour (14 - `row`) made `step` of `steps` of the way from
 * colour 15 to colour `color` of the file's palette, each 5-bit channel rounded down (in a
 * byte), and the palette queued.
 * REQUIRES: `row` is 0-14 and `color` 0-15 (the game passes rows 0-5); others reach past the
 * palettes as in the game. */
void ResRows_FadeRow(ResRows *self, int row, int step, int steps, int color)
{
    u16 background = self->palette_file[RES_ROWS_BACKGROUND_COLOR];
    u16 target = self->palette_file[color];
    int rest = steps - step;
    u8 red = (u8) res_rows_div((u8) (target & 0x1f) * step + (u8) (background & 0x1f) * rest, steps);
    u8 green = (u8) res_rows_div((u8) ((target & 0x3e0) >> 5) * step + (u8) ((background & 0x3e0) >> 5) * rest, steps);
    u8 blue = (u8) res_rows_div((u8) ((target & 0x7c00) >> 10) * step + (u8) ((background & 0x7c00) >> 10) * rest, steps);

    self->palette[RES_ROWS_ROW_COLOR(row)] = (u16) (red | (green << 5) | (blue << 10));
    ResRows_SetFlags(self, RES_ROWS_FLAG_PALETTE);
}
CLEAN_AS(func_ov139_02299888, ResRows_FadeRow)

/* func_ov139_02299964: the sub screen's OBJ characters 0x80-0xff and 0x160-0x1ff and palettes
 * 4-13 from their files. */
void ResRows_LoadObjFiles(ResRows *self)
{
    Heap *heap = data_021fbe94;

    (void) self;
    DisplayLayer_LoadCharsFromFile(data_ov139_02299e00, heap, LAYER_SUB_OBJ, 0x80, 0x80, 0xff);
    DisplayLayer_LoadCharsFromFile(data_ov139_02299e14, heap, LAYER_SUB_OBJ, 0x160, 0x160, 0x1ff);
    DisplayLayer_LoadPalettesFromFile(data_ov139_02299e28, heap, LAYER_SUB_OBJ, 4, 4, 0xd);
}
CLEAN_AS(func_ov139_02299964, ResRows_LoadObjFiles)

/* func_ov139_022999c4: the six rows emptied, in colour 14. */
void ResRows_ClearRows(ResRows *self)
{
    for (int i = 0; i < RES_ROWS_ROWS; i++) {
        ResRows_SetFirstColumn(self, i, NULL, 0xe);
        ResRows_SetSecondColumn(self, i, NULL, 0xe);
    }
}
CLEAN_AS(func_ov139_022999c4, ResRows_ClearRows)

/* func_ov139_022999f8: the layer's characters 0x11-0x36 and palettes 1-8 from their files, and
 * the rows' palette read and copied. */
void ResRows_LoadBg(ResRows *self)
{
    Heap *heap = data_021fbe94;

    DisplayLayer_LoadCharsFromFile(data_ov139_02299e3c, heap, self->layer, 0x11, 0x11, 0x36);
    DisplayLayer_LoadPalettesFromFile(data_ov139_02299e4c, heap, self->layer, 1, 1, 8);
    RomFile_Read(data_ov139_02299e5c, self->palette_file, sizeof(self->palette_file));
    MIi_CpuCopy16(self->palette_file, self->palette, sizeof(self->palette));
}
CLEAN_AS(func_ov139_022999f8, ResRows_LoadBg)

/* func_ov139_02299a68: the window placed at (`x`, `y`) and drawn (its class's slot 2). */
void ResRows_DrawAt(ResRows *self, int x, int y)
{
    void (*const *vtable)(void *);

    SlidingWindow_SetPlace((SlidingWindow *) (void *) &self->window, x, y);
    vtable = *(void (*const *const *)(void *))(void *) &self->window;
    vtable[2](&self->window);
}
CLEAN_AS(func_ov139_02299a68, ResRows_DrawAt)

/* func_ov139_02299a80: a changed palette queued as the layer's palette 7, the flag kept until
 * the queueing succeeds. */
void ResRows_QueuePalette(ResRows *self)
{
    if (ResRows_TestFlags(self, RES_ROWS_FLAG_PALETTE) != 0) {
        if (LayerTask_QueuePalette(&self->palette_task, (int) (uintptr_t) self->palette, self->layer,
                                   RES_ROWS_PALETTE_NUMBER) != 0) {
            ResRows_ClearFlags(self, RES_ROWS_FLAG_PALETTE);
        }
    }
}
CLEAN_AS(func_ov139_02299a80, ResRows_QueuePalette)

/* func_ov139_02299ac0: the labels let go and the layer task ended. */
void ResRows_Teardown(ResRows *self)
{
    ResRows_ReleaseLabels(self);
    LayerTask_End(&self->palette_task);
}
CLEAN_AS(func_ov139_02299ac0, ResRows_Teardown)

/* func_ov139_02299adc: the same as ResRows_Teardown. */
void ResRows_End(ResRows *self)
{
    ResRows_ReleaseLabels(self);
    LayerTask_End(&self->palette_task);
}
CLEAN_AS(func_ov139_02299adc, ResRows_End)

/* func_ov139_02299af8: the block set up on `layer` with no flags, and the window opened again
 * with `message` at (0x90, 0x18), its extra cells shown. */
void ResRows_Open(ResRows *self, unsigned char layer, int message)
{
    self->layer = layer;
    self->flags = 0;
    MessageWindow_Close(&self->window);
    MessageWindow_Open(&self->window, message, 0x90, 0x18);
    SlidingWindow_ShowExtra((SlidingWindow *) (void *) &self->window);
}
CLEAN_AS(func_ov139_02299af8, ResRows_Open)

/* func_ov139_02299b30: the labels destructed, then the window.
 * QUIRK: the layer task is not destructed. */
ResRows *ResRows_Destroy(ResRows *self)
{
    __cxa_vec_cleanup(self->labels, RES_ROWS_LABELS, sizeof(TextLabel), RES_ROWS_LABEL_DESTRUCT);
    MessageWindow_Destroy(&self->window);
    return self;
}
CLEAN_AS(func_ov139_02299b30, ResRows_Destroy)

/* func_ov139_02299b54: the window, the labels (by __cxa_vec_ctor) and the layer task
 * constructed. */
ResRows *ResRows_Construct(ResRows *self)
{
    MessageWindow_Construct(&self->window);
    __cxa_vec_ctor(self->labels, RES_ROWS_LABELS, sizeof(TextLabel), RES_ROWS_LABEL_CONSTRUCT, RES_ROWS_LABEL_DESTRUCT);
    LayerTask_Construct(&self->palette_task);
    return self;
}
CLEAN_AS(func_ov139_02299b54, ResRows_Construct)
