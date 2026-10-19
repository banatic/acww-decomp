/* The special character of overlay 88, who teaches reactions: its object, its states and its
 * creation (reaction_npc.h). */
#include "reaction_npc.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/fx_math.h"
#include "autoload_2/heap.h"
#include "autoload_2/sound_emitter_class.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/acre_tile.h"
#include "main/act_effects.h"
#include "main/actor.h"
#include "main/block_021d27ac.h"
#include "main/camera_control.h"
#include "main/event_announce.h"
#include "main/event_queue.h"
#include "main/event_schedule.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/layered_model.h"
#include "main/main_random.h"
#include "main/motion_slots.h"
#include "main/obj_020d8c64.h"
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
#include "main/special_scene_object.h"
#include "main/speaker_anim.h"
#include "main/town_spot.h"
#include "main/town_tile.h"
#include "reaction_npc_talk.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(ReactionNpcTalk, step) == 0xb0, "step");
static_assert(offsetof(ReactionNpcTalk, owner) == 0xb8, "owner");
static_assert(offsetof(ReactionNpcTalk, chosen) == 0xbc, "chosen");
static_assert(offsetof(ReactionNpcTalk, known) == 0xbd, "known");
static_assert(offsetof(ReactionNpcTalk, offered) == 0xdb, "offered");
static_assert(sizeof(ReactionNpcTalk) == 0xe0, "its talk scene");
static_assert(sizeof(ReactionNpcStep) == 0x10, "a state's functions");
static_assert(offsetof(ReactionNpc, state) == 0x654, "state");
static_assert(offsetof(ReactionNpc, talk) == 0x658, "talk scene");
static_assert(offsetof(ReactionNpc, countdown) == 0x738, "countdown");
static_assert(offsetof(ReactionNpc, watch) == 0x739, "watch");
static_assert(sizeof(ReactionNpc) == 0x73c, "the size ReactionNpc_Create allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h). */
#define RNPC_POSITION 0x5c        /* Vec3: where it stands */
#define RNPC_YAW 0x8e             /* s16: where it faces */
#define RNPC_WALK_ANGLE 0x94      /* s16: where it walks */
#define RNPC_SPEED 0x98           /* fx32: its speed (scene_mover.h) */
#define RNPC_PERSON 0xea          /* u16: its person code */
#define RNPC_MODEL 0xec           /* LayeredModel */
#define RNPC_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define RNPC_FACE 0x2ac           /* SceneFace */
#define RNPC_ANIM 0x334           /* SpeakerAnim */
#define RNPC_MOVER 0x350          /* SceneMover */
#define RNPC_PROBE 0x3a8          /* the probe ahead */
#define RNPC_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define RNPC_LOOK 0x3b0           /* SceneLook */
#define RNPC_TALK_STATE 0x418     /* SceneTalkState */
#define RNPC_EFFECTS 0x420        /* ActEffects */
#define RNPC_COLLIDER 0x49c       /* CollisionContacts */
#define RNPC_CARRIER 0x4cc        /* FieldOwnedBody */
#define RNPC_EMITTER 0x514        /* SoundEmitterObject */
#define RNPC_FOOTSTEPS 0x558      /* Footsteps */
#define RNPC_MOTION 0x564         /* SceneMotion */
#define RNPC_ACTION 0x618         /* SceneAction */
#define RNPC_HEAP 0x640           /* PoolLink */

#define RNPC_NO_PERSON 0xfff1

/* The field actor of this console's player. */
#define RNPC_PLAYER_ACTOR 4

/* The codes of its vtable slot 0x4c (main's event_kinds.h). */
#define RNPC_EVENT_0 0
#define RNPC_EVENT_TALK 3
#define RNPC_EVENT_ENDED 8

/* The scene's vtable slot its talks call first. */
#define RNPC_TALK_SLOT_08 0x08

/* The event taking part in which teaching a reaction marks. */
#define RNPC_EVENT 0x43

/* No motion number (Obj020d8c64_TakeNewMotionNumber). */
#define RNPC_NO_NUMBER (-1)

/* The motions it asks for (scene_motion_kinds.h): stand, walk, walk in the second way, turn
 * then walk. */
#define RNPC_MOTION_STAND 0
#define RNPC_MOTION_WALK 1
#define RNPC_MOTION_WALK_2 2
#define RNPC_MOTION_TURN_WALK 4

/* What the probe ahead says (scene_probe.h): its first point blocked, its second, both. */
#define RNPC_PROBE_FIRST 1
#define RNPC_PROBE_SECOND 2
#define RNPC_PROBE_BOTH 3

/* The value of the pair at 0x3aa (SceneValue3aa_Grade) at which it stands. */
#define RNPC_GRADE_STAND 2

/* The frames a walk or a turn toward the point picked may go on. */
#define RNPC_WALK_FRAMES_WALK 100
#define RNPC_WALK_FRAMES_TURN 80

/* The tries at a point to walk to, and how far it is (12.0). */
#define RNPC_WALK_TRIES 6
#define RNPC_WALK_DISTANCE 0xc000

/* The camera's view, around the point it looks at: 16.0 to either side on x, from 26.0 before
 * to 10.0 past it on z. */
#define RNPC_VIEW_X 0x10000
#define RNPC_VIEW_Z_NEAR 0x1a000
#define RNPC_VIEW_Z_FAR 0xa000

/* The vtables: the class's and those of the classes it derives from. */
extern const u8 data_ov088_02279cec[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* Its states' functions (filled at start-up by __sinit_ov088_022799c4). */
extern ReactionNpcStep data_ov088_02279e28[REACTION_NPC_STATES];
/* The points beside the way ahead it steps to when the probe ahead is blocked: (0.5, 0, 1.0)
 * and (-0.5, 0, 1.0), set at start-up. */
extern Vec3 data_ov088_02279e10[2];
/* Its model's and texture's file names: "npc_sp/model/upa.nsbmd", "npc_sp/model/upa_tex.nsbtx". */
extern const char data_ov088_02279bc8[];
extern const char data_ov088_02279bf8[];
/* The field camera, or NULL, and the point it looks at. */
extern CameraControl *data_021c67a4;
extern Vec3 data_021c67d0;
/* The game's first random generator. */
extern Random data_021cb5a0;
/* Main's vector its look and its walk points start from, and its look's range. */
extern Vec3 data_021fbee8;
extern fx32 data_020c814c;
/* The word its motion requests carry. */
extern u16 data_020c80f8;
/* The speed scale of its animation player. */
extern s32 data_020c8120;
/* NitroSDK's sine and cosine table and fixed-point product. */
extern const fx16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);

static u8 *rnpc_part(ReactionNpc *npc, u32 offset)
{
    return npc->base + offset;
}

static Vec3 *rnpc_position(ReactionNpc *npc)
{
    return (Vec3 *) (void *) rnpc_part(npc, RNPC_POSITION);
}

static s16 rnpc_s16(ReactionNpc *npc, u32 offset)
{
    return *(const s16 *) (const void *) rnpc_part(npc, offset);
}

static s32 rnpc_speed(ReactionNpc *npc)
{
    return *(const s32 *) (const void *) rnpc_part(npc, RNPC_SPEED);
}

static SceneMotion *rnpc_motion(ReactionNpc *npc)
{
    return (SceneMotion *) (void *) rnpc_part(npc, RNPC_MOTION);
}

static SceneAction *rnpc_action(ReactionNpc *npc)
{
    return (SceneAction *) (void *) rnpc_part(npc, RNPC_ACTION);
}

static SceneMover *rnpc_mover(ReactionNpc *npc)
{
    return (SceneMover *) (void *) rnpc_part(npc, RNPC_MOVER);
}

static Footsteps *rnpc_footsteps(ReactionNpc *npc)
{
    return (Footsteps *) (void *) rnpc_part(npc, RNPC_FOOTSTEPS);
}

/* Its motion of kind `kind` (priority 1) from (x, z) at `angle`. */
static void rnpc_move(ReactionNpc *npc, int kind, int x, int z, int angle)
{
    SceneMotion_Request(rnpc_motion(npc), kind, 1, x, z, 0, (s16) angle, 0, 0, data_020c80f8, 0);
}

/* It stands (motion 0, priority 1). */
static void rnpc_stand(ReactionNpc *npc)
{
    rnpc_move(npc, RNPC_MOTION_STAND, 0, 0, 0);
}

/* Whether its motion is a walk or a turn then walk (kinds 1, 2 and 4), asking its kind once
 * for each until one matches. */
static int rnpc_is_walking(ReactionNpc *npc)
{
    return SceneMotion_Kind(rnpc_motion(npc)) == RNPC_MOTION_WALK ||
           SceneMotion_Kind(rnpc_motion(npc)) == RNPC_MOTION_WALK_2 ||
           SceneMotion_Kind(rnpc_motion(npc)) == RNPC_MOTION_TURN_WALK;
}

/* Whether the angle from it to `point` is within a quarter turn of where it faces. */
static int rnpc_faces(ReactionNpc *npc, const Vec3 *point)
{
    int angle = Vec_YawTo(rnpc_position(npc), point);
    return SceneObject_IsWithinQuarterTurn((s16) (angle - rnpc_s16(npc, RNPC_YAW)));
}

/* ---- The object */

/* func_ov088_02278a00 (vtable slot 0x40): its talk scene's destructor, then the special
 * character's; the object. */
void *ReactionNpc_Destroy(void *object)
{
    ReactionNpc *npc = object;
    *(const u8 **) (void *) npc->base = data_ov088_02279cec;
    ReactionNpcTalk_Destroy(&npc->talk);
    SpecialSceneObject_DestructBody(npc);
    return npc;
}
CLEAN_AS(func_ov088_02278a00, ReactionNpc_Destroy)

/* func_ov088_02278a28 (vtable slot 0x44): the same, then the object freed. */
ReactionNpc *ReactionNpc_Delete(ReactionNpc *npc)
{
    *(const u8 **) (void *) npc->base = data_ov088_02279cec;
    ReactionNpcTalk_Destroy(&npc->talk);
    SpecialSceneObject_DestructBody(npc);
    Heap_FreeAux(npc);
    return npc;
}
CLEAN_AS(func_ov088_02278a28, ReactionNpc_Delete)

/* func_ov088_02278a54: reaction `reaction` taught: put in the current player's motion slot
 * `slot`, and event 0x43 marked taken part in. */
void ReactionNpc_PutReaction(ReactionNpc *npc, int slot, int reaction)
{
    (void) npc;
    MotionSlots_Set(slot, reaction);
    EventSchedule_MarkTakenPart(RNPC_EVENT);
}
CLEAN_AS(func_ov088_02278a54, ReactionNpc_PutReaction)

/* func_ov088_02278a6c (vtable slot 0xa0): while it is watched (ReactionNpc.watch), a new
 * number its motion shows, kept (Obj020d8c64_TakeNewMotionNumber); else none (-1). */
int ReactionNpc_MotionNumber(ReactionNpc *npc)
{
    if (npc->watch == 0) {
        return RNPC_NO_NUMBER;
    }
    return Obj020d8c64_TakeNewMotionNumber(npc);
}
CLEAN_AS(func_ov088_02278a6c, ReactionNpc_MotionNumber)

/* func_ov088_02278a8c (vtable slot 0x4c, told of an event about it): code 0, state 0 (the talk
 * ends once its action is idle); code 3, its talk scene told through its slot 0x08, the
 * talk's partner this console's player's object, and it talks (state 4); code 8, the event
 * ended: it wanders (state 2). The base class is not told. */
void ReactionNpc_OnEvent(ReactionNpc *npc, int code)
{
    switch (code) {
        case RNPC_EVENT_0:
            ReactionNpc_SetState(npc, REACTION_NPC_TALK_END);
            break;
        case RNPC_EVENT_TALK: {
            u32 vtable = *(const u32 *) (const void *) &npc->talk;
            u32 slot = *(const u32 *) (uintptr_t) (vtable + RNPC_TALK_SLOT_08);
            ((void (*)(ReactionNpcTalk *))(uintptr_t) slot)(&npc->talk);
            SceneBase_SetMotionArg(&npc->talk.base, SceneObject_ActorObject(npc->base, RNPC_PLAYER_ACTOR));
            ReactionNpc_SetState(npc, REACTION_NPC_TALK);
            break;
        }
        case RNPC_EVENT_ENDED:
            ReactionNpc_SetState(npc, REACTION_NPC_WANDER);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov088_02278a8c, ReactionNpc_OnEvent)

/* func_ov088_02278adc (vtable slot 0x48): whether the player may talk to it: its action is
 * idle. */
int ReactionNpc_MayAct(ReactionNpc *npc)
{
    return SceneAction_IsBusy(rnpc_action(npc)) == 0;
}
CLEAN_AS(func_ov088_02278adc, ReactionNpc_MayAct)

/* ---- Its states */

/* func_ov088_0227915c (state 4's update): nothing. 1. */
int ReactionNpc_UpdateTalk(void)
{
    return 1;
}
CLEAN_AS(func_ov088_0227915c, ReactionNpc_UpdateTalk)

/* func_ov088_02279160 (state 4's entry): it turns to the talk's partner (when it has one, else
 * keeps its angle) and talks (its motion kept, the camera not). 1. */
int ReactionNpc_EnterTalk(ReactionNpc *npc)
{
    int partner = SceneBase_MotionArg(&npc->talk.base);
    int angle = rnpc_s16(npc, RNPC_YAW);
    if (partner != 0) {
        angle = SceneObject_YawTo(npc->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(rnpc_action(npc), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov088_02279160, ReactionNpc_EnterTalk)

/* func_ov088_0227919c (state 3's update): once it is in the camera's view, it wanders
 * (state 2). 1. */
int ReactionNpc_UpdateWait(ReactionNpc *npc)
{
    if (ReactionNpc_InView(npc)) {
        ReactionNpc_SetState(npc, REACTION_NPC_WANDER);
    }
    return 1;
}
CLEAN_AS(func_ov088_0227919c, ReactionNpc_UpdateWait)

/* func_ov088_022791b8 (state 3's entry): it stands, with no walk frames left and its
 * footsteps off. 1. */
int ReactionNpc_EnterWait(ReactionNpc *npc)
{
    rnpc_stand(npc);
    npc->countdown = 0;
    Footsteps_Disable(rnpc_footsteps(npc));
    return 1;
}
CLEAN_AS(func_ov088_022791b8, ReactionNpc_EnterWait)

/* func_ov088_02279208 (state 2's update): its walk frames counted down, then:
 * - out of the camera's view: while it moves, state 3;
 * - in view, unless it is steering aside (ReactionNpc_IsSteeringAside):
 *   - once its motion is done: it stands when the pair at 0x3aa says 2; else on one frame in
 *     eight (the game's first random generator) a free point 12.0 away is picked: within a
 *     quarter turn of where it faces it walks to it (kind 1, or 2 on one in four) unless it
 *     walks so already, for up to 100 frames; else it turns and walks (kind 4) unless it does
 *     so already, for up to 80 frames; without a point, or on the other frames, it stands;
 *   - while its motion goes on, it moves and walks or turns (kinds 1, 2 or 4): it stands when
 *     its walk frames ran out, or when the end point of its mover is more than a quarter turn
 *     from where it faces.
 * 0. */
int ReactionNpc_UpdateWander(ReactionNpc *npc)
{
    SceneMotion *motion = rnpc_motion(npc);
    int in_view = ReactionNpc_InView(npc);

    Countdown_Tick8(&npc->countdown);
    if (!in_view) {
        if (rnpc_speed(npc) != 0) {
            ReactionNpc_SetState(npc, REACTION_NPC_WAIT);
        }
        return 0;
    }
    if (ReactionNpc_IsSteeringAside(npc)) {
        return 0;
    }
    if (SceneMotion_IsDone(motion)) {
        if (SceneValue3aa_Grade((SceneValue3aa *) (void *) rnpc_part(npc, RNPC_VALUE_3AA)) == RNPC_GRADE_STAND) {
            rnpc_stand(npc);
            return 0;
        }
        if ((Random_Next(&data_021cb5a0) & 7) != 0) {
            rnpc_stand(npc);
            return 0;
        }
        Vec3 point = data_021fbee8;
        if (!ReactionNpc_PickWalkPoint(npc, &point.x, &point.z)) {
            rnpc_stand(npc);
            return 0;
        }
        int angle = Vec_YawTo(rnpc_position(npc), &point);
        if (SceneObject_IsWithinQuarterTurn((s16) (angle - rnpc_s16(npc, RNPC_YAW)))) {
            int kind = RNPC_MOTION_WALK;
            if (MainRandom_Below(4) == 0) {
                kind = RNPC_MOTION_WALK_2;
            }
            if (kind != SceneMotion_Kind(motion)) {
                rnpc_move(npc, kind, point.x, point.z, 0);
                npc->countdown = RNPC_WALK_FRAMES_WALK;
            }
        } else if (SceneMotion_Kind(motion) != RNPC_MOTION_TURN_WALK) {
            rnpc_move(npc, RNPC_MOTION_TURN_WALK, point.x, point.z, angle);
            npc->countdown = RNPC_WALK_FRAMES_TURN;
        }
        return 0;
    }
    if (rnpc_speed(npc) != 0 && rnpc_is_walking(npc)) {
        if (npc->countdown == 0) {
            rnpc_stand(npc);
        } else {
            Vec3 end = *SceneMover_End(rnpc_mover(npc));
            if (!rnpc_faces(npc, &end)) {
                rnpc_stand(npc);
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov088_02279208, ReactionNpc_UpdateWander)

/* func_ov088_02279450: whether it moves and steps aside of what blocks its way
 * (ReactionNpc_SteerAside). */
int ReactionNpc_IsSteeringAside(ReactionNpc *npc)
{
    if (rnpc_speed(npc) == 0) {
        return 0;
    }
    return ReactionNpc_SteerAside(npc) != 0;
}
CLEAN_AS(func_ov088_02279450, ReactionNpc_IsSteeringAside)

/* func_ov088_02279474: what the probe ahead says, acted on while it is not yet within its
 * mover's reach of its start point: its first point blocked, the mover's end becomes the free
 * point beside the way at (-0.5, 0, 1.0); its second, the one at (0.5, 0, 1.0); with no free
 * point there, or with both blocked, it stands; whether it acted (1 for those). Within reach,
 * the mover's end goes back to its start when they differ; 0. */
int ReactionNpc_SteerAside(ReactionNpc *npc)
{
    SceneMover *mover = rnpc_mover(npc);
    int blocked = SceneProbe_Bits(rnpc_part(npc, RNPC_PROBE));

    if (SceneMover_Reached(mover, npc->base, 1) != 0) {
        if (SceneMover_PointsDiffer(mover)) {
            SceneMover_EndAtStart(mover);
        }
        return 0;
    }

    const Vec3 *offset;
    switch (blocked) {
        case RNPC_PROBE_FIRST:
            offset = &data_ov088_02279e10[1];
            break;
        case RNPC_PROBE_SECOND:
            offset = &data_ov088_02279e10[0];
            break;
        case RNPC_PROBE_BOTH:
            rnpc_stand(npc);
            return 1;
        default:
            return 0;
    }
    Vec3 point;
    if (ReactionNpc_SidePoint(npc, &point, offset)) {
        SceneMover_SetEnd(mover, &point);
    } else {
        rnpc_stand(npc);
    }
    return 1;
}
CLEAN_AS(func_ov088_02279474, ReactionNpc_SteerAside)

/* func_ov088_02279574: the point `offset` from it, turned by its walking angle; kept in `out`
 * when it is not blocked (SceneProbe_IsBlocked other than 1). Whether it was. */
int ReactionNpc_SidePoint(ReactionNpc *npc, Vec3 *out, const Vec3 *offset)
{
    Vec3 point;
    SceneProbe_PointAt(&point, rnpc_position(npc), offset, rnpc_s16(npc, RNPC_WALK_ANGLE));
    if (SceneProbe_IsBlocked(&point) == 1) {
        return 0;
    }
    *out = point;
    return 1;
}
CLEAN_AS(func_ov088_02279574, ReactionNpc_SidePoint)

/* func_ov088_022795b0: up to six tries at a point 12.0 from it in a random direction (the
 * game's first random generator), put at its tile's centre: the first whose tile is clear
 * (TownTile_IsClearAt) gives `*x` and `*z`. Whether one did. */
int ReactionNpc_PickWalkPoint(ReactionNpc *npc, fx32 *x, fx32 *z)
{
    Vec3 point = {0, 0, 0};
    for (int i = 0; i < RNPC_WALK_TRIES; i++) {
        u16 angle = (u16) (s16) Random_Next(&data_021cb5a0);
        int index = (angle >> 4) * 2;
        point.x = FX_MulFunc(RNPC_WALK_DISTANCE, FX_SinCosTable_[index]) + rnpc_position(npc)->x;
        point.z = FX_MulFunc(RNPC_WALK_DISTANCE, FX_SinCosTable_[index + 1]) + rnpc_position(npc)->z;
        AcreTile_SnapToTileCentre(&point, &point);
        if (TownTile_IsClearAt(&point, NULL)) {
            *x = point.x;
            *z = point.z;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov088_022795b0, ReactionNpc_PickWalkPoint)

/* func_ov088_02279640: whether there is a field camera and it is in its view around the point
 * it looks at (ReactionNpc_IsInViewOf). */
int ReactionNpc_InView(ReactionNpc *npc)
{
    if (data_021c67a4 == NULL) {
        return 0;
    }
    Vec3 focus = data_021c67d0;
    return ReactionNpc_IsInViewOf((int) (u32) (uintptr_t) npc, &focus, rnpc_position(npc));
}
CLEAN_AS(func_ov088_02279640, ReactionNpc_InView)

/* func_ov088_02279678: whether `at` is strictly within 16.0 of `focus` on x and strictly
 * between 26.0 before and 10.0 past it on z. */
int ReactionNpc_IsInViewOf(int unused, const Vec3 *focus, const Vec3 *at)
{
    (void) unused;
    return at->x > focus->x - RNPC_VIEW_X && at->x < focus->x + RNPC_VIEW_X && at->z > focus->z - RNPC_VIEW_Z_NEAR &&
           at->z < focus->z + RNPC_VIEW_Z_FAR;
}
CLEAN_AS(func_ov088_02279678, ReactionNpc_IsInViewOf)

/* func_ov088_022796d0 (state 2's entry): no walk frames left; it stands; its footsteps on
 * (twice); it looks at the player (priority 0, within its look's range, only in view). 1. */
int ReactionNpc_EnterWander(ReactionNpc *npc)
{
    npc->countdown = 0;
    rnpc_stand(npc);
    Footsteps_Enable(rnpc_footsteps(npc));
    Footsteps_Enable(rnpc_footsteps(npc));
    SceneLook_Request((SceneLook *) (void *) rnpc_part(npc, RNPC_LOOK), SCENE_LOOK_PLAYER, 0, 0, &data_021fbee8,
                      RNPC_PLAYER_ACTOR, data_020c814c, 1);
    return 1;
}
CLEAN_AS(func_ov088_022796d0, ReactionNpc_EnterWander)

/* func_ov088_02279750 (state 1's update): nothing. 1. */
int ReactionNpc_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov088_02279750, ReactionNpc_UpdateTalked)

/* func_ov088_02279754 (state 0's update): once its action is idle, the object's event ends and
 * state 1 follows. 1. */
int ReactionNpc_UpdateTalkEnd(ReactionNpc *npc)
{
    if (SceneAction_IsBusy(rnpc_action(npc)) == 0) {
        EventQueue_FinishObjectEvent(npc);
        ReactionNpc_SetState(npc, REACTION_NPC_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov088_02279754, ReactionNpc_UpdateTalkEnd)

/* func_ov088_02279780 (state 0's entry): 1. */
int ReactionNpc_EnterTalkEnd(void)
{
    return 1;
}
CLEAN_AS(func_ov088_02279780, ReactionNpc_EnterTalkEnd)

/* func_ov088_02279784: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 4 (the table is not bounded). */
void ReactionNpc_SetState(ReactionNpc *npc, int state)
{
    const ReactionNpcStep *step = &data_ov088_02279e28[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, npc);
    }
    if (taken != 0) {
        npc->state = state;
    }
}
CLEAN_AS(func_ov088_02279784, ReactionNpc_SetState)

/* func_ov088_022797c8 (vtable slot 0x68, each frame): its state's update when it has one, and
 * its answer; else 0.
 * REQUIRES: its state is 0 to 4. */
int ReactionNpc_Update(ReactionNpc *npc)
{
    const ReactionNpcStep *step = &data_ov088_02279e28[npc->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, npc);
}
CLEAN_AS(func_ov088_022797c8, ReactionNpc_Update)

/* func_ov088_02279814 (vtable slot 0x70): its model's file name, "npc_sp/model/upa.nsbmd". */
int ReactionNpc_ModelName(void)
{
    return (int) (u32) (uintptr_t) data_ov088_02279bc8;
}
CLEAN_AS(func_ov088_02279814, ReactionNpc_ModelName)

/* func_ov088_0227981c (vtable slot 0x6c): its texture's file name,
 * "npc_sp/model/upa_tex.nsbtx". */
int ReactionNpc_TextureName(void)
{
    return (int) (u32) (uintptr_t) data_ov088_02279bf8;
}
CLEAN_AS(func_ov088_0227981c, ReactionNpc_TextureName)

/* func_ov088_02279824 (vtable slot 0x0c, its leaving): unless the special character refuses,
 * a random spot of the town is picked for the next time (part 0x04 of main's object at
 * data_021d27ac) unless the event's announcement was entered. Whether it left. */
int ReactionNpc_Leave(ReactionNpc *npc)
{
    if (SpecialSceneObject_Leave(npc) == 0) {
        return 0;
    }
    if (EventAnnounce_Entered() == 0) {
        TownSpot_PickRandom((TownSpot *) Block021d27ac_Part04(Block021d27ac_Get()));
    }
    return 1;
}
CLEAN_AS(func_ov088_02279824, ReactionNpc_Leave)

/* func_ov088_02279850 (vtable slot 0x00, its start): unless the special character refuses to
 * start, it waits (state 3). Whether it started. */
int ReactionNpc_Start(ReactionNpc *npc)
{
    if (SpecialSceneObject_Start(npc) == 0) {
        return 0;
    }
    ReactionNpc_SetState(npc, REACTION_NPC_WAIT);
    return 1;
}
CLEAN_AS(func_ov088_02279850, ReactionNpc_Start)

/* func_ov088_02279870 (vtable slot 0x04, its set-up): unless the special character refuses,
 * its talk scene becomes its scene and gets it as its owner. Whether it was set up. */
int ReactionNpc_Init(ReactionNpc *npc)
{
    if (SpecialSceneObject_Init(npc) == 0) {
        return 0;
    }
    SceneObject_SetScene(npc->base, &npc->talk.base);
    ReactionNpcTalk_Begin(&npc->talk, npc);
    return 1;
}
CLEAN_AS(func_ov088_02279870, ReactionNpc_Init)

/* func_ov088_022798a0 (vtable slot 0xa8): the speed scale of its animation player, main's
 * data_020c8120 as it is (the special character's own slot gives data_021c30ac). */
int ReactionNpc_AnimSpeed(void)
{
    return data_020c8120;
}
CLEAN_AS(func_ov088_022798a0, ReactionNpc_AnimSpeed)

/* func_ov088_022798ac (the create function its record at 0x02279be0 names): a zeroed block of
 * 0x73c bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable and its talk scene. Null when
 * there is no room. */
void *ReactionNpc_Create(void)
{
    ReactionNpc *npc = (ReactionNpc *) Heap_AllocAuxZeroed(sizeof(ReactionNpc));
    if (npc == NULL) {
        return NULL;
    }
    u8 *object = npc->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) rnpc_part(npc, RNPC_PERSON) = RNPC_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) rnpc_part(npc, RNPC_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) rnpc_part(npc, RNPC_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) rnpc_part(npc, RNPC_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) rnpc_part(npc, RNPC_ANIM));
    SceneMover_Construct(rnpc_mover(npc));
    SceneProbe_Construct(rnpc_part(npc, RNPC_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) rnpc_part(npc, RNPC_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) rnpc_part(npc, RNPC_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) rnpc_part(npc, RNPC_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) rnpc_part(npc, RNPC_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) rnpc_part(npc, RNPC_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) rnpc_part(npc, RNPC_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) rnpc_part(npc, RNPC_EMITTER));
    Footsteps_Construct(rnpc_footsteps(npc));
    SceneMotion_Construct(rnpc_motion(npc));
    SceneAction_Construct(rnpc_action(npc));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) rnpc_part(npc, RNPC_HEAP));
    *(const u8 **) (void *) object = data_ov088_02279cec;
    ReactionNpcTalk_Construct(&npc->talk);
    return npc;
}
CLEAN_AS(func_ov088_022798ac, ReactionNpc_Create)
