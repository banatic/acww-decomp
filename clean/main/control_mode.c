/* Buttons or touch screen (control_mode.h). */
#include "control_mode.h"

#include "clean.h"
#include "state_flags.h"
#include "control_mode_icon.h"

#define FLAG_BUTTONS 0x02

/* func_0206fe38: set both records again from data_021d369c's. */
void ControlMode_Reapply(void)
{
    if (ControlModeIcon_IsButtons() != 0) {
        ControlMode_UseButtons();
    } else {
        ControlMode_UseTouch();
    }
}
CLEAN_AS(func_0206fe38, ControlMode_Reapply)

/* func_0206fe7c */
void ControlMode_UseButtons(void)
{
    StateFlags_Set(FLAG_BUTTONS);
    ControlModeIcon_SetButtons();
}
CLEAN_AS(func_0206fe7c, ControlMode_UseButtons)

/* func_0206fe90 */
void ControlMode_UseTouch(void)
{
    StateFlags_Clear(FLAG_BUTTONS);
    ControlModeIcon_SetTouch();
}
CLEAN_AS(func_0206fe90, ControlMode_UseTouch)
