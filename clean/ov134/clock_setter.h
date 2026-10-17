/* The clock setter of overlay 134: the part of the clock screens (files menu/clock/...) that
 * overlays 135, 136, 137 and 138 each embed in their scene (at 0x2c8 or 0x2c4), the screens
 * overlay 92's dispatcher opens for GroupParams' modes 0x30-0x33 (ov092/menu_dispatch.c). It is
 * not a scene of its own: the embedding scene constructs it (ClockSetter_Construct), sets it up
 * (ClockSetter_Init with one of the ClockSetterMode), and runs its pieces from its own states.
 *
 * It shows a date and time (`value`) as up to five numbers on the sub screen (year, month, day,
 * hour, minute, and the weekday), each a field (ClockSetterField) of a layout chosen by the mode,
 * and for modes 0 and 1 an analog clock whose two hands can be dragged with the pen
 * (clock_setter_hands.c). Touching a field (or picking it with the keys) opens a list of its
 * values beside it (clock_setter_list.c): rows of 16 pixels on the list layer, scrolled by a
 * scroll bar whose thumb is a PushButton, and a cursor row for the keys. Picking a row writes
 * the value back (ClockSetter_CommitPick); for the hour or the minute the hands then spin to the
 * new time.
 *
 * In modes 0 and 1 `min` and `max` (now and twelve hours later) can bound the value
 * (CLOCK_SETTER_FLAG_HAS_MIN / HAS_MAX); overlay 136 (mode 1) sets both, overlay 135 (mode 0)
 * sets the minimum only, under a condition of its own (ClockSetter_UseMinimum). */
#ifndef CLEAN_OV134_CLOCK_SETTER_H
#define CLEAN_OV134_CLOCK_SETTER_H

#include "main/calendar.h"
#include "main/layer_load_task.h"
#include "main/oam_buffer.h"
#include "main/text_label.h"
#include "ov002/push_button.h"
#include "types.h"

/* The modes (ClockSetter_Init), each with its own layout of fields, background and title. */
enum ClockSetterMode {
    CLOCK_SETTER_MODE_DATE_TIME = 0, /* overlay 135: every field, from now, with the clock */
    CLOCK_SETTER_MODE_TIME = 1,      /* overlay 136: the hour and the minute, from now, bounded,
                                     * with the clock; the date fields are shown dimmed */
    CLOCK_SETTER_MODE_MONTH_DAY = 2, /* overlay 137: the month and the day, from 2001-01-01 */
    CLOCK_SETTER_MODE_DATE = 3       /* overlay 138: the date, from tomorrow (the hour and the
                                     * minute are kept but not drawn) */
};

/* The fields, in the order of DateTime's bytes from the year down. */
enum ClockSetterField {
    CLOCK_SETTER_YEAR = 0, /* years from 2000 */
    CLOCK_SETTER_MONTH = 1,
    CLOCK_SETTER_DAY = 2,
    CLOCK_SETTER_HOUR = 3,
    CLOCK_SETTER_MINUTE = 4,
    CLOCK_SETTER_WEEKDAY = 5, /* shown, never edited */
    CLOCK_SETTER_FIELDS = 6,
    CLOCK_SETTER_NO_FIELD = 6 /* `focus` when none has it, and the hit tests' miss */
};

/* In `flags`. */
enum ClockSetterFlag {
    CLOCK_SETTER_FLAG_LIST_DIRTY = 0x001,  /* list_map_shown changed: queued on the list layer */
    CLOCK_SETTER_FLAG_PANEL_DIRTY = 0x002, /* panel_map changed: queued on the panel layer */
    CLOCK_SETTER_FLAG_THUMB_SHOWN = 0x004, /* the list is open: its scroll thumb is drawn */
    CLOCK_SETTER_FLAG_SUNDAY = 0x008,      /* the weekday is Sunday (drawn in its own palette) */
    CLOCK_SETTER_FLAG_AT_MAX = 0x010,      /* a hand dragged past `max`: the value holds `max` */
    CLOCK_SETTER_FLAG_AT_MIN = 0x020,      /* ... before `min`: the value holds `min` */
    CLOCK_SETTER_FLAG_HAS_MAX = 0x040,     /* the value is bounded by `max` */
    CLOCK_SETTER_FLAG_HAS_MIN = 0x080,     /* ... by `min` */
    CLOCK_SETTER_FLAG_FAST_TICK = 0x100,   /* toggled at each fast step; the sound plays every
                                           * second step */
    CLOCK_SETTER_FLAG_LIST_FRESH = 0x200   /* the list was just opened: its top edge's shade is
                                           * left out of the next draw */
};

/* The steps of the list (`list_state`): opening, open, and closing. */
enum ClockSetterListState {
    CLOCK_SETTER_LIST_SHOW = 0,      /* ClockSetter_OpenListStep: the list layer is shown */
    CLOCK_SETTER_LIST_GROW = 1,      /* its window grows to the full list */
    CLOCK_SETTER_LIST_FADE_IN = 2,   /* its palette's last colour fades in */
    CLOCK_SETTER_LIST_PICKED = 3,    /* ClockSetter_PickRow: a row was picked */
    CLOCK_SETTER_LIST_CANCELLED = 4, /* ClockSetter_CancelList */
    CLOCK_SETTER_LIST_FADE_OUT = 5,  /* ClockSetter_CloseListStep: the colour fades out */
    CLOCK_SETTER_LIST_SHRINK = 6,    /* the window shrinks onto the field */
    CLOCK_SETTER_LIST_SPIN = 7,      /* the hands spin to the picked time */
    CLOCK_SETTER_LIST_DONE = 8
};

/* What ClockSetter_TouchList answers for a touch while the list is open. */
enum ClockSetterTouch {
    CLOCK_SETTER_TOUCH_PICKED = 0,  /* a row was touched: it is `list_pick` */
    CLOCK_SETTER_TOUCH_OUTSIDE = 1, /* away from the list and its bar */
    CLOCK_SETTER_TOUCH_BAR = 2,     /* on the bar off the thumb: the thumb is pressed */
    CLOCK_SETTER_TOUCH_THUMB = 3,   /* on the thumb: it is grabbed (ClockSetter_GrabThumb) */
    CLOCK_SETTER_TOUCH_NONE = 4     /* on the list but not on a row that can be picked */
};

/* What ClockSetter_ListKeys answers. */
enum ClockSetterKeys {
    CLOCK_SETTER_KEYS_NONE = 0,
    CLOCK_SETTER_KEYS_SWITCHED = 1, /* the cursor moved between the thumb and the rows */
    CLOCK_SETTER_KEYS_STEPPED = 2,  /* the cursor moved one row */
    CLOCK_SETTER_KEYS_FAST = 3      /* the cursor moved one row in a held run (ClockSetter_FastStep) */
};

/* The hand being dragged (`hand`). */
enum ClockSetterHand { CLOCK_SETTER_HAND_MINUTE = 0, CLOCK_SETTER_HAND_HOUR = 1 };

/* The palettes of the panel's screen entries (ClockSetter_ColorField): in the screen data. */
#define CLOCK_SETTER_PAL_NORMAL 3
#define CLOCK_SETTER_PAL_DIM 4       /* a field mode 1 does not edit */
#define CLOCK_SETTER_PAL_FOCUS 5     /* the focused field, or one that just changed */
#define CLOCK_SETTER_PAL_DIM_FOCUS 7 /* PAL_FOCUS on a field mode 1 does not edit */
#define CLOCK_SETTER_PAL_SUNDAY 8    /* the weekday on a Sunday */
#define CLOCK_SETTER_PAL_LIST 10     /* a field's button while its list is open */

#define CLOCK_SETTER_LABELS 17
#define CLOCK_SETTER_ROWS_SHOWN 16 /* `row_values`: the list's screen holds 16 rows of 16 pixels */
#define CLOCK_SETTER_MAP_ENTRIES 0x400

typedef struct ClockSetter {
    s32 scroll;                                   /* 0x000: the list's scroll, in pixels */
    s32 scroll_pending;                           /* 0x004: still to scroll, 8 pixels a frame */
    u8 row_values[CLOCK_SETTER_ROWS_SHOWN];       /* 0x008: the value each screen row's label shows (0xff:
                                             * none yet), so a label is drawn only when it changes */
    PushButton thumb;                             /* 0x018: the scroll bar's thumb */
    s32 bar_x;                                    /* 0x060: the scroll bar's x (the list's right edge) */
    int thumb_y;                                  /* 0x064: 0x20-0xa0 */
    s32 grab_dy;                                  /* 0x068: from the pen to the thumb while it is held */
    s32 cue_y;                                    /* 0x06c: thumb_y when the scroll sound last played */
    const OamEntry *marker_cell;                  /* 0x070: drawn at (list_x, marker_y) while closing */
    const OamEntry *top_cell;                     /* 0x074: the list's top edge, at window_top */
    const OamEntry *bottom_cell;                  /* 0x078: its bottom edge, at window_bottom */
    s32 list_x;                                   /* 0x07c: the list's left edge, in pixels */
    s32 marker_y;                                 /* 0x080: the picked row's y */
    int clock_minutes;                            /* 0x084: the time the hands show, in minutes */
    s32 target_minutes;                           /* 0x088: the time they spin to */
    s32 scroll_max;                               /* 0x08c */
    u16 flags;                                    /* 0x090: ClockSetterFlag */
    u16 minute_angle;                             /* 0x092: 0x10000 a turn, clockwise from twelve */
    u16 hour_angle;                               /* 0x094 */
    u16 tick_angle;                               /* 0x096: the dragged hand's angle at its last tick */
    u8 blink[CLOCK_SETTER_FIELDS];                /* 0x098: frames each changed field stays highlighted */
    u8 hand;                                      /* 0x09e: ClockSetterHand */
    u8 labels_used;                               /* 0x09f: of `labels` (ClockSetter_NextLabel) */
    u8 mode;                                      /* 0x0a0: ClockSetterMode */
    u8 face;                                      /* 0x0a1: 0 with the hands (modes 0, 1), 1 (mode 2),
                                             * 2 (mode 3): the column of the digits' characters */
    u8 base_layer;                                /* 0x0a2: characters, palettes, backdrop and title */
    u8 panel_layer;                               /* 0x0a3: the fields (panel_map) and their labels */
    u8 list_layer;                                /* 0x0a4: the list (list_map_shown) and its labels */
    u8 list_field;                                /* 0x0a5: the field whose list is open */
    u8 pad_a6;                                    /* 0x0a6 */
    u8 list_col;                                  /* 0x0a7: the field's column, in tiles */
    u8 list_row;                                  /* 0x0a8: the field's row, in tiles */
    u8 list_state;                                /* 0x0a9: ClockSetterListState */
    u8 list_scroll_x;                             /* 0x0aa: the list layer's x scroll, negated */
    u8 list_top;                                  /* 0x0ab: the list's first row's y at scroll 0 */
    u8 list_rows;                                 /* 0x0ac */
    u8 list_pick;                                 /* 0x0ad: the row picked */
    u8 field_y;                                   /* 0x0ae: the field's middle, in pixels: the window
                                             * closes onto it */
    u8 fade;                                      /* 0x0af: the steps of the opening and closing */
    u8 cursor;                                    /* 0x0b0: the cursor's row plus 1; 0 on the thumb */
    u8 focus;                                     /* 0x0b1: the focused field, or CLOCK_SETTER_NO_FIELD */
    u8 min_hour;                                  /* 0x0b2: min's hour */
    u8 max_hour;                                  /* 0x0b3: max's hour */
    u8 min_minute;                                /* 0x0b4: min's minute (not read here) */
    u8 window_top;                                /* 0x0b5: the list's window (sub window 0) */
    u8 window_bottom;                             /* 0x0b6 */
    s8 key_run;                                   /* 0x0b7: rows stepped in a row: up > 0, down < 0 */
    DateTime value;                               /* 0x0b8: what the panel shows and edits */
    DateTime drag;                                /* 0x0c0: the time a hand drag has reached */
    DateTime min;                                 /* 0x0c8 */
    DateTime max;                                 /* 0x0d0 */
    TextLabel labels[CLOCK_SETTER_LABELS];        /* 0x0d8: handed out each frame, the last one shared */
    LayerTask panel_task;                         /* 0x804: panel_map to the panel layer */
    LayerTask list_task;                          /* 0x828: list_map_shown to the list layer */
    LayerTask palette_task;                       /* 0x84c: palette_shown to the list layer */
    u16 panel_map[CLOCK_SETTER_MAP_ENTRIES];      /* 0x870: the fields' screen (bgb-bge.bsc) */
    u16 list_base[CLOCK_SETTER_MAP_ENTRIES];      /* 0x1070: the list's screen as read (b_tim_b1_bg.bsc) */
    u16 list_map[CLOCK_SETTER_MAP_ENTRIES];       /* 0x1870: list_base fitted to the open field */
    u16 list_map_shown[CLOCK_SETTER_MAP_ENTRIES]; /* 0x2070: list_map with the rows drawn in */
    u16 palette[16];                              /* 0x2870: the list's palette (b_tim_bg_9.bpl) */
    u16 palette_shown[16];                        /* 0x2890: with its last colour faded */
} ClockSetter;

/* clock_setter.c */
void ClockSetter_ClearFlags(ClockSetter *self, u16 flags);
void ClockSetter_SetFlags(ClockSetter *self, u32 flags);
int ClockSetter_TestFlags(ClockSetter *self, u32 flags);
void ClockSetter_FadeListColor(ClockSetter *self, int step);
void ClockSetter_SetFocus(ClockSetter *self, int field);
u8 ClockSetter_Focus(ClockSetter *self);
void ClockSetter_TickBlinks(ClockSetter *self);
void ClockSetter_ResetFieldColors(ClockSetter *self);
void ClockSetter_ColorFieldButton(ClockSetter *self, int field, int palette);
void ClockSetter_ColorField(ClockSetter *self, int field, int palette);
int ClockSetter_FieldBottom(ClockSetter *self, int field);
int ClockSetter_FieldRight(ClockSetter *self, int field);
int ClockSetter_FieldWidth(ClockSetter *self, int field);
int ClockSetter_FieldTop(ClockSetter *self, int field);
int ClockSetter_FieldLeft(ClockSetter *self, int field);
int ClockSetter_TouchedTimeField(ClockSetter *self, int x, int y);
int ClockSetter_TouchedMonthDayField(ClockSetter *self, int x, int y);
int ClockSetter_TouchedDateField(ClockSetter *self, int x, int y);
int ClockSetter_TouchedField(ClockSetter *self, int x, int y);
void ClockSetter_Draw(ClockSetter *self, int x, int y);
void ClockSetter_DrawNumber(ClockSetter *self, int layer, int first_char, int cells, int number, u8 color_38, u8 color_39);
void ClockSetter_DrawTitle(ClockSetter *self, int layer, int first_char, int cells, u8 message, int text_cells);
void ClockSetter_DrawMessage(ClockSetter *self, int layer, int first_char, int cells, u8 message, int center, u8 color_38,
                             u8 color_39);
TextLabel *ClockSetter_NextLabel(ClockSetter *self);
void ClockSetter_CloseLabels(ClockSetter *self);
void ClockSetter_DrawPickLabel(ClockSetter *self);
void ClockSetter_DrawMinute(ClockSetter *self);
void ClockSetter_DrawHour(ClockSetter *self);
void ClockSetter_DrawDay(ClockSetter *self);
void ClockSetter_DrawMonth(ClockSetter *self);
void ClockSetter_DrawYear(ClockSetter *self);
void ClockSetter_SetField(ClockSetter *self, unsigned int field, int value);
int ClockSetter_FieldOf(ClockSetter *self, unsigned int field, const DateTime *when);
int ClockSetter_Field(ClockSetter *self, int field);
void ClockSetter_DrawField(ClockSetter *self, unsigned int field);
void ClockSetter_DrawFields(ClockSetter *self);
void ClockSetter_DrawWeekday(ClockSetter *self);
int ClockSetter_LoadSprites(ClockSetter *self);
void ClockSetter_DrawLabels(ClockSetter *self, unsigned int title);
int ClockSetter_LoadBackground(ClockSetter *self);
int ClockSetter_IsBeforeMin(ClockSetter *self);
void ClockSetter_CopyValue(ClockSetter *self, DateTime *out);
void ClockSetter_Update(ClockSetter *self);
void ClockSetter_EndFrame(ClockSetter *self);
void ClockSetter_Teardown(ClockSetter *self);
void ClockSetter_UseMinimum(ClockSetter *self);
void ClockSetter_Init(ClockSetter *self, int mode, int base_layer, int panel_layer, u8 list_layer);
ClockSetter *ClockSetter_Destroy(ClockSetter *self);
ClockSetter *ClockSetter_Construct(ClockSetter *self);

/* clock_setter_list.c */
void ClockSetter_StepScroll(ClockSetter *self);
int ClockSetter_RowAt(ClockSetter *self, int y);
int ClockSetter_CursorDown(ClockSetter *self);
int ClockSetter_CursorUp(ClockSetter *self);
int ClockSetter_PickCursorRow(ClockSetter *self);
int ClockSetter_ListKeys(ClockSetter *self, int keys);
void ClockSetter_CursorToY(ClockSetter *self, int y);
int ClockSetter_CursorY(ClockSetter *self);
int ClockSetter_CursorX(ClockSetter *self);
void ClockSetter_PlaceThumb(ClockSetter *self);
int ClockSetter_ScrollFromThumb(ClockSetter *self);
void ClockSetter_ThumbFromScroll(ClockSetter *self);
int ClockSetter_SettleThumb(ClockSetter *self);
int ClockSetter_ReleaseThumb(ClockSetter *self);
void ClockSetter_MoveThumbByKeys(ClockSetter *self);
void ClockSetter_ThumbTowardPen(ClockSetter *self, int pen_y);
void ClockSetter_DragThumb(ClockSetter *self, int pen_y);
void ClockSetter_ThumbMoved(ClockSetter *self);
int ClockSetter_PressThumbByKey(ClockSetter *self);
int ClockSetter_GrabThumb(ClockSetter *self, int x, int y);
int ClockSetter_RowDisabled(ClockSetter *self, int row);
int ClockSetter_BelowMin(ClockSetter *self, int row, unsigned int field);
int ClockSetter_AboveMax(ClockSetter *self, int row, unsigned int field);
int ClockSetter_CommitPick(ClockSetter *self);
void ClockSetter_CloseWindowStep(ClockSetter *self);
void ClockSetter_OpenWindowStep(ClockSetter *self);
void ClockSetter_RedrawList(ClockSetter *self);
void ClockSetter_ScrollLayer(ClockSetter *self);
void ClockSetter_SetScroll(ClockSetter *self, int scroll);
int ClockSetter_TouchList(ClockSetter *self, int x, int y);
int ClockSetter_CloseListStep(ClockSetter *self);
void ClockSetter_CancelList(ClockSetter *self);
void ClockSetter_PickRow(ClockSetter *self);
int ClockSetter_TouchRow(ClockSetter *self, int x, int y);
int ClockSetter_OpenListStep(ClockSetter *self);
void ClockSetter_OpenList(ClockSetter *self, int field);
void ClockSetter_FocusNext(ClockSetter *self);

/* clock_setter_hands.c */
int ClockSetter_SpinHands(ClockSetter *self);
int ClockSetter_Approach(ClockSetter *self, int *value, int target, int max_step, int min_step);
void ClockSetter_AddMinutes(ClockSetter *self, int minutes);
int ClockSetter_InDial(ClockSetter *self, int x, int y, int radius);
int ClockSetter_AngleDiff(ClockSetter *self, int to, int from);
int ClockSetter_TouchTurn(ClockSetter *self, int x, int y, int angle);
int ClockSetter_TouchAngle(ClockSetter *self, int x, int y);
void ClockSetter_HandsFromClock(ClockSetter *self);
void ClockSetter_HandsFromValue(ClockSetter *self);
void ClockSetter_SetHands(ClockSetter *self, unsigned int hour, int minute);
void ClockSetter_TurnHourHand(ClockSetter *self, int x, int y);
void ClockSetter_TurnMinuteHand(ClockSetter *self, int x, int y);
int ClockSetter_SpinHandsHome(ClockSetter *self);
int ClockSetter_ReleaseHand(ClockSetter *self);
void ClockSetter_DragHand(ClockSetter *self, int x, int y);
int ClockSetter_GrabHand(ClockSetter *self, int x, int y);

#endif
