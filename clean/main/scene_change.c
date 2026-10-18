/* The process between scenes and its neighbours' destructors (scene_change.h). */
#include "scene_change.h"

#include "clean.h"
#include "main/ab_all_obj.h"
#include "main/display_frame.h"
#include "main/global_021dc5b0.h"
#include "main/scene_sound.h"
#include "main/session.h"
#include "ov004/member_pointer.h"
#include "link_scene.h"
#include "scene_display.h"
#include "scene_process_base.h"
#include "transition_mark.h"

static_assert(offsetof(SceneChange, step) == 0x50, "step");
static_assert(sizeof(SceneChange) == 0x54, "scene change");

#define SCENE_CHANGE_STEPS 3
/* The link's states (func_020a6ea0): the one waited for and the one it is moved on to. */
#define SCENE_CHANGE_LINK_READY 0x0b
#define SCENE_CHANGE_LINK_GOING 0x0c
/* The next scene's process class and what it is asked for with. */
#define SCENE_CHANGE_NEXT_CLASS 6
#define SCENE_CHANGE_NEXT_PARAM 3

/* The classes' vtables, the scene base class's and the processes' root class's. */
extern const u32 data_020e5408[];
extern const u32 data_020e5460[];
extern const u32 data_020e5574[];
extern const u32 data_020e3c94[];
extern const u32 data_020da13c[];

/* The steps' member pointers: the table SceneChange_Update calls through (filled once, bit 0 of
 * the guard) and its constants. */
extern u32 data_021f6910;
extern MemberPointer data_021f6914[SCENE_CHANGE_STEPS];
extern const MemberPointer data_020e53f8; /* SceneChange_WaitLink */
extern const MemberPointer data_020e53f0; /* SceneChange_Start */
extern const MemberPointer data_020e53e8; /* SceneChange_Idle */

extern NetSession *data_020ccf94;
extern DisplayFrameHooks *data_021c8ca0; /* the running scene's hooks, or NULL */

/* func_020b5abc (vtable slot 16): the destructor: the class's vtable, the scene base class's
 * and the root class's in turn, then the process destructor. */
SceneChange *SceneChange_Destruct(SceneChange *change)
{
    change->base.vtable = data_020e5408;
    change->base.vtable = data_020e3c94;
    change->base.vtable = data_020da13c;
    Process_Destruct(&change->base);
    return change;
}
CLEAN_AS(func_020b5abc, SceneChange_Destruct)

/* func_020b5ae4 (slot 17): destroyed (SceneChange_Destruct) and freed. */
SceneChange *SceneChange_Delete(SceneChange *change)
{
    change->base.vtable = data_020e5408;
    change->base.vtable = data_020e3c94;
    change->base.vtable = data_020da13c;
    Process_Destruct(&change->base);
    Heap_FreeAux(change);
    return change;
}
CLEAN_AS(func_020b5ae4, SceneChange_Delete)

/* func_020b5b14 (slot 9): done. */
int SceneChange_Slot9(void)
{
    return 1;
}
CLEAN_AS(func_020b5b14, SceneChange_Slot9)

/* func_020b5b18 (slot 6): the step's function, through the table of member pointers (filled
 * from its constants the first time); always 1. */
int SceneChange_Update(SceneChange *change)
{
    static const MemberPointer *const steps[SCENE_CHANGE_STEPS] = {
        &data_020e53f8, /* SceneChange_WaitLink */
        &data_020e53f0, /* SceneChange_Start */
        &data_020e53e8, /* SceneChange_Idle */
    };
    MemberTable_InitOnce(&data_021f6910, data_021f6914, steps, SCENE_CHANGE_STEPS);
    MemberPointer_CallVoid(&data_021f6914[change->step], change);
    return 1;
}
CLEAN_AS(func_020b5b18, SceneChange_Update)

/* func_020b5b8c (slot 3): the running scene's display hooks cleared and the scene's display
 * taken down; done. */
int SceneChange_End(void)
{
    data_021c8ca0 = NULL;
    SceneDisplay_TearDown();
    return 1;
}
CLEAN_AS(func_020b5b8c, SceneChange_End)

/* func_020b5ba8 (slot 0): waits for the link when this system's slot of the session is taken,
 * else starts at once; the scene's sound made, the display set up, the shared objects loaded
 * and func_0208f930's step; done. */
int SceneChange_Init(SceneChange *change)
{
    NetSession *session = data_020ccf94;

    if (Session_IsSlotTaken(session, session->local_slot) != 0) {
        change->step = SCENE_CHANGE_WAIT_LINK;
    } else {
        change->step = SCENE_CHANGE_START;
    }
    SceneSound_Create();
    SceneDisplay_SetUp();
    AbAllObj_LoadAndUpload();
    TransitionMark_Restore();
    return 1;
}
CLEAN_AS(func_020b5ba8, SceneChange_Init)

/* func_020b5be0 (step 2): nothing. */
void SceneChange_Idle(SceneChange *change)
{
    (void) change;
}
CLEAN_AS(func_020b5be0, SceneChange_Idle)

/* func_020b5be4 (step 1): process class 6 asked for, with 3 and the byte kept for it; then
 * idle. */
void SceneChange_Start(SceneChange *change)
{
    int kept = Global021dc5b0_Get();
    SceneProcessBase_Request(SCENE_CHANGE_NEXT_CLASS, SCENE_CHANGE_NEXT_PARAM, kept, 1);
    change->step = SCENE_CHANGE_IDLE;
}
CLEAN_AS(func_020b5be4, SceneChange_Start)

/* func_020b5c04 (step 0): once the link's state is 0x0b, it is moved on to 0x0c and the next
 * scene started. */
void SceneChange_WaitLink(SceneChange *change)
{
    if (LinkScene_GlobalPhase() == SCENE_CHANGE_LINK_READY) {
        LinkScene_GlobalSetPhase(SCENE_CHANGE_LINK_GOING);
        SceneChange_Start(change);
    }
}
CLEAN_AS(func_020b5c04, SceneChange_WaitLink)

/* The scene base class's part of a construction: its vtable after the root class's, and flags
 * 1 and 4 set. */
static void scene_change_construct_scene(Process *process)
{
    process->vtable = data_020da13c;
    process->vtable = data_020e3c94;
    process->flags |= PROCESS_EXECUTE_STOPPED;
    process->flags |= PROCESS_DRAW_STOPPED;
}

/* func_020b5c24 (the profile's create): a new process between scenes, zeroed and constructed;
 * NULL when there is no memory. */
SceneChange *SceneChange_New(void)
{
    SceneChange *change = Heap_AllocAuxZeroed(sizeof(SceneChange));
    if (change != NULL) {
        Process_Construct(&change->base);
        scene_change_construct_scene(&change->base);
        change->base.vtable = data_020e5408;
    }
    return change;
}
CLEAN_AS(func_020b5c24, SceneChange_New)

/* func_020b5c68 (class 4's create): likewise for class 4. */
Process *SceneClass4_New(void)
{
    Process *process = Heap_AllocAuxZeroed(sizeof(Process));
    if (process != NULL) {
        Process_Construct(process);
        scene_change_construct_scene(process);
        process->vtable = data_020e5460;
    }
    return process;
}
CLEAN_AS(func_020b5c68, SceneClass4_New)

/* A destructor's vtables in turn (the class's, the scene base class's, the root class's), then
 * the process destructor. */
static void scene_change_destruct(Process *process, const u32 *vtable)
{
    process->vtable = vtable;
    process->vtable = data_020e3c94;
    process->vtable = data_020da13c;
    Process_Destruct(process);
}

/* func_020b5cac (class 4's slot 16): the destructor. */
Process *SceneClass4_Destruct(Process *process)
{
    scene_change_destruct(process, data_020e5460);
    return process;
}
CLEAN_AS(func_020b5cac, SceneClass4_Destruct)

/* func_020b5cd4 (class 4's slot 17): destroyed and freed. */
Process *SceneClass4_Delete(Process *process)
{
    scene_change_destruct(process, data_020e5460);
    Heap_FreeAux(process);
    return process;
}
CLEAN_AS(func_020b5cd4, SceneClass4_Delete)

/* func_020b5d04 (class 6's slot 16): the destructor. */
Process *SceneClass6_Destruct(Process *process)
{
    scene_change_destruct(process, data_020e5574);
    return process;
}
CLEAN_AS(func_020b5d04, SceneClass6_Destruct)

/* func_020b5d2c (class 6's slot 17): destroyed and freed. */
Process *SceneClass6_Delete(Process *process)
{
    scene_change_destruct(process, data_020e5574);
    Heap_FreeAux(process);
    return process;
}
CLEAN_AS(func_020b5d2c, SceneClass6_Delete)
