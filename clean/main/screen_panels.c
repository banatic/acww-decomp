/* The four screen panels (screen_panels.h). */
#include "screen_panels.h"

#include "a_mes_obj.h"
#include "autoload_2/heap.h" /* Heap_OperatorDeleteB */
#include "bells_panel.h"
#include "clean.h"
#include "ov004/member_pointer.h" /* MemberPointer */

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

/* The control mode (control_mode.h): buttons, touch. */
extern int func_0208ffac(void);
extern int func_0208ff98(void);

/* The first panel: shown (byte 0x4e set, byte 0x4f set in a room), hidden, settled; drawn,
 * updated, rewound and reset. */
extern void func_0208dd18(u8 *panel);
extern void func_0208dd10(u8 *panel);
extern int func_0208dd00(u8 *panel);
extern void func_0208dd40(u8 *panel);
extern void *func_0208dd50(u8 *panel);
extern void func_0208dd60(u8 *panel);
extern void func_0208dd68(u8 *panel);
/* The second panel: idle (its mode word, func_0208d12c, is 0 and its count at 0xc8 has run
 * out), shown (byte 0xa8 set, byte 0xa9 set in a room), hidden, settled; drawn, updated,
 * rewound and reset. */
extern int func_0208d01c(u8 *panel);
extern void func_0208d054(u8 *panel);
extern void func_0208d04c(u8 *panel);
extern int func_0208d03c(u8 *panel);
extern int func_0208d13c(u8 *panel);
extern void func_0208d14c(u8 *panel);
extern void func_0208d15c(u8 *panel);
extern void func_0208d164(u8 *panel);
/* The third panel: shown (byte 0x26 set), hidden, settled; drawn, updated, rewound and
 * reset. */
extern void func_0208bfc8(u8 *panel);
extern void func_0208bfc0(u8 *panel);
extern int func_0208bfa0(u8 *panel);
extern void func_0208bfd0(u8 *panel);
extern void func_0208bfe8(u8 *panel);
extern void func_0208c008(u8 *panel);
extern void func_0208c020(u8 *panel);
/* The fourth panel: shown (byte 0x80 set), hidden, settled; drawn, updated, rewound and
 * reset. */
extern void func_0208b9d8(u8 *panel);
extern void func_0208b9d0(u8 *panel);
extern int func_0208b9c0(u8 *panel);
extern void func_0208b9e0(u8 *panel);
extern void func_0208b9f8(u8 *panel);
extern void func_0208ba10(u8 *panel);
extern void func_0208ba30(u8 *panel);

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
        changed = func_0208ffac() != 0;
    } else {
        changed = func_0208ff98() != 0;
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
    if (func_0208d01c(panels->second) != 0) {
        func_0208d04c(panels->second);
        if (func_0208d03c(panels->second) != 0) {
            func_0208dd18(panels->first);
        }
    } else {
        func_0208dd10(panels->first);
        if (func_0208dd00(panels->first) != 0) {
            func_0208d054(panels->second);
        }
    }
}
CLEAN_AS(func_0208b0d8, ScreenPanels_StepRoom)

/* func_0208b148: the fourth panel shown while requested; else hidden, and once settled the
 * scene's window and state again. */
void ScreenPanels_StepRequested(ScreenPanels *panels)
{
    if (requested(panels)) {
        func_0208b9d8(panels->fourth);
    } else {
        func_0208b9d0(panels->fourth);
        if (func_0208b9c0(panels->fourth) != 0) {
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
    func_0208b9d8(panels->fourth);
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
        func_0208bfc0(panels->third);
        if (func_0208bfa0(panels->third) != 0) {
            ScreenPanels_EnterRequested(panels);
        }
    } else {
        func_0208bfc8(panels->third);
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
    int idle = func_0208d01c(panels->second);
    if (request || idle) {
        func_0208d04c(panels->second);
        if (func_0208d03c(panels->second) != 0) {
            if (request) {
                ScreenPanels_EnterRequested(panels);
            } else {
                AMesObj_SetVariant(0);
                AMesObj_SetWindow(AMES_KIND_SCENE, AMES_SCREENS_MAIN);
                ScreenPanels_EnterFirst(panels);
            }
        }
    } else {
        func_0208d054(panels->second);
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
    int busy = func_0208d01c(panels->second) == 0;
    if (request || busy) {
        func_0208dd10(panels->first);
        if (func_0208dd00(panels->first) != 0) {
            if (request) {
                ScreenPanels_EnterRequested(panels);
            } else {
                ScreenPanels_EnterSecond(panels);
            }
        }
    } else {
        func_0208dd18(panels->first);
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
    func_0208dd40(panels->first);
    func_0208d13c(panels->second);
    func_0208bfd0(panels->third);
    func_0208b9e0(panels->fourth);
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
    func_0208dd50(panels->first);
    func_0208d14c(panels->second);
    func_0208bfe8(panels->third);
    func_0208b9f8(panels->fourth);
    ScreenPanels_FollowControlMode(panels);
}
CLEAN_AS(func_0208b3ac, ScreenPanels_Update)

/* func_0208b478: the four panels rewound, the last first. */
void ScreenPanels_Rewind(ScreenPanels *panels)
{
    func_0208ba10(panels->fourth);
    func_0208c008(panels->third);
    func_0208d15c(panels->second);
    func_0208dd60(panels->first);
}
CLEAN_AS(func_0208b478, ScreenPanels_Rewind)

/* func_0208b4ac: the requests cleared (those of data_021d3258, whichever object this is), the
 * scene's state, the four panels reset and `touch` cleared. */
void ScreenPanels_Reset(ScreenPanels *panels)
{
    ScreenPanels_ClearRequest((unsigned int) (uintptr_t) panels);
    ScreenPanels_ClearRequest2();
    ScreenPanels_SelectState(panels);
    func_0208dd68(panels->first);
    func_0208d164(panels->second);
    func_0208c020(panels->third);
    func_0208ba30(panels->fourth);
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

/* The panels' constructors and destructors: the first, the second, the third. */
extern void *func_0208df44(u8 *panel);
extern void *func_0208def4(u8 *panel);
extern void *func_0208d338(u8 *panel);
extern void *func_0208d2e8(u8 *panel);
extern void *func_0208c1dc(u8 *panel);
extern void *func_0208c1ac(u8 *panel);

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
    func_0208c1ac(panels->third);
    func_0208d2e8(panels->second);
    func_0208def4(panels->first);
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
    func_0208df44(panels->first);
    func_0208d338(panels->second);
    func_0208c1dc(panels->third);
    BellsPanel_Construct((BellsPanel *) panels->fourth);
    panels->request = 0;
    panels->request_2 = 0;
    panels->touch = 0;
    return panels;
}
CLEAN_AS(func_0208b5ec, ScreenPanels_Construct)
