/* The town object actor's modes (town_object_actor_mode.h). */
#include "town_object_actor_mode.h"

#include <stdint.h>

#include "clean.h"
#include "main/animated_model.h"    /* AnimatedModel_Start, AnimatedModel_StepFrames */
#include "main/event_queue.h"       /* EventQueue_RequestKind6, EventQueue_TestFlag8 */
#include "main/frame_ctrl.h"        /* FrameControl_IsDone, FrameControl_Passed */
#include "main/item_code.h"         /* ItemCode_IsFurniture, ItemCode_FurnitureNumber */
#include "main/map_code.h"          /* MapCode_IsStore */
#include "main/player_actor_ops.h"  /* PlayerActorOps_TestFlag */
#include "main/scene_object_base.h" /* SceneObjectBase_ClearApproach */
#include "main/scene_query.h"       /* SceneQuery_FieldObject */
#include "main/session_players.h"   /* SessionPlayers_ActorOf */
#include "main/touch_pick_shapes.h" /* TouchPick_ObjectOnPenDown */
#include "main/town_objects.h"      /* TownObjects_SetRecordedMode */
#include "main/town_tune.h"         /* TownTune_PlayAt */
#include "ov004/member_pointer.h"
#include "town_object_actor_life.h" /* TownObjectActor_Kind */

static_assert(offsetof(TownObjectActor, close_wait) == 0x132, "close wait");
static_assert(offsetof(TownObjectActor, index) == 0x138, "index");
static_assert(offsetof(AnimatedModel, frames) == 0x9c, "animated model frames");

/* The vtable slots the modes call. */
#define TOWN_OBJECT_ACTOR_MODE_SLOT_POSITION 0xb4 /* TownObjectActor_Position (a Vec3 returned through `out`) */
#define TOWN_OBJECT_ACTOR_MODE_SLOT_ANIM_0 0x64   /* the first animation (TownObjectActor_JointAnim0) */
#define TOWN_OBJECT_ACTOR_MODE_SLOT_ANIM_1 0x68   /* the second (TownObjectActor_JointAnim1) */
#define TOWN_OBJECT_ACTOR_MODE_SLOT_SET_MODE 0x6c /* TownObjectActor_SetMode */
#define TOWN_OBJECT_ACTOR_MODE_SLOT_IS_OPEN 0x8c  /* TownObjectActor_IsOpen */
#define TOWN_OBJECT_ACTOR_MODE_SLOT_TUNE 0x98     /* whether modes 1 and 2 play the melody (TownObjectActor_Slot98) */

/* How the animations are started: looping (mode 0) or once, at normal speed from frame 0. */
#define TOWN_OBJECT_ACTOR_ANIM_LOOP 0
#define TOWN_OBJECT_ACTOR_ANIM_ONCE 1
#define TOWN_OBJECT_ACTOR_ANIM_SPEED 0x1000

/* The sounds. */
#define TOWN_OBJECT_ACTOR_SOUND_SHOP_OPEN 0x806
#define TOWN_OBJECT_ACTOR_SOUND_SHOP_CLOSE 0x807
#define TOWN_OBJECT_ACTOR_SOUND_OPEN 0x808
#define TOWN_OBJECT_ACTOR_SOUND_CLOSE 0x809
#define TOWN_OBJECT_ACTOR_SOUND_MODE_START_A 0x7d1
#define TOWN_OBJECT_ACTOR_SOUND_MODE_START_B 0x7d2
#define TOWN_OBJECT_ACTOR_SOUND_MODE_FRAME_A 0x7d3
#define TOWN_OBJECT_ACTOR_SOUND_MODE_FRAME_B 0x7d4

/* The frames of modes 1 and 2 at which their two sounds play. */
#define TOWN_OBJECT_ACTOR_MODE_1_FRAME_A 0x14
#define TOWN_OBJECT_ACTOR_MODE_1_FRAME_B 0x1e
#define TOWN_OBJECT_ACTOR_MODE_2_FRAME_A 0x12
#define TOWN_OBJECT_ACTOR_MODE_2_FRAME_B 0x18

/* Mode 4 waits this many frames before the door closes. */
#define TOWN_OBJECT_ACTOR_CLOSE_WAIT 26

/* The buildings whose modes 1 and 2 play the melody, and as what kind: Nook's store, the town
 * hall and the tailor. */
#define TOWN_OBJECT_ACTOR_TUNE_STORE 0x500d
#define TOWN_OBJECT_ACTOR_TUNE_TOWN_HALL 0x5000
#define TOWN_OBJECT_ACTOR_TUNE_TAILOR 0x500c

/* Mode 0 asks nothing while flag 0x13 of this console's player is set. */
#define TOWN_OBJECT_ACTOR_MODE_PLAYER_FLAG 0x13
#define TOWN_OBJECT_ACTOR_MODE_PLAYER 4

/* The tables of runs and entries, filled once (member_pointer.h), and the constants they are
 * filled from. */
extern u32 data_ov009_02265b44;
extern MemberPointer data_ov009_02265bb4[TOWN_OBJECT_ACTOR_MODES];
extern const MemberPointer data_ov009_02265858, data_ov009_02265880, data_ov009_02265838, data_ov009_02265830,
    data_ov009_022657b0, data_ov009_022657a0, data_ov009_02265818;
extern u32 data_ov009_02265b24;
extern MemberPointer data_ov009_02265bec[TOWN_OBJECT_ACTOR_MODES];
extern const MemberPointer data_ov009_02265890, data_ov009_022657e8, data_ov009_02265800, data_ov009_02265878,
    data_ov009_02265870, data_ov009_02265868, data_ov009_02265860;

/* The address of the function in vtable slot `offset`. */
static uintptr_t mode_slot(const TownObjectActor *actor, u32 offset)
{
    return *(const u32 *) ((const u8 *) actor->vtable + offset);
}

static int mode_call_int(TownObjectActor *actor, u32 offset)
{
    return ((int (*)(TownObjectActor *)) mode_slot(actor, offset))(actor);
}

static int mode_set(TownObjectActor *actor, int mode)
{
    return ((int (*)(TownObjectActor *, int)) mode_slot(actor, TOWN_OBJECT_ACTOR_MODE_SLOT_SET_MODE))(actor, mode);
}

static void mode_position(TownObjectActor *actor, Vec3 *out)
{
    ((void (*)(Vec3 *, TownObjectActor *)) mode_slot(actor, TOWN_OBJECT_ACTOR_MODE_SLOT_POSITION))(out, actor);
}

static AnimatedModel *mode_model(TownObjectActor *actor)
{
    return (AnimatedModel *) (void *) actor->model_object;
}

/* Whether `*code` is `value`, through ItemCode_FurnitureNumber when the code is furniture. */
static int mode_code_is(u16 *code, u16 value)
{
    if (ItemCode_IsFurniture(code)) {
        u16 other = value;
        int converted = ItemCode_FurnitureNumber(code);
        return converted == ItemCode_FurnitureNumber(&other);
    }
    return *code == value;
}

/* The animation of vtable slot `slot` started (`flags`); whether there was one. */
static int mode_start_anim(TownObjectActor *actor, u32 slot, int flags)
{
    int file = mode_call_int(actor, slot);
    if (file == 0) {
        return 0;
    }
    AnimatedModel_Start(mode_model(actor), (const u8 *) (uintptr_t) file, flags, TOWN_OBJECT_ACTOR_ANIM_SPEED, 0, 0);
    return 1;
}

/* The animation stepped; whether it is done. */
static int mode_step(TownObjectActor *actor)
{
    AnimatedModel_StepFrames(mode_model(actor));
    return FrameControl_IsDone(&mode_model(actor)->frames);
}

/* _ZN18Obj_ov009_022658dc19func_ov009_02263ab0Ev (run of mode 4): the wait counted down, the
 * closing sound (a shop's or another's) on its last frame; once it is over, the animation
 * stepped and mode 0 when it is done. */
void TownObjectActor_RunMode4(TownObjectActor *actor)
{
    if (actor->close_wait != 0) {
        actor->close_wait--;
        if (actor->close_wait == 0) {
            TownObjectActorSound_Play(&actor->sound, MapCode_IsStore(&actor->code) ? TOWN_OBJECT_ACTOR_SOUND_SHOP_CLOSE
                                                                                   : TOWN_OBJECT_ACTOR_SOUND_CLOSE);
        }
    }
    if (actor->close_wait == 0 && mode_step(actor)) {
        mode_set(actor, 0);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263ab0Ev, TownObjectActor_RunMode4)

/* func_ov009_02263b34 (entry of mode 4): the wait set, then the second animation started once;
 * whether there is one.
 * QUIRK: the wait is set even when the mode is refused. */
int TownObjectActor_EnterMode4(TownObjectActor *actor)
{
    actor->close_wait = TOWN_OBJECT_ACTOR_CLOSE_WAIT;
    return mode_start_anim(actor, TOWN_OBJECT_ACTOR_MODE_SLOT_ANIM_1, TOWN_OBJECT_ACTOR_ANIM_ONCE);
}
CLEAN_AS(func_ov009_02263b34, TownObjectActor_EnterMode4)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263b78Ev (run of mode 3): the animation stepped, mode 4
 * when it is done. */
void TownObjectActor_RunMode3(TownObjectActor *actor)
{
    if (mode_step(actor)) {
        mode_set(actor, 4);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263b78Ev, TownObjectActor_RunMode3)

/* func_ov009_02263ba8 (entry of mode 3): the first animation started once and the opening
 * sound (a shop's or another's); whether there is an animation. */
int TownObjectActor_EnterMode3(TownObjectActor *actor)
{
    if (!mode_start_anim(actor, TOWN_OBJECT_ACTOR_MODE_SLOT_ANIM_0, TOWN_OBJECT_ACTOR_ANIM_ONCE)) {
        return 0;
    }
    TownObjectActorSound_Play(&actor->sound, MapCode_IsStore(&actor->code) ? TOWN_OBJECT_ACTOR_SOUND_SHOP_OPEN
                                                                           : TOWN_OBJECT_ACTOR_SOUND_OPEN);
    return 1;
}
CLEAN_AS(func_ov009_02263ba8, TownObjectActor_EnterMode3)

/* The runs of modes 1 and 2: the animation stepped, mode 0 when it is done, else a sound at
 * either of two frames. */
static void mode_run_with_sounds(TownObjectActor *actor, int frame_a, int frame_b)
{
    if (mode_step(actor)) {
        mode_set(actor, 0);
    } else if (FrameControl_Passed(&mode_model(actor)->frames, frame_a)) {
        TownObjectActorSound_Play(&actor->sound, TOWN_OBJECT_ACTOR_SOUND_MODE_FRAME_A);
    } else if (FrameControl_Passed(&mode_model(actor)->frames, frame_b)) {
        TownObjectActorSound_Play(&actor->sound, TOWN_OBJECT_ACTOR_SOUND_MODE_FRAME_B);
    }
}

/* The entries of modes 1 and 2: the animation of `slot` started once with two sounds; when
 * vtable slot 0x98 says so, the melody played at its position, as kind 1, 2 or 3 for three
 * buildings and 0 for the others. Whether there is an animation. */
static int mode_enter_with_sounds(TownObjectActor *actor, u32 slot)
{
    if (!mode_start_anim(actor, slot, TOWN_OBJECT_ACTOR_ANIM_ONCE)) {
        return 0;
    }
    TownObjectActorSound_Play(&actor->sound, TOWN_OBJECT_ACTOR_SOUND_MODE_START_A);
    TownObjectActorSound_Play(&actor->sound, TOWN_OBJECT_ACTOR_SOUND_MODE_START_B);
    if (mode_call_int(actor, TOWN_OBJECT_ACTOR_MODE_SLOT_TUNE) == 0) {
        return 1;
    }
    int kind = 0;
    if (mode_code_is(&actor->code, TOWN_OBJECT_ACTOR_TUNE_STORE)) {
        kind = 1;
    } else if (mode_code_is(&actor->code, TOWN_OBJECT_ACTOR_TUNE_TOWN_HALL)) {
        kind = 2;
    } else if (mode_code_is(&actor->code, TOWN_OBJECT_ACTOR_TUNE_TAILOR)) {
        kind = 3;
    }
    Vec3 position;
    mode_position(actor, &position);
    TownTune_PlayAt(&position, kind);
    return 1;
}

/* _ZN18Obj_ov009_022658dc19func_ov009_02263c14Ev (run of mode 2) */
void TownObjectActor_RunMode2(TownObjectActor *actor)
{
    mode_run_with_sounds(actor, TOWN_OBJECT_ACTOR_MODE_2_FRAME_A, TOWN_OBJECT_ACTOR_MODE_2_FRAME_B);
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263c14Ev, TownObjectActor_RunMode2)

/* func_ov009_02263c84 (entry of mode 2): with the second animation. */
int TownObjectActor_EnterMode2(TownObjectActor *actor)
{
    return mode_enter_with_sounds(actor, TOWN_OBJECT_ACTOR_MODE_SLOT_ANIM_1);
}
CLEAN_AS(func_ov009_02263c84, TownObjectActor_EnterMode2)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263de8Ev (run of mode 1) */
void TownObjectActor_RunMode1(TownObjectActor *actor)
{
    mode_run_with_sounds(actor, TOWN_OBJECT_ACTOR_MODE_1_FRAME_A, TOWN_OBJECT_ACTOR_MODE_1_FRAME_B);
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263de8Ev, TownObjectActor_RunMode1)

/* func_ov009_02263e58 (entry of mode 1): with the first animation. */
int TownObjectActor_EnterMode1(TownObjectActor *actor)
{
    return mode_enter_with_sounds(actor, TOWN_OBJECT_ACTOR_MODE_SLOT_ANIM_0);
}
CLEAN_AS(func_ov009_02263e58, TownObjectActor_EnterMode1)

/* Asks for the event of kind 6 that takes the player in: the visit record is skipped unless
 * vtable slot 0x8c (TownObjectActor_IsOpen) says it is open. */
static void mode_request_entry(TownObjectActor *actor)
{
    if (mode_call_int(actor, TOWN_OBJECT_ACTOR_MODE_SLOT_IS_OPEN) == 0) {
        SceneObjectBase_ClearApproach((SceneObjectBase *) (void *) actor);
        actor->skip_visit = 1;
    } else {
        SceneObjectBase_ClearApproach((SceneObjectBase *) (void *) actor);
        actor->skip_visit = 0;
    }
    EventQueue_RequestKind6(actor, 0);
}

/* _ZN18Obj_ov009_022658dc19func_ov009_02263fbcEv (run of mode 0): unless flag 0x13 of this
 * console's player or the event queue's flag 8 is set, asks for the event that takes the
 * player in when an actor of kind 1 or 3 was walked into fast (TOWN_OBJECT_ACTOR_FLAG_RUN_IN), or
 * else when the player stands at a door (TOWN_OBJECT_ACTOR_FLAG_AT_DOOR) and the pen has just come
 * down on the player's own actor. */
void TownObjectActor_RunMode0(TownObjectActor *actor)
{
    if (PlayerActorOps_TestFlag(TOWN_OBJECT_ACTOR_MODE_PLAYER_FLAG, TOWN_OBJECT_ACTOR_MODE_PLAYER) != 0) {
        return;
    }
    if (EventQueue_TestFlag8() != 0) {
        return;
    }
    int kind = TownObjectActor_Kind(actor);
    if ((kind == 1 || kind == 3) && (actor->flags_235 & TOWN_OBJECT_ACTOR_FLAG_RUN_IN)) {
        mode_request_entry(actor);
        return;
    }
    if (!(actor->flags_235 & TOWN_OBJECT_ACTOR_FLAG_AT_DOOR)) {
        return;
    }
    int picked = TouchPick_ObjectOnPenDown((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), NULL, NULL);
    void *player = SessionPlayers_ActorOf(TOWN_OBJECT_ACTOR_MODE_PLAYER);
    if (player == NULL || (int) (uintptr_t) player != picked) {
        return;
    }
    mode_request_entry(actor);
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263fbcEv, TownObjectActor_RunMode0)

/* func_ov009_02264090 (entry of mode 0): for kinds 1 and 2 the first animation started,
 * looping; refused when there is none. Other kinds always enter. */
int TownObjectActor_EnterMode0(TownObjectActor *actor)
{
    switch (TownObjectActor_Kind(actor)) {
        case 1:
        case 2: {
            int file = mode_call_int(actor, TOWN_OBJECT_ACTOR_MODE_SLOT_ANIM_0);
            if (file == 0) {
                return 0;
            }
            AnimatedModel_Start(mode_model(actor), (const u8 *) (uintptr_t) file, TOWN_OBJECT_ACTOR_ANIM_LOOP,
                                TOWN_OBJECT_ACTOR_ANIM_SPEED, 0, 0);
            break;
        }
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_ov009_02264090, TownObjectActor_EnterMode0)

/* _ZN18Obj_ov009_022658dc8vfunc_74Ev (vtable slot 0x74): the mode's run, through its table. */
void TownObjectActor_RunMode(TownObjectActor *actor)
{
    static const MemberPointer *const runs[TOWN_OBJECT_ACTOR_MODES] = {
        &data_ov009_02265858, /* TownObjectActor_RunMode0 */
        &data_ov009_02265880, /* TownObjectActor_RunMode1 */
        &data_ov009_02265838, /* TownObjectActor_RunMode2 */
        &data_ov009_02265830, /* TownObjectActor_RunMode3 */
        &data_ov009_022657b0, /* TownObjectActor_RunMode4 */
        &data_ov009_022657a0, /* TownObjectActor_RunMode5 */
        &data_ov009_02265818, /* TownObjectActor_RunMode6 */
    };
    MemberTable_InitOnce(&data_ov009_02265b44, data_ov009_02265bb4, runs, TOWN_OBJECT_ACTOR_MODES);
    if (actor->mode < TOWN_OBJECT_ACTOR_MODES) {
        MemberPointer_CallVoid(&data_ov009_02265bb4[actor->mode], actor);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc8vfunc_74Ev, TownObjectActor_RunMode)

/* func_ov009_0226418c (vtable slot 0x6c): enters `mode` if its entry (through a table) agrees
 * and main takes it as the building's recorded mode; whether it did. Modes 7 and above do not
 * exist. */
int TownObjectActor_SetMode(TownObjectActor *actor, unsigned int mode)
{
    static const MemberPointer *const entries[TOWN_OBJECT_ACTOR_MODES] = {
        &data_ov009_02265890, /* TownObjectActor_EnterMode0 */
        &data_ov009_022657e8, /* TownObjectActor_EnterMode1 */
        &data_ov009_02265800, /* TownObjectActor_EnterMode2 */
        &data_ov009_02265878, /* TownObjectActor_EnterMode3 */
        &data_ov009_02265870, /* TownObjectActor_EnterMode4 */
        &data_ov009_02265868, /* TownObjectActor_EnterMode5 */
        &data_ov009_02265860, /* TownObjectActor_EnterMode6 */
    };
    MemberTable_InitOnce(&data_ov009_02265b24, data_ov009_02265bec, entries, TOWN_OBJECT_ACTOR_MODES);
    if (mode >= TOWN_OBJECT_ACTOR_MODES) {
        return 0;
    }
    if (MemberPointer_CallInt(&data_ov009_02265bec[mode], actor) == 0) {
        return 0;
    }
    if (TownObjects_SetRecordedMode(actor->code, (u8) mode) == 0) {
        return 0;
    }
    actor->mode = (u8) mode;
    return 1;
}
CLEAN_AS(func_ov009_0226418c, TownObjectActor_SetMode)
