/* The special character of "sp_npc_missing2" (missing_npc2.h). */
#include "missing_npc2.h"

#include "actor.h" /* Vec_YawTo */
#include "acre_tile.h"
#include "autoload_2/approach.h"
#include "autoload_2/fx_math.h"
#include "autoload_2/heap.h"
#include "clean.h"
#include "footsteps.h"
#include "scene_look.h"
#include "scene_motion_request.h"
#include "scene_mover.h"
#include "scene_object.h"
#include "scene_probe.h"
#include "scene_value_3aa.h"
#include "special_scene_object.h"
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
/* Its state set (the state's entry run first; its answer 0 refuses it). */
extern void func_020c3690(MissingNpc2 *self, int state);
/* Its talk's destructor. */
extern void *func_020c338c(void *talk);

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
    func_020c338c(self->talk);
    SpecialSceneObject_DestructBody(self);
    return self;
}
CLEAN_AS(func_020c2c34, MissingNpc2_Destruct)

/* func_020c2c5c (slot 0x44): destructed, then freed to the auxiliary heap. */
MissingNpc2 *MissingNpc2_DestructDelete(MissingNpc2 *self)
{
    *(const u8 **) (void *) self = data_020e7ea4;
    func_020c338c(self->talk);
    SpecialSceneObject_DestructBody(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_020c2c5c, MissingNpc2_DestructDelete)

/* func_020c2c88: once the camera's box holds it again, MISSING_NPC2_WANDER. Always 1. */
int MissingNpc2_UpdateOutOfView(MissingNpc2 *self)
{
    if (MissingNpc2_InView(self)) {
        func_020c3690(self, MISSING_NPC2_WANDER);
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
            func_020c3690(self, MISSING_NPC2_OUT_OF_VIEW);
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
