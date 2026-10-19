/* Overlay 93's staff roll (staff_roll.h). */
#include "staff_roll.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/message_query.h"
#include "main/message_reader.h"
#include "main/rom_file.h"
#include "main/text_base.h"

/* The text's vtable. */
extern const TextVtable data_ov093_022998b8;

/* The files: pointers to two of the names, and the names themselves. */
extern const char *const data_ov093_02299880; /* "menu/staff/sfr.bpl" */
extern const char *const data_ov093_02299884; /* "menu/staff/logo.bch" */
extern const char data_ov093_022998c8[];      /* "menu/staff/logo.bsc" */
extern const char data_ov093_022998dc[];      /* "menu/staff/logo1.bch" */
extern const char data_ov093_022998f4[];      /* "menu/staff/logo2.bch" */
extern const char data_ov093_0229990c[];      /* "st_staffroll", the message archive */
extern const char data_ov093_0229991c[];      /* "menu/staff/bg.bsc", the template map */

/* The current heap. */
extern Heap *data_021fbe94;

/* The SDK's copies and fills (16 bits at a time) and the C++ array helpers. The labels'
 * constructor and destructor are handed to them, so they are the game's symbols
 * (TextLabel_Construct, TextLabel_Destruct in Clean). */
extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);
extern void MIi_CpuClear16(u16 value, void *destination, u32 size);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void *func_02070c08(void *label);
extern void *func_02070be8(void *label);

/* The display registers this overlay writes itself. */
#define STAFF_ROLL_REG_DISPCNT (*(volatile u32 *) 0x04000000)
#define STAFF_ROLL_REG_BG1CNT (*(volatile u16 *) 0x0400000a)
#define STAFF_ROLL_DISPCNT_PLANES 0x00001f00u /* BG0-3 and OBJ shown */
#define STAFF_ROLL_BG1CNT_KEPT 0x0043         /* the priority and the mosaic bit */
#define STAFF_ROLL_BG1CNT_SCREEN_7 0x0700     /* screen base block 7 */

/* The layers (display_layers.h's numbers). */
#define STAFF_ROLL_LAYER_0 0
#define STAFF_ROLL_LAYER_4 4

/* Layer 4 runs this far behind layer 0, and both are scrolled up by it more. */
#define STAFF_ROLL_LAYER4_LAG 0xc0
/* Both layers' x scroll. */
#define STAFF_ROLL_SCROLL_X 8

/* The text: 6 lines a message, 0xcc lines in all; a line that starts with one of these is
 * blank. */
#define STAFF_ROLL_LINES_PER_MESSAGE 6
#define STAFF_ROLL_LINES 0xcc
#define STAFF_ROLL_NEWLINE 0x0a

/* After this many rows without text the screen says it is done. */
#define STAFF_ROLL_BLANK_LIMIT 0x0d
/* The text slots: past the 25th the next row starts again at slot 0. */
#define STAFF_ROLL_SLOTS 25
/* A text slot's first tile and width. */
#define STAFF_ROLL_SLOT_FIRST_TILE 0x11
#define STAFF_ROLL_SLOT_TILES 0x10
#define STAFF_ROLL_SLOT_CELLS 0x10
#define STAFF_ROLL_TEXT_COLOUR 1

/* A row of a map, in bytes. */
#define STAFF_ROLL_ROW_BYTES (STAFF_ROLL_MAP_COLUMNS * 2)

/* The logo's slide: from 0x78 pixels above, 2 pixels a frame; then its fade. */
#define STAFF_ROLL_LOGO_START (-0x78 * 0x1000)
#define STAFF_ROLL_WINDOW_SPEED 0x2000
#define STAFF_ROLL_FADE_IN 0x10   /* frames 0-15: the blend rises to 16 */
#define STAFF_ROLL_FADE_HOLD 0x38 /* until frame 0x38 it stays at 16 */
#define STAFF_ROLL_FADE_END 0x48  /* then falls to 1; at frame 0x48 the roll ends */
#define STAFF_ROLL_BLEND_PLANES 2
#define STAFF_ROLL_BLEND_SECOND 0x21
#define STAFF_ROLL_WINDOW_0 1
#define STAFF_ROLL_ALL_PLANES 0x1f
#define STAFF_ROLL_WINDOW_PLANES 0x1d
#define STAFF_ROLL_WINDOW_RIGHT 0xfe
#define STAFF_ROLL_WINDOW_BOTTOM 0xbf

/* A sum of two of the roll's 32-bit values, wrapping as the ROM's addition does. */
static s32 staff_roll_add(s32 a, s32 b)
{
    return (s32) ((u32) a + (u32) b);
}

static StaffRollScreen *staff_roll_screen_of(StaffRoll *self, int layer)
{
    return layer == STAFF_ROLL_LAYER_4 ? &self->layer4 : &self->layer0;
}

/* ---- the text */

/* func_ov093_02298f20 (vtable slot 3): the characters. */
int StaffRollText_Chars(StaffRollText *text)
{
    return (int) (uintptr_t) text->chars;
}
CLEAN_AS(func_ov093_02298f20, StaffRollText_Chars)

/* func_ov093_02298f24 (vtable slot 2): the capacity. */
int StaffRollText_Capacity(void)
{
    return STAFF_ROLL_TEXT_CAPACITY;
}
CLEAN_AS(func_ov093_02298f24, StaffRollText_Capacity)

/* func_ov093_02298f2c (vtable slot 1): destructed and freed. */
StaffRollText *StaffRollText_Delete(StaffRollText *text)
{
    text->vtable = &data_ov093_022998b8;
    TextBase_Destruct((TextBase *) (void *) text);
    Heap_OperatorDeleteB(text);
    return text;
}
CLEAN_AS(func_ov093_02298f2c, StaffRollText_Delete)

/* func_ov093_02298f4c (vtable slot 0): the destructor. */
StaffRollText *StaffRollText_Destruct(StaffRollText *text)
{
    text->vtable = &data_ov093_022998b8;
    TextBase_Destruct((TextBase *) (void *) text);
    return text;
}
CLEAN_AS(func_ov093_02298f4c, StaffRollText_Destruct)

/* func_ov093_02298f64: the constructor: the base's, the vtable, the text emptied. */
StaffRollText *StaffRollText_Construct(StaffRollText *text)
{
    TextBase_Construct(text);
    text->vtable = &data_ov093_022998b8;
    TextBase_Clear(text);
    return text;
}
CLEAN_AS(func_ov093_02298f64, StaffRollText_Construct)

/* ---- flags */

/* func_ov093_02298f84: the roll's flags in `mask` set. */
void StaffRoll_SetFlags(u16 *flags, int mask)
{
    *flags = (u16) (*flags | mask);
}
CLEAN_AS(func_ov093_02298f84, StaffRoll_SetFlags)

/* func_ov093_02298f8c: whether any of the roll's flags in `mask` is set. */
int StaffRoll_TestFlags(u16 *flags, u16 mask)
{
    return (*flags & mask) != 0;
}
CLEAN_AS(func_ov093_02298f8c, StaffRoll_TestFlags)

/* func_ov093_02298f9c */
void StaffRollScreen_ClearFlags(StaffRollScreen *screen, u8 mask)
{
    screen->flags &= (u8) ~mask;
}
CLEAN_AS(func_ov093_02298f9c, StaffRollScreen_ClearFlags)

/* func_ov093_02298fa4 */
void StaffRollScreen_SetFlags(StaffRollScreen *screen, int mask)
{
    screen->flags = (u8) (screen->flags | mask);
}
CLEAN_AS(func_ov093_02298fa4, StaffRollScreen_SetFlags)

/* func_ov093_02298fac: whether any of the flags in `mask` is set. */
int StaffRollScreen_TestFlags(StaffRollScreen *screen, int mask)
{
    return (screen->flags & mask) != 0;
}
CLEAN_AS(func_ov093_02298fac, StaffRollScreen_TestFlags)

/* func_ov093_02298fbc: nothing laid out, the first line next (a heading), the map to be
 * uploaded. The slot is left as it is. */
void StaffRollScreen_Reset(StaffRollScreen *screen)
{
    screen->rows = -1;
    screen->line = -1;
    screen->flags = 0;
    screen->blank_count = 0;
    StaffRollScreen_SetFlags(screen, STAFF_ROLL_SCREEN_HEADING | STAFF_ROLL_SCREEN_DIRTY);
}
CLEAN_AS(func_ov093_02298fbc, StaffRollScreen_Reset)

/* func_ov093_02298fd4: the destructor: nothing. */
void StaffRollScreen_Destruct(StaffRollScreen *screen)
{
    (void) screen;
}
CLEAN_AS(func_ov093_02298fd4, StaffRollScreen_Destruct)

/* func_ov093_02298fd8: the constructor: nothing. */
void StaffRollScreen_Construct(StaffRollScreen *screen)
{
    (void) screen;
}
CLEAN_AS(func_ov093_02298fd8, StaffRollScreen_Construct)

/* ---- the roll */

/* func_ov093_02298fdc: the logo loaded on layer 0 from the current heap: its map, then its
 * tiles from three files (0x10-0x78, 0x79-0xf0, 0xf1-0x15f). */
void StaffRoll_LoadLogo(StaffRoll *self)
{
    (void) self;
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadScreenFromFile(data_ov093_022998c8, heap, STAFF_ROLL_LAYER_0);
    DisplayLayer_LoadCharsFromFile(data_ov093_02299884, heap, STAFF_ROLL_LAYER_0, 0x10, 0x10, 0x78);
    DisplayLayer_LoadCharsFromFile(data_ov093_022998dc, heap, STAFF_ROLL_LAYER_0, 0x79, 0x79, 0xf0);
    DisplayLayer_LoadCharsFromFile(data_ov093_022998f4, heap, STAFF_ROLL_LAYER_0, 0xf1, 0xf1, 0x15f);
}
CLEAN_AS(func_ov093_02298fdc, StaffRoll_LoadLogo)

/* func_ov093_02299048: no label in use, all 26 labels' boxes closed, both layer load tasks
 * ended. */
void StaffRoll_CloseLabels(StaffRoll *self)
{
    self->label_count = 0;
    for (int i = 0; i < STAFF_ROLL_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
    for (int i = 0; i < STAFF_ROLL_SCREENS; i++) {
        LayerTask_End(&self->tasks[i]);
    }
}
CLEAN_AS(func_ov093_02299048, StaffRoll_CloseLabels)

/* func_ov093_02299090: the next free label; once all are in use, the last again. */
TextLabel *StaffRoll_NextLabel(StaffRoll *self)
{
    if (self->label_count >= STAFF_ROLL_LABELS) {
        return &self->labels[STAFF_ROLL_LABELS - 1];
    }
    self->label_count++;
    return &self->labels[self->label_count - 1];
}
CLEAN_AS(func_ov093_02299090, StaffRoll_NextLabel)

/* func_ov093_022990b8: the roll moved on by its speed: layer 4 laid out and scrolled to the
 * new position less 0xc0, then, when `both`, layer 0 to the position itself. */
void StaffRoll_Scroll(StaffRoll *self, int both)
{
    self->scroll = staff_roll_add(self->scroll, self->speed);
    int y = self->scroll >> 12;
    StaffRoll_Advance(self, STAFF_ROLL_LAYER_4, y - STAFF_ROLL_LAYER4_LAG);
    if (both != 0) {
        StaffRoll_Advance(self, STAFF_ROLL_LAYER_0, y);
    }
}
CLEAN_AS(func_ov093_022990b8, StaffRoll_Scroll)

/* The template row of the screen's slot copied to its next map row, both counted on. */
static void staff_roll_add_slot_row(StaffRoll *self, StaffRollScreen *screen)
{
    StaffRoll_CopyTemplateRow(self, screen->map, screen->slot, screen->rows & (STAFF_ROLL_MAP_ROWS - 1));
}

/* An empty row added to the screen's map. */
static void staff_roll_add_blank_row(StaffRoll *self, StaffRollScreen *screen)
{
    StaffRoll_ClearRow(self, screen->map, screen->rows & (STAFF_ROLL_MAP_ROWS - 1));
    screen->rows++;
}

/* A row laid out without text counted; at the limit the screen says it is done. */
static void staff_roll_count_blank(StaffRollScreen *screen)
{
    if (screen->blank_count < STAFF_ROLL_BLANK_LIMIT) {
        screen->blank_count++;
    } else {
        StaffRollScreen_SetFlags(screen, STAFF_ROLL_SCREEN_DONE);
    }
}

/* Whether a line is missing or blank. */
static int staff_roll_is_blank(const char *chars)
{
    return chars == NULL || chars[0] == STAFF_ROLL_NEWLINE || chars[0] == 0;
}

/* A heading line laid out: one row of the screen's slot, its label left-aligned. */
static void staff_roll_add_heading(StaffRoll *self, int layer, StaffRollScreen *screen, const char *chars)
{
    staff_roll_add_slot_row(self, screen);
    TextLabel *label = StaffRoll_NextLabel(self);
    TextBase_SetLine((TextBase *) (void *) label, chars);
    TextLabel_OpenStyledBox(label, layer, screen->slot * STAFF_ROLL_SLOT_TILES + STAFF_ROLL_SLOT_FIRST_TILE,
                            STAFF_ROLL_SLOT_CELLS, STAFF_ROLL_TEXT_COLOUR, 0, 0);
    TextLabel_Show(label, 0, 0);
    screen->slot++;
    screen->line++;
    screen->rows++;
}

/* func_ov093_022990e8: the screen's next part laid out for layer `layer`:
 * - the first time, it starts at line 0, row 0 and slot 0;
 * - past the text's last line, one empty row;
 * - a blank line (or one the archive does not have): two empty rows, the next line a heading;
 * - after a blank line, the heading and, unless it is blank (then skipped), the line after it,
 *   one row and one left-aligned label each;
 * - else the line on two rows of two slots, its label against the right edge.
 * A slot past the 25th starts again at slot 0. */
void StaffRoll_LayOutRow(StaffRoll *self, int layer, StaffRollScreen *screen)
{
    if (screen->line < 0) {
        screen->line = 0;
        screen->rows = 0;
        screen->slot = 0;
    } else if (screen->line >= STAFF_ROLL_LINES) {
        staff_roll_count_blank(screen);
        staff_roll_add_blank_row(self, screen);
        return;
    }
    if (screen->slot >= STAFF_ROLL_SLOTS) {
        screen->slot = 0;
    }

    const char *chars = (const char *) (uintptr_t) StaffRoll_Line(self, screen->line);
    if (staff_roll_is_blank(chars)) {
        if (chars != NULL) {
            StaffRollScreen_SetFlags(screen, STAFF_ROLL_SCREEN_HEADING);
        }
        for (int i = 0; i < 2; i++) {
            staff_roll_add_blank_row(self, screen);
        }
        screen->line++;
        staff_roll_count_blank(screen);
        return;
    }

    screen->blank_count = 0;
    if (StaffRollScreen_TestFlags(screen, STAFF_ROLL_SCREEN_HEADING) != 0) {
        StaffRollScreen_ClearFlags(screen, STAFF_ROLL_SCREEN_HEADING);
        staff_roll_add_heading(self, layer, screen, chars);
        const char *next = (const char *) (uintptr_t) StaffRoll_Line(self, screen->line);
        if (staff_roll_is_blank(next)) {
            screen->line++;
            return;
        }
        staff_roll_add_heading(self, layer, screen, next);
        return;
    }

    for (int i = 0; i < 2; i++) {
        staff_roll_add_slot_row(self, screen);
        screen->rows++;
        screen->slot++;
    }
    TextLabel *label = StaffRoll_NextLabel(self);
    TextBase_SetLine((TextBase *) (void *) label, chars);
    TextLabel_OpenStyledBox2(label, layer, (screen->slot - 2) * STAFF_ROLL_SLOT_TILES + STAFF_ROLL_SLOT_FIRST_TILE,
                             STAFF_ROLL_SLOT_CELLS, STAFF_ROLL_TEXT_COLOUR, 0, 0);
    TextLabel_ShowRightAligned(label);
    screen->line++;
}
CLEAN_AS(func_ov093_022990e8, StaffRoll_LayOutRow)

/* func_ov093_02299338: where line `line` of the roll starts in the text, its message (line / 6)
 * loaded into the text first; 0 when the message has no such line. */
int StaffRoll_Line(StaffRoll *self, int line)
{
    int message = line / STAFF_ROLL_LINES_PER_MESSAGE;
    unsigned char number = (unsigned char) message;
    MessageReader_LoadMessage(&self->text, &number, data_ov093_0229990c);
    return MessageQuery_Line((int) (uintptr_t) self->text.chars, line - message * STAFF_ROLL_LINES_PER_MESSAGE);
}
CLEAN_AS(func_ov093_02299338, StaffRoll_Line)

/* func_ov093_0229937c: template row `template_row` copied to row `map_row` of `map`. */
void StaffRoll_CopyTemplateRow(StaffRoll *self, u16 *map, int template_row, int map_row)
{
    MIi_CpuCopy16(&self->template_map[template_row * STAFF_ROLL_MAP_COLUMNS], &map[map_row * STAFF_ROLL_MAP_COLUMNS],
                  STAFF_ROLL_ROW_BYTES);
}
CLEAN_AS(func_ov093_0229937c, StaffRoll_CopyTemplateRow)

/* func_ov093_0229939c: row `map_row` of `map` filled with the template's first cell. */
void StaffRoll_ClearRow(StaffRoll *self, u16 *map, int map_row)
{
    MIi_CpuClear16(self->template_map[0], &map[map_row * STAFF_ROLL_MAP_COLUMNS], STAFF_ROLL_ROW_BYTES);
}
CLEAN_AS(func_ov093_0229939c, StaffRoll_ClearRow)

/* func_ov093_022993c0: for a position `y` not below 0, layer `layer`'s screen laid out until
 * it has (y / 8) + 1 rows (each step marking its map to be uploaded), and the layer scrolled to
 * (8, y - 0xc0). */
void StaffRoll_Advance(StaffRoll *self, int layer, int y)
{
    if (y < 0) {
        return;
    }
    int rows = (y >> 3) + 1;
    StaffRollScreen *screen = staff_roll_screen_of(self, layer);
    while (rows > screen->rows) {
        StaffRoll_LayOutRow(self, layer, screen);
        StaffRollScreen_SetFlags(screen, STAFF_ROLL_SCREEN_DIRTY);
    }
    DisplayLayer_SetScroll((unsigned int) layer, STAFF_ROLL_SCROLL_X, y - STAFF_ROLL_LAYER4_LAG);
}
CLEAN_AS(func_ov093_022993c0, StaffRoll_Advance)

/* func_ov093_02299418: whether the roll has ended. */
int StaffRoll_HasEnded(StaffRoll *self)
{
    return StaffRoll_TestFlags(&self->flags, STAFF_ROLL_FLAG_ENDED);
}
CLEAN_AS(func_ov093_02299418, StaffRoll_HasEnded)

/* func_ov093_02299424: the switch to the logo: layer 0 hidden, the display register's shown
 * planes set from the main screen's shadow, window 0 turned on with every plane inside it and
 * every plane but BG1 outside, its top at 0x78, and layer 0 scrolled to (0, -0x78); state 4,
 * the fade's counter 0, the slide from 0x78 pixels above.
 * HW: the display register is read and written here, between the shadow's read and the
 * windows' setup. */
void StaffRoll_ShowLogo(StaffRoll *self)
{
    DisplayLayer_Hide(STAFF_ROLL_LAYER_0);
    u32 planes = DisplayShadow_GetMainPlanes();
    STAFF_ROLL_REG_DISPCNT = (STAFF_ROLL_REG_DISPCNT & ~STAFF_ROLL_DISPCNT_PLANES) | (planes << 8);
    DisplayShadow_EnableMainWindows(STAFF_ROLL_WINDOW_0);
    DisplayShadow_SetMainWindow0Planes(STAFF_ROLL_ALL_PLANES);
    DisplayShadow_SetMainOutsidePlanes(STAFF_ROLL_WINDOW_PLANES);
    DisplayShadow_SetWindow(0, 0, 0x78, STAFF_ROLL_WINDOW_RIGHT, STAFF_ROLL_WINDOW_BOTTOM);
    DisplayLayer_SetScroll(STAFF_ROLL_LAYER_0, 0, -0x78);
    self->state = STAFF_ROLL_STATE_LOGO_WINDOW;
    self->counter = 0;
    self->window = STAFF_ROLL_LOGO_START;
}
CLEAN_AS(func_ov093_02299424, StaffRoll_ShowLogo)

/* func_ov093_02299490: both layers hidden, the roll idle. */
void StaffRoll_Stop(StaffRoll *self)
{
    DisplayLayer_Hide(STAFF_ROLL_LAYER_4);
    DisplayLayer_Hide(STAFF_ROLL_LAYER_0);
    self->state = STAFF_ROLL_STATE_IDLE;
}
CLEAN_AS(func_ov093_02299490, StaffRoll_Stop)

/* func_ov093_022994ac: the roll restarted at `speed`: position 0, both screens reset and their
 * maps emptied (filled with the template's first cell), state 1. */
void StaffRoll_Restart(StaffRoll *self, int speed)
{
    self->speed = speed;
    self->window_speed = STAFF_ROLL_WINDOW_SPEED;
    self->scroll = 0;
    StaffRollScreen_Reset(&self->layer0);
    StaffRollScreen_Reset(&self->layer4);
    MIi_CpuClear16(self->template_map[0], self->layer0.map, sizeof self->layer0.map);
    MIi_CpuClear16(self->template_map[0], self->layer4.map, sizeof self->layer4.map);
    self->state = STAFF_ROLL_STATE_BEGIN;
}
CLEAN_AS(func_ov093_022994ac, StaffRoll_Restart)

/* func_ov093_02299514: the roll's palettes 1-3 ("menu/staff/sfr.bpl") and its tile 0x10
 * ("menu/staff/logo.bch") loaded on layers 4 and 0 from the current heap. */
void StaffRoll_LoadRollGraphics(StaffRoll *self)
{
    (void) self;
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadPalettesFromFile(data_ov093_02299880, heap, STAFF_ROLL_LAYER_4, 1, 1, 3);
    DisplayLayer_LoadPalettesFromFile(data_ov093_02299880, heap, STAFF_ROLL_LAYER_0, 1, 1, 3);
    DisplayLayer_LoadCharsFromFile(data_ov093_02299884, heap, STAFF_ROLL_LAYER_4, 0x10, 0x10, 0x10);
    DisplayLayer_LoadCharsFromFile(data_ov093_02299884, heap, STAFF_ROLL_LAYER_0, 0x10, 0x10, 0x10);
}
CLEAN_AS(func_ov093_02299514, StaffRoll_LoadRollGraphics)

/* func_ov093_0229957c: the template map read from "menu/staff/bg.bsc". */
void StaffRoll_ReadTemplate(StaffRoll *self)
{
    RomFile_Read(data_ov093_0229991c, self->template_map, sizeof self->template_map);
}
CLEAN_AS(func_ov093_0229957c, StaffRoll_ReadTemplate)

/* func_ov093_0229959c: the roll stopped and its labels closed. */
void StaffRoll_Close(StaffRoll *self)
{
    StaffRoll_Stop(self);
    StaffRoll_CloseLabels(self);
}
CLEAN_AS(func_ov093_0229959c, StaffRoll_Close)

/* func_ov093_022995b0: each screen's map that changed queued for upload (layer 4's first),
 * and marked clean once queued. */
void StaffRoll_Upload(StaffRoll *self)
{
    if (StaffRollScreen_TestFlags(&self->layer4, STAFF_ROLL_SCREEN_DIRTY) != 0 &&
        LayerTask_QueueScreen(&self->tasks[0], (int) (uintptr_t) self->layer4.map, STAFF_ROLL_LAYER_4, sizeof self->layer4.map,
                              0) != 0) {
        StaffRollScreen_ClearFlags(&self->layer4, STAFF_ROLL_SCREEN_DIRTY);
    }
    if (StaffRollScreen_TestFlags(&self->layer0, STAFF_ROLL_SCREEN_DIRTY) != 0 &&
        LayerTask_QueueScreen(&self->tasks[1], (int) (uintptr_t) self->layer0.map, STAFF_ROLL_LAYER_0, sizeof self->layer0.map,
                              0) != 0) {
        StaffRollScreen_ClearFlags(&self->layer0, STAFF_ROLL_SCREEN_DIRTY);
    }
}
CLEAN_AS(func_ov093_022995b0, StaffRoll_Upload)

/* func_ov093_02299630: a frame of the roll, after its labels are closed:
 * - state 1: both layers shown and scrolled to (8, -0xc0), the roll's graphics loaded; state 2;
 * - state 2: the roll scrolled on both layers;
 * - state 3: scrolled on layer 4 only, layer 0 shown with the main screen's blend (planes 2 and
 *   0x21, 0), the logo loaded; state 5;
 * - state 4: scrolled on layer 4 only, layer 0 shown, the logo loaded; state 6;
 * - state 5: scrolled on layer 4 only; for 0x48 frames the blend's weight rises over 16 frames,
 *   holds at 16 until frame 0x38 and falls back; then the roll stops, the blend is turned off
 *   and the roll has ended;
 * - state 6: scrolled on layer 4 only; the logo slides down by the window's speed, window 0's
 *   top following it, until it is in place: then the windows are off, every plane shown outside
 *   them, the fade's counter at 16 (its hold) and state 5. Layer 0 is scrolled to the slide. */
void StaffRoll_Update(StaffRoll *self)
{
    StaffRoll_CloseLabels(self);
    switch (self->state) {
        case STAFF_ROLL_STATE_BEGIN:
            self->state = STAFF_ROLL_STATE_ROLL;
            DisplayLayer_Show(STAFF_ROLL_LAYER_4);
            DisplayLayer_Show(STAFF_ROLL_LAYER_0);
            DisplayLayer_SetScroll(STAFF_ROLL_LAYER_4, STAFF_ROLL_SCROLL_X, -STAFF_ROLL_LAYER4_LAG);
            DisplayLayer_SetScroll(STAFF_ROLL_LAYER_0, STAFF_ROLL_SCROLL_X, -STAFF_ROLL_LAYER4_LAG);
            StaffRoll_LoadRollGraphics(self);
            break;
        case STAFF_ROLL_STATE_ROLL:
            StaffRoll_Scroll(self, 1);
            break;
        case STAFF_ROLL_STATE_LOGO_BLEND:
            StaffRoll_Scroll(self, 0);
            DisplayLayer_Show(STAFF_ROLL_LAYER_0);
            DisplayShadow_SetMainAlpha(STAFF_ROLL_BLEND_PLANES, STAFF_ROLL_BLEND_SECOND, 0);
            StaffRoll_LoadLogo(self);
            self->state = STAFF_ROLL_STATE_LOGO_FADE;
            break;
        case STAFF_ROLL_STATE_LOGO_WINDOW:
            StaffRoll_Scroll(self, 0);
            DisplayLayer_Show(STAFF_ROLL_LAYER_0);
            StaffRoll_LoadLogo(self);
            self->state = STAFF_ROLL_STATE_LOGO_SLIDE;
            break;
        case STAFF_ROLL_STATE_LOGO_FADE: {
            StaffRoll_Scroll(self, 0);
            unsigned int weight = self->counter;
            if (weight < STAFF_ROLL_FADE_END) {
                if (weight >= STAFF_ROLL_FADE_IN) {
                    weight = weight < STAFF_ROLL_FADE_HOLD ? STAFF_ROLL_FADE_IN : STAFF_ROLL_FADE_END - weight;
                }
                self->counter++;
                DisplayShadow_SetMainAlpha(STAFF_ROLL_BLEND_PLANES, STAFF_ROLL_BLEND_SECOND, (u8) weight);
            } else {
                StaffRoll_Stop(self);
                DisplayShadow_MainBlendOff();
                StaffRoll_SetFlags(&self->flags, STAFF_ROLL_FLAG_ENDED);
            }
            break;
        }
        case STAFF_ROLL_STATE_LOGO_SLIDE: {
            StaffRoll_Scroll(self, 0);
            self->window = staff_roll_add(self->window, self->window_speed);
            int y = self->window >> 12;
            if (y >= 0) {
                y = 0;
                self->counter = STAFF_ROLL_FADE_IN;
                DisplayShadow_DisableMainWindows(STAFF_ROLL_WINDOW_0);
                DisplayShadow_SetMainOutsidePlanes(STAFF_ROLL_ALL_PLANES);
                self->state = STAFF_ROLL_STATE_LOGO_FADE;
            } else {
                DisplayShadow_SetWindow(0, 0, -y, STAFF_ROLL_WINDOW_RIGHT, STAFF_ROLL_WINDOW_BOTTOM);
            }
            DisplayLayer_SetScroll(STAFF_ROLL_LAYER_0, 0, y);
            break;
        }
    }
}
CLEAN_AS(func_ov093_02299630, StaffRoll_Update)

/* func_ov093_0229976c: the roll set up idle: no flags, no label in use, both layers hidden,
 * layer 4's control reset, BG1's screen base set to block 7 (its priority and mosaic kept), and
 * the template map read.
 * HW: BG1's control register is read and written here, after the layers' setup. */
void StaffRoll_Start(StaffRoll *self)
{
    self->flags = 0;
    self->label_count = 0;
    DisplayLayer_Hide(STAFF_ROLL_LAYER_4);
    DisplayLayer_Hide(STAFF_ROLL_LAYER_0);
    DisplayLayer_SetBgControl(STAFF_ROLL_LAYER_4, 0, 0, 0);
    STAFF_ROLL_REG_BG1CNT = (u16) ((STAFF_ROLL_REG_BG1CNT & STAFF_ROLL_BG1CNT_KEPT) | STAFF_ROLL_BG1CNT_SCREEN_7);
    self->state = STAFF_ROLL_STATE_IDLE;
    StaffRoll_ReadTemplate(self);
}
CLEAN_AS(func_ov093_0229976c, StaffRoll_Start)

/* func_ov093_022997b4: the destructor: the labels (by __cxa_vec_cleanup), the text and both
 * screens, last member first. */
StaffRoll *StaffRoll_Destruct(StaffRoll *self)
{
    __cxa_vec_cleanup(self->labels, STAFF_ROLL_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070be8);
    StaffRollText_Destruct(&self->text);
    StaffRollScreen_Destruct(&self->layer4);
    StaffRollScreen_Destruct(&self->layer0);
    return self;
}
CLEAN_AS(func_ov093_022997b4, StaffRoll_Destruct)

/* func_ov093_022997f8: the constructor: both screens, the text, the labels (by __cxa_vec_ctor)
 * and the two layer load tasks. */
StaffRoll *StaffRoll_Construct(StaffRoll *self)
{
    StaffRollScreen_Construct(&self->layer0);
    StaffRollScreen_Construct(&self->layer4);
    StaffRollText_Construct(&self->text);
    __cxa_vec_ctor(self->labels, STAFF_ROLL_LABELS, sizeof(TextLabel), (void (*)(void *))(uintptr_t) func_02070c08,
                   (void (*)(void *))(uintptr_t) func_02070be8);
    for (int i = 0; i < STAFF_ROLL_SCREENS; i++) {
        LayerTask_Construct(&self->tasks[i]);
    }
    return self;
}
CLEAN_AS(func_ov093_022997f8, StaffRoll_Construct)
