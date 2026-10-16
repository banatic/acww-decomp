/* The first screen panel (screen_panels.h, the member at 0x08 of data_021d3258): a sprite
 * (vtable data_020e226c, 0xd8 bytes, derived from main's screen sprite base, screen_sprite.h)
 * that shows the clock: the month and the day, the weekday, AM or PM, the hour (of 12) and the
 * minutes, with a colon between them that blinks (drawn for 12 frames, cleared for 8).
 *
 * Each frame the date, the time and the weekday are read (ClockPanel_ReadClock) and a number
 * whose value changed is redrawn. The seven parts are text boxes in VRAM (other tiles in a
 * room), made when the panel appears and freed once it has hidden. The weekday is drawn as one
 * of the font's weekday characters, and the whole panel in palette 15 on Sundays, 9 otherwise.
 *
 * Its states (ClockPanelState), stepped by its update (ClockPanel_Update): hidden, until it has
 * been asked to show for `wait` frames; appearing, until its animation is done; shown, while it
 * should; hiding, until its animation is done. It should show while `shown` is set, unless an
 * event runs with no overlay group owner, or no owner while player 4 is not in session state 2, or
 * an event with an owner while state flag 4 is clear or its value below 1.0. The wait is set while
 * it should not: 30 frames after the first two cases, 1 after the third, 10 while `shown` is
 * clear. It is drawn 20 pixels higher, eased, while this system's quick message balloon is out and
 * it should show. */
#ifndef CLEAN_MAIN_CLOCK_PANEL_H
#define CLEAN_MAIN_CLOCK_PANEL_H

#include "calendar.h"    /* Time */
#include "catch_panel.h" /* CatchPanelText */
#include "label_box.h"   /* LabelBox */
#include "screen_icon.h" /* CellAnim */
#include "screen_sprite.h"
#include "types.h"

enum ClockPanelState {
    CLOCK_PANEL_HIDDEN = 0,
    CLOCK_PANEL_APPEARING = 1,
    CLOCK_PANEL_SHOWN = 2,
    CLOCK_PANEL_HIDING = 3,
};

typedef struct ClockPanel {
    ScreenSprite base;           /* vtable data_020e226c */
    CellAnim anim;               /* 0x0c: appearing and hiding, entries of data_020d5b3c */
    int state;                   /* 0x20: ClockPanelState */
    int wait;                    /* 0x24: frames left to be asked to show before appearing */
    LabelBox *month_box;         /* 0x28: the boxes of the seven parts, or NULL */
    LabelBox *day_box;           /* 0x2c */
    LabelBox *weekday_box;       /* 0x30 */
    LabelBox *am_pm_box;         /* 0x34 */
    LabelBox *hour_box;          /* 0x38 */
    LabelBox *minutes_box;       /* 0x3c */
    LabelBox *colon_box;         /* 0x40 */
    int blink;                   /* 0x44: frames until the colon is drawn again */
    u8 month_changed;            /* 0x48: the part's box is to be redrawn */
    u8 day_changed;              /* 0x49 */
    u8 weekday_changed;          /* 0x4a */
    u8 am_pm_changed;            /* 0x4b */
    u8 hour_changed;             /* 0x4c */
    u8 minutes_changed;          /* 0x4d */
    u8 shown;                    /* 0x4e: the panel is asked to be shown */
    u8 in_room;                  /* 0x4f: shown in a room (data_020e54a8 was 1) */
    int shift;                   /* 0x50: 20.12 pixels lower, eased toward `shift_target` */
    int shift_target;            /* 0x54: 0, or 20 pixels higher while the balloon is out */
    int shift_speed;             /* 0x58: the ease's largest step */
    int shift_wait;              /* 0x5c: frames a new target has waited, -1 for none since the reset */
    u8 day_month[2];             /* 0x60: the day and the month shown (Clock_GetDayMonth) */
    Time time;                   /* 0x62: the time shown */
    u32 weekday;                 /* 0x64: the weekday shown, 0 = Sunday */
    CatchPanelText month_text;   /* 0x68 */
    CatchPanelText day_text;     /* 0x84 */
    CatchPanelText hour_text;    /* 0xa0 */
    CatchPanelText minutes_text; /* 0xbc */
} ClockPanel;

void ClockPanel_ResetShift(ClockPanel *panel);
void ClockPanel_UpdateShift(ClockPanel *panel);
void ClockPanel_ReadClock(ClockPanel *panel);
void ClockPanel_BlinkColon(ClockPanel *panel);
void ClockPanel_RedrawMinutes(ClockPanel *panel);
void ClockPanel_RedrawHour(ClockPanel *panel);
void ClockPanel_RedrawAmPm(ClockPanel *panel);
void ClockPanel_RedrawWeekday(ClockPanel *panel);
void ClockPanel_RedrawDay(ClockPanel *panel);
void ClockPanel_RedrawMonth(ClockPanel *panel);
void ClockPanel_RedrawParts(ClockPanel *panel);
void ClockPanel_FreeTextBoxes(ClockPanel *panel);
void ClockPanel_OpenColonBox(ClockPanel *panel);
void ClockPanel_OpenMinutesBox(ClockPanel *panel);
void ClockPanel_OpenHourBox(ClockPanel *panel);
void ClockPanel_OpenAmPmBox(ClockPanel *panel);
void ClockPanel_OpenWeekdayBox(ClockPanel *panel);
void ClockPanel_OpenDayBox(ClockPanel *panel);
void ClockPanel_OpenMonthBox(ClockPanel *panel);
void ClockPanel_OpenTextBoxes(ClockPanel *panel);
int ClockPanel_ShouldShow(ClockPanel *panel);
void ClockPanel_StepHiding(ClockPanel *panel);
void ClockPanel_EnterHiding(ClockPanel *panel);
void ClockPanel_StepShown(ClockPanel *panel);
void ClockPanel_EnterShown(ClockPanel *panel);
void ClockPanel_StepAppearing(ClockPanel *panel);
void ClockPanel_EnterAppearing(ClockPanel *panel);
void ClockPanel_StepHidden(ClockPanel *panel);
void ClockPanel_EnterHidden(ClockPanel *panel);
int ClockPanel_IsHidden(ClockPanel *panel);
void ClockPanel_Hide(ClockPanel *panel);
void ClockPanel_Show(ClockPanel *panel);
void ClockPanel_CallDraw(ClockPanel *panel);
void *ClockPanel_CallUpdate(ClockPanel *panel);
void ClockPanel_Rewind(ClockPanel *panel);
void ClockPanel_Reset(ClockPanel *panel);
void ClockPanel_Update(ClockPanel *panel);
void ClockPanel_Draw(ClockPanel *panel);
ClockPanel *ClockPanel_Delete(ClockPanel *panel);
ClockPanel *ClockPanel_Destruct(ClockPanel *panel);
ClockPanel *ClockPanel_Construct(ClockPanel *panel);

#endif
