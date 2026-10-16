/* Whether the player is controlling the game with the buttons or with the touch screen. The
 * callers switch to buttons when a button is pressed (func_ov002_02208054, and the menu
 * buttons in OverlayTask_Update) and to touch when the pen goes down (func_ov002_02208014).
 * The choice is kept twice: as state flag 2 (state_flags.h) and as a word of the object at
 * data_021d369c (1 for buttons, 2 for touch), set and read through its own functions. */
#ifndef CLEAN_MAIN_CONTROL_MODE_H
#define CLEAN_MAIN_CONTROL_MODE_H

#include "types.h"

void ControlMode_Reapply(void);
void ControlMode_UseButtons(void);
void ControlMode_UseTouch(void);

#endif
