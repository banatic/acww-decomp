/* The four screen panels (screen_panels.h). */
#include "screen_panels.h"

#include "a_mes_obj.h"
#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "bells_panel.h"
#include "clean.h"
#include "ov004/member_pointer.h" /* MemberPointer */
#include "catch_panel.h"
#include "clock_panel.h"
#include "control_mode_icon.h"
#include "menu_tab.h"

static_assert(offsetof(ScreenPanels, second) == 0xe0 && offsetof(ScreenPanels, third) == 0x1c4, "ScreenPanels");
static_assert(offsetof(ScreenPanels, fourth) == 0x2c4 && offsetof(ScreenPanels, request) == 0x348, "ScreenPanels");
static_assert(sizeof(ScreenPanels) == 0x34c, "ScreenPanels");

/* The a_mes window kind shown with the fourth panel on request. */
#define WINDOW_KIND_REQUESTED 3
/* The a_mes window kind shown with the second panel. */
#define WINDOW_KIND_SECOND 1

#define IN_A_ROOM 1

extern ScreenPanels data_021d3258;
extern u8 data_020e54a8; /* 0 outdoors, 1 in a room */

/* The member function table of ScreenPanels_Update (a function-local static of the game): its
 * guard, the table, and the constants it is filled from. */
extern u32 data_021d3150;
extern MemberPointer data_021d31f0[6];
extern const MemberPointer data_020e21ac, data_020e219c, data_020e210c, data_020e2104, data_020e2144, data_020e20ec;

static int requested(const ScreenPanels *panels)
{
    return panels->request != 0 || panels->request_2 != 0;
}

/* func_0208b034: the third panel's extra characters follow the control mode: once it changed,
 * `touch` flips, and in the third panel's state the extra characters are switched (their upload
 * left pending). */
void ScreenPanels_FollowControlMode(ScreenPanels *panels)
{
    int changed;
    if (panels->touch != 0) {
        changed = ControlModeIcon_IsButtons() != 0;
    } else {
        changed = ControlModeIcon_IsTouch() != 0;
    }
    if (!changed) {
        return;
    }
    panels->touch = panels->touch == 0 ? 1 : 0;
    if (panels->state == SCREEN_PANELS_THIRD) {
        AMesObj_SetExtraChars(panels->touch, 1, AMES_SCREENS_MAIN);
    }
}
CLEAN_AS(func_0208b034, ScreenPanels_FollowControlMode)

/* func_0208b090: the state of the current scene's style (for style 1, the second panel when the
 * a_mes variant is set). */
void ScreenPanels_SelectState(ScreenPanels *panels)
{
    int style = AMesObj_Style();
    if (style == 1) {
        if (AMesObj_Variant() != 0) {
            ScreenPanels_EnterSecond(panels);
        } else {
            ScreenPanels_EnterFirst(panels);
        }
    } else if (style == 2) {
        ScreenPanels_EnterThird(panels);
    } else if (style == 3) {
        ScreenPanels_EnterFourth(panels);
    } else {
        ScreenPanels_EnterNone(panels);
    }
}
CLEAN_AS(func_0208b090, ScreenPanels_SelectState)

/* func_0208b0d8: in a room of a scene with a style, the first and second panels swapped as in
 * style 1: the second hidden when idle, then the first shown; else the first hidden, then the
 * second shown. */
void ScreenPanels_StepRoom(ScreenPanels *panels)
{
    if (AMesObj_Style() == 0 || data_020e54a8 != IN_A_ROOM) {
        return;
    }
    if (CatchPanel_IsIdle((CatchPanel *) (void *) panels->second) != 0) {
        CatchPanel_Hide((CatchPanel *) (void *) panels->second);
        if (CatchPanel_IsHidden((CatchPanel *) (void *) panels->second) != 0) {
            ClockPanel_Show((ClockPanel *) (void *) panels->first);
        }
    } else {
        ClockPanel_Hide((ClockPanel *) (void *) panels->first);
        if (ClockPanel_IsHidden((ClockPanel *) (void *) panels->first) != 0) {
            CatchPanel_Show((CatchPanel *) (void *) panels->second);
        }
    }
}
CLEAN_AS(func_0208b0d8, ScreenPanels_StepRoom)

/* func_0208b148: the fourth panel shown while requested; else hidden, and once settled the
 * scene's window and state again. */
void ScreenPanels_StepRequested(ScreenPanels *panels)
{
    if (requested(panels)) {
        BellsPanel_Show((BellsPanel *) (void *) panels->fourth);
    } else {
        BellsPanel_Hide((BellsPanel *) (void *) panels->fourth);
        if (BellsPanel_IsClosed((BellsPanel *) (void *) panels->fourth) != 0) {
            AMesObj_SetWindow(AMES_KIND_SCENE, AMES_SCREENS_MAIN);
            ScreenPanels_SelectState(panels);
        }
    }
    ScreenPanels_StepRoom(panels);
}
CLEAN_AS(func_0208b148, ScreenPanels_StepRequested)

/* func_0208b1a0 */
void ScreenPanels_EnterRequested(ScreenPanels *panels)
{
    AMesObj_SetWindow(WINDOW_KIND_REQUESTED, AMES_SCREENS_MAIN);
    panels->state = SCREEN_PANELS_REQUESTED;
}
CLEAN_AS(func_0208b1a0, ScreenPanels_EnterRequested)

/* func_0208b1b8 */
void ScreenPanels_StepFourth(ScreenPanels *panels)
{
    BellsPanel_Show((BellsPanel *) (void *) panels->fourth);
    ScreenPanels_StepRoom(panels);
}
CLEAN_AS(func_0208b1b8, ScreenPanels_StepFourth)

/* func_0208b1d4 */
void ScreenPanels_EnterFourth(ScreenPanels *panels)
{
    panels->state = SCREEN_PANELS_FOURTH;
}
CLEAN_AS(func_0208b1d4, ScreenPanels_EnterFourth)

/* func_0208b1dc: the third panel shown; when requested, hidden and once settled the request's
 * state. */
void ScreenPanels_StepThird(ScreenPanels *panels)
{
    if (requested(panels)) {
        MenuTab_Hide((MenuTab *) (void *) panels->third);
        if (MenuTab_IsSettled((MenuTab *) (void *) panels->third) != 0) {
            ScreenPanels_EnterRequested(panels);
        }
    } else {
        MenuTab_Show((MenuTab *) (void *) panels->third);
    }
    ScreenPanels_StepRoom(panels);
}
CLEAN_AS(func_0208b1dc, ScreenPanels_StepThird)

/* func_0208b22c */
void ScreenPanels_EnterThird(ScreenPanels *panels)
{
    panels->state = SCREEN_PANELS_THIRD;
}
CLEAN_AS(func_0208b22c, ScreenPanels_EnterThird)

/* func_0208b234: the second panel shown; when requested or idle, hidden and once settled the
 * request's state, or the first panel's with the a_mes variant cleared and the scene's
 * window. */
void ScreenPanels_StepSecond(ScreenPanels *panels)
{
    int request = requested(panels);
    int idle = CatchPanel_IsIdle((CatchPanel *) (void *) panels->second);
    if (request || idle) {
        CatchPanel_Hide((CatchPanel *) (void *) panels->second);
        if (CatchPanel_IsHidden((CatchPanel *) (void *) panels->second) != 0) {
            if (request) {
                ScreenPanels_EnterRequested(panels);
            } else {
                AMesObj_SetVariant(0);
                AMesObj_SetWindow(AMES_KIND_SCENE, AMES_SCREENS_MAIN);
                ScreenPanels_EnterFirst(panels);
            }
        }
    } else {
        CatchPanel_Show((CatchPanel *) (void *) panels->second);
    }
}
CLEAN_AS(func_0208b234, ScreenPanels_StepSecond)

/* func_0208b2b0: the second panel's state, with the a_mes variant set and window kind 1. */
void ScreenPanels_EnterSecond(ScreenPanels *panels)
{
    panels->state = SCREEN_PANELS_SECOND;
    AMesObj_SetVariant(1);
    AMesObj_SetWindow(WINDOW_KIND_SECOND, AMES_SCREENS_MAIN);
}
CLEAN_AS(func_0208b2b0, ScreenPanels_EnterSecond)

/* func_0208b2cc: the first panel shown; when requested or the second panel is not idle,
 * hidden and once settled the request's state or the second panel's. */
void ScreenPanels_StepFirst(ScreenPanels *panels)
{
    int request = requested(panels);
    int busy = CatchPanel_IsIdle((CatchPanel *) (void *) panels->second) == 0;
    if (request || busy) {
        ClockPanel_Hide((ClockPanel *) (void *) panels->first);
        if (ClockPanel_IsHidden((ClockPanel *) (void *) panels->first) != 0) {
            if (request) {
                ScreenPanels_EnterRequested(panels);
            } else {
                ScreenPanels_EnterSecond(panels);
            }
        }
    } else {
        ClockPanel_Show((ClockPanel *) (void *) panels->first);
    }
}
CLEAN_AS(func_0208b2cc, ScreenPanels_StepFirst)

/* func_0208b344 */
void ScreenPanels_EnterFirst(ScreenPanels *panels)
{
    panels->state = SCREEN_PANELS_FIRST;
}
CLEAN_AS(func_0208b344, ScreenPanels_EnterFirst)

/* func_0208b34c: nothing shown; when requested, the request's state. */
void ScreenPanels_StepNone(ScreenPanels *panels)
{
    if (requested(panels)) {
        ScreenPanels_EnterRequested(panels);
    }
}
CLEAN_AS(func_0208b34c, ScreenPanels_StepNone)

/* func_0208b374 */
void ScreenPanels_EnterNone(ScreenPanels *panels)
{
    panels->state = SCREEN_PANELS_NONE;
}
CLEAN_AS(func_0208b374, ScreenPanels_EnterNone)

/* func_0208b37c: the four panels drawn. */
void ScreenPanels_Draw(ScreenPanels *panels)
{
    ClockPanel_CallDraw((ClockPanel *) (void *) panels->first);
    CatchPanel_CallDraw((CatchPanel *) (void *) panels->second);
    MenuTab_CallDraw((MenuTab *) (void *) panels->third);
    BellsPanel_CallDraw((BellsPanel *) (void *) panels->fourth);
}
CLEAN_AS(func_0208b37c, ScreenPanels_Draw)

/* func_0208b3ac: a frame: the state's step (through the game's table, filled on the first
 * call), the four panels updated, and the control mode followed.
 * REQUIRES: the state is 0-5 (the ROM indexes its table unchecked). */
void ScreenPanels_Update(ScreenPanels *panels)
{
    static const MemberPointer *const constants[6] = {
        &data_020e21ac, /* ScreenPanels_StepNone */
        &data_020e219c, /* ScreenPanels_StepFirst */
        &data_020e210c, /* ScreenPanels_StepSecond */
        &data_020e2104, /* ScreenPanels_StepThird */
        &data_020e2144, /* ScreenPanels_StepFourth */
        &data_020e20ec, /* ScreenPanels_StepRequested */
    };
    MemberTable_InitOnce(&data_021d3150, data_021d31f0, constants, 6);
    MemberPointer_CallVoid(&data_021d31f0[panels->state], panels);
    ClockPanel_CallUpdate((ClockPanel *) (void *) panels->first);
    CatchPanel_CallUpdate((CatchPanel *) (void *) panels->second);
    MenuTab_Update((MenuTab *) (void *) panels->third);
    BellsPanel_CallUpdate((BellsPanel *) (void *) panels->fourth);
    ScreenPanels_FollowControlMode(panels);
}
CLEAN_AS(func_0208b3ac, ScreenPanels_Update)

/* func_0208b478: the four panels rewound, the last first. */
void ScreenPanels_Rewind(ScreenPanels *panels)
{
    BellsPanel_Rewind((BellsPanel *) (void *) panels->fourth);
    MenuTab_Rewind((MenuTab *) (void *) panels->third);
    CatchPanel_Rewind((CatchPanel *) (void *) panels->second);
    ClockPanel_Rewind((ClockPanel *) (void *) panels->first);
}
CLEAN_AS(func_0208b478, ScreenPanels_Rewind)

/* func_0208b4ac: the requests cleared (those of data_021d3258, whichever object this is), the
 * scene's state, the four panels reset and `touch` cleared. */
void ScreenPanels_Reset(ScreenPanels *panels)
{
    ScreenPanels_ClearRequest((unsigned int) (uintptr_t) panels);
    ScreenPanels_ClearRequest2();
    ScreenPanels_SelectState(panels);
    ClockPanel_Reset((ClockPanel *) (void *) panels->first);
    CatchPanel_Reset((CatchPanel *) (void *) panels->second);
    MenuTab_Reset((MenuTab *) (void *) panels->third);
    BellsPanel_Reset((BellsPanel *) (void *) panels->fourth);
    panels->touch = 0;
}
CLEAN_AS(func_0208b4ac, ScreenPanels_Reset)

/* func_0208b4f8: the fourth panel of data_021d3258 (data_021d351c). */
int ScreenPanels_FourthPanel(void)
{
    return (int) (uintptr_t) data_021d3258.fourth;
}
CLEAN_AS(func_0208b4f8, ScreenPanels_FourthPanel)

/* func_0208b500: the second panel of data_021d3258 (data_021d3338). */
int ScreenPanels_SecondPanel(void)
{
    return (int) (uintptr_t) data_021d3258.second;
}
CLEAN_AS(func_0208b500, ScreenPanels_SecondPanel)

/* func_0208b508 */
void ScreenPanels_ClearRequest2(void)
{
    data_021d3258.request_2 = 0;
}
CLEAN_AS(func_0208b508, ScreenPanels_ClearRequest2)

/* func_0208b514: the argument is not used. */
void ScreenPanels_ClearRequest(unsigned int unused)
{
    (void) unused;
    data_021d3258.request = 0;
}
CLEAN_AS(func_0208b514, ScreenPanels_ClearRequest)

/* func_0208b520 */
void ScreenPanels_Request(void)
{
    data_021d3258.request = 1;
}
CLEAN_AS(func_0208b520, ScreenPanels_Request)

/* ---- The global object, its constructor and destructors */

extern const u32 data_020e21d4[]; /* the class's vtable */

/* func_0208b52c */
void ScreenPanels_DrawGlobal(void)
{
    ScreenPanels_Draw(&data_021d3258);
}
CLEAN_AS(func_0208b52c, ScreenPanels_DrawGlobal)

/* func_0208b53c */
void ScreenPanels_UpdateGlobal(void)
{
    ScreenPanels_Update(&data_021d3258);
}
CLEAN_AS(func_0208b53c, ScreenPanels_UpdateGlobal)

/* func_0208b54c */
void ScreenPanels_RewindGlobal(void)
{
    ScreenPanels_Rewind(&data_021d3258);
}
CLEAN_AS(func_0208b54c, ScreenPanels_RewindGlobal)

/* func_0208b55c */
void ScreenPanels_ResetGlobal(void)
{
    ScreenPanels_Reset(&data_021d3258);
}
CLEAN_AS(func_0208b55c, ScreenPanels_ResetGlobal)

/* The destructors' work: the panels destructed, the last first. */
static void destruct_panels(ScreenPanels *panels)
{
    panels->unk_00 = (u32) (uintptr_t) data_020e21d4; /* the vtable */
    BellsPanel_Destruct((BellsPanel *) panels->fourth);
    MenuTab_Destruct((MenuTab *) (void *) panels->third);
    CatchPanel_Destruct((CatchPanel *) (void *) panels->second);
    ClockPanel_Destruct((ClockPanel *) (void *) panels->first);
}

/* func_0208b56c (vtable slot 1): destructed and freed. */
ScreenPanels *ScreenPanels_Delete(ScreenPanels *panels)
{
    destruct_panels(panels);
    Heap_OperatorDeleteB(panels);
    return panels;
}
CLEAN_AS(func_0208b56c, ScreenPanels_Delete)

/* func_0208b5b0 (vtable slot 0): the destructor (registered for data_021d3258 at start-up). */
ScreenPanels *ScreenPanels_Destruct(ScreenPanels *panels)
{
    destruct_panels(panels);
    return panels;
}
CLEAN_AS(func_0208b5b0, ScreenPanels_Destruct)

/* func_0208b5ec: the constructor (of data_021d3258, at start-up): nothing shown, the panels
 * constructed, no request, buttons. */
ScreenPanels *ScreenPanels_Construct(ScreenPanels *panels)
{
    panels->unk_00 = (u32) (uintptr_t) data_020e21d4; /* the vtable */
    panels->state = SCREEN_PANELS_NONE;
    ClockPanel_Construct((ClockPanel *) (void *) panels->first);
    CatchPanel_Construct((CatchPanel *) (void *) panels->second);
    MenuTab_Construct((MenuTab *) (void *) panels->third);
    BellsPanel_Construct((BellsPanel *) panels->fourth);
    panels->request = 0;
    panels->request_2 = 0;
    panels->touch = 0;
    return panels;
}
CLEAN_AS(func_0208b5ec, ScreenPanels_Construct)
