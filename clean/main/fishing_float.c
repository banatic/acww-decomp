/* The fishing rod's float and the pool of its models (fishing_float.h). */
#include "fishing_float.h"

#include <string.h>

#include "autoload_2/approach.h"
#include "autoload_2/fx_math.h"
#include "autoload_2/heap.h"
#include "autoload_2/matrix.h"
#include "autoload_2/process.h" /* MemberFn */
#include "clean.h"
#include "field_collision.h"
#include "globe.h"
#include "resource_pools.h"
#include "scene_heaps.h"
#include "scene_query.h"
#include "scene_tables.h"
#include "session.h"
#include "vram_copy_task.h"
#include "c_library.h"
#include "effect_system.h"
#include "ov003/fish_shadow.h"
#include "rom_file.h"

static_assert(sizeof(FishingFloat) == 0x40, "FishingFloat");
static_assert(offsetof(FishingFloat, target) == 0x1c && offsetof(FishingFloat, holder) == 0x28, "FishingFloat");
static_assert(offsetof(FishingFloat, landed) == 0x38 && offsetof(FishingFloat, player) == 0x3c, "FishingFloat");
static_assert(offsetof(FishingFloatPool, region) == 0x024, "FishingFloatPool.region");
static_assert(offsetof(FishingFloatPool, task) == 0x0d8, "FishingFloatPool.task");
static_assert(offsetof(FishingFloatPool, model) == 0x1d4, "FishingFloatPool.model");
static_assert(offsetof(FishingFloatPool, owner) == 0x750, "FishingFloatPool.owner");

/* The ModelLoaderTask.state of a task that is queued. */
#define FISHING_FLOAT_TASK_QUEUED 1
/* The first entry of the scene's other actors. */
#define FISHING_FLOAT_POOL_OTHERS 4
/* The players' float entries: FishingFloatPool_FloatingOf answers for these only. */
#define FISHING_FLOAT_POOL_PLAYERS 4
/* The models: three ("/PItm/Uki0/0-2"); any other number loads model 0 and leaves the entry
 * without its float. */
#define FISHING_FLOAT_MODELS 3
#define FISHING_FLOAT_POOL_ALIGN 4

/* The effects (func_020912d4). */
#define FISHING_FLOAT_EFFECT_LAND 12
#define FISHING_FLOAT_EFFECT_REELED 13
#define FISHING_FLOAT_EFFECT_PULL 14
#define FISHING_FLOAT_EFFECT_BOB 15
#define FISHING_FLOAT_EFFECT_UNDER 16
#define FISHING_FLOAT_EFFECT_RIPPLE 17

/* The flight (FishingFloat_Fly): across, at least 0.1 and at most 3.2 a frame by 1/5 or 1/10
 * of the way; eased down at least 0.02 a frame. */
#define FISHING_FLOAT_FLY_MAX_STEP 0xccd
#define FISHING_FLOAT_FLY_MIN_STEP 0x19a
#define FISHING_FLOAT_FLY_DOWN_MIN_STEP 0x52
/* The arcs' gravity (FishingFloat_Arc): fixed, or the height to cover plus 4.0 or 8.0, over
 * 100; the speed it starts with is ten times it. */
#define FISHING_FLOAT_ARC_GRAVITY_CAST 0xa3

/* The swing (FishingFloat_SwingBack, FishingFloat_StepSwing): frames of the swing back, the
 * last frame of the throw, the throw's turn off the holder's facing and the distances. */
#define FISHING_FLOAT_SWING_FRAMES 15
#define FISHING_FLOAT_THROW_LAST 20
#define FISHING_FLOAT_THROW_TURN 0x1838
#define FISHING_FLOAT_SWING_STEP 0x2ee
#define FISHING_FLOAT_THROW_STEP 1600

/* The heights over the water's surface, and the line's length. */
#define FISHING_FLOAT_RISE_STEP 0x1000
#define FISHING_FLOAT_RISE_TOP 0x28000
#define FISHING_FLOAT_LAND_DEPTH 819
#define FISHING_FLOAT_BOB_STEP 0x66
#define FISHING_FLOAT_BOB_TOP 0x19a
#define FISHING_FLOAT_BOB_CEILING 0x333
#define FISHING_FLOAT_BOB_DROP 0x30a
#define FISHING_FLOAT_SINK_STEP 0x19a
#define FISHING_FLOAT_SINK_DEPTH 0x333
#define FISHING_FLOAT_RAISE_STEP 410
#define FISHING_FLOAT_RAISE_TOP 1229
#define FISHING_FLOAT_SURFACE_HEIGHT 0xcd
#define FISHING_FLOAT_LINE 0x8000
#define FISHING_FLOAT_LINE_HELD 0x7f33
#define FISHING_FLOAT_LINE_SLACK 0x7e66
/* The ground's normal is the water's flow, a 32nd of it a frame. */
#define FISHING_FLOAT_DRIFT_SHIFT 5
/* A fish draws the float an eighth of the way to it, across. */
#define FISHING_FLOAT_FISH_PULL_SHIFT 3
/* The fish's point (ov003) the float is drawn to. */
#define FISHING_FLOAT_FISH_POINT 0x120

/* The method at slot 0x5c (word 23) of an actor's vtable: its hold point written to `out`
 * (not 0), or 0 when it has none. */
typedef int (*FishingFloatHoldPoint)(Actor *actor, Vec3 *out);
#define FISHING_FLOAT_SLOT_HOLD_POINT 23

typedef void (*FishingFloatStep)(void *self);

extern FishingFloatPool data_021cad80;               /* the pool */
extern MemberFn data_021cad30[FISHING_FLOAT_STATES]; /* the states' step functions */
extern Heap *data_021c9ac8;                          /* the model files' heap (SceneHeaps_Create021c9ac8) */
extern NetSession *data_020ccf94;                    /* the session */
extern const fx16 FX_SinCosTable_[4096 * 2];

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *difference);
/* The model files: the file's texture resource and a file read (its size, 0 on failure). */
extern G3dResTex *func_021077e8(void *file);

static fx32 fishing_float_sin(u16 angle)
{
    return FX_SinCosTable_[2 * (angle >> 4)];
}

static fx32 fishing_float_cos(u16 angle)
{
    return FX_SinCosTable_[2 * (angle >> 4) + 1];
}

/* The float's position at the height `y`: where the effects on the water go. */
static Vec3 fishing_float_at(const FishingFloat *self, fx32 y)
{
    Vec3 at = self->position;
    at.y = y;
    return at;
}

/* The pool's slot of entry `entry`'s float. The original indexes the words at 0x750 without
 * a bound, so the address is computed as it does. */
static FishingFloat **fishing_float_owner_slot(FishingFloatPool *pool, int entry)
{
    return (FishingFloat **) ((uintptr_t) pool + offsetof(FishingFloatPool, owner) + (uintptr_t) entry * 4u);
}

/* ---- The flight ---- */

/* func_0205fb28: one frame of flight to `target`: across (x and z) eased by 1/5 of the way
 * (`ease_down`) or 1/10; down eased the same way while falling when `ease_down`, else moved by
 * the speed, which then loses `gravity`. Whether it is over the target across. */
int FishingFloat_Fly(const Vec3 *target, fx32 gravity, Vec3 *position, fx32 *speed, unsigned char ease_down)
{
    int rate = 0x1000 / (ease_down ? 5 : 10);
    int left_x =
        Approach_EaseS32MinMax((int *) &position->x, target->x, rate, FISHING_FLOAT_FLY_MAX_STEP, FISHING_FLOAT_FLY_MIN_STEP);
    int left_z =
        Approach_EaseS32MinMax((int *) &position->z, target->z, rate, FISHING_FLOAT_FLY_MAX_STEP, FISHING_FLOAT_FLY_MIN_STEP);
    if (*speed < 0 && ease_down) {
        Approach_EaseS32MinMax((int *) &position->y, target->y, rate, FISHING_FLOAT_FLY_MAX_STEP,
                               FISHING_FLOAT_FLY_DOWN_MIN_STEP);
    } else {
        position->y += *speed;
        *speed -= gravity;
    }
    return (u32) left_x + (u32) left_z == 0;
}
CLEAN_AS(func_0205fb28, FishingFloat_Fly)

/* func_0205fbc4: the gravity of an arc from `position` to `target`: for the cast (0) fixed,
 * for the reels (1 and 3, or 2 higher) the height between them plus 4.0 (or 8.0), over 100;
 * the speed it starts with ten times it. Any other arc leaves the gravity as it is. */
void FishingFloat_Arc(const Vec3 *target, const Vec3 *position, fx32 *gravity, fx32 *speed, unsigned char arc)
{
    int height;
    switch (arc) {
        case 0:
            *gravity = FISHING_FLOAT_ARC_GRAVITY_CAST;
            break;
        case 1:
        case 3:
            height = position->y - target->y;
            if (height < 0) {
                height = -height;
            }
            *gravity = (height + 0x4000) / 100;
            break;
        case 2:
            height = position->y - target->y;
            if (height < 0) {
                height = -height;
            }
            *gravity = (height + 0x8000) / 100;
            break;
    }
    *speed = *gravity * 10;
}
CLEAN_AS(func_0205fbc4, FishingFloat_Arc)

/* func_0205fc3c: the float carried back with the rod's swing: moved 0.18 against the holder's
 * facing turned by frames^2 * 0x4800 / 225. */
void FishingFloat_SwingBack(FishingFloat *self)
{
    int turn = self->frames * self->frames * 0x4800 / 0xe1;
    u16 angle = (u16) (self->holder->angle[1] - turn);
    self->position.x -= FX_MulFunc(fishing_float_sin(angle), FISHING_FLOAT_SWING_STEP);
    self->position.z -= FX_MulFunc(fishing_float_cos(angle), FISHING_FLOAT_SWING_STEP);
}
CLEAN_AS(func_0205fc3c, FishingFloat_SwingBack)

/* ---- The states' step functions ---- */

/* func_0205fca0: FISHING_FLOAT_RISE: up 1.0 a frame; at 40.0 none. */
void FishingFloat_StepRise(FishingFloat *self)
{
    self->position.y += FISHING_FLOAT_RISE_STEP;
    if (self->position.y >= FISHING_FLOAT_RISE_TOP) {
        FishingFloat_SetState(self, FISHING_FLOAT_NONE);
    }
}
CLEAN_AS(func_0205fca0, FishingFloat_StepRise)

/* func_0205fcc8: FISHING_FLOAT_REEL_HIGH: flown to the target; once over it, held. */
void FishingFloat_StepReelHigh(FishingFloat *self)
{
    Vec3 target = self->target;
    if (FishingFloat_Fly(&target, self->gravity, &self->position, &self->speed, 1)) {
        FishingFloat_SetState(self, FISHING_FLOAT_HELD);
    }
}
CLEAN_AS(func_0205fcc8, FishingFloat_StepReelHigh)

/* func_0205fd04: FISHING_FLOAT_REEL: the same. */
void FishingFloat_StepReel(FishingFloat *self)
{
    Vec3 target = self->target;
    if (FishingFloat_Fly(&target, self->gravity, &self->position, &self->speed, 1)) {
        FishingFloat_SetState(self, FISHING_FLOAT_HELD);
    }
}
CLEAN_AS(func_0205fd04, FishingFloat_StepReel)

/* The ripples at the float, on the water's surface: started, or moved. */
static void fishing_float_ripple(FishingFloat *self, fx32 surface)
{
    Vec3 at = fishing_float_at(self, surface);
    if (self->ripple == FISHING_FLOAT_NO_EFFECT) {
        self->ripple = EffectSystem_StartKind(FISHING_FLOAT_EFFECT_RIPPLE, &at, NULL, 0);
    } else {
        EffectSystem_MoveHandle(self->ripple, &at, NULL, 0);
    }
}

/* func_0205fd40: FISHING_FLOAT_RIPPLING: without a fish the local player's float floats
 * again; else the ripples follow it on water, where with a fish it is raised 0.1 a frame to
 * 0.3 over the surface. */
void FishingFloat_StepRippling(FishingFloat *self)
{
    CollisionGround ground;

    if (self->fish == NULL) {
        if (Session_IsLocalSlot(data_020ccf94, self->player)) {
            FishingFloat_SetState(self, FISHING_FLOAT_FLOATING);
            return;
        }
        CollisionGround_Init(&ground, &self->position, 1, 1);
        if (ground.unk_30 != 0) {
            fishing_float_ripple(self, ground.limit);
        }
        CollisionGround_Destroy(&ground);
        return;
    }
    CollisionGround_Init(&ground, &self->position, 1, 1);
    if (ground.unk_30 != 0) {
        if (self->position.y < ground.limit + FISHING_FLOAT_RAISE_TOP) {
            self->position.y += FISHING_FLOAT_RAISE_STEP;
        } else {
            self->position.y = ground.limit + FISHING_FLOAT_RAISE_TOP;
        }
        fishing_float_ripple(self, ground.limit);
    }
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_0205fd40, FishingFloat_StepRippling)

/* func_0205fe24: FISHING_FLOAT_SINKING: on water, down 0.1 a frame while above 0.2 under the
 * surface, else there.
 * QUIRK: the last step can take it up to 0.1 below that depth before it is set to it. */
void FishingFloat_StepSinking(FishingFloat *self)
{
    CollisionGround ground;

    CollisionGround_Init(&ground, &self->position, 1, 1);
    if (ground.unk_30 != 0) {
        fx32 depth = ground.limit - FISHING_FLOAT_SINK_DEPTH;
        if (self->position.y > depth) {
            self->position.y -= FISHING_FLOAT_SINK_STEP;
        } else {
            self->position.y = depth;
        }
    }
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_0205fe24, FishingFloat_StepSinking)

/* func_0205fe6c: FISHING_FLOAT_FLOATING: on water the float drifts with it (a 32nd of the
 * ground's normal) and bobs: up 0.025 a frame below 0.1 over the surface (effect 15 when it
 * gets there), on up to 0.2, and set to 0.19 once above it. Then, farther than 8.0 across from
 * the holder, it is held at 7.95 from it with the line's pull (effect 14) following it on the
 * water; nearer than 7.9 the pull stops. */
void FishingFloat_StepFloating(FishingFloat *self)
{
    CollisionGround ground;
    Vec3 holder = self->holder->position;
    u16 flow = 0;

    CollisionGround_Init(&ground, &self->position, 0, 1);
    if (ground.unk_30 != 0) {
        Vec3 drift;
        Vec_ShiftRightCopy(&drift, &ground.normal, FISHING_FLOAT_DRIFT_SHIFT);
        flow = (u16) Math_Atan2(drift.x, drift.z);
        VEC_Add(&self->position, &drift, &self->position);
        fx32 surface = ground.limit;
        fx32 y = self->position.y;
        if (y < surface + FISHING_FLOAT_BOB_CEILING) {
            self->position.y = y + FISHING_FLOAT_BOB_STEP;
            if (y < surface + FISHING_FLOAT_BOB_TOP && self->position.y >= surface + FISHING_FLOAT_BOB_TOP) {
                Vec3 at = fishing_float_at(self, surface);
                EffectSystem_StartKind(FISHING_FLOAT_EFFECT_BOB, &at, NULL, 0);
            }
        } else {
            self->position.y = surface + FISHING_FLOAT_BOB_DROP;
        }
    }

    fx32 distance = Vec_DistanceXZ(&holder, &self->position);
    if (distance >= FISHING_FLOAT_LINE) {
        u16 angle = (u16) Math_Atan2(self->position.x - holder.x, self->position.z - holder.z);
        self->position.x = holder.x + FX_MulFunc(FISHING_FLOAT_LINE_HELD, fishing_float_sin(angle));
        self->position.z = holder.z + FX_MulFunc(FISHING_FLOAT_LINE_HELD, fishing_float_cos(angle));
        if (ground.unk_30 != 0) {
            Vec3 at = fishing_float_at(self, ground.limit);
            if (self->ripple == FISHING_FLOAT_NO_EFFECT) {
                self->ripple = EffectSystem_StartKind(FISHING_FLOAT_EFFECT_PULL, &at, (const s16 *) &flow, 0);
            } else {
                EffectSystem_MoveHandle(self->ripple, &at, (const s16 *) &flow, 0);
            }
        }
    } else if (self->ripple != FISHING_FLOAT_NO_EFFECT) {
        if (distance < FISHING_FLOAT_LINE_SLACK) {
            EffectSystem_EndHandle(self->ripple);
            self->ripple = FISHING_FLOAT_NO_EFFECT;
        } else if (ground.unk_30 != 0) {
            Vec3 at = fishing_float_at(self, ground.limit);
            EffectSystem_MoveHandle(self->ripple, &at, (const s16 *) &flow, 0);
        }
    }
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_0205fe6c, FishingFloat_StepFloating)

/* func_0205fff4: FISHING_FLOAT_CAST: carried back with the swing, its arc set on the last
 * frame of it; then flown to the target until it is at or under the surface of water, where
 * it floats 0.2 under it (effect 12, `landed`, and the fish told, func_ov003_0222a56c). */
void FishingFloat_StepCast(FishingFloat *self)
{
    if (self->frames < FISHING_FLOAT_SWING_FRAMES) {
        FishingFloat_SwingBack(self);
        if (self->frames == FISHING_FLOAT_SWING_FRAMES - 1) {
            Vec3 target = self->target;
            Vec3 position = self->position;
            FishingFloat_Arc(&target, &position, &self->gravity, &self->speed, 0);
        }
        return;
    }

    Vec3 target = self->target;
    FishingFloat_Fly(&target, self->gravity, &self->position, &self->speed, 0);
    CollisionGround ground;
    CollisionGround_Init(&ground, &self->position, 1, 1);
    if (ground.unk_30 != 0) {
        fx32 surface = ground.limit;
        if (surface >= self->position.y) {
            FishingFloat_SetState(self, FISHING_FLOAT_FLOATING);
            self->position.y = ground.limit - FISHING_FLOAT_LAND_DEPTH;
            Vec3 at = fishing_float_at(self, surface);
            EffectSystem_StartKind(FISHING_FLOAT_EFFECT_LAND, &at, NULL, 0);
            self->landed = 1;
            FishShadow_NoteSplash();
        }
    }
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_0205fff4, FishingFloat_StepCast)

/* func_020600bc: FISHING_FLOAT_SWING: carried back with the swing; then thrown 0.39 a frame
 * ahead of the holder's facing, turned by 0x1838, until it is held again after frame 20. */
void FishingFloat_StepSwing(FishingFloat *self)
{
    if (self->frames < FISHING_FLOAT_SWING_FRAMES) {
        FishingFloat_SwingBack(self);
    } else if (self->frames > FISHING_FLOAT_THROW_LAST) {
        FishingFloat_SetState(self, FISHING_FLOAT_HELD);
    } else {
        u16 angle = (u16) (self->holder->angle[1] - FISHING_FLOAT_THROW_TURN);
        self->position.x += FX_MulFunc(fishing_float_sin(angle), FISHING_FLOAT_THROW_STEP);
        self->position.z += FX_MulFunc(fishing_float_cos(angle), FISHING_FLOAT_THROW_STEP);
    }
}
CLEAN_AS(func_020600bc, FishingFloat_StepSwing)

/* func_0206012c: FISHING_FLOAT_HELD: nothing (the drawing puts it at the rod's tip). */
void FishingFloat_StepHeld(void) {}
CLEAN_AS(func_0206012c, FishingFloat_StepHeld)

/* func_02060130: FISHING_FLOAT_NONE: nothing. */
void FishingFloat_StepNone(void) {}
CLEAN_AS(func_02060130, FishingFloat_StepNone)

/* ---- The float ---- */

/* func_02060134: the float drawn with `scale`, unless it is none. Held, it is at the
 * translation of `hand` (the rod's tip), its position then that point unbent from the globe;
 * else it is drawn at its position bent onto the globe, drawn an eighth of the way to the fish
 * across while rippling. */
void FishingFloat_Draw(FishingFloat *self, const Mtx43 *hand, const Vec3 *scale)
{
    if (self->state == FISHING_FLOAT_NONE) {
        return;
    }
    ModelObject *model = FishingFloatPool_Model(&data_021cad80, self->entry);
    Mtx43 matrix = *hand;

    if (self->state <= FISHING_FLOAT_HELD) {
        Vec3 tip = {matrix.m[3][0], matrix.m[3][1], matrix.m[3][2]};
        Globe_Unbend(&self->position, &tip);
    } else {
        Vec3 at = self->position;
        if (self->state == FISHING_FLOAT_RIPPLING) {
            u8 *fish = FishingFloat_Fish(self);
            if (fish != NULL) {
                Vec3 pull;
                memcpy(&pull, fish + FISHING_FLOAT_FISH_POINT, sizeof pull);
                VEC_Subtract(&pull, &at, &pull);
                Vec_ShiftRight(&pull, FISHING_FLOAT_FISH_PULL_SHIFT);
                pull.y = 0;
                VEC_Add(&at, &pull, &at);
            }
        }
        Globe_BendFar(&at, &at);
        Mtx43 placed;
        Mtx43_Translation(&placed, at.x, at.y, at.z);
        matrix = placed;
    }
    memcpy(model->unk_64, &matrix, sizeof matrix);
    ModelObject_Draw(model, scale);
}
CLEAN_AS(func_02060134, FishingFloat_Draw)

/* The step function `fn` called on `object`, as a C++ member function pointer: the object
 * moved by half the adjustment, and for a virtual one the entry `ptr` bytes into its vtable. */
static void fishing_float_call_member(const MemberFn *fn, void *object)
{
    uintptr_t self = (uintptr_t) object + (uintptr_t) (intptr_t) (fn->adj >> 1);
    uintptr_t target = fn->ptr;
    if ((fn->adj & 1) != 0) {
        uintptr_t vtable = *(const u32 *) self;
        target = *(const u32 *) (vtable + fn->ptr);
    }
    ((FishingFloatStep) target)((void *) self);
}

/* func_02060214: once a frame: its texture taken to VRAM until it is there, a frame counted,
 * `landed` cleared, a state out of range made none, then its state's step function
 * (data_021cad30) called. */
void FishingFloat_Update(FishingFloat *self)
{
    FishingFloatPool_UploadTexture(&data_021cad80, self->entry);
    self->frames++;
    self->landed = 0;
    if (self->state >= FISHING_FLOAT_STATES) {
        FishingFloat_SetState(self, FISHING_FLOAT_NONE);
    }
    fishing_float_call_member(&data_021cad30[self->state], self);
}
CLEAN_AS(func_02060214, FishingFloat_Update)

/* The holder's hold point (the rod's tip) as the target, or its position without one. */
static void fishing_float_target_hold_point(FishingFloat *self)
{
    Actor *holder = self->holder;
    const u32 *vtable = (const u32 *) holder->vtable;
    if (((FishingFloatHoldPoint) (uintptr_t) vtable[FISHING_FLOAT_SLOT_HOLD_POINT])(holder, &self->target) == 0) {
        self->target = holder->position;
    }
}

/* Effect `kind` started at the float on the water's surface, when the ground is water. */
static void fishing_float_effect_on_water(FishingFloat *self, int kind, const CollisionGround *ground)
{
    if (ground->unk_30 != 0) {
        Vec3 at = fishing_float_at(self, ground->limit);
        EffectSystem_StartKind(kind, &at, NULL, 0);
    }
}

/* func_0206026c: the float's state set, its effect stopped first; without a holder it is
 * none. Entering a state starts it from frame 0:
 *   HELD      the fish let go when there is one and it agrees (func_ov003_0222a784);
 *   REEL      the target the holder's hold point, the arc set (1), effect 13 on water;
 *   REEL_HIGH the same with the higher arc (2), no effect;
 *   SINKING   effect 16 on water;
 *   FLOATING  from RIPPLING, effect 15 on water;
 *   RIPPLING  the ripples (17) started on water. */
void FishingFloat_SetState(FishingFloat *self, int state)
{
    if (self->ripple != FISHING_FLOAT_NO_EFFECT) {
        EffectSystem_EndHandle(self->ripple);
        self->ripple = FISHING_FLOAT_NO_EFFECT;
    }
    if (self->holder == NULL) {
        self->state = FISHING_FLOAT_NONE;
        return;
    }
    int old = self->state;
    self->state = state;
    self->frames = 0;

    CollisionGround ground;
    CollisionGround_Init(&ground, &self->position, 1, 1);
    switch (state) {
        case FISHING_FLOAT_HELD:
            if (self->fish != NULL && FishShadow_FleeFromPlayer((FishShadow *) (void *) self->fish) != 0) {
                self->fish = NULL;
            }
            break;
        case FISHING_FLOAT_REEL: {
            fishing_float_target_hold_point(self);
            Vec3 target = self->target;
            Vec3 position = self->position;
            FishingFloat_Arc(&target, &position, &self->gravity, &self->speed, 1);
            fishing_float_effect_on_water(self, FISHING_FLOAT_EFFECT_REELED, &ground);
            break;
        }
        case FISHING_FLOAT_REEL_HIGH: {
            fishing_float_target_hold_point(self);
            Vec3 target = self->target;
            Vec3 position = self->position;
            FishingFloat_Arc(&target, &position, &self->gravity, &self->speed, 2);
            break;
        }
        case FISHING_FLOAT_SINKING:
            fishing_float_effect_on_water(self, FISHING_FLOAT_EFFECT_UNDER, &ground);
            break;
        case FISHING_FLOAT_FLOATING:
            if (old == FISHING_FLOAT_RIPPLING) {
                fishing_float_effect_on_water(self, FISHING_FLOAT_EFFECT_BOB, &ground);
            }
            break;
        case FISHING_FLOAT_RIPPLING:
            if (ground.unk_30 != 0) {
                Vec3 at = fishing_float_at(self, ground.limit);
                self->ripple = EffectSystem_StartKind(FISHING_FLOAT_EFFECT_RIPPLE, &at, NULL, 0);
            }
            break;
        default:
            break;
    }
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_0206026c, FishingFloat_SetState)

/* func_02060428 */
void FishingFloat_SetPosition(FishingFloat *self, const Vec3 *position)
{
    self->position.x = position->x;
    self->position.y = position->y;
    self->position.z = position->z;
}
CLEAN_AS(func_02060428, FishingFloat_SetPosition)

/* func_02060438 */
void FishingFloat_SetTarget(FishingFloat *self, const Vec3 *target)
{
    self->target.x = target->x;
    self->target.y = target->y;
    self->target.z = target->z;
}
CLEAN_AS(func_02060438, FishingFloat_SetTarget)

/* func_02060448: the fish told of the player (func_ov003_0222a960 with 0), then forgotten. */
void FishingFloat_TellPlayerFish(FishingFloat *self)
{
    PlayerFish_ThrowBack(self->player, 0);
    self->fish = NULL;
}
CLEAN_AS(func_02060448, FishingFloat_TellPlayerFish)

/* func_02060460: the fish let go (func_ov003_0222aae8), then forgotten. */
void FishingFloat_LetFishGo(FishingFloat *self)
{
    PlayerFish_EndForShadow((FishShadow *) (void *) self->fish);
    self->fish = NULL;
}
CLEAN_AS(func_02060460, FishingFloat_LetFishGo)

/* func_02060474: the fish's flag (func_ov003_0222ab14). */
int FishingFloat_FishFlag80(FishingFloat *self)
{
    return PlayerFish_ArrivedForShadow((FishShadow *) (void *) self->fish);
}
CLEAN_AS(func_02060474, FishingFloat_FishFlag80)

/* func_02060480: on water, the float put 0.05 over the surface. */
void FishingFloat_ToSurface(FishingFloat *self)
{
    CollisionGround ground;

    CollisionGround_Init(&ground, &self->position, 1, 1);
    if (ground.unk_30 != 0) {
        self->position.y = ground.limit + FISHING_FLOAT_SURFACE_HEIGHT;
    }
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_02060480, FishingFloat_ToSurface)

/* func_020604b0: what the fish says (func_ov003_0222ab4c: 0, 1 or 2), 1 without a fish. */
int FishingFloat_FishBite(FishingFloat *self)
{
    if (self->fish == NULL) {
        return 1;
    }
    return FishShadowHook_TryLand((FishShadow *) (void *) self->fish);
}
CLEAN_AS(func_020604b0, FishingFloat_FishBite)

/* func_020604c8: what the fish says (func_ov003_0222aba4); without a fish the float is reeled
 * in and 0. */
int FishingFloat_FishPull(FishingFloat *self)
{
    u8 *fish = self->fish;
    if (fish == NULL) {
        FishingFloat_SetState(self, FISHING_FLOAT_REEL);
        return 0;
    }
    return FishShadowHook_Strike((FishShadow *) (void *) fish);
}
CLEAN_AS(func_020604c8, FishingFloat_FishPull)

/* func_020604e8: whether it is floating or sinking. */
int FishingFloat_IsInWater(FishingFloat *self)
{
    return self->state == FISHING_FLOAT_FLOATING || self->state == FISHING_FLOAT_SINKING;
}
CLEAN_AS(func_020604e8, FishingFloat_IsInWater)

/* func_020604f8 */
u8 *FishingFloat_Fish(FishingFloat *self)
{
    return self->fish;
}
CLEAN_AS(func_020604f8, FishingFloat_Fish)

/* func_020604fc */
void FishingFloat_SetFish(FishingFloat *self, u8 *fish)
{
    self->fish = fish;
}
CLEAN_AS(func_020604fc, FishingFloat_SetFish)

/* func_02060500 */
void FishingFloat_SetPlayer(FishingFloat *self, int player)
{
    self->player = player;
}
CLEAN_AS(func_02060500, FishingFloat_SetPlayer)

/* func_02060504 */
int FishingFloat_Entry(FishingFloat *self)
{
    return self->entry;
}
CLEAN_AS(func_02060504, FishingFloat_Entry)

/* ---- The pool ---- */

/* func_02060508: the float of player entry `entry` when it is floating, as an address; else 0
 * (also from entry FISHING_FLOAT_POOL_PLAYERS on). */
int FishingFloatPool_FloatingOf(FishingFloatPool *pool, int entry)
{
    if (entry >= FISHING_FLOAT_POOL_PLAYERS) {
        return 0;
    }
    FishingFloat *owner = *fishing_float_owner_slot(pool, entry);
    if (owner != NULL && owner->state == FISHING_FLOAT_FLOATING) {
        return (int) (uintptr_t) owner;
    }
    return 0;
}
CLEAN_AS(func_02060508, FishingFloatPool_FloatingOf)

/* func_0206052c */
void FishingFloatPool_SetOwner(FishingFloatPool *pool, int entry, FishingFloat *owner)
{
    *fishing_float_owner_slot(pool, entry) = owner;
}
CLEAN_AS(func_0206052c, FishingFloatPool_SetOwner)

/* func_0206053c: entry `entry`'s texture on its way to VRAM: 1 once the task is done; else
 * the task queued with the model file's texture resource unless it already is, and 0. */
int FishingFloatPool_UploadTexture(FishingFloatPool *pool, int entry)
{
    ModelLoaderTask *task = FishingFloatPool_Task(pool, entry);
    if (task->state == MODEL_LOADER_TASK_DONE) {
        return 1;
    }
    if (task->state != FISHING_FLOAT_TASK_QUEUED) {
        u8 *file = (u8 *) (uintptr_t) FishingFloatPool_ModelFile(pool, entry);
        VramCopyTask_QueueTexture((VramCopyTask *) task, func_021077e8(file), 1);
    }
    return 0;
}
CLEAN_AS(func_0206053c, FishingFloatPool_UploadTexture)

/* func_02060588: the texture of entry `entry`'s model file placed in its VRAM region. */
void FishingFloatPool_PlaceTexture(FishingFloatPool *pool, int entry)
{
    G3dResTex *texture = func_021077e8((void *) (uintptr_t) FishingFloatPool_ModelFile(pool, entry));
    VramRegion_PlaceTexture(FishingFloatPool_Region(pool, entry), texture);
}
CLEAN_AS(func_02060588, FishingFloatPool_PlaceTexture)

/* func_020605ac: model `model`'s file read into entry `entry`'s buffer, at most its size; its
 * size, 0 on failure. */
int FishingFloatPool_LoadModel(FishingFloatPool *pool, int entry, int model)
{
    char *path = FishingFloatPool_ModelPath(model);
    unsigned long file = FishingFloatPool_ModelFile(pool, entry);
    int size = FishingFloatPool_ModelFileSize();
    return RomFile_Read(path, (void *) (uintptr_t) file, size);
}
CLEAN_AS(func_020605ac, FishingFloatPool_LoadModel)

/* func_020605d8: entry `entry`'s task ended when it is queued, else reset. */
void FishingFloatPool_StopUpload(FishingFloatPool *pool, int entry)
{
    VramCopyTask *task = (VramCopyTask *) &pool->task[entry];
    if (pool->task[entry].state == FISHING_FLOAT_TASK_QUEUED) {
        VramCopyTask_End(task);
    } else {
        VramCopyTask_Reset(task);
    }
}
CLEAN_AS(func_020605d8, FishingFloatPool_StopUpload)

/* func_0206060c: the float's entry let go: its model released, its upload stopped and its
 * float forgotten; the float then has no entry. */
void FishingFloat_Release(FishingFloat *self)
{
    FishingFloatPool *pool = &data_021cad80;
    ModelObject_Release(FishingFloatPool_Model(pool, FishingFloat_Entry(self)));
    FishingFloatPool_StopUpload(pool, FishingFloat_Entry(self));
    FishingFloatPool_SetOwner(pool, FishingFloat_Entry(self), NULL);
    self->entry = FISHING_FLOAT_POOL_COUNT;
}
CLEAN_AS(func_0206060c, FishingFloat_Release)

/* func_0206064c: the float set up on entry `entry` with float model `model` (below 3; any
 * other loads model 0 and leaves the entry without the float), its texture placed and the
 * model made from the file; `holder`, unless NULL, its new holder; its state none. */
void FishingFloat_Setup(FishingFloat *self, int entry, Actor *holder, unsigned int model)
{
    FishingFloatPool *pool = &data_021cad80;
    self->entry = (u8) entry;
    if (model < FISHING_FLOAT_MODELS) {
        FishingFloatPool_SetOwner(pool, entry, self);
        FishingFloatPool_LoadModel(pool, entry, (int) model);
    } else {
        FishingFloatPool_SetOwner(pool, entry, NULL);
        FishingFloatPool_LoadModel(pool, entry, 0);
    }
    u8 *file = (u8 *) (uintptr_t) FishingFloatPool_ModelFile(pool, entry);
    FishingFloatPool_PlaceTexture(pool, entry);
    ModelObject_UseFileModel(FishingFloatPool_Model(pool, entry), file);
    if (holder != NULL) {
        self->holder = holder;
    }
    self->state = FISHING_FLOAT_NONE;
}
CLEAN_AS(func_0206064c, FishingFloat_Setup)

/* func_020606bc: the float's destructor, which does nothing. */
void FishingFloat_Destruct(void *self)
{
    (void) self;
}
CLEAN_AS(func_020606bc, FishingFloat_Destruct)

/* func_020606c0: the float's constructor: no entry, holder, fish, effect or player. */
void FishingFloat_Construct(FishingFloat *self)
{
    self->entry = FISHING_FLOAT_POOL_COUNT;
    self->holder = NULL;
    self->fish = NULL;
    self->ripple = FISHING_FLOAT_NO_EFFECT;
    self->player = FISHING_FLOAT_NO_PLAYER;
}
CLEAN_AS(func_020606c0, FishingFloat_Construct)

/* func_020606d4 */
ModelObject *FishingFloatPool_Model(FishingFloatPool *pool, int entry)
{
    return &pool->model[entry];
}
CLEAN_AS(func_020606d4, FishingFloatPool_Model)

/* func_020606e4 */
ModelLoaderTask *FishingFloatPool_Task(FishingFloatPool *pool, int entry)
{
    return &pool->task[entry];
}
CLEAN_AS(func_020606e4, FishingFloatPool_Task)

/* func_020606f0 */
VramRegion *FishingFloatPool_Region(FishingFloatPool *pool, int entry)
{
    return &pool->region[entry];
}
CLEAN_AS(func_020606f0, FishingFloatPool_Region)

/* func_020606fc: entry `entry`'s model file buffer, as an address. */
unsigned long FishingFloatPool_ModelFile(FishingFloatPool *pool, int entry)
{
    return (unsigned long) (uintptr_t) pool->model_file[entry];
}
CLEAN_AS(func_020606fc, FishingFloatPool_ModelFile)

/* func_02060704: every entry's VRAM region cleared, its buffer and float forgotten; then the
 * model files' heap, if there is one, emptied. */
void FishingFloatPool_Clear(FishingFloatPool *pool)
{
    for (int i = 0; i < FISHING_FLOAT_POOL_COUNT; i++) {
        VramRegion_Clear(&pool->region[i]);
    }
    for (int i = 0; i < FISHING_FLOAT_POOL_COUNT; i++) {
        pool->model_file[i] = NULL;
        pool->owner[i] = NULL;
    }
    Heap *heap = data_021c9ac8;
    if (heap != NULL) {
        Heap_FreeAll(heap);
    }
}
CLEAN_AS(func_02060704, FishingFloatPool_Clear)

/* func_02060754: for the entries the scene uses (from 0 the smaller of the session's players
 * and the scene's second count; from FISHING_FLOAT_POOL_OTHERS the scene's first count and
 * heaps less that number, less 1 when it is 0), the VRAM regions allocated, then the model
 * file buffers taken from the heap at data_021c9ac8.
 * REQUIRES: players <= 4 and others <= 5, as the scenes give; no entry's range is checked. */
void FishingFloatPool_AllocEntries(FishingFloatPool *pool)
{
    unsigned int session_players = data_020ccf94->player_count;
    unsigned int players = SceneTables_SecondCount(SceneQuery_Current());
    if (session_players < players) {
        players = session_players;
    }
    unsigned int at_least_one = players != 0 ? players : 1;
    unsigned int first = SceneTables_FirstCount(SceneQuery_Current());
    unsigned int others = first + (unsigned int) ResourcePools_SceneHeapCount() - at_least_one;

    for (unsigned int i = 0; i < players; i++) {
        u32 texture_size = (u32) FishingFloatPool_TextureSize();
        u32 texture_4x4_size = (u32) FishingFloatPool_Texture4x4Size();
        u32 palette_size = (u32) FishingFloatPool_PaletteSize();
        VramRegion_Alloc(&pool->region[i], texture_size, texture_4x4_size, palette_size);
    }
    for (unsigned int i = FISHING_FLOAT_POOL_OTHERS; i < others + FISHING_FLOAT_POOL_OTHERS; i++) {
        u32 texture_size = (u32) FishingFloatPool_TextureSize();
        u32 texture_4x4_size = (u32) FishingFloatPool_Texture4x4Size();
        u32 palette_size = (u32) FishingFloatPool_PaletteSize();
        VramRegion_Alloc(&pool->region[i], texture_size, texture_4x4_size, palette_size);
    }
    Heap *heap = data_021c9ac8;
    for (unsigned int i = 0; i < players; i++) {
        pool->model_file[i] = Heap_AllocAligned(heap, FishingFloatPool_ModelFileSize(), FISHING_FLOAT_POOL_ALIGN);
    }
    for (unsigned int i = FISHING_FLOAT_POOL_OTHERS; i < others + FISHING_FLOAT_POOL_OTHERS; i++) {
        pool->model_file[i] = Heap_AllocAligned(heap, FishingFloatPool_ModelFileSize(), FISHING_FLOAT_POOL_ALIGN);
    }
}
CLEAN_AS(func_02060754, FishingFloatPool_AllocEntries)

/* The members' constructors and destructors handed to __cxa_vec_ctor and __cxa_vec_cleanup:
 * the game's own (VramRegion_Construct, VramRegion_Destruct, ModelObject_Construct,
 * ModelObject_DestructComplete). */
extern void *func_02055cf4(void *region);
extern void func_02055ce8(void *region);
extern void *func_0205577c(void *model);
extern void *func_02055764(void *model);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
/* The model file's path: its buffer, and "/PItm/Uki0/%d.nsbmd". */
extern char data_021cad1c[];
extern const char data_020dd814[];

#define FISHING_FLOAT_PALETTE_SIZE 32
#define FISHING_FLOAT_TEXTURE_4X4_SIZE 0
#define FISHING_FLOAT_TEXTURE_SIZE 512
#define FISHING_FLOAT_MODEL_FILE_SIZE 1240

/* func_02060844: the pool's destructor: the models, then the VRAM regions. Returns the pool. */
FishingFloatPool *FishingFloatPool_Destruct(FishingFloatPool *pool)
{
    __cxa_vec_cleanup(pool->model, FISHING_FLOAT_POOL_COUNT, sizeof(ModelObject), (void (*)(void *))(uintptr_t) func_02055764);
    __cxa_vec_cleanup(pool->region, FISHING_FLOAT_POOL_COUNT, sizeof(VramRegion), func_02055ce8);
    return pool;
}
CLEAN_AS(func_02060844, FishingFloatPool_Destruct)

/* func_02060878: the pool's constructor: the VRAM regions, the tasks and the models; no
 * buffer and no float. Returns the pool. */
FishingFloatPool *FishingFloatPool_Construct(FishingFloatPool *pool)
{
    __cxa_vec_ctor(pool->region, FISHING_FLOAT_POOL_COUNT, sizeof(VramRegion), (void (*)(void *))(uintptr_t) func_02055cf4,
                   func_02055ce8);
    for (int i = 0; i < FISHING_FLOAT_POOL_COUNT; i++) {
        VramCopyTask_Construct((VramCopyTask *) &pool->task[i]);
    }
    __cxa_vec_ctor(pool->model, FISHING_FLOAT_POOL_COUNT, sizeof(ModelObject), (void (*)(void *))(uintptr_t) func_0205577c,
                   (void (*)(void *))(uintptr_t) func_02055764);
    for (int i = 0; i < FISHING_FLOAT_POOL_COUNT; i++) {
        pool->model_file[i] = NULL;
        pool->owner[i] = NULL;
    }
    return pool;
}
CLEAN_AS(func_02060878, FishingFloatPool_Construct)

/* func_020608ec: an entry's VRAM for palettes. */
int FishingFloatPool_PaletteSize(void)
{
    return FISHING_FLOAT_PALETTE_SIZE;
}
CLEAN_AS(func_020608ec, FishingFloatPool_PaletteSize)

/* func_020608f0: an entry's VRAM for 4x4 compressed textures: none. */
int FishingFloatPool_Texture4x4Size(void)
{
    return FISHING_FLOAT_TEXTURE_4X4_SIZE;
}
CLEAN_AS(func_020608f0, FishingFloatPool_Texture4x4Size)

/* func_020608f4: an entry's VRAM for plain textures. */
int FishingFloatPool_TextureSize(void)
{
    return FISHING_FLOAT_TEXTURE_SIZE;
}
CLEAN_AS(func_020608f4, FishingFloatPool_TextureSize)

/* func_020608fc: the size of an entry's model file buffer. */
int FishingFloatPool_ModelFileSize(void)
{
    return FISHING_FLOAT_MODEL_FILE_SIZE;
}
CLEAN_AS(func_020608fc, FishingFloatPool_ModelFileSize)

/* func_02060904: the path of model `model`, "/PItm/Uki0/<model>.nsbmd", in its buffer. */
char *FishingFloatPool_ModelPath(int model)
{
    CLib_SPrintf(data_021cad1c, data_020dd814, model);
    return data_021cad1c;
}
CLEAN_AS(func_02060904, FishingFloatPool_ModelPath)

/* func_02060924: FishingFloatPool_FloatingOf for the pool. */
int FishingFloat_FloatingOf(int entry)
{
    return FishingFloatPool_FloatingOf(&data_021cad80, entry);
}
CLEAN_AS(func_02060924, FishingFloat_FloatingOf)

/* func_02060934, when a scene ends: the pool cleared and the model files' heap destroyed. */
void FishingFloat_EndScene(void)
{
    FishingFloatPool_Clear(&data_021cad80);
    SceneHeaps_Destroy021c9ac8();
}
CLEAN_AS(func_02060934, FishingFloat_EndScene)

/* func_0206094c, when a scene starts: the model files' heap made from `parent`, the scene's
 * entries allocated from it, and the heap shrunk to what they took. */
void FishingFloat_StartScene(Heap *parent)
{
    SceneHeaps_Create021c9ac8(parent);
    FishingFloatPool_AllocEntries(&data_021cad80);
    if (data_021c9ac8 != NULL) {
        Heap_Adjust(data_021c9ac8);
    }
}
CLEAN_AS(func_0206094c, FishingFloat_StartScene)
