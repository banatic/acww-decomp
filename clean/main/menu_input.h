/* Which input the menus and choices follow, the buttons or the touch screen, and whether one of
 * their controls is being held (set by func_020aaabc when a control is taken, cleared when it
 * is let go). While a control is held with one input, the other is ignored: the pad's buttons
 * read as up while the touch screen holds it, the touch screen as untouched while the buttons
 * do. The choice is taken from and handed to the game's control mode (control_mode.h). */
#ifndef CLEAN_MAIN_MENU_INPUT_H
#define CLEAN_MAIN_MENU_INPUT_H

#include "types.h"

int MenuInput_HeldByButtons(void);
int MenuInput_HeldByTouch(void);
void MenuInput_ApplyMode(void);
void MenuInput_TakeMode(void);
void MenuInput_Reset(void);
u8 MenuInput_UsesButtons(void);
int MenuInput_UsesTouch(void);
void MenuInput_UseButtons(void);
void MenuInput_UseTouch(void);
void MenuInput_Release(void);
void MenuInput_Hold(void);
int MenuInput_DownHeld(void);
int MenuInput_UpHeld(void);
int MenuInput_BHeld(void);

int MenuInput_AHeld(void);
int MenuInput_StartPressed(void);
int MenuInput_DownPressed(void);
int MenuInput_UpPressed(void);
int MenuInput_BPressed(void);
int MenuInput_APressed(void);
int MenuInput_AnyPressed(void);
int MenuInput_TouchPosition(int *x, int *y);
int MenuInput_TouchPressedAt(int *x, int *y);
int MenuInput_TouchPressedIn(int left, int right, int top, int bottom);
int MenuInput_TouchPressed(void);

#endif
