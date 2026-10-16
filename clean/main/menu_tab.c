/* The menu tab, the third screen panel (menu_tab.h). */
#include "menu_tab.h"

#include "autoload_2/input.h" /* PadState */
#include "cell_anim.h"
#include "clean.h"
#include "event_queue.h" /* EventQueue_FinishKind10, EventQueue_IsKind10Unfinished, ... */
#include "sound.h"       /* SoundSys_PlaySe */

static_assert(offsetof(MenuTab, anim) == 0x0c && offsetof(MenuTab, state) == 0x20, "MenuTab");
static_assert(offsetof(MenuTab, open) == 0x24 && offsetof(MenuTab, shown) == 0x26, "MenuTab");
static_assert(offsetof(MenuTab, window) == 0x28 && sizeof(MenuTab) == 0x100, "MenuTab");

/* The animations: appearing; shown (its first frame, still) and hiding; open. */
extern const CellAnimData data_020d5c3c, data_020d5c44, data_020d5c4c;

extern PadState data_021fbe40;
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */
extern u8 data_021f6c60; /* the touch's x */
extern u8 data_021f6c5c; /* the touch's y */

/* The menu window (the member at 0x28): closed or open; open; closed; asked to open (1) or to
 * close (0); drawn. */
extern int func_0208c5f0(u8 *window);
extern int func_0208c610(u8 *window);
extern int func_0208c620(u8 *window);
extern void func_0208c630(u8 *window, u8 open);
extern int func_0208c638(u8 *window);

/* The input's choice of buttons or touch (data_021f43f4): touch is chosen; a button was
 * pressed (as the input layer counts it); buttons are chosen; the pen tapped; buttons chosen;
 * touch chosen; the control mode set from the choice (control_mode.h). */
extern int func_020a7e50(void);
extern int func_020a7ffc(void);
extern u8 func_020a7e44(void);
extern int func_020a812c(void);
extern void func_020a7e64(void);
extern void func_020a7e70(void);
extern void func_020a7dec(void);

/* State flag 0x80 is set and the byte at data_021cfc54 is 0: the menu is asked to close. */
extern int func_0206f56c(void);
/* State flag 0x80 cleared and data_021cfc54 set to 0x37. */
extern void func_0206f5b0(void);
/* The current scene's number (func_020960d8(4)). */
extern int func_020960d8(int which);

#define PAD_B 0x0002
#define PAD_X 0x0400

/* The tab's place on the touch screen. */
#define TAB_LEFT 0xc8
#define TAB_RIGHT 0xe8 /* past the last column */
#define TAB_BOTTOM 0x10

/* The scenes without the tab: 8 to 15 and 0x24 to 0x2c. */
#define SCENE_WHICH 4
#define NO_TAB_FIRST_1 8
#define NO_TAB_COUNT_1 8
#define NO_TAB_FIRST_2 0x24
#define NO_TAB_COUNT_2 9

#define WINDOW_OPEN 1
#define WINDOW_CLOSE 0

/* The sounds of the window opening and closing. */
#define SE_OPEN 0x4a
#define SE_CLOSE 0x4b

#define SLOT_DRAW 2

static void set_anim(MenuTab *tab, const CellAnimData *data)
{
    CellAnim_SetData(&tab->anim, data);
    CellAnim_SetHold(&tab->anim, 1);
    CellAnim_Restart(&tab->anim);
}

/* func_0208bc0c: once the hiding animation is done, hidden. */
void MenuTab_StepHiding(MenuTab *tab)
{
    CellAnim_Advance(&tab->anim);
    if (CellAnim_IsDone(&tab->anim) != 0) {
        MenuTab_EnterHidden(tab);
    }
}
CLEAN_AS(func_0208bc0c, MenuTab_StepHiding)

/* func_0208bc30 */
void MenuTab_EnterHiding(MenuTab *tab)
{
    tab->state = MENU_TAB_HIDING;
    set_anim(tab, &data_020d5c44);
}
CLEAN_AS(func_0208bc30, MenuTab_EnterHiding)

/* func_0208bc60: once the window is closed, the menu's event finished and the tab shown. */
void MenuTab_StepClosing(MenuTab *tab)
{
    if (func_0208c620(tab->window) != 0) {
        EventQueue_FinishKind10();
        tab->open = 0;
        MenuTab_EnterShown(tab);
    }
}
CLEAN_AS(func_0208bc60, MenuTab_StepClosing)

/* func_0208bc88: the window asked to close, with its sound. */
void MenuTab_EnterClosing(MenuTab *tab)
{
    tab->state = MENU_TAB_CLOSING;
    func_0208c630(tab->window, WINDOW_CLOSE);
    SoundSys_PlaySe(SE_CLOSE);
}
CLEAN_AS(func_0208bc88, MenuTab_EnterClosing)

/* func_0208bca4: closed by X, B or a tap at the tab, or when the menu is asked to close. Both
 * are asked every frame. */
void MenuTab_StepOpen(MenuTab *tab)
{
    int pressed = MenuTab_Pressed(tab, 1);
    int asked = func_0206f56c();
    if (pressed != 0 || asked != 0) {
        MenuTab_EnterClosing(tab);
    }
}
CLEAN_AS(func_0208bca4, MenuTab_StepOpen)

/* func_0208bccc */
void MenuTab_EnterOpen(MenuTab *tab)
{
    tab->state = MENU_TAB_OPEN;
    set_anim(tab, &data_020d5c4c);
}
CLEAN_AS(func_0208bccc, MenuTab_EnterOpen)

/* func_0208bcfc: once the window is open, open. */
void MenuTab_StepOpening(MenuTab *tab)
{
    if (func_0208c610(tab->window) != 0) {
        MenuTab_EnterOpen(tab);
    }
}
CLEAN_AS(func_0208bcfc, MenuTab_StepOpening)

/* func_0208bd18: the window asked to open, the menu open, the input switched to what pressed
 * the tab, and the opening sound. */
void MenuTab_EnterOpening(MenuTab *tab)
{
    tab->state = MENU_TAB_OPENING;
    func_0208c630(tab->window, WINDOW_OPEN);
    tab->open = 1;
    if (tab->by_button != 0) {
        func_020a7e64();
    } else {
        func_020a7e70();
    }
    SoundSys_PlaySe(SE_OPEN);
}
CLEAN_AS(func_0208bd18, MenuTab_EnterOpening)

/* func_0208bd50: once the menu's event runs, the window opens; when the tab is no longer
 * allowed, it hides; a press asks for the menu's event. */
void MenuTab_StepShown(MenuTab *tab)
{
    if (EventQueue_IsKind10Unfinished() != 0) {
        func_0206f5b0();
        MenuTab_EnterOpening(tab);
    } else if (MenuTab_IsAllowed(tab) == 0) {
        MenuTab_EnterHiding(tab);
    } else if (MenuTab_Pressed(tab, 0) != 0) {
        EventQueue_RequestKind10();
    }
}
CLEAN_AS(func_0208bd50, MenuTab_StepShown)

/* func_0208bd90: the hiding animation's first frame, held still; the press forgotten. */
void MenuTab_EnterShown(MenuTab *tab)
{
    tab->state = MENU_TAB_SHOWN;
    tab->by_button = 0;
    set_anim(tab, &data_020d5c44);
    CellAnim_Stop(&tab->anim);
}
CLEAN_AS(func_0208bd90, MenuTab_EnterShown)

/* func_0208bdd0 */
void MenuTab_StepAppearing(MenuTab *tab)
{
    CellAnim_Advance(&tab->anim);
    if (CellAnim_IsDone(&tab->anim) != 0) {
        MenuTab_EnterShown(tab);
    }
}
CLEAN_AS(func_0208bdd0, MenuTab_StepAppearing)

/* func_0208bdf4 */
void MenuTab_EnterAppearing(MenuTab *tab)
{
    tab->state = MENU_TAB_APPEARING;
    set_anim(tab, &data_020d5c3c);
}
CLEAN_AS(func_0208bdf4, MenuTab_EnterAppearing)

/* func_0208be24 */
void MenuTab_StepHidden(MenuTab *tab)
{
    if (MenuTab_IsAllowed(tab) != 0) {
        MenuTab_EnterAppearing(tab);
    }
}
CLEAN_AS(func_0208be24, MenuTab_StepHidden)

/* func_0208be3c */
void MenuTab_EnterHidden(MenuTab *tab)
{
    tab->state = MENU_TAB_HIDDEN;
}
CLEAN_AS(func_0208be3c, MenuTab_EnterHidden)

/* func_0208be44: while the menu is open, the input switched to the buttons by a button press
 * and to touch by a tap, and the control mode set from it. */
void MenuTab_FollowInput(MenuTab *tab)
{
    if (tab->open == 0) {
        return;
    }
    if (func_020a7e50() != 0) {
        if (func_020a7ffc() != 0) {
            func_020a7e64();
        }
    } else if (func_020a7e44() != 0 && func_020a812c() != 0) {
        func_020a7e70();
    }
    func_020a7dec();
}
CLEAN_AS(func_0208be44, MenuTab_FollowInput)

/* func_0208be84: whether the tab is pressed: with the window closed or open, X (or B too when
 * `with_b`) pressed, noted as a button's press; else the pen tapping the tab, noted as a tap.
 * While the menu is open, a press that switches the input (MenuTab_FollowInput) is none. */
int MenuTab_Pressed(MenuTab *tab, int with_b)
{
    int switches = 0;
    if (tab->open != 0) {
        if (func_020a7e50() != 0) {
            if (func_020a7ffc() != 0) {
                switches = 1;
            }
        } else if (func_020a7e44() != 0 && func_020a812c() != 0) {
            switches = 1;
        }
    }
    if (switches || func_0208c5f0(tab->window) == 0) {
        return 0;
    }
    u16 pressed = data_021fbe40.pressed;
    if ((pressed & PAD_X) != 0 || (with_b != 0 && (pressed & PAD_B) != 0)) {
        tab->by_button = 1;
        return 1;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        int x = data_021f6c60;
        int y = data_021f6c5c;
        if (y < TAB_BOTTOM && x >= TAB_LEFT && x < TAB_RIGHT) {
            tab->by_button = 0;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0208be84, MenuTab_Pressed)

/* func_0208bf48: whether the tab may show: `shown` set, no event running, and a scene that
 * has it. Both the event and the scene are asked every time. */
int MenuTab_IsAllowed(MenuTab *tab)
{
    int event = EventQueue_HasCurrent() != 0;
    unsigned int scene = (unsigned int) func_020960d8(SCENE_WHICH);
    int no_tab_1 = scene - NO_TAB_FIRST_1 < NO_TAB_COUNT_1;
    int no_tab_2 = scene - NO_TAB_FIRST_2 < NO_TAB_COUNT_2;
    return tab->shown != 0 && !event && !no_tab_1 && !no_tab_2;
}
CLEAN_AS(func_0208bf48, MenuTab_IsAllowed)

/* func_0208bfa0: hidden, with the window closed. */
int MenuTab_IsSettled(MenuTab *tab)
{
    return tab->state == MENU_TAB_HIDDEN && func_0208c620(tab->window) != 0;
}
CLEAN_AS(func_0208bfa0, MenuTab_IsSettled)

/* func_0208bfc0 */
void MenuTab_Hide(MenuTab *tab)
{
    tab->shown = 0;
}
CLEAN_AS(func_0208bfc0, MenuTab_Hide)

/* func_0208bfc8 */
void MenuTab_Show(MenuTab *tab)
{
    tab->shown = 1;
}
CLEAN_AS(func_0208bfc8, MenuTab_Show)

/* func_0208bfd0: the class's draw, then the window's. */
void MenuTab_CallDraw(MenuTab *tab)
{
    ((void (*)(MenuTab *))(uintptr_t) tab->base.vtable[SLOT_DRAW])(tab);
    func_0208c638(tab->window);
}
CLEAN_AS(func_0208bfd0, MenuTab_CallDraw)
