/* The second screen panel (screen_panels.h, the member at 0xe0 of data_021d3258, so the object
 * at data_021d3338): a sprite (vtable data_020e2218, 0xe4 bytes, derived from main's screen
 * sprite base, screen_sprite.h) that shows a countdown, in minutes and seconds, and two counts:
 * the fish (func_0208d09c, when this console's player lands one) and the insects
 * (func_0208d07c, when this console's player catches one) caught while it runs.
 *
 * func_0208d0bc starts the countdown with one of the times of data_020d0a58 (3, 5, 10 or 15
 * minutes; the player messages of a link choose it, the gatekeeper's talks stop it) and clears
 * the counts. Each frame the time left is taken from the RTC (CatchPanel_UpdateTime); during
 * the last ten seconds each second beeps, and at 0 the countdown stops with a sound and the
 * field label's notice 3, the panel staying for 600 more frames (`linger`).
 *
 * The numbers are drawn into four text boxes in VRAM (other tiles in a room), made when the
 * panel appears and freed once it has hidden; a number's box is redrawn when it changed.
 *
 * Its states (CatchPanelState), stepped by its update (func_0208d174): hidden, until it should
 * show; appearing, until its animation is done; shown, while it should; hiding, until its
 * animation is done. It should show while `shown` is set, unless an event runs with no overlay
 * group owner, or with one while state flag 4 is clear or its value below 1.0. It is drawn 20
 * pixels higher, eased, while this system's quick message balloon is out and it should show. */
#ifndef CLEAN_MAIN_CATCH_PANEL_H
#define CLEAN_MAIN_CATCH_PANEL_H

#include "calendar.h"    /* DateTime */
#include "label_box.h"   /* LabelBox */
#include "screen_icon.h" /* CellAnim */
#include "screen_sprite.h"
#include "text_label.h" /* TextVtable */
#include "types.h"

enum CatchPanelState {
    CATCH_PANEL_HIDDEN = 0,
    CATCH_PANEL_APPEARING = 1,
    CATCH_PANEL_SHOWN = 2,
    CATCH_PANEL_HIDING = 3,
};

/* A number's characters (vtable data_020e21e4, 0x1c bytes): a text of the label base
 * (text_label.h) with room for 10 characters. */
#define CATCH_PANEL_TEXT_CAPACITY 10
typedef struct CatchPanelText {
    const TextVtable *vtable;
    u8 base_04[0x0e];
    char text[CATCH_PANEL_TEXT_CAPACITY]; /* 0x12 */
} CatchPanelText;

typedef struct CatchPanel {
    ScreenSprite base;           /* vtable data_020e2218 */
    CellAnim anim;               /* 0x0c: appearing and hiding, entries of data_020d5b3c */
    int state;                   /* 0x20: CatchPanelState */
    LabelBox *minutes_box;       /* 0x24: the boxes of the four numbers, or NULL */
    LabelBox *seconds_box;       /* 0x28 */
    LabelBox *fish_box;          /* 0x2c */
    LabelBox *insects_box;       /* 0x30 */
    CatchPanelText minutes_text; /* 0x34 */
    CatchPanelText seconds_text; /* 0x50 */
    CatchPanelText fish_text;    /* 0x6c */
    CatchPanelText insects_text; /* 0x88 */
    u8 minutes_changed;          /* 0xa4: the number's box is to be redrawn */
    u8 seconds_changed;          /* 0xa5 */
    u8 fish_changed;             /* 0xa6 */
    u8 insects_changed;          /* 0xa7 */
    u8 shown;                    /* 0xa8: the panel is asked to be shown */
    u8 in_room;                  /* 0xa9: shown in a room (data_020e54a8 was 1) */
    u8 pad_aa[2];
    int fish;         /* 0xac */
    int insects;      /* 0xb0 */
    int time_limit;   /* 0xb4: the index into data_020d0a58, 0 when stopped */
    DateTime end;     /* 0xb8: when the countdown ends */
    DateTime left;    /* 0xc0: the time left shown */
    int linger;       /* 0xc8: frames the panel stays after the countdown ended */
    int shift;        /* 0xcc: 20.12 pixels lower, eased toward `shift_target` */
    int shift_target; /* 0xd0: 0, or 20 pixels higher while the balloon is out */
    int shift_speed;  /* 0xd4: the ease's largest step */
    int shift_wait;   /* 0xd8: frames a new target has waited, -1 for none since the reset */
    u32 beep_tick[2]; /* 0xdc: the OS tick of the last second shown, low word first */
} CatchPanel;

void CatchPanel_ResetShift(CatchPanel *panel);
void CatchPanel_UpdateShift(CatchPanel *panel);
void CatchPanel_UpdateTime(CatchPanel *panel);
void CatchPanel_RedrawInsects(CatchPanel *panel);
void CatchPanel_RedrawFish(CatchPanel *panel);
void CatchPanel_RedrawSeconds(CatchPanel *panel);
void CatchPanel_RedrawMinutes(CatchPanel *panel);
void CatchPanel_RedrawNumbers(CatchPanel *panel);
void CatchPanel_FreeTextBoxes(CatchPanel *panel);
void CatchPanel_OpenInsectsBox(CatchPanel *panel);
void CatchPanel_OpenFishBox(CatchPanel *panel);
void CatchPanel_OpenSecondsBox(CatchPanel *panel);
void CatchPanel_OpenMinutesBox(CatchPanel *panel);
void CatchPanel_OpenTextBoxes(CatchPanel *panel);
u8 CatchPanel_ShouldShow(CatchPanel *panel);
void CatchPanel_StepHiding(CatchPanel *panel);
void CatchPanel_EnterHiding(CatchPanel *panel);
void CatchPanel_StepShown(CatchPanel *panel);
void CatchPanel_EnterShown(CatchPanel *panel);
void CatchPanel_StepAppearing(CatchPanel *panel);
void CatchPanel_EnterAppearing(CatchPanel *panel);
void CatchPanel_StepHidden(CatchPanel *panel);
void CatchPanel_EnterHidden(CatchPanel *panel);
int CatchPanel_IsIdle(CatchPanel *panel);
int CatchPanel_IsHidden(CatchPanel *panel);

void CatchPanel_Hide(CatchPanel *panel);
void CatchPanel_Show(CatchPanel *panel);
void CatchPanel_CountInsect(CatchPanel *panel);
void CatchPanel_CountFish(CatchPanel *panel);
void CatchPanel_Start(CatchPanel *panel, int time_limit, int quiet);
unsigned int CatchPanel_IsStopped(CatchPanel *panel);
int CatchPanel_CallDraw(CatchPanel *panel);
void CatchPanel_CallUpdate(CatchPanel *panel);
void CatchPanel_Rewind(CatchPanel *panel);
void CatchPanel_Reset(CatchPanel *panel);
void CatchPanel_Update(CatchPanel *panel);
void CatchPanel_Draw(CatchPanel *panel);
CatchPanel *CatchPanel_Delete(CatchPanel *panel);
CatchPanel *CatchPanel_Destruct(CatchPanel *panel);
CatchPanel *CatchPanel_Construct(CatchPanel *panel);

/* The number text's class (vtable data_020e21e4), the clock panel's (clock_panel.h) too. */
int CatchPanelText_Chars(CatchPanelText *text);
int CatchPanelText_Capacity(CatchPanelText *text);
CatchPanelText *CatchPanelText_Delete(CatchPanelText *text);
CatchPanelText *CatchPanelText_Destruct(CatchPanelText *text);
void *CatchPanelText_Construct(CatchPanelText *text);

#endif
