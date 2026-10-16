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

/* The pad's buttons read by the queries below. */
#define MENU_INPUT_PAD_A 0x0001
#define MENU_INPUT_PAD_START 0x0008
/* A to L, X and Y: every button but the debug button and the lid. */
#define MENU_INPUT_PAD_ANY 0x0fff

/* func_020a7f0c */
int MenuInput_AHeld(void)
{
    return menu_input_button_held(MENU_INPUT_PAD_A);
}
CLEAN_AS(func_020a7f0c, MenuInput_AHeld)

/* Whether the pad's `button` went down this frame, unless the touch screen holds a control. */
static int menu_input_button_pressed(u16 button)
{
    return !MenuInput_HeldByTouch() && (data_021fbe40.pressed & button) != 0;
}

/* func_020a7f34 */
int MenuInput_StartPressed(void)
{
    return menu_input_button_pressed(MENU_INPUT_PAD_START);
}
CLEAN_AS(func_020a7f34, MenuInput_StartPressed)

/* func_020a7f5c */
int MenuInput_DownPressed(void)
{
    return menu_input_button_pressed(PAD_DOWN);
}
CLEAN_AS(func_020a7f5c, MenuInput_DownPressed)

/* func_020a7f84 */
int MenuInput_UpPressed(void)
{
    return menu_input_button_pressed(PAD_UP);
}
CLEAN_AS(func_020a7f84, MenuInput_UpPressed)

/* func_020a7fac */
int MenuInput_BPressed(void)
{
    return menu_input_button_pressed(PAD_B);
}
CLEAN_AS(func_020a7fac, MenuInput_BPressed)

/* func_020a7fd4 */
int MenuInput_APressed(void)
{
    return menu_input_button_pressed(MENU_INPUT_PAD_A);
}
CLEAN_AS(func_020a7fd4, MenuInput_APressed)

/* func_020a7ffc: whether any button went down this frame. */
int MenuInput_AnyPressed(void)
{
    return menu_input_button_pressed(MENU_INPUT_PAD_ANY);
}
CLEAN_AS(func_020a7ffc, MenuInput_AnyPressed)

/* The touch as the menus keep it, in pixels (a byte each; func_020b9280 sets them each
 * frame from the touch screen). */
extern u8 data_021f6c58; /* x, while the pen is down */
extern u8 data_021f6c54; /* y, while the pen is down */
extern u8 data_021f6c60; /* x where the pen last went down */
extern u8 data_021f6c5c; /* y where the pen last went down */
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */

/* Whether the pen went down this frame. */
static int menu_input_pen_went_down(void)
{
    return data_021fbdd8 != 0 && data_021fbddc != 0;
}

/* func_020a8028: where the pen is, when it is down and the buttons hold no control; `x` and
 * `y` may be NULL. */
int MenuInput_TouchPosition(int *x, int *y)
{
    if (MenuInput_HeldByButtons() || data_021fbdd8 == 0) {
        return 0;
    }
    u8 touch_x = data_021f6c58;
    u8 touch_y = data_021f6c54;
    if (x != NULL) {
        *x = touch_x;
    }
    if (y != NULL) {
        *y = touch_y;
    }
    return 1;
}
CLEAN_AS(func_020a8028, MenuInput_TouchPosition)

/* func_020a806c: where the pen went down, when it did this frame and the buttons hold no
 * control; `x` and `y` may be NULL. */
int MenuInput_TouchPressedAt(int *x, int *y)
{
    if (MenuInput_HeldByButtons() || !menu_input_pen_went_down()) {
        return 0;
    }
    u8 touch_x = data_021f6c60;
    u8 touch_y = data_021f6c5c;
    if (x != NULL) {
        *x = touch_x;
    }
    if (y != NULL) {
        *y = touch_y;
    }
    return 1;
}
CLEAN_AS(func_020a806c, MenuInput_TouchPressedAt)

/* func_020a80c4: whether the pen went down this frame inside the rectangle from (left, top)
 * to (right, bottom), the right and bottom edges excluded, and the buttons hold no control. */
int MenuInput_TouchPressedIn(int left, int right, int top, int bottom)
{
    if (MenuInput_HeldByButtons() || !menu_input_pen_went_down()) {
        return 0;
    }
    int x = data_021f6c60;
    int y = data_021f6c5c;
    return x >= left && x < right && y >= top && y < bottom;
}
CLEAN_AS(func_020a80c4, MenuInput_TouchPressedIn)

/* func_020a812c: whether the pen went down this frame and the buttons hold no control. */
int MenuInput_TouchPressed(void)
{
    return !MenuInput_HeldByButtons() && menu_input_pen_went_down();
}
CLEAN_AS(func_020a812c, MenuInput_TouchPressed)
