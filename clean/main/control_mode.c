/* Buttons or touch screen (control_mode.h). */
#include "control_mode.h"

#include "clean.h"
#include "state_flags.h"

#define FLAG_BUTTONS 0x02

extern int func_0208ffac(void);  /* data_021d369c's mode is 1 (buttons) */
extern void func_0208ffcc(void); /* set it to 1 */
extern void func_0208ffc0(void); /* set it to 2 */

/* func_0206fe38: set both records again from data_021d369c's. */
void ControlMode_Reapply(void)
{
    if (func_0208ffac() != 0) {
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
    func_0208ffcc();
}
CLEAN_AS(func_0206fe7c, ControlMode_UseButtons)

/* func_0206fe90 */
void ControlMode_UseTouch(void)
{
    StateFlags_Clear(FLAG_BUTTONS);
    func_0208ffc0();
}
CLEAN_AS(func_0206fe90, ControlMode_UseTouch)
