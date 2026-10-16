/* Which input the menus follow (menu_input.h). */
#include "menu_input.h"

#include "autoload_2/input.h"
#include "clean.h"

/* The pad's buttons. */
#define PAD_B 0x0002
#define PAD_UP 0x0040
#define PAD_DOWN 0x0080

extern u8 data_021f43f0; /* a control is held */
extern u8 data_021f43f4; /* the menus follow the buttons (else the touch screen) */
extern PadState data_021fbe40;

/* The game's control mode: whether it is the buttons, and set to the buttons or to touch. */
extern int func_0208ffac(void);
extern void func_0208ffcc(void);
extern void func_0208ffc0(void);

/* func_020a7dac: whether a control is held with the buttons. */
int MenuInput_HeldByButtons(void)
{
    return data_021f43f0 != 0 && data_021f43f4 != 0;
}
CLEAN_AS(func_020a7dac, MenuInput_HeldByButtons)

/* func_020a7dcc: whether a control is held with the touch screen. */
int MenuInput_HeldByTouch(void)
{
    return data_021f43f0 != 0 && data_021f43f4 == 0;
}
CLEAN_AS(func_020a7dcc, MenuInput_HeldByTouch)

/* func_020a7dec: the game's control mode set to the input the menus follow. */
void MenuInput_ApplyMode(void)
{
    if (data_021f43f4 != 0) {
        func_0208ffcc();
    } else {
        func_0208ffc0();
    }
}
CLEAN_AS(func_020a7dec, MenuInput_ApplyMode)

/* func_020a7e0c: the menus follow the game's control mode. */
void MenuInput_TakeMode(void)
{
    data_021f43f4 = func_0208ffac() != 0;
}
CLEAN_AS(func_020a7e0c, MenuInput_TakeMode)

/* func_020a7e30: nothing held, the touch screen followed. */
void MenuInput_Reset(void)
{
    data_021f43f0 = 0;
    data_021f43f4 = 0;
}
CLEAN_AS(func_020a7e30, MenuInput_Reset)

/* func_020a7e44 */
u8 MenuInput_UsesButtons(void)
{
    return data_021f43f4;
}
CLEAN_AS(func_020a7e44, MenuInput_UsesButtons)

/* func_020a7e50 */
int MenuInput_UsesTouch(void)
{
    return data_021f43f4 == 0;
}
CLEAN_AS(func_020a7e50, MenuInput_UsesTouch)

/* func_020a7e64 */
void MenuInput_UseButtons(void)
{
    data_021f43f4 = 1;
}
CLEAN_AS(func_020a7e64, MenuInput_UseButtons)

/* func_020a7e70 */
void MenuInput_UseTouch(void)
{
    data_021f43f4 = 0;
}
CLEAN_AS(func_020a7e70, MenuInput_UseTouch)

/* func_020a7e7c: the control let go. */
void MenuInput_Release(void)
{
    data_021f43f0 = 0;
}
CLEAN_AS(func_020a7e7c, MenuInput_Release)

/* func_020a7e88: a control taken. */
void MenuInput_Hold(void)
{
    data_021f43f0 = 1;
}
CLEAN_AS(func_020a7e88, MenuInput_Hold)

/* Whether the pad's `button` is held, unless the touch screen holds a control. */
static int menu_input_button_held(u16 button)
{
    return !MenuInput_HeldByTouch() && (data_021fbe40.held & button) != 0;
}

/* func_020a7e94 */
int MenuInput_DownHeld(void)
{
    return menu_input_button_held(PAD_DOWN);
}
CLEAN_AS(func_020a7e94, MenuInput_DownHeld)

/* func_020a7ebc */
int MenuInput_UpHeld(void)
{
    return menu_input_button_held(PAD_UP);
}
CLEAN_AS(func_020a7ebc, MenuInput_UpHeld)

/* func_020a7ee4 */
int MenuInput_BHeld(void)
{
    return menu_input_button_held(PAD_B);
}
CLEAN_AS(func_020a7ee4, MenuInput_BHeld)
