/* The insurance seller of overlay 71: his object, his states, the chase and his walks, and his
 * creation (insurer.h). */
#include "insurer.h"

#include <stdint.h>

#include "autoload_2/fx_math.h"
#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "insurer_talk.h"
#include "main/acre_tile.h"
#include "main/act_effects.h"
#include "main/actor.h"
#include "main/block_021d27ac.h"
#include "main/event_announce.h"
#include "main/event_queue.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/layered_model.h"
#include "main/main_random.h"
#include "main/pool_link.h"
#include "main/scene_action.h"
#include "main/scene_base.h"
#include "main/scene_face.h"
#include "main/scene_look.h"
#include "main/scene_motion.h"
#include "main/scene_motion_request.h"
#include "main/scene_mover.h"
#include "main/scene_object.h"
#include "main/scene_object_base.h"
#include "main/scene_probe.h"
#include "main/scene_standard_anims.h"
#include "main/scene_talk_state.h"
#include "main/scene_value_3aa.h"
#include "main/session_players.h"
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "main/talk_checks.h"
#include "main/town_spot.h"
#include "main/town_tile.h"

static_assert(sizeof(InsurerStep) == 0x10, "a state's functions");
static_assert(offsetof(Insurer, state) == 0x654, "state");
static_assert(offsetof(Insurer, talk) == 0x658, "talk scene");
static_assert(offsetof(Insurer, explained) == 0x724, "explained");
static_assert(offsetof(Insurer, chase_step) == 0x729, "chase step");
static_assert(offsetof(Insurer, timer) == 0x72c, "timer");
static_assert(offsetof(Insurer, rest) == 0x730, "rest");
static_assert(offsetof(Insurer, player) == 0x734, "player");
static_assert(offsetof(Insurer, start) == 0x738, "start");
static_assert(sizeof(Insurer) == 0x744, "the size Insurer_Create allocates");
static_assert(offsetof(Actor, position) == 0x5c && offsetof(Actor, angle) == 0x8c, "actor position, angle");
static_assert(offsetof(Actor, move_angle) == 0x92 && offsetof(Actor, speed) == 0x98, "actor heading, speed");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h). */
#define INS_PERSON 0xea          /* u16: its person code */
#define INS_MODEL 0xec           /* LayeredModel */
#define INS_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define INS_FACE 0x2ac           /* SceneFace */
#define INS_ANIM 0x334           /* SpeakerAnim */
#define INS_MOVER 0x350          /* SceneMover */
#define INS_PROBE 0x3a8          /* the probe ahead */
#define INS_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define INS_LOOK 0x3b0           /* SceneLook */
#define INS_TALK_STATE 0x418     /* SceneTalkState */
#define INS_EFFECTS 0x420        /* ActEffects */
#define INS_COLLIDER 0x49c       /* CollisionContacts */
#define INS_CARRIER 0x4cc        /* FieldOwnedBody */
#define INS_EMITTER 0x514        /* SoundEmitterObject */
#define INS_FOOTSTEPS 0x558      /* Footsteps */
#define INS_MOTION 0x564         /* SceneMotion */
#define INS_ACTION 0x618         /* SceneAction */
#define INS_HEAP 0x640           /* PoolLink */

#define INS_NO_PERSON 0xfff1

/* The field actor of this console's player. */
#define INS_PLAYER_ACTOR 4

/* The codes of his vtable slot 0x4c (main's event_kinds.h): the player's act (the talk), the
 * event's start and its end. */
#define INS_EVENT_ACT 0
#define INS_EVENT_STARTS 3
#define INS_EVENT_ENDED 8

/* The talk scene's vtable slot his talks call first, and his own slot 0x98 (the second
 * animation of kind 11, Insurer_SecondAnimation), the animation he greets the player with. */
#define INS_TALK_SLOT_08 0x08
#define INS_SLOT_SECOND_ANIMATION 0x98

/* The daily bit of the current player set once he pitched to the player today. */
#define INS_DAILY_PITCHED 0x28

/* His motions (SceneMotion_Request's kinds): stand, walk and run to a point, turn, turn to a
 * point (scene_motion_request.h); and the animation he calls to the player with. */
#define INS_MOTION_STAND 0
#define INS_MOTION_WALK 1
#define INS_MOTION_RUN 2
#define INS_MOTION_TURN 3
#define INS_MOTION_TURN_TO 4
#define INS_CALL_ANIMATION 0xdf

/* The chase: within this distance (and the half-angle data_ov071_0227a340) the player is close
 * ahead of him; the frames of a run and of the wait in front of the player; his rest after a
 * chase; how far from where it started he goes on. */
#define INS_CLOSE 0x3000
#define INS_NEAR 0x5000
#define INS_FAR 0x8000
#define INS_RUN_FRAMES 300
#define INS_WAIT_FRAMES 0xf0
#define INS_REST_FRAMES 200
#define INS_CHASE_RANGE 0xc000

/* His walks: the frames of a walk and of a turn, of the wait before wandering; the distance of
 * a random spot. */
#define INS_WALK_FRAMES 100
#define INS_TURN_FRAMES 0x50
#define INS_WAIT_START_FRAMES 0x28
#define INS_SPOT_DISTANCE 0xc000
#define INS_SPOT_TRIES 6

/* The probe's bits (SceneProbe_Bits): its point at +x blocked, its point at -x, both. */
#define INS_PROBE_PLUS_X 1
#define INS_PROBE_MINUS_X 2
#define INS_PROBE_BOTH 3

/* The grade of SceneValue3aa that keeps him standing. */
#define INS_VALUE_3AA_STAND 2

/* The vtables: the class's and those of the classes it derives from. */
extern const u8 data_ov071_0227a278[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* His states' functions (filled at start-up by __sinit_ov071_02279fd4). */
extern InsurerStep data_ov071_0227a3a4[INSURER_STATES];
/* The table of the chase's steps (a function-local static, filled once from three constants;
 * bit 0 of data_ov071_0227a348 says it was). */
extern u32 data_ov071_0227a348;
extern MemberPointer data_ov071_0227a374[INSURER_CHASE_STEPS];
extern const MemberPointer data_ov071_0227a150, data_ov071_0227a158, data_ov071_0227a168;
/* The half-angle of "ahead" (a copy of main's data_020c80f0) and the offsets he steps aside to,
 * (-0.5, 0, 1.0) and (0.5, 0, 1.0) (Vec3 objects made at start-up). */
extern s16 data_ov071_0227a340;
extern Vec3 data_ov071_0227a398;
extern Vec3 data_ov071_0227a38c;
/* His model's and texture's file names: "npc_sp/model/ott.nsbmd", "npc_sp/model/ott_tex.nsbtx". */
extern const char data_ov071_0227a194[];
extern const char data_ov071_0227a1c4[];
/* The field camera and the point it looks at. */
extern void *data_021c67a4;
extern const Vec3 data_021c67d0;
/* The game's main random generator. */
extern Random data_021cb5a0;
/* The origin, as the look's point and the start of a random spot. */
extern Vec3 data_021fbee8;
/* The look's range, the word his motion requests carry, the animations' speed. */
extern fx32 data_020c814c;
extern u16 data_020c80f8;
extern int data_020c8120;

extern const s16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void MI_CpuFill8(void *dst, u8 value, u32 size);

static u8 *ins_part(Insurer *insurer, u32 offset)
{
    return insurer->base + offset;
}

static Actor *ins_actor(Insurer *insurer)
{
    return (Actor *) (void *) insurer->base;
}

static SceneMotion *ins_motion(Insurer *insurer)
{
    return (SceneMotion *) (void *) ins_part(insurer, INS_MOTION);
}

static SceneAction *ins_action(Insurer *insurer)
{
    return (SceneAction *) (void *) ins_part(insurer, INS_ACTION);
}

static SceneMover *ins_mover(Insurer *insurer)
{
    return (SceneMover *) (void *) ins_part(insurer, INS_MOVER);
}

static u8 *ins_player(Insurer *insurer)
{
    return (u8 *) (uintptr_t) insurer->player;
}

static const Vec3 *ins_player_position(Insurer *insurer)
{
    return &((const Actor *) (const void *) ins_player(insurer))->position;
}

static fx32 ins_add(fx32 a, fx32 b)
{
    return (fx32) ((u32) a + (u32) b);
}

static fx32 ins_sub(fx32 a, fx32 b)
{
    return (fx32) ((u32) a - (u32) b);
}

/* His motion of `kind` (priority 1) towards (x, z), turning to `angle`. */
static void ins_move(Insurer *insurer, int kind, int x, int z, s16 angle)
{
    SceneMotion_Request(ins_motion(insurer), kind, 1, x, z, 0, angle, 0, 0, data_020c80f8, 0);
}

static void ins_stand(Insurer *insurer)
{
    ins_move(insurer, INS_MOTION_STAND, 0, 0, 0);
}

/* His look at this console's player, priority 0. */
static void ins_look_at_player(Insurer *insurer)
{
    SceneLook_Request((SceneLook *) (void *) ins_part(insurer, INS_LOOK), 1, 0, 0, &data_021fbee8, INS_PLAYER_ACTOR,
                      data_020c814c, 1);
}

/* His animation number `animation` (priority 1), in `mode`. */
static void ins_animate(Insurer *insurer, int animation, char mode)
{
    SceneMotion_RequestAnimation(ins_motion(insurer), 1, animation, mode, data_020c80f8, 0);
}

/* His own vtable slot 0x98 called: the animation he greets the player with. */
static int ins_greeting_animation(Insurer *insurer)
{
    u32 vtable = *(const u32 *) (const void *) insurer->base;
    u32 code = *(const u32 *) (uintptr_t) (vtable + INS_SLOT_SECOND_ANIMATION);
    return ((int (*)(Insurer *))(uintptr_t) code)(insurer);
}

/* func_ov071_02278a00 (vtable slot 0x40): his talk scene's destructor, then the special
 * character's; the object. */
void *Insurer_Destroy(void *object)
{
    Insurer *insurer = object;
    *(const u8 **) (void *) insurer->base = data_ov071_0227a278;
    InsurerTalk_Destroy(&insurer->talk);
    SpecialSceneObject_DestructBody(insurer);
    return insurer;
}
CLEAN_AS(func_ov071_02278a00, Insurer_Destroy)

/* func_ov071_02278a28 (vtable slot 0x44): the same, then the object freed. */
void *Insurer_Delete(void *object)
{
    Insurer *insurer = object;
    *(const u8 **) (void *) insurer->base = data_ov071_0227a278;
    InsurerTalk_Destroy(&insurer->talk);
    SpecialSceneObject_DestructBody(insurer);
    Heap_FreeAux(insurer);
    return insurer;
}
CLEAN_AS(func_ov071_02278a28, Insurer_Delete)

/* func_ov071_02278a54 (vtable slot 0x4c, told of an event about him): code 3, the event
 * starts: his talk scene told through its slot 0x08, the talk's partner this console's
 * player's object, and he talks (state 5); code 0, the player's act: the talk ends (state 0);
 * code 8, the event ended: he wanders (state 3). The base class is not told. */
void Insurer_OnEvent(Insurer *insurer, int code)
{
    switch (code) {
        case INS_EVENT_ACT:
            Insurer_SetState(insurer, INSURER_TALK_ENDS);
            break;
        case INS_EVENT_STARTS: {
            u32 vtable = *(const u32 *) (const void *) &insurer->talk;
            u32 slot = *(const u32 *) (uintptr_t) (vtable + INS_TALK_SLOT_08);
            ((void (*)(InsurerTalk *))(uintptr_t) slot)(&insurer->talk);
            SceneBase_SetMotionArg(&insurer->talk.base, SceneObject_ActorObject(insurer->base, INS_PLAYER_ACTOR));
            Insurer_SetState(insurer, INSURER_TALKING);
            break;
        }
        case INS_EVENT_ENDED:
            Insurer_SetState(insurer, INSURER_WANDER);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov071_02278a54, Insurer_OnEvent)

/* func_ov071_02278aa4 (vtable slot 0x48): whether the player may talk to him: his action is
 * idle. */
int Insurer_MayAct(Insurer *insurer)
{
    return !SceneAction_IsBusy(ins_action(insurer));
}
CLEAN_AS(func_ov071_02278aa4, Insurer_MayAct)

/* func_ov071_0227920c (state 2's update): nothing. 1. */
int Insurer_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov071_0227920c, Insurer_UpdateTalked)

/* func_ov071_02279210 (state 4's update): this console's player's object noted; when he
 * pitched to the player today he wanders (state 3) once the player is in the wide view; else,
 * with the player in view, not within 3.0 ahead but within 8.0 ahead, he chases (state 1), and
 * otherwise wanders. 1. */
int Insurer_UpdateWait(Insurer *insurer)
{
    insurer->player = (u32) SessionPlayers_ActorHandle(INS_PLAYER_ACTOR);
    if (TalkChecks_TestSetDailyBit(INS_DAILY_PITCHED, 0) != 0) {
        if (Insurer_InView(insurer, 1) != 0) {
            Insurer_SetState(insurer, INSURER_WANDER);
        }
        return 1;
    }
    if (Insurer_InView(insurer, 0) != 0 && Insurer_PlayerAhead(insurer, INS_CLOSE) == 0 &&
        Insurer_PlayerAhead(insurer, INS_FAR) != 0) {
        Insurer_SetState(insurer, INSURER_CHASE);
        return 1;
    }
    Insurer_SetState(insurer, INSURER_WANDER);
    return 1;
}
CLEAN_AS(func_ov071_02279210, Insurer_UpdateWait)

/* func_ov071_02279290 (state 4's entry): his footsteps off, he stands, and waits 40 frames. 1. */
int Insurer_EnterWait(Insurer *insurer)
{
    Footsteps_Disable((Footsteps *) (void *) ins_part(insurer, INS_FOOTSTEPS));
    ins_stand(insurer);
    insurer->timer = INS_WAIT_START_FRAMES;
    return 1;
}
CLEAN_AS(func_ov071_02279290, Insurer_EnterWait)

/* A new move once the last one is done: standing while SceneValue3aa grades 2; else one frame
 * in eight (by the main random generator) towards a random clear spot (Insurer_RandomSpot):
 * when it lies within a quarter turn of where he faces he walks there (one in four: runs) for
 * 100 frames unless that is his motion already, else he turns to it for 80 frames unless he is
 * turning already; without a spot, or in the other frames, he stands. */
static void ins_next_move(Insurer *insurer)
{
    Actor *self = ins_actor(insurer);
    if (SceneValue3aa_Grade((SceneValue3aa *) (void *) ins_part(insurer, INS_VALUE_3AA)) == INS_VALUE_3AA_STAND) {
        ins_stand(insurer);
        return;
    }
    if ((Random_Next(&data_021cb5a0) & 7) != 0) {
        ins_stand(insurer);
        return;
    }
    Vec3 spot = data_021fbee8;
    int x = spot.x;
    int z = spot.z;
    if (Insurer_RandomSpot(insurer, &x, &z) == 0) {
        ins_stand(insurer);
        return;
    }
    spot.x = x;
    spot.z = z;
    int yaw = Vec_YawTo(&self->position, &spot);
    if (SceneObject_IsWithinQuarterTurn((s16) (yaw - self->angle[1])) != 0) {
        int kind = INS_MOTION_WALK;
        if (MainRandom_Below(4) == 0) {
            kind = INS_MOTION_RUN;
        }
        if (kind != SceneMotion_Kind(ins_motion(insurer))) {
            ins_move(insurer, kind, spot.x, spot.z, 0);
            insurer->timer = INS_WALK_FRAMES;
        }
    } else if (SceneMotion_Kind(ins_motion(insurer)) != INS_MOTION_TURN_TO) {
        ins_move(insurer, INS_MOTION_TURN_TO, spot.x, spot.z, (s16) yaw);
        insurer->timer = INS_TURN_FRAMES;
    }
}

/* While he moves (a walk, a run or a turn to a point): he stands once its frames are over, or
 * once the end of his mover is no longer within a quarter turn of where he faces. */
static void ins_check_move(Insurer *insurer)
{
    Actor *self = ins_actor(insurer);
    if (SceneMotion_Kind(ins_motion(insurer)) != INS_MOTION_WALK && SceneMotion_Kind(ins_motion(insurer)) != INS_MOTION_RUN &&
        SceneMotion_Kind(ins_motion(insurer)) != INS_MOTION_TURN_TO) {
        return;
    }
    if (insurer->timer == 0) {
        ins_stand(insurer);
        return;
    }
    Vec3 end = *SceneMover_End(ins_mover(insurer));
    if (SceneObject_IsWithinQuarterTurn((s16) (Vec_YawTo(&self->position, &end) - self->angle[1])) == 0) {
        ins_stand(insurer);
    }
}

/* func_ov071_022792e0 (state 3's update): once his rest is over (counted down each frame), a
 * player in view who was not pitched to today and is within 8.0 ahead is chased (state 1), 1.
 * Else his move's frames are counted down and, with the player in the wide view and nothing
 * he has to step aside of (Insurer_StepAsideIfMoving), once his motion is done he takes a new
 * move (ins_next_move), else while he has a speed his move is checked (ins_check_move); out of
 * the wide view, while he has a speed, he waits (state 4). 0. */
int Insurer_UpdateWander(Insurer *insurer)
{
    if (Insurer_CountDown((int) (u32) (uintptr_t) insurer, &insurer->rest) == 0 &&
        TalkChecks_TestSetDailyBit(INS_DAILY_PITCHED, 0) == 0 && Insurer_InView(insurer, 0) != 0 &&
        Insurer_PlayerAhead(insurer, INS_FAR) != 0) {
        Insurer_SetState(insurer, INSURER_CHASE);
        return 1;
    }
    Insurer_CountDown((int) (u32) (uintptr_t) insurer, &insurer->timer);
    if (Insurer_InView(insurer, 1) != 0) {
        if (Insurer_StepAsideIfMoving(insurer) == 0) {
            if (SceneMotion_IsDone(ins_motion(insurer)) != 0) {
                ins_next_move(insurer);
            } else if (ins_actor(insurer)->speed != 0) {
                ins_check_move(insurer);
            }
        }
    } else if (ins_actor(insurer)->speed != 0) {
        Insurer_SetState(insurer, INSURER_WAIT);
    }
    return 0;
}
CLEAN_AS(func_ov071_022792e0, Insurer_UpdateWander)

/* func_ov071_02279570: while he has a speed, whether he steps aside (Insurer_StepAside). */
int Insurer_StepAsideIfMoving(Insurer *insurer)
{
    return ins_actor(insurer)->speed != 0 && Insurer_StepAside(insurer) != 0;
}
CLEAN_AS(func_ov071_02279570, Insurer_StepAsideIfMoving)

/* The end of his mover set to the point the probe finds clear at `offset`, or he stands. */
static void ins_step_to(Insurer *insurer, Vec3 *offset)
{
    Vec3 point;
    if (Insurer_ProbePoint(insurer, &point, (int) (u32) (uintptr_t) offset) != 0) {
        SceneMover_SetEnd(ins_mover(insurer), &point);
    } else {
        ins_stand(insurer);
    }
}

/* func_ov071_02279594: what the probe ahead of him says, unless his mover reached its start:
 * its point at +x blocked (1), he steps to the offset at -x, its point at -x blocked (2) to the
 * one at +x, or stands when it is not clear; blocked both ways (3) he stands; whether he did any of it.
 * Once his mover reached its start, its end is put back to its start when they differ; 0. */
int Insurer_StepAside(Insurer *insurer)
{
    SceneMover *mover = ins_mover(insurer);
    int bits = SceneProbe_Bits(ins_part(insurer, INS_PROBE));
    if (SceneMover_Reached(mover, insurer->base, 1) != 0) {
        if (SceneMover_PointsDiffer(mover) != 0) {
            SceneMover_EndAtStart(mover);
        }
        return 0;
    }
    switch (bits) {
        case INS_PROBE_PLUS_X:
            ins_step_to(insurer, &data_ov071_0227a398);
            return 1;
        case INS_PROBE_MINUS_X:
            ins_step_to(insurer, &data_ov071_0227a38c);
            return 1;
        case INS_PROBE_BOTH:
            ins_stand(insurer);
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_ov071_02279594, Insurer_StepAside)

/* func_ov071_02279694: the point at `offset` (a Vec3's address) from where he stands, turned by
 * his heading, into `out` when the probe does not find it blocked; whether it was clear. */
int Insurer_ProbePoint(Insurer *insurer, Vec3 *out, int offset)
{
    Actor *self = ins_actor(insurer);
    Vec3 point;
    SceneProbe_PointAt(&point, &self->position, (const Vec3 *) (uintptr_t) (u32) offset, self->move_angle[1]);
    if (SceneProbe_IsBlocked(&point) == 1) {
        return 0;
    }
    *out = point;
    return 1;
}
CLEAN_AS(func_ov071_02279694, Insurer_ProbePoint)

/* func_ov071_022796d0: a random clear spot 12.0 from him: up to six tries of a random angle (by
 * the main random generator), the point snapped to its tile's centre and asked of the town's
 * tiles (TownTile_IsClearAt); its x and z, when one is clear. Whether one was. The height of the
 * point is 0 at first and whatever the snapping leaves it after. */
int Insurer_RandomSpot(Insurer *insurer, int *x, int *z)
{
    Actor *self = ins_actor(insurer);
    Vec3 spot = {0, 0, 0};
    for (int i = 0; i < INS_SPOT_TRIES; i++) {
        u32 index = (((u32) Random_Next(&data_021cb5a0) & 0xffff) >> 4) * 2;
        spot.x = ins_add(FX_MulFunc(INS_SPOT_DISTANCE, FX_SinCosTable_[index]), self->position.x);
        spot.z = ins_add(FX_MulFunc(INS_SPOT_DISTANCE, FX_SinCosTable_[index + 1]), self->position.z);
        AcreTile_SnapToTileCentre(&spot, &spot);
        if (TownTile_IsClearAt(&spot, NULL) != 0) {
            *x = spot.x;
            *z = spot.z;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov071_022796d0, Insurer_RandomSpot)

/* func_ov071_02279760 (state 3's entry): no move's frames, he stands, his footsteps on and he
 * looks at this console's player. 1. */
int Insurer_EnterWander(Insurer *insurer)
{
    insurer->timer = 0;
    ins_stand(insurer);
    Footsteps_Enable((Footsteps *) (void *) ins_part(insurer, INS_FOOTSTEPS));
    ins_look_at_player(insurer);
    return 1;
}
CLEAN_AS(func_ov071_02279760, Insurer_EnterWander)

/* _ZN18Obj_ov071_0227a27819func_ov071_022797d8Ev (state 1's update): the chase's step runs,
 * from its table (filled the first time). 0. */
int Insurer_UpdateChase(Insurer *insurer)
{
    static const MemberPointer *const constants[INSURER_CHASE_STEPS] = {&data_ov071_0227a150, &data_ov071_0227a158,
                                                                        &data_ov071_0227a168};
    MemberTable_InitOnce(&data_ov071_0227a348, data_ov071_0227a374, constants, INSURER_CHASE_STEPS);
    if (insurer->chase_step < INSURER_CHASE_STEPS) {
        MemberPointer_CallVoid(&data_ov071_0227a374[insurer->chase_step], insurer);
    }
    return 0;
}
CLEAN_AS(_ZN18Obj_ov071_0227a27819func_ov071_022797d8Ev, Insurer_UpdateChase)

/* func_ov071_02279858 (state 1's entry): this console's player's object noted and where he
 * stands kept as the chase's start; his calling animation (0xdf, mode 1), his footsteps on, he
 * looks at the player; the chase's first step. 1. */
int Insurer_EnterChase(Insurer *insurer)
{
    insurer->player = (u32) SessionPlayers_ActorHandle(INS_PLAYER_ACTOR);
    insurer->start = ins_actor(insurer)->position;
    ins_animate(insurer, INS_CALL_ANIMATION, 1);
    Footsteps_Enable((Footsteps *) (void *) ins_part(insurer, INS_FOOTSTEPS));
    ins_look_at_player(insurer);
    insurer->chase_step = INSURER_CHASE_CALL;
    return 1;
}
CLEAN_AS(func_ov071_02279858, Insurer_EnterChase)

/* He runs to the player for 300 frames (step 1). */
static void ins_run_to_player(Insurer *insurer)
{
    const Vec3 *at = ins_player_position(insurer);
    ins_move(insurer, INS_MOTION_RUN, at->x, at->z, 0);
    insurer->timer = INS_RUN_FRAMES;
    insurer->chase_step = INSURER_CHASE_RUN;
}

/* He greets the player (his slot 0x98's animation) and waits in front of the player (step
 * 2). */
static void ins_greet(Insurer *insurer)
{
    ins_animate(insurer, ins_greeting_animation(insurer), 0);
    insurer->chase_step = INSURER_CHASE_WAIT;
}

/* func_ov071_022798f8 (the chase's step 2, waiting in front of the player): without the
 * player he wanders (state 3); once the wait is over he turns to the player, rests 200 frames
 * and wanders; else once the player is no longer within 5.0 ahead he runs after the player
 * again. */
void Insurer_ChaseWait(Insurer *insurer)
{
    if (insurer->player == 0) {
        Insurer_SetState(insurer, INSURER_WANDER);
    } else if (Insurer_CountDown((int) (u32) (uintptr_t) insurer, &insurer->timer) == 0) {
        int angle = SceneObject_YawTo(insurer->base, ins_player(insurer));
        ins_move(insurer, INS_MOTION_TURN, 0, 0, (s16) angle);
        insurer->rest = INS_REST_FRAMES;
        Insurer_SetState(insurer, INSURER_WANDER);
    } else if (Insurer_PlayerAhead(insurer, INS_NEAR) == 0) {
        ins_run_to_player(insurer);
    }
}
CLEAN_AS(func_ov071_022798f8, Insurer_ChaseWait)

/* func_ov071_022799c0 (the chase's step 1, running after the player): while the run's frames
 * last and there is the player: with the player within 3.0 ahead he greets the player and
 * waits 240 frames; else while he is within 12.0 of the chase's start the run's goal follows
 * the player; else, and once the frames are over, he rests 200 frames and wanders (state 3). */
void Insurer_ChaseRun(Insurer *insurer)
{
    if (Insurer_CountDown((int) (u32) (uintptr_t) insurer, &insurer->timer) != 0 && insurer->player != 0) {
        if (Insurer_PlayerAhead(insurer, INS_CLOSE) != 0) {
            ins_greet(insurer);
            insurer->timer = INS_WAIT_FRAMES;
            return;
        }
        if (Insurer_NearStart(insurer) != 0) {
            SceneMover_SetStart(ins_mover(insurer), ins_player_position(insurer));
            return;
        }
    }
    insurer->rest = INS_REST_FRAMES;
    Insurer_SetState(insurer, INSURER_WANDER);
}
CLEAN_AS(func_ov071_022799c0, Insurer_ChaseRun)

/* func_ov071_02279a78 (the chase's step 0, calling to the player): without the player he
 * wanders (state 3); once his calling animation is done, with the player within 3.0 ahead he
 * greets the player (without a wait's frames), else runs after the player. */
void Insurer_ChaseCall(Insurer *insurer)
{
    if (insurer->player == 0) {
        Insurer_SetState(insurer, INSURER_WANDER);
        return;
    }
    if (SceneMotion_IsDone(ins_motion(insurer)) == 0) {
        return;
    }
    if (Insurer_PlayerAhead(insurer, INS_CLOSE) != 0) {
        ins_greet(insurer);
        return;
    }
    ins_run_to_player(insurer);
}
CLEAN_AS(func_ov071_02279a78, Insurer_ChaseCall)

/* func_ov071_02279b2c: whether the player is within `range` of him and within the half-angle
 * data_ov071_0227a340 either side of where he faces. */
int Insurer_PlayerAhead(Insurer *insurer, int range)
{
    if (SceneObject_DistanceTo(insurer->base, ins_player(insurer)) > range) {
        return 0;
    }
    int angle = SceneObject_AngleTo(insurer->base, ins_player(insurer));
    int half = data_ov071_0227a340;
    return angle >= -half && angle <= half;
}
CLEAN_AS(func_ov071_02279b2c, Insurer_PlayerAhead)

/* func_ov071_02279b6c: whether he is within 12.0 of the chase's start. */
int Insurer_NearStart(Insurer *insurer)
{
    return Vec_Distance(&ins_actor(insurer)->position, &insurer->start) <= INS_CHASE_RANGE;
}
CLEAN_AS(func_ov071_02279b6c, Insurer_NearStart)

/* func_ov071_02279b98 (state 5's update): nothing. 1. */
int Insurer_UpdateTalking(void)
{
    return 1;
}
CLEAN_AS(func_ov071_02279b98, Insurer_UpdateTalking)

/* func_ov071_02279b9c (state 5's entry): he turns to the talk's partner (keeping where he
 * faces without one) and talks. 1. */
int Insurer_EnterTalking(char *object)
{
    Insurer *insurer = (Insurer *) (void *) object;
    int partner = SceneBase_MotionArg(&insurer->talk.base);
    int angle = ins_actor(insurer)->angle[1];
    if (partner != 0) {
        angle = SceneObject_YawTo(insurer->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(ins_action(insurer), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov071_02279b9c, Insurer_EnterTalking)

/* func_ov071_02279bd8 (state 0's update): once his action is idle, the object's event ends and
 * state 2 follows. 1. */
int Insurer_UpdateTalkEnds(Insurer *insurer)
{
    if (!SceneAction_IsBusy(ins_action(insurer))) {
        EventQueue_FinishObjectEvent(insurer);
        Insurer_SetState(insurer, INSURER_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov071_02279bd8, Insurer_UpdateTalkEnds)

/* func_ov071_02279c04 (state 0's entry): 1. */
int Insurer_EnterTalkEnds(void)
{
    return 1;
}
CLEAN_AS(func_ov071_02279c04, Insurer_EnterTalkEnds)

/* func_ov071_02279c08: `counter` counted down unless it is 0; what it is now. */
int Insurer_CountDown(int unused, int *counter)
{
    (void) unused;
    if (*counter != 0) {
        (*counter)--;
    }
    return *counter;
}
CLEAN_AS(func_ov071_02279c08, Insurer_CountDown)

/* func_ov071_02279c18: whether he stands in the box around the point the field camera looks
 * at (Insurer_InBox; `wide` 0 the near one, else the wide one); 0 without a camera. */
int Insurer_InView(Insurer *insurer, int wide)
{
    if (data_021c67a4 == NULL) {
        return 0;
    }
    Vec3 target = data_021c67d0;
    return Insurer_InBox((int) (u32) (uintptr_t) insurer, &target, &ins_actor(insurer)->position, wide);
}
CLEAN_AS(func_ov071_02279c18, Insurer_InView)

/* func_ov071_02279c54: whether `point` is strictly inside the box around `centre`: with `wide`
 * 0, x within 8.0 and z from 12.0 behind to 6.0 in front; else x within 16.0 and z from 26.0
 * behind to 10.0 in front. */
int Insurer_InBox(int unused, const Vec3 *centre, const Vec3 *point, int wide)
{
    (void) unused;
    fx32 half_x = wide == 0 ? 0x8000 : 0x10000;
    fx32 back = wide == 0 ? 0xc000 : 0x1a000;
    fx32 front = wide == 0 ? 0x6000 : 0xa000;
    if (!(point->x > ins_sub(centre->x, half_x) && point->x < ins_add(centre->x, half_x))) {
        return 0;
    }
    if (!(point->z > ins_sub(centre->z, back))) {
        return 0;
    }
    return point->z < ins_add(centre->z, front);
}
CLEAN_AS(func_ov071_02279c54, Insurer_InBox)

/* func_ov071_02279d04: state `state` taken unless its entry function, if it has one, answers
 * 0.
 * REQUIRES: `state` is 0 to 5 (the table is not bounded). */
void Insurer_SetState(Insurer *insurer, int state)
{
    const InsurerStep *step = &data_ov071_0227a3a4[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, insurer);
    }
    if (taken != 0) {
        insurer->state = state;
    }
}
CLEAN_AS(func_ov071_02279d04, Insurer_SetState)

/* func_ov071_02279d48 (vtable slot 0x68, each frame): his state's update when it has one, and
 * its answer; else 0.
 * REQUIRES: his state is 0 to 5. */
int Insurer_Update(Insurer *insurer)
{
    const InsurerStep *step = &data_ov071_0227a3a4[insurer->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, insurer);
}
CLEAN_AS(func_ov071_02279d48, Insurer_Update)

/* func_ov071_02279d94 (vtable slot 0x98, the second animation of kind 11): 107, also the one he
 * greets the player with. */
int Insurer_SecondAnimation(void)
{
    return 107;
}
CLEAN_AS(func_ov071_02279d94, Insurer_SecondAnimation)

/* func_ov071_02279d98 (vtable slot 0x94, the first animation of kind 11): 219. */
int Insurer_FirstAnimation(void)
{
    return 219;
}
CLEAN_AS(func_ov071_02279d98, Insurer_FirstAnimation)

/* func_ov071_02279d9c (vtable slot 0x70): his model's file name, "npc_sp/model/ott.nsbmd". */
int Insurer_ModelName(void)
{
    return (int) (u32) (uintptr_t) data_ov071_0227a194;
}
CLEAN_AS(func_ov071_02279d9c, Insurer_ModelName)

/* func_ov071_02279da4 (vtable slot 0x6c): his texture's file name,
 * "npc_sp/model/ott_tex.nsbtx". */
int Insurer_TextureName(void)
{
    return (int) (u32) (uintptr_t) data_ov071_0227a1c4;
}
CLEAN_AS(func_ov071_02279da4, Insurer_TextureName)

/* func_ov071_02279dac (vtable slot 0x0c, his leaving): unless the special character refuses,
 * a random spot of the town is picked for the next time (part 0x04 of main's object at
 * data_021d27ac) unless the event's announcement was entered. Whether he left. */
int Insurer_Leave(void *insurer)
{
    if (SpecialSceneObject_Leave(insurer) == 0) {
        return 0;
    }
    if (EventAnnounce_Entered() == 0) {
        TownSpot_PickRandom((TownSpot *) (void *) Block021d27ac_Part04(Block021d27ac_Get()));
    }
    return 1;
}
CLEAN_AS(func_ov071_02279dac, Insurer_Leave)

/* func_ov071_02279dd8 (vtable slot 0x00, his start): unless the special character refuses to
 * start, his animation player plays animation 0x141 (speed 1.0, slot 1), his model's nodes
 * 0x0c-0x0e go to its part A, and he waits (state 4). Whether he started. */
int Insurer_Start(Insurer *insurer)
{
    if (SpecialSceneObject_Start(insurer) == 0) {
        return 0;
    }
    SpeakerAnim_Play((SpeakerAnim *) (void *) ins_part(insurer, INS_ANIM), insurer->base, 0x141, 0, 0, 0x1000, 0, 1);
    LayeredModel_MoveNodesToA((LayeredModel *) (void *) ins_part(insurer, INS_MODEL), 0x0c, 0x0e);
    Insurer_SetState(insurer, INSURER_WAIT);
    return 1;
}
CLEAN_AS(func_ov071_02279dd8, Insurer_Start)

/* func_ov071_02279e30 (vtable slot 0x04, his set-up): unless the special character refuses,
 * his talk scene becomes his scene and gets him as its owner, his mover's pace 2 set (speed
 * 0.125, speeding up and slowing down by 0.0625) and no explanation marked said. Whether he
 * was set up. */
int Insurer_Init(Insurer *insurer)
{
    if (SpecialSceneObject_Init(insurer) == 0) {
        return 0;
    }
    SceneObject_SetScene(insurer->base, &insurer->talk.base);
    InsurerTalk_Begin(&insurer->talk, insurer);
    SceneMover_SetPace(ins_mover(insurer), 2, 0x200, 0x100, 0x100);
    MI_CpuFill8(insurer->explained, 0, INSURER_EXPLANATIONS);
    return 1;
}
CLEAN_AS(func_ov071_02279e30, Insurer_Init)

/* func_ov071_02279e90 (vtable slot 0xa8, his animation player's speed scale): main's
 * data_020c8120 less 1.0. */
int Insurer_AnimSpeed(void)
{
    return (int) ((u32) data_020c8120 - 0x1000);
}
CLEAN_AS(func_ov071_02279e90, Insurer_AnimSpeed)

/* func_ov071_02279ea4 (the create function his record at 0x0227a1ac names): a zeroed block of
 * 0x744 bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable and its talk scene. Null when
 * there is no room. */
void *Insurer_Create(void)
{
    Insurer *insurer = (Insurer *) Heap_AllocAuxZeroed(sizeof(Insurer));
    if (insurer == NULL) {
        return NULL;
    }
    u8 *object = insurer->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) ins_part(insurer, INS_PERSON) = INS_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) ins_part(insurer, INS_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) ins_part(insurer, INS_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) ins_part(insurer, INS_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) ins_part(insurer, INS_ANIM));
    SceneMover_Construct(ins_mover(insurer));
    SceneProbe_Construct(ins_part(insurer, INS_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) ins_part(insurer, INS_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) ins_part(insurer, INS_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) ins_part(insurer, INS_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) ins_part(insurer, INS_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) ins_part(insurer, INS_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) ins_part(insurer, INS_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) ins_part(insurer, INS_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) ins_part(insurer, INS_FOOTSTEPS));
    SceneMotion_Construct(ins_motion(insurer));
    SceneAction_Construct(ins_action(insurer));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) ins_part(insurer, INS_HEAP));
    *(const u8 **) (void *) object = data_ov071_0227a278;
    InsurerTalk_Construct(&insurer->talk);
    return insurer;
}
CLEAN_AS(func_ov071_02279ea4, Insurer_Create)
