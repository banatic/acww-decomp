/* The special character of "sp_npc_missing2" (missing_npc2.h). */
#include "missing_npc2.h"

#include "actor.h" /* Vec_YawTo */
#include "acre_tile.h"
#include "autoload_2/approach.h"
#include "autoload_2/fx_math.h"
#include "autoload_2/heap.h"
#include "autoload_2/process.h" /* MemberFn */
#include "clean.h"
#include "event_queue.h"
#include "footsteps.h"
#include "obj_020d9ff8.h"
#include "paired_town.h"
#include "player_record.h"
#include "player_records.h"
#include "pool_link.h"
#include "scene_action.h"
#include "scene_look.h"
#include "scene_motion_request.h"
#include "scene_mover.h"
#include "scene_object.h"
#include "scene_object_members.h"
#include "scene_probe.h"
#include "scene_query.h"
#include "scene_value_3aa.h"
#include "special_scene_object.h"
#include "talk_checks.h"
#include "town_tile.h"

static_assert(offsetof(MissingNpc2, position) == 0x5c && offsetof(MissingNpc2, angle) == 0x8e, "MissingNpc2");
static_assert(offsetof(MissingNpc2, walk_angle) == 0x94 && offsetof(MissingNpc2, speed) == 0x98, "MissingNpc2");
static_assert(offsetof(MissingNpc2, wander_count) == 0x651 && offsetof(MissingNpc2, state) == 0x654, "MissingNpc2");
static_assert(offsetof(MissingNpc2, talk) == 0x658 && sizeof(MissingNpc2) == 0x714, "MissingNpc2");

/* The members of the scene object, by place (scene_object.h). */
#define MISSING_NPC2_MOVER 0x350
#define MISSING_NPC2_PROBE 0x3a8
#define MISSING_NPC2_VALUE_3AA 0x3aa
#define MISSING_NPC2_LOOK 0x3b0
#define MISSING_NPC2_FOOTSTEPS 0x558
#define MISSING_NPC2_MOTION 0x564

/* The kinds of motion it asks for (scene_motion_kinds.h). */
#define MISSING_NPC2_STAND 0
#define MISSING_NPC2_WALK 1
#define MISSING_NPC2_WALK_2 2
#define MISSING_NPC2_TURN_THEN_WALK 4
#define MISSING_NPC2_LOOK_PLAYER 1 /* scene_look.h */
#define MISSING_NPC2_PLAYER_ACTOR 4

/* What the probe ahead finds (scene_probe.h): the first point blocked, the second, both. */
#define MISSING_NPC2_BLOCKED_FIRST 1
#define MISSING_NPC2_BLOCKED_SECOND 2
#define MISSING_NPC2_BLOCKED_BOTH 3

/* SceneValue3aa_Grade's answer that keeps it standing. */
#define MISSING_NPC2_GRADE_STAND 2

#define MISSING_NPC2_WALK_FRAMES 100
#define MISSING_NPC2_TURN_FRAMES 0x50
#define MISSING_NPC2_WANDER_TRIES 6
#define MISSING_NPC2_WANDER_RADIUS 0xc000

/* The camera's box (MissingNpc2_InCameraBox): half its width, and how far it reaches behind
 * and ahead of the camera's point along z. */
#define MISSING_NPC2_BOX_HALF_WIDTH 0x10000
#define MISSING_NPC2_BOX_BEHIND 0x1a000
#define MISSING_NPC2_BOX_AHEAD 0xa000

/* The class's vtable. */
extern const u8 data_020e7ea4[];
/* The word its motion requests carry, the range of its looks and the point they are given. */
extern u16 data_020c80f8;
extern fx32 data_020c814c;
extern Vec3 data_021fbee8;
/* The game's random numbers. */
extern Random data_021cb5a0;
/* The camera, while it exists, and its point. */
extern int data_021c67a4;
extern const Vec3 data_021c67d0;
/* The offsets of the points it steps aside to: x +0x800 and x -0x800, 0x1000 ahead. */
extern const Vec3 data_021fbcc0;
extern const Vec3 data_021fbccc;
/* Sines and cosines by the angle's top 12 bits (NitroSDK). */
extern const s16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* A random number below `range` (Random_Below on the game's generator). */
extern int func_020644cc(int range);

static u8 *missing_npc2_at(MissingNpc2 *self, u32 offset)
{
    return (u8 *) self + offset;
}

static SceneMotion *missing_npc2_motion(MissingNpc2 *self)
{
    return (SceneMotion *) (void *) missing_npc2_at(self, MISSING_NPC2_MOTION);
}

static SceneMover *missing_npc2_mover(MissingNpc2 *self)
{
    return (SceneMover *) (void *) missing_npc2_at(self, MISSING_NPC2_MOVER);
}

static Footsteps *missing_npc2_footsteps(MissingNpc2 *self)
{
    return (Footsteps *) (void *) missing_npc2_at(self, MISSING_NPC2_FOOTSTEPS);
}

static void missing_npc2_move(MissingNpc2 *self, int kind, int x, int z, int angle)
{
    SceneMotion_Request(missing_npc2_motion(self), kind, 1, x, z, 0, (s16) angle, 0, 0, data_020c80f8, 0);
}

static void missing_npc2_stand(MissingNpc2 *self)
{
    missing_npc2_move(self, MISSING_NPC2_STAND, 0, 0, 0);
}

static int missing_npc2_add(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

/* Whether `point` is less than a quarter turn from where it faces. */
static int missing_npc2_ahead(MissingNpc2 *self, const Vec3 *point)
{
    int angle = Vec_YawTo(&self->position, point);
    return SceneObject_IsWithinQuarterTurn((s16) (angle - self->angle));
}

/* func_020c2c34 (slot 0x40): the destructor: its talk, then the base class's. */
MissingNpc2 *MissingNpc2_Destruct(MissingNpc2 *self)
{
    *(const u8 **) (void *) self = data_020e7ea4;
    MissingNpc2Talk_Destruct((MissingNpc2Talk *) (void *) self->talk);
    SpecialSceneObject_DestructBody(self);
    return self;
}
CLEAN_AS(func_020c2c34, MissingNpc2_Destruct)

/* func_020c2c5c (slot 0x44): destructed, then freed to the auxiliary heap. */
MissingNpc2 *MissingNpc2_DestructDelete(MissingNpc2 *self)
{
    *(const u8 **) (void *) self = data_020e7ea4;
    MissingNpc2Talk_Destruct((MissingNpc2Talk *) (void *) self->talk);
    SpecialSceneObject_DestructBody(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_020c2c5c, MissingNpc2_DestructDelete)

/* func_020c2c88: once the camera's box holds it again, MISSING_NPC2_WANDER. Always 1. */
int MissingNpc2_UpdateOutOfView(MissingNpc2 *self)
{
    if (MissingNpc2_InView(self)) {
        MissingNpc2_SetState(self, MISSING_NPC2_WANDER);
    }
    return 1;
}
CLEAN_AS(func_020c2c88, MissingNpc2_UpdateOutOfView)

/* func_020c2ca4: standing, its wander over, its footsteps off. Always 1. */
int MissingNpc2_EnterOutOfView(MissingNpc2 *self)
{
    missing_npc2_stand(self);
    self->wander_count = 0;
    Footsteps_Disable(missing_npc2_footsteps(self));
    return 1;
}
CLEAN_AS(func_020c2ca4, MissingNpc2_EnterOutOfView)

/* func_020c2cf4: a frame of wandering (missing_npc2.h). The wander's frames count down. Out of
 * the camera's box, it goes out of view when moving. In view, unless it steps around what
 * blocks the way (MissingNpc2_AvoidAhead):
 * - with its motion done: it stands while its value at 0x3aa grades 2; else one frame in eight
 *   it draws a point to wander to (standing when none is clear): ahead of it within a quarter
 *   turn, it walks there (the second way one time in four) for 100 frames unless it already
 *   walks that way; behind, it turns and walks there for 80 frames unless it already does;
 *   the other frames it stands;
 * - while moving and walking (kinds 1, 2 and 4): it stands when the wander's frames are over
 *   or the mover's end point is more than a quarter turn from where it faces.
 * Always 0. */
int MissingNpc2_UpdateWander(MissingNpc2 *self)
{
    SceneMotion *motion = missing_npc2_motion(self);
    int in_view = MissingNpc2_InView(self);
    Countdown_Tick8(&self->wander_count);
    if (!in_view) {
        if (self->speed != 0) {
            MissingNpc2_SetState(self, MISSING_NPC2_OUT_OF_VIEW);
        }
        return 0;
    }
    if (MissingNpc2_AvoidAhead(self)) {
        return 0;
    }

    if (SceneMotion_IsDone(motion)) {
        if (SceneValue3aa_Grade((SceneValue3aa *) (void *) missing_npc2_at(self, MISSING_NPC2_VALUE_3AA)) ==
            MISSING_NPC2_GRADE_STAND) {
            missing_npc2_stand(self);
            return 0;
        }
        if ((Random_Next(&data_021cb5a0) & 7) != 0) {
            missing_npc2_stand(self);
            return 0;
        }
        Vec3 point = data_021fbee8;
        if (!MissingNpc2_PickWanderPoint(self, &point.x, &point.z)) {
            missing_npc2_stand(self);
            return 0;
        }
        int angle = Vec_YawTo(&self->position, &point);
        if (SceneObject_IsWithinQuarterTurn((s16) (angle - self->angle))) {
            int kind = MISSING_NPC2_WALK;
            if (func_020644cc(4) == 0) {
                kind = MISSING_NPC2_WALK_2;
            }
            if (kind != SceneMotion_Kind(motion)) {
                missing_npc2_move(self, kind, point.x, point.z, 0);
                self->wander_count = MISSING_NPC2_WALK_FRAMES;
            }
        } else if (SceneMotion_Kind(motion) != MISSING_NPC2_TURN_THEN_WALK) {
            missing_npc2_move(self, MISSING_NPC2_TURN_THEN_WALK, point.x, point.z, angle);
            self->wander_count = MISSING_NPC2_TURN_FRAMES;
        }
        return 0;
    }

    if (self->speed != 0 &&
        (SceneMotion_Kind(motion) == MISSING_NPC2_WALK || SceneMotion_Kind(motion) == MISSING_NPC2_WALK_2 ||
         SceneMotion_Kind(motion) == MISSING_NPC2_TURN_THEN_WALK)) {
        if (self->wander_count == 0) {
            missing_npc2_stand(self);
        } else {
            Vec3 end = *SceneMover_End(missing_npc2_mover(self));
            if (!missing_npc2_ahead(self, &end)) {
                missing_npc2_stand(self);
            }
        }
    }
    return 0;
}
CLEAN_AS(func_020c2cf4, MissingNpc2_UpdateWander)

/* func_020c2f3c: while it moves, whether it stepped around what blocks the way ahead
 * (MissingNpc2_StepAside). */
int MissingNpc2_AvoidAhead(MissingNpc2 *self)
{
    return self->speed != 0 && MissingNpc2_StepAside(self) != 0;
}
CLEAN_AS(func_020c2f3c, MissingNpc2_AvoidAhead)

/* func_020c2f60: before it reaches the mover's start point, what the probe ahead finds: both
 * points blocked, it stands; one blocked, its end point moves to the clear point on the other
 * side (MissingNpc2_SidePoint), or it stands without one; whether it did either. Once it
 * reaches it, the end point is brought back to the start when they differ (0). */
int MissingNpc2_StepAside(MissingNpc2 *self)
{
    SceneMover *mover = missing_npc2_mover(self);
    int blocked = SceneProbe_Bits(missing_npc2_at(self, MISSING_NPC2_PROBE));
    if (SceneMover_Reached(mover, (u8 *) self, 1)) {
        if (SceneMover_PointsDiffer(mover)) {
            SceneMover_EndAtStart(mover);
        }
        return 0;
    }

    Vec3 point;
    switch (blocked) {
        case MISSING_NPC2_BLOCKED_BOTH:
            missing_npc2_stand(self);
            return 1;
        case MISSING_NPC2_BLOCKED_FIRST:
            if (MissingNpc2_SidePoint(self, &point, &data_021fbccc)) {
                SceneMover_SetEnd(mover, &point);
            } else {
                missing_npc2_stand(self);
            }
            return 1;
        case MISSING_NPC2_BLOCKED_SECOND:
            if (MissingNpc2_SidePoint(self, &point, &data_021fbcc0)) {
                SceneMover_SetEnd(mover, &point);
            } else {
                missing_npc2_stand(self);
            }
            return 1;
        default:
            return 0;
    }
}
CLEAN_AS(func_020c2f60, MissingNpc2_StepAside)

/* func_020c3060: the point `offset` from its position, turned by its walking angle, into
 * `out` unless that point is blocked; whether it was given. */
int MissingNpc2_SidePoint(MissingNpc2 *self, Vec3 *out, const Vec3 *offset)
{
    Vec3 point;
    SceneProbe_PointAt(&point, &self->position, offset, self->walk_angle);
    if (SceneProbe_IsBlocked(&point) == 1) {
        return 0;
    }
    *out = point;
    return 1;
}
CLEAN_AS(func_020c3060, MissingNpc2_SidePoint)

/* func_020c309c: up to six tries at a point 0xc000 away at a random angle, taken to its tile's
 * centre; the first clear one's x and z given (1), else 0.
 * QUIRK: each try's height is the one the tile centre of the try before gave. */
int MissingNpc2_PickWanderPoint(MissingNpc2 *self, fx32 *x, fx32 *z)
{
    Vec3 point = {0, 0, 0};
    for (int i = 0; i < MISSING_NPC2_WANDER_TRIES; i++) {
        u32 index = (Random_Next(&data_021cb5a0) & 0xffff) >> 4;
        point.x = missing_npc2_add(FX_MulFunc(MISSING_NPC2_WANDER_RADIUS, FX_SinCosTable_[index * 2]), self->position.x);
        point.z = missing_npc2_add(FX_MulFunc(MISSING_NPC2_WANDER_RADIUS, FX_SinCosTable_[index * 2 + 1]), self->position.z);
        AcreTile_SnapToTileCentre(&point, &point);
        if (TownTile_IsClearAt(&point, NULL)) {
            *x = point.x;
            *z = point.z;
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_020c309c, MissingNpc2_PickWanderPoint)

/* func_020c312c: whether the camera exists and its box holds it. */
int MissingNpc2_InView(MissingNpc2 *self)
{
    if (data_021c67a4 == 0) {
        return 0;
    }
    Vec3 camera = data_021c67d0;
    return MissingNpc2_InCameraBox((int) (uintptr_t) self, &camera, &self->position);
}
CLEAN_AS(func_020c312c, MissingNpc2_InView)

/* func_020c3164: whether `point` is within 0x10000 of `camera` along x, and between 0x1a000
 * behind and 0xa000 ahead of it along z (all bounds excluded). */
int MissingNpc2_InCameraBox(int unused, const Vec3 *camera, const Vec3 *point)
{
    (void) unused;
    return point->x > missing_npc2_add(camera->x, -MISSING_NPC2_BOX_HALF_WIDTH) &&
           point->x < missing_npc2_add(camera->x, MISSING_NPC2_BOX_HALF_WIDTH) &&
           point->z > missing_npc2_add(camera->z, -MISSING_NPC2_BOX_BEHIND) &&
           point->z < missing_npc2_add(camera->z, MISSING_NPC2_BOX_AHEAD);
}
CLEAN_AS(func_020c3164, MissingNpc2_InCameraBox)

/* func_020c31bc: the wander's frames cleared, standing, its footsteps on (enabled twice), and
 * a look at the player. Always 1. */
int MissingNpc2_EnterWander(MissingNpc2 *self)
{
    self->wander_count = 0;
    missing_npc2_stand(self);
    Footsteps_Enable(missing_npc2_footsteps(self));
    Footsteps_Enable(missing_npc2_footsteps(self));
    SceneLook_Request((SceneLook *) (void *) missing_npc2_at(self, MISSING_NPC2_LOOK), MISSING_NPC2_LOOK_PLAYER, 0, 0,
                      &data_021fbee8, MISSING_NPC2_PLAYER_ACTOR, data_020c814c, 1);
    return 1;
}
CLEAN_AS(func_020c31bc, MissingNpc2_EnterWander)

/* func_020c323c (the talk's slot 0x18): no answer is handled. */
void MissingNpc2Talk_OnAnswer(void) {}
CLEAN_AS(func_020c323c, MissingNpc2Talk_OnAnswer)

/* ---- Its talk scene, its other states and the object */

/* The members of the scene object used below, by place (scene_object.h). */
#define MISSING_NPC2_PERSON 0x0ea /* u16: the person code */
#define MISSING_NPC2_MODEL 0x0ec
#define MISSING_NPC2_STANDARD_ANIMS 0x2a0
#define MISSING_NPC2_FACE 0x2ac
#define MISSING_NPC2_ANIM 0x334
#define MISSING_NPC2_TALK_STATE 0x418
#define MISSING_NPC2_EFFECTS 0x420
#define MISSING_NPC2_COLLIDER 0x49c
#define MISSING_NPC2_CARRIER 0x4cc
#define MISSING_NPC2_SOLID 0x510 /* u8: it collides and moves with its carrier */
#define MISSING_NPC2_EMITTER 0x514
#define MISSING_NPC2_LOCAL 0x563 /* u8: not shared with a session */
#define MISSING_NPC2_ACTION 0x618
#define MISSING_NPC2_HEAP 0x640

#define MISSING_NPC2_SIZE 0x714
#define MISSING_NPC2_NO_PERSON 0xfff1

/* The scenes it acts in (SceneQuery_Current). */
#define MISSING_NPC2_SCENE_TOWN 0x00
#define MISSING_NPC2_SCENE_2F 0x2f

/* The motion kind of a turn (scene_motion_kinds.h), the turn's way (scene_mover.h) and the
 * look ahead (scene_look.h). */
#define MISSING_NPC2_TURN_KIND 3
#define MISSING_NPC2_TURN_WAY 2
#define MISSING_NPC2_LOOK_AHEAD 0

/* The flags of the player's record (player_record.h) and the daily bit of talk_checks.h its talk
 * reads and sets. */
#define MISSING_NPC2_FLAG_33 0x33
#define MISSING_NPC2_FLAG_39 0x39 /* set at the end of the walk of scene 0x2f (missing_npc1.c) */
#define MISSING_NPC2_DAILY_BIT 0x2a

/* The talk scene's vtable slot that resets it (SceneBase_Reset). */
#define MISSING_NPC2_TALK_SLOT_RESET 2

/* The codes of its vtable slot 0x4c (scene_object_base.h). */
#define MISSING_NPC2_EVENT_0 0
#define MISSING_NPC2_EVENT_1 1
#define MISSING_NPC2_EVENT_ACT_STARTS 3
#define MISSING_NPC2_EVENT_ACT_ENDED 8

/* The vtables of its talk's class and of its base classes. */
extern const u8 data_020e7e14[];
extern const u8 data_020d8c64[];
extern const u8 data_020da088[];
/* The file names its slots 0x70 and 0x6c give: "npc_sp/model/mum.nsbmd" and
 * "npc_sp/model/mum_tex.nsbtx". */
extern const char data_020e7dc0[];
extern const char data_020e7df0[];
/* The address of "sp_npc_missing2", the archive of its lines. */
extern const char *const data_020e7d0c;
/* The speed scale of its animation player in the town. */
extern s32 data_020c8120;
/* The states' entries and updates (filled at start-up from data_020e7d10 to data_020e7da8). */
typedef struct MissingNpc2StateFns {
    MemberFn enter;
    MemberFn update;
} MissingNpc2StateFns;
extern MissingNpc2StateFns data_021fbcd8[MISSING_NPC2_STATES];
/* The one that exists, or null. */
extern MissingNpc2 *data_021fbca0;

static MissingNpc2Talk *missing_npc2_talk(MissingNpc2 *self)
{
    return (MissingNpc2Talk *) (void *) self->talk;
}

static SceneAction *missing_npc2_action(MissingNpc2 *self)
{
    return (SceneAction *) (void *) missing_npc2_at(self, MISSING_NPC2_ACTION);
}

/* A motion of `kind` with the priority and points given (scene_motion_request.h). */
static void missing_npc2_move_at(MissingNpc2 *self, int kind, int priority, int x, int z)
{
    SceneMotion_Request(missing_npc2_motion(self), kind, priority, x, z, 0, 0, 0, 0, data_020c80f8, 0);
}

/* When its motion is done and still of `kind`, standing with priority 2. */
static void missing_npc2_stand_after(MissingNpc2 *self, int kind)
{
    SceneMotion *motion = missing_npc2_motion(self);
    if (SceneMotion_IsDone(motion) && SceneMotion_Kind(motion) == kind) {
        missing_npc2_move_at(self, MISSING_NPC2_STAND, 2, 0, 0);
    }
}

static void missing_npc2_look_at(MissingNpc2 *self, u8 kind)
{
    SceneLook_Request((SceneLook *) (void *) missing_npc2_at(self, MISSING_NPC2_LOOK), kind, 0, 0, &data_021fbee8,
                      MISSING_NPC2_PLAYER_ACTOR, data_020c814c, 1);
}

/* The member function `fn` called on the object, as a C++ pointer to member function: the
 * object moved by half the adjustment and, for a virtual one, the entry `ptr` bytes into its
 * vtable. */
static int missing_npc2_call(const MemberFn *fn, MissingNpc2 *self)
{
    typedef int (*MissingNpc2Step)(void *self);
    uintptr_t object = (uintptr_t) self + (uintptr_t) (intptr_t) ((fn->adj - (fn->adj & 1)) / 2);
    uintptr_t target = fn->ptr;
    if ((fn->adj & 1) != 0) {
        uintptr_t vtable = *(const u32 *) object;
        target = *(const u32 *) (vtable + fn->ptr);
    }
    return ((MissingNpc2Step) target)((void *) object);
}

/* The talk scene's vtable slot `slot` called with no argument. */
static void missing_npc2_talk_slot(MissingNpc2Talk *talk, int slot)
{
    const u32 *vtable = (const u32 *) (const void *) talk->scene.vtable;
    ((void (*)(MissingNpc2Talk *))(uintptr_t) vtable[slot])(talk);
}

/* func_020c3240 (the talk's slot 0x14): no message is handled. */
void MissingNpc2Talk_OnMessage(void) {}
CLEAN_AS(func_020c3240, MissingNpc2Talk_OnMessage)

/* func_020c3244 (the talk's slot 0x10): the name of the current player's paired town put into
 * the talk's text slots 0 and 1. */
void MissingNpc2Talk_PutTownNames(MissingNpc2Talk *talk)
{
    u8 *pairing = PlayerRecord_Field242C(PlayerRecords_Current());
    SceneBase_PutNameAt2(&talk->scene, (unsigned int) (uintptr_t) PairedTown_Town(pairing), 0);
    SceneBase_PutNameAt2(&talk->scene, (unsigned int) (uintptr_t) PairedTown_Town(pairing), 1);
}
CLEAN_AS(func_020c3244, MissingNpc2Talk_PutTownNames)

/* func_020c327c (the talk's slot 0x78): the topic chosen from the current player's record (the
 * first talk until flag 0x33 is set, or "again" once flag 0x39 is; then "today" until the daily
 * bit 0x2a is set, else "later"), and the line to say for it with the archive's name. The
 * first two topics set flag 0x33; "today" sets the daily bit after drawing its line. */
void MissingNpc2Talk_Line(MissingNpc2Talk *talk, MissingNpc2Line *line)
{
    u8 *record = PlayerRecords_Current();
    line->name = (u32) (uintptr_t) data_020e7d0c;
    if (PlayerRecord_TestFlag(record, MISSING_NPC2_FLAG_33) == 0) {
        if (PlayerRecord_TestFlag(record, MISSING_NPC2_FLAG_39) == 0) {
            MissingNpc2Talk_SetTopic(talk, MISSING_NPC2_TOPIC_FIRST);
        } else {
            MissingNpc2Talk_SetTopic(talk, MISSING_NPC2_TOPIC_AGAIN);
        }
    } else if (TalkChecks_TestSetDailyBit(MISSING_NPC2_DAILY_BIT, 0) == 0) {
        MissingNpc2Talk_SetTopic(talk, MISSING_NPC2_TOPIC_TODAY);
    } else {
        MissingNpc2Talk_SetTopic(talk, MISSING_NPC2_TOPIC_LATER);
    }

    switch (MissingNpc2Talk_Topic(talk)) {
        case MISSING_NPC2_TOPIC_FIRST:
            PlayerRecord_SetFlag(record, MISSING_NPC2_FLAG_33);
            line->message = 0;
            break;
        case MISSING_NPC2_TOPIC_AGAIN:
            PlayerRecord_SetFlag(record, MISSING_NPC2_FLAG_33);
            line->message = (u8) (func_020644cc(3) + 1);
            break;
        case MISSING_NPC2_TOPIC_TODAY:
            line->message = (u8) (func_020644cc(3) + 4);
            TalkChecks_TestSetDailyBit(MISSING_NPC2_DAILY_BIT, 1);
            break;
        case MISSING_NPC2_TOPIC_LATER:
            line->message = (u8) (func_020644cc(3) + 7);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020c327c, MissingNpc2Talk_Line)

/* func_020c3340 */
u32 MissingNpc2Talk_Topic(MissingNpc2Talk *talk)
{
    return talk->topic;
}
CLEAN_AS(func_020c3340, MissingNpc2Talk_Topic)

/* func_020c3348 */
void MissingNpc2Talk_SetTopic(MissingNpc2Talk *talk, u32 topic)
{
    talk->topic = topic;
}
CLEAN_AS(func_020c3348, MissingNpc2Talk_SetTopic)

/* func_020c3350: the scene reset (its vtable slot 2), then given its owner. */
void MissingNpc2Talk_SetOwner(MissingNpc2Talk *talk, MissingNpc2 *owner)
{
    missing_npc2_talk_slot(talk, MISSING_NPC2_TALK_SLOT_RESET);
    talk->owner = owner;
}
CLEAN_AS(func_020c3350, MissingNpc2Talk_SetOwner)

/* func_020c336c (the talk's slot 0x04): destructed, then freed (Heap_OperatorDeleteB). */
MissingNpc2Talk *MissingNpc2Talk_DestructDelete(MissingNpc2Talk *talk)
{
    *(const u8 **) (void *) talk = data_020e7e14;
    Obj020d9ff8_DestructBody(talk);
    Heap_OperatorDeleteB(talk);
    return talk;
}
CLEAN_AS(func_020c336c, MissingNpc2Talk_DestructDelete)

/* func_020c338c (the talk's slot 0x00): the destructor. */
MissingNpc2Talk *MissingNpc2Talk_Destruct(MissingNpc2Talk *talk)
{
    *(const u8 **) (void *) talk = data_020e7e14;
    Obj020d9ff8_DestructBody(talk);
    return talk;
}
CLEAN_AS(func_020c338c, MissingNpc2Talk_Destruct)

/* func_020c33a4: the constructor: a scene of class 0x020d9ff8 given the class's vtable. */
MissingNpc2Talk *MissingNpc2Talk_Construct(MissingNpc2Talk *talk)
{
    Obj020d9ff8_Construct(talk);
    *(const u8 **) (void *) talk = data_020e7e14;
    return talk;
}
CLEAN_AS(func_020c33a4, MissingNpc2Talk_Construct)

/* func_020c33bc: once the walk after its turn (kind 1) is done, standing. Always 1. */
int MissingNpc2_UpdateScene2FExit(MissingNpc2 *self)
{
    missing_npc2_stand_after(self, MISSING_NPC2_WALK);
    return 1;
}
CLEAN_AS(func_020c33bc, MissingNpc2_UpdateScene2FExit)

/* func_020c340c: a turn, then a walk (kind 4, priority 2) to (0x10000, 0x1d000). Always 1. */
int MissingNpc2_EnterScene2FExit(MissingNpc2 *self)
{
    missing_npc2_move_at(self, MISSING_NPC2_TURN_THEN_WALK, 2, 0x10000, 0x1d000);
    return 1;
}
CLEAN_AS(func_020c340c, MissingNpc2_EnterScene2FExit)

/* func_020c344c: once its turn is done, standing. Always 1. */
int MissingNpc2_UpdateTurn(MissingNpc2 *self)
{
    missing_npc2_stand_after(self, MISSING_NPC2_TURN_KIND);
    return 1;
}
CLEAN_AS(func_020c344c, MissingNpc2_UpdateTurn)

/* func_020c349c: a turn (priority 2, to angle 0), the mover's turn way 2. Always 1. */
int MissingNpc2_EnterTurn(MissingNpc2 *self)
{
    missing_npc2_move_at(self, MISSING_NPC2_TURN_KIND, 2, 0, 0);
    SceneMover_SetTurnWay(missing_npc2_mover(self), MISSING_NPC2_TURN_WAY);
    return 1;
}
CLEAN_AS(func_020c349c, MissingNpc2_EnterTurn)

/* func_020c34e4: once the walk (kind 2) is done, standing. Always 1. */
int MissingNpc2_UpdateScene2FWalk(MissingNpc2 *self)
{
    missing_npc2_stand_after(self, MISSING_NPC2_WALK_2);
    return 1;
}
CLEAN_AS(func_020c34e4, MissingNpc2_UpdateScene2FWalk)

/* func_020c3534: a walk (kind 2, priority 2) to (0xf400, 0x14600). Always 1. */
int MissingNpc2_EnterScene2FWalk(MissingNpc2 *self)
{
    missing_npc2_move_at(self, MISSING_NPC2_WALK_2, 2, 0xf400, 0x14600);
    return 1;
}
CLEAN_AS(func_020c3534, MissingNpc2_EnterScene2FWalk)

/* func_020c3574: nothing. */
int MissingNpc2_UpdateSpeaker(void)
{
    return 1;
}
CLEAN_AS(func_020c3574, MissingNpc2_UpdateSpeaker)

/* func_020c3578: standing, as MISSING_NPC2_IDLE begins.
 * QUIRK: declared without a result although the state machine reads one; the ROM's code leaves
 * MissingNpc2_EnterIdle's 1 in place, so the state is always taken. */
void MissingNpc2_EnterSpeaker(MissingNpc2 *self)
{
    MissingNpc2_EnterIdle(self);
}
CLEAN_AS(func_020c3578, MissingNpc2_EnterSpeaker)

/* func_020c3580 (slot 0x90): told that a talk it was in ended: a look at the player, and
 * MISSING_NPC2_IDLE. */
void MissingNpc2_OnTalkEnd(MissingNpc2 *self)
{
    missing_npc2_look_at(self, MISSING_NPC2_LOOK_PLAYER);
    MissingNpc2_SetState(self, MISSING_NPC2_IDLE);
}
CLEAN_AS(func_020c3580, MissingNpc2_OnTalkEnd)

/* func_020c35c0 (slot 0x8c): told it joined a talk as a speaker: MISSING_NPC2_SPEAKER. */
void MissingNpc2_OnSpeakerJoined(MissingNpc2 *self)
{
    MissingNpc2_SetState(self, MISSING_NPC2_SPEAKER);
}
CLEAN_AS(func_020c35c0, MissingNpc2_OnSpeakerJoined)

/* func_020c35cc: nothing. */
int MissingNpc2_UpdateTalked(void)
{
    return 1;
}
CLEAN_AS(func_020c35cc, MissingNpc2_UpdateTalked)

/* func_020c35d0: nothing. */
int MissingNpc2_EnterTalked(void)
{
    return 1;
}
CLEAN_AS(func_020c35d0, MissingNpc2_EnterTalked)

/* func_020c35d4: nothing. */
int MissingNpc2_UpdateTurnAndTalk(void)
{
    return 1;
}
CLEAN_AS(func_020c35d4, MissingNpc2_UpdateTurnAndTalk)

/* func_020c35d8: the action that turns it to the object its talk names (its motion argument;
 * angle 0 without one) and talks. Always 1. */
int MissingNpc2_EnterTurnAndTalk(MissingNpc2 *self)
{
    int target = SceneBase_MotionArg(&missing_npc2_talk(self)->scene);
    int angle = 0;
    if (target != 0) {
        angle = SceneObject_YawTo((u8 *) self, (u8 *) (uintptr_t) target);
    }
    SceneAction_RequestTurnAndTalk(missing_npc2_action(self), 0, angle, 0);
    return 1;
}
CLEAN_AS(func_020c35d8, MissingNpc2_EnterTurnAndTalk)

/* func_020c3610: once its action ends, its event finished (EventQueue_FinishObjectEvent) and
 * MISSING_NPC2_TALKED. Always 1. */
int MissingNpc2_UpdateTalk(MissingNpc2 *self)
{
    if (!SceneAction_IsBusy(missing_npc2_action(self))) {
        EventQueue_FinishObjectEvent(self);
        MissingNpc2_SetState(self, MISSING_NPC2_TALKED);
    }
    return 1;
}
CLEAN_AS(func_020c3610, MissingNpc2_UpdateTalk)

/* func_020c363c: nothing. */
int MissingNpc2_EnterTalk(void)
{
    return 1;
}
CLEAN_AS(func_020c363c, MissingNpc2_EnterTalk)

/* func_020c3640: in the town, MISSING_NPC2_WANDER. Always 1. */
int MissingNpc2_UpdateIdle(MissingNpc2 *self)
{
    if (SceneQuery_Current() == MISSING_NPC2_SCENE_TOWN) {
        MissingNpc2_SetState(self, MISSING_NPC2_WANDER);
    }
    return 1;
}
CLEAN_AS(func_020c3640, MissingNpc2_UpdateIdle)

/* func_020c365c: standing. Always 1. */
int MissingNpc2_EnterIdle(MissingNpc2 *self)
{
    missing_npc2_stand(self);
    return 1;
}
CLEAN_AS(func_020c365c, MissingNpc2_EnterIdle)

/* func_020c3690: the state's entry run (when it has one); unless it answers 0 the state is
 * taken.
 * REQUIRES: `state` is one of the ten. */
void MissingNpc2_SetState(MissingNpc2 *self, int state)
{
    const MemberFn *enter = &data_021fbcd8[state].enter;
    int taken = 1;
    if (enter->ptr != 0) {
        taken = missing_npc2_call(enter, self);
    }
    if (taken) {
        self->state = state;
    }
}
CLEAN_AS(func_020c3690, MissingNpc2_SetState)

/* func_020c36d4 (slot 0x4c): told of an event. Code 0: MISSING_NPC2_TALK. Codes 1 and 3 (the
 * act starts): its talk is reset and given the player's object as its motion argument, then
 * MISSING_NPC2_TALK after code 1 and MISSING_NPC2_TURN_AND_TALK after code 3. Code 8 (its act
 * ended): MISSING_NPC2_IDLE. */
void MissingNpc2_OnEvent(MissingNpc2 *self, int code)
{
    MissingNpc2Talk *talk = missing_npc2_talk(self);
    switch (code) {
        case MISSING_NPC2_EVENT_1:
            missing_npc2_talk_slot(talk, MISSING_NPC2_TALK_SLOT_RESET);
            SceneBase_SetMotionArg(&talk->scene, SceneObject_ActorObject((u8 *) self, MISSING_NPC2_PLAYER_ACTOR));
            MissingNpc2_SetState(self, MISSING_NPC2_TALK);
            break;
        case MISSING_NPC2_EVENT_0:
            MissingNpc2_SetState(self, MISSING_NPC2_TALK);
            break;
        case MISSING_NPC2_EVENT_ACT_STARTS:
            missing_npc2_talk_slot(talk, MISSING_NPC2_TALK_SLOT_RESET);
            SceneBase_SetMotionArg(&talk->scene, SceneObject_ActorObject((u8 *) self, MISSING_NPC2_PLAYER_ACTOR));
            MissingNpc2_SetState(self, MISSING_NPC2_TURN_AND_TALK);
            break;
        case MISSING_NPC2_EVENT_ACT_ENDED:
            MissingNpc2_SetState(self, MISSING_NPC2_IDLE);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_020c36d4, MissingNpc2_OnEvent)

/* func_020c3760 (slot 0x48): the player may act on it while no action of its runs. */
int MissingNpc2_MayAct(MissingNpc2 *self)
{
    return !SceneAction_IsBusy(missing_npc2_action(self));
}
CLEAN_AS(func_020c3760, MissingNpc2_MayAct)

/* func_020c3780 (slot 0x68): the state's update run (when it has one); its answer, else 0. */
int MissingNpc2_Update(MissingNpc2 *self)
{
    const MemberFn *update = &data_021fbcd8[self->state].update;
    if (update->ptr == 0) {
        return 0;
    }
    return missing_npc2_call(update, self);
}
CLEAN_AS(func_020c3780, MissingNpc2_Update)

/* func_020c37cc (slot 0x70): the model's file name. */
int MissingNpc2_ModelName(void)
{
    return (int) (uintptr_t) data_020e7dc0;
}
CLEAN_AS(func_020c37cc, MissingNpc2_ModelName)

/* func_020c37d4 (slot 0x6c): the texture's file name. */
int MissingNpc2_TextureName(void)
{
    return (int) (uintptr_t) data_020e7df0;
}
CLEAN_AS(func_020c37d4, MissingNpc2_TextureName)

/* func_020c37dc: the one that exists (if any) set to MISSING_NPC2_SCENE_2F_EXIT. */
void MissingNpc2_StartScene2FExit(void)
{
    if (data_021fbca0 != NULL) {
        MissingNpc2_SetState(data_021fbca0, MISSING_NPC2_SCENE_2F_EXIT);
    }
}
CLEAN_AS(func_020c37dc, MissingNpc2_StartScene2FExit)

/* func_020c37f8: the one that exists (if any) set to MISSING_NPC2_SCENE_2F_WALK. */
void MissingNpc2_StartScene2FWalk(void)
{
    if (data_021fbca0 != NULL) {
        MissingNpc2_SetState(data_021fbca0, MISSING_NPC2_SCENE_2F_WALK);
    }
}
CLEAN_AS(func_020c37f8, MissingNpc2_StartScene2FWalk)

/* func_020c3814 (slot 0x0c): unless the base class refuses to leave, it is no longer the one
 * that exists. Whether it left. */
int MissingNpc2_Leave(MissingNpc2 *self)
{
    if (SpecialSceneObject_Leave(self) == 0) {
        return 0;
    }
    data_021fbca0 = NULL;
    return 1;
}
CLEAN_AS(func_020c3814, MissingNpc2_Leave)

/* func_020c3838 (slot 0x00): unless the base class refuses to start, MISSING_NPC2_IDLE; in
 * scene 0x2f it is not solid, looks ahead, and stands at (0x10000, 0x16800). Whether it
 * started. (The current player's record is asked for and not used.) */
int MissingNpc2_Start(MissingNpc2 *self)
{
    if (SpecialSceneObject_Start(self) == 0) {
        return 0;
    }
    PlayerRecords_Current();
    MissingNpc2_SetState(self, MISSING_NPC2_IDLE);
    if (SceneQuery_Current() == MISSING_NPC2_SCENE_2F) {
        *missing_npc2_at(self, MISSING_NPC2_SOLID) = 0;
        missing_npc2_look_at(self, MISSING_NPC2_LOOK_AHEAD);
        self->position.x = 0x10000;
        self->position.z = 0x16800;
    }
    return 1;
}
CLEAN_AS(func_020c3838, MissingNpc2_Start)

/* func_020c38ac (slot 0xa8): the speed scale of its animation player: data_020c8120 in the
 * town, the base class's elsewhere. */
int MissingNpc2_AnimSpeed(MissingNpc2 *self)
{
    if (SceneQuery_Current() != MISSING_NPC2_SCENE_TOWN) {
        return (int) (uintptr_t) SpecialSceneObject_AnimSpeed(self);
    }
    return data_020c8120;
}
CLEAN_AS(func_020c38ac, MissingNpc2_AnimSpeed)

/* func_020c38d0 (slot 0x04): unless the base class refuses, it becomes the one that exists,
 * its scene is its talk (which gets it as its owner), and outside the town its walking paces
 * 2 and 1 are set. It is not shared. Whether it was set up. */
int MissingNpc2_Init(MissingNpc2 *self)
{
    if (SpecialSceneObject_Init(self) == 0) {
        return 0;
    }
    data_021fbca0 = self;
    SceneObject_SetScene((u8 *) self, &missing_npc2_talk(self)->scene);
    MissingNpc2Talk_SetOwner(missing_npc2_talk(self), self);
    if (SceneQuery_Current() != MISSING_NPC2_SCENE_TOWN) {
        SceneMover_SetPace(missing_npc2_mover(self), 2, 0x333, 0xcc, 0x133);
        SceneMover_SetPace(missing_npc2_mover(self), 1, 0x280, 0xcc, 0x133);
    }
    *missing_npc2_at(self, MISSING_NPC2_LOCAL) = 1;
    return 1;
}
CLEAN_AS(func_020c38d0, MissingNpc2_Init)

/* func_020c3950 (the create function of its record, data_020e7dd8): a zeroed block of 0x714
 * bytes from the auxiliary heap, constructed: the scene object base, the class 0x020d8c64's
 * vtable and members in place order (no person yet, 0xfff1), the class 0x020da088's vtable and
 * heap link, then the class's vtable and its talk. Null when there is no room. */
MissingNpc2 *MissingNpc2_Create(void)
{
    u8 *object = (u8 *) Heap_AllocAuxZeroed(MISSING_NPC2_SIZE);
    if (object == NULL) {
        return NULL;
    }
    SceneObjectBase_Construct((SceneObjectBase *) (void *) object);
    *(const u8 **) (void *) object = data_020d8c64;
    *(u16 *) (void *) (object + MISSING_NPC2_PERSON) = MISSING_NPC2_NO_PERSON;
    LayeredModel_ConstructB((LayeredModel *) (void *) (object + MISSING_NPC2_MODEL));
    SceneStandardAnims_Init((SceneStandardAnims *) (void *) (object + MISSING_NPC2_STANDARD_ANIMS));
    SceneFace_Construct((SceneFace *) (void *) (object + MISSING_NPC2_FACE));
    /* func_020169a8, the animation player's constructor (registered under the destructor's
     * name). */
    SpeakerAnim_Destruct((SpeakerAnim *) (void *) (object + MISSING_NPC2_ANIM));
    SceneMover_Construct((SceneMover *) (void *) (object + MISSING_NPC2_MOVER));
    SceneProbe_Construct(object + MISSING_NPC2_PROBE);
    SceneValue3aa_Clear((SceneValue3aa *) (void *) (object + MISSING_NPC2_VALUE_3AA));
    SceneLook_Construct((SceneLook *) (void *) (object + MISSING_NPC2_LOOK));
    SceneTalkState_Construct((SceneTalkState *) (void *) (object + MISSING_NPC2_TALK_STATE));
    ActEffects_Construct((ActEffects *) (void *) (object + MISSING_NPC2_EFFECTS));
    CollisionContacts_Construct((CollisionContacts *) (void *) (object + MISSING_NPC2_COLLIDER));
    FieldOwnedBody_Construct2((FieldOwnedBody *) (void *) (object + MISSING_NPC2_CARRIER));
    SoundEmitterClass_Construct1((SoundEmitterObject *) (void *) (object + MISSING_NPC2_EMITTER));
    Footsteps_Construct((Footsteps *) (void *) (object + MISSING_NPC2_FOOTSTEPS));
    SceneMotion_Construct((SceneMotion *) (void *) (object + MISSING_NPC2_MOTION));
    SceneAction_Construct((SceneAction *) (void *) (object + MISSING_NPC2_ACTION));
    *(const u8 **) (void *) object = data_020da088;
    PoolLink_Heap4Construct((PoolLink *) (void *) (object + MISSING_NPC2_HEAP));
    *(const u8 **) (void *) object = data_020e7ea4;
    MissingNpc2 *self = (MissingNpc2 *) (void *) object;
    MissingNpc2Talk_Construct(missing_npc2_talk(self));
    return self;
}
CLEAN_AS(func_020c3950, MissingNpc2_Create)
