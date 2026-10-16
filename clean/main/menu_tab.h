/* The third screen panel (screen_panels.h, the member at 0x1c4 of data_021d3258): a tab
 * (vtable data_020e2234, 0x100 bytes, derived from main's screen sprite base, screen_sprite.h)
 * that opens a menu window of its own (the member at 0x28, 0xd8 bytes) by X, or by a tap at
 * the touch screen's top right (x 200 to 231, y 0 to 15), and closes it by X, B, a tap there,
 * or once state flag 0x80 asks the menu to close (func_0206f56c).
 *
 * A press asks main's event queue for an event of kind 10 (EventQueue_RequestKind10); the
 * window opens once that event runs, and the event is finished when the window has closed.
 * While the window is open, a button press switches the input to the buttons and a tap to the
 * touch screen (the byte at data_021f43f4, 1 for buttons), and the control mode follows.
 *
 * Its states (MenuTabState), stepped through a table of member functions by its update:
 * hidden; appearing (until its animation is done); shown, while the scene allows the tab; the
 * window opening; open; the window closing; hiding (until its animation is done). The tab is
 * allowed while `shown` is set, no event runs and the scene (func_020960d8(4)) is not 8 to 15
 * or 0x24 to 0x2c. */
#ifndef CLEAN_MAIN_MENU_TAB_H
#define CLEAN_MAIN_MENU_TAB_H

#include "screen_icon.h" /* CellAnim */
#include "screen_sprite.h"
#include "types.h"

enum MenuTabState {
    MENU_TAB_HIDDEN = 0,
    MENU_TAB_APPEARING = 1,
    MENU_TAB_SHOWN = 2,
    MENU_TAB_OPENING = 3,
    MENU_TAB_OPEN = 4,
    MENU_TAB_CLOSING = 5,
    MENU_TAB_HIDING = 6,
};

typedef struct MenuTab {
    ScreenSprite base; /* vtable data_020e2234 */
    CellAnim anim;     /* 0x0c: data_020d5c3c appearing, data_020d5c44 shown (still) and hiding,
                        * data_020d5c4c open */
    int state;         /* 0x20: MenuTabState */
    u8 open;           /* 0x24: the menu is open (from the press until the window closed) */
    u8 by_button;      /* 0x25: the last press was a button's, not a tap */
    u8 shown;          /* 0x26: the tab is asked to be shown */
    u8 pad_27;
    u8 window[0xd8]; /* 0x28: the menu window; its state at 0xc0 is 0 closed, 2 open */
} MenuTab;

void MenuTab_StepHiding(MenuTab *tab);
void MenuTab_EnterHiding(MenuTab *tab);
void MenuTab_StepClosing(MenuTab *tab);
void MenuTab_EnterClosing(MenuTab *tab);
void MenuTab_StepOpen(MenuTab *tab);
void MenuTab_EnterOpen(MenuTab *tab);
void MenuTab_StepOpening(MenuTab *tab);
void MenuTab_EnterOpening(MenuTab *tab);
void MenuTab_StepShown(MenuTab *tab);
void MenuTab_EnterShown(MenuTab *tab);
void MenuTab_StepAppearing(MenuTab *tab);
void MenuTab_EnterAppearing(MenuTab *tab);
void MenuTab_StepHidden(MenuTab *tab);
void MenuTab_EnterHidden(MenuTab *tab);
void MenuTab_FollowInput(MenuTab *tab);
int MenuTab_Pressed(MenuTab *tab, int with_b);
int MenuTab_IsAllowed(MenuTab *tab);
int MenuTab_IsSettled(MenuTab *tab);
void MenuTab_Hide(MenuTab *tab);
void MenuTab_Show(MenuTab *tab);
void MenuTab_CallDraw(MenuTab *tab);
void MenuTab_Update(MenuTab *tab);
void MenuTab_Rewind(MenuTab *tab);
void MenuTab_Reset(MenuTab *tab);
void MenuTab_Step(MenuTab *tab);
void MenuTab_Draw(MenuTab *tab);
MenuTab *MenuTab_Delete(MenuTab *tab);
MenuTab *MenuTab_Destruct(MenuTab *tab);
MenuTab *MenuTab_Construct(MenuTab *tab);

#endif
