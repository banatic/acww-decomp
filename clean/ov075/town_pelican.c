/* The town pelican of overlay 75: his object, his states and his creation (town_pelican.h). */
#include "town_pelican.h"

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
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/footsteps.h"
#include "main/layered_model.h"
#include "main/main_random.h"
#include "main/near_spot.h"
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
#include "main/town_tile.h"
#include "town_pelican_talk.h"

static_assert(sizeof(SceneBase) == 0x80, "scene base");
static_assert(offsetof(TownPelicanTalk, sequence) == 0xb0, "sequence");
static_assert(offsetof(TownPelicanTalk, step) == 0xb4, "step");
static_assert(offsetof(TownPelicanTalk, owner) == 0xb8, "owner");
static_assert(sizeof(TownPelicanTalk) == 0xc0, "his talk scene");
static_assert(sizeof(TownPelicanStep) == 0x10, "a state's functions");
static_assert(offsetof(TownPelican, state) == 0x654, "state");
static_assert(offsetof(TownPelican, talk) == 0x658, "talk scene");
static_assert(offsetof(TownPelican, met) == 0x718, "met");
static_assert(offsetof(TownPelican, walk_frames) == 0x719, "walk frames");
static_assert(sizeof(TownPelican) == 0x71c, "the size TownPelican_Create allocates");

/* The parts of the special character's scene object used here, by place (main's
 * scene_object.h). */
#define TPEL_POSITION 0x5c        /* Vec3: where he stands */
#define TPEL_LAST_POSITION 0x68   /* Vec3: where he stood the frame before */
#define TPEL_YAW 0x8e             /* s16: where he faces */
#define TPEL_WALK_ANGLE 0x94      /* s16: where he walks */
#define TPEL_SPEED 0x98           /* fx32: his speed (scene_mover.h) */
#define TPEL_PERSON 0xea          /* u16: his person code */
#define TPEL_MODEL 0xec           /* LayeredModel */
#define TPEL_STANDARD_ANIMS 0x2a0 /* SceneStandardAnims */
#define TPEL_FACE 0x2ac           /* SceneFace */
#define TPEL_ANIM 0x334           /* SpeakerAnim */
#define TPEL_MOVER 0x350          /* SceneMover */
#define TPEL_PROBE 0x3a8          /* the probe ahead */
#define TPEL_VALUE_3AA 0x3aa      /* SceneValue3aa */
#define TPEL_LOOK 0x3b0           /* SceneLook */
#define TPEL_TALK_STATE 0x418     /* SceneTalkState */
#define TPEL_EFFECTS 0x420        /* ActEffects */
#define TPEL_COLLIDER 0x49c       /* CollisionContacts */
#define TPEL_CARRIER 0x4cc        /* FieldOwnedBody */
#define TPEL_HELD_FLAGS 0x4e8     /* u32: the scene object's flags (2: held) */
#define TPEL_EMITTER 0x514        /* SoundEmitterObject */
#define TPEL_FOOTSTEPS 0x558      /* Footsteps */
#define TPEL_SHOWN 0x561          /* u8: 0 stops his frame after the mover, and his drawing */
#define TPEL_MOTION 0x564         /* SceneMotion */
#define TPEL_ACTION 0x618         /* SceneAction */
#define TPEL_HEAP 0x640           /* PoolLink */

#define TPEL_NO_PERSON 0xfff1
#define TPEL_HELD 2

/* The field actor of this console's player. */
#define TPEL_PLAYER_ACTOR 4

/* The codes of his vtable slot 0x4c (main's event_kinds.h). */
#define TPEL_EVENT_0 0
#define TPEL_EVENT_TALK 3
#define TPEL_EVENT_ENDED 8

/* The scene's vtable slot his talks call first. */
#define TPEL_TALK_SLOT_08 0x08

/* The motions he asks for (scene_motion_kinds.h): stand, walk, walk in the second way, turn
 * then walk. */
#define TPEL_MOTION_STAND 0
#define TPEL_MOTION_WALK 1
#define TPEL_MOTION_WALK_2 2
#define TPEL_MOTION_TURN_WALK 4

/* The animation he rests with. */
#define TPEL_REST_ANIMATION 0xef

/* What the probe ahead says (scene_probe.h): its first point blocked, its second, both. */
#define TPEL_PROBE_FIRST 1
#define TPEL_PROBE_SECOND 2
#define TPEL_PROBE_BOTH 3

/* The value of the pair at 0x3aa (SceneValue3aa_Grade) at which he stands. */
#define TPEL_GRADE_STAND 2

/* The frames a walk or a turn toward the point picked may go on. */
#define TPEL_WALK_FRAMES_WALK 100
#define TPEL_WALK_FRAMES_TURN 80

/* The tries at a point to walk to, and how far it is (12.0). */
#define TPEL_WALK_TRIES 6
#define TPEL_WALK_DISTANCE 0xc000

/* The camera's view, around the point it looks at: 16.0 to either side on x, from 26.0 before
 * to 10.0 past it on z. */
#define TPEL_VIEW_X 0x10000
#define TPEL_VIEW_Z_NEAR 0x1a000
#define TPEL_VIEW_Z_FAR 0xa000

/* The vtables: the class's and those of the classes it derives from. */
extern const u8 data_ov075_022799fc[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* His states' functions (filled at start-up by __sinit_ov075_02279724). */
extern TownPelicanStep data_ov075_02279b08[TOWN_PELICAN_STATES];
/* The points beside the way ahead he steps to when the probe ahead is blocked: (0.5, 0, 1.0)
 * and (-0.5, 0, 1.0), set at start-up. */
extern Vec3 data_ov075_02279af0[2];
/* His model's and texture's file names: "npc_sp/model/plb.nsbmd", "npc_sp/model/plb_tex.nsbtx". */
extern const char data_ov075_02279900[];
extern const char data_ov075_02279948[];
/* The field camera, or NULL, and the point it looks at. */
extern CameraControl *data_021c67a4;
extern Vec3 data_021c67d0;
/* The game's first random generator. */
extern Random data_021cb5a0;
/* Main's vector his look and his walk points start from, and his look's range. */
extern Vec3 data_021fbee8;
extern fx32 data_020c814c;
/* The word his motion requests carry. */
extern u16 data_020c80f8;
/* The speed scale of his animation player. */
extern s32 data_020c8120;
/* NitroSDK's sine and cosine table and fixed-point product. */
extern const fx16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);

static u8 *tpel_part(TownPelican *pelican, u32 offset)
{
    return pelican->base + offset;
}

static Vec3 *tpel_position(TownPelican *pelican)
{
    return (Vec3 *) (void *) tpel_part(pelican, TPEL_POSITION);
}

static s16 tpel_s16(TownPelican *pelican, u32 offset)
{
    return *(const s16 *) (const void *) tpel_part(pelican, offset);
}

static s32 tpel_speed(TownPelican *pelican)
{
    return *(const s32 *) (const void *) tpel_part(pelican, TPEL_SPEED);
}

static SceneMotion *tpel_motion(TownPelican *pelican)
{
    return (SceneMotion *) (void *) tpel_part(pelican, TPEL_MOTION);
}

static SceneAction *tpel_action(TownPelican *pelican)
{
    return (SceneAction *) (void *) tpel_part(pelican, TPEL_ACTION);
}

static SceneMover *tpel_mover(TownPelican *pelican)
{
    return (SceneMover *) (void *) tpel_part(pelican, TPEL_MOVER);
}

static Footsteps *tpel_footsteps(TownPelican *pelican)
{
    return (Footsteps *) (void *) tpel_part(pelican, TPEL_FOOTSTEPS);
}

static SceneLook *tpel_look(TownPelican *pelican)
{
    return (SceneLook *) (void *) tpel_part(pelican, TPEL_LOOK);
}

static u32 *tpel_held_flags(TownPelican *pelican)
{
    return (u32 *) (void *) tpel_part(pelican, TPEL_HELD_FLAGS);
}

/* His look asked for, of `kind` (priority 0, the player's actor, within his look's range, only
 * in view). */
static void tpel_look_at(TownPelican *pelican, u8 kind)
{
    SceneLook_Request(tpel_look(pelican), kind, 0, 0, &data_021fbee8, TPEL_PLAYER_ACTOR, data_020c814c, 1);
}

/* His motion of kind `kind` (priority 1) from (x, z) at `angle`. */
static void tpel_move(TownPelican *pelican, int kind, int x, int z, int angle)
{
    SceneMotion_Request(tpel_motion(pelican), kind, 1, x, z, 0, (s16) angle, 0, 0, data_020c80f8, 0);
}

/* He stands (motion 0, priority 1). */
static void tpel_stand(TownPelican *pelican)
{
    tpel_move(pelican, TPEL_MOTION_STAND, 0, 0, 0);
}

/* Whether his motion is a walk or a turn then walk (kinds 1, 2 and 4), asking its kind once
 * for each until one matches. */
static int tpel_is_walking(TownPelican *pelican)
{
    return SceneMotion_Kind(tpel_motion(pelican)) == TPEL_MOTION_WALK ||
           SceneMotion_Kind(tpel_motion(pelican)) == TPEL_MOTION_WALK_2 ||
           SceneMotion_Kind(tpel_motion(pelican)) == TPEL_MOTION_TURN_WALK;
}

/* The town's near spot (part 0x24 of the object at data_021d27ac). */
static NearSpot *tpel_near_spot(void)
{
    return (NearSpot *) Block021d27ac_Part24(Block021d27ac_Get());
}

/* ---- The object */

/* func_ov075_02278a00 (vtable slot 0x40): his talk scene's destructor, then the special
 * character's; the object. */
void *TownPelican_Destroy(TownPelican *pelican)
{
    *(const u8 **) (void *) pelican->base = data_ov075_022799fc;
    TownPelicanTalk_Destroy(&pelican->talk);
    SpecialSceneObject_DestructBody(pelican);
    return pelican;
}
CLEAN_AS(func_ov075_02278a00, TownPelican_Destroy)

/* func_ov075_02278a28 (vtable slot 0x44): the same, then the object freed. */
void *TownPelican_Delete(void *object)
{
    TownPelican *pelican = object;
    *(const u8 **) (void *) pelican->base = data_ov075_022799fc;
    TownPelicanTalk_Destroy(&pelican->talk);
    SpecialSceneObject_DestructBody(pelican);
    Heap_FreeAux(pelican);
    return pelican;
}
CLEAN_AS(func_ov075_02278a28, TownPelican_Delete)

/* func_ov075_02278a54 (vtable slot 0x4c, told of an event about him): code 0, state 2 (the
 * talk ends once his action is idle); code 3, his talk scene told through its slot 0x08, the
 * talk's partner this console's player's object, and once met he talks (state 1); code 8, the
 * event ended: he rests (state 0) or, once met, wanders (state 5). The base class is not told. */
void TownPelican_OnEvent(TownPelican *pelican, int code)
{
    switch (code) {
        case TPEL_EVENT_0:
            TownPelican_SetState(pelican, TOWN_PELICAN_TALK_END);
            break;
        case TPEL_EVENT_TALK: {
            u32 vtable = *(const u32 *) (const void *) &pelican->talk;
            u32 slot = *(const u32 *) (uintptr_t) (vtable + TPEL_TALK_SLOT_08);
            ((void (*)(TownPelicanTalk *))(uintptr_t) slot)(&pelican->talk);
            SceneBase_SetMotionArg(&pelican->talk.base, SceneObject_ActorObject(pelican->base, TPEL_PLAYER_ACTOR));
            if (pelican->met != 0) {
                TownPelican_SetState(pelican, TOWN_PELICAN_TALK);
            }
            break;
        }
        case TPEL_EVENT_ENDED:
            TownPelican_SetState(pelican, pelican->met == 0 ? TOWN_PELICAN_REST : TOWN_PELICAN_WANDER);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov075_02278a54, TownPelican_OnEvent)

/* func_ov075_02278ac0 (vtable slot 0x48): whether the player may talk to him: he is shown and
 * his action is idle. */
int TownPelican_MayAct(TownPelican *pelican)
{
    if (*tpel_part(pelican, TPEL_SHOWN) == 0) {
        return 0;
    }
    return SceneAction_IsBusy(tpel_action(pelican)) == 0;
}
CLEAN_AS(func_ov075_02278ac0, TownPelican_MayAct)

/* ---- His states */

/* func_ov075_02278de8 (state 3's update): nothing. 1. */
int TownPelican_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_ov075_02278de8, TownPelican_UpdateTalked)

/* func_ov075_02278dec (state 2's update): once his action is idle, the object's event ends and
 * state 3 follows. 1. */
int TownPelican_UpdateTalkEnd(TownPelican *pelican)
{
    if (!SceneAction_IsBusy(tpel_action(pelican))) {
        EventQueue_FinishObjectEvent(pelican);
        TownPelican_SetState(pelican, TOWN_PELICAN_TALKED);
    }
    return 1;
}
CLEAN_AS(func_ov075_02278dec, TownPelican_UpdateTalkEnd)

/* func_ov075_02278e18 (state 2's entry): unless he was met, he talks where he is (his motion
 * and the camera not kept). 1. */
int TownPelican_EnterTalkEnd(TownPelican *pelican)
{
    if (pelican->met == 0) {
        SceneAction_RequestTalk(tpel_action(pelican), 0, 0);
    }
    return 1;
}
CLEAN_AS(func_ov075_02278e18, TownPelican_EnterTalkEnd)

/* func_ov075_02278e40 (state 1's update): nothing. 1. */
int TownPelican_UpdateTalk(void)
{
    return 1;
}
CLEAN_AS(func_ov075_02278e40, TownPelican_UpdateTalk)

/* func_ov075_02278e44 (state 1's entry): once met, he looks at the player and is no longer held
 * (flag 2 at 0x4e8 cleared); he turns to the talk's partner (when it has one, else keeps his
 * angle) and talks (his motion kept, the camera not). 1. */
int TownPelican_EnterTalk(TownPelican *pelican)
{
    int partner = SceneBase_MotionArg(&pelican->talk.base);
    int angle = tpel_s16(pelican, TPEL_YAW);
    if (pelican->met != 0) {
        tpel_look_at(pelican, SCENE_LOOK_PLAYER);
        *tpel_held_flags(pelican) &= ~(u32) TPEL_HELD;
    }
    if (partner != 0) {
        angle = SceneObject_YawTo(pelican->base, (u8 *) (uintptr_t) (u32) partner);
    }
    SceneAction_RequestTurnAndTalk(tpel_action(pelican), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_ov075_02278e44, TownPelican_EnterTalk)

/* func_ov075_02278ecc (state 5's update): out of the camera's view, nothing but his walk frames
 * counted down. In view, the same, then, unless he is steering aside
 * (TownPelican_IsSteeringAside):
 * - once his motion is done: he stands when the pair at 0x3aa says 2; else on one frame in
 *   eight (the game's first random generator) a free point 12.0 away is picked: within a
 *   quarter turn of where he faces he walks to it (kind 1, or 2 on one in four) for up to 100
 *   frames; else he turns and walks (kind 4) for up to 80 frames; without a point, or on the
 *   other frames, he stands;
 * - while his motion goes on, he moves and walks or turns (kinds 1, 2 or 4): he stands when his
 *   walk frames ran out, or when the end point of his mover is more than a quarter turn from
 *   where he faces.
 * 0. */
int TownPelican_UpdateWander(TownPelican *pelican)
{
    SceneMotion *motion = tpel_motion(pelican);
    int in_view = TownPelican_InView(pelican);

    Countdown_Tick8(&pelican->walk_frames);
    if (!in_view || TownPelican_IsSteeringAside(pelican)) {
        return 0;
    }
    if (SceneMotion_IsDone(motion)) {
        if (SceneValue3aa_Grade((SceneValue3aa *) (void *) tpel_part(pelican, TPEL_VALUE_3AA)) == TPEL_GRADE_STAND) {
            tpel_stand(pelican);
            return 0;
        }
        if ((Random_Next(&data_021cb5a0) & 7) != 0) {
            tpel_stand(pelican);
            return 0;
        }
        Vec3 point = data_021fbee8;
        if (!TownPelican_PickWalkPoint(pelican, &point.x, &point.z)) {
            tpel_stand(pelican);
            return 0;
        }
        int angle = Vec_YawTo(tpel_position(pelican), &point);
        if (SceneObject_IsWithinQuarterTurn((s16) (angle - tpel_s16(pelican, TPEL_YAW)))) {
            int kind = TPEL_MOTION_WALK;
            if (MainRandom_Below(4) == 0) {
                kind = TPEL_MOTION_WALK_2;
            }
            tpel_move(pelican, kind, point.x, point.z, 0);
            pelican->walk_frames = TPEL_WALK_FRAMES_WALK;
        } else {
            tpel_move(pelican, TPEL_MOTION_TURN_WALK, point.x, point.z, angle);
            pelican->walk_frames = TPEL_WALK_FRAMES_TURN;
        }
        return 0;
    }
    if (tpel_speed(pelican) != 0 && tpel_is_walking(pelican)) {
        if (pelican->walk_frames == 0) {
            tpel_stand(pelican);
        } else {
            Vec3 end = *SceneMover_End(tpel_mover(pelican));
            int angle = Vec_YawTo(tpel_position(pelican), &end);
            if (!SceneObject_IsWithinQuarterTurn((s16) (angle - tpel_s16(pelican, TPEL_YAW)))) {
                tpel_stand(pelican);
            }
        }
    }
    return 0;
}
CLEAN_AS(func_ov075_02278ecc, TownPelican_UpdateWander)

/* func_ov075_022790e4: whether he moves and steps aside of what blocks his way
 * (TownPelican_SteerAside). */
int TownPelican_IsSteeringAside(TownPelican *pelican)
{
    if (tpel_speed(pelican) == 0) {
        return 0;
    }
    return TownPelican_SteerAside(pelican) != 0;
}
CLEAN_AS(func_ov075_022790e4, TownPelican_IsSteeringAside)

/* func_ov075_02279108: what the probe ahead says, acted on while he is not yet within his
 * mover's reach of its start point: its first point blocked, the mover's end becomes the free
 * point beside the way at (-0.5, 0, 1.0); its second, the one at (0.5, 0, 1.0); with no free
 * point there, or with both blocked, he stands; whether it acted (1 for those). Within reach,
 * the mover's end goes back to its start when they differ; 0. */
int TownPelican_SteerAside(TownPelican *pelican)
{
    SceneMover *mover = tpel_mover(pelican);
    int blocked = SceneProbe_Bits(tpel_part(pelican, TPEL_PROBE));

    if (SceneMover_Reached(mover, pelican->base, 1) != 0) {
        if (SceneMover_PointsDiffer(mover)) {
            SceneMover_EndAtStart(mover);
        }
        return 0;
    }

    const Vec3 *offset;
    switch (blocked) {
        case TPEL_PROBE_FIRST:
            offset = &data_ov075_02279af0[1];
            break;
        case TPEL_PROBE_SECOND:
            offset = &data_ov075_02279af0[0];
            break;
        case TPEL_PROBE_BOTH:
            tpel_stand(pelican);
            return 1;
        default:
            return 0;
    }
    Vec3 point;
    if (TownPelican_SidePoint(pelican, &point, offset)) {
        SceneMover_SetEnd(mover, &point);
    } else {
        tpel_stand(pelican);
    }
    return 1;
}
CLEAN_AS(func_ov075_02279108, TownPelican_SteerAside)

/* func_ov075_02279208: the point `offset` from him, turned by his walking angle; kept in `out`
 * when it is not blocked (SceneProbe_IsBlocked other than 1). Whether it was. */
int TownPelican_SidePoint(TownPelican *pelican, Vec3 *out, const Vec3 *offset)
{
    Vec3 point;
    SceneProbe_PointAt(&point, tpel_position(pelican), offset, tpel_s16(pelican, TPEL_WALK_ANGLE));
    if (SceneProbe_IsBlocked(&point) == 1) {
        return 0;
    }
    *out = point;
    return 1;
}
CLEAN_AS(func_ov075_02279208, TownPelican_SidePoint)

/* func_ov075_02279244: up to six tries at a point 12.0 from him in a random direction (the
 * game's first random generator), put at its tile's centre: the first whose tile is clear
 * (TownTile_IsClearAt) gives `*x` and `*z`. Whether one did. */
int TownPelican_PickWalkPoint(TownPelican *pelican, fx32 *x, fx32 *z)
{
    Vec3 point = {0, 0, 0};
    for (int i = 0; i < TPEL_WALK_TRIES; i++) {
        u16 angle = (u16) (s16) Random_Next(&data_021cb5a0);
        int index = (angle >> 4) * 2;
        point.x = FX_MulFunc(TPEL_WALK_DISTANCE, FX_SinCosTable_[index]) + tpel_position(pelican)->x;
        point.z = FX_MulFunc(TPEL_WALK_DISTANCE, FX_SinCosTable_[index + 1]) + tpel_position(pelican)->z;
        AcreTile_SnapToTileCentre(&point, &point);
        if (TownTile_IsClearAt(&point, NULL)) {
            *x = point.x;
            *z = point.z;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov075_02279244, TownPelican_PickWalkPoint)

/* func_ov075_022792d4: whether there is a field camera and he is in its view around the point
 * it looks at (TownPelican_IsInViewOf). */
int TownPelican_InView(TownPelican *pelican)
{
    if (data_021c67a4 == NULL) {
        return 0;
    }
    Vec3 focus = data_021c67d0;
    return TownPelican_IsInViewOf((int) (u32) (uintptr_t) pelican, &focus, tpel_position(pelican));
}
CLEAN_AS(func_ov075_022792d4, TownPelican_InView)

/* func_ov075_0227930c: whether `at` is strictly within 16.0 of `focus` on x and strictly
 * between 26.0 before and 10.0 past it on z. */
int TownPelican_IsInViewOf(int unused, const Vec3 *focus, const Vec3 *at)
{
    (void) unused;
    return at->x > focus->x - TPEL_VIEW_X && at->x < focus->x + TPEL_VIEW_X && at->z > focus->z - TPEL_VIEW_Z_NEAR &&
           at->z < focus->z + TPEL_VIEW_Z_FAR;
}
CLEAN_AS(func_ov075_0227930c, TownPelican_IsInViewOf)

/* func_ov075_02279364 (state 5's entry): no walk frames left; he stands; his footsteps on
 * (twice); he looks at the player. 1. */
int TownPelican_EnterWander(TownPelican *pelican)
{
    pelican->walk_frames = 0;
    tpel_stand(pelican);
    Footsteps_Enable(tpel_footsteps(pelican));
    Footsteps_Enable(tpel_footsteps(pelican));
    tpel_look_at(pelican, SCENE_LOOK_PLAYER);
    return 1;
}
CLEAN_AS(func_ov075_02279364, TownPelican_EnterWander)

/* func_ov075_022793e4 (state 4's update): when the town's near spot was found, he is put there
 * (the position of the frame before the same), shown, and rests (state 0). 1. */
int TownPelican_UpdateHidden(TownPelican *pelican)
{
    NearSpot *spot = tpel_near_spot();
    if (NearSpot_Found(spot)) {
        Vec3 *position = tpel_position(pelican);
        NearSpot_ToPosition(spot, position);
        *(Vec3 *) (void *) tpel_part(pelican, TPEL_LAST_POSITION) = *position;
        *tpel_part(pelican, TPEL_SHOWN) = 1;
        TownPelican_SetState(pelican, TOWN_PELICAN_REST);
    }
    return 1;
}
CLEAN_AS(func_ov075_022793e4, TownPelican_UpdateHidden)

/* func_ov075_02279438 (state 4's entry): he is not shown. 1. */
int TownPelican_EnterHidden(u8 *pelican)
{
    pelican[TPEL_SHOWN] = 0;
    return 1;
}
CLEAN_AS(func_ov075_02279438, TownPelican_EnterHidden)

/* func_ov075_02279448 (state 0's update): nothing. 1. */
int TownPelican_UpdateRest(void)
{
    return 1;
}
CLEAN_AS(func_ov075_02279448, TownPelican_UpdateRest)

/* func_ov075_0227944c (state 0's entry): his look asked for nothing (kind 0), his animation
 * 0xef (priority 1, played once) and his standard animations' first set to it. 1. */
int TownPelican_EnterRest(TownPelican *pelican)
{
    tpel_look_at(pelican, SCENE_LOOK_NONE);
    SceneMotion_RequestAnimation(tpel_motion(pelican), 1, TPEL_REST_ANIMATION, 1, data_020c80f8, 0);
    SceneStandardAnims_SetFirst((SceneStandardAnims *) (void *) tpel_part(pelican, TPEL_STANDARD_ANIMS), TPEL_REST_ANIMATION);
    return 1;
}
CLEAN_AS(func_ov075_0227944c, TownPelican_EnterRest)

/* func_ov075_022794b8: state `state` taken when its entry function, if it has one, answers
 * nonzero.
 * REQUIRES: `state` is 0 to 5 (the table is not bounded). */
void TownPelican_SetState(TownPelican *pelican, int state)
{
    const TownPelicanStep *step = &data_ov075_02279b08[state];
    int taken = 1;
    if (step->enter.function != 0) {
        taken = MemberPointer_CallInt(&step->enter, pelican);
    }
    if (taken != 0) {
        pelican->state = state;
    }
}
CLEAN_AS(func_ov075_022794b8, TownPelican_SetState)

/* func_ov075_022794fc (vtable slot 0x68, each frame): his state's update when it has one, and
 * its answer; else 0.
 * REQUIRES: his state is 0 to 5. */
int TownPelican_Update(TownPelican *pelican)
{
    const TownPelicanStep *step = &data_ov075_02279b08[pelican->state];
    if (step->update.function == 0) {
        return 0;
    }
    return MemberPointer_CallInt(&step->update, pelican);
}
CLEAN_AS(func_ov075_022794fc, TownPelican_Update)

/* func_ov075_02279548 (vtable slot 0x70): his model's file name, "npc_sp/model/plb.nsbmd". */
int TownPelican_ModelName(void)
{
    return (int) (u32) (uintptr_t) data_ov075_02279900;
}
CLEAN_AS(func_ov075_02279548, TownPelican_ModelName)

/* func_ov075_02279550 (vtable slot 0x6c): his texture's file name,
 * "npc_sp/model/plb_tex.nsbtx". */
int TownPelican_TextureName(void)
{
    return (int) (u32) (uintptr_t) data_ov075_02279948;
}
CLEAN_AS(func_ov075_02279550, TownPelican_TextureName)

/* func_ov075_02279558 (vtable slot 0x0c, his leaving): unless the special character refuses,
 * the town's near spot is cleared, except when an event's announcement was entered
 * (EventAnnounce_Entered). Whether he left. */
int TownPelican_Leave(TownPelican *pelican)
{
    if (SpecialSceneObject_Leave(pelican) == 0) {
        return 0;
    }
    if (EventAnnounce_Entered() == 0) {
        NearSpot_Clear(tpel_near_spot());
    }
    return 1;
}
CLEAN_AS(func_ov075_02279558, TownPelican_Leave)

/* func_ov075_02279584 (vtable slot 0xa8): the speed scale of his animation player, main's
 * data_020c8120 as it is (the special character's own slot gives data_021c30ac). */
int TownPelican_AnimSpeed(void)
{
    return data_020c8120;
}
CLEAN_AS(func_ov075_02279584, TownPelican_AnimSpeed)

/* func_ov075_02279590 (vtable slot 0x00, his start): unless the special character refuses to
 * start, he rests (state 0) when the town's near spot was found, else is hidden (state 4), and
 * is held (flag 2 at 0x4e8). Whether he started. */
int TownPelican_Start(TownPelican *pelican)
{
    if (SpecialSceneObject_Start(pelican) == 0) {
        return 0;
    }
    if (NearSpot_Found(tpel_near_spot())) {
        TownPelican_SetState(pelican, TOWN_PELICAN_REST);
    } else {
        TownPelican_SetState(pelican, TOWN_PELICAN_HIDDEN);
    }
    *tpel_held_flags(pelican) |= TPEL_HELD;
    return 1;
}
CLEAN_AS(func_ov075_02279590, TownPelican_Start)

/* func_ov075_022795dc (vtable slot 0x04, his set-up): unless the special character refuses,
 * his talk scene becomes his scene and gets him as its owner. Whether he was set up. */
int TownPelican_Init(TownPelican *pelican)
{
    if (SpecialSceneObject_Init(pelican) == 0) {
        return 0;
    }
    SceneObject_SetScene(pelican->base, &pelican->talk.base);
    TownPelicanTalk_Begin(&pelican->talk, (int) (u32) (uintptr_t) pelican);
    return 1;
}
CLEAN_AS(func_ov075_022795dc, TownPelican_Init)

/* func_ov075_0227960c (the create function his record at 0x02279918 names): a zeroed block of
 * 0x71c bytes from the auxiliary heap, constructed: the scene object base, the class
 * 0x020d8c64's vtable and members in place order (no person yet, 0xfff1), the class
 * 0x020da088's vtable and heap link, then the class's vtable and its talk scene. Null when
 * there is no room. */
void *TownPelican_Create(void)
{
    TownPelican *pelican = (TownPelican *) Heap_AllocAuxZeroed(sizeof(TownPelican));
    if (pelican == NULL) {
        return NULL;
    }
    u8 *object = pelican->base;
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) tpel_part(pelican, TPEL_PERSON) = TPEL_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) tpel_part(pelican, TPEL_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) tpel_part(pelican, TPEL_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) tpel_part(pelican, TPEL_FACE));
    SpeakerAnim_Construct((SpeakerAnim *) (void *) tpel_part(pelican, TPEL_ANIM));
    SceneMover_Construct(tpel_mover(pelican));
    SceneProbe_Construct(tpel_part(pelican, TPEL_PROBE));
    SceneValue3aa_Clear((SceneValue3aa *) (void *) tpel_part(pelican, TPEL_VALUE_3AA));
    SceneLook_Construct(tpel_look(pelican));
    SceneTalkState_Construct((SceneTalkState *) (void *) tpel_part(pelican, TPEL_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) tpel_part(pelican, TPEL_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) tpel_part(pelican, TPEL_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) tpel_part(pelican, TPEL_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) tpel_part(pelican, TPEL_EMITTER));
    Footsteps_Construct(tpel_footsteps(pelican));
    SceneMotion_Construct(tpel_motion(pelican));
    SceneAction_Construct(tpel_action(pelican));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) tpel_part(pelican, TPEL_HEAP));
    *(const u8 **) (void *) object = data_ov075_022799fc;
    TownPelicanTalk_Construct(&pelican->talk);
    return pelican;
}
CLEAN_AS(func_ov075_0227960c, TownPelican_Create)
