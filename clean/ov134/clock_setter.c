/* The clock setter of overlay 134 (clock_setter.h): its flags, the layout of the fields and their
 * colours, the labels that show the values, its graphics, its frame and its setup. */
#include "clock_setter.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/input.h"
#include "clean.h"
#include "main/calendar.h"
#include "main/date_time.h"
#include "main/display_layers.h"
#include "main/dual_cell_sprite.h"
#include "main/layer_load_task.h"
#include "main/oam_buffer.h"
#include "main/rom_file.h"
#include "main/screen_map.h"
#include "main/text_label.h"

static_assert(offsetof(ClockSetter, row_values) == 0x08 && offsetof(ClockSetter, thumb) == 0x18, "thumb");
static_assert(sizeof(PushButton) == 0x48 && offsetof(ClockSetter, bar_x) == 0x60, "bar");
static_assert(offsetof(ClockSetter, marker_cell) == 0x70 && offsetof(ClockSetter, scroll_max) == 0x8c, "cells");
static_assert(offsetof(ClockSetter, flags) == 0x90 && offsetof(ClockSetter, blink) == 0x98, "flags");
static_assert(offsetof(ClockSetter, hand) == 0x9e && offsetof(ClockSetter, mode) == 0xa0, "hand");
static_assert(offsetof(ClockSetter, list_field) == 0xa5 && offsetof(ClockSetter, list_col) == 0xa7, "list");
static_assert(offsetof(ClockSetter, cursor) == 0xb0 && offsetof(ClockSetter, key_run) == 0xb7, "cursor");
static_assert(offsetof(ClockSetter, value) == 0xb8 && offsetof(ClockSetter, drag) == 0xc0, "value");
static_assert(offsetof(ClockSetter, min) == 0xc8 && offsetof(ClockSetter, max) == 0xd0, "bounds");
static_assert(sizeof(TextLabel) == 0x6c && offsetof(ClockSetter, labels) == 0xd8, "labels");
static_assert(sizeof(LayerTask) == 0x24 && offsetof(ClockSetter, panel_task) == 0x804, "tasks");
static_assert(offsetof(ClockSetter, list_task) == 0x828 && offsetof(ClockSetter, palette_task) == 0x84c, "tasks");
static_assert(offsetof(ClockSetter, panel_map) == 0x870 && offsetof(ClockSetter, list_base) == 0x1070, "maps");
static_assert(offsetof(ClockSetter, list_map) == 0x1870 && offsetof(ClockSetter, list_map_shown) == 0x2070, "maps");
static_assert(offsetof(ClockSetter, palette) == 0x2870 && offsetof(ClockSetter, palette_shown) == 0x2890, "palettes");
static_assert(sizeof(ClockSetter) == 0x28b0, "size (the scenes of overlays 135-138 hold it at 0x2c8 of 0x2b78)");

/* The layout of the fields by mode, in tiles of the panel's screen: the left column (mode 2,
 * mode 1, the others), the top row (likewise) and the width (every mode). */
extern const s32 data_ov134_0229bfd4[CLOCK_SETTER_FIELDS];
extern const s32 data_ov134_0229bfec[CLOCK_SETTER_FIELDS];
extern const s32 data_ov134_0229bf74[CLOCK_SETTER_FIELDS];
extern const s32 data_ov134_0229bf8c[CLOCK_SETTER_FIELDS];
extern const s32 data_ov134_0229bfbc[CLOCK_SETTER_FIELDS];
extern const s32 data_ov134_0229c004[CLOCK_SETTER_FIELDS];
extern const s32 data_ov134_0229bfa4[CLOCK_SETTER_FIELDS];

/* The weekdays' names, Sunday first (menu messages 0xaa-0xb0). */
extern const u8 data_ov134_0229bf6c[7];

/* The OBJs and cells drawn (ClockSetter_Draw): the hands' pin, the minute and the hour hand; the
 * panel's frame; the list's top shade; the frames of the fields of modes 0 and 3, mode 2 and
 * mode 1; the cells of each field (modes 0 and 3) and the cells of the month and day (mode 2)
 * and of the hour and minute (mode 1). */
extern const OamEntry data_ov134_0229c134;
extern const OamEntry data_ov134_0229c13c;
extern const OamEntry data_ov134_0229c144;
extern const OamEntry data_ov134_0229c024[];
extern const OamEntry data_ov134_0229c06c[];
extern const OamEntry data_ov134_0229c17c[];
extern const OamEntry data_ov134_0229c384[];
extern const OamEntry *const data_ov134_0229c14c[CLOCK_SETTER_FIELDS];
extern const OamEntry data_ov134_0229c1f4[];
extern const OamEntry data_ov134_0229c214[];
extern const OamEntry data_ov134_0229c1b4[];
extern const OamEntry data_ov134_0229c1d4[];

/* The files: the OBJ palettes and characters, the digits' characters by face (a table of one
 * entry, "menu/clock/b_tim_ten0_obj.bch") and their palettes; the background's characters and
 * palettes, each mode's palettes (bg0-bg3.bpl), the backdrop's screen, each mode's fields'
 * screen (bgb-bge.bsc), the list's screen and the list's palette. */
extern const char data_ov134_0229c3f4[];
extern const char data_ov134_0229c410[];
extern const char *const data_ov134_0229c020[];
extern const char data_ov134_0229c42c[];
extern const char data_ov134_0229c44c[];
extern const char data_ov134_0229c464[];
extern const char *const data_ov134_0229c05c[4];
extern const char data_ov134_0229c47c[];
extern const char *const data_ov134_0229c02c[4];
extern const char data_ov134_0229c490[];
extern const char data_ov134_0229c4ac[];

/* The heap the scenes load into (autoload_2/heap.c), and the pad (autoload_2/input.c). */
extern Heap *data_021fbe94;
extern PadState data_021fbe40;
#define CLOCK_SETTER_PAD_UP 0x40
#define CLOCK_SETTER_PAD_DOWN 0x80

/* The labels' class: constructor and destructor, as the game hands them to __cxa_vec_ctor and
 * __cxa_vec_cleanup (main/text_label.h's TextLabel_Construct and TextLabel_Destruct). */
extern void func_02070c08(void *label);
extern void func_02070be8(void *label);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);

/* The list's palette queued with its last colour faded (ClockSetter_FadeListColor). */
#define CLOCK_SETTER_LIST_PALETTE 9

/* The palettes of the cells drawn: a focused field's, the weekday's on a Sunday and otherwise,
 * a field's in mode 1 or 2 that is not focused. -1 keeps a cell's own. */
#define CLOCK_SETTER_CELL_FOCUS 7
#define CLOCK_SETTER_CELL_SUNDAY 10
#define CLOCK_SETTER_CELL_WEEKDAY 9
#define CLOCK_SETTER_CELL_PLAIN 6
#define CLOCK_SETTER_CELL_OWN (-1)

/* Where the analog clock's middle is, from the draw's origin; the frame's middle. */
#define CLOCK_SETTER_DIAL_X 0x38
#define CLOCK_SETTER_DIAL_Y 0x34
#define CLOCK_SETTER_FRAME_X 0x80
#define CLOCK_SETTER_FRAME_Y 0x60

/* The labels' characters on the panel layer: year, month, day, hour, minute, weekday. */
#define CLOCK_SETTER_CHAR_YEAR 0x180
#define CLOCK_SETTER_CHAR_MONTH 0x190
#define CLOCK_SETTER_CHAR_DAY 0x19c
#define CLOCK_SETTER_CHAR_HOUR 0x1b6
#define CLOCK_SETTER_CHAR_MINUTE 0x1c2
#define CLOCK_SETTER_CHAR_WEEKDAY 0x1a8

/* The year is shown from 2000. */
#define CLOCK_SETTER_YEAR_BASE 2000

#define CLOCK_SETTER_SCREEN_BYTES 0x800

static PushButton *panel_thumb(ClockSetter *self)
{
    return &self->thumb;
}

/* A member's virtual function `slot` (2 draws, 3 animates) through its own vtable. */
static void panel_call_member(void *object, int slot)
{
    const u32 *vtable = (const u32 *) (uintptr_t) *(const u32 *) object;
    ((void (*)(void *))(uintptr_t) vtable[slot])(object);
}

static int panel_address(const void *pointer)
{
    return (int) (uintptr_t) pointer;
}

/* func_ov134_022995a0 */
void ClockSetter_ClearFlags(ClockSetter *self, u16 flags)
{
    self->flags = (u16) (self->flags & ~flags);
}
CLEAN_AS(func_ov134_022995a0, ClockSetter_ClearFlags)

/* func_ov134_022995b0 */
void ClockSetter_SetFlags(ClockSetter *self, u32 flags)
{
    self->flags = (u16) (self->flags | flags);
}
CLEAN_AS(func_ov134_022995b0, ClockSetter_SetFlags)

/* func_ov134_022995c0 */
int ClockSetter_TestFlags(ClockSetter *self, u32 flags)
{
    return (self->flags & flags) != 0;
}
CLEAN_AS(func_ov134_022995c0, ClockSetter_TestFlags)

/* func_ov134_022995d4: the list's palette queued with its last colour (15) blended from colour
 * 14 (step 0) to its own (step 3), a third of the way for each step. */
void ClockSetter_FadeListColor(ClockSetter *self, int step)
{
    MIi_CpuCopy16(self->palette, self->palette_shown, sizeof self->palette_shown);
    u16 from = self->palette[14];
    u16 to = self->palette[15];
    int rest = 3 - step;
    u8 red = (u8) (((u8) (to & 0x1f) * step + (u8) (from & 0x1f) * rest) / 3);
    u8 green = (u8) (((u8) ((to & 0x3e0) >> 5) * step + (u8) ((from & 0x3e0) >> 5) * rest) / 3);
    u8 blue = (u8) (((u8) ((to & 0x7c00) >> 10) * step + (u8) ((from & 0x7c00) >> 10) * rest) / 3);
    self->palette_shown[15] = (u16) (red | (green << 5) | (blue << 10));
    LayerTask_QueuePalette(&self->palette_task, panel_address(self->palette_shown), self->list_layer,
                           CLOCK_SETTER_LIST_PALETTE);
}
CLEAN_AS(func_ov134_022995d4, ClockSetter_FadeListColor)

/* func_ov134_0229a868: the focus moved to `field` (CLOCK_SETTER_NO_FIELD for none): the field
 * that had it and the one that has it are coloured again. */
void ClockSetter_SetFocus(ClockSetter *self, int field)
{
    u8 before = self->focus;
    if (before == field) {
        return;
    }
    self->focus = (u8) field;
    if (before != CLOCK_SETTER_NO_FIELD) {
        ClockSetter_ColorField(self, before, CLOCK_SETTER_PAL_NORMAL);
    }
    if (field != CLOCK_SETTER_NO_FIELD) {
        ClockSetter_ColorField(self, field, CLOCK_SETTER_PAL_NORMAL);
    }
}
CLEAN_AS(func_ov134_0229a868, ClockSetter_SetFocus)

/* func_ov134_0229a8a0 */
u8 ClockSetter_Focus(ClockSetter *self)
{
    return self->focus;
}
CLEAN_AS(func_ov134_0229a8a0, ClockSetter_Focus)

/* func_ov134_0229a8a8: each field's highlight counted down; one that runs out is coloured
 * normally again. */
void ClockSetter_TickBlinks(ClockSetter *self)
{
    for (int field = 0; field < CLOCK_SETTER_FIELDS; field++) {
        if (self->blink[field] != 0) {
            self->blink[field]--;
            if (self->blink[field] == 0) {
                ClockSetter_ColorField(self, field, CLOCK_SETTER_PAL_NORMAL);
            }
        }
    }
}
CLEAN_AS(func_ov134_0229a8a8, ClockSetter_TickBlinks)

/* func_ov134_0229a8e8: every field coloured normally, the highlights stopped. */
void ClockSetter_ResetFieldColors(ClockSetter *self)
{
    for (int field = 0; field < CLOCK_SETTER_FIELDS; field++) {
        ClockSetter_ColorField(self, field, CLOCK_SETTER_PAL_NORMAL);
    }
    for (int field = 0; field < CLOCK_SETTER_FIELDS; field++) {
        self->blink[field] = 0;
    }
}
CLEAN_AS(func_ov134_0229a8e8, ClockSetter_ResetFieldColors)

/* func_ov134_0229a918: the field's button (the two tiles right of it, one for the hour of mode
 * 0) on its two rows set to `palette`. */
void ClockSetter_ColorFieldButton(ClockSetter *self, int field, int palette)
{
    int left = ClockSetter_FieldRight(self, field) + 1;
    int top = ClockSetter_FieldTop(self, field);
    int right;
    if (self->mode == CLOCK_SETTER_MODE_DATE_TIME && field == CLOCK_SETTER_HOUR) {
        right = left + 1;
    } else {
        right = left + 2;
    }
    ScreenMap_SetPalette(self->panel_map, left, top, right, top + 1, (u32) palette);
    ClockSetter_SetFlags(self, CLOCK_SETTER_FLAG_PANEL_DIRTY);
}
CLEAN_AS(func_ov134_0229a918, ClockSetter_ColorFieldButton)

/* func_ov134_0229a96c: the field's tiles set to `palette`, as the mode and the field have it:
 * mode 1 leaves the year alone and dims the month, the day and the weekday (normal to
 * PAL_DIM, focus to PAL_DIM_FOCUS); mode 2 colours only the month and the day. The weekday in
 * the normal palette turns PAL_SUNDAY on a Sunday (CLOCK_SETTER_FLAG_SUNDAY follows), and the
 * focused field in the normal palette turns PAL_FOCUS. */
void ClockSetter_ColorField(ClockSetter *self, int field, int palette)
{
    u8 mode = self->mode;
    if (mode == CLOCK_SETTER_MODE_TIME) {
        if (field == CLOCK_SETTER_YEAR) {
            return;
        }
        if (field == CLOCK_SETTER_MONTH || field == CLOCK_SETTER_DAY || field == CLOCK_SETTER_WEEKDAY) {
            if (palette == CLOCK_SETTER_PAL_NORMAL) {
                palette = CLOCK_SETTER_PAL_DIM;
            }
            if (palette == CLOCK_SETTER_PAL_FOCUS) {
                palette = CLOCK_SETTER_PAL_DIM_FOCUS;
            }
        }
    } else if (mode == CLOCK_SETTER_MODE_MONTH_DAY) {
        if (field != CLOCK_SETTER_MONTH && field != CLOCK_SETTER_DAY) {
            return;
        }
    }
    if (field == CLOCK_SETTER_WEEKDAY && palette == CLOCK_SETTER_PAL_NORMAL) {
        if (Calendar_Weekday(self->value.year, self->value.month, self->value.day) == 0) {
            palette = CLOCK_SETTER_PAL_SUNDAY;
            ClockSetter_SetFlags(self, CLOCK_SETTER_FLAG_SUNDAY);
        } else {
            ClockSetter_ClearFlags(self, CLOCK_SETTER_FLAG_SUNDAY);
        }
    }
    if (self->focus == field && palette == CLOCK_SETTER_PAL_NORMAL) {
        palette = CLOCK_SETTER_PAL_FOCUS;
    }
    int left = ClockSetter_FieldLeft(self, field);
    int top = ClockSetter_FieldTop(self, field);
    int right = ClockSetter_FieldRight(self, field);
    int bottom = ClockSetter_FieldBottom(self, field);
    ScreenMap_SetPalette(self->panel_map, left, top, right, bottom, (u32) palette);
    ClockSetter_SetFlags(self, CLOCK_SETTER_FLAG_PANEL_DIRTY);
}
CLEAN_AS(func_ov134_0229a96c, ClockSetter_ColorField)

/* func_ov134_0229aa3c: a field is two rows of tiles. */
int ClockSetter_FieldBottom(ClockSetter *self, int field)
{
    return ClockSetter_FieldTop(self, field) + 1;
}
CLEAN_AS(func_ov134_0229aa3c, ClockSetter_FieldBottom)

/* func_ov134_0229aa4c */
int ClockSetter_FieldRight(ClockSetter *self, int field)
{
    int left = ClockSetter_FieldLeft(self, field);
    int width = ClockSetter_FieldWidth(self, field);
    return left + width - 1;
}
CLEAN_AS(func_ov134_0229aa4c, ClockSetter_FieldRight)

/* func_ov134_0229aa6c: the same in every mode. */
int ClockSetter_FieldWidth(ClockSetter *self, int field)
{
    (void) self;
    return data_ov134_0229bfa4[field];
}
CLEAN_AS(func_ov134_0229aa6c, ClockSetter_FieldWidth)

/* func_ov134_0229aa78 */
int ClockSetter_FieldTop(ClockSetter *self, int field)
{
    u8 mode = self->mode;
    if (mode == CLOCK_SETTER_MODE_MONTH_DAY) {
        return data_ov134_0229bf8c[field];
    }
    if (mode == CLOCK_SETTER_MODE_TIME) {
        return data_ov134_0229bfbc[field];
    }
    return data_ov134_0229c004[field];
}
CLEAN_AS(func_ov134_0229aa78, ClockSetter_FieldTop)

/* func_ov134_0229aaa8 (its source gives the word as a pointer) */
int ClockSetter_FieldLeft(ClockSetter *self, int field)
{
    u8 mode = self->mode;
    if (mode == CLOCK_SETTER_MODE_MONTH_DAY) {
        return data_ov134_0229bfd4[field];
    }
    if (mode == CLOCK_SETTER_MODE_TIME) {
        return data_ov134_0229bfec[field];
    }
    return data_ov134_0229bf74[field];
}
CLEAN_AS(func_ov134_0229aaa8, ClockSetter_FieldLeft)

/* The first of the fields `first`-`last` whose tiles, with `extra` tiles more on the right (its
 * button), hold the tile of pixel (x, y); CLOCK_SETTER_NO_FIELD for none. `extra_hour` is the
 * hour's. */
static int panel_touched_field(ClockSetter *self, int x, int y, int first, int last, int extra, int extra_hour)
{
    int column = x >> 3;
    int row = y >> 3;
    for (int field = first; field <= last; field++) {
        int more = field == CLOCK_SETTER_HOUR ? extra_hour : extra;
        if (ClockSetter_FieldLeft(self, field) > column) {
            continue;
        }
        if (ClockSetter_FieldRight(self, field) + more < column) {
            continue;
        }
        if (ClockSetter_FieldTop(self, field) > row) {
            continue;
        }
        if (ClockSetter_FieldBottom(self, field) < row) {
            continue;
        }
        return field;
    }
    return CLOCK_SETTER_NO_FIELD;
}

/* func_ov134_0229aad8: the hour or the minute touched (mode 1's screen). */
int ClockSetter_TouchedTimeField(ClockSetter *self, int x, int y)
{
    return panel_touched_field(self, x, y, CLOCK_SETTER_HOUR, CLOCK_SETTER_MINUTE, 3, 3);
}
CLEAN_AS(func_ov134_0229aad8, ClockSetter_TouchedTimeField)

/* func_ov134_0229ab2c: the month or the day touched. */
int ClockSetter_TouchedMonthDayField(ClockSetter *self, int x, int y)
{
    return panel_touched_field(self, x, y, CLOCK_SETTER_MONTH, CLOCK_SETTER_DAY, 3, 3);
}
CLEAN_AS(func_ov134_0229ab2c, ClockSetter_TouchedMonthDayField)

/* func_ov134_0229ab80: the year, the month or the day touched. */
int ClockSetter_TouchedDateField(ClockSetter *self, int x, int y)
{
    return panel_touched_field(self, x, y, CLOCK_SETTER_YEAR, CLOCK_SETTER_DAY, 3, 3);
}
CLEAN_AS(func_ov134_0229ab80, ClockSetter_TouchedDateField)

/* func_ov134_0229abd4: any field but the weekday touched; the hour's button is a tile
 * narrower (ClockSetter_ColorFieldButton). */
int ClockSetter_TouchedField(ClockSetter *self, int x, int y)
{
    return panel_touched_field(self, x, y, CLOCK_SETTER_YEAR, CLOCK_SETTER_MINUTE, 3, 2);
}
CLEAN_AS(func_ov134_0229abd4, ClockSetter_TouchedField)

static void panel_draw_cell(const OamEntry *cell, int x, int y, int palette, int priority)
{
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_SUB, cell, x, y, palette, priority, 0x1000, 0x1000, 0, -1, 0, 0);
}

/* The two cells of mode 1 or 2: the first in the focus's palette when `first` has the focus,
 * the second when `second` has it. */
static void panel_draw_pair(ClockSetter *self, const OamEntry *first_cell, const OamEntry *second_cell, int first, int second,
                            int x, int y)
{
    int first_palette;
    int second_palette;
    if (self->focus == first) {
        first_palette = CLOCK_SETTER_CELL_FOCUS;
        second_palette = CLOCK_SETTER_CELL_PLAIN;
    } else if (self->focus == second) {
        second_palette = CLOCK_SETTER_CELL_FOCUS;
        first_palette = CLOCK_SETTER_CELL_PLAIN;
    } else {
        first_palette = CLOCK_SETTER_CELL_PLAIN;
        second_palette = first_palette;
    }
    panel_draw_cell(first_cell, x, y, first_palette, 2);
    panel_draw_cell(second_cell, x, y, second_palette, 2);
}

/* func_ov134_0229b220: the panel's OBJs on the sub screen, moved by (x, y): the hands (face 0),
 * the frame, the scroll thumb while the list is open, the list's edges, the picked row's
 * marker, and the cells of the fields as the mode has them. */
void ClockSetter_Draw(ClockSetter *self, int x, int y)
{
    int frame_x = x + CLOCK_SETTER_FRAME_X;
    int frame_y = y + CLOCK_SETTER_FRAME_Y;

    if (self->face == 0) {
        int dial_x = x + CLOCK_SETTER_DIAL_X;
        int dial_y = y + CLOCK_SETTER_DIAL_Y;
        OamBuffer_DrawObjAffine(OAM_BUFFER_SCREEN_SUB, &data_ov134_0229c134, dial_x, dial_y, -1, 2, NULL);
        OamBuffer_DrawObjRotated(OAM_BUFFER_SCREEN_SUB, &data_ov134_0229c13c, dial_x, dial_y, -1, 2, 0x1000,
                                 self->minute_angle, 0);
        OamBuffer_DrawObjRotated(OAM_BUFFER_SCREEN_SUB, &data_ov134_0229c144, dial_x, dial_y, -1, 2, 0x1000, self->hour_angle,
                                 0);
    }
    panel_draw_cell(data_ov134_0229c024, frame_x, frame_y, CLOCK_SETTER_CELL_OWN, 2);
    if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_THUMB_SHOWN)) {
        panel_call_member(panel_thumb(self), 2);
    }
    if (self->top_cell != NULL) {
        if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_LIST_FRESH)) {
            ClockSetter_ClearFlags(self, CLOCK_SETTER_FLAG_LIST_FRESH);
        } else {
            panel_draw_cell(data_ov134_0229c06c, self->list_x - 8, self->window_top, CLOCK_SETTER_CELL_OWN, 1);
        }
        panel_draw_cell(self->top_cell, self->list_x - 8, self->window_top, CLOCK_SETTER_CELL_OWN, 1);
    }
    if (self->bottom_cell != NULL) {
        panel_draw_cell(self->bottom_cell, self->list_x - 8, self->window_bottom, CLOCK_SETTER_CELL_OWN, 1);
    }
    if (self->marker_cell != NULL) {
        panel_draw_cell(self->marker_cell, self->list_x, self->marker_y, CLOCK_SETTER_CELL_OWN, 1);
    }

    switch (self->mode) {
        case CLOCK_SETTER_MODE_DATE_TIME:
        case CLOCK_SETTER_MODE_DATE:
            panel_draw_cell(data_ov134_0229c17c, frame_x, frame_y, CLOCK_SETTER_CELL_OWN, 2);
            for (int field = CLOCK_SETTER_YEAR; field <= CLOCK_SETTER_MINUTE; field++) {
                /* mode 3 does not show the time */
                if (self->mode == CLOCK_SETTER_MODE_DATE && (field == CLOCK_SETTER_HOUR || field == CLOCK_SETTER_MINUTE)) {
                    continue;
                }
                int palette = field == self->focus ? CLOCK_SETTER_CELL_FOCUS : CLOCK_SETTER_CELL_OWN;
                panel_draw_cell(data_ov134_0229c14c[field], frame_x, frame_y, palette, 2);
            }
            panel_draw_cell(data_ov134_0229c14c[CLOCK_SETTER_WEEKDAY], frame_x, frame_y,
                            ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_SUNDAY) ? CLOCK_SETTER_CELL_SUNDAY
                                                                                  : CLOCK_SETTER_CELL_WEEKDAY,
                            2);
            break;
        case CLOCK_SETTER_MODE_MONTH_DAY:
            panel_draw_pair(self, data_ov134_0229c1f4, data_ov134_0229c214, CLOCK_SETTER_MONTH, CLOCK_SETTER_DAY, frame_x,
                            frame_y);
            break;
        case CLOCK_SETTER_MODE_TIME:
            panel_draw_cell(data_ov134_0229c384, frame_x, frame_y, CLOCK_SETTER_CELL_OWN, 2);
            panel_draw_pair(self, data_ov134_0229c1b4, data_ov134_0229c1d4, CLOCK_SETTER_HOUR, CLOCK_SETTER_MINUTE, frame_x,
                            frame_y);
            break;
    }
}
CLEAN_AS(func_ov134_0229b220, ClockSetter_Draw)

/* func_ov134_0229b5ac: `number` drawn against the right of a box of `cells` cells from
 * character `first_char` of `layer`, with the next label. */
void ClockSetter_DrawNumber(ClockSetter *self, int layer, int first_char, int cells, int number, u8 color_38, u8 color_39)
{
    TextLabel *label = ClockSetter_NextLabel(self);
    TextLabel_Compose(label, number, 4, 0, 0, 0);
    TextLabel_OpenStyledBox2(label, layer, first_char, cells, color_38, color_39, 0);
    TextLabel_ShowRightAligned(label);
}
CLEAN_AS(func_ov134_0229b5ac, ClockSetter_DrawNumber)

/* func_ov134_0229b5f4: menu message `message` drawn in the middle of a box of `cells` cells,
 * moved left by 4 pixels for each cell it has more than `text_cells` (so it sits in the middle
 * of the first `text_cells`). */
void ClockSetter_DrawTitle(ClockSetter *self, int layer, int first_char, int cells, u8 message, int text_cells)
{
    TextLabel *label = ClockSetter_NextLabel(self);
    TextLabel_LoadMenuMessage(label, (char) message);
    TextLabel_OpenStyledBox2(label, layer, first_char, cells, 15, 0, 0);
    TextLabel_ShowShifted(label, 1, -(int) ((u32) (cells - text_cells) << 2));
}
CLEAN_AS(func_ov134_0229b5f4, ClockSetter_DrawTitle)

/* func_ov134_0229b63c: menu message `message` drawn from the left or in the middle. */
void ClockSetter_DrawMessage(ClockSetter *self, int layer, int first_char, int cells, u8 message, int center, u8 color_38,
                             u8 color_39)
{
    TextLabel *label = ClockSetter_NextLabel(self);
    TextLabel_LoadMenuMessage(label, (char) message);
    TextLabel_OpenStyledBox2(label, layer, first_char, cells, color_38, color_39, 0);
    TextLabel_Show(label, center, 0);
}
CLEAN_AS(func_ov134_0229b63c, ClockSetter_DrawMessage)

/* func_ov134_0229b680: the next of the labels; once sixteen are out, the last one again and
 * again. */
TextLabel *ClockSetter_NextLabel(ClockSetter *self)
{
    if (self->labels_used >= CLOCK_SETTER_LABELS) {
        return &self->labels[CLOCK_SETTER_LABELS - 1];
    }
    self->labels_used++;
    return &self->labels[self->labels_used - 1];
}
CLEAN_AS(func_ov134_0229b680, ClockSetter_NextLabel)

/* func_ov134_0229b6b4: every label's box closed and the labels handed out again. */
void ClockSetter_CloseLabels(ClockSetter *self)
{
    self->labels_used = 0;
    for (int i = 0; i < CLOCK_SETTER_LABELS; i++) {
        TextLabel_CloseBox(&self->labels[i]);
    }
}
CLEAN_AS(func_ov134_0229b6b4, ClockSetter_CloseLabels)

/* func_ov134_0229b6dc: the picked row's value drawn into the OBJ characters at 0xcb (the marker
 * that closes onto the field). */
void ClockSetter_DrawPickLabel(ClockSetter *self)
{
    int cells = 3;
    int number = self->list_pick;
    switch (self->list_field) {
        case CLOCK_SETTER_YEAR:
            cells = 5;
            number += CLOCK_SETTER_YEAR_BASE;
            break;
        case CLOCK_SETTER_MONTH:
        case CLOCK_SETTER_DAY:
            number += 1;
            break;
        default:
            break;
    }
    ClockSetter_DrawNumber(self, LAYER_SUB_OBJ, 0xcb, cells, number, 15, 0);
}
CLEAN_AS(func_ov134_0229b6dc, ClockSetter_DrawPickLabel)

/* func_ov134_0229b724 */
void ClockSetter_DrawMinute(ClockSetter *self)
{
    ClockSetter_DrawNumber(self, self->panel_layer, CLOCK_SETTER_CHAR_MINUTE, 3, self->value.minute, 15, 0);
}
CLEAN_AS(func_ov134_0229b724, ClockSetter_DrawMinute)

/* func_ov134_0229b750 */
void ClockSetter_DrawHour(ClockSetter *self)
{
    ClockSetter_DrawNumber(self, self->panel_layer, CLOCK_SETTER_CHAR_HOUR, 3, self->value.hour, 15, 0);
}
CLEAN_AS(func_ov134_0229b750, ClockSetter_DrawHour)

/* func_ov134_0229b77c */
void ClockSetter_DrawDay(ClockSetter *self)
{
    ClockSetter_DrawNumber(self, self->panel_layer, CLOCK_SETTER_CHAR_DAY, 3, self->value.day, 15, 0);
}
CLEAN_AS(func_ov134_0229b77c, ClockSetter_DrawDay)

/* func_ov134_0229b7a8 */
void ClockSetter_DrawMonth(ClockSetter *self)
{
    ClockSetter_DrawNumber(self, self->panel_layer, CLOCK_SETTER_CHAR_MONTH, 3, self->value.month, 15, 0);
}
CLEAN_AS(func_ov134_0229b7a8, ClockSetter_DrawMonth)

/* func_ov134_0229b7d4 */
void ClockSetter_DrawYear(ClockSetter *self)
{
    ClockSetter_DrawNumber(self, self->panel_layer, CLOCK_SETTER_CHAR_YEAR, 5, self->value.year + CLOCK_SETTER_YEAR_BASE, 15,
                           0);
}
CLEAN_AS(func_ov134_0229b7d4, ClockSetter_DrawYear)

/* func_ov134_0229b808: field `field` of the value set from a row of its list (the month's and
 * the day's rows count from 0); the weekday is not set. */
void ClockSetter_SetField(ClockSetter *self, unsigned int field, int value)
{
    switch (field) {
        case CLOCK_SETTER_YEAR:
            self->value.year = (u8) value;
            break;
        case CLOCK_SETTER_MONTH:
            self->value.month = (u8) (value + 1);
            break;
        case CLOCK_SETTER_DAY:
            self->value.day = (u8) (value + 1);
            break;
        case CLOCK_SETTER_HOUR:
            self->value.hour = (u8) value;
            break;
        case CLOCK_SETTER_MINUTE:
            self->value.minute = (u8) value;
            break;
        case CLOCK_SETTER_WEEKDAY:
            break;
    }
}
CLEAN_AS(func_ov134_0229b808, ClockSetter_SetField)

/* func_ov134_0229b848: field `field` of `when` (0 for the weekday, 0xff past it). */
int ClockSetter_FieldOf(ClockSetter *self, unsigned int field, const DateTime *when)
{
    (void) self;
    switch (field) {
        case CLOCK_SETTER_YEAR:
            return when->year;
        case CLOCK_SETTER_MONTH:
            return when->month;
        case CLOCK_SETTER_DAY:
            return when->day;
        case CLOCK_SETTER_HOUR:
            return when->hour;
        case CLOCK_SETTER_MINUTE:
            return when->minute;
        case CLOCK_SETTER_WEEKDAY:
            return 0;
    }
    return 0xff;
}
CLEAN_AS(func_ov134_0229b848, ClockSetter_FieldOf)

/* func_ov134_0229b884: field `field` of the value. */
int ClockSetter_Field(ClockSetter *self, int field)
{
    return ClockSetter_FieldOf(self, (unsigned int) field, &self->value);
}
CLEAN_AS(func_ov134_0229b884, ClockSetter_Field)

/* func_ov134_0229b890: the label of field `field` drawn again. */
void ClockSetter_DrawField(ClockSetter *self, unsigned int field)
{
    switch (field) {
        case CLOCK_SETTER_YEAR:
            ClockSetter_DrawYear(self);
            break;
        case CLOCK_SETTER_MONTH:
            ClockSetter_DrawMonth(self);
            break;
        case CLOCK_SETTER_DAY:
            ClockSetter_DrawDay(self);
            break;
        case CLOCK_SETTER_HOUR:
            ClockSetter_DrawHour(self);
            break;
        case CLOCK_SETTER_MINUTE:
            ClockSetter_DrawMinute(self);
            break;
        case CLOCK_SETTER_WEEKDAY:
            ClockSetter_DrawWeekday(self);
            break;
    }
}
CLEAN_AS(func_ov134_0229b890, ClockSetter_DrawField)

/* func_ov134_0229b8dc */
void ClockSetter_DrawFields(ClockSetter *self)
{
    ClockSetter_DrawYear(self);
    ClockSetter_DrawMonth(self);
    ClockSetter_DrawDay(self);
    ClockSetter_DrawHour(self);
    ClockSetter_DrawMinute(self);
    ClockSetter_DrawWeekday(self);
}
CLEAN_AS(func_ov134_0229b8dc, ClockSetter_DrawFields)

/* func_ov134_0229b908: the value's weekday's name, in the middle of its box. */
void ClockSetter_DrawWeekday(ClockSetter *self)
{
    int weekday = Calendar_Weekday(self->value.year, self->value.month, self->value.day);
    ClockSetter_DrawMessage(self, self->panel_layer, CLOCK_SETTER_CHAR_WEEKDAY, 7, data_ov134_0229bf6c[weekday], 1, 15, 0);
}
CLEAN_AS(func_ov134_0229b908, ClockSetter_DrawWeekday)

/* func_ov134_0229b954: the sub screen's OBJ graphics: the palettes 4-10 and the characters
 * 0xc0-0x1df, then the face's digits, eight rows of 0x400 bytes from the face's 0x100-byte
 * column of the file, into the characters 0xc0-0xc7, 0xe0-0xe7 and so on, then their palette
 * (the face's) into palette 4. */
int ClockSetter_LoadSprites(ClockSetter *self)
{
    Heap *heap = data_021fbe94;
    u32 size;
    DisplayLayer_LoadPalettesFromFile(data_ov134_0229c3f4, heap, LAYER_SUB_OBJ, 4, 4, 10);
    DisplayLayer_LoadCharsFromFile(data_ov134_0229c410, heap, LAYER_SUB_OBJ, 0xc0, 0xc0, 0x1df);
    u8 face = self->face;
    u8 *file = RomFile_Load(data_ov134_0229c020[face >> 2], heap, -4, &size);
    u32 data = (u32) (uintptr_t) file + ((u32) (face % 4) << 8);
    u32 first = 0xc0;
    for (int row = 0; row < 8; row++) {
        DisplayLayer_LoadChars(data, LAYER_SUB_OBJ, first, first, first + 7);
        data += 0x400;
        first += 0x20;
    }
    Heap_Free(heap, file);
    return DisplayLayer_LoadPaletteFromFile(data_ov134_0229c42c, heap, LAYER_SUB_OBJ, self->face, 4);
}
CLEAN_AS(func_ov134_0229b954, ClockSetter_LoadSprites)

/* func_ov134_0229ba10: the fields' names, the values, and the screen's title (menu message
 * `title`, chosen by the scene) on the base layer. */
void ClockSetter_DrawLabels(ClockSetter *self, unsigned int title)
{
    ClockSetter_DrawMessage(self, self->panel_layer, 0x18a, 3, 0xb2, 0, 15, 0);
    ClockSetter_DrawMessage(self, self->panel_layer, 0x196, 3, 0xb3, 0, 15, 0);
    ClockSetter_DrawMessage(self, self->panel_layer, 0x1a2, 3, 0xb4, 0, 15, 0);
    ClockSetter_DrawMessage(self, self->panel_layer, 0x1bc, 3, 0xb5, 0, 15, 0);
    ClockSetter_DrawMessage(self, self->panel_layer, 0x1c8, 3, 0xb6, 0, 15, 0);
    ClockSetter_DrawFields(self);
    ClockSetter_DrawMessage(self, self->base_layer, 0x54, 0x10, (u8) title, 1, 15, 14);
}
CLEAN_AS(func_ov134_0229ba10, ClockSetter_DrawLabels)

/* func_ov134_0229baec: the background's characters (0x10-0x80) and palettes 1-10, the mode's
 * palettes 1-2, the backdrop's screen, all on the base layer; then the mode's fields' screen,
 * coloured normally, the list's screen and the list's palette, read into the panel. */
int ClockSetter_LoadBackground(ClockSetter *self)
{
    Heap *heap = data_021fbe94;
    DisplayLayer_LoadCharsFromFile(data_ov134_0229c44c, heap, self->base_layer, 0x10, 0x10, 0x80);
    DisplayLayer_LoadPalettesFromFile(data_ov134_0229c464, heap, self->base_layer, 1, 1, 10);
    DisplayLayer_LoadPalettesFromFile(data_ov134_0229c05c[self->mode], heap, self->base_layer, 1, 1, 2);
    DisplayLayer_LoadScreenFromFile(data_ov134_0229c47c, heap, self->base_layer);
    RomFile_Read(data_ov134_0229c02c[self->mode], self->panel_map, CLOCK_SETTER_SCREEN_BYTES);
    ClockSetter_ResetFieldColors(self);
    RomFile_Read(data_ov134_0229c490, self->list_base, CLOCK_SETTER_SCREEN_BYTES);
    return RomFile_Read(data_ov134_0229c4ac, self->palette, sizeof self->palette);
}
CLEAN_AS(func_ov134_0229baec, ClockSetter_LoadBackground)

/* func_ov134_0229bbbc: whether `min` is after the value (to the minute and the second). */
int ClockSetter_IsBeforeMin(ClockSetter *self)
{
    return DateTime_Compare(&self->min, &self->value, 0x3f) == 1;
}
CLEAN_AS(func_ov134_0229bbbc, ClockSetter_IsBeforeMin)

/* func_ov134_0229bbdc */
void ClockSetter_CopyValue(ClockSetter *self, DateTime *out)
{
    MI_CpuCopy8(&self->value, out, sizeof self->value);
}
CLEAN_AS(func_ov134_0229bbdc, ClockSetter_CopyValue)

/* func_ov134_0229bbe8: each frame: the list scrolled on, the thumb's release settled, the
 * screens that changed queued (each flag cleared once its load is queued), and the run of
 * steps ended when the pad holds up after steps up or down after steps down. */
void ClockSetter_Update(ClockSetter *self)
{
    ClockSetter_StepScroll(self);
    PushButton_SettleRelease(panel_thumb(self));
    if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_PANEL_DIRTY)) {
        if (LayerTask_QueueScreen(&self->panel_task, panel_address(self->panel_map), self->panel_layer,
                                  CLOCK_SETTER_SCREEN_BYTES, 0) != 0) {
            ClockSetter_ClearFlags(self, CLOCK_SETTER_FLAG_PANEL_DIRTY);
        }
    }
    if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_LIST_DIRTY)) {
        if (LayerTask_QueueScreen(&self->list_task, panel_address(self->list_map_shown), self->list_layer,
                                  CLOCK_SETTER_SCREEN_BYTES, 0) != 0) {
            ClockSetter_ClearFlags(self, CLOCK_SETTER_FLAG_LIST_DIRTY);
        }
    }
    if (self->key_run > 0) {
        if (data_021fbe40.held & CLOCK_SETTER_PAD_UP) {
            self->key_run = 0;
        }
    } else if (self->key_run < 0) {
        if (data_021fbe40.held & CLOCK_SETTER_PAD_DOWN) {
            self->key_run = 0;
        }
    }
}
CLEAN_AS(func_ov134_0229bbe8, ClockSetter_Update)

/* func_ov134_0229bcac: the end of a frame: the labels' boxes closed, the loads ended, the
 * highlights counted down and the thumb animated (vtable slot 3). */
void ClockSetter_EndFrame(ClockSetter *self)
{
    ClockSetter_CloseLabels(self);
    LayerTask_End(&self->panel_task);
    LayerTask_End(&self->list_task);
    LayerTask_End(&self->palette_task);
    ClockSetter_TickBlinks(self);
    panel_call_member(panel_thumb(self), 3);
}
CLEAN_AS(func_ov134_0229bcac, ClockSetter_EndFrame)

/* func_ov134_0229bcf0 */
void ClockSetter_Teardown(ClockSetter *self)
{
    ClockSetter_CloseLabels(self);
    DisplayLayer_Hide(self->list_layer);
    LayerTask_End(&self->panel_task);
    LayerTask_End(&self->list_task);
    LayerTask_End(&self->palette_task);
}
CLEAN_AS(func_ov134_0229bcf0, ClockSetter_Teardown)

/* func_ov134_0229bd2c: the value bounded below by `min` (overlay 135 asks for it after
 * ClockSetter_Init in one case of its own). */
void ClockSetter_UseMinimum(ClockSetter *self)
{
    ClockSetter_SetFlags(self, CLOCK_SETTER_FLAG_HAS_MIN);
}
CLEAN_AS(func_ov134_0229bd2c, ClockSetter_UseMinimum)

/* func_ov134_0229bd38: the panel set up for `mode` on its three layers. The value is now with
 * the seconds cleared (tomorrow for mode 3), or 2001-01-01 0:00 for mode 2; `min` is the value
 * and `max` twelve hours later; mode 1 is bounded by both and starts on the hour. The hands
 * show the value.
 * QUIRK: of the highlights only the first field's is cleared. */
void ClockSetter_Init(ClockSetter *self, int mode, int base_layer, int panel_layer, u8 list_layer)
{
    self->flags = 0;
    self->key_run = 0;
    self->mode = (u8) mode;
    self->blink[0] = 0;
    switch (self->mode) {
        case CLOCK_SETTER_MODE_DATE_TIME:
        case CLOCK_SETTER_MODE_TIME:
            self->face = 0;
            break;
        case CLOCK_SETTER_MODE_MONTH_DAY:
            self->face = 1;
            break;
        case CLOCK_SETTER_MODE_DATE:
            self->face = 2;
            break;
    }
    self->base_layer = (u8) base_layer;
    self->panel_layer = (u8) panel_layer;
    self->list_layer = list_layer;
    self->marker_cell = NULL;
    self->top_cell = NULL;
    self->bottom_cell = NULL;
    PushButton_ShowUp(panel_thumb(self));
    self->scroll_pending = 0;
    switch (self->mode) {
        case CLOCK_SETTER_MODE_DATE_TIME:
        case CLOCK_SETTER_MODE_DATE:
            self->focus = CLOCK_SETTER_YEAR;
            break;
        case CLOCK_SETTER_MODE_TIME:
            self->focus = CLOCK_SETTER_HOUR;
            ClockSetter_SetFlags(self, CLOCK_SETTER_FLAG_HAS_MAX);
            ClockSetter_SetFlags(self, CLOCK_SETTER_FLAG_HAS_MIN);
            break;
        case CLOCK_SETTER_MODE_MONTH_DAY:
            self->focus = CLOCK_SETTER_MONTH;
            break;
    }
    if (self->mode == CLOCK_SETTER_MODE_MONTH_DAY) {
        self->value.second = 0;
        self->value.minute = 0;
        self->value.hour = 0;
        self->value.day = 0;
        self->value.month = 0;
        self->value.year = 0;
        self->value.unused[0] = 0;
        self->value.unused[1] = 0;
        self->value.year = 1;
        self->value.month = 1;
        self->value.day = 1;
    } else {
        DateTime_Now(&self->value);
        self->value.second = 0;
        if (self->mode == CLOCK_SETTER_MODE_DATE) {
            DateTime_AddDays(&self->value, 1);
        }
        MI_CpuCopy8(&self->value, &self->min, sizeof self->min);
        MI_CpuCopy8(&self->value, &self->max, sizeof self->max);
        DateTime_AddHours(&self->max, 12);
        self->min_hour = self->min.hour;
        self->max_hour = self->max.hour;
        self->min_minute = self->min.minute;
        ClockSetter_HandsFromValue(self);
    }
}
CLEAN_AS(func_ov134_0229bd38, ClockSetter_Init)

/* func_ov134_0229beb0: the labels' and the thumb's destructors (the load tasks have none). */
ClockSetter *ClockSetter_Destroy(ClockSetter *self)
{
    __cxa_vec_cleanup(self->labels, CLOCK_SETTER_LABELS, sizeof(TextLabel), func_02070be8);
    PushButton_Destroy(panel_thumb(self));
    return self;
}
CLEAN_AS(func_ov134_0229beb0, ClockSetter_Destroy)

/* func_ov134_0229bed4: the thumb, the cells and positions (0x70-0x8f) cleared, the labels and
 * the three load tasks constructed. */
ClockSetter *ClockSetter_Construct(ClockSetter *self)
{
    PushButton_Construct(panel_thumb(self));
    self->marker_cell = NULL;
    self->top_cell = NULL;
    self->bottom_cell = NULL;
    self->list_x = 0;
    self->marker_y = 0;
    self->clock_minutes = 0;
    self->target_minutes = 0;
    self->scroll_max = 0;
    __cxa_vec_ctor(self->labels, CLOCK_SETTER_LABELS, sizeof(TextLabel), func_02070c08, func_02070be8);
    LayerTask_Construct(&self->panel_task);
    LayerTask_Construct(&self->list_task);
    LayerTask_Construct(&self->palette_task);
    return self;
}
CLEAN_AS(func_ov134_0229bed4, ClockSetter_Construct)
