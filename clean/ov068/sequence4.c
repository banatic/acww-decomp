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

/* States 0 to 4, the state machine itself, its effects and the class's own slots. State 0 does
 * nothing (its entry starts the animation of slot 0x64); state 1 (entry: that animation and
 * event flag 1) waits for the player and moves to state 2; state 2 plays the animation of slot
 * 0x64 with sound 0x888 and effect 0x41 over frames 0x2d-0x31, then state 3; state 3 (entry:
 * field actor state 0x87 for the player, the animation of slot 0x68 and sound 0x88a) counts
 * frames once that animation is done: at the 18th the player turns to the effect point, at the
 * 28th state 4; state 4's entry starts its talk. */

#include "autoload_2/fx_math.h" /* Math_Atan2 */
#include "autoload_2/heap.h"
#include "itcm/vector.h" /* Vec_Add */
#include "main/block_020b220c.h"
#include "main/effect_system.h"
#include "main/message_receiver.h"
#include "main/npc_lookup.h"
#include "main/player_id.h"
#include "main/talk_receiver.h"
#include "ov004/member_pointer.h"

static_assert(offsetof(Sequence4, frames_2dd) == 0x2dd, "frames 2dd");
static_assert(offsetof(Sequence4, flag_2de) == 0x2de, "flag 2de");
static_assert(offsetof(Sequence4, effect_b) == 0x2e0, "effect b");
static_assert(offsetof(Sequence4, effect_a) == 0x2e4, "effect a");
static_assert(sizeof(Sequence4) == 0x2e8, "the size Sequence4_New allocates");
static_assert(offsetof(SceneActor, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(SceneActor, message) == 0x10a, "message");
static_assert(offsetof(AnimatedModelNodeState, joint) == 0xb4, "joint");
static_assert(offsetof(AnimatedModelJoint, translation) == 0x4c, "translation");

#define SEQUENCE4_STATES 17
#define SEQUENCE4_RECEIVER_OFFSET 0xec
#define SEQUENCE4_TALK 0          /* the talk object its talk runs on */
#define SEQUENCE4_SPEAKER 0xd014  /* the speaker: special character 0x14 (npc_lookup.h) */
#define SEQUENCE4_TURN_FRAME 0x12 /* state 3: the frame the player turns at */
#define SEQUENCE4_TALK_FRAME 0x1c /* state 3: the frame state 4 follows at */
#define SEQUENCE4_EFFECT_A 0x42   /* the effect over frames 0x25-0x32 of the animation */
#define SEQUENCE4_EFFECT_A_FIRST 0x25
#define SEQUENCE4_EFFECT_A_LAST 0x32
#define SEQUENCE4_EFFECT_B 0x41 /* the effect over frames 0x2d-0x31 */
#define SEQUENCE4_EFFECT_B_FIRST 0x2d
#define SEQUENCE4_EFFECT_B_LAST 0x31
#define SEQUENCE4_AHEAD_NUMERATOR 0x19000 /* the effect point ahead: 25.0 / 100.0 ... */
#define SEQUENCE4_AHEAD_DENOMINATOR 0x64000
#define SEQUENCE4_AHEAD_BACK 0xf6 /* ... less 0xf6, along x */
#define SEQUENCE4_NO_ITEM 0xfff1  /* the item code of an empty hand */
#define SEQUENCE4_ID_MESSAGE 1    /* the message when the player's id byte 0x1c is 1 */

/* The vtables: the class's and its receiver part's. */
extern const u8 data_ov068_02277750[];
extern const u8 data_ov068_02277814[];
/* "sp_etc_sequence4", its talk's message file. */
extern const char data_ov068_02277890[];

/* The state tables (ov004/member_pointer.h): the updates' guard, table and constants, then the
 * entries'. */
extern u32 data_ov068_022786cc;
extern MemberPointer data_ov068_02278774[SEQUENCE4_STATES];
extern const MemberPointer data_ov068_02277660, data_ov068_02277668, data_ov068_02277688, data_ov068_022776c8,
    data_ov068_02277708, data_ov068_02277720, data_ov068_02277640, data_ov068_02277638, data_ov068_02277628,
    data_ov068_02277648, data_ov068_02277680, data_ov068_02277678, data_ov068_022776d0, data_ov068_02277728,
    data_ov068_02277620, data_ov068_02277650, data_ov068_02277658;
extern u32 data_ov068_022786e8;
extern MemberPointer data_ov068_022786ec[SEQUENCE4_STATES];
extern const MemberPointer data_ov068_02277670, data_ov068_02277700, data_ov068_022776f8, data_ov068_022776f0,
    data_ov068_022776e8, data_ov068_022776d8, data_ov068_022776e0, data_ov068_02277710, data_ov068_02277718,
    data_ov068_022776c0, data_ov068_022776b8, data_ov068_022776b0, data_ov068_022776a8, data_ov068_022776a0,
    data_ov068_02277698, data_ov068_02277690, data_ov068_02277630;

/* Overlay 9's scene actor: its third animation, its destructor and its constructor. */
extern int func_ov009_02264d18(Sequence4 *actor);
extern void *func_ov009_0226539c(Sequence4 *actor);
extern void *func_ov009_0226552c(Sequence4 *actor);

extern fx32 FX_Div(fx32 numerator, fx32 denominator);

static TalkReceiver *sequence4_receiver(Sequence4 *actor)
{
    return (TalkReceiver *) (void *) &actor->base.receiver_vtable;
}

/* The whole frame its animation is at. */
static unsigned int sequence4_frame(Sequence4 *actor)
{
    return (u16) ((u32) sequence4_model(actor)->frames.frame >> 12);
}

/* func_ov068_022726d4 (entry of state 4): talk 0 takes its receiver, reset and named
 * "sp_etc_sequence4", with message 1 when the current player's id byte 0x1c is 1, else
 * message 0; the talk is asked to open, and the speaker is special character 0x14. */
int Sequence4_EnterState4(Sequence4 *actor)
{
    TalkObject *talk = TalkObject_Get(SEQUENCE4_TALK);
    TalkReceiver *receiver = sequence4_receiver(actor);
    TalkReceiver_Reset(receiver);
    MessageReceiver_SetName(&receiver->base, data_ov068_02277890);
    u8 *record = PlayerRecords_Current();
    int message = 0;
    if (record != NULL && PlayerId_Byte1c((const s8 *) (void *) PlayerRecord_Player(record)) == SEQUENCE4_ID_MESSAGE) {
        message = SEQUENCE4_ID_MESSAGE;
    }
    actor->base.message = (u8) message;
    TalkObject_AttachReceiver(talk, receiver);
    talk->next_state = TALK_OBJECT_OPENING;

    PlayerIdText name;
    PlayerIdText_Construct(&name);
    ItemCode speaker = SEQUENCE4_SPEAKER;
    NpcLookup_FormatPersonName(&name, &speaker);
    /* the text's characters, through its vtable */
    typedef const char *(*Sequence4TextChars)(PlayerIdText *text);
    const char *chars = ((Sequence4TextChars) (uintptr_t) name.vtable->buffer)(&name);
    TalkReceiver_SetSpeaker(receiver, chars, 0);
    PlayerIdText_Destruct(&name);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_022726d4Ev, Sequence4_EnterState4)

/* func_ov068_0227276c (update of state 3): once the animation is done, its frames count (to
 * 200): at the 18th the player's own flag 0x17 is set and the player turns to the effect point;
 * at the 28th, state 4. Until then the animation steps. */
void Sequence4_UpdateState3(Sequence4 *actor)
{
    if (!animation_done(actor)) {
        step_animation(actor);
        return;
    }
    switch (actor->frames_2dd) {
        case SEQUENCE4_TURN_FRAME:
            PlayerActorOps_SetOwnFlag17();
            PlayerActorOps_Turn(Sequence4_YawToEffect(actor), SEQUENCE4_PLAYER);
            break;
        case SEQUENCE4_TALK_FRAME:
            set_state(actor, 4);
            break;
        default:
            break;
    }
    if (actor->frames_2dd < SEQUENCE4_FRAMES_MAX) {
        actor->frames_2dd++;
    }
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_0227276cEv, Sequence4_UpdateState3)

/* func_ov068_022727d0 (entry of state 3): its frames from 0; taken when the player takes field
 * actor state 0x87, then the animation of slot 0x68 and sound 0x88a. */
int Sequence4_EnterState3(Sequence4 *actor)
{
    actor->frames_2dd = 0;
    if (FieldActor_PlayerRequestState87() == NULL) {
        return 0;
    }
    start_animation(actor, call_slot(actor, SEQUENCE4_SLOT_ANIM_B));
    SceneActorSound_Play(&actor->base.sound, SEQUENCE4_SOUND_B);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_022727d0Ev, Sequence4_EnterState3)

/* func_ov068_0227282c (update of state 2): sound 0x888; at the animation's end, state 3; effect
 * 0x41 follows (Sequence4_FollowEffectB) and the animation steps. */
void Sequence4_UpdateState2(Sequence4 *actor)
{
    SceneActorSound_PlayEx(&actor->base.sound, SEQUENCE4_SOUND_A);
    if (animation_done(actor)) {
        set_state(actor, 3);
    }
    Sequence4_FollowEffectB(actor);
    step_animation(actor);
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_0227282cEv, Sequence4_UpdateState2)

/* func_ov068_02272874 (entry of state 2): the animation of slot 0x64. */
int Sequence4_EnterState2(Sequence4 *actor)
{
    start_animation(actor, call_slot(actor, SEQUENCE4_SLOT_ANIM_A));
    return 1;
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_02272874Ev, Sequence4_EnterState2)

/* func_ov068_022728a8 (update of state 1): once this console's player has an actor, state 2. */
void Sequence4_UpdateState1(Sequence4 *actor)
{
    if (SessionPlayers_ActorOf(SEQUENCE4_PLAYER) != NULL) {
        set_state(actor, 2);
    }
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_022728a8Ev, Sequence4_UpdateState1)

/* func_ov068_022728c4 (entry of state 1): the animation of slot 0x64, and event flag 1 set. */
int Sequence4_EnterState1(Sequence4 *actor)
{
    start_animation(actor, call_slot(actor, SEQUENCE4_SLOT_ANIM_A));
    EventQueue_SetFlag1();
    return 1;
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_022728c4Ev, Sequence4_EnterState1)

/* func_ov068_022728fc (update of state 0) */
void Sequence4_UpdateState0(void *actor)
{
    (void) actor;
}
CLEAN_AS(func_ov068_022728fc, Sequence4_UpdateState0)

/* func_ov068_02272900 (entry of state 0): the animation of slot 0x64. */
int Sequence4_EnterState0(Sequence4 *actor)
{
    start_animation(actor, call_slot(actor, SEQUENCE4_SLOT_ANIM_A));
    return 1;
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_02272900Ev, Sequence4_EnterState0)

/* func_ov068_02272934: the update of its state runs (through a table filled once). States 17
 * and above do nothing. */
void Sequence4_UpdateState(Sequence4 *actor)
{
    static const MemberPointer *const updates[SEQUENCE4_STATES] = {
        &data_ov068_02277660, /* Sequence4_UpdateState0 */
        &data_ov068_02277668, /* Sequence4_UpdateState1 */
        &data_ov068_02277688, /* Sequence4_UpdateState2 */
        &data_ov068_022776c8, /* Sequence4_UpdateState3 */
        &data_ov068_02277708, /* Sequence4_UpdateState4 */
        &data_ov068_02277720, /* Sequence4_UpdateState5 */
        &data_ov068_02277640, /* Sequence4_UpdateState6 */
        &data_ov068_02277638, /* Sequence4_UpdateState7 */
        &data_ov068_02277628, /* Sequence4_UpdateState8 */
        &data_ov068_02277648, /* Sequence4_UpdateState9 */
        &data_ov068_02277680, /* Sequence4_UpdateState10 */
        &data_ov068_02277678, /* Sequence4_UpdateState11 */
        &data_ov068_022776d0, /* Sequence4_UpdateState12 */
        &data_ov068_02277728, /* Sequence4_UpdateState13 */
        &data_ov068_02277620, /* Sequence4_UpdateState14 */
        &data_ov068_02277650, /* Sequence4_UpdateState15 */
        &data_ov068_02277658, /* Sequence4_UpdateState16 */
    };
    MemberTable_InitOnce(&data_ov068_022786cc, data_ov068_02278774, updates, SEQUENCE4_STATES);
    /* REQUIRES: state >= 0 (the entries set 0 to 16); the ROM's signed test lets a negative one
     * index before the table */
    if (actor->state >= 0 && actor->state < SEQUENCE4_STATES) {
        MemberPointer_CallVoid(&data_ov068_02278774[actor->state], actor);
    }
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_02272934Ev, Sequence4_UpdateState)

/* func_ov068_02272a7c: enters `state` if its entry (through a table filled once) agrees;
 * whether it did. States 17 and above do not exist. */
int Sequence4_SetState(Sequence4 *actor, int state)
{
    static const MemberPointer *const entries[SEQUENCE4_STATES] = {
        &data_ov068_02277670, /* Sequence4_EnterState0 */
        &data_ov068_02277700, /* Sequence4_EnterState1 */
        &data_ov068_022776f8, /* Sequence4_EnterState2 */
        &data_ov068_022776f0, /* Sequence4_EnterState3 */
        &data_ov068_022776e8, /* Sequence4_EnterState4 */
        &data_ov068_022776d8, /* Sequence4_EnterState5 */
        &data_ov068_022776e0, /* Sequence4_EnterState6 */
        &data_ov068_02277710, /* Sequence4_EnterState7 */
        &data_ov068_02277718, /* Sequence4_EnterState8 */
        &data_ov068_022776c0, /* Sequence4_EnterState9 */
        &data_ov068_022776b8, /* Sequence4_EnterState10 */
        &data_ov068_022776b0, /* Sequence4_EnterState11 */
        &data_ov068_022776a8, /* Sequence4_EnterState12 */
        &data_ov068_022776a0, /* Sequence4_EnterState13 */
        &data_ov068_02277698, /* Sequence4_EnterState14 */
        &data_ov068_02277690, /* Sequence4_EnterState15 */
        &data_ov068_02277630, /* Sequence4_EnterState16 */
    };
    MemberTable_InitOnce(&data_ov068_022786e8, data_ov068_022786ec, entries, SEQUENCE4_STATES);
    /* REQUIRES: state >= 0 (the game passes 0 to 16); the ROM's signed test lets a negative one
     * index before the table */
    if (state >= 0 && state < SEQUENCE4_STATES && MemberPointer_CallInt(&data_ov068_022786ec[state], actor) != 0) {
        actor->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_02272a7cEi, Sequence4_SetState)

/* func_ov068_02272bd4: effect 0x42 ended. */
void Sequence4_EndEffectA(Sequence4 *actor)
{
    EffectSystem_EndHandle(actor->effect_a);
}
CLEAN_AS(func_ov068_02272bd4, Sequence4_EndEffectA)

/* func_ov068_02272be4: over frames 0x25-0x32 of its animation, effect 0x42 is at the effect
 * point: started at the first, moved there each frame, ended after the move at the last. */
void Sequence4_FollowEffectA(Sequence4 *actor)
{
    unsigned int frame = sequence4_frame(actor);
    if (frame < SEQUENCE4_EFFECT_A_FIRST || frame > SEQUENCE4_EFFECT_A_LAST) {
        return;
    }
    if (frame == SEQUENCE4_EFFECT_A_FIRST) {
        Sequence4_StartEffectA(actor);
    }
    EffectSystem_MoveHandle(actor->effect_a, &actor->effect_point, NULL, NULL);
    if (frame == SEQUENCE4_EFFECT_A_LAST) {
        Sequence4_EndEffectA(actor);
    }
}
CLEAN_AS(func_ov068_02272be4, Sequence4_FollowEffectA)

/* func_ov068_02272c30: effect 0x42 started at the effect point. */
void Sequence4_StartEffectA(Sequence4 *actor)
{
    actor->effect_a = EffectSystem_StartKind(SEQUENCE4_EFFECT_A, &actor->effect_point, NULL, NULL);
}
CLEAN_AS(func_ov068_02272c30, Sequence4_StartEffectA)

/* func_ov068_02272c54: effect 0x41 ended. */
void Sequence4_EndEffectB(Sequence4 *actor)
{
    EffectSystem_EndHandle(actor->effect_b);
}
CLEAN_AS(func_ov068_02272c54, Sequence4_EndEffectB)

/* func_ov068_02272c64: as Sequence4_FollowEffectA, for effect 0x41 over frames 0x2d-0x31. */
void Sequence4_FollowEffectB(Sequence4 *actor)
{
    unsigned int frame = sequence4_frame(actor);
    if (frame < SEQUENCE4_EFFECT_B_FIRST || frame > SEQUENCE4_EFFECT_B_LAST) {
        return;
    }
    if (frame == SEQUENCE4_EFFECT_B_FIRST) {
        Sequence4_StartEffectB(actor);
    }
    EffectSystem_MoveHandle(actor->effect_b, &actor->effect_point, NULL, NULL);
    if (frame == SEQUENCE4_EFFECT_B_LAST) {
        Sequence4_EndEffectB(actor);
    }
}
CLEAN_AS(func_ov068_02272c64, Sequence4_FollowEffectB)

/* func_ov068_02272cb0: effect 0x41 started at the effect point. */
void Sequence4_StartEffectB(Sequence4 *actor)
{
    actor->effect_b = EffectSystem_StartKind(SEQUENCE4_EFFECT_B, &actor->effect_point, NULL, NULL);
}
CLEAN_AS(func_ov068_02272cb0, Sequence4_StartEffectB)

/* func_ov068_02272cd4: the yaw from where this console's player stood when its frame began to
 * the effect point moved ahead (Sequence4_EffectPointAhead); 0 without the player. */
int Sequence4_YawToEffect(Sequence4 *actor)
{
    if (PlayerActorOps_StartPosition(SEQUENCE4_PLAYER) == NULL) {
        return 0;
    }
    Vec3 from = *PlayerActorOps_StartPosition(SEQUENCE4_PLAYER);
    Vec3 to;
    Vec3 delta;
    Sequence4_EffectPointAhead(&to, actor);
    Vec_Subtract(&delta, &to, &from);
    return Math_Atan2(delta.x, delta.z);
}
CLEAN_AS(func_ov068_02272cd4, Sequence4_YawToEffect)

/* func_ov068_02272d1c: the effect point moved along x by 25.0 / 100.0 less 0xf6 (0x30a). */
void Sequence4_EffectPointAhead(Vec3 *out, const Sequence4 *actor)
{
    /* x, y, then z, as the ROM copies them (`out` may overlap the actor) */
    out->x = actor->effect_point.x;
    out->y = actor->effect_point.y;
    out->z = actor->effect_point.z;
    out->x += FX_Div(SEQUENCE4_AHEAD_NUMERATOR, SEQUENCE4_AHEAD_DENOMINATOR) - SEQUENCE4_AHEAD_BACK;
}
CLEAN_AS(func_ov068_02272d1c, Sequence4_EffectPointAhead)

/* func_ov068_02272d5c (receiver slot 0x14, also vtable slot 0x88: a message ended): nothing. */
void Sequence4_OnMessageEnd(void *actor)
{
    (void) actor;
}
CLEAN_AS(func_ov068_02272d5c, Sequence4_OnMessageEnd)

/* func_ov068_02272d60 (receiver slot 0x6c, also the word after the receiver vtable): 0. */
int Sequence4_ReceiverSlot6c(void *actor)
{
    (void) actor;
    return 0;
}
CLEAN_AS(func_ov068_02272d60, Sequence4_ReceiverSlot6c)

/* func_ov068_02272d64 (vtable slot 0x60, a joint of its model being described): at joint 0 the
 * effect point becomes its position moved by the joint's translation. */
void Sequence4_PlaceEffectPoint(Sequence4 *actor, int node, const AnimatedModelNodeState *state)
{
    if (node != 0) {
        return;
    }
    Vec3 translation = state->joint->translation;
    Vec3 point;
    Vec_Add(&point, &actor->base.position, &translation);
    actor->effect_point = point;
}
CLEAN_AS(func_ov068_02272d64, Sequence4_PlaceEffectPoint)

/* func_ov068_02272db4 (vtable slot 0xb0): whether its drawing draws the model: in any state
 * but 0. */
int Sequence4_DrawsModel(const Sequence4 *actor)
{
    return actor->state != 0;
}
CLEAN_AS(func_ov068_02272db4, Sequence4_DrawsModel)

/* func_ov068_02272dc8: its third animation (overlay 9's func_ov009_02264d18). */
int Sequence4_ThirdAnimation(Sequence4 *actor)
{
    return func_ov009_02264d18(actor);
}
CLEAN_AS(func_ov068_02272dc8, Sequence4_ThirdAnimation)

/* func_ov068_02272dd0 (vtable slot 0xb4, returning a Vec3): the effect point, where overlay 9's
 * class gives its position. */
void Sequence4_EffectPoint(Vec3 *out, const Sequence4 *actor)
{
    /* x, y, then z, as the ROM copies them (`out` may overlap the actor) */
    out->x = actor->effect_point.x;
    out->y = actor->effect_point.y;
    out->z = actor->effect_point.z;
}
CLEAN_AS(func_ov068_02272dd0, Sequence4_EffectPoint)

/* func_ov068_02272df0 (vtable slot 0x0c): out of state 0, event flag 1 cleared; when a
 * sequence started, main's two flags that pick the first state are cleared. Always 1. */
int Sequence4_Release(Sequence4 *actor)
{
    if (actor->state != 0) {
        EventQueue_ClearFlag1();
    }
    if (actor->flag_2de != 0) {
        actor->flag_2de = 0;
        Block020b220c_ClearFlag4b18();
        Block020b220c_ClearFlag4b1c();
    }
    return 1;
}
CLEAN_AS(func_ov068_02272df0, Sequence4_Release)

/* func_ov068_02272e28 (vtable slot 0x24): nothing drawn here; 1. */
int Sequence4_Draw(void)
{
    return 1;
}
CLEAN_AS(func_ov068_02272e28, Sequence4_Draw)

/* func_ov068_02272e2c (vtable slot 0x18): its state's update; out of state 0 the player's own
 * flag 0x0b is switched on. Always 1. */
int Sequence4_Update(Sequence4 *actor)
{
    Sequence4_UpdateState(actor);
    if (actor->state != 0) {
        PlayerActorOps_SwitchOwnFlag0b(1);
    }
    return 1;
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_02272e2cEv, Sequence4_Update)

/* func_ov068_02272e50 (vtable slot 0x70, setting it up): the effect point starts at its
 * position. With main's flag 4b18 a sequence starts at state 1; with flag 4b1c, at state 10,
 * the current player's hand emptied first; both reset the marked place. Otherwise state 0.
 * Always 1. */
int Sequence4_Setup(Sequence4 *actor)
{
    u8 *record = PlayerRecords_Current();
    actor->effect_point = actor->base.position;
    if (Block020b220c_Flag4b18() != 0) {
        actor->flag_2de = 1;
        (void) SceneTables_EntryRecord();
        ScenePlace_ResetMarked();
        set_state(actor, 1);
    } else if (Block020b220c_Flag4b1c() != 0) {
        actor->flag_2de = 1;
        if (record != NULL) {
            u16 item = SEQUENCE4_NO_ITEM;
            PlayerRecord_SetHeldItem(record, &item);
        }
        (void) SceneTables_EntryRecord();
        ScenePlace_ResetMarked();
        set_state(actor, 10);
    } else {
        set_state(actor, 0);
    }
    return 1;
}
CLEAN_AS(_ZN18Obj_ov068_0227775019func_ov068_02272e50Ev, Sequence4_Setup)

/* func_ov068_02272ee8 (vtable slot 0x44, the deleting destructor): its vtables set back,
 * overlay 9's destructor, and the memory freed. */
Sequence4 *Sequence4_DestroyAndFree(Sequence4 *actor)
{
    actor->base.vtable = data_ov068_02277750;
    actor->base.receiver_vtable = data_ov068_02277814;
    func_ov009_0226539c(actor);
    Heap_FreeAux(actor);
    return actor;
}
CLEAN_AS(func_ov068_02272ee8, Sequence4_DestroyAndFree)

/* func_ov068_02272f14 (vtable slot 0x40): the destructor, without freeing. */
Sequence4 *Sequence4_Destroy(Sequence4 *actor)
{
    actor->base.vtable = data_ov068_02277750;
    actor->base.receiver_vtable = data_ov068_02277814;
    func_ov009_0226539c(actor);
    return actor;
}
CLEAN_AS(func_ov068_02272f14, Sequence4_Destroy)

/* func_ov068_02272f38: the constructor: overlay 9's, then its vtables. */
Sequence4 *Sequence4_Construct(Sequence4 *actor)
{
    func_ov009_0226552c(actor);
    actor->base.vtable = data_ov068_02277750;
    actor->base.receiver_vtable = data_ov068_02277814;
    return actor;
}
CLEAN_AS(func_ov068_02272f38, Sequence4_Construct)

/* func_ov068_02272f5c (the class's entry in the overlay's table of profiles): allocates and
 * constructs one; nothing keeps the pointer here. */
void Sequence4_New(void)
{
    Sequence4 *actor = Heap_AllocAuxZeroed(sizeof(Sequence4));
    if (actor != NULL) {
        Sequence4_Construct(actor);
    }
}
CLEAN_AS(func_ov068_02272f5c, Sequence4_New)

/* The actor around its receiver part, as the receiver vtable's thunks find it. */
static Sequence4 *sequence4_from_receiver(void *receiver)
{
    return (Sequence4 *) (void *) ((u8 *) receiver - SEQUENCE4_RECEIVER_OFFSET);
}

/* _ZThn236_N18Obj_ov068_02277750D0Ev (receiver slot 0x04): Sequence4_DestroyAndFree. */
Sequence4 *Sequence4_ReceiverDestroyAndFree(void *receiver)
{
    return Sequence4_DestroyAndFree(sequence4_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov068_02277750D0Ev, Sequence4_ReceiverDestroyAndFree)

/* _ZThn236_N18Obj_ov068_0227775017vfunc_02066994_6cEv (receiver slot 0x6c):
 * Sequence4_ReceiverSlot6c. */
int Sequence4_ReceiverThunk6c(void *receiver)
{
    return Sequence4_ReceiverSlot6c(sequence4_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov068_0227775017vfunc_02066994_6cEv, Sequence4_ReceiverThunk6c)

/* _ZThn236_N18Obj_ov068_0227775017vfunc_02066994_14Ev (receiver slot 0x14):
 * Sequence4_OnMessageEnd. */
void Sequence4_ReceiverOnMessageEnd(void *receiver)
{
    Sequence4_OnMessageEnd(sequence4_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov068_0227775017vfunc_02066994_14Ev, Sequence4_ReceiverOnMessageEnd)

/* _ZThn236_N18Obj_ov068_02277750D1Ev (receiver slot 0x00): Sequence4_Destroy. */
Sequence4 *Sequence4_ReceiverDestroy(void *receiver)
{
    return Sequence4_Destroy(sequence4_from_receiver(receiver));
}
CLEAN_AS(_ZThn236_N18Obj_ov068_02277750D1Ev, Sequence4_ReceiverDestroy)
