/* The states of the scene actor of "sp_etc_sequence4" held here (sequence4.h). */
#include "sequence4.h"

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "clean.h"
#include "field_actor_states87.h"
#include "main/actor.h"
#include "main/animated_model.h"
#include "main/event_queue.h"
#include "main/frame_ctrl.h"
#include "main/player_actor_ops.h"
#include "main/player_record.h"
#include "main/player_records.h"
#include "main/scene_exit.h"
#include "main/scene_place.h"
#include "main/scene_query.h"
#include "main/scene_tables.h"
#include "main/session_players.h"
#include "main/state_block.h"
#include "main/talk_object.h"
#include "ov003/field_actor.h" /* FieldActor_PlayerRequestState39 */
#include "ov003/object_actors.h"

static_assert(offsetof(SceneActor, model_object) == 0x13c, "model");
static_assert(offsetof(SceneActor, sound) == 0x238, "sound");
static_assert(offsetof(Sequence4, state) == 0x2b4, "state");
static_assert(offsetof(Sequence4, stand) == 0x2c0, "stand");
static_assert(offsetof(Sequence4, effect_point) == 0x2cc, "effect point");
static_assert(offsetof(Sequence4, timer) == 0x2d8, "timer");
static_assert(offsetof(Sequence4, look_frames) == 0x2da, "look frames");
static_assert(offsetof(Sequence4, wait) == 0x2db, "wait");
static_assert(offsetof(Sequence4, frames) == 0x2dc, "frames");
static_assert(offsetof(AnimatedModel, frames) == 0x9c, "model frames");

#define SEQUENCE4_PLAYER 4         /* this console's player */
#define SEQUENCE4_BUILDING 0x5000  /* the building the sequences lead into and out of */
#define SEQUENCE4_SLOT_ANIM_A 0x64 /* vtable slots giving animations */
#define SEQUENCE4_SLOT_ANIM_B 0x68
#define SEQUENCE4_ANIM_FLAGS 1
#define SEQUENCE4_ANIM_SPEED 0x1000

/* Its sounds (SceneActorSound_Play once, SceneActorSound_PlayEx each frame). */
#define SEQUENCE4_SOUND_A 0x888
#define SEQUENCE4_SOUND_LOOP 0x889
#define SEQUENCE4_SOUND_B 0x88a
#define SEQUENCE4_SOUND_C 0x88b

/* The player's head follows it while it is within this of where the player faces. */
#define SEQUENCE4_LOOK_REACH 0x1200
#define SEQUENCE4_MOVE_ACCEL 0x400

#define SEQUENCE4_FRAMES_MAX 200
#define SEQUENCE4_WALK_FRAME 0x10 /* state 6: the look's frame the player walks off at */
#define SEQUENCE4_STAND_STEP 0x200
#define SEQUENCE4_ENTER_FRAMES 0x14
#define SEQUENCE4_ENTER_EXIT 9
#define SEQUENCE4_ENTER_STEP 0x1000
#define SEQUENCE4_ENTER_PLAYER_PARAM 0x0f000000
#define SEQUENCE4_CALL_WAIT 0x10
#define SEQUENCE4_CALL_STEP 0x4000
#define SEQUENCE4_LOOK_FRAMES 0x1e
#define SEQUENCE4_LEAVE_FRAMES 0x41
#define SEQUENCE4_LEAVE_SCENE 0x2c
#define SEQUENCE4_STAND_YAW (-0x8000)
#define SEQUENCE4_HALF_TURN 0x8000

/* State 16's frames left (s16, counted down to -1). */
extern s16 data_ov068_022786c8;
extern StateBlock data_021dc7a8;

/* Its member func_ov068_02272a7c: the state's entry runs and, when it answers nonzero, the state
 * is taken; whether it was. */
extern int _ZN18Obj_ov068_0227775019func_ov068_02272a7cEi(Sequence4 *actor, int state);
/* Its third animation (overlay 9's func_ov009_02264d18). */
extern int func_ov068_02272dc8(Sequence4 *actor);
/* The yaw from where this console's player stood when its frame began to the effect point moved
 * 0x30a along x; 0 without the player. */
extern int func_ov068_02272cd4(Sequence4 *actor);
/* Over frames 0x25-0x32 of its animation the effect at 0x2e4 is moved to the effect point
 * (func_ov068_02272c30 runs first at frame 0x25, func_ov068_02272bd4 after it at 0x32). */
extern void func_ov068_02272be4(Sequence4 *actor);
/* The same over frames 0x2d-0x31 for the effect at 0x2e0 (func_ov068_02272cb0 and
 * func_ov068_02272c54). */
extern void func_ov068_02272c64(Sequence4 *actor);

typedef int (*Sequence4Slot)(Sequence4 *actor);

static void set_state(Sequence4 *actor, int state)
{
    _ZN18Obj_ov068_0227775019func_ov068_02272a7cEi(actor, state);
}

static AnimatedModel *sequence4_model(Sequence4 *actor)
{
    return (AnimatedModel *) (void *) actor->base.model_object;
}

static int animation_done(Sequence4 *actor)
{
    return FrameCtrl_IsDone(&sequence4_model(actor)->frames) != 0;
}

static void step_animation(Sequence4 *actor)
{
    AnimatedModel_StepFrames(sequence4_model(actor));
}

static void start_animation(Sequence4 *actor, int file)
{
    AnimatedModel_Start(sequence4_model(actor), (const u8 *) (uintptr_t) (u32) file, SEQUENCE4_ANIM_FLAGS,
                        SEQUENCE4_ANIM_SPEED, 0, 0);
}

/* Its vtable slot `offset`, called virtually. */
static int call_slot(Sequence4 *actor, int offset)
{
    Sequence4Slot slot = (Sequence4Slot) (uintptr_t) *(const u32 *) ((const u8 *) actor->base.vtable + offset);
    return slot(actor);
}

/* The player turns its head to it while it is within SEQUENCE4_LOOK_REACH of where the player
 * faces; whether it was. */
static int player_looks(Sequence4 *actor, const Actor *player)
{
    s16 facing = player->angle[1];
    if (Math_AbsDiff16(facing, func_ov068_02272cd4(actor)) < SEQUENCE4_LOOK_REACH) {
        PlayerActorOps_SetLook(0, (s16) (func_ov068_02272cd4(actor) - facing), SEQUENCE4_PLAYER);
        return 1;
    }
    return 0;
}

/* func_ov068_022720b4 (update of state 16): once its frames are out, event flag 1 is cleared,
 * the entry record's exit is set to scene 0x2c, and the current player's record is cleared and
 * forgotten by the state block; the frames count down to -1. */
void Sequence4_UpdateState16(Sequence4 *actor)
{
    (void) actor;
    if (data_ov068_022786c8 == 0) {
        EventQueue_ClearFlag1();
        SceneExit_SetToScene((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), SEQUENCE4_LEAVE_SCENE, 2, 2);
        PlayerRecord_Clear(PlayerRecords_Current());
        StateBlock_ForgetPlayer(&data_021dc7a8, PlayerRecords_CurrentNumber());
    }
    if (data_ov068_022786c8 >= 0) {
        data_ov068_022786c8--;
    }
}
CLEAN_AS(func_ov068_022720b4, Sequence4_UpdateState16)

/* func_ov068_02272104 (entry of state 16): 0x41 frames. */
int Sequence4_EnterState16(Sequence4 *actor)
{
    (void) actor;
    data_ov068_022786c8 = SEQUENCE4_LEAVE_FRAMES;
    return 1;
}
CLEAN_AS(func_ov068_02272104, Sequence4_EnterState16)

/* func_ov068_02272114 (update of state 15): sound 0x889; at the animation's end, state 16; its
 * effects follow (func_ov068_02272be4) and the animation steps. */
void Sequence4_UpdateState15(Sequence4 *actor)
{
    SceneActorSound_PlayEx(&actor->base.sound, SEQUENCE4_SOUND_LOOP);
    if (animation_done(actor)) {
        set_state(actor, 16);
    }
    func_ov068_02272be4(actor);
    step_animation(actor);
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_02272114Ev, Sequence4_UpdateState15)

/* func_ov068_0227215c (entry of state 15): the third animation, and sound 0x88b. */
int Sequence4_EnterState15(Sequence4 *actor)
{
    start_animation(actor, func_ov068_02272dc8(actor));
    SceneActorSound_Play(&actor->base.sound, SEQUENCE4_SOUND_C);
    return 1;
}
CLEAN_AS(func_ov068_0227215c, Sequence4_EnterState15)

/* func_ov068_022721a0 (update of state 14): once its look frames are out, state 15; while they
 * run, the player looks straight ahead and they count down. The animation steps. */
void Sequence4_UpdateState14(Sequence4 *actor)
{
    if (actor->look_frames == 0) {
        set_state(actor, 15);
    }
    if (actor->look_frames != 0) {
        PlayerActorOps_SetLook(0, 0, SEQUENCE4_PLAYER);
        actor->look_frames--;
    }
    step_animation(actor);
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_022721a0Ev, Sequence4_UpdateState14)

/* func_ov068_022721e4 (entry of state 14): 30 look frames; taken when the player takes field
 * actor state 0x88. */
int Sequence4_EnterState14(Sequence4 *actor)
{
    actor->look_frames = SEQUENCE4_LOOK_FRAMES;
    return FieldActor_PlayerRequestState88() != 0;
}
CLEAN_AS(func_ov068_022721e4, Sequence4_EnterState14)

/* func_ov068_02272208 (update of state 13): at the animation's end, state 14; the animation
 * steps. */
void Sequence4_UpdateState13(Sequence4 *actor)
{
    if (animation_done(actor)) {
        set_state(actor, 14);
    }
    step_animation(actor);
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_02272208Ev, Sequence4_UpdateState13)

/* func_ov068_02272238 (entry of state 13): the animation of slot 0x68, and sound 0x88a. */
int Sequence4_EnterState13(Sequence4 *actor)
{
    start_animation(actor, call_slot(actor, SEQUENCE4_SLOT_ANIM_B));
    SceneActorSound_Play(&actor->base.sound, SEQUENCE4_SOUND_B);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_02272238Ev, Sequence4_EnterState13)

/* func_ov068_0227227c (update of state 12): sound 0x888; at the animation's end, state 13; its
 * effects follow (func_ov068_02272c64), the animation steps, and the player (when there is
 * one) looks at it. */
void Sequence4_UpdateState12(Sequence4 *actor)
{
    SceneActorSound_PlayEx(&actor->base.sound, SEQUENCE4_SOUND_A);
    if (animation_done(actor)) {
        set_state(actor, 13);
    }
    func_ov068_02272c64(actor);
    step_animation(actor);
    const Actor *player = (const Actor *) SessionPlayers_ActorOf(SEQUENCE4_PLAYER);
    if (player != NULL) {
        player_looks(actor, player);
    }
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_0227227cEv, Sequence4_UpdateState12)

/* func_ov068_02272304 (entry of state 12): the animation of slot 0x64. */
int Sequence4_EnterState12(Sequence4 *actor)
{
    start_animation(actor, call_slot(actor, SEQUENCE4_SLOT_ANIM_A));
    return 1;
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_02272304Ev, Sequence4_EnterState12)

/* func_ov068_02272338 (update of state 11): with building 0x5000 back in mode 0, once its wait
 * is out, the player (when there is one) walks to 4.0 along z from where it stands; when the
 * walk is taken, state 12. The wait counts down while the building is in mode 0. */
void Sequence4_UpdateState11(Sequence4 *actor)
{
    SceneActor *building = ObjectActors_FindByCode(SEQUENCE4_BUILDING);
    if (building == NULL || SceneActor_IsInMode0(building) == 0) {
        return;
    }
    const Actor *player = (const Actor *) SessionPlayers_ActorOf(SEQUENCE4_PLAYER);
    if (player != NULL && actor->wait == 0) {
        Vec3 to = player->position;
        to.z += SEQUENCE4_CALL_STEP;
        if (PlayerActorOps_MoveTo(&to, SEQUENCE4_MOVE_ACCEL, SEQUENCE4_PLAYER) != 0) {
            set_state(actor, 12);
        }
    }
    if (actor->wait != 0) {
        actor->wait--;
    }
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_02272338Ev, Sequence4_UpdateState11)

/* func_ov068_022723b4 (entry of state 11): with building 0x5000, a wait of 16 frames and the
 * building's mode set by its kind (SceneActor_SetModeByKindA), whose answer it gives; 1
 * without the building. */
int Sequence4_EnterState11(Sequence4 *actor)
{
    SceneActor *building = ObjectActors_FindByCode(SEQUENCE4_BUILDING);
    if (building != NULL) {
        actor->wait = SEQUENCE4_CALL_WAIT;
        return SceneActor_SetModeByKindA(building);
    }
    return 1;
}
CLEAN_AS(func_ov068_022723b4, Sequence4_EnterState11)

/* func_ov068_022723e0 (update of state 10): state 11. */
void Sequence4_UpdateState10(Sequence4 *actor)
{
    set_state(actor, 11);
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_022723e0Ev, Sequence4_UpdateState10)

/* func_ov068_022723ec (entry of state 10): event flag 1 and the object actors' pose flag set. */
int Sequence4_EnterState10(Sequence4 *actor)
{
    (void) actor;
    EventQueue_SetFlag1();
    ObjectActors_SetPoseFlag(1);
    return 1;
}
CLEAN_AS(func_ov068_022723ec, Sequence4_EnterState10)

/* func_ov068_02272404 (update of state 9): its timer counts down; once out, with building
 * 0x5000 and its stand point, the entry record's exit 9 is taken and the place the player
 * appears at is marked: 1.0 along z beyond the stand point, turned half round from it, in the
 * current scene, at the building's tile; event flag 1 is cleared. */
void Sequence4_UpdateState9(Sequence4 *actor)
{
    if (actor->timer != 0) {
        actor->timer--;
    }
    if (actor->timer != 0) {
        return;
    }
    SceneActor *building = ObjectActors_FindByCode(SEQUENCE4_BUILDING);
    if (building == NULL) {
        return;
    }
    Vec3 point;
    s16 angle;
    if (SceneActor_GetStandPoint(building, &point, &angle) == 0) {
        return;
    }
    SceneExit_Take((SceneExit *) (uintptr_t) SceneTables_EntryRecord(), SEQUENCE4_ENTER_EXIT);
    point.z += SEQUENCE4_ENTER_STEP;
    int entry = SceneTables_EntryRecord();
    int scene = SceneQuery_Current();
    ScenePlace_SetMarked(entry, scene, &point, SEQUENCE4_ENTER_PLAYER_PARAM, (s16) (angle + SEQUENCE4_HALF_TURN),
                         actor->tile_x, actor->tile_z);
    EventQueue_ClearFlag1();
}
CLEAN_AS(func_ov068_02272404, Sequence4_UpdateState9)

/* func_ov068_022724a4 (entry of state 9): 20 frames. */
int Sequence4_EnterState9(Sequence4 *actor)
{
    actor->timer = SEQUENCE4_ENTER_FRAMES;
    return 1;
}
CLEAN_AS(func_ov068_022724a4, Sequence4_EnterState9)

/* func_ov068_022724b4 (update of state 8): with building 0x5000, its mode is set by its kind
 * (SceneActor_SetModeByKindB), its tile kept, and state 9 follows. */
void Sequence4_UpdateState8(Sequence4 *actor)
{
    SceneActor *building = ObjectActors_FindByCode(SEQUENCE4_BUILDING);
    if (building == NULL) {
        return;
    }
    SceneActor_SetModeByKindB(building);
    actor->tile_x = SceneActor_TileX(building);
    actor->tile_z = (int) SceneActor_TileZ(building);
    set_state(actor, 9);
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_022724b4Ev, Sequence4_UpdateState8)

/* func_ov068_022724fc (entry of state 8): taken when the player agrees to stand at the stand
 * point facing 0x8000 (FieldActor_PlayerRequestState39, kind 1). */
int Sequence4_EnterState8(Sequence4 *actor)
{
    return FieldActor_PlayerRequestState39(1, (int *) (void *) &actor->stand.x, (int *) (void *) &actor->stand.z,
                                           SEQUENCE4_STAND_YAW) != 0;
}
CLEAN_AS(func_ov068_022724fc, Sequence4_EnterState8)

/* func_ov068_02272530 (update of state 7): once the player is no longer busy, state 8. */
void Sequence4_UpdateState7(Sequence4 *actor)
{
    if (PlayerActorOps_IsBusy(SEQUENCE4_PLAYER) == 0) {
        set_state(actor, 8);
    }
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_02272530Ev, Sequence4_UpdateState7)

/* func_ov068_0227254c (entry of state 7) */
int Sequence4_EnterState7(Sequence4 *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov068_0227254c, Sequence4_EnterState7)

/* func_ov068_02272550 (update of state 6): sound 0x889 and its effects follow
 * (func_ov068_02272be4); at the animation's end, state 7 and nothing more. Else the animation
 * steps, and with a player: the player looks at it, or else its frames count (to 200); at the
 * 16th, with building 0x5000 and its stand point, the player looks straight and walks to 1/8
 * along z beyond the stand point (kept in `stand`). */
void Sequence4_UpdateState6(Sequence4 *actor)
{
    SceneActorSound_PlayEx(&actor->base.sound, SEQUENCE4_SOUND_LOOP);
    func_ov068_02272be4(actor);
    if (animation_done(actor)) {
        set_state(actor, 7);
        return;
    }
    step_animation(actor);
    const Actor *player = (const Actor *) SessionPlayers_ActorOf(SEQUENCE4_PLAYER);
    if (player == NULL || player_looks(actor, player)) {
        return;
    }
    if (actor->frames < SEQUENCE4_FRAMES_MAX) {
        actor->frames++;
    }
    if (actor->frames != SEQUENCE4_WALK_FRAME) {
        return;
    }
    SceneActor *building = ObjectActors_FindByCode(SEQUENCE4_BUILDING);
    if (building == NULL) {
        return;
    }
    Vec3 point;
    s16 angle;
    if (SceneActor_GetStandPoint(building, &point, &angle) != 0) {
        actor->stand = point;
        actor->stand.z += SEQUENCE4_STAND_STEP;
        PlayerActorOps_SetLook(0, 0, SEQUENCE4_PLAYER);
        PlayerActorOps_MoveTo(&actor->stand, SEQUENCE4_MOVE_ACCEL, SEQUENCE4_PLAYER);
    }
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_02272550Ev, Sequence4_UpdateState6)

/* func_ov068_02272654 (entry of state 6): the third animation, sound 0x88b, and its frames
 * from 0. */
int Sequence4_EnterState6(Sequence4 *actor)
{
    start_animation(actor, func_ov068_02272dc8(actor));
    SceneActorSound_Play(&actor->base.sound, SEQUENCE4_SOUND_C);
    actor->frames = 0;
    return 1;
}
CLEAN_AS(func_ov068_02272654, Sequence4_EnterState6)

/* func_ov068_022726a0 (update of state 5): once talk 0 has closed, the talk lets go of its
 * receiver and state 6 follows. */
void Sequence4_UpdateState5(Sequence4 *actor)
{
    TalkObject *talk = TalkObject_Get(0);
    if (talk->state == TALK_OBJECT_CLOSED) {
        TalkObject_DetachReceiver(talk);
        set_state(actor, 6);
    }
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_022726a0Ev, Sequence4_UpdateState5)

/* func_ov068_022726c4 (entry of state 5) */
int Sequence4_EnterState5(Sequence4 *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov068_022726c4, Sequence4_EnterState5)

/* func_ov068_022726c8 (update of state 4, whose entry started the talk): state 5. */
void Sequence4_UpdateState4(Sequence4 *actor)
{
    set_state(actor, 5);
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_022726c8Ev, Sequence4_UpdateState4)
