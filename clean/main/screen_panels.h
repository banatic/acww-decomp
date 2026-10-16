/* The four panels main shows over the screen (the object at data_021d3258), one at a time, with
 * the window graphics of /a_mes/ that go with each (a_mes_obj.h). It is one of the screen
 * indicators the screen indicators process draws and updates (screen_indicators.h).
 *
 * Each panel is shown or hidden by a flag of its own and is settled once its timer (its word
 * 0x20) has run out; a panel being hidden is waited for before the next one is shown. Which
 * panel is shown follows the current scene's style (AMesObj_Style):
 * - style 1: the first panel, or the second while the second has something to show (it is not
 *   idle); the a_mes window of the scene's kind, or of kind 1 for the second panel;
 * - style 2: the third panel; its extra characters follow the control mode (buttons or touch);
 * - style 3: the fourth panel;
 * - others: none.
 * While a request is set (ScreenPanels_Request, called from overlays 4, 53, 70, 71 and 73), the
 * panel shown is hidden and the fourth panel shown instead, with the a_mes window of kind 3.
 *
 * In a room (data_020e54a8 is 1) of a scene with a style, the third and fourth panels' states
 * also swap the first and second panels as in style 1 (ScreenPanels_StepRoom). */
#ifndef CLEAN_MAIN_SCREEN_PANELS_H
#define CLEAN_MAIN_SCREEN_PANELS_H

#include "types.h"

/* What is shown (ScreenPanels.state). */
enum ScreenPanelsState {
    SCREEN_PANELS_NONE = 0,
    SCREEN_PANELS_FIRST = 1,
    SCREEN_PANELS_SECOND = 2,
    SCREEN_PANELS_THIRD = 3,
    SCREEN_PANELS_FOURTH = 4,
    SCREEN_PANELS_REQUESTED = 5, /* the fourth panel, on request */
};

/* data_021d3258 */
typedef struct ScreenPanels {
    u32 unk_00;
    int state;       /* 0x04: ScreenPanelsState */
    u8 first[0xd8];  /* 0x08: shown while byte 0x4e is set */
    u8 second[0xe4]; /* 0xe0 (data_021d3338): shown while byte 0xa8 is set */
    u8 third[0x100]; /* 0x1c4: shown while byte 0x26 is set */
    u8 fourth[0x84]; /* 0x2c4 (data_021d351c): shown while byte 0x80 is set */
    u8 request;      /* 0x348: the fourth panel asked for */
    u8 request_2;    /* 0x349: the same, set by nothing found */
    u8 touch;        /* 0x34a: the third panel's extra characters are touch's */
    u8 pad_34b;
} ScreenPanels;

void ScreenPanels_FollowControlMode(ScreenPanels *panels);
void ScreenPanels_SelectState(ScreenPanels *panels);
void ScreenPanels_StepRoom(ScreenPanels *panels);
void ScreenPanels_StepRequested(ScreenPanels *panels);
void ScreenPanels_EnterRequested(ScreenPanels *panels);
void ScreenPanels_StepFourth(ScreenPanels *panels);
void ScreenPanels_EnterFourth(ScreenPanels *panels);
void ScreenPanels_StepThird(ScreenPanels *panels);
void ScreenPanels_EnterThird(ScreenPanels *panels);
void ScreenPanels_StepSecond(ScreenPanels *panels);
void ScreenPanels_EnterSecond(ScreenPanels *panels);
void ScreenPanels_StepFirst(ScreenPanels *panels);
void ScreenPanels_EnterFirst(ScreenPanels *panels);
void ScreenPanels_StepNone(ScreenPanels *panels);
void ScreenPanels_EnterNone(ScreenPanels *panels);
void ScreenPanels_Draw(ScreenPanels *panels);
void ScreenPanels_Update(ScreenPanels *panels);
void ScreenPanels_Rewind(ScreenPanels *panels);
void ScreenPanels_Reset(ScreenPanels *panels);
int ScreenPanels_FourthPanel(void);
int ScreenPanels_SecondPanel(void);
void ScreenPanels_ClearRequest2(void);
void ScreenPanels_ClearRequest(unsigned int unused);
void ScreenPanels_Request(void);

/* The third panel is the menu tab (menu_tab.h), the fourth the bells panel (bells_panel.h). */
void ScreenPanels_DrawGlobal(void);
void ScreenPanels_UpdateGlobal(void);
void ScreenPanels_RewindGlobal(void);
void ScreenPanels_ResetGlobal(void);
ScreenPanels *ScreenPanels_Delete(ScreenPanels *panels);
ScreenPanels *ScreenPanels_Destruct(ScreenPanels *panels);
ScreenPanels *ScreenPanels_Construct(ScreenPanels *panels);

#endif
