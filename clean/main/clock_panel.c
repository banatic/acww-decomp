/* The clock panel, the first screen panel (clock_panel.h). */
#include "clock_panel.h"

#include "autoload_2/approach.h" /* Approach_EaseS32MinMax */
#include "autoload_2/heap.h"     /* Heap_OperatorDeleteB */
#include "cell_anim.h"
#include "clean.h"
#include "clock.h"          /* Clock_GetDayMonth */
#include "event_queue.h"    /* EventQueue_HasCurrent */
#include "number_text.h"    /* NumberText_Format */
#include "oam_buffer.h"     /* OamBuffer_DrawCell */
#include "overlay_groups.h" /* OverlayGroups_HasOwner */
#include "quick_message.h"  /* QuickMessage_OwnBalloonBusy */
#include "state_flags.h"    /* StateFlags_Test4, StateFlags_ValueOrOne */
#include "text_draw.h"      /* TextDraw_AlignRight, TextDraw_Center, TextDraw_RequestClear, TextDraw_RequestDraw */

#include "ov004/member_pointer.h" /* MemberPointer */

static_assert(offsetof(ClockPanel, anim) == 0x0c && offsetof(ClockPanel, state) == 0x20, "ClockPanel");
static_assert(offsetof(ClockPanel, month_box) == 0x28 && offsetof(ClockPanel, colon_box) == 0x40, "ClockPanel");
static_assert(offsetof(ClockPanel, blink) == 0x44 && offsetof(ClockPanel, month_changed) == 0x48, "ClockPanel");
static_assert(offsetof(ClockPanel, shown) == 0x4e && offsetof(ClockPanel, shift) == 0x50, "ClockPanel");
static_assert(offsetof(ClockPanel, shift_wait) == 0x5c && offsetof(ClockPanel, day_month) == 0x60, "ClockPanel");
static_assert(offsetof(ClockPanel, time) == 0x62 && offsetof(ClockPanel, weekday) == 0x64, "ClockPanel");
static_assert(offsetof(ClockPanel, month_text) == 0x68 && offsetof(ClockPanel, minutes_text) == 0xbc, "ClockPanel");
static_assert(sizeof(ClockPanel) == 0xd8, "ClockPanel");

extern u8 data_020e54a8; /* 0 outdoors, 1 in a room */
#define CLOCK_PANEL_IN_A_ROOM 1

/* The animations of main's sprites: the panel appears with entry 4 and hides with 5, in a room
 * with 0x29 and 0x2a. */
extern const CellAnimData data_020d5b3c[];
#define CLOCK_PANEL_ANIM_APPEARING 4
#define CLOCK_PANEL_ANIM_HIDING 5
#define CLOCK_PANEL_ANIM_APPEARING_ROOM 0x29
#define CLOCK_PANEL_ANIM_HIDING_ROOM 0x2a

/* The fonts: fontC for the date, the weekday and the colon, fontD for AM/PM and the time. */
extern TextFont data_021c82e8;
extern TextFont data_021c81d4;

/* The texts of the parts that are not numbers (16-bit characters): the colon; "AM" and "PM",
 * 6 bytes each; the font's weekday characters, one 4-byte text a weekday from Sunday. */
extern const char data_020d0a54[];
extern const char data_020d0a64[];
extern const u32 data_020d0aac[];
#define CLOCK_PANEL_AM_PM_SIZE 6

/* The class's vtable, and the member function table of ClockPanel_Update (a function-local
 * static of the game): its guard, the table, and the constants it is filled from. */
extern const u32 data_020e226c[];
extern u32 data_021d3158;
extern MemberPointer data_021d3170[4];
extern const MemberPointer data_020e213c, data_020e212c, data_020e215c, data_020e214c;

/* Player `player`'s session state is `state`. */
extern int func_020960f8(int state, int player);
#define CLOCK_PANEL_PLAYER 4
#define CLOCK_PANEL_PLAYER_STATE 2
/* The number text's constructor. */
extern void *func_0208e024(CatchPanelText *text);

/* The ease of `shift`, as the catch panel's: 20 pixels higher while this system's balloon is
 * out, eased by 0x600 of the distance a frame, the step from 0x2300 up to `shift_speed`, which
 * grows by 0xa00 a frame from 0x2300 to 0x5000. A new target waits 10 frames, except the first
 * after a reset and one while the panel should not show. */
#define CLOCK_PANEL_SHIFT_BALLOON (-0x14000)
#define CLOCK_PANEL_SHIFT_RATE 0x600
#define CLOCK_PANEL_SHIFT_SPEED_ADD 0xa00
#define CLOCK_PANEL_SHIFT_SPEED_MIN 0x2300
#define CLOCK_PANEL_SHIFT_SPEED_MAX 0x5000
#define CLOCK_PANEL_SHIFT_WAIT 10

#define CLOCK_PANEL_FX_ONE 0x1000

/* The waits before appearing: after an event with no owner or no owner away from session
 * state 2, after an event with an owner that covers the panel, and while not asked to show. */
#define CLOCK_PANEL_WAIT_AWAY 30
#define CLOCK_PANEL_WAIT_COVERED 1
#define CLOCK_PANEL_WAIT_NOT_SHOWN 10

/* The colon's blink: drawn when the count runs out (and set to 20), cleared at 8. */
#define CLOCK_PANEL_BLINK_PERIOD 20
#define CLOCK_PANEL_BLINK_CLEAR 8

/* The hours of a half day. */
#define CLOCK_PANEL_HALF_DAY 12

/* The numbers: 2 digits, no unit, half-width characters; the date's not padded, the time's
 * padded with zeros. */
#define CLOCK_PANEL_DIGITS 2
#define CLOCK_PANEL_UNIT 0
#define CLOCK_PANEL_HALF_WIDTH 1

/* The text boxes, on OBJs of the main screen. */
#define CLOCK_PANEL_BOX_LAYER_OBJECTS 4
#define CLOCK_PANEL_BOX_BACKGROUND 0
#define CLOCK_PANEL_DATE_COLOR 0xc
#define CLOCK_PANEL_WEEKDAY_COLOR 0xa
#define CLOCK_PANEL_TIME_COLOR 9

/* The palettes of the panel's cell: on Sundays, on the other days. */
#define CLOCK_PANEL_PALETTE_SUNDAY 15
#define CLOCK_PANEL_PALETTE 9
#define CLOCK_PANEL_SUNDAY 0

/* vtable slots */
#define CLOCK_PANEL_SLOT_DRAW 2
#define CLOCK_PANEL_SLOT_UPDATE 3

static void clock_panel_set_anim(ClockPanel *panel, int entry)
{
    CellAnim_SetData(&panel->anim, &data_020d5b3c[entry]);
    CellAnim_SetHold(&panel->anim, 1);
    CellAnim_Restart(&panel->anim);
}

/* A number written into `text` and handed to `box` (through the text's vtable). */
static void clock_panel_format(LabelBox *box, CatchPanelText *text, int value, int format)
{
    NumberText_Format(text, value, CLOCK_PANEL_DIGITS, format, CLOCK_PANEL_UNIT, CLOCK_PANEL_HALF_WIDTH);
    int chars = ((int (*)(CatchPanelText *))(uintptr_t) text->vtable->buffer)(text);
    box->base.text = (const char *) (uintptr_t) chars;
}

/* A box from VRAM tile `tile`, set up in `font` and `color` and marked for a draw; NULL when
 * the boxes' heap is full. */
static LabelBox *clock_panel_open_box(LabelBox **slot, int tile, int cells, int rows, u8 color, TextFont *font)
{
    *slot = LabelBox_NewInVram(tile, cells, rows);
    LabelBox *box = *slot;
    if (box == NULL) {
        return NULL;
    }
    box->base.layer = CLOCK_PANEL_BOX_LAYER_OBJECTS;
    box->base.screens = TEXT_DRAW_TO_MAIN;
    box->base.rows_full_width = 1;
    box->base.background = CLOCK_PANEL_BOX_BACKGROUND;
    box->base.color = color;
    box->base.font = font;
    TextDraw_RequestDraw(&box->base);
    return box;
}

/* func_0208d400 */
void ClockPanel_ResetShift(ClockPanel *panel)
{
    panel->shift = 0;
    panel->shift_target = 0;
    panel->shift_wait = -1;
    panel->shift_speed = 0;
}
CLEAN_AS(func_0208d400, ClockPanel_ResetShift)

/* func_0208d410: `shift` eased toward its target, 20 pixels higher while this system's quick
 * message balloon is out and the panel should show. Both are asked every frame. */
void ClockPanel_UpdateShift(ClockPanel *panel)
{
    int busy = QuickMessage_OwnBalloonBusy();
    int show = ClockPanel_ShouldShow(panel);
    int target = (busy != 0 && show != 0) ? CLOCK_PANEL_SHIFT_BALLOON : 0;
    panel->shift_speed += CLOCK_PANEL_SHIFT_SPEED_ADD;
    if (panel->shift_speed < CLOCK_PANEL_SHIFT_SPEED_MIN) {
        panel->shift_speed = CLOCK_PANEL_SHIFT_SPEED_MIN;
    } else if (panel->shift_speed > CLOCK_PANEL_SHIFT_SPEED_MAX) {
        panel->shift_speed = CLOCK_PANEL_SHIFT_SPEED_MAX;
    }
    if (target != panel->shift_target) {
        int waited;
        if (panel->shift_wait < 0 || show == 0) {
            waited = 1;
        } else {
            panel->shift_wait++;
            waited = panel->shift_wait > CLOCK_PANEL_SHIFT_WAIT;
        }
        if (waited) {
            panel->shift_target = target;
            panel->shift_wait = 0;
        }
    } else {
        panel->shift_wait = 0;
    }
    Approach_EaseS32MinMax(&panel->shift, panel->shift_target, CLOCK_PANEL_SHIFT_RATE, panel->shift_speed,
                           CLOCK_PANEL_SHIFT_SPEED_MIN);
}
CLEAN_AS(func_0208d410, ClockPanel_UpdateShift)

/* func_0208d4a4: the date, the time and the weekday read and kept, each part whose value
 * changed marked for a redraw (AM/PM with the hour). */
void ClockPanel_ReadClock(ClockPanel *panel)
{
    u8 day_month[2];
    Time time;
    Clock_GetDayMonth(day_month);
    Calendar_Now(&time);
    u32 weekday = (u32) Calendar_TodayWeekday();

    if (day_month[0] != panel->day_month[0] || day_month[1] != panel->day_month[1]) {
        if (day_month[1] != panel->day_month[1]) {
            panel->month_changed = 1;
        }
        if (day_month[0] != panel->day_month[0]) {
            panel->day_changed = 1;
        }
        panel->day_month[0] = day_month[0];
        panel->day_month[1] = day_month[1];
    }
    if (time.minute != panel->time.minute || time.hour != panel->time.hour) {
        if (time.hour != panel->time.hour) {
            panel->hour_changed = 1;
            panel->am_pm_changed = 1;
        }
        if (time.minute != panel->time.minute) {
            panel->minutes_changed = 1;
        }
        panel->time = time;
    }
    if (weekday != panel->weekday) {
        panel->weekday_changed = 1;
        panel->weekday = weekday;
    }
}
CLEAN_AS(func_0208d4a4, ClockPanel_ReadClock)

/* func_0208d560: while the colon's box is there, the colon drawn every 20 frames and cleared
 * 12 frames after. */
void ClockPanel_BlinkColon(ClockPanel *panel)
{
    if (panel->colon_box == NULL) {
        return;
    }
    panel->blink--;
    if (panel->blink <= 0) {
        panel->blink = CLOCK_PANEL_BLINK_PERIOD;
        TextDraw_RequestDraw(&panel->colon_box->base);
    } else if (panel->blink == CLOCK_PANEL_BLINK_CLEAR) {
        TextDraw_RequestClear(&panel->colon_box->base, 0);
    }
}
CLEAN_AS(func_0208d560, ClockPanel_BlinkColon)

/* func_0208d594: the minutes written, padded with zeros, and their box redrawn, centred, once
 * changed. */
void ClockPanel_RedrawMinutes(ClockPanel *panel)
{
    if (panel->minutes_box == NULL || panel->minutes_changed == 0) {
        return;
    }
    panel->minutes_changed = 0;
    clock_panel_format(panel->minutes_box, &panel->minutes_text, panel->time.minute, NUMBER_TEXT_ZEROS);
    TextDraw_Center(&panel->minutes_box->base);
    TextDraw_RequestDraw(&panel->minutes_box->base);
}
CLEAN_AS(func_0208d594, ClockPanel_RedrawMinutes)

/* func_0208d5ec: the hour of the half day written, padded with zeros, and its box redrawn,
 * centred, once changed.
 * QUIRK: noon and midnight show as 00. */
void ClockPanel_RedrawHour(ClockPanel *panel)
{
    if (panel->hour_box == NULL || panel->hour_changed == 0) {
        return;
    }
    panel->hour_changed = 0;
    u8 hour = panel->time.hour;
    if (hour >= CLOCK_PANEL_HALF_DAY) {
        hour = (u8) (hour - CLOCK_PANEL_HALF_DAY);
    }
    clock_panel_format(panel->hour_box, &panel->hour_text, hour, NUMBER_TEXT_ZEROS);
    TextDraw_Center(&panel->hour_box->base);
    TextDraw_RequestDraw(&panel->hour_box->base);
}
CLEAN_AS(func_0208d5ec, ClockPanel_RedrawHour)

/* func_0208d650: "AM" or "PM" (from hour 12) handed to its box, redrawn centred, once
 * changed. */
void ClockPanel_RedrawAmPm(ClockPanel *panel)
{
    if (panel->am_pm_box == NULL || panel->am_pm_changed == 0) {
        return;
    }
    panel->am_pm_changed = 0;
    int pm = panel->time.hour >= CLOCK_PANEL_HALF_DAY;
    panel->am_pm_box->base.text = data_020d0a64 + CLOCK_PANEL_AM_PM_SIZE * pm;
    TextDraw_Center(&panel->am_pm_box->base);
    TextDraw_RequestDraw(&panel->am_pm_box->base);
}
CLEAN_AS(func_0208d650, ClockPanel_RedrawAmPm)

/* func_0208d69c: the weekday's character handed to its box, redrawn centred, once changed.
 * QUIRK: the weekday indexes data_020d0aac unchecked (the clock gives 0-6). */
void ClockPanel_RedrawWeekday(ClockPanel *panel)
{
    if (panel->weekday_box == NULL || panel->weekday_changed == 0) {
        return;
    }
    panel->weekday_changed = 0;
    u32 chars = (u32) (uintptr_t) data_020d0aac + panel->weekday * (u32) sizeof(data_020d0aac[0]);
    panel->weekday_box->base.text = (const char *) (uintptr_t) chars;
    TextDraw_Center(&panel->weekday_box->base);
    TextDraw_RequestDraw(&panel->weekday_box->base);
}
CLEAN_AS(func_0208d69c, ClockPanel_RedrawWeekday)

/* func_0208d6dc: the day written and its box redrawn (as laid out), once changed. */
void ClockPanel_RedrawDay(ClockPanel *panel)
{
    if (panel->day_box == NULL || panel->day_changed == 0) {
        return;
    }
    panel->day_changed = 0;
    clock_panel_format(panel->day_box, &panel->day_text, panel->day_month[0], NUMBER_TEXT_PLAIN);
    TextDraw_RequestDraw(&panel->day_box->base);
}
CLEAN_AS(func_0208d6dc, ClockPanel_RedrawDay)

/* func_0208d72c: the month written and its box redrawn, right-aligned, once changed. */
void ClockPanel_RedrawMonth(ClockPanel *panel)
{
    if (panel->month_box == NULL || panel->month_changed == 0) {
        return;
    }
    panel->month_changed = 0;
    clock_panel_format(panel->month_box, &panel->month_text, panel->day_month[1], NUMBER_TEXT_PLAIN);
    TextDraw_AlignRight(&panel->month_box->base);
    TextDraw_RequestDraw(&panel->month_box->base);
}
CLEAN_AS(func_0208d72c, ClockPanel_RedrawMonth)

/* func_0208d784 */
void ClockPanel_RedrawParts(ClockPanel *panel)
{
    ClockPanel_RedrawMonth(panel);
    ClockPanel_RedrawDay(panel);
    ClockPanel_RedrawWeekday(panel);
    ClockPanel_RedrawAmPm(panel);
    ClockPanel_RedrawHour(panel);
    ClockPanel_RedrawMinutes(panel);
    ClockPanel_BlinkColon(panel);
}
CLEAN_AS(func_0208d784, ClockPanel_RedrawParts)

static void clock_panel_free_box(LabelBox **box)
{
    if (*box != NULL) {
        LabelBox_Free(*box);
        *box = NULL;
    }
}

/* func_0208d7b8 */
void ClockPanel_FreeTextBoxes(ClockPanel *panel)
{
    clock_panel_free_box(&panel->month_box);
    clock_panel_free_box(&panel->day_box);
    clock_panel_free_box(&panel->weekday_box);
    clock_panel_free_box(&panel->am_pm_box);
    clock_panel_free_box(&panel->hour_box);
    clock_panel_free_box(&panel->minutes_box);
    clock_panel_free_box(&panel->colon_box);
}
CLEAN_AS(func_0208d7b8, ClockPanel_FreeTextBoxes)

/* func_0208d824: the colon's box made (from tile 0x8c, or 0xd8 in a room), unless there is
 * one: the colon centred, then cleared (the blink draws it). */
void ClockPanel_OpenColonBox(ClockPanel *panel)
{
    if (panel->colon_box != NULL) {
        return;
    }
    panel->colon_box = LabelBox_NewInVram(panel->in_room != 0 ? 0xd8 : 0x8c, 1, 2);
    LabelBox *box = panel->colon_box;
    if (box == NULL) {
        return;
    }
    box->base.layer = CLOCK_PANEL_BOX_LAYER_OBJECTS;
    box->base.text = data_020d0a54;
    box->base.screens = TEXT_DRAW_TO_MAIN;
    box->base.rows_full_width = 1;
    box->base.font = &data_021c82e8;
    TextDraw_Center(&box->base);
    box->base.background = CLOCK_PANEL_BOX_BACKGROUND;
    box->base.color = CLOCK_PANEL_TIME_COLOR;
    TextDraw_RequestClear(&box->base, 0);
}
CLEAN_AS(func_0208d824, ClockPanel_OpenColonBox)

/* func_0208d898: the minutes' box (from tile 0xaa, or 0xf6 in a room), unless there is one,
 * marked for a redraw. */
void ClockPanel_OpenMinutesBox(ClockPanel *panel)
{
    if (panel->minutes_box != NULL) {
        return;
    }
    int tile = panel->in_room != 0 ? 0xf6 : 0xaa;
    if (clock_panel_open_box(&panel->minutes_box, tile, 2, 1, CLOCK_PANEL_TIME_COLOR, &data_021c81d4) != NULL) {
        panel->minutes_changed = 1;
    }
}
CLEAN_AS(func_0208d898, ClockPanel_OpenMinutesBox)

/* func_0208d900: the hour's box (from tile 0xa8, or 0xf4 in a room), the same way. */
void ClockPanel_OpenHourBox(ClockPanel *panel)
{
    if (panel->hour_box != NULL) {
        return;
    }
    int tile = panel->in_room != 0 ? 0xf4 : 0xa8;
    if (clock_panel_open_box(&panel->hour_box, tile, 2, 1, CLOCK_PANEL_TIME_COLOR, &data_021c81d4) != NULL) {
        panel->hour_changed = 1;
    }
}
CLEAN_AS(func_0208d900, ClockPanel_OpenHourBox)

/* func_0208d968: AM/PM's box (from tile 0x88, or 0xd4 in a room), the same way. */
void ClockPanel_OpenAmPmBox(ClockPanel *panel)
{
    if (panel->am_pm_box != NULL) {
        return;
    }
    int tile = panel->in_room != 0 ? 0xd4 : 0x88;
    if (clock_panel_open_box(&panel->am_pm_box, tile, 2, 1, CLOCK_PANEL_TIME_COLOR, &data_021c81d4) != NULL) {
        panel->am_pm_changed = 1;
    }
}
CLEAN_AS(func_0208d968, ClockPanel_OpenAmPmBox)

/* func_0208d9d0: the weekday's box (from tile 0x86, or 0x9a in a room), the same way. */
void ClockPanel_OpenWeekdayBox(ClockPanel *panel)
{
    if (panel->weekday_box != NULL) {
        return;
    }
    int tile = panel->in_room != 0 ? 0x9a : 0x86;
    if (clock_panel_open_box(&panel->weekday_box, tile, 2, 2, CLOCK_PANEL_WEEKDAY_COLOR, &data_021c82e8) != NULL) {
        panel->weekday_changed = 1;
    }
}
CLEAN_AS(func_0208d9d0, ClockPanel_OpenWeekdayBox)

/* func_0208da38: the day's box (from tile 0x83, or 0x97 in a room), the same way. */
void ClockPanel_OpenDayBox(ClockPanel *panel)
{
    if (panel->day_box != NULL) {
        return;
    }
    int tile = panel->in_room != 0 ? 0x97 : 0x83;
    if (clock_panel_open_box(&panel->day_box, tile, 3, 2, CLOCK_PANEL_DATE_COLOR, &data_021c82e8) != NULL) {
        panel->day_changed = 1;
    }
}
CLEAN_AS(func_0208da38, ClockPanel_OpenDayBox)

/* func_0208daa0: the month's box (from tile 0x80, or 0x94 in a room), the same way. */
void ClockPanel_OpenMonthBox(ClockPanel *panel)
{
    if (panel->month_box != NULL) {
        return;
    }
    int tile = panel->in_room != 0 ? 0x94 : 0x80;
    if (clock_panel_open_box(&panel->month_box, tile, 3, 2, CLOCK_PANEL_DATE_COLOR, &data_021c82e8) != NULL) {
        panel->month_changed = 1;
    }
}
CLEAN_AS(func_0208daa0, ClockPanel_OpenMonthBox)

/* func_0208db08 */
void ClockPanel_OpenTextBoxes(ClockPanel *panel)
{
    ClockPanel_OpenMonthBox(panel);
    ClockPanel_OpenDayBox(panel);
    ClockPanel_OpenWeekdayBox(panel);
    ClockPanel_OpenAmPmBox(panel);
    ClockPanel_OpenHourBox(panel);
    ClockPanel_OpenMinutesBox(panel);
    ClockPanel_OpenColonBox(panel);
}
CLEAN_AS(func_0208db08, ClockPanel_OpenTextBoxes)

/* func_0208db3c: whether the panel should show (the `shown` byte as it is, else 0): `shown`
 * set, and none of: an event running with no overlay group owner; no owner while player 4 is
 * not in session state 2; an event with an owner while state flag 4 is clear or its value
 * below 1.0. When it should not, `wait` is set: 10 without `shown`, 30 for the first two
 * cases, 1 for the third. */
int ClockPanel_ShouldShow(ClockPanel *panel)
{
    int shown = panel->shown;
    if (shown == 0) {
        panel->wait = CLOCK_PANEL_WAIT_NOT_SHOWN;
        return 0;
    }
    int event = EventQueue_HasCurrent();
    int standing = func_020960f8(CLOCK_PANEL_PLAYER_STATE, CLOCK_PANEL_PLAYER);
    int owner = OverlayGroups_HasOwner();
    int event_no_owner = event != 0 && owner == 0;
    int away = owner == 0 && standing == 0;
    int covered = 0;
    if (event != 0 && owner != 0) {
        int flag = StateFlags_Test4();
        fx32 value = StateFlags_ValueOrOne();
        covered = flag == 0 || value < CLOCK_PANEL_FX_ONE;
    }
    if (event_no_owner || away || covered) {
        panel->wait = (event_no_owner || away) ? CLOCK_PANEL_WAIT_AWAY : CLOCK_PANEL_WAIT_COVERED;
        return 0;
    }
    return shown;
}
CLEAN_AS(func_0208db3c, ClockPanel_ShouldShow)

/* func_0208dbd8: once the hiding animation is done, the text boxes freed and hidden. */
void ClockPanel_StepHiding(ClockPanel *panel)
{
    CellAnim_Advance(&panel->anim);
    if (CellAnim_IsDone(&panel->anim) != 0) {
        ClockPanel_FreeTextBoxes(panel);
        ClockPanel_EnterHidden(panel);
    }
}
CLEAN_AS(func_0208dbd8, ClockPanel_StepHiding)

/* func_0208dc00 */
void ClockPanel_EnterHiding(ClockPanel *panel)
{
    panel->state = CLOCK_PANEL_HIDING;
    clock_panel_set_anim(panel, panel->in_room != 0 ? CLOCK_PANEL_ANIM_HIDING_ROOM : CLOCK_PANEL_ANIM_HIDING);
}
CLEAN_AS(func_0208dc00, ClockPanel_EnterHiding)

/* func_0208dc44 */
void ClockPanel_StepShown(ClockPanel *panel)
{
    if (ClockPanel_ShouldShow(panel) == 0) {
        ClockPanel_EnterHiding(panel);
    }
}
CLEAN_AS(func_0208dc44, ClockPanel_StepShown)

/* func_0208dc5c */
void ClockPanel_EnterShown(ClockPanel *panel)
{
    panel->state = CLOCK_PANEL_SHOWN;
}
CLEAN_AS(func_0208dc5c, ClockPanel_EnterShown)

/* func_0208dc64 */
void ClockPanel_StepAppearing(ClockPanel *panel)
{
    CellAnim_Advance(&panel->anim);
    if (CellAnim_IsDone(&panel->anim) != 0) {
        ClockPanel_EnterShown(panel);
    }
}
CLEAN_AS(func_0208dc64, ClockPanel_StepAppearing)

/* func_0208dc88: the shift reset, the appearing animation started and the text boxes made. */
void ClockPanel_EnterAppearing(ClockPanel *panel)
{
    panel->state = CLOCK_PANEL_APPEARING;
    ClockPanel_ResetShift(panel);
    clock_panel_set_anim(panel, panel->in_room != 0 ? CLOCK_PANEL_ANIM_APPEARING_ROOM : CLOCK_PANEL_ANIM_APPEARING);
    ClockPanel_OpenTextBoxes(panel);
}
CLEAN_AS(func_0208dc88, ClockPanel_EnterAppearing)

/* func_0208dcd4: while the panel should show, `wait` counted down; appearing once it runs
 * out. */
void ClockPanel_StepHidden(ClockPanel *panel)
{
    if (ClockPanel_ShouldShow(panel) != 0) {
        panel->wait--;
        if (panel->wait <= 0) {
            ClockPanel_EnterAppearing(panel);
        }
    }
}
CLEAN_AS(func_0208dcd4, ClockPanel_StepHidden)

/* func_0208dcf8 */
void ClockPanel_EnterHidden(ClockPanel *panel)
{
    panel->state = CLOCK_PANEL_HIDDEN;
}
CLEAN_AS(func_0208dcf8, ClockPanel_EnterHidden)

/* func_0208dd00 */
int ClockPanel_IsHidden(ClockPanel *panel)
{
    return panel->state == CLOCK_PANEL_HIDDEN;
}
CLEAN_AS(func_0208dd00, ClockPanel_IsHidden)

/* func_0208dd10 */
void ClockPanel_Hide(ClockPanel *panel)
{
    panel->shown = 0;
}
CLEAN_AS(func_0208dd10, ClockPanel_Hide)

/* func_0208dd18: shown, in a room when data_020e54a8 is 1. */
void ClockPanel_Show(ClockPanel *panel)
{
    panel->shown = 1;
    panel->in_room = data_020e54a8 == CLOCK_PANEL_IN_A_ROOM;
}
CLEAN_AS(func_0208dd18, ClockPanel_Show)

/* func_0208dd40: the class's draw (vtable slot 2). */
void ClockPanel_CallDraw(ClockPanel *panel)
{
    ((void (*)(ClockPanel *))(uintptr_t) panel->base.vtable[CLOCK_PANEL_SLOT_DRAW])(panel);
}
CLEAN_AS(func_0208dd40, ClockPanel_CallDraw)

typedef void *ClockPanelSlot(ClockPanel *panel);

/* func_0208dd50: the class's update (vtable slot 3).
 * QUIRK: the result is whatever the slot leaves; ClockPanel_Update returns nothing, and the
 * caller (ScreenPanels_Update) ignores it. */
void *ClockPanel_CallUpdate(ClockPanel *panel)
{
    return ((ClockPanelSlot *) (uintptr_t) panel->base.vtable[CLOCK_PANEL_SLOT_UPDATE])(panel);
}
CLEAN_AS(func_0208dd50, ClockPanel_CallUpdate)

/* func_0208dd60: the text boxes freed. */
void ClockPanel_Rewind(ClockPanel *panel)
{
    ClockPanel_FreeTextBoxes(panel);
}
CLEAN_AS(func_0208dd60, ClockPanel_Rewind)

/* func_0208dd68: not shown, and hidden at once. */
void ClockPanel_Reset(ClockPanel *panel)
{
    panel->shown = 0;
    ClockPanel_EnterHidden(panel);
}
CLEAN_AS(func_0208dd68, ClockPanel_Reset)

/* func_0208dd78 (vtable slot 3): a frame: the state's step (through the game's table, filled
 * on the first call), the clock read, the parts redrawn and, unless hidden, the shift eased.
 * REQUIRES: the state is 0-3 (the ROM indexes its table unchecked). */
void ClockPanel_Update(ClockPanel *panel)
{
    static const MemberPointer *const constants[4] = {
        &data_020e213c, /* ClockPanel_StepHidden */
        &data_020e212c, /* ClockPanel_StepAppearing */
        &data_020e215c, /* ClockPanel_StepShown */
        &data_020e214c, /* ClockPanel_StepHiding */
    };
    MemberTable_InitOnce(&data_021d3158, data_021d3170, constants, 4);
    MemberPointer_CallVoid(&data_021d3170[panel->state], panel);
    ClockPanel_ReadClock(panel);
    ClockPanel_RedrawParts(panel);
    if (panel->state != CLOCK_PANEL_HIDDEN) {
        ClockPanel_UpdateShift(panel);
    }
}
CLEAN_AS(func_0208dd78, ClockPanel_Update)

/* func_0208de10 (vtable slot 2): unless hidden, the animation's cell drawn on the main screen
 * at the sprite's place plus the frame's offset, `shift` (rounded) lower, in palette 15 on
 * Sundays. */
void ClockPanel_Draw(ClockPanel *panel)
{
    if (panel->state == CLOCK_PANEL_HIDDEN) {
        return;
    }
    const OamEntry *cell = CellAnim_Cell(&panel->anim);
    if (cell == NULL) {
        return;
    }
    int frame_x = CellAnim_FrameX(&panel->anim, -1);
    int frame_y = CellAnim_FrameY(&panel->anim, -1);
    int x = ScreenSprite_X(&panel->base) + frame_x;
    int shift = (panel->shift + CLOCK_PANEL_FX_ONE / 2) >> 12;
    int y = ScreenSprite_Y(&panel->base) + shift + frame_y;
    int palette = panel->weekday == CLOCK_PANEL_SUNDAY ? CLOCK_PANEL_PALETTE_SUNDAY : CLOCK_PANEL_PALETTE;
    OamBuffer_DrawCell(0, cell, x, y, palette, -1, CLOCK_PANEL_FX_ONE, CLOCK_PANEL_FX_ONE, 0, -1, 0, 0);
}
CLEAN_AS(func_0208de10, ClockPanel_Draw)

/* The destructor's work (the ROM has it in both destructors): the animation restarted, the
 * text boxes freed, then the members, the last first, and the base. */
static void clock_panel_destruct(ClockPanel *panel)
{
    panel->base.vtable = data_020e226c;
    CellAnim_Restart(&panel->anim);
    ClockPanel_Rewind(panel);
    CatchPanelText_Destruct(&panel->minutes_text);
    CatchPanelText_Destruct(&panel->hour_text);
    CatchPanelText_Destruct(&panel->day_text);
    CatchPanelText_Destruct(&panel->month_text);
    CellAnim_Destruct(&panel->anim);
    ScreenSprite_DestructBase(&panel->base);
}

/* func_0208de9c (vtable slot 1): destructed and freed. */
ClockPanel *ClockPanel_Delete(ClockPanel *panel)
{
    clock_panel_destruct(panel);
    Heap_OperatorDeleteB(panel);
    return panel;
}
CLEAN_AS(func_0208de9c, ClockPanel_Delete)

/* func_0208def4 (vtable slot 0): the destructor. */
ClockPanel *ClockPanel_Destruct(ClockPanel *panel)
{
    clock_panel_destruct(panel);
    return panel;
}
CLEAN_AS(func_0208def4, ClockPanel_Destruct)

/* func_0208df44: the constructor (of the member of data_021d3258, at start-up): hidden, no
 * boxes, nothing to redraw, not shown, the shift reset, the date and time shown 0. */
ClockPanel *ClockPanel_Construct(ClockPanel *panel)
{
    ScreenSprite_Construct(&panel->base);
    panel->base.vtable = data_020e226c;
    CellAnim_Construct(&panel->anim);
    panel->state = CLOCK_PANEL_HIDDEN;
    panel->wait = 0;
    panel->month_box = NULL;
    panel->day_box = NULL;
    panel->weekday_box = NULL;
    panel->am_pm_box = NULL;
    panel->hour_box = NULL;
    panel->minutes_box = NULL;
    panel->colon_box = NULL;
    panel->blink = 0;
    panel->month_changed = 0;
    panel->day_changed = 0;
    panel->weekday_changed = 0;
    panel->am_pm_changed = 0;
    panel->hour_changed = 0;
    panel->minutes_changed = 0;
    panel->shown = 0;
    panel->in_room = 0;
    panel->shift = 0;
    panel->shift_target = 0;
    panel->shift_speed = 0;
    panel->shift_wait = -1;
    panel->weekday = 0;
    func_0208e024(&panel->month_text);
    func_0208e024(&panel->day_text);
    func_0208e024(&panel->hour_text);
    func_0208e024(&panel->minutes_text);
    panel->day_month[0] = 0;
    panel->day_month[1] = 0;
    panel->time.minute = 0;
    panel->time.hour = 0;
    return panel;
}
CLEAN_AS(func_0208df44, ClockPanel_Construct)
