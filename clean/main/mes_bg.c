/* The background of a message window kind and its marker and slider sprites (mes_bg.h). */
#include "mes_bg.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "autoload_2/heap.h"
#include "clean.h"
#include "display_shadow.h" /* DisplayShadow_SetMainBg1Scroll, DisplayShadow_HideMainPlanes */
#include "game_variables.h" /* GameVariables_Tweak */

static_assert(offsetof(MesBg, colours_dirty) == 0x12, "MesBg layout");
static_assert(offsetof(MesBg, lines) == 0x1e, "MesBg layout");
static_assert(sizeof(MesBg) == 0x20, "MesBg layout");
static_assert(offsetof(MesBgMarker, unk_28) == 0x28, "MesBgMarker layout");
static_assert(sizeof(MesBgMarker) == 0x4c, "MesBgMarker layout");
static_assert(offsetof(MesBgIndicator, state) == 0x3c, "MesBgIndicator layout");
static_assert(sizeof(MesBgIndicator) == 0x48, "MesBgIndicator layout");
static_assert(offsetof(MesBgSlider, indicator) == 0x10, "MesBgSlider layout");
static_assert(sizeof(MesBgSlider) == 0x58, "MesBgSlider layout");

#define FS_READ_FAILED (-1)
#define SCALE_ONE 0x1000

/* The classes' vtables. */
extern const u8 data_020e3fb4[];
extern const MesBgSpriteVtable data_020e4030;
extern const MesBgSpriteVtable data_020e4014;
/* "/a_mes/a_mes1a_bg_nsc.bin" */
extern const char data_020e40c4[];
/* The cells the slider's knob is drawn with: the first entry. */
extern const void *const *data_020d5b3c;

extern int FS_OpenFile(void *file, const char *path);
extern s32 FS_ReadFile(void *file, void *dst, s32 size);
extern int FS_CloseFile(void *file);

/* main's sprite classes */
extern void *func_0208e8d4(void *sprite, u8 kind);     /* constructor */
extern void *func_0208e7f0(void *sprite);              /* destructor */
extern void func_0208af30(void *sprite);               /* the base class's constructor: place (0x80, 0x60) */
extern void func_0208af00(void *sprite);               /* the base class's destructor */
extern void func_0208aef4(void *sprite, int x, int y); /* place at (0x80 + x, 0x60 + y) */
extern int func_0208aeec(void *sprite);                /* y */
extern int func_0208aef0(void *sprite);                /* x */
extern MesBgIndicator *func_0208ec40(MesBgIndicator *indicator, u8 kind); /* constructor */
extern MesBgIndicator *func_0208ec14(MesBgIndicator *indicator);          /* destructor */
extern void func_0208ea6c(MesBgIndicator *indicator, int value);
extern void func_0208ea70(MesBgIndicator *indicator, int x, int y); /* the offset */
extern void *func_0208e95c(MesBgIndicator *indicator, int state);
extern int func_0208e958(MesBgIndicator *indicator); /* the state */
extern int func_0208e930(MesBgIndicator *indicator); /* both animations at their end */
extern void func_0208e9e0(MesBgIndicator *indicator, int *dx, int *dy);
extern void func_02088df8(int a0, const void *cell, int x, int y, int palette, int priority, int scale_x, int scale_y,
                          int rotation, int p9, int p10, int p11);

/* func_020ac8f0: reads the first MES_BG_SCREEN_SIZE bytes of /a_mes/a_mes1a_bg_nsc.bin into a
 * block of the current heap kept in `screen`. Returns 1 when the file opened, the block was
 * had, the read worked and the file closed.
 * QUIRK: the block is asked for, and the file closed, even when it did not open. */
int MesBg_LoadScreen(MesBg *bg, void *file)
{
    int opened = FS_OpenFile(file, data_020e40c4);
    bg->screen = Heap_AllocCurrentBack(MES_BG_SCREEN_SIZE);
    int read = 0;
    if (bg->screen != NULL) {
        read = FS_ReadFile(file, bg->screen, MES_BG_SCREEN_SIZE) != FS_READ_FAILED;
    }
    int closed = FS_CloseFile(file);
    return opened && read && closed && bg->screen != NULL;
}
CLEAN_AS(func_020ac8f0, MesBg_LoadScreen)

/* func_020ac954: the destructor the derived classes' destructors end with (the same as
 * MesBg_Destruct). */
MesBg *MesBg_DestructBase(MesBg *bg)
{
    bg->vtable = data_020e3fb4;
    MesBg_FreeScreen(bg);
    return bg;
}
CLEAN_AS(func_020ac954, MesBg_DestructBase)

/* func_020ac96c: the class's deleting destructor (vtable slot 1). */
MesBg *MesBg_DestructDelete(MesBg *bg)
{
    bg->vtable = data_020e3fb4;
    MesBg_FreeScreen(bg);
    Heap_OperatorDeleteB(bg);
    return bg;
}
CLEAN_AS(func_020ac96c, MesBg_DestructDelete)

/* func_020ac98c: the class's destructor (vtable slot 0). */
MesBg *MesBg_Destruct(MesBg *bg)
{
    bg->vtable = data_020e3fb4;
    MesBg_FreeScreen(bg);
    return bg;
}
CLEAN_AS(func_020ac98c, MesBg_Destruct)

/* func_020ac9a4 */
void MesBg_Construct(MesBg *bg)
{
    bg->vtable = data_020e3fb4;
    bg->screen = NULL;
    bg->colours_dirty = 0;
    bg->columns = 0;
    bg->scroll_x = 0;
    bg->scroll_y = 0;
    bg->lines_top = 0;
    bg->lines = 0;
    for (int i = 0; i < MES_BG_COLOURS; i++) {
        bg->colours[i] = 0;
    }
}
CLEAN_AS(func_020ac9a4, MesBg_Construct)

/* func_020ac9cc: the marker's deleting destructor (vtable slot 1). */
MesBgMarker *MesBgMarker_DestructDelete(MesBgMarker *marker)
{
    marker->vtable = &data_020e4030;
    func_0208e7f0(marker);
    Heap_OperatorDeleteB(marker);
    return marker;
}
CLEAN_AS(func_020ac9cc, MesBgMarker_DestructDelete)

/* func_020ac9ec: the marker's destructor (vtable slot 0). */
MesBgMarker *MesBgMarker_Destruct(MesBgMarker *marker)
{
    marker->vtable = &data_020e4030;
    func_0208e7f0(marker);
    return marker;
}
CLEAN_AS(func_020ac9ec, MesBgMarker_Destruct)

/* func_020aca04 */
MesBgMarker *MesBgMarker_Construct(MesBgMarker *marker)
{
    func_0208e8d4(marker, 1);
    marker->vtable = &data_020e4030;
    marker->unk_28 = 0;
    return marker;
}
CLEAN_AS(func_020aca04, MesBgMarker_Construct)

/* func_020aca24 */
void MesBgSlider_PlayIndicatorB(MesBgSlider *slider)
{
    func_0208e95c(&slider->indicator, 3);
}
CLEAN_AS(func_020aca24, MesBgSlider_PlayIndicatorB)

/* func_020aca30 */
void MesBgSlider_PlayIndicatorA(MesBgSlider *slider)
{
    func_0208e95c(&slider->indicator, 2);
}
CLEAN_AS(func_020aca30, MesBgSlider_PlayIndicatorA)

/* func_020aca3c: indicator state 0, in which the slider is not drawn. */
void MesBgSlider_Hide(MesBgSlider *slider)
{
    func_0208e95c(&slider->indicator, 0);
}
CLEAN_AS(func_020aca3c, MesBgSlider_Hide)

/* func_020aca48 */
void MesBgSlider_ShowStill(MesBgSlider *slider)
{
    func_0208e95c(&slider->indicator, 1);
}
CLEAN_AS(func_020aca48, MesBgSlider_ShowStill)

/* func_020aca54 */
int MesBgSlider_IndicatorDone(MesBgSlider *slider)
{
    return func_0208e930(&slider->indicator);
}
CLEAN_AS(func_020aca54, MesBgSlider_IndicatorDone)

/* func_020aca60: how far the indicator's animations move (0 unless it plays them). */
void MesBgSlider_IndicatorMove(MesBgSlider *slider, int *dx, int *dy)
{
    func_0208e9e0(&slider->indicator, dx, dy);
}
CLEAN_AS(func_020aca60, MesBgSlider_IndicatorMove)

/* func_020aca6c: the top of the track, from the slider's place. */
int MesBgSlider_TrackTop(MesBgSlider *slider)
{
    (void) slider;
    return 0;
}
CLEAN_AS(func_020aca6c, MesBgSlider_TrackTop)

/* func_020aca70: the bottom of the track, from the slider's place. */
int MesBgSlider_TrackBottom(MesBgSlider *slider)
{
    (void) slider;
    return MES_BG_SLIDER_TRACK;
}
CLEAN_AS(func_020aca70, MesBgSlider_TrackBottom)

/* func_020aca74: the knob's offset down the track. */
int MesBgSlider_KnobY(MesBgSlider *slider)
{
    return MesBgSlider_LevelToY(slider);
}
CLEAN_AS(func_020aca74, MesBgSlider_KnobY)

/* func_020aca7c: the indicator's offset across, from the slider's place. */
int MesBgSlider_TrackX(MesBgSlider *slider)
{
    (void) slider;
    return 6;
}
CLEAN_AS(func_020aca7c, MesBgSlider_TrackX)

/* func_020aca80: the level as an offset down the track, 0 at the top level to 32 at level 0.
 * QUIRK: the product is formed in 32 bits and shifted down with its sign, so a level outside
 * 0-0x1000 gives an offset outside the track (and wraps for levels beyond 2^26 away). */
int MesBgSlider_LevelToY(MesBgSlider *slider)
{
    s32 scaled = (s32) ((u32) (MES_BG_SLIDER_LEVEL_TOP - slider->level) * MES_BG_SLIDER_TRACK);
    return scaled >> 12;
}
CLEAN_AS(func_020aca80, MesBgSlider_LevelToY)

/* func_020aca94 */
void MesBgSlider_SetLevel(MesBgSlider *slider, fx32 level)
{
    slider->level = level;
}
CLEAN_AS(func_020aca94, MesBgSlider_SetLevel)

/* func_020aca98: the class's place function (vtable slot 4): the slider's place, and the
 * indicator's own place function with the same values. */
void MesBgSlider_SetPlace(MesBgSlider *slider, int x, int y)
{
    func_0208aef4(slider, x, y);
    slider->indicator.vtable->set_place(&slider->indicator, x, y);
}
CLEAN_AS(func_020aca98, MesBgSlider_SetPlace)

/* func_020acab8: the class's update (vtable slot 3): the indicator goes beside the knob and
 * updates. */
void MesBgSlider_Update(MesBgSlider *slider)
{
    int x = MesBgSlider_TrackX(slider);
    int y = MesBgSlider_KnobY(slider);
    func_0208ea70(&slider->indicator, x, y);
    slider->indicator.vtable->update(&slider->indicator);
}
CLEAN_AS(func_020acab8, MesBgSlider_Update)

/* func_020acae8: the class's draw (vtable slot 2): unless hidden, the indicator, then the knob
 * at the slider's place. */
void MesBgSlider_Draw(MesBgSlider *slider)
{
    if (func_0208e958(&slider->indicator) == 0) {
        return;
    }
    slider->indicator.vtable->draw(&slider->indicator);
    const void *cell = data_020d5b3c[0];
    int y = func_0208aeec(slider);
    int x = func_0208aef0(slider);
    func_02088df8(0, cell, x, y, -1, 0, SCALE_ONE, SCALE_ONE, 0, -1, 0, 0);
}
CLEAN_AS(func_020acae8, MesBgSlider_Draw)

/* func_020acb48: the slider's deleting destructor (vtable slot 1). */
MesBgSlider *MesBgSlider_DestructDelete(MesBgSlider *slider)
{
    slider->vtable = &data_020e4014;
    func_0208ec14(&slider->indicator);
    func_0208af00(slider);
    Heap_OperatorDeleteB(slider);
    return slider;
}
CLEAN_AS(func_020acb48, MesBgSlider_DestructDelete)

/* func_020acb70: the slider's destructor (vtable slot 0). */
MesBgSlider *MesBgSlider_Destruct(MesBgSlider *slider)
{
    slider->vtable = &data_020e4014;
    func_0208ec14(&slider->indicator);
    func_0208af00(slider);
    return slider;
}
CLEAN_AS(func_020acb70, MesBgSlider_Destruct)

/* func_020acb94: a slider at half level, its indicator of kind 1 hidden. */
MesBgSlider *MesBgSlider_Construct(MesBgSlider *slider)
{
    func_0208af30(slider);
    slider->vtable = &data_020e4014;
    slider->level = MES_BG_SLIDER_LEVEL_TOP / 2;
    func_0208ec40(&slider->indicator, 1);
    func_0208ea6c(&slider->indicator, 0);
    return slider;
}
CLEAN_AS(func_020acb94, MesBgSlider_Construct)

/* ---- The window's screen, lines and colours */

/* The screen is 32 entries of 2 bytes per row. The frame in the file spans columns 15 to 31 of
 * rows 9 to 20: a border row, five lines of two rows each (rows 10 to 19), a border row. A
 * window of fewer lines moves rows two at a time (one 16-pixel line) and blanks what it leaves;
 * one narrower than MES_BG_MAX_COLUMNS text columns moves its right border left and blanks the
 * columns past it, and is scrolled right by as many columns to keep its right edge. */
#define MES_BG_ROW_BYTES 64
#define MES_BG_FRAME_COLUMN 15
#define MES_BG_FRAME_BYTES 0x22 /* columns 15 to 31 */
#define MES_BG_FRAME_TOP_ROW 9
#define MES_BG_FRAME_BOTTOM_ROW 20
#define MES_BG_MAX_COLUMNS 13
#define MES_BG_BLANK_BYTE 0x10 /* a blank cell is the entry 0x1010 */

/* Where the window is on the screen at scroll (0, 0): its text starts at x 0x88 (column 17),
 * the first line at y 0x50 (row 10) plus `lines_top`. */
#define MES_BG_TEXT_LEFT 0x88
#define MES_BG_TEXT_TOP 0x50
#define MES_BG_LINE_HEIGHT 16

/* The labels' VRAM tiles: MES_BG_LABEL_TILES tiles per label from tile MES_BG_LABEL_FIRST_TILE,
 * five places; the place of each line by the number of lines (2 to 4). */
#define MES_BG_LABEL_FIRST_TILE 153
#define MES_BG_LABEL_TILES 26
extern const u8 data_020d1dd4[]; /* 2 lines: places 0, 4 */
extern const u8 data_020d1dd8[]; /* 3 lines: places 0, 3, 4 */
extern const u8 data_020d1ddc[]; /* 4 lines: places 0, 2, 3, 4 */

/* The lines' colours: background colours 0x41 to 0x45 (byte 0x82 of the palette). */
#define MES_BG_COLOURS_OFFSET 0x82
#define MES_BG_LINE_COLOUR 12

/* Main BG1's control register. */
#define MES_BG_REG_BG1CNT (*(volatile u16 *) 0x0400000a)
#define MES_BG_BGCNT_PRIORITY 0x0003
#define MES_BG_BGCNT_MOSAIC 0x0040
#define MES_BG_BGCNT_KEEP 0x0043   /* priority and mosaic */
#define MES_BG_BGCNT_SCREEN 0x0500 /* screen base 5, character base 0, 32x32, 16 colours */
#define MES_BG_PLANE_BG1 2

#define MES_BG_FILE_SIZE 0x4c /* NitroSDK's FSFile */

/* The adjustments (GameVariables_Tweak, always 0) of the window's place. */
#define MES_BG_TWEAK 0x66

extern void DC_FlushRange(const void *start, u32 size);
extern void GX_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void func_02113088(const void *src, u32 offset, u32 size); /* main BG1's screen */
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern void FS_InitFile(void *file);
extern Heap *data_021fbe94; /* the scene's heap */

static u8 *mes_bg_cell(MesBg *bg, u32 row, u32 column)
{
    return bg->screen + row * MES_BG_ROW_BYTES + column * 2;
}

/* The frame's columns of row `from` copied over row `to`. */
static void mes_bg_copy_frame_row(MesBg *bg, u32 from, u32 to)
{
    MI_CpuCopy8(mes_bg_cell(bg, from, MES_BG_FRAME_COLUMN), mes_bg_cell(bg, to, MES_BG_FRAME_COLUMN), MES_BG_FRAME_BYTES);
}

static void mes_bg_blank_frame_row(MesBg *bg, u32 row)
{
    MesBg_BlankCells(mes_bg_cell(bg, row, MES_BG_FRAME_COLUMN), MES_BG_FRAME_BYTES);
}

/* One entry copied, from (from_row, from_column) to (to_row, to_column). */
static void mes_bg_copy_cell(MesBg *bg, u32 from_row, u32 from_column, u32 to_row, u32 to_column)
{
    u16 entry;
    memcpy(&entry, mes_bg_cell(bg, from_row, from_column), sizeof entry);
    memcpy(mes_bg_cell(bg, to_row, to_column), &entry, sizeof entry);
}

/* func_020ac148: the line under the screen point (x, y), or -1 when the point is outside the
 * window's text columns or its lines.
 * QUIRK: the right edge (the width in columns times 8 from the text's left) wraps in 32 bits. */
int MesBg_LineAt(MesBg *bg, int x, int y)
{
    int left = MES_BG_TEXT_LEFT - bg->scroll_x;
    int right = (int) ((u32) left + (u32) bg->columns * 8);
    if (x < left || x >= right) {
        return -1;
    }
    int top = bg->lines_top + MES_BG_TEXT_TOP - bg->scroll_y;
    for (int line = 0; line < bg->lines; line++) {
        int bottom = top + MES_BG_LINE_HEIGHT;
        if (y >= top && y < bottom) {
            return line;
        }
        top = bottom;
    }
    return -1;
}
CLEAN_AS(func_020ac148, MesBg_LineAt)

/* func_020ac318: the first VRAM tile of the label of line `line` when the window shows `lines`
 * lines: one line takes the first place, five lines one place each, 2 to 4 lines the places of
 * their table (the first and the last always). Another number of lines gives the first place.
 * REQUIRES: 0 <= line < lines (the tables are read at `line` as it is). */
int MesBg_LabelTile(int line, int lines)
{
    int place = 0;
    switch (lines) {
        case 2:
            place = data_020d1dd4[line];
            break;
        case 3:
            place = data_020d1dd8[line];
            break;
        case 4:
            place = data_020d1ddc[line];
            break;
        case 5:
            place = line;
            break;
        default:
            break;
    }
    return (int) ((u32) place * MES_BG_LABEL_TILES + MES_BG_LABEL_FIRST_TILE);
}
CLEAN_AS(func_020ac318, MesBg_LabelTile)

/* func_020ac358: line `line` in `colour`, the other lines' colours 0; uploaded with the next
 * draw. */
void MesBg_HighlightLine(MesBg *bg, int line, u16 colour)
{
    for (int i = 0; i < MES_BG_COLOURS; i++) {
        bg->colours[i] = i == line ? colour : 0;
    }
    bg->colours_dirty = 1;
}
CLEAN_AS(func_020ac358, MesBg_HighlightLine)

/* func_020ac384: every line in the usual colour; uploaded with the next draw. */
void MesBg_ResetLineColours(MesBg *bg)
{
    for (int i = 0; i < MES_BG_COLOURS; i++) {
        bg->colours[i] = MES_BG_LINE_COLOUR;
    }
    bg->colours_dirty = 1;
}
CLEAN_AS(func_020ac384, MesBg_ResetLineColours)

/* func_020ac39c: main BG1 scrolled to (x, y) from the window's place in the file, x less 8 per
 * column the window is narrower than the frame (GameVariables_Tweak adds 0 to both terms), and
 * the scroll kept. A window wider than the frame is not moved.
 * QUIRK: the scroll is kept in 16 bits. */
void MesBg_SetScroll(MesBg *bg, int x, int y)
{
    int base = GameVariables_Tweak(MES_BG_TWEAK, 2);
    int per_column = GameVariables_Tweak(MES_BG_TWEAK, 3) - 8;
    int narrower = MES_BG_MAX_COLUMNS - bg->columns;
    if (narrower < 0) {
        narrower = 0;
    }
    int scroll_x = (int) ((u32) x + (u32) base + (u32) per_column * (u32) narrower);
    DisplayShadow_SetMainBg1Scroll((u16) scroll_x, (u16) y);
    bg->scroll_x = (s16) scroll_x;
    bg->scroll_y = (s16) y;
}
CLEAN_AS(func_020ac39c, MesBg_SetScroll)

/* func_020ac3e0: main BG1 hidden. */
void MesBg_Hide(MesBg *bg)
{
    (void) bg;
    DisplayShadow_HideMainPlanes(MES_BG_PLANE_BG1);
}
CLEAN_AS(func_020ac3e0, MesBg_Hide)

/* func_020ac3ec: main BG1 shown. */
void MesBg_Show(MesBg *bg)
{
    (void) bg;
    DisplayShadow_ShowMainPlanes(MES_BG_PLANE_BG1);
}
CLEAN_AS(func_020ac3ec, MesBg_Show)

/* func_020ac3f8: the lines' colours uploaded to the background palette when they changed. */
void MesBg_UploadColours(MesBg *bg)
{
    if (bg->colours_dirty == 0) {
        return;
    }
    DC_FlushRange(bg->colours, sizeof bg->colours);
    GX_LoadBGPltt(bg->colours, MES_BG_COLOURS_OFFSET, sizeof bg->colours);
    bg->colours_dirty = 0;
}
CLEAN_AS(func_020ac3f8, MesBg_UploadColours)

/* func_020ac424: the screen uploaded as main BG1's (the game does it while the screen is
 * loaded). */
void MesBg_UploadScreen(MesBg *bg)
{
    DC_FlushRange(bg->screen, MES_BG_SCREEN_SIZE);
    func_02113088(bg->screen, 0, MES_BG_SCREEN_SIZE);
}
CLEAN_AS(func_020ac424, MesBg_UploadScreen)

/* func_020ac444: main BG1 in front of the others, its screen at base 5, without mosaic.
 * HW: three read-modify-writes of BG1CNT, in this order. */
void MesBg_SetBgControl(MesBg *bg)
{
    (void) bg;
    MES_BG_REG_BG1CNT = (u16) (MES_BG_REG_BG1CNT & ~MES_BG_BGCNT_PRIORITY);
    MES_BG_REG_BG1CNT = (u16) ((MES_BG_REG_BG1CNT & MES_BG_BGCNT_KEEP) | MES_BG_BGCNT_SCREEN);
    MES_BG_REG_BG1CNT = (u16) (MES_BG_REG_BG1CNT & ~MES_BG_BGCNT_MOSAIC);
}
CLEAN_AS(func_020ac444, MesBg_SetBgControl)

/* func_020ac46c: the window's width in 8-pixel text columns. */
void MesBg_SetColumns(MesBg *bg, int columns)
{
    bg->columns = columns;
}
CLEAN_AS(func_020ac46c, MesBg_SetColumns)

/* func_020ac470: the frame's top row; the first line starts 8 pixels per row below row 9's
 * place.
 * QUIRK: kept in 16 bits. */
void MesBg_SetTopRow(MesBg *bg, int row)
{
    bg->lines_top = (s16) (u16) (((u32) row - MES_BG_FRAME_TOP_ROW) << 3);
}
CLEAN_AS(func_020ac470, MesBg_SetTopRow)

/* func_020ac478: rows `first_row` to `last_row` cut to the window's width: the right border
 * (columns 30 and 31) copied left by the columns the window is narrower than the frame, and
 * the columns past it blanked, left to right. Nothing for a window of the frame's width or
 * wider.
 * QUIRK: the width is compared unsigned, so a negative width also leaves the rows. */
void MesBg_NarrowRows(MesBg *bg, u32 first_row, u32 last_row)
{
    u32 columns = (u32) bg->columns;
    if (columns >= MES_BG_MAX_COLUMNS) {
        return;
    }
    u32 narrower = MES_BG_MAX_COLUMNS - columns;
    for (u32 row = first_row; row <= last_row; row++) {
        mes_bg_copy_cell(bg, row, 30, row, 30 - narrower);
        mes_bg_copy_cell(bg, row, 31, row, 31 - narrower);
        for (u32 column = 32 - narrower; column < 32; column++) {
            MesBg_BlankCells(mes_bg_cell(bg, row, column), 2);
        }
    }
}
CLEAN_AS(func_020ac478, MesBg_NarrowRows)

/* func_020ac4ec: the frame as it is in the file: five lines from row 9. */
void MesBg_ShapeFiveLines(MesBg *bg)
{
    MesBg_NarrowRows(bg, 9, MES_BG_FRAME_BOTTOM_ROW);
    MesBg_SetTopRow(bg, 9);
    bg->lines = 5;
}
CLEAN_AS(func_020ac4ec, MesBg_ShapeFiveLines)

/* func_020ac50c: four lines from row 11: the top border and the first line moved down a line,
 * rows 9 and 10 blanked. */
void MesBg_ShapeFourLines(MesBg *bg)
{
    mes_bg_copy_frame_row(bg, 10, 12);
    mes_bg_copy_frame_row(bg, 11, 13);
    mes_bg_copy_frame_row(bg, 9, 11);
    mes_bg_blank_frame_row(bg, 9);
    mes_bg_blank_frame_row(bg, 10);
    MesBg_NarrowRows(bg, 11, MES_BG_FRAME_BOTTOM_ROW);
    MesBg_SetTopRow(bg, 11);
    bg->lines = 4;
}
CLEAN_AS(func_020ac50c, MesBg_ShapeFourLines)

/* func_020ac588: three lines from row 13: the top border and the first line moved down two
 * lines, rows 9 to 12 blanked. */
void MesBg_ShapeThreeLines(MesBg *bg)
{
    mes_bg_copy_frame_row(bg, 10, 14);
    mes_bg_copy_frame_row(bg, 11, 15);
    mes_bg_copy_frame_row(bg, 9, 13);
    mes_bg_blank_frame_row(bg, 9);
    mes_bg_blank_frame_row(bg, 10);
    mes_bg_blank_frame_row(bg, 11);
    mes_bg_blank_frame_row(bg, 12);
    MesBg_NarrowRows(bg, 13, MES_BG_FRAME_BOTTOM_ROW);
    MesBg_SetTopRow(bg, 13);
    bg->lines = 3;
}
CLEAN_AS(func_020ac588, MesBg_ShapeThreeLines)

/* func_020ac624: two lines in rows 13 to 18: the top as for three lines, the last line and the
 * bottom border moved up a line, rows 9 to 12, 19 and 20 blanked. */
void MesBg_ShapeTwoLines(MesBg *bg)
{
    mes_bg_copy_frame_row(bg, 10, 14);
    mes_bg_copy_frame_row(bg, 11, 15);
    mes_bg_copy_frame_row(bg, 9, 13);
    mes_bg_copy_frame_row(bg, 18, 16);
    mes_bg_copy_frame_row(bg, 19, 17);
    mes_bg_copy_frame_row(bg, 20, 18);
    mes_bg_blank_frame_row(bg, 9);
    mes_bg_blank_frame_row(bg, 10);
    mes_bg_blank_frame_row(bg, 11);
    mes_bg_blank_frame_row(bg, 12);
    mes_bg_blank_frame_row(bg, 19);
    mes_bg_blank_frame_row(bg, 20);
    MesBg_NarrowRows(bg, 13, 18);
    MesBg_SetTopRow(bg, 13);
    bg->lines = 2;
}
CLEAN_AS(func_020ac624, MesBg_ShapeTwoLines)

/* func_020ac71c: one line in rows 13 to 16: the top border, the first line's top row, a row of
 * the first line's second row with the last line's second row's two cells at each end (the
 * line's bottom corners), then the bottom border; rows 9 to 12 and 17 to 20 blanked. The two
 * line rows' middles (columns 17 to 29) are copied first, their end cells one by one after the
 * borders. */
void MesBg_ShapeOneLine(MesBg *bg)
{
    MI_CpuCopy8(mes_bg_cell(bg, 10, 17), mes_bg_cell(bg, 14, 17), 13 * 2);
    MI_CpuCopy8(mes_bg_cell(bg, 11, 17), mes_bg_cell(bg, 15, 17), 13 * 2);
    mes_bg_copy_frame_row(bg, 9, 13);
    mes_bg_copy_frame_row(bg, 20, 16);

    mes_bg_copy_cell(bg, 10, 15, 14, 15);
    mes_bg_copy_cell(bg, 10, 16, 14, 16);
    mes_bg_copy_cell(bg, 10, 31, 14, 31);
    mes_bg_copy_cell(bg, 10, 30, 14, 30);
    mes_bg_copy_cell(bg, 19, 15, 15, 15);
    mes_bg_copy_cell(bg, 19, 16, 15, 16);
    mes_bg_copy_cell(bg, 19, 31, 15, 31);
    mes_bg_copy_cell(bg, 19, 30, 15, 30);

    mes_bg_blank_frame_row(bg, 9);
    mes_bg_blank_frame_row(bg, 10);
    mes_bg_blank_frame_row(bg, 11);
    mes_bg_blank_frame_row(bg, 12);
    mes_bg_blank_frame_row(bg, 17);
    mes_bg_blank_frame_row(bg, 18);
    mes_bg_blank_frame_row(bg, 19);
    mes_bg_blank_frame_row(bg, 20);
    MesBg_NarrowRows(bg, 13, 16);
    MesBg_SetTopRow(bg, 13);
    bg->lines = 1;
}
CLEAN_AS(func_020ac71c, MesBg_ShapeOneLine)

/* func_020ac89c: `size` bytes of screen entries made blank cells. */
void MesBg_BlankCells(void *cells, int size)
{
    MI_CpuFill8(cells, MES_BG_BLANK_BYTE, (u32) size);
}
CLEAN_AS(func_020ac89c, MesBg_BlankCells)

/* func_020ac8a8: the screen, when loaded, given back to the scene's heap. */
void MesBg_FreeScreen(MesBg *bg)
{
    if (bg->screen != NULL) {
        Heap_Free(data_021fbe94, bg->screen);
        bg->screen = NULL;
    }
}
CLEAN_AS(func_020ac8a8, MesBg_FreeScreen)

/* func_020ac8c8: the screen read from its file; whether that worked. */
int MesBg_Load(MesBg *bg)
{
    u8 file[MES_BG_FILE_SIZE];
    FS_InitFile(file);
    return MesBg_LoadScreen(bg, file) != 0;
}
CLEAN_AS(func_020ac8c8, MesBg_Load)
