/* The base class of the scenes' processes and the request for the next scene
 * (scene_process_base.h). */
#include "scene_process_base.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "display_3d.h"
#include "display_frame.h"
#include "empty_0203de64.h"
#include "game_stop.h"
#include "itcm/process_phases.h"
#include "scene_sound.h"
#include "session.h"
#include "session_link.h"

static_assert(offsetof(Process, class_id) == 0x0c && offsetof(Process, flags) == 0x13, "process");

/* The vtables of this class and of the processes' root class. */
extern const u32 data_020e3c94[];
extern const u32 data_020da13c[];

extern NetSession *data_020ccf94;

/* The scene asked for: its process class (SCENE_PROCESS_BASE_NONE for none) and the kinds of
 * transition that close the screen before it and open it after; whether the class asked for
 * was spawned. */
extern u16 data_020e3c80;
extern u8 data_021f42ec;
extern u8 data_021f42e8;
extern u8 data_020e3c7c;

/* The resident process, which the scenes are spawned under. */
extern Process *data_021dc740;
/* The running scene's process, or NULL. */
extern Process *data_021f42f4;
/* The step of the running scene's creation (scene_process.h); 0 before it begins. */
extern u8 data_021f42f0;
/* The frames before the running scene opens the screen; 0 once it did. */
extern u8 data_021f42e0;
/* The step and the item of the scene's setup (scene_setup.h). */
extern u8 data_021f42dc;
extern u8 data_021f42e4;

/* The latch that stops the game's scenes (game_stop.h). */
extern u8 data_021dc6c4;
/* The screen's transition (SCREEN_*), and a flag that lets func_02041d14 close the screen
 * when it is not shown. */
extern u8 data_021c75b8;
extern u8 data_021c75b0;

/* The screen opened (from closed) or closed (from shown, or with data_021c75b0) with
 * transition `kind` over `frames` frames; 0 when it cannot be now. */
extern int func_02041c88(int kind, int frames, int option);
extern int func_02041d14(int kind, int frames);

/* A process of class `class_id` spawned under `parent`; NULL when it could not be. */
extern Process *func_0202f134(int class_id, Process *parent, int group, int arg);
/* The class whose after-create deletes a process whose creation is pending (actor.c). */
extern void func_0202f144(Process *process, int outcome);
/* Called with 1 before scene 2 is spawned (and with 0 when the library is shut down). */
extern void func_02116a1c(int arg);

/* The link's work of a frame (data_021f4320), and the link's state read and set. */
extern void func_020a6c08(void);
extern int func_020a6ea0(void);
extern void func_020a6eb0(int value);
/* The link's set-up when a scene is created (only for a slot of the session's), and a step
 * that does nothing. */
extern void func_020a6d84(void);
extern void func_020a7448(void);
/* Two objects of the game (data_021c7c48 and data_021c776c) updated. */
extern void func_02046600(void);
/* The second background of both engines cleared (and their palettes' first colours). */
extern void func_02041a9c(void);
/* The events dropped, and the four heap words OSiHeapInfo and data_021c72d4 cleared. */
extern void func_0203ecfc(void);
extern void func_0203f4c4(void);
/* Byte 0x19 of data_021d3674 set. */
extern void func_0208f8f0(void);

extern void G3X_Init(void);
extern void GX_SetBankForBG(int banks);
extern void GX_SetBankForOBJ(int banks);
extern void GX_SetBankForBGExtPltt(int banks);
extern void GX_SetBankForTex(int banks);
extern void GX_SetBankForTexPltt(int banks);

/* The 3D engine's lighting command ports. */
#define REG_DIF_AMB (*(volatile u32 *) 0x040004c0)
#define REG_SPE_EMI (*(volatile u32 *) 0x040004c4)
#define REG_LIGHT_VECTOR (*(volatile u32 *) 0x040004c8)
#define REG_LIGHT_COLOR (*(volatile u32 *) 0x040004cc)

/* The VRAM banks a scene uses. */
#define BANK_BG_F 0x20
#define BANK_OBJ_A 0x01
#define BANK_BGEXTPLTT_G 0x40
#define BANK_TEX_BC 0x06
#define BANK_TEXPLTT_E 0x10

enum SceneProcessBaseScreen {
    SCREEN_CLOSED = 0,
    SCREEN_SHOWN = 2,
};

#define SCENE_STOPPED 0xd4    /* the scene asked for once the game stops */
#define SCENE_2 2             /* the scene func_02116a1c is told of */
#define SCENE_FIELD_CLASS 6   /* the field's process class (scene_process.h) */
#define TRANSITION_FRAMES 0xf /* the frames of a transition between scenes */
#define STOP_TRANSITION 2     /* the transition that closes the screen when the game stops */
#define STOP_FRAMES 0x10
#define OPEN_DELAY 4 /* the frames of execution before the screen opens */
#define SPAWN_ARG 2
#define SCENE_PROCESS_BASE_SIZE 0x50

/* The link's states the creation and the change move on. */
enum {
    LINK_06 = 6,
    LINK_07 = 7,
    LINK_05 = 5,
    LINK_0C = 0x0c,
    LINK_0D = 0x0d,
    LINK_0E = 0x0e,
};

static int slot_taken(void)
{
    NetSession *session = data_020ccf94;
    return Session_IsSlotTaken(session, session->local_slot) != 0;
}

/* func_020a5254 (vtable slot 16): the destructor: this class's vtable, the root class's, then
 * the process destructor. */
Process *SceneProcessBase_Destruct(Process *process)
{
    process->vtable = data_020e3c94;
    process->vtable = data_020da13c;
    Process_Destruct(process);
    return process;
}
CLEAN_AS(func_020a5254, SceneProcessBase_Destruct)

/* func_020a5274 (vtable slot 17): the destructor, then the process freed. */
Process *SceneProcessBase_DestructFree(Process *process)
{
    process->vtable = data_020e3c94;
    process->vtable = data_020da13c;
    Process_Destruct(process);
    Heap_FreeAux(process);
    return process;
}
CLEAN_AS(func_020a5274, SceneProcessBase_DestructFree)

/* func_020a529c: after the root process's execution, for the running scene: once the screen
 * is closed, the scene deletes itself. When the game stopped, scene 0xd4 is asked for first
 * and the events and heap words are dropped after. Else only while a change is asked for and
 * data_021c75b0 is clear; then, with this system's slot of the session taken, only when the
 * link is at 5 or 0xc, which it moves on to 6 or 0xd. */
void SceneProcessBase_CheckChange(Process *process)
{
    if (data_021dc6c4 != 0) {
        if (data_021c75b8 != SCREEN_CLOSED) {
            return;
        }
        SceneProcessBase_Request(SCENE_STOPPED, 0, 0, 0);
        Process_RequestDelete(process);
        func_0203ecfc();
        func_0203f4c4();
        return;
    }
    if (data_020e3c80 == SCENE_PROCESS_BASE_NONE) {
        return;
    }
    if (data_021c75b8 != SCREEN_CLOSED || data_021c75b0 != 0) {
        return;
    }
    if (slot_taken()) {
        switch (func_020a6ea0()) {
            case LINK_05:
                Process_RequestDelete(process);
                func_020a6eb0(LINK_06);
                break;
            case LINK_0C:
                Process_RequestDelete(process);
                func_020a6eb0(LINK_0D);
                break;
            default:
                break;
        }
    } else {
        Process_RequestDelete(process);
    }
}
CLEAN_AS(func_020a529c, SceneProcessBase_CheckChange)

/* func_020a536c: the scene asked for spawned under the resident process (with
 * func_02116a1c(1) first for scene 2), once; it is then no longer asked for. Gives the
 * process, or 0 when nothing was spawned. */
int SceneProcessBase_StartAsked(void)
{
    Process *scene;

    if (data_020e3c7c != 0 || data_020e3c80 == SCENE_PROCESS_BASE_NONE) {
        return 0;
    }
    if (data_020e3c80 == SCENE_2) {
        func_02116a1c(1);
    }
    scene = func_0202f134(data_020e3c80, data_021dc740, 0, SPAWN_ARG);
    if (scene == NULL) {
        return 0;
    }
    data_020e3c80 = SCENE_PROCESS_BASE_NONE;
    data_020e3c7c = 1;
    return (int) (uintptr_t) scene;
}
CLEAN_AS(func_020a536c, SceneProcessBase_StartAsked)

/* func_020a53c4: the first request: scene 1, with the transitions 3, not spawned yet. */
void SceneProcessBase_ResetRequest(void)
{
    data_020e3c80 = 1;
    data_021f42ec = 3;
    data_021f42e8 = 3;
    data_020e3c7c = 0;
}
CLEAN_AS(func_020a53c4, SceneProcessBase_ResetRequest)

/* func_020a53ec: scene `class_id` asked for, the screen closed with transition `param` and
 * opened with `arg`. */
void SceneProcessBase_Request(int class_id, int param, int arg, int unused)
{
    (void) unused;
    data_020e3c80 = (u16) class_id;
    data_021f42ec = (u8) param;
    data_021f42e8 = (u8) arg;
}
CLEAN_AS(func_020a53ec, SceneProcessBase_Request)

/* func_020a5408 (vtable slot 11): the root class's. */
void SceneProcessBase_AfterDraw(Process *process, int outcome)
{
    (void) outcome;
    Process_AfterDraw(process);
}
CLEAN_AS(func_020a5408, SceneProcessBase_AfterDraw)

/* func_020a5410 (vtable slot 10): the root class's answer as 0 or 1. */
int SceneProcessBase_CanDraw(Process *process)
{
    return Process_CanDraw(process) != 0;
}
CLEAN_AS(func_020a5410, SceneProcessBase_CanDraw)

/* func_020a5428 (vtable slot 8): the root class's. */
void SceneProcessBase_AfterExecute(Process *process)
{
    Process_AfterExecute(process);
}
CLEAN_AS(func_020a5428, SceneProcessBase_AfterExecute)

/* func_020a5430 (vtable slot 7): first the session's messages delivered, the link's work of
 * the frame and func_02046600. Then the scene executes when the root class allows it, unless
 * the game stopped (the screen then closed with transition 2 over 16 frames when shown, and
 * opened with transition 0 after) or a change is pending (the screen then closed with the
 * request's transition when shown or data_021c75b0 is set). A scene whose execution and
 * drawing were stopped (by SceneProcessBase_New) waits for its children's creation, then has
 * both restarted. While the screen is closed the frames before it opens are counted down; at
 * the last one it is opened with the request's transition, or tried again the next frame. */
int SceneProcessBase_CanExecute(Process *process)
{
    Session_Deliver(0);
    func_020a6c08();
    func_02046600();
    if (!Process_CanExecute(process)) {
        return 0;
    }
    if (data_021dc6c4 != 0) {
        if (data_021c75b8 == SCREEN_SHOWN) {
            data_021f42ec = STOP_TRANSITION;
            data_021f42e8 = 0;
            func_02041d14(STOP_TRANSITION, STOP_FRAMES);
        }
        return 0;
    }
    if (data_020e3c80 != SCENE_PROCESS_BASE_NONE) {
        if (data_021c75b8 == SCREEN_SHOWN || data_021c75b0 != 0) {
            func_02041d14(data_021f42ec, TRANSITION_FRAMES);
        }
        return 0;
    }
    if (process->flags & PROCESS_EXECUTE_STOPPED) {
        if (Process_IsAnyDescendantCreating(process) != 0) {
            return 0;
        }
        process->flags &= (u8) ~PROCESS_EXECUTE_STOPPED;
        process->flags &= (u8) ~PROCESS_DRAW_STOPPED;
    }
    if (data_021f42e0 != 0 && data_021c75b8 == SCREEN_CLOSED) {
        data_021f42e0--;
        if (data_021f42e0 == 0 && func_02041c88(data_021f42e8, TRANSITION_FRAMES, 0) == 0) {
            data_021f42e0 = 1;
        }
    }
    return 1;
}
CLEAN_AS(func_020a5430, SceneProcessBase_CanExecute)

/* func_020a553c (vtable slot 5): once deleted (OUTCOME_DONE) the next scene may be spawned, a
 * stopped game's leftovers are released, there is no running scene any more and the scene's
 * sound is deleted; then the root class's. */
void SceneProcessBase_AfterDelete(Process *process, int outcome)
{
    if (outcome == OUTCOME_DONE) {
        data_020e3c7c = 0;
        if (data_021dc6c4 != 0) {
            GameStop_Release();
        }
        data_021f42f4 = NULL;
        SceneSound_Delete();
    }
    Process_AfterDelete(process, outcome);
}
CLEAN_AS(func_020a553c, SceneProcessBase_AfterDelete)

/* func_020a5580 (vtable slot 4): the root class's answer as 0 or 1. */
int SceneProcessBase_CanDelete(Process *process)
{
    return Process_CanDelete(process) != 0;
}
CLEAN_AS(func_020a5580, SceneProcessBase_CanDelete)

/* func_020a5598 (vtable slot 2): once created (OUTCOME_DONE) the creation's step is cleared,
 * the second backgrounds cleared (not for the field's class), the session's messages delivered,
 * the link's work of the frame done, func_02046600 and func_0203de64; then func_0202f144's. */
void SceneProcessBase_AfterCreate(Process *process, int outcome)
{
    if (outcome == OUTCOME_DONE) {
        data_021f42f0 = 0;
        if (process->class_id != SCENE_FIELD_CLASS) {
            func_02041a9c();
        }
        Session_Deliver(0);
        func_020a6c08();
        func_02046600();
        Empty0203de64_Nothing64();
    }
    func_0202f144(process, outcome);
}
CLEAN_AS(func_020a5598, SceneProcessBase_AfterCreate)

/* func_020a55dc (vtable slot 1): when the root class allows it, the first time (step 0) the
 * display set up, func_0208f8f0, the scene noted as the running one, the screen to open after
 * four frames, the link's set-up, the step 1; with this system's slot of the session taken the
 * link moved on from 6 to 7 or from 0xd to 0xe; the scene setup's step and item cleared. */
int SceneProcessBase_CanCreate(Process *process)
{
    if (Process_CanCreateDefault() == 0) {
        return 0;
    }
    if (data_021f42f0 != 0) {
        return 1;
    }
    SceneProcessBase_SetUpDisplay();
    func_0208f8f0();
    data_021f42f4 = process;
    data_021f42e0 = OPEN_DELAY;
    func_020a7448();
    func_020a6d84();
    data_021f42f0++;
    if (slot_taken()) {
        switch (func_020a6ea0()) {
            case LINK_06:
                func_020a6eb0(LINK_07);
                break;
            case LINK_0D:
                func_020a6eb0(LINK_0E);
                break;
        }
    }
    data_021f42dc = 0;
    data_021f42e4 = 0;
    return 1;
}
CLEAN_AS(func_020a55dc, SceneProcessBase_CanCreate)

/* func_020a5670: the display for a scene: the 2D engines reset, the 3D engine set up, the VRAM
 * banks given out (BG: F, OBJ: A, BG extended palettes: G, textures: B and C, texture
 * palettes: E), the light: vector (0, 0, -1 << 9) in white, white diffuse and ambient, no
 * specular or emission; then the 3D engine's state.
 * HW: the four lighting registers are written in this order. */
void SceneProcessBase_SetUpDisplay(void)
{
    DisplayFrame_Reset2D();
    G3X_Init();
    GX_SetBankForBG(BANK_BG_F);
    GX_SetBankForOBJ(BANK_OBJ_A);
    GX_SetBankForBGExtPltt(BANK_BGEXTPLTT_G);
    GX_SetBankForTex(BANK_TEX_BC);
    GX_SetBankForTexPltt(BANK_TEXPLTT_E);
    REG_LIGHT_VECTOR = 0x20000000;
    REG_LIGHT_COLOR = 0x7fff;
    REG_DIF_AMB = 0x7fff;
    REG_SPE_EMI = 0;
    Display3D_InitEngine();
}
CLEAN_AS(func_020a5670, SceneProcessBase_SetUpDisplay)

/* func_020a56d4: a process of this class made (0x50 bytes, zeroed, from the auxiliary heap)
 * with its execution and drawing stopped until its children are created
 * (SceneProcessBase_CanExecute); NULL when there is no room. */
Process *SceneProcessBase_New(void)
{
    Process *process = Heap_AllocAuxZeroed(SCENE_PROCESS_BASE_SIZE);
    if (process != NULL) {
        Process_Construct(process);
        process->vtable = data_020da13c;
        process->vtable = data_020e3c94;
        process->flags |= PROCESS_EXECUTE_STOPPED;
        process->flags |= PROCESS_DRAW_STOPPED;
    }
    return process;
}
CLEAN_AS(func_020a56d4, SceneProcessBase_New)
