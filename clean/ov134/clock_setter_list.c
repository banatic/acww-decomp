/* The clock setter's list of a field's values (clock_setter.h): opening it beside the field,
 * scrolling it with the scroll bar's thumb, the keys or the pen, picking a row (rows outside
 * `min` and `max` cannot be picked), writing it back and closing the list onto the field. */
#include "clock_setter.h"

#include <stddef.h>
#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/input.h"
#include "clean.h"
#include "main/calendar.h"
#include "main/date_time.h"
#include "main/display_layers.h"
#include "main/display_shadow.h"
#include "main/dual_cell_sprite.h"
#include "main/screen_map.h"
#include "main/sound.h"
#include "ov002/key_repeat.h"
#include "ov002/push_button.h"

/* The rows of each field's list (the day's is the month's length): 100, 12, 31, 24, 60, 7. */
extern const u8 data_ov134_0229bf64[CLOCK_SETTER_FIELDS];
/* The menu message of each field's list title. */
extern const u8 data_ov134_0229bf5c[CLOCK_SETTER_FIELDS];

/* The list's edges (ClockSetter_Draw): top and bottom for the year's list and for the others;
 * the marker of the picked row, the year's and the others'. */
extern const OamEntry data_ov134_0229c294[];
extern const OamEntry data_ov134_0229c164[];
extern const OamEntry data_ov134_0229c2c4[];
extern const OamEntry data_ov134_0229c11c[];
extern const OamEntry data_ov134_0229c04c[];
extern const OamEntry data_ov134_0229c03c[];

/* The pad (autoload_2/input.c). */
extern PadState data_021fbe40;
#define CLOCK_SETTER_PAD_UP 0x40
#define CLOCK_SETTER_PAD_DOWN 0x80

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);

/* The thumb's range on the bar, and its step for the keys. */
#define CLOCK_SETTER_THUMB_TOP 0x20
#define CLOCK_SETTER_THUMB_BOTTOM 0xa0
#define CLOCK_SETTER_THUMB_RANGE 0x80
#define CLOCK_SETTER_THUMB_KEY_STEP 4

/* The rows are 16 pixels; the list shows from y 0x28 to 0xa8 (eight rows). */
#define CLOCK_SETTER_ROW_HEIGHT 16
#define CLOCK_SETTER_LIST_TOP 0x28
#define CLOCK_SETTER_LIST_BOTTOM 0xa8
#define CLOCK_SETTER_ROWS_VISIBLE 8

/* The list's screen entries: blank (palette 3, the list's background), the left border, the
 * entry outside the list; and the palette of a row that cannot be picked. */
#define CLOCK_SETTER_TILE_BLANK 0x3074
#define CLOCK_SETTER_TILE_BORDER 0x3079
#define CLOCK_SETTER_TILE_OUTSIDE 0x10
#define CLOCK_SETTER_PAL_ROW_DISABLED 6

/* The list's labels: a row's value from character 0x80 of the list layer, 16 a row. */
#define CLOCK_SETTER_CHAR_ROWS 0x80

/* The sounds. */
#define CLOCK_SETTER_SE_FAST_STEP 0xb
#define CLOCK_SETTER_SE_OPEN 0x13
#define CLOCK_SETTER_SE_CLOSE 0x14
#define CLOCK_SETTER_SE_PICK 0x29
#define CLOCK_SETTER_SE_CANCEL 0x2a
#define CLOCK_SETTER_SOUND_SPIN 0x54

/* The hit tests on the list (ClockSetter_TouchRow). */
#define CLOCK_SETTER_ROW_MISS 0
#define CLOCK_SETTER_ROW_HIT 1
#define CLOCK_SETTER_ROW_NONE 2

#define CLOCK_SETTER_MINUTES_PER_DAY 1440
#define CLOCK_SETTER_YEAR_BASE 2000

/* Held key steps before a held key scrolls a row each frame. */
#define CLOCK_SETTER_FAST_RUN 6

static PushButton *list_thumb(ClockSetter *self)
{
    return &self->thumb;
}

static DualCellSprite *list_thumb_sprite(ClockSetter *self)
{
    return (DualCellSprite *) (void *) &self->thumb;
}

/* The ROM's signed division (_s32_div_f): a divisor of 0 gives the numerator back, and
 * INT32_MIN / -1 gives INT32_MIN. */
static int list_div(int numerator, int divisor)
{
    if (divisor == 0) {
        return numerator;
    }
    if (divisor == -1) {
        return (int) (0u - (u32) numerator);
    }
    return numerator / divisor;
}

static int list_shl(int value, int shift)
{
    return (int) ((u32) value << shift);
}

/* Row `row` (0-31) of a screen map. */
static u16 *list_map_row(u16 *map, int row)
{
    return map + row * 32;
}

/* func_ov134_022996b4: unless the list waits for its screen, the scroll still to do is done up
 * to 8 pixels at a time; the list and the thumb follow. */
void ClockSetter_StepScroll(ClockSetter *self)
{
    if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_LIST_DIRTY)) {
        return;
    }
    int scroll = self->scroll;
    int pending = self->scroll_pending;
    if (pending > 0) {
        if (pending < 8) {
            scroll += pending;
            self->scroll_pending = 0;
        } else {
            scroll += 8;
            self->scroll_pending = pending - 8;
        }
    } else if (pending < 0) {
        if (pending > -8) {
            scroll += pending;
            self->scroll_pending = 0;
        } else {
            scroll -= 8;
            self->scroll_pending = pending + 8;
        }
    }
    if (scroll != self->scroll) {
        ClockSetter_SetScroll(self, scroll);
        ClockSetter_ThumbFromScroll(self);
    }
}
CLEAN_AS(func_ov134_022996b4, ClockSetter_StepScroll)

/* func_ov134_02299710: the row at screen y `y`, within the list's rows.
 * REQUIRES: the list has a row (else -1). */
int ClockSetter_RowAt(ClockSetter *self, int y)
{
    y -= self->list_top - self->scroll;
    if (y < 0) {
        y = 0;
    }
    y >>= 4;
    if (y >= self->list_rows) {
        y = self->list_rows - 1;
    }
    return y;
}
CLEAN_AS(func_ov134_02299710, ClockSetter_RowAt)

/* func_ov134_02299734: the cursor one row down, if there is one; the list scrolls to keep it
 * above y 0xa0. */
int ClockSetter_CursorDown(ClockSetter *self)
{
    if ((int) self->cursor < (int) self->list_rows) {
        self->cursor++;
        int y = ClockSetter_CursorY(self);
        if (y > 0xa0) {
            self->scroll_pending += y - 0xa0;
        }
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov134_02299734, ClockSetter_CursorDown)

/* func_ov134_02299774: the cursor one row up, if it is below the first; the list scrolls to
 * keep it below y 0x30. */
int ClockSetter_CursorUp(ClockSetter *self)
{
    if (self->cursor > 1) {
        self->cursor--;
        int y = ClockSetter_CursorY(self);
        if (y < 0x30) {
            self->scroll_pending -= 0x30 - y;
        }
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov134_02299774, ClockSetter_CursorUp)

/* func_ov134_022997b0: the cursor's row picked, unless it cannot be. */
int ClockSetter_PickCursorRow(ClockSetter *self)
{
    int row = self->cursor - 1;
    if (ClockSetter_RowDisabled(self, row)) {
        return 0;
    }
    self->list_pick = (u8) row;
    return 1;
}
CLEAN_AS(func_ov134_022997b0, ClockSetter_PickCursorRow)

/* One step of a held run (ClockSetter_ListKeys): the scroll still to do done at once, and the
 * fast step's sound every second step. */
static int list_fast_step(ClockSetter *self)
{
    if (self->scroll_pending != 0) {
        ClockSetter_SetScroll(self, self->scroll + self->scroll_pending);
        self->scroll_pending = 0;
        ClockSetter_ThumbFromScroll(self);
    }
    if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_FAST_TICK)) {
        ClockSetter_ClearFlags(self, CLOCK_SETTER_FLAG_FAST_TICK);
        SoundSys_PlaySe(CLOCK_SETTER_SE_FAST_STEP);
    } else {
        ClockSetter_SetFlags(self, CLOCK_SETTER_FLAG_FAST_TICK);
    }
    return CLOCK_SETTER_KEYS_FAST;
}

/* func_ov134_022997dc: the d-pad keys `keys` (ov002/key_repeat.h) on the open list. On the
 * thumb, left moves the cursor onto the row at the thumb's height; on the rows, right moves it
 * back. Up and down step the cursor a row and count the run (`key_run`); after six steps one
 * way, while the pad holds that way, the cursor steps each call with the scroll done at once
 * (and the run ends when the pad lets go). */
int ClockSetter_ListKeys(ClockSetter *self, int keys)
{
    if (self->cursor == 0) {
        self->key_run = 0;
        if (KeyRepeat_HasLeft(keys) == 0) {
            return CLOCK_SETTER_KEYS_NONE;
        }
        self->cursor = 1;
        ClockSetter_CursorToY(self, PushButton_FaceY(list_thumb(self)));
        return CLOCK_SETTER_KEYS_SWITCHED;
    }
    if (KeyRepeat_HasRight(keys)) {
        self->cursor = 0;
        self->key_run = 0;
        return CLOCK_SETTER_KEYS_SWITCHED;
    }
    if (self->key_run >= CLOCK_SETTER_FAST_RUN) {
        if ((data_021fbe40.held & CLOCK_SETTER_PAD_UP) == 0) {
            self->key_run = 0;
        } else if (ClockSetter_CursorUp(self)) {
            return list_fast_step(self);
        }
    } else if (self->key_run <= -CLOCK_SETTER_FAST_RUN) {
        if ((data_021fbe40.held & CLOCK_SETTER_PAD_DOWN) == 0) {
            self->key_run = 0;
        } else if (ClockSetter_CursorDown(self)) {
            return list_fast_step(self);
        }
    }
    if (KeyRepeat_HasUp(keys)) {
        if (self->key_run < 0) {
            self->key_run = 1;
        } else {
            self->key_run = (s8) (self->key_run + 1);
        }
        if (ClockSetter_CursorUp(self)) {
            return CLOCK_SETTER_KEYS_STEPPED;
        }
    } else if (KeyRepeat_HasDown(keys)) {
        if (self->key_run > 0) {
            self->key_run = -1;
        } else {
            self->key_run = (s8) (self->key_run - 1);
        }
        if (ClockSetter_CursorDown(self)) {
            return CLOCK_SETTER_KEYS_STEPPED;
        }
    }
    return CLOCK_SETTER_KEYS_NONE;
}
CLEAN_AS(func_ov134_022997dc, ClockSetter_ListKeys)

/* func_ov134_02299980: on the rows, the cursor moved to the row at screen y `y` (kept within
 * the list's window). */
void ClockSetter_CursorToY(ClockSetter *self, int y)
{
    if (self->cursor == 0) {
        return;
    }
    if (y < CLOCK_SETTER_LIST_TOP) {
        y = CLOCK_SETTER_LIST_TOP;
    } else if (y > CLOCK_SETTER_LIST_BOTTOM) {
        y = CLOCK_SETTER_LIST_BOTTOM;
    }
    self->cursor = (u8) (ClockSetter_RowAt(self, y) + 1);
}
CLEAN_AS(func_ov134_02299980, ClockSetter_CursorToY)

/* func_ov134_022999ac: the cursor's screen y: the thumb's face, or the middle of its row once
 * the scroll still to do is done. */
int ClockSetter_CursorY(ClockSetter *self)
{
    if (self->cursor == 0) {
        return PushButton_FaceY(list_thumb(self));
    }
    return self->list_top + list_shl(self->cursor - 1, 4) - self->scroll + 8 - self->scroll_pending;
}
CLEAN_AS(func_ov134_022999ac, ClockSetter_CursorY)

/* func_ov134_022999e0: the cursor's screen x: the thumb's face, or the bar's x. */
int ClockSetter_CursorX(ClockSetter *self)
{
    if (self->cursor == 0) {
        return PushButton_FaceX(list_thumb(self));
    }
    return self->bar_x;
}
CLEAN_AS(func_ov134_022999e0, ClockSetter_CursorX)

/* func_ov134_02299a00: the thumb drawn at (bar_x, thumb_y), from the frame's middle. */
void ClockSetter_PlaceThumb(ClockSetter *self)
{
    DualCellSprite_SetOffset(list_thumb_sprite(self), self->bar_x - 0x78, self->thumb_y - 0x60);
}
CLEAN_AS(func_ov134_02299a00, ClockSetter_PlaceThumb)

/* func_ov134_02299a14: the list scrolled to where the thumb is on the bar, at once. */
int ClockSetter_ScrollFromThumb(ClockSetter *self)
{
    ClockSetter_SetScroll(self, self->scroll_max * (self->thumb_y - CLOCK_SETTER_THUMB_TOP) / CLOCK_SETTER_THUMB_RANGE);
    self->scroll_pending = 0;
    return 0;
}
CLEAN_AS(func_ov134_02299a14, ClockSetter_ScrollFromThumb)

/* func_ov134_02299a3c: the thumb moved to where the scroll is. */
void ClockSetter_ThumbFromScroll(ClockSetter *self)
{
    self->thumb_y = list_div(list_shl(self->scroll, 7), self->scroll_max) + CLOCK_SETTER_THUMB_TOP;
    ClockSetter_PlaceThumb(self);
}
CLEAN_AS(func_ov134_02299a3c, ClockSetter_ThumbFromScroll)

/* func_ov134_02299a60: once the thumb's animation has ended, the thumb back at rest. */
int ClockSetter_SettleThumb(ClockSetter *self)
{
    if (DualCellSprite_IsDone(list_thumb_sprite(self))) {
        PushButton_ShowUp(list_thumb(self));
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov134_02299a60, ClockSetter_SettleThumb)

/* func_ov134_02299a84 */
int ClockSetter_ReleaseThumb(ClockSetter *self)
{
    return PushButton_Release(list_thumb(self));
}
CLEAN_AS(func_ov134_02299a84, ClockSetter_ReleaseThumb)

/* func_ov134_02299a90: the thumb moved 4 pixels up or down while the pad holds up or down (the
 * scene calls it while A is held); the list follows. */
void ClockSetter_MoveThumbByKeys(ClockSetter *self)
{
    int before = self->thumb_y;
    u16 held = data_021fbe40.held;
    if (held & CLOCK_SETTER_PAD_UP) {
        self->thumb_y = before - CLOCK_SETTER_THUMB_KEY_STEP;
        if (self->thumb_y < CLOCK_SETTER_THUMB_TOP) {
            self->thumb_y = CLOCK_SETTER_THUMB_TOP;
        }
    } else if (held & CLOCK_SETTER_PAD_DOWN) {
        self->thumb_y = before + CLOCK_SETTER_THUMB_KEY_STEP;
        if (self->thumb_y > CLOCK_SETTER_THUMB_BOTTOM) {
            self->thumb_y = CLOCK_SETTER_THUMB_BOTTOM;
        }
    }
    if (before != self->thumb_y) {
        ClockSetter_ScrollFromThumb(self);
        ClockSetter_PlaceThumb(self);
        PushButton_ScrollCue(list_thumb(self));
    }
}
CLEAN_AS(func_ov134_02299a90, ClockSetter_MoveThumbByKeys)

/* func_ov134_02299af0: the thumb moved up to 8 pixels toward the pen at `pen_y` (the bar was
 * touched off the thumb). */
void ClockSetter_ThumbTowardPen(ClockSetter *self, int pen_y)
{
    int target = pen_y - 8;
    if (target < CLOCK_SETTER_THUMB_TOP) {
        target = CLOCK_SETTER_THUMB_TOP;
    }
    if (target > CLOCK_SETTER_THUMB_BOTTOM) {
        target = CLOCK_SETTER_THUMB_BOTTOM;
    }
    Approach_S32Again(&self->thumb_y, target, 8);
    ClockSetter_ThumbMoved(self);
}
CLEAN_AS(func_ov134_02299af0, ClockSetter_ThumbTowardPen)

/* func_ov134_02299b18: the held thumb kept at the pen at `pen_y`. */
void ClockSetter_DragThumb(ClockSetter *self, int pen_y)
{
    self->thumb_y = pen_y + self->grab_dy;
    if (self->thumb_y < CLOCK_SETTER_THUMB_TOP) {
        self->thumb_y = CLOCK_SETTER_THUMB_TOP;
    }
    if (self->thumb_y > CLOCK_SETTER_THUMB_BOTTOM) {
        self->thumb_y = CLOCK_SETTER_THUMB_BOTTOM;
    }
    ClockSetter_ThumbMoved(self);
}
CLEAN_AS(func_ov134_02299b18, ClockSetter_DragThumb)

/* func_ov134_02299b3c: the list scrolled to the moved thumb, and the thumb's scroll sound
 * once it has gone 4 pixels from where it last played. */
void ClockSetter_ThumbMoved(ClockSetter *self)
{
    ClockSetter_ScrollFromThumb(self);
    ClockSetter_PlaceThumb(self);
    int moved = self->cue_y - self->thumb_y;
    if (moved >= 4 || moved <= -4) {
        PushButton_ScrollCue(list_thumb(self));
        self->cue_y = self->thumb_y;
    }
}
CLEAN_AS(func_ov134_02299b3c, ClockSetter_ThumbMoved)

/* func_ov134_02299b70: with the cursor on the thumb, the thumb pressed (A). */
int ClockSetter_PressThumbByKey(ClockSetter *self)
{
    if (self->cursor == 0) {
        PushButton_Press(list_thumb(self));
        PushButton_PressCue(list_thumb(self));
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov134_02299b70, ClockSetter_PressThumbByKey)

/* func_ov134_02299b98: the thumb grabbed if the pen at (x, y) is on it. */
int ClockSetter_GrabThumb(ClockSetter *self, int x, int y)
{
    if (PushButton_Contains(list_thumb(self), x, y)) {
        self->grab_dy = self->thumb_y - y;
        PushButton_Press(list_thumb(self));
        self->cue_y = self->thumb_y;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov134_02299b98, ClockSetter_GrabThumb)

/* func_ov134_02299bcc: whether row `row` of the open list cannot be picked. In mode 1 the
 * hours outside min_hour-max_hour (which may wrap past midnight) cannot; otherwise the rows
 * that would take the value before `min` or after `max`, when they bound it. */
int ClockSetter_RowDisabled(ClockSetter *self, int row)
{
    switch (self->list_field) {
        case CLOCK_SETTER_MONTH:
        case CLOCK_SETTER_DAY:
            row++;
            break;
    }
    if (self->mode == CLOCK_SETTER_MODE_TIME && self->list_field == CLOCK_SETTER_HOUR) {
        int last = self->max_hour;
        int first = self->min_hour;
        if ((unsigned int) first < (unsigned int) last) {
            if (row < first || row > last) {
                return 1;
            }
        } else {
            if (row < first && row > last) {
                return 1;
            }
        }
        return 0;
    }
    if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_HAS_MIN)) {
        if (ClockSetter_BelowMin(self, row, self->list_field)) {
            return 1;
        }
    }
    if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_HAS_MAX)) {
        return ClockSetter_AboveMax(self, row, self->list_field);
    }
    return 0;
}
CLEAN_AS(func_ov134_02299bcc, ClockSetter_RowDisabled)

/* func_ov134_02299c60: whether the value with `value` in field `field` is before `min`: the
 * fields above it equal min's and `value` is below min's. */
int ClockSetter_BelowMin(ClockSetter *self, int value, unsigned int field)
{
    for (u8 i = 0; i < field; i++) {
        int mine = ClockSetter_Field(self, i);
        if (mine != ClockSetter_FieldOf(self, i, &self->min)) {
            return 0;
        }
    }
    return value < ClockSetter_FieldOf(self, field, &self->min);
}
CLEAN_AS(func_ov134_02299c60, ClockSetter_BelowMin)

/* func_ov134_02299cb8: whether the value with `value` in field `field` is after `max`. */
int ClockSetter_AboveMax(ClockSetter *self, int value, unsigned int field)
{
    for (u8 i = 0; i < field; i++) {
        int mine = ClockSetter_Field(self, i);
        if (mine != ClockSetter_FieldOf(self, i, &self->max)) {
            return 0;
        }
    }
    return value > ClockSetter_FieldOf(self, field, &self->max);
}
CLEAN_AS(func_ov134_02299cb8, ClockSetter_AboveMax)

/* func_ov134_02299d10: the picked row written into the list's field. The day is cut to the
 * month's length; a date field recolours the weekday. In mode 1 an hour that crosses min_hour
 * moves the date a day (back when it comes up to min_hour from below, on when it goes below).
 * Then the value is kept within `min` and `max` when they bound it, and the labels of what
 * changed are drawn again. For the hour or the minute the answer is whether it changed, with
 * the hands' target set to the new time (a day either way when the date moved). */
int ClockSetter_CommitPick(ClockSetter *self)
{
    u16 changed = 0;
    unsigned int before = (unsigned int) ClockSetter_Field(self, self->list_field);
    ClockSetter_SetField(self, self->list_field, self->list_pick);
    changed = (u16) (changed | (1 << self->list_field));

    int days = Calendar_DaysInMonth(self->value.year, self->value.month);
    if (days < (int) self->value.day) {
        self->value.day = (u8) days;
        changed = (u16) (changed | (1 << CLOCK_SETTER_DAY));
    }
    if (self->list_field <= CLOCK_SETTER_DAY) {
        ClockSetter_ColorField(self, CLOCK_SETTER_WEEKDAY, CLOCK_SETTER_PAL_NORMAL);
        changed = (u16) (changed | (1 << CLOCK_SETTER_WEEKDAY));
    }

    int day_shift = 0;
    if (self->list_field == CLOCK_SETTER_HOUR && self->mode == CLOCK_SETTER_MODE_TIME) {
        u8 first = self->min_hour;
        if (before < first) {
            if (self->list_pick >= first) {
                DateTime_SubtractDays(&self->value, 1);
                day_shift = -1;
            }
        } else {
            if (self->list_pick < first) {
                DateTime_AddDays(&self->value, 1);
                day_shift = 1;
            }
        }
        if (day_shift != 0) {
            changed = (u16) (changed | 0x27); /* the year, month, day and weekday */
        }
    }

    if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_HAS_MIN)) {
        if (DateTime_Compare(&self->min, &self->value, 0x3f) == 1) {
            MI_CpuCopy8(&self->min, &self->value, sizeof self->value);
            changed = 0xffff;
        }
    }
    if (ClockSetter_TestFlags(self, CLOCK_SETTER_FLAG_HAS_MAX)) {
        if (DateTime_Compare(&self->max, &self->value, 0x3f) == -1) {
            MI_CpuCopy8(&self->max, &self->value, sizeof self->value);
            changed = 0xffff;
        }
    }
    for (u8 field = 0; field < CLOCK_SETTER_FIELDS; field++) {
        if (changed & (1 << field)) {
            ClockSetter_DrawField(self, field);
        }
    }

    if (self->list_field == CLOCK_SETTER_HOUR || self->list_field == CLOCK_SETTER_MINUTE) {
        if (before == self->list_pick) {
            return 0;
        }
        int minute = ClockSetter_Field(self, CLOCK_SETTER_MINUTE);
        int hour = ClockSetter_Field(self, CLOCK_SETTER_HOUR);
        self->target_minutes = minute + hour * 60;
        self->target_minutes += day_shift * CLOCK_SETTER_MINUTES_PER_DAY;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov134_02299d10, ClockSetter_CommitPick)

/* func_ov134_02299ecc: the list's window halfway closer to the field's middle (at once when
 * `fade` is 0), and the marker kept inside it. */
void ClockSetter_CloseWindowStep(ClockSetter *self)
{
    if (self->fade != 0) {
        self->window_top = (u8) ((self->field_y - 8 + self->window_top) >> 1);
        self->window_bottom = (u8) ((self->field_y + 8 + self->window_bottom) >> 1);
    } else {
        self->window_top = (u8) (self->field_y - 8);
        self->window_bottom = (u8) (self->field_y + 8);
    }
    DisplayShadow_SetWindow(2, 0, self->window_top, 0xff, self->window_bottom);
    if (self->marker_y < self->window_top) {
        self->marker_y = self->window_top;
    }
    if (self->marker_y > self->window_bottom - 8) {
        self->marker_y = self->window_bottom - 8;
    }
}
CLEAN_AS(func_ov134_02299ecc, ClockSetter_CloseWindowStep)

/* func_ov134_02299f74: the list's window halfway closer to the whole list (at once when `fade`
 * is 0). */
void ClockSetter_OpenWindowStep(ClockSetter *self)
{
    if (self->fade != 0) {
        self->window_top = (u8) ((self->window_top + CLOCK_SETTER_LIST_TOP) >> 1);
        self->window_bottom = (u8) ((self->window_bottom + CLOCK_SETTER_LIST_BOTTOM) >> 1);
    } else {
        self->window_top = CLOCK_SETTER_LIST_TOP;
        self->window_bottom = CLOCK_SETTER_LIST_BOTTOM;
    }
    DisplayShadow_SetWindow(2, 0, self->window_top, 0xff, self->window_bottom);
}
CLEAN_AS(func_ov134_02299f74, ClockSetter_OpenWindowStep)

/* Columns `first`-7 of `count` screen rows from `row` (wrapping past row 31) blanked. */
static void list_blank_rows(ClockSetter *self, int row, int count, int first)
{
    for (int i = 0; i < count; i++) {
        u16 *entries = list_map_row(self->list_map_shown, row);
        for (int column = first; column < 8; column++) {
            entries[column] = CLOCK_SETTER_TILE_BLANK;
        }
        row = (row + 1) & 0x1f;
    }
}

/* The edge rows at screen row `row` (columns 0-9 and 31 left outside the list), `count` of them
 * going by `step`. */
static void list_edge_rows(ClockSetter *self, int row, int count, int step)
{
    for (int i = 0; i < count; i++) {
        u16 *entries = list_map_row(self->list_map_shown, row);
        for (int column = 0; column < 10; column++) {
            entries[column] = CLOCK_SETTER_TILE_OUTSIDE;
        }
        entries[31] = CLOCK_SETTER_TILE_OUTSIDE;
        row = (row + step) & 0x1f;
    }
}

/* func_ov134_02299fd0: the list's screen drawn for the scroll: list_map copied, the space above
 * the first row and below the last blanked, the rows that cannot be picked dimmed, the labels
 * of the rows whose value changed drawn, and the edges above y 0x28 and from y 0xa8 cleared.
 * The list layer scrolls by `scroll`, so its 32 screen rows wrap: list row t is at screen rows
 * 2t and 2t+1 (mod 32).
 * QUIRK: the field's width is asked for twice.
 * REQUIRES: 0 <= scroll (as ClockSetter_OpenList keeps it), so the rows above the list are
 * within the screen. */
void ClockSetter_RedrawList(ClockSetter *self)
{
    MIi_CpuCopy16(self->list_map, self->list_map_shown, sizeof self->list_map_shown);
    int above = self->list_top - self->scroll;
    ClockSetter_FieldWidth(self, self->list_field);
    int first = 8 - ClockSetter_FieldWidth(self, self->list_field);
    if (above > 0) {
        above += 0xf;
        int row = (0x10 - (above >> 4)) * 2;
        list_blank_rows(self, row, 0x20 - row, first);
    }

    int top_row = (self->scroll - self->list_top) >> 4;
    for (int i = 0; i < CLOCK_SETTER_ROWS_SHOWN; i++) {
        int row = i + top_row;
        int slot = row & 0xf;
        if (row < 0 || row >= self->list_rows) {
            continue;
        }
        if (ClockSetter_RowDisabled(self, row)) {
            ScreenMap_SetPalette(self->list_map_shown, first, slot * 2, 7, slot * 2 + 1, CLOCK_SETTER_PAL_ROW_DISABLED);
        }
        if (row != self->row_values[slot]) {
            self->row_values[slot] = (u8) row;
            int number = row;
            if (self->list_field == CLOCK_SETTER_YEAR) {
                number += CLOCK_SETTER_YEAR_BASE;
            }
            if ((u8) (self->list_field - 1) <= 1) { /* the month or the day count from 1 */
                number++;
            }
            ClockSetter_DrawNumber(self, self->list_layer, (slot << 4) + CLOCK_SETTER_CHAR_ROWS, 8, number, 15, 14);
        }
    }

    int rows = self->list_rows;
    int end = self->list_top - self->scroll + rows * CLOCK_SETTER_ROW_HEIGHT;
    if (end < 0xc0) {
        list_blank_rows(self, (rows * 2) & 0x1f, ((0xcf - end) >> 4) * 2, first);
    }
    list_edge_rows(self, (((self->scroll - self->list_top) + 0x20) & 0xff) >> 3, 5, -1);
    list_edge_rows(self, (((self->scroll - self->list_top) + 0xb0) & 0xff) >> 3, 3, 1);
    ClockSetter_SetFlags(self, CLOCK_SETTER_FLAG_LIST_DIRTY);
}
CLEAN_AS(func_ov134_02299fd0, ClockSetter_RedrawList)

/* func_ov134_0229a1b4: the list layer scrolled so the list's first row is at list_top less the
 * scroll, and its column at the field's. */
void ClockSetter_ScrollLayer(ClockSetter *self)
{
    DisplayLayer_SetScroll(self->list_layer, -self->list_scroll_x, -(self->list_top - self->scroll));
}
CLEAN_AS(func_ov134_0229a1b4, ClockSetter_ScrollLayer)

/* func_ov134_0229a1d8 */
void ClockSetter_SetScroll(ClockSetter *self, int scroll)
{
    self->scroll = scroll;
    ClockSetter_ScrollLayer(self);
    ClockSetter_RedrawList(self);
}
CLEAN_AS(func_ov134_0229a1d8, ClockSetter_SetScroll)

/* func_ov134_0229a1f0: a touch at (x, y) while the list is open (ClockSetterTouch). A touch on
 * the bar's column (y 32-168) off the thumb presses the thumb. */
int ClockSetter_TouchList(ClockSetter *self, int x, int y)
{
    switch (ClockSetter_TouchRow(self, x, y)) {
        case CLOCK_SETTER_ROW_HIT:
            return CLOCK_SETTER_TOUCH_PICKED;
        case CLOCK_SETTER_ROW_NONE:
            return CLOCK_SETTER_TOUCH_NONE;
        default:
            break;
    }
    if (ClockSetter_GrabThumb(self, x, y)) {
        return CLOCK_SETTER_TOUCH_THUMB;
    }
    if (y >= 32 && y <= 168) {
        if (x <= self->bar_x + 24 && x >= self->bar_x) {
            PushButton_Press(list_thumb(self));
            return CLOCK_SETTER_TOUCH_BAR;
        }
    }
    return CLOCK_SETTER_TOUCH_OUTSIDE;
}
CLEAN_AS(func_ov134_0229a1f0, ClockSetter_TouchList)

/* func_ov134_0229a24c: a step of the list's closing (after ClockSetter_PickRow or
 * ClockSetter_CancelList); 1 once it is done. The marker of a picked row is chosen, the colour
 * fades out, the window closes onto the field, then the list layer is hidden, the field's
 * button coloured back, and a pick is written (ClockSetter_CommitPick): when the hour or minute
 * changed the hands spin to it with their sound, and the focus moves to the next field. */
int ClockSetter_CloseListStep(ClockSetter *self)
{
    switch (self->list_state) {
        case CLOCK_SETTER_LIST_PICKED:
            self->list_state = CLOCK_SETTER_LIST_FADE_OUT;
            if (self->list_field == CLOCK_SETTER_YEAR) {
                self->marker_cell = data_ov134_0229c04c;
            } else {
                self->marker_cell = data_ov134_0229c03c;
            }
            break;
        case CLOCK_SETTER_LIST_CANCELLED:
            self->list_state = CLOCK_SETTER_LIST_FADE_OUT;
            break;
        case CLOCK_SETTER_LIST_FADE_OUT:
            if (self->fade != 0) {
                self->fade--;
                ClockSetter_FadeListColor(self, self->fade);
            } else {
                SoundSys_PlaySe(CLOCK_SETTER_SE_CLOSE);
                self->list_state = CLOCK_SETTER_LIST_SHRINK;
                self->fade = 3;
                DisplayShadow_EnableSubWindows(1);
                self->fade--;
                ClockSetter_CloseWindowStep(self);
            }
            break;
        case CLOCK_SETTER_LIST_SHRINK:
            if (self->fade != 0) {
                self->fade--;
                ClockSetter_CloseWindowStep(self);
            } else {
                DisplayLayer_Hide(self->list_layer);
                DisplayShadow_DisableSubWindows(1);
                ClockSetter_ColorFieldButton(self, self->list_field, CLOCK_SETTER_PAL_NORMAL);
                self->top_cell = NULL;
                self->bottom_cell = NULL;
                if (self->marker_cell != NULL) {
                    if (ClockSetter_CommitPick(self)) {
                        self->list_state = CLOCK_SETTER_LIST_SPIN;
                        SoundSys_StartOnHandle38(CLOCK_SETTER_SOUND_SPIN);
                    } else {
                        self->list_state = CLOCK_SETTER_LIST_DONE;
                    }
                    self->marker_cell = NULL;
                    ClockSetter_FocusNext(self);
                } else {
                    self->list_state = CLOCK_SETTER_LIST_DONE;
                }
            }
            break;
        case CLOCK_SETTER_LIST_SPIN:
            if (ClockSetter_SpinHands(self)) {
                ClockSetter_HandsFromValue(self);
                self->list_state = CLOCK_SETTER_LIST_DONE;
            }
            break;
        case CLOCK_SETTER_LIST_DONE:
            return 1;
        default:
            break;
    }
    return 0;
}
CLEAN_AS(func_ov134_0229a24c, ClockSetter_CloseListStep)

/* The list's window for its opening and closing: sub window 0 shows every plane, outside it
 * every plane but the list layer. */
static void list_window_planes(ClockSetter *self)
{
    DisplayShadow_DisableSubWindows(1);
    DisplayShadow_SetSubWindow0Planes(0x1f, 1);
    DisplayShadow_SetSubOutsidePlanes((u8) (~DisplayLayer_PlaneMaskInt(self->list_layer) & 0x1f));
}

/* func_ov134_0229a398: the list closed without a pick (B, or a touch away from it). */
void ClockSetter_CancelList(ClockSetter *self)
{
    SoundSys_PlaySe(CLOCK_SETTER_SE_CANCEL);
    self->list_state = CLOCK_SETTER_LIST_CANCELLED;
    self->fade = 3;
    list_window_planes(self);
    ClockSetter_ClearFlags(self, CLOCK_SETTER_FLAG_THUMB_SHOWN);
}
CLEAN_AS(func_ov134_0229a398, ClockSetter_CancelList)

/* func_ov134_0229a3e4: the list closed on the picked row (`list_pick`), whose value is drawn
 * as the marker at its row. */
void ClockSetter_PickRow(ClockSetter *self)
{
    SoundSys_PlaySe(CLOCK_SETTER_SE_PICK);
    self->list_state = CLOCK_SETTER_LIST_PICKED;
    self->fade = 3;
    list_window_planes(self);
    ClockSetter_DrawPickLabel(self);
    self->marker_y = self->list_top + list_shl(self->list_pick, 4) - self->scroll;
    ClockSetter_ClearFlags(self, CLOCK_SETTER_FLAG_THUMB_SHOWN);
}
CLEAN_AS(func_ov134_0229a3e4, ClockSetter_PickRow)

/* func_ov134_0229a44c: a touch at (x, y) against the list's rows: CLOCK_SETTER_ROW_MISS off the
 * list (or above y 0x28 or below 0xa8), CLOCK_SETTER_ROW_NONE on a part row at the window's
 * edges, past the last row or on a row that cannot be picked, else CLOCK_SETTER_ROW_HIT with the
 * row in `list_pick`. */
int ClockSetter_TouchRow(ClockSetter *self, int x, int y)
{
    if (y <= CLOCK_SETTER_LIST_TOP || y >= CLOCK_SETTER_LIST_BOTTOM) {
        return CLOCK_SETTER_ROW_MISS;
    }
    int column = x >> 3;
    if (ClockSetter_FieldLeft(self, self->list_field) > column || ClockSetter_FieldRight(self, self->list_field) < column) {
        return CLOCK_SETTER_ROW_MISS;
    }
    int part = self->scroll & 0xf;
    if (y >= 0xb2 - part) {
        return CLOCK_SETTER_ROW_NONE;
    }
    if (y <= ((0x10 - part) & 0xf) + 0x1e) {
        return CLOCK_SETTER_ROW_NONE;
    }
    int into = y - (self->list_top - self->scroll);
    if (into < 0) {
        return CLOCK_SETTER_ROW_NONE;
    }
    int row = into >> 4;
    if (row >= self->list_rows) {
        return CLOCK_SETTER_ROW_NONE;
    }
    if (ClockSetter_RowDisabled(self, row)) {
        return CLOCK_SETTER_ROW_NONE;
    }
    self->list_pick = (u8) row;
    return CLOCK_SETTER_ROW_HIT;
}
CLEAN_AS(func_ov134_0229a44c, ClockSetter_TouchRow)

/* func_ov134_0229a4e4: a step of the list's opening (after ClockSetter_OpenList); 1 once it is
 * open. The list layer is shown in a window that grows to the whole list; then the thumb is
 * shown on the bar right of the field and the colour fades in. */
int ClockSetter_OpenListStep(ClockSetter *self)
{
    switch (self->list_state) {
        case CLOCK_SETTER_LIST_SHOW:
            self->list_state = CLOCK_SETTER_LIST_GROW;
            DisplayLayer_Show(self->list_layer);
            DisplayShadow_EnableSubWindows(1);
            self->fade--;
            ClockSetter_OpenWindowStep(self);
            break;
        case CLOCK_SETTER_LIST_GROW:
            if (self->fade != 0) {
                self->fade--;
                ClockSetter_OpenWindowStep(self);
            } else {
                DisplayShadow_DisableSubWindows(1);
                self->list_state = CLOCK_SETTER_LIST_FADE_IN;
                self->fade = 0;
                ClockSetter_SetFlags(self, CLOCK_SETTER_FLAG_THUMB_SHOWN);
                self->bar_x = list_shl(ClockSetter_FieldRight(self, self->list_field), 3);
                ClockSetter_PlaceThumb(self);
            }
            break;
        case CLOCK_SETTER_LIST_FADE_IN:
            if (self->fade < 3) {
                self->fade++;
                ClockSetter_FadeListColor(self, self->fade);
            } else {
                self->list_state = CLOCK_SETTER_LIST_DONE;
            }
            break;
        case CLOCK_SETTER_LIST_PICKED:
        case CLOCK_SETTER_LIST_CANCELLED:
        case CLOCK_SETTER_LIST_FADE_OUT:
        case CLOCK_SETTER_LIST_SHRINK:
        case CLOCK_SETTER_LIST_SPIN:
            break;
        case CLOCK_SETTER_LIST_DONE:
            return 1;
    }
    return 0;
}
CLEAN_AS(func_ov134_0229a4e4, ClockSetter_OpenListStep)

/* func_ov134_0229a5c8: the list of field `field` opened (hidden until ClockSetter_OpenListStep
 * shows it): its screen fitted to the field's width (the columns left of it outside, a border
 * on the last of them), its rows (the month's length for the day), scrolled to put the value's
 * row at the field, the cursor on that row, the field's button and focus, the list's title,
 * edges and the window round the field, and the colour faded out. */
void ClockSetter_OpenList(ClockSetter *self, int field)
{
    SoundSys_PlaySe(CLOCK_SETTER_SE_OPEN);
    self->list_field = (u8) field;
    self->list_state = CLOCK_SETTER_LIST_SHOW;
    DisplayLayer_Hide(self->list_layer);
    self->list_col = (u8) ClockSetter_FieldLeft(self, field);
    self->list_row = (u8) ClockSetter_FieldTop(self, field);
    MIi_CpuCopy16(self->list_base, self->list_map, sizeof self->list_map);
    int width = ClockSetter_FieldWidth(self, field);
    int outside = 8 - width;
    for (int row = 0; row < 0x20; row++) {
        u16 *entries = list_map_row(self->list_map, row);
        for (int column = 0; column < outside; column++) {
            entries[column] = CLOCK_SETTER_TILE_OUTSIDE;
        }
        entries[(outside - 1) & 0x1f] = CLOCK_SETTER_TILE_BORDER;
    }
    self->list_scroll_x = (u8) list_shl(self->list_col - outside, 3);
    self->list_top = CLOCK_SETTER_LIST_TOP;
    self->list_rows = data_ov134_0229bf64[field];
    if (field == CLOCK_SETTER_DAY) {
        self->list_rows = Calendar_DaysInMonth(self->value.year, self->value.month);
    }
    self->scroll_max = list_shl(self->list_rows - CLOCK_SETTER_ROWS_VISIBLE, 4);
    for (int slot = 0; slot < CLOCK_SETTER_ROWS_SHOWN; slot++) {
        self->row_values[slot] = 0xff;
    }
    u8 row = (u8) ClockSetter_Field(self, self->list_field);
    if (self->list_field == CLOCK_SETTER_MONTH || self->list_field == CLOCK_SETTER_DAY) {
        row = (u8) (row - 1);
    }
    int scroll = list_shl(row, 4) - (list_shl(self->list_row, 3) - self->list_top);
    if (scroll < 0) {
        scroll = 0;
    } else if (scroll > self->scroll_max) {
        scroll = self->scroll_max;
    }
    ClockSetter_SetScroll(self, scroll);
    ClockSetter_ThumbFromScroll(self);
    ClockSetter_ColorFieldButton(self, field, CLOCK_SETTER_PAL_LIST);
    ClockSetter_SetFocus(self, (u8) field);
    self->list_x = list_shl(ClockSetter_FieldLeft(self, self->list_field), 3);
    self->field_y = (u8) list_shl(ClockSetter_FieldBottom(self, field), 3);
    self->window_top = (u8) (self->field_y - 8);
    self->window_bottom = (u8) (self->field_y + 8);
    ClockSetter_DrawTitle(self, LAYER_SUB_OBJ, 0x1aa, 8, data_ov134_0229bf5c[field], width + 1);
    ClockSetter_SetFlags(self, CLOCK_SETTER_FLAG_LIST_FRESH);
    if (field == CLOCK_SETTER_YEAR) {
        self->top_cell = data_ov134_0229c294;
        self->bottom_cell = data_ov134_0229c164;
    } else {
        self->top_cell = data_ov134_0229c2c4;
        self->bottom_cell = data_ov134_0229c11c;
    }
    self->fade = 3;
    list_window_planes(self);
    ClockSetter_FadeListColor(self, 0);
    self->cursor = (u8) (row + 1);
    self->scroll_pending = 0;
}
CLEAN_AS(func_ov134_0229a5c8, ClockSetter_OpenList)

/* func_ov134_0229a804: the focus moved to the next field the mode edits, or to none after the
 * last (the minute for modes 0 and 1, the day for modes 2 and 3). */
void ClockSetter_FocusNext(ClockSetter *self)
{
    switch (self->mode) {
        case CLOCK_SETTER_MODE_DATE_TIME:
        case CLOCK_SETTER_MODE_TIME:
            if (self->focus < 4u) {
                ClockSetter_SetFocus(self, (u8) (self->focus + 1));
            } else {
                ClockSetter_SetFocus(self, CLOCK_SETTER_NO_FIELD);
            }
            break;
        case CLOCK_SETTER_MODE_MONTH_DAY:
        case CLOCK_SETTER_MODE_DATE:
            if (self->focus < 2u) {
                ClockSetter_SetFocus(self, (u8) (self->focus + 1));
            } else {
                ClockSetter_SetFocus(self, CLOCK_SETTER_NO_FIELD);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov134_0229a804, ClockSetter_FocusNext)
