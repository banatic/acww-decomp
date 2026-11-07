/* The camera tab, the third screen panel (camera_tab.h). */
#include "camera_tab.h"

#include "autoload_2/heap.h"  /* Heap_OperatorDeleteB */
#include "autoload_2/input.h" /* PadState */
#include "camera_grid.h"
#include "cell_anim.h"
#include "clean.h"
#include "event_queue.h" /* EventQueue_FinishKind10, EventQueue_IsKind10Unfinished, ... */
#include "oam_buffer.h"  /* OamBuffer_DrawCell */
#include "ov004/member_pointer.h"
#include "sound.h"       /* SoundSys_PlaySe */
#include "state_flags.h" /* StateFlags_MenuCloseAsked, StateFlags_EndMenuClose */
#include "menu_input.h"
#include "player_actor_ops.h"

static_assert(offsetof(CameraTab, anim) == 0x0c && offsetof(CameraTab, state) == 0x20, "CameraTab");
static_assert(offsetof(CameraTab, grid_open) == 0x24 && offsetof(CameraTab, shown) == 0x26, "CameraTab");
static_assert(offsetof(CameraTab, window) == 0x28 && sizeof(CameraTab) == 0x100, "CameraTab");

/* The animations: appearing; shown (its first frame, still) and hiding; open. */
extern const CellAnimData data_020d5c3c, data_020d5c44, data_020d5c4c;

extern PadState data_021fbe40;
extern u8 data_021fbdd8; /* the pen is down */
extern u8 data_021fbddc; /* the pen went down or up this frame */
extern u8 data_021f6c60; /* the touch's x */
extern u8 data_021f6c5c; /* the touch's y */

#define PAD_B 0x0002
#define PAD_X 0x0400

/* The tab's place on the touch screen. */
#define TAB_LEFT 0xc8
#define TAB_RIGHT 0xe8 /* past the last column */
#define TAB_BOTTOM 0x10

/* The own player's actor states without the tab: 8 to 15 and 0x24 to 0x2c. */
#define CAMERA_TAB_OWN_PLAYER 4
#define NO_TAB_STATES_FIRST_1 8
#define NO_TAB_STATES_COUNT_1 8
#define NO_TAB_STATES_FIRST_2 0x24
#define NO_TAB_STATES_COUNT_2 9

#define WINDOW_OPEN 1
#define WINDOW_CLOSE 0

/* The sounds of the window opening and closing. */
#define SE_OPEN 0x4a
#define SE_CLOSE 0x4b

#define SLOT_DRAW 2

static void set_anim(CameraTab *tab, const CellAnimData *data)
{
    CellAnim_SetData(&tab->anim, data);
    CellAnim_SetHold(&tab->anim, 1);
    CellAnim_Restart(&tab->anim);
}

/* func_0208bc0c: once the hiding animation is done, hidden. */
void CameraTab_StepHiding(CameraTab *tab)
{
    CellAnim_Advance(&tab->anim);
    if (CellAnim_IsDone(&tab->anim) != 0) {
        CameraTab_EnterHidden(tab);
    }
}
CLEAN_AS(func_0208bc0c, CameraTab_StepHiding)

/* func_0208bc30 */
void CameraTab_EnterHiding(CameraTab *tab)
{
    tab->state = CAMERA_TAB_HIDING;
    set_anim(tab, &data_020d5c44);
}
CLEAN_AS(func_0208bc30, CameraTab_EnterHiding)

/* func_0208bc60: once the window is closed, the menu's event finished and the tab shown. */
void CameraTab_StepClosing(CameraTab *tab)
{
    if (CameraGrid_IsClosed((CameraGrid *) (void *) tab->window) != 0) {
        EventQueue_FinishKind10();
        tab->grid_open = 0;
        CameraTab_EnterShown(tab);
    }
}
CLEAN_AS(func_0208bc60, CameraTab_StepClosing)

/* func_0208bc88: the window asked to close, with its sound. */
void CameraTab_EnterClosing(CameraTab *tab)
{
    tab->state = CAMERA_TAB_CLOSING;
    CameraGrid_AskOpen((CameraGrid *) (void *) tab->window, WINDOW_CLOSE);
    SoundSys_PlaySe(SE_CLOSE);
}
CLEAN_AS(func_0208bc88, CameraTab_EnterClosing)

/* func_0208bca4: closed by X, B or a tap at the tab, or when the menu is asked to close. Both
 * are asked every frame. */
void CameraTab_StepOpen(CameraTab *tab)
{
    int pressed = CameraTab_Pressed(tab, 1);
    int asked = StateFlags_MenuCloseAsked();
    if (pressed != 0 || asked != 0) {
        CameraTab_EnterClosing(tab);
    }
}
CLEAN_AS(func_0208bca4, CameraTab_StepOpen)

/* func_0208bccc */
void CameraTab_EnterOpen(CameraTab *tab)
{
    tab->state = CAMERA_TAB_OPEN;
    set_anim(tab, &data_020d5c4c);
}
CLEAN_AS(func_0208bccc, CameraTab_EnterOpen)

/* func_0208bcfc: once the window is open, open. */
void CameraTab_StepOpening(CameraTab *tab)
{
    if (CameraGrid_IsOpen((CameraGrid *) (void *) tab->window) != 0) {
        CameraTab_EnterOpen(tab);
    }
}
CLEAN_AS(func_0208bcfc, CameraTab_StepOpening)

/* func_0208bd18: the window asked to open, the menu open, the input switched to what pressed
 * the tab, and the opening sound. */
void CameraTab_EnterOpening(CameraTab *tab)
{
    tab->state = CAMERA_TAB_OPENING;
    CameraGrid_AskOpen((CameraGrid *) (void *) tab->window, WINDOW_OPEN);
    tab->grid_open = 1;
    if (tab->by_button != 0) {
        MenuInput_UseButtons();
    } else {
        MenuInput_UseTouch();
    }
    SoundSys_PlaySe(SE_OPEN);
}
CLEAN_AS(func_0208bd18, CameraTab_EnterOpening)

/* func_0208bd50: once the menu's event runs, the window opens; when the tab is no longer
 * allowed, it hides; a press asks for the menu's event. */
void CameraTab_StepShown(CameraTab *tab)
{
    if (EventQueue_IsKind10Unfinished() != 0) {
        StateFlags_EndMenuClose();
        CameraTab_EnterOpening(tab);
    } else if (CameraTab_IsAllowed(tab) == 0) {
        CameraTab_EnterHiding(tab);
    } else if (CameraTab_Pressed(tab, 0) != 0) {
        EventQueue_RequestKind10();
    }
}
CLEAN_AS(func_0208bd50, CameraTab_StepShown)

/* func_0208bd90: the hiding animation's first frame, held still; the press forgotten. */
void CameraTab_EnterShown(CameraTab *tab)
{
    tab->state = CAMERA_TAB_SHOWN;
    tab->by_button = 0;
    set_anim(tab, &data_020d5c44);
    CellAnim_Stop(&tab->anim);
}
CLEAN_AS(func_0208bd90, CameraTab_EnterShown)

/* func_0208bdd0 */
void CameraTab_StepAppearing(CameraTab *tab)
{
    CellAnim_Advance(&tab->anim);
    if (CellAnim_IsDone(&tab->anim) != 0) {
        CameraTab_EnterShown(tab);
    }
}
CLEAN_AS(func_0208bdd0, CameraTab_StepAppearing)

/* func_0208bdf4 */
void CameraTab_EnterAppearing(CameraTab *tab)
{
    tab->state = CAMERA_TAB_APPEARING;
    set_anim(tab, &data_020d5c3c);
}
CLEAN_AS(func_0208bdf4, CameraTab_EnterAppearing)

/* func_0208be24 */
void CameraTab_StepHidden(CameraTab *tab)
{
    if (CameraTab_IsAllowed(tab) != 0) {
        CameraTab_EnterAppearing(tab);
    }
}
CLEAN_AS(func_0208be24, CameraTab_StepHidden)

/* func_0208be3c */
void CameraTab_EnterHidden(CameraTab *tab)
{
    tab->state = CAMERA_TAB_HIDDEN;
}
CLEAN_AS(func_0208be3c, CameraTab_EnterHidden)

/* func_0208be44: while the menu is open, the input switched to the buttons by a button press
 * and to touch by a tap, and the control mode set from it. */
void CameraTab_FollowInput(CameraTab *tab)
{
    if (tab->grid_open == 0) {
        return;
    }
    if (MenuInput_UsesTouch() != 0) {
        if (MenuInput_AnyPressed() != 0) {
            MenuInput_UseButtons();
        }
    } else if (MenuInput_UsesButtons() != 0 && MenuInput_TouchPressed() != 0) {
        MenuInput_UseTouch();
    }
    MenuInput_ApplyMode();
}
CLEAN_AS(func_0208be44, CameraTab_FollowInput)

/* func_0208be84: whether the tab is pressed: with the window closed or open, X (or B too when
 * `with_b`) pressed, noted as a button's press; else the pen tapping the tab, noted as a tap.
 * While the menu is open, a press that switches the input (CameraTab_FollowInput) is none. */
int CameraTab_Pressed(CameraTab *tab, int with_b)
{
    int switches = 0;
    if (tab->grid_open != 0) {
        if (MenuInput_UsesTouch() != 0) {
            if (MenuInput_AnyPressed() != 0) {
                switches = 1;
            }
        } else if (MenuInput_UsesButtons() != 0 && MenuInput_TouchPressed() != 0) {
            switches = 1;
        }
    }
    if (switches || CameraGrid_IsSettled((CameraGrid *) (void *) tab->window) == 0) {
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
CLEAN_AS(func_0208be84, CameraTab_Pressed)

/* func_0208bf48: whether the tab may show: `shown` set, no event running, and the own player's
 * actor in a state that has it. Both the event and the state are asked every time. */
int CameraTab_IsAllowed(CameraTab *tab)
{
    int event = EventQueue_HasCurrent() != 0;
    unsigned int player_state = (unsigned int) PlayerActorOps_State(CAMERA_TAB_OWN_PLAYER);
    int no_tab_1 = player_state - NO_TAB_STATES_FIRST_1 < NO_TAB_STATES_COUNT_1;
    int no_tab_2 = player_state - NO_TAB_STATES_FIRST_2 < NO_TAB_STATES_COUNT_2;
    return tab->shown != 0 && !event && !no_tab_1 && !no_tab_2;
}
CLEAN_AS(func_0208bf48, CameraTab_IsAllowed)

/* func_0208bfa0: hidden, with the window closed. */
int CameraTab_IsSettled(CameraTab *tab)
{
    return tab->state == CAMERA_TAB_HIDDEN && CameraGrid_IsClosed((CameraGrid *) (void *) tab->window) != 0;
}
CLEAN_AS(func_0208bfa0, CameraTab_IsSettled)

/* func_0208bfc0 */
void CameraTab_Hide(CameraTab *tab)
{
    tab->shown = 0;
}
CLEAN_AS(func_0208bfc0, CameraTab_Hide)

/* func_0208bfc8 */
void CameraTab_Show(CameraTab *tab)
{
    tab->shown = 1;
}
CLEAN_AS(func_0208bfc8, CameraTab_Show)

/* func_0208bfd0: the class's draw, then the window's. */
void CameraTab_CallDraw(CameraTab *tab)
{
    ((void (*)(CameraTab *))(uintptr_t) tab->base.vtable[SLOT_DRAW])(tab);
    CameraGrid_CallDraw((CameraGrid *) (void *) tab->window);
}
CLEAN_AS(func_0208bfd0, CameraTab_CallDraw)

/* ---- The tab's update, draw, reset, constructor and destructors */

extern const u32 data_020e2234[]; /* the class's vtable */

/* The member function table of CameraTab_Step (a function-local static of the game): its guard,
 * the table, and the constants it is filled from. */
extern u32 data_021d315c;
extern MemberPointer data_021d3220[7];
extern const MemberPointer data_020e21a4, data_020e216c, data_020e2194, data_020e218c, data_020e2184, data_020e217c,
    data_020e2174;

/* The palettes of the tab: while its window opens, is open or closes; else. */
#define MENU_TAB_PALETTE_OPEN 6
#define MENU_TAB_PALETTE 5

#define MENU_TAB_SLOT_STEP 3

static CameraGrid *menu_tab_grid(CameraTab *tab)
{
    return (CameraGrid *) (void *) tab->window;
}

/* func_0208bfe8: a frame: the class's step, the window's update, and the input followed. */
void CameraTab_Update(CameraTab *tab)
{
    ((void (*)(CameraTab *))(uintptr_t) tab->base.vtable[MENU_TAB_SLOT_STEP])(tab);
    CameraGrid_CallUpdate(menu_tab_grid(tab));
    CameraTab_FollowInput(tab);
}
CLEAN_AS(func_0208bfe8, CameraTab_Update)

/* func_0208c008: the window's animations and the tab's restarted. */
void CameraTab_Rewind(CameraTab *tab)
{
    CameraGrid_RestartButtons(menu_tab_grid(tab));
    CellAnim_Restart(&tab->anim);
}
CLEAN_AS(func_0208c008, CameraTab_Rewind)

/* func_0208c020: not shown, the menu not open, hidden, and the window reset. */
void CameraTab_Reset(CameraTab *tab)
{
    tab->shown = 0;
    tab->grid_open = 0;
    tab->by_button = 0;
    CameraTab_EnterHidden(tab);
    CameraGrid_Reset(menu_tab_grid(tab));
}
CLEAN_AS(func_0208c020, CameraTab_Reset)

/* func_0208c04c (vtable slot 3): the state's step, through the game's table (filled on the
 * first call).
 * REQUIRES: the state is 0-6 (the ROM indexes its table unchecked). */
void CameraTab_Step(CameraTab *tab)
{
    static const MemberPointer *const constants[7] = {
        &data_020e21a4, /* CameraTab_StepHidden */
        &data_020e216c, /* CameraTab_StepAppearing */
        &data_020e2194, /* CameraTab_StepShown */
        &data_020e218c, /* CameraTab_StepOpening */
        &data_020e2184, /* CameraTab_StepOpen */
        &data_020e217c, /* CameraTab_StepClosing */
        &data_020e2174, /* CameraTab_StepHiding */
    };
    MemberTable_InitOnce(&data_021d315c, data_021d3220, constants, 7);
    MemberPointer_CallVoid(&data_021d3220[tab->state], tab);
}
CLEAN_AS(func_0208c04c, CameraTab_Step)

/* func_0208c0f8 (vtable slot 2): unless hidden, the animation's cell drawn on the main screen at
 * the sprite's place plus the frame's offset, in palette 6 from the window's opening to its
 * closing. */
void CameraTab_Draw(CameraTab *tab)
{
    if (tab->state == CAMERA_TAB_HIDDEN) {
        return;
    }
    const OamEntry *cell = CellAnim_Cell(&tab->anim);
    if (cell == NULL) {
        return;
    }
    int dx = CellAnim_FrameX(&tab->anim, -1);
    int dy = CellAnim_FrameY(&tab->anim, -1);
    int x = ScreenSprite_X(&tab->base);
    int y = ScreenSprite_Y(&tab->base);
    int with_window = tab->state >= CAMERA_TAB_OPENING && tab->state <= CAMERA_TAB_CLOSING;
    int palette = with_window ? MENU_TAB_PALETTE_OPEN : MENU_TAB_PALETTE;
    OamBuffer_DrawCell(OAM_BUFFER_SCREEN_MAIN, cell, x + dx, y + dy, palette, -1, FX32_ONE, FX32_ONE, 0, -1, 0, 0);
}
CLEAN_AS(func_0208c0f8, CameraTab_Draw)

static void menu_tab_destruct(CameraTab *tab)
{
    tab->base.vtable = data_020e2234;
    CameraTab_Rewind(tab);
    CameraGrid_Destruct(menu_tab_grid(tab));
    CellAnim_Destruct(&tab->anim);
    ScreenSprite_DestructBase(&tab->base);
}

/* func_0208c178 (vtable slot 1): destructed and freed. */
CameraTab *CameraTab_Delete(CameraTab *tab)
{
    menu_tab_destruct(tab);
    Heap_OperatorDeleteB(tab);
    return tab;
}
CLEAN_AS(func_0208c178, CameraTab_Delete)

/* func_0208c1ac (vtable slot 0): the destructor: rewound, then the window and the animation
 * destructed. */
CameraTab *CameraTab_Destruct(CameraTab *tab)
{
    menu_tab_destruct(tab);
    return tab;
}
CLEAN_AS(func_0208c1ac, CameraTab_Destruct)

/* func_0208c1dc: the constructor: hidden, not shown, the menu not open. */
CameraTab *CameraTab_Construct(CameraTab *tab)
{
    ScreenSprite_Construct(&tab->base);
    tab->base.vtable = data_020e2234;
    CellAnim_Construct(&tab->anim);
    tab->state = CAMERA_TAB_HIDDEN;
    tab->grid_open = 0;
    tab->by_button = 0;
    tab->shown = 0;
    CameraGrid_Construct(menu_tab_grid(tab));
    return tab;
}
CLEAN_AS(func_0208c1dc, CameraTab_Construct)
