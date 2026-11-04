/* The third screen panel (screen_panels.h, the member at 0x1c4 of data_021d3258): a tab
 * (vtable data_020e2234, 0x100 bytes, derived from main's screen sprite base, screen_sprite.h)
 * that opens a menu window of its own (the camera grid, camera_grid.h: the member at 0x28, 0xd8 bytes) by X, or by a tap at
 * the touch screen's top right (x 200 to 231, y 0 to 15), and closes it by X, B, a tap there,
 * or once state flag 0x80 asks the menu to close (StateFlags_MenuCloseAsked).
 *
 * A press asks main's event queue for an event of kind 10 (EventQueue_RequestKind10); the
 * window opens once that event runs, and the event is finished when the window has closed.
 * While the window is open, a button press switches the input to the buttons and a tap to the
 * touch screen (the byte at data_021f43f4, 1 for buttons), and the control mode follows.
 *
 * Its states (CameraTabState), stepped through a table of member functions by its update:
 * hidden; appearing (until its animation is done); shown, while the scene allows the tab; the
 * window opening; open; the window closing; hiding (until its animation is done). The tab is
 * allowed while `shown` is set, no event runs and the scene (func_020960d8(4)) is not 8 to 15
 * or 0x24 to 0x2c. */
#ifndef CLEAN_MAIN_CAMERA_TAB_H
#define CLEAN_MAIN_CAMERA_TAB_H

#include "screen_icon.h" /* CellAnim */
#include "screen_sprite.h"
#include "types.h"

enum CameraTabState {
    CAMERA_TAB_HIDDEN = 0,
    CAMERA_TAB_APPEARING = 1,
    CAMERA_TAB_SHOWN = 2,
    CAMERA_TAB_OPENING = 3,
    CAMERA_TAB_OPEN = 4,
    CAMERA_TAB_CLOSING = 5,
    CAMERA_TAB_HIDING = 6,
};

typedef struct CameraTab {
    ScreenSprite base; /* vtable data_020e2234 */
    CellAnim anim;     /* 0x0c: data_020d5c3c appearing, data_020d5c44 shown (still) and hiding,
                        * data_020d5c4c open */
    int state;         /* 0x20: CameraTabState */
    u8 grid_open;      /* 0x24: the menu is open (from the press until the window closed) */
    u8 by_button;      /* 0x25: the last press was a button's, not a tap */
    u8 shown;          /* 0x26: the tab is asked to be shown */
    u8 pad_27;
    u8 window[0xd8]; /* 0x28: the menu window; its state at 0xc0 is 0 closed, 2 open */
} CameraTab;

void CameraTab_StepHiding(CameraTab *tab);
void CameraTab_EnterHiding(CameraTab *tab);
void CameraTab_StepClosing(CameraTab *tab);
void CameraTab_EnterClosing(CameraTab *tab);
void CameraTab_StepOpen(CameraTab *tab);
void CameraTab_EnterOpen(CameraTab *tab);
void CameraTab_StepOpening(CameraTab *tab);
void CameraTab_EnterOpening(CameraTab *tab);
void CameraTab_StepShown(CameraTab *tab);
void CameraTab_EnterShown(CameraTab *tab);
void CameraTab_StepAppearing(CameraTab *tab);
void CameraTab_EnterAppearing(CameraTab *tab);
void CameraTab_StepHidden(CameraTab *tab);
void CameraTab_EnterHidden(CameraTab *tab);
void CameraTab_FollowInput(CameraTab *tab);
int CameraTab_Pressed(CameraTab *tab, int with_b);
int CameraTab_IsAllowed(CameraTab *tab);
int CameraTab_IsSettled(CameraTab *tab);
void CameraTab_Hide(CameraTab *tab);
void CameraTab_Show(CameraTab *tab);
void CameraTab_CallDraw(CameraTab *tab);
void CameraTab_Update(CameraTab *tab);
void CameraTab_Rewind(CameraTab *tab);
void CameraTab_Reset(CameraTab *tab);
void CameraTab_Step(CameraTab *tab);
void CameraTab_Draw(CameraTab *tab);
CameraTab *CameraTab_Delete(CameraTab *tab);
CameraTab *CameraTab_Destruct(CameraTab *tab);
CameraTab *CameraTab_Construct(CameraTab *tab);

#endif
