/* The scene actor's modes (scene_actor_mode.h). */
#include "scene_actor_mode.h"

#include <stdint.h>

#include "clean.h"
#include "main/animated_model.h"    /* AnimatedModel_Start, AnimatedModel_StepFrames */
#include "main/event_queue.h"       /* EventQueue_RequestKind6, EventQueue_TestFlag8 */
#include "main/frame_ctrl.h"        /* FrameCtrl_IsDone, FrameCtrl_Passed */
#include "main/item_code.h"         /* ItemCode_HasVariant, ItemCode_VariantItem */
#include "main/map_code.h"          /* MapCode_IsStore */
#include "main/player_actor_ops.h"  /* PlayerActorOps_TestFlag */
#include "main/scene_object_base.h" /* SceneObjectBase_ClearApproach */
#include "main/scene_query.h"       /* SceneQuery_FieldObject */
#include "main/session_players.h"   /* SessionPlayers_ActorOf */
#include "main/touch_pick_shapes.h" /* TouchPick_ObjectOnPenDown */
#include "main/town_objects.h"      /* TownObjects_SetRecordedMode */
#include "main/town_tune.h"         /* TownTune_PlayAt */
#include "ov004/member_pointer.h"
#include "scene_actor_life.h" /* SceneActor_Kind */

static_assert(offsetof(SceneActor, close_wait) == 0x132, "close wait");
static_assert(offsetof(SceneActor, index) == 0x138, "index");
static_assert(offsetof(AnimatedModel, frames) == 0x9c, "animated model frames");

/* The vtable slots the modes call. */
#define SCENE_ACTOR_MODE_SLOT_POSITION 0xb4 /* SceneActor_Position (a Vec3 returned through `out`) */
#define SCENE_ACTOR_MODE_SLOT_ANIM_0 0x64   /* the first animation (SceneActor_JointAnim0) */
#define SCENE_ACTOR_MODE_SLOT_ANIM_1 0x68   /* the second (SceneActor_JointAnim1) */
#define SCENE_ACTOR_MODE_SLOT_SET_MODE 0x6c /* SceneActor_SetMode */
#define SCENE_ACTOR_MODE_SLOT_ASKS 0x8c     /* SceneActor_AsksToVisit */
#define SCENE_ACTOR_MODE_SLOT_TUNE 0x98     /* whether modes 1 and 2 play the melody (SceneActor_Slot98) */

/* How the animations are started: looping (mode 0) or once, at normal speed from frame 0. */
#define SCENE_ACTOR_ANIM_LOOP 0
#define SCENE_ACTOR_ANIM_ONCE 1
#define SCENE_ACTOR_ANIM_SPEED 0x1000

/* The sounds. */
#define SCENE_ACTOR_SOUND_SHOP_OPEN 0x806
#define SCENE_ACTOR_SOUND_SHOP_CLOSE 0x807
#define SCENE_ACTOR_SOUND_OPEN 0x808
#define SCENE_ACTOR_SOUND_CLOSE 0x809
#define SCENE_ACTOR_SOUND_MODE_START_A 0x7d1
#define SCENE_ACTOR_SOUND_MODE_START_B 0x7d2
#define SCENE_ACTOR_SOUND_MODE_FRAME_A 0x7d3
#define SCENE_ACTOR_SOUND_MODE_FRAME_B 0x7d4

/* The frames of modes 1 and 2 at which their two sounds play. */
#define SCENE_ACTOR_MODE_1_FRAME_A 0x14
#define SCENE_ACTOR_MODE_1_FRAME_B 0x1e
#define SCENE_ACTOR_MODE_2_FRAME_A 0x12
#define SCENE_ACTOR_MODE_2_FRAME_B 0x18

/* Mode 4 waits this many frames before the door closes. */
#define SCENE_ACTOR_CLOSE_WAIT 26

/* The buildings whose modes 1 and 2 play the melody, and as what kind. */
#define SCENE_ACTOR_TUNE_CODE_1 0x500d
#define SCENE_ACTOR_TUNE_CODE_2 0x5000
#define SCENE_ACTOR_TUNE_CODE_3 0x500c

/* Mode 0 asks nothing while flag 0x13 of this console's player is set. */
#define SCENE_ACTOR_MODE_PLAYER_FLAG 0x13
#define SCENE_ACTOR_MODE_PLAYER 4

/* The tables of runs and entries, filled once (member_pointer.h), and the constants they are
 * filled from. */
extern u32 data_ov009_02265b44;
extern MemberPointer data_ov009_02265bb4[SCENE_ACTOR_MODES];
extern const MemberPointer data_ov009_02265858, data_ov009_02265880, data_ov009_02265838, data_ov009_02265830,
    data_ov009_022657b0, data_ov009_022657a0, data_ov009_02265818;
extern u32 data_ov009_02265b24;
extern MemberPointer data_ov009_02265bec[SCENE_ACTOR_MODES];
extern const MemberPointer data_ov009_02265890, data_ov009_022657e8, data_ov009_02265800, data_ov009_02265878,
    data_ov009_02265870, data_ov009_02265868, data_ov009_02265860;

/* The address of the function in vtable slot `offset`. */
static uintptr_t mode_slot(const SceneActor *actor, u32 offset)
{
    return *(const u32 *) ((const u8 *) actor->vtable + offset);
}

static int mode_call_int(SceneActor *actor, u32 offset)
{
    return ((int (*)(SceneActor *)) mode_slot(actor, offset))(actor);
}

static int mode_set(SceneActor *actor, int mode)
{
    return ((int (*)(SceneActor *, int)) mode_slot(actor, SCENE_ACTOR_MODE_SLOT_SET_MODE))(actor, mode);
}

static void mode_position(SceneActor *actor, Vec3 *out)
{
    ((void (*)(Vec3 *, SceneActor *)) mode_slot(actor, SCENE_ACTOR_MODE_SLOT_POSITION))(out, actor);
}

static AnimatedModel *mode_model(SceneActor *actor)
{
    return (AnimatedModel *) (void *) actor->model_object;
}

/* Whether `*code` is `value`, through ItemCode_VariantItem when the code has variants. */
static int mode_code_is(u16 *code, u16 value)
{
    if (ItemCode_HasVariant(code)) {
        u16 other = value;
        int converted = ItemCode_VariantItem(code);
        return converted == ItemCode_VariantItem(&other);
    }
    return *code == value;
}

/* The animation of vtable slot `slot` started (`flags`); whether there was one. */
static int mode_start_anim(SceneActor *actor, u32 slot, int flags)
{
    int file = mode_call_int(actor, slot);
    if (file == 0) {
        return 0;
    }
    AnimatedModel_Start(mode_model(actor), (const u8 *) (uintptr_t) file, flags, SCENE_ACTOR_ANIM_SPEED, 0, 0);
    return 1;
}

/* The animation stepped; whether it is done. */
static int mode_step(SceneActor *actor)
{
    AnimatedModel_StepFrames(mode_model(actor));
    return FrameCtrl_IsDone(&mode_model(actor)->frames);
}

/* _ZN18Obj_ov009_022658dc19func_ov009_02263ab0Ev (run of mode 4): the wait counted down, the
 * closing sound (a shop's or another's) on its last frame; once it is over, the animation
 * stepped and mode 0 when it is done. */
void SceneActor_RunMode4(SceneActor *actor)
{
    if (actor->close_wait != 0) {
        actor->close_wait--;
        if (actor->close_wait == 0) {
            SceneActorSound_Play(&actor->sound,
                                 MapCode_IsStore(&actor->code) ? SCENE_ACTOR_SOUND_SHOP_CLOSE : SCENE_ACTOR_SOUND_CLOSE);
        }
    }
    if (actor->close_wait == 0 && mode_step(actor)) {
        mode_set(actor, 0);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263ab0Ev, SceneActor_RunMode4)

/* func_ov009_02263b34 (entry of mode 4): the wait set, then the second animation started once;
 * whether there is one.
 * QUIRK: the wait is set even when the mode is refused. */
int SceneActor_EnterMode4(SceneActor *actor)
{
    actor->close_wait = SCENE_ACTOR_CLOSE_WAIT;
    return mode_start_anim(actor, SCENE_ACTOR_MODE_SLOT_ANIM_1, SCENE_ACTOR_ANIM_ONCE);
}
CLEAN_AS(func_ov009_02263b34, SceneActor_EnterMode4)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263b78Ev (run of mode 3): the animation stepped, mode 4
 * when it is done. */
void SceneActor_RunMode3(SceneActor *actor)
{
    if (mode_step(actor)) {
        mode_set(actor, 4);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263b78Ev, SceneActor_RunMode3)

/* func_ov009_02263ba8 (entry of mode 3): the first animation started once and the opening
 * sound (a shop's or another's); whether there is an animation. */
int SceneActor_EnterMode3(SceneActor *actor)
{
    if (!mode_start_anim(actor, SCENE_ACTOR_MODE_SLOT_ANIM_0, SCENE_ACTOR_ANIM_ONCE)) {
        return 0;
    }
    SceneActorSound_Play(&actor->sound, MapCode_IsStore(&actor->code) ? SCENE_ACTOR_SOUND_SHOP_OPEN : SCENE_ACTOR_SOUND_OPEN);
    return 1;
}
CLEAN_AS(func_ov009_02263ba8, SceneActor_EnterMode3)

/* The runs of modes 1 and 2: the animation stepped, mode 0 when it is done, else a sound at
 * either of two frames. */
static void mode_run_with_sounds(SceneActor *actor, int frame_a, int frame_b)
{
    if (mode_step(actor)) {
        mode_set(actor, 0);
    } else if (FrameCtrl_Passed(&mode_model(actor)->frames, frame_a)) {
        SceneActorSound_Play(&actor->sound, SCENE_ACTOR_SOUND_MODE_FRAME_A);
    } else if (FrameCtrl_Passed(&mode_model(actor)->frames, frame_b)) {
        SceneActorSound_Play(&actor->sound, SCENE_ACTOR_SOUND_MODE_FRAME_B);
    }
}

/* The entries of modes 1 and 2: the animation of `slot` started once with two sounds; when
 * vtable slot 0x98 says so, the melody played at its position, as kind 1, 2 or 3 for three
 * buildings and 0 for the others. Whether there is an animation. */
static int mode_enter_with_sounds(SceneActor *actor, u32 slot)
{
    if (!mode_start_anim(actor, slot, SCENE_ACTOR_ANIM_ONCE)) {
        return 0;
    }
    SceneActorSound_Play(&actor->sound, SCENE_ACTOR_SOUND_MODE_START_A);
    SceneActorSound_Play(&actor->sound, SCENE_ACTOR_SOUND_MODE_START_B);
    if (mode_call_int(actor, SCENE_ACTOR_MODE_SLOT_TUNE) == 0) {
        return 1;
    }
    int kind = 0;
    if (mode_code_is(&actor->code, SCENE_ACTOR_TUNE_CODE_1)) {
        kind = 1;
    } else if (mode_code_is(&actor->code, SCENE_ACTOR_TUNE_CODE_2)) {
        kind = 2;
    } else if (mode_code_is(&actor->code, SCENE_ACTOR_TUNE_CODE_3)) {
        kind = 3;
    }
    Vec3 position;
    mode_position(actor, &position);
    TownTune_PlayAt(&position, kind);
    return 1;
}

/* _ZN18Obj_ov009_022658dc19func_ov009_02263c14Ev (run of mode 2) */
void SceneActor_RunMode2(SceneActor *actor)
{
    mode_run_with_sounds(actor, SCENE_ACTOR_MODE_2_FRAME_A, SCENE_ACTOR_MODE_2_FRAME_B);
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263c14Ev, SceneActor_RunMode2)

/* func_ov009_02263c84 (entry of mode 2): with the second animation. */
int SceneActor_EnterMode2(SceneActor *actor)
{
    return mode_enter_with_sounds(actor, SCENE_ACTOR_MODE_SLOT_ANIM_1);
}
CLEAN_AS(func_ov009_02263c84, SceneActor_EnterMode2)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263de8Ev (run of mode 1) */
void SceneActor_RunMode1(SceneActor *actor)
{
    mode_run_with_sounds(actor, SCENE_ACTOR_MODE_1_FRAME_A, SCENE_ACTOR_MODE_1_FRAME_B);
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263de8Ev, SceneActor_RunMode1)

/* func_ov009_02263e58 (entry of mode 1): with the first animation. */
int SceneActor_EnterMode1(SceneActor *actor)
{
    return mode_enter_with_sounds(actor, SCENE_ACTOR_MODE_SLOT_ANIM_0);
}
CLEAN_AS(func_ov009_02263e58, SceneActor_EnterMode1)

/* Asks for the event of kind 6 that takes the player in: the visit record is skipped unless
 * vtable slot 0x8c says to ask for it. */
static void mode_request_entry(SceneActor *actor)
{
    if (mode_call_int(actor, SCENE_ACTOR_MODE_SLOT_ASKS) == 0) {
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
 * player in when an actor of kind 1 or 3 was walked into fast (SCENE_ACTOR_FLAG_RUN_IN), or
 * else when the player stands at a door (SCENE_ACTOR_FLAG_AT_DOOR) and the pen has just come
 * down on the player's own actor. */
void SceneActor_RunMode0(SceneActor *actor)
{
    if (PlayerActorOps_TestFlag(SCENE_ACTOR_MODE_PLAYER_FLAG, SCENE_ACTOR_MODE_PLAYER) != 0) {
        return;
    }
    if (EventQueue_TestFlag8() != 0) {
        return;
    }
    int kind = SceneActor_Kind(actor);
    if ((kind == 1 || kind == 3) && (actor->flags_235 & SCENE_ACTOR_FLAG_RUN_IN)) {
        mode_request_entry(actor);
        return;
    }
    if (!(actor->flags_235 & SCENE_ACTOR_FLAG_AT_DOOR)) {
        return;
    }
    int picked = TouchPick_ObjectOnPenDown((TouchPick *) (uintptr_t) SceneQuery_FieldObject(), NULL, NULL);
    void *player = SessionPlayers_ActorOf(SCENE_ACTOR_MODE_PLAYER);
    if (player == NULL || (int) (uintptr_t) player != picked) {
        return;
    }
    mode_request_entry(actor);
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263fbcEv, SceneActor_RunMode0)

/* func_ov009_02264090 (entry of mode 0): for kinds 1 and 2 the first animation started,
 * looping; refused when there is none. Other kinds always enter. */
int SceneActor_EnterMode0(SceneActor *actor)
{
    switch (SceneActor_Kind(actor)) {
        case 1:
        case 2: {
            int file = mode_call_int(actor, SCENE_ACTOR_MODE_SLOT_ANIM_0);
            if (file == 0) {
                return 0;
            }
            AnimatedModel_Start(mode_model(actor), (const u8 *) (uintptr_t) file, SCENE_ACTOR_ANIM_LOOP,
                                SCENE_ACTOR_ANIM_SPEED, 0, 0);
            break;
        }
        default:
            break;
    }
    return 1;
}
CLEAN_AS(func_ov009_02264090, SceneActor_EnterMode0)

/* _ZN18Obj_ov009_022658dc8vfunc_74Ev (vtable slot 0x74): the mode's run, through its table. */
void SceneActor_RunMode(SceneActor *actor)
{
    static const MemberPointer *const runs[SCENE_ACTOR_MODES] = {
        &data_ov009_02265858, /* SceneActor_RunMode0 */
        &data_ov009_02265880, /* SceneActor_RunMode1 */
        &data_ov009_02265838, /* SceneActor_RunMode2 */
        &data_ov009_02265830, /* SceneActor_RunMode3 */
        &data_ov009_022657b0, /* SceneActor_RunMode4 */
        &data_ov009_022657a0, /* SceneActor_RunMode5 */
        &data_ov009_02265818, /* SceneActor_RunMode6 */
    };
    MemberTable_InitOnce(&data_ov009_02265b44, data_ov009_02265bb4, runs, SCENE_ACTOR_MODES);
    if (actor->mode < SCENE_ACTOR_MODES) {
        MemberPointer_CallVoid(&data_ov009_02265bb4[actor->mode], actor);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc8vfunc_74Ev, SceneActor_RunMode)

/* func_ov009_0226418c (vtable slot 0x6c): enters `mode` if its entry (through a table) agrees
 * and main takes it as the building's recorded mode; whether it did. Modes 7 and above do not
 * exist. */
int SceneActor_SetMode(SceneActor *actor, unsigned int mode)
{
    static const MemberPointer *const entries[SCENE_ACTOR_MODES] = {
        &data_ov009_02265890, /* SceneActor_EnterMode0 */
        &data_ov009_022657e8, /* SceneActor_EnterMode1 */
        &data_ov009_02265800, /* SceneActor_EnterMode2 */
        &data_ov009_02265878, /* SceneActor_EnterMode3 */
        &data_ov009_02265870, /* SceneActor_EnterMode4 */
        &data_ov009_02265868, /* SceneActor_EnterMode5 */
        &data_ov009_02265860, /* SceneActor_EnterMode6 */
    };
    MemberTable_InitOnce(&data_ov009_02265b24, data_ov009_02265bec, entries, SCENE_ACTOR_MODES);
    if (mode >= SCENE_ACTOR_MODES) {
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
CLEAN_AS(func_ov009_0226418c, SceneActor_SetMode)
