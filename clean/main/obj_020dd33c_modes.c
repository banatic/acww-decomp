/* The mode handlers of the scene object with vtable 0x020dd33c (obj_020dd33c.h): the table at
 * data_021c9460 (built by __sinit_020c5430) gives each mode and kind an Enter handler, run when
 * the mode starts, and an Update handler, run each frame (func_02059b6c).
 *
 * They move the item's point between the first actor's hold point (Obj020dd33c_HoldPoint),
 * a goal beside that actor and the tile in front of it, grow and shrink its scale, and set the
 * moving flag (Obj020dd33c_SetMoving) while that runs. The frame counts and offsets come from
 * small tables in the ROM, some of them differences of others computed once at start-up:
 *
 *   mode  kind  Enter                          Update
 *    1     0    Obj020dd33c_EnterMode1Kind0    Obj020dd33c_UpdateMode1Kind0
 *    1     1    Obj020dd33c_EnterMode1Kind1    Obj020dd33c_UpdateMode1Kind1
 *    2     0    Obj020dd33c_EnterMode2Kind0    -
 *    2     1    Obj020dd33c_EnterMode2Kind1    Obj020dd33c_UpdateMode2Kind1
 *    3     0    Obj020dd33c_EnterMode3Kind0    Obj020dd33c_UpdateMode3Kind0
 *    3     1    Obj020dd33c_EnterMode3Kind1    Obj020dd33c_UpdateMode3Kind1
 *    4     0    Obj020dd33c_EnterMode4Kind0    Obj020dd33c_UpdateMode4Kind0
 *    4     1    Obj020dd33c_EnterMode4Kind1    Obj020dd33c_UpdateMode4Kind1
 *    5     0    Obj020dd33c_EnterMode5Kind0    Obj020dd33c_UpdateMode5Kind0
 *    5     1    Obj020dd33c_EnterMode5Kind1    Obj020dd33c_UpdateMode5Kind1
 *    6     0    Obj020dd33c_EnterMode6Kind0    Obj020dd33c_UpdateMode6Kind0
 *    7     0    Obj020dd33c_EnterMode7Kind0    Obj020dd33c_UpdateMode7Kind0
 *    7     1    Obj020dd33c_EnterMode7Kind1    Obj020dd33c_UpdateMode7Kind1
 *    8     0    Obj020dd33c_EnterMode8Kind0    Obj020dd33c_UpdateMode8Kind0
 *    9     1    Obj020dd33c_EnterMode9Kind1    Obj020dd33c_UpdateMode9Kind1
 *   10     0    Obj020dd33c_EnterMode10Kind0   Obj020dd33c_UpdateMode10Kind0
 *   11     0    Obj020dd33c_EnterMode11Kind0   Obj020dd33c_UpdateMode11Kind0
 *
 * REQUIRES (all of them): the frame-count divisors read from the tables are not 0 (the ROM's
 * values are 2 to 12). */
#include "obj_020dd33c.h"

#include "autoload_2/approach.h"
#include "autoload_2/vector.h"
#include "clean.h"
#include "main/acre_tile.h"
#include "main/creature_table.h"
#include "main/scene_query.h"
#include "main/sound_emitter.h"
#include "effect_system.h"
#include "ov004/member_pointer.h"

static_assert(offsetof(Obj020dd33c, item) == 0x50, "Obj020dd33c item");
static_assert(offsetof(Obj020dd33c, look) == 0x54, "Obj020dd33c look");
static_assert(offsetof(Obj020dd33c, kind) == 0x5c, "Obj020dd33c kind");
static_assert(offsetof(Obj020dd33c, target) == 0x6c, "Obj020dd33c target");
static_assert(offsetof(Obj020dd33c, offset) == 0x78, "Obj020dd33c offset");
static_assert(offsetof(Obj020dd33c, velocity) == 0x84, "Obj020dd33c velocity");
static_assert(offsetof(Obj020dd33c, speed) == 0x90, "Obj020dd33c speed");
static_assert(offsetof(Obj020dd33c, goal) == 0x9c, "Obj020dd33c goal");
static_assert(offsetof(Obj020dd33c, scale) == 0xa8, "Obj020dd33c scale");
static_assert(offsetof(Obj020dd33c, rotation) == 0xb4, "Obj020dd33c rotation");
static_assert(offsetof(Obj020dd33c, scale_step) == 0xc0, "Obj020dd33c scale_step");
static_assert(offsetof(Obj020dd33c, fish_model) == 0xc4, "Obj020dd33c fish_model");
static_assert(offsetof(Obj020dd33c, phase) == 0xd4, "Obj020dd33c phase");
static_assert(offsetof(Obj020dd33c, frames) == 0xd6, "Obj020dd33c frames");
static_assert(offsetof(Obj020dd33c, shown) == 0xd8, "Obj020dd33c shown");
static_assert(offsetof(Obj020dd33c, unk_d9) == 0xd9, "Obj020dd33c unk_d9");
static_assert(offsetof(Obj020dd33c, emitter) == 0xdc, "Obj020dd33c emitter");
static_assert(offsetof(Actor, profile) == 0x0c && offsetof(Actor, position) == 0x5c && offsetof(Actor, angle) == 0x8c,
              "Actor");

extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void __register_global_object(void *object, void *destruct, void *record);
/* The destructor of a trivial global object (TrivialObject_Destruct); handed to the C++
 * runtime, so the game's symbol. */
extern void func_020012dc(void *object);

/* The scene (SceneQuery_Current) where the item drops onto a fixed point. */
#define OBJ_020DD33C_SCENE_FIXED_DROP 0x10
/* The fish items: their creature kind is the item less the first. */
#define OBJ_020DD33C_FISH_FIRST 0x12e8
#define OBJ_020DD33C_FISH_LAST 0x131f

/* The offset from the first actor's hold point the item follows, turned to its heading
 * (-0x400, -0x300, 0x1100), set up at start-up. */
extern Vec3 data_021c9390;
/* The goals' offsets before the hold offset: mode 1's (0, 0, 0xd00) and mode 3's
 * (0, 0, 0x1300), set up at start-up. */
extern Vec3 data_021c93e4;
extern Vec3 data_021c939c;

/* Frame counts, each the frame the counter reaches at the end of a phase: mode 1 kind 0's
 * (11, 20, 22, 24), mode 1 kind 1's (11, 17, 21), mode 9's (6, 9, 21), mode 11's (10, 22). */
extern const u8 data_020cbb00[4];
extern const u8 data_020cbaf0[3];
extern const u8 data_020cbaf4[3];
extern const u8 data_020cbaec[2];
/* The lengths of those phases (differences of the counts above), set up at start-up. */
extern u8 data_021c9348[3];
extern u8 data_021c9344[2];
extern u8 data_021c9340[2];
extern u8 data_021c933c[1];
/* Mode 1 kind 0: the scale each of phases 1 to 3 grows to (0x1100, 0xf80, 0x1000) and its step
 * per frame (computed at start-up). */
extern const fx32 data_020cbb34[4];
extern const fx32 data_021c9400[4];

/* The function-local statics: mode 9's shrink step (0x1000 over the last phase's length) and
 * mode 5 kind 1's (0x200), each with its "made" guard bit. */
extern u32 data_021c9374;
extern fx32 data_021c9368;
extern u32 data_021c9364;
extern fx32 data_021c9360;
/* The fixed drop point (0x10000, 0, 0x17000) of mode 2 kind 1 and mode 1 kind 1, one each,
 * with its guard bit and its record for the C++ runtime. */
extern u32 data_021c9358;
extern Vec3 data_021c93b4;
extern u8 data_021c93a8[];
extern u32 data_021c9354;
extern Vec3 data_021c93cc;
extern u8 data_021c93c0[];

static int sub32(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

/* |`value`|, wrapping as the ARM's negation does. */
static int abs32(int value)
{
    return value < 0 ? (int) (0u - (u32) value) : value;
}

/* A component stepped towards `target` by `step` (Approach_S32Again); fx32 is the 32-bit int
 * it takes. */
static void approach(fx32 *value, fx32 target, fx32 step)
{
    Approach_S32Again((int *) (void *) value, target, step);
}

/* The step that covers `distance` in `frames` frames: |distance / frames|, rounded towards 0. */
static fx32 step_over(fx32 distance, int frames)
{
    return abs32(distance / frames);
}

/* Each axis's step from the point to the target over `frames` frames. */
static void steps_to_target(Obj020dd33c *obj, int frames)
{
    fx32 z = step_over(sub32(obj->target.z, obj->point.z), frames);
    fx32 y = step_over(sub32(obj->target.y, obj->point.y), frames);
    fx32 x = step_over(sub32(obj->target.x, obj->point.x), frames);
    obj->speed.x = x;
    obj->speed.y = y;
    obj->speed.z = z;
}

/* The point moved a step towards the target on each axis. */
static void point_to_target(Obj020dd33c *obj)
{
    approach(&obj->point.x, obj->target.x, obj->speed.x);
    approach(&obj->point.y, obj->target.y, obj->speed.y);
    approach(&obj->point.z, obj->target.z, obj->speed.z);
}

/* The velocity moved a step towards 0 on each axis. */
static void velocity_to_zero(Obj020dd33c *obj)
{
    approach(&obj->velocity.x, 0, obj->speed.x);
    approach(&obj->velocity.y, 0, obj->speed.y);
    approach(&obj->velocity.z, 0, obj->speed.z);
}

/* The velocity's steps to 0 over `frames` frames. */
static void steps_of_velocity(Obj020dd33c *obj, int frames)
{
    fx32 z = step_over(obj->velocity.z, frames);
    fx32 y = step_over(obj->velocity.y, frames);
    fx32 x = step_over(obj->velocity.x, frames);
    obj->speed.x = x;
    obj->speed.y = y;
    obj->speed.z = z;
}

/* The scale's three axes set to `value`. */
static void set_scale(Obj020dd33c *obj, fx32 value)
{
    obj->scale.x = value;
    obj->scale.y = value;
    obj->scale.z = value;
}

/* The offset made from `from` and turned to the first actor's heading, when there is one. */
static void turn_offset(Obj020dd33c *obj, const Vec3 *from)
{
    if (obj->actors[0] != NULL) {
        obj->offset = *from;
        Vec_RotateY(&obj->offset, obj->actors[0]->angle[1]);
    }
}

/* Whether the item is a fish (one with a held creature's offsets). */
static int holds_fish(const Obj020dd33c *obj)
{
    return obj->item >= OBJ_020DD33C_FISH_FIRST && obj->item <= OBJ_020DD33C_FISH_LAST;
}

/* The target: the tile centre 0x2000 in front of the first actor, or the fixed point `fixed`
 * in scene 0x10, raised by 0x1000. `fixed` is made once (its guard `made`, registered with the
 * C++ runtime under `record`). */
static void target_drop_tile(Obj020dd33c *obj, u32 *made, Vec3 *fixed, u8 *record)
{
    if ((*made & 1) == 0) {
        fixed->x = 0x10000;
        fixed->y = 0;
        fixed->z = 0x17000;
        __register_global_object(fixed, (void *) (uintptr_t) func_020012dc, record);
        *made |= 1;
    }
    Vec3 ahead = {0, 0, 0x2000};
    if (SceneQuery_Current() == OBJ_020DD33C_SCENE_FIXED_DROP) {
        obj->target = *fixed;
    } else {
        Vec_RotateY(&ahead, obj->actors[0]->angle[1]);
        VEC_Add(&ahead, &obj->actors[0]->position, &ahead);
        AcreTile_SnapToTileCentre(&obj->target, &ahead);
    }
    obj->target.y += 0x1000;
}

/* The phases' handlers func_02057d90 calls through: a function-local static the game fills from
 * these constants on its first call (ov004/member_pointer.h). */
extern u32 data_021c936c;
extern MemberPointer data_021c9428[3];
extern const MemberPointer data_020dd1ec, data_020dd1f4, data_020dd2a4;

/* func_02057d90: mode 9 kind 1, each frame: the phase's handler (wait, follow, shrink); none
 * after the third. */
void Obj020dd33c_UpdateMode9Kind1(Obj020dd33c *obj)
{
    static const MemberPointer *const phases[3] = {
        &data_020dd1ec,
        &data_020dd1f4,
        &data_020dd2a4,
    };
    MemberTable_InitOnce(&data_021c936c, data_021c9428, phases, 3);
    switch (obj->phase) {
        case 0:
            Obj020dd33c_Mode9Kind1Wait(obj);
            break;
        case 1:
            Obj020dd33c_Mode9Kind1Follow(obj);
            break;
        case 2:
            Obj020dd33c_Mode9Kind1Shrink(obj);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_02057d90, Obj020dd33c_UpdateMode9Kind1)

/* func_02057e0c: mode 9 kind 1, phase 2: until the frame count reaches data_020cbaf4[2], the
 * scale shrinks to 0 by the step made once from that phase's length, the velocity slows to 0,
 * and the point is the hold point plus the velocity turned to the first actor's heading. Then
 * phase 3, and the movement is over. */
void Obj020dd33c_Mode9Kind1Shrink(Obj020dd33c *obj)
{
    if ((data_021c9374 & 1) == 0) {
        data_021c9368 = abs32(0x1000 / data_021c9340[1]);
        data_021c9374 |= 1;
    }
    int scale = obj->scale.x;
    u8 limit = data_020cbaf4[2];
    if (obj->frames >= limit) {
        return;
    }
    Obj020dd33c_HoldPoint(obj, &obj->point);
    Approach_S32Again(&scale, 0, data_021c9368);
    set_scale(obj, scale);
    velocity_to_zero(obj);
    turn_offset(obj, &obj->velocity);
    VEC_Add(&obj->point, &obj->offset, &obj->point);
    obj->frames++;
    if (obj->frames < limit) {
        return;
    }
    obj->phase = 3;
    Obj020dd33c_SetMoving(obj, 0);
}
CLEAN_AS(func_02057e0c, Obj020dd33c_Mode9Kind1Shrink)

/* func_02057f38: mode 9 kind 1, phase 1: until the frame count reaches data_020cbaf4[1], the
 * target is the hold point plus the turned offset data_021c9390 and the point steps towards
 * it. Then the velocity starts as that offset, to slow to 0 over 8 frames, and phase 2. */
void Obj020dd33c_Mode9Kind1Follow(Obj020dd33c *obj)
{
    int limit = data_020cbaf4[1];
    if (obj->frames >= limit) {
        return;
    }
    Obj020dd33c_HoldPoint(obj, &obj->target);
    turn_offset(obj, &data_021c9390);
    VEC_Add(&obj->target, &obj->offset, &obj->target);
    point_to_target(obj);
    obj->frames++;
    if (obj->frames < limit) {
        return;
    }
    obj->target.x = 0;
    obj->target.y = 0;
    obj->target.z = 0;
    obj->velocity = data_021c9390;
    obj->offset.x = 0;
    obj->offset.y = 0;
    obj->offset.z = 0;
    steps_of_velocity(obj, 8);
    obj->phase = 2;
}
CLEAN_AS(func_02057f38, Obj020dd33c_Mode9Kind1Follow)

/* func_02058064: mode 9 kind 1, phase 0: nothing until the frame count reaches
 * data_020cbaf4[0]; then the target is the hold point plus the turned offset data_021c9390,
 * the steps cover the way there in data_021c9340[0] frames, and phase 1. */
void Obj020dd33c_Mode9Kind1Wait(Obj020dd33c *obj)
{
    if (obj->frames >= data_020cbaf4[0]) {
        return;
    }
    obj->frames++;
    if (obj->frames < data_020cbaf4[0]) {
        return;
    }
    Obj020dd33c_HoldPoint(obj, &obj->target);
    turn_offset(obj, &data_021c9390);
    VEC_Add(&obj->target, &obj->offset, &obj->target);
    steps_to_target(obj, data_021c9340[0]);
    obj->phase = 1;
}
CLEAN_AS(func_02058064, Obj020dd33c_Mode9Kind1Wait)

/* func_02058140: mode 9 kind 1 starts: moving, from frame 0 and phase 0. */
void Obj020dd33c_EnterMode9Kind1(Obj020dd33c *obj)
{
    Obj020dd33c_SetMoving(obj, 1);
    obj->frames = 0;
    obj->phase = 0;
}
CLEAN_AS(func_02058140, Obj020dd33c_EnterMode9Kind1)

/* func_0205815c: mode 7 kind 1, each frame: as mode 4 kind 0. */
void Obj020dd33c_UpdateMode7Kind1(Obj020dd33c *obj)
{
    Obj020dd33c_UpdateMode4Kind0(obj);
}
CLEAN_AS(func_0205815c, Obj020dd33c_UpdateMode7Kind1)

/* func_02058164: mode 7 kind 1 starts: moving, from frame 0. */
void Obj020dd33c_EnterMode7Kind1(Obj020dd33c *obj)
{
    Obj020dd33c_SetMoving(obj, 1);
    obj->frames = 0;
}
CLEAN_AS(func_02058164, Obj020dd33c_EnterMode7Kind1)

/* func_0205817c: mode 5 kind 1, each of 8 frames: the scale shrinks to 0 by 0x200 (a static
 * made once), the velocity slows to 0, and the point is the hold point plus the velocity
 * turned to the first actor's heading. After the eighth, the movement is over. */
void Obj020dd33c_UpdateMode5Kind1(Obj020dd33c *obj)
{
    if ((data_021c9364 & 1) == 0) {
        data_021c9360 = 0x200;
        data_021c9364 |= 1;
    }
    int scale = obj->scale.x;
    if (obj->frames >= 8) {
        return;
    }
    Obj020dd33c_HoldPoint(obj, &obj->point);
    Approach_S32Again(&scale, 0, data_021c9360);
    set_scale(obj, scale);
    velocity_to_zero(obj);
    turn_offset(obj, &obj->velocity);
    VEC_Add(&obj->point, &obj->offset, &obj->point);
    obj->frames++;
    if (obj->frames >= 8) {
        Obj020dd33c_SetMoving(obj, 0);
    }
}
CLEAN_AS(func_0205817c, Obj020dd33c_UpdateMode5Kind1)

/* func_02058280: mode 5 kind 1 starts: the velocity is the offset data_021c9390, to slow to 0
 * over 8 frames; the target and the offset are cleared; moving, from frame 0 and phase 0. */
void Obj020dd33c_EnterMode5Kind1(Obj020dd33c *obj)
{
    obj->target.x = 0;
    obj->target.y = 0;
    obj->target.z = 0;
    obj->velocity = data_021c9390;
    obj->offset.x = 0;
    obj->offset.y = 0;
    obj->offset.z = 0;
    steps_of_velocity(obj, 8);
    Obj020dd33c_SetMoving(obj, 1);
    obj->frames = 0;
    obj->phase = 0;
}
CLEAN_AS(func_02058280, Obj020dd33c_EnterMode5Kind1)

/* func_0205831c: mode 4 kind 1, each of 10 frames: the point is the hold point plus the offset
 * data_021c9390 turned to the first actor's heading. After the tenth, the movement is over. */
void Obj020dd33c_UpdateMode4Kind1(Obj020dd33c *obj)
{
    if (obj->frames >= 10) {
        return;
    }
    Obj020dd33c_HoldPoint(obj, &obj->point);
    turn_offset(obj, &data_021c9390);
    VEC_Add(&obj->point, &obj->offset, &obj->point);
    obj->frames++;
    if (obj->frames >= 10) {
        Obj020dd33c_SetMoving(obj, 0);
    }
}
CLEAN_AS(func_0205831c, Obj020dd33c_UpdateMode4Kind1)

/* func_02058398: mode 4 kind 1 starts: moving, from frame 0. */
void Obj020dd33c_EnterMode4Kind1(Obj020dd33c *obj)
{
    Obj020dd33c_SetMoving(obj, 1);
    obj->frames = 0;
}
CLEAN_AS(func_02058398, Obj020dd33c_EnterMode4Kind1)

/* func_020583b0: mode 3 kind 1, each of 2 frames: the point steps towards the target. After
 * the second, the movement is over. */
void Obj020dd33c_UpdateMode3Kind1(Obj020dd33c *obj)
{
    if (obj->frames >= 2) {
        return;
    }
    point_to_target(obj);
    obj->frames++;
    if (obj->frames >= 2) {
        Obj020dd33c_SetMoving(obj, 0);
    }
}
CLEAN_AS(func_020583b0, Obj020dd33c_UpdateMode3Kind1)

/* func_02058414: mode 3 kind 1 starts: the target is the hold point plus the offset
 * data_021c9390 turned to the first actor's heading, reached in 2 frames; moving, from
 * frame 0. */
void Obj020dd33c_EnterMode3Kind1(Obj020dd33c *obj)
{
    Obj020dd33c_HoldPoint(obj, &obj->target);
    turn_offset(obj, &data_021c9390);
    VEC_Add(&obj->target, &obj->offset, &obj->target);
    steps_to_target(obj, 2);
    obj->frames = 0;
    Obj020dd33c_SetMoving(obj, 1);
}
CLEAN_AS(func_02058414, Obj020dd33c_EnterMode3Kind1)

/* func_020584c4: mode 2 kind 1, each of 4 frames: the point steps towards the target. After
 * the fourth, the movement is over. */
void Obj020dd33c_UpdateMode2Kind1(Obj020dd33c *obj)
{
    if (obj->frames >= 4) {
        return;
    }
    point_to_target(obj);
    obj->frames++;
    if (obj->frames >= 4) {
        Obj020dd33c_SetMoving(obj, 0);
    }
}
CLEAN_AS(func_020584c4, Obj020dd33c_UpdateMode2Kind1)

/* func_02058528: mode 2 kind 1 starts: the target is the tile in front of the first actor
 * (target_drop_tile, with this mode's own fixed point), reached in 4 frames; moving, from
 * frame 0. */
void Obj020dd33c_EnterMode2Kind1(Obj020dd33c *obj)
{
    target_drop_tile(obj, &data_021c9358, &data_021c93b4, data_021c93a8);
    steps_to_target(obj, 4);
    obj->frames = 0;
    Obj020dd33c_SetMoving(obj, 1);
}
CLEAN_AS(func_02058528, Obj020dd33c_EnterMode2Kind1)

/* The phases' handlers func_02058634 calls through: a function-local static the game fills from
 * these constants on its first call (ov004/member_pointer.h). */
extern u32 data_021c9370;
extern MemberPointer data_021c9410[3];
extern const MemberPointer data_020dd284, data_020dd29c, data_020dd2fc;

/* func_02058634: mode 1 kind 1, each frame: the phase's handler (wait, grow, drop); none
 * after the third. */
void Obj020dd33c_UpdateMode1Kind1(Obj020dd33c *obj)
{
    static const MemberPointer *const phases[3] = {
        &data_020dd284,
        &data_020dd29c,
        &data_020dd2fc,
    };
    MemberTable_InitOnce(&data_021c9370, data_021c9410, phases, 3);
    switch (obj->phase) {
        case 0:
            Obj020dd33c_Mode1Kind1Wait(obj);
            break;
        case 1:
            Obj020dd33c_Mode1Kind1Grow(obj);
            break;
        case 2:
            Obj020dd33c_Mode1Kind1Drop(obj);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_02058634, Obj020dd33c_UpdateMode1Kind1)

/* func_020586b0: mode 1 kind 1, phase 2: until the frame count reaches data_020cbaf0[2], the
 * scale grows to 0x1000 by 0x200 and the point steps towards the target. Then, for the items
 * 0x1492-0x14fd, sound 0x70 plays; phase 3, and the movement is over. */
void Obj020dd33c_Mode1Kind1Drop(Obj020dd33c *obj)
{
    u8 limit = data_020cbaf0[2];
    if (obj->frames >= limit) {
        return;
    }
    int scale = obj->scale.x;
    Approach_S32Again(&scale, 0x1000, 0x200);
    set_scale(obj, scale);
    point_to_target(obj);
    obj->frames++;
    if (obj->frames < limit) {
        return;
    }
    if (obj->item >= 0x1492 && obj->item <= 0x14fd) {
        SoundEmitter_PlayB((SoundEmitter *) (void *) obj->emitter, 0x70, 0x7f, 0);
    }
    obj->phase = 3;
    Obj020dd33c_SetMoving(obj, 0);
}
CLEAN_AS(func_020586b0, Obj020dd33c_Mode1Kind1Drop)

/* func_02058788: mode 1 kind 1, phase 1: until the frame count reaches data_020cbaf0[1], the
 * scale grows to 0x1000 by 0x200, the velocity steps towards the target, and the point is the
 * hold point plus the velocity turned to the first actor's heading. Then the target is the
 * tile in front of the first actor (target_drop_tile, with this mode's own fixed point), the
 * steps cover the way there in data_021c9344[1] frames, and phase 2. */
void Obj020dd33c_Mode1Kind1Grow(Obj020dd33c *obj)
{
    int limit = data_020cbaf0[1];
    if (obj->frames >= limit) {
        return;
    }
    int scale = obj->scale.x;
    Obj020dd33c_HoldPoint(obj, &obj->point);
    Approach_S32Again(&scale, 0x1000, 0x200);
    set_scale(obj, scale);
    approach(&obj->velocity.x, obj->target.x, obj->speed.x);
    approach(&obj->velocity.y, obj->target.y, obj->speed.y);
    approach(&obj->velocity.z, obj->target.z, obj->speed.z);
    turn_offset(obj, &obj->velocity);
    VEC_Add(&obj->point, &obj->offset, &obj->point);
    obj->frames++;
    if (obj->frames < limit) {
        return;
    }
    target_drop_tile(obj, &data_021c9354, &data_021c93cc, data_021c93c0);
    steps_to_target(obj, data_021c9344[1]);
    obj->phase = 2;
}
CLEAN_AS(func_02058788, Obj020dd33c_Mode1Kind1Grow)

/* func_02058964: mode 1 kind 1, phase 0: nothing until the frame count reaches
 * data_020cbaf0[0]; then the velocity and the offset start at 0 to go to the target offset
 * data_021c9390 in 12 frames, and phase 1. */
void Obj020dd33c_Mode1Kind1Wait(Obj020dd33c *obj)
{
    if (obj->frames >= data_020cbaf0[0]) {
        return;
    }
    obj->frames++;
    if (obj->frames < data_020cbaf0[0]) {
        return;
    }
    obj->velocity.x = 0;
    obj->velocity.y = 0;
    obj->velocity.z = 0;
    obj->offset.x = 0;
    obj->offset.y = 0;
    obj->offset.z = 0;
    obj->target = data_021c9390;
    fx32 z = step_over(obj->target.z, 12);
    fx32 y = step_over(obj->target.y, 12);
    fx32 x = step_over(obj->target.x, 12);
    obj->speed.x = x;
    obj->speed.y = y;
    obj->speed.z = z;
    obj->phase = 1;
}
CLEAN_AS(func_02058964, Obj020dd33c_Mode1Kind1Wait)

/* func_02058a10: mode 1 kind 1 starts: the velocity, the offset and the scale at 0, the item
 * shown; moving, from frame 0 and phase 0. */
void Obj020dd33c_EnterMode1Kind1(Obj020dd33c *obj)
{
    obj->velocity.x = 0;
    obj->velocity.y = 0;
    obj->velocity.z = 0;
    obj->offset.x = 0;
    obj->offset.y = 0;
    obj->offset.z = 0;
    set_scale(obj, 0);
    obj->shown = 1;
    obj->phase = 0;
    obj->frames = 0;
    Obj020dd33c_SetMoving(obj, 1);
}
CLEAN_AS(func_02058a10, Obj020dd33c_EnterMode1Kind1)

/* func_02058a5c: mode 11 kind 0, each frame: the phase's handler (follow, shrink); none after
 * the second. */
void Obj020dd33c_UpdateMode11Kind0(Obj020dd33c *obj)
{
    switch (obj->phase) {
        case 0:
            Obj020dd33c_Mode11Kind0Follow(obj);
            break;
        case 1:
            Obj020dd33c_Mode11Kind0Shrink(obj);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_02058a5c, Obj020dd33c_UpdateMode11Kind0)

/* func_02058ac8: mode 11 kind 0, phase 1: until the frame count reaches data_020cbaec[1], the
 * scale shrinks to 0 by its step and the point is the hold point plus the velocity. Then the
 * next phase. */
void Obj020dd33c_Mode11Kind0Shrink(Obj020dd33c *obj)
{
    if (obj->frames >= data_020cbaec[obj->phase]) {
        return;
    }
    int scale = obj->scale.x;
    Approach_S32Again(&scale, 0, obj->scale_step);
    set_scale(obj, scale);
    Obj020dd33c_HoldPoint(obj, &obj->point);
    VEC_Add(&obj->point, &obj->velocity, &obj->point);
    obj->frames++;
    if (obj->frames >= data_020cbaec[obj->phase]) {
        obj->phase++;
    }
}
CLEAN_AS(func_02058ac8, Obj020dd33c_Mode11Kind0Shrink)

/* func_02058b5c: mode 11 kind 0, phase 0: until the frame count reaches data_020cbaec[0], the
 * point is the hold point plus the velocity. Then the scale's step is set to shrink it to 0
 * over data_021c933c[0] frames, and the next phase. */
void Obj020dd33c_Mode11Kind0Follow(Obj020dd33c *obj)
{
    if (obj->frames >= data_020cbaec[obj->phase]) {
        return;
    }
    Obj020dd33c_HoldPoint(obj, &obj->point);
    VEC_Add(&obj->point, &obj->velocity, &obj->point);
    obj->frames++;
    if (obj->frames >= data_020cbaec[obj->phase]) {
        obj->scale_step = step_over(obj->scale.x, data_021c933c[obj->phase]);
        obj->phase++;
    }
}
CLEAN_AS(func_02058b5c, Obj020dd33c_Mode11Kind0Follow)

/* func_02058be0: mode 11 kind 0 starts: moving; the velocity is the point less the hold
 * point (so the item keeps its place by the hand); from frame 0 and phase 0. */
void Obj020dd33c_EnterMode11Kind0(Obj020dd33c *obj)
{
    Vec3 hold;
    Vec3 difference;
    Obj020dd33c_SetMoving(obj, 1);
    Obj020dd33c_HoldPoint(obj, &hold);
    Vec_Subtract(&difference, &obj->point, &hold);
    obj->velocity = difference;
    obj->frames = 0;
    obj->phase = 0;
}
CLEAN_AS(func_02058be0, Obj020dd33c_EnterMode11Kind0)

/* func_02058c2c: mode 8 kind 0, each of 10 frames: only counted. After the tenth, the
 * movement is over. */
void Obj020dd33c_UpdateMode8Kind0(Obj020dd33c *obj)
{
    if (obj->frames >= 10) {
        return;
    }
    obj->frames++;
    if (obj->frames >= 10) {
        Obj020dd33c_SetMoving(obj, 0);
    }
}
CLEAN_AS(func_02058c2c, Obj020dd33c_UpdateMode8Kind0)

/* func_02058c60: mode 8 kind 0 starts: moving, from frame 0; an item drawn as model 0x27 is
 * drawn as itself from now on, and effect 0x93 starts at the point. */
void Obj020dd33c_EnterMode8Kind0(Obj020dd33c *obj)
{
    Obj020dd33c_SetMoving(obj, 1);
    obj->frames = 0;
    if (obj->look == OBJ_020DD33C_LOOK_MODEL_27) {
        obj->look = 0;
    }
    EffectSystem_StartOneShotSetNumberCopy(0x93, &obj->point, 0, 0);
}
CLEAN_AS(func_02058c60, Obj020dd33c_EnterMode8Kind0)

/* func_02058c90: mode 7 kind 0, each of 9 frames: the point is the hold point plus the
 * velocity. After the ninth, the movement is over. */
void Obj020dd33c_UpdateMode7Kind0(Obj020dd33c *obj)
{
    if (obj->frames >= 9) {
        return;
    }
    Obj020dd33c_HoldPoint(obj, &obj->point);
    VEC_Add(&obj->point, &obj->velocity, &obj->point);
    obj->frames++;
    if (obj->frames >= 9) {
        Obj020dd33c_SetMoving(obj, 0);
    }
}
CLEAN_AS(func_02058c90, Obj020dd33c_UpdateMode7Kind0)

/* func_02058cdc: mode 7 kind 0 starts: the velocity is the point less the hold point; moving,
 * from frame 0. */
void Obj020dd33c_EnterMode7Kind0(Obj020dd33c *obj)
{
    Vec3 hold;
    Vec3 difference;
    Obj020dd33c_HoldPoint(obj, &hold);
    Vec_Subtract(&difference, &obj->point, &hold);
    obj->velocity = difference;
    Obj020dd33c_SetMoving(obj, 1);
    obj->frames = 0;
}
CLEAN_AS(func_02058cdc, Obj020dd33c_EnterMode7Kind0)

/* func_02058d24: mode 6 kind 0, each frame: nothing. */
void Obj020dd33c_UpdateMode6Kind0(void) {}
CLEAN_AS(func_02058d24, Obj020dd33c_UpdateMode6Kind0)

/* func_02058d28: mode 6 kind 0 starts: nothing. */
void Obj020dd33c_EnterMode6Kind0(void) {}
CLEAN_AS(func_02058d28, Obj020dd33c_EnterMode6Kind0)

/* func_02058d2c: mode 5 kind 0, each of 8 frames: the scale shrinks to 0 by its step, the
 * velocity slows to 0, and the point is the hold point plus the velocity turned to the first
 * actor's heading. After the eighth, the movement is over. */
void Obj020dd33c_UpdateMode5Kind0(Obj020dd33c *obj)
{
    int scale = obj->scale.x;
    if (obj->frames >= 8) {
        return;
    }
    Obj020dd33c_HoldPoint(obj, &obj->point);
    Approach_S32Again(&scale, 0, obj->scale_step);
    set_scale(obj, scale);
    velocity_to_zero(obj);
    turn_offset(obj, &obj->velocity);
    VEC_Add(&obj->point, &obj->offset, &obj->point);
    obj->frames++;
    if (obj->frames >= 8) {
        Obj020dd33c_SetMoving(obj, 0);
    }
}
CLEAN_AS(func_02058d2c, Obj020dd33c_UpdateMode5Kind0)

/* func_02058e0c: mode 5 kind 0 starts: the velocity is the point less the hold point, turned
 * back from the first actor's heading, to slow to 0 over 8 frames, and the scale shrinks to 0
 * over 8 frames; the target and the offset are cleared; moving, from frame 0 and phase 0. */
void Obj020dd33c_EnterMode5Kind0(Obj020dd33c *obj)
{
    Vec3 hold;
    Vec3 difference;
    obj->target.x = 0;
    obj->target.y = 0;
    obj->target.z = 0;
    Obj020dd33c_HoldPoint(obj, &hold);
    Vec_Subtract(&difference, &obj->point, &hold);
    obj->velocity = difference;
    if (obj->actors[0] != NULL) {
        /* QUIRK: the heading is negated in 16 bits, so 0x8000 stays 0x8000. */
        Vec_RotateY(&obj->velocity, (s16) -obj->actors[0]->angle[1]);
    }
    obj->offset.x = 0;
    obj->offset.y = 0;
    obj->offset.z = 0;
    steps_of_velocity(obj, 8);
    obj->scale_step = step_over(obj->scale.x, 8);
    Obj020dd33c_SetMoving(obj, 1);
    obj->frames = 0;
    obj->phase = 0;
}
CLEAN_AS(func_02058e0c, Obj020dd33c_EnterMode5Kind0)

/* func_02058eec: mode 10 kind 0, each frame: the point is the hold point plus the velocity. */
void Obj020dd33c_UpdateMode10Kind0(Obj020dd33c *obj)
{
    Obj020dd33c_HoldPoint(obj, &obj->point);
    VEC_Add(&obj->point, &obj->velocity, &obj->point);
}
CLEAN_AS(func_02058eec, Obj020dd33c_UpdateMode10Kind0)

/* func_02058f0c: mode 10 kind 0 starts: not moving (it follows the hold point for as long as
 * it lasts); the velocity is the point less the hold point; from frame 0. */
void Obj020dd33c_EnterMode10Kind0(Obj020dd33c *obj)
{
    Vec3 hold;
    Vec3 difference;
    Obj020dd33c_SetMoving(obj, 0);
    Obj020dd33c_HoldPoint(obj, &hold);
    Vec_Subtract(&difference, &obj->point, &hold);
    obj->velocity = difference;
    obj->frames = 0;
}
CLEAN_AS(func_02058f0c, Obj020dd33c_EnterMode10Kind0)

/* func_02058f54: mode 4 kind 0 (and mode 7 kind 1), each frame: for 9 frames the point steps
 * towards the target on X and Z, its height the hold point's plus the target's; after the
 * ninth the velocity keeps the point's place from the hold point and the movement is over.
 * On the frame after, the point is the hold point plus that velocity (and nothing after).
 * BUG: the hold point is read even when the first actor's method writes nothing (no first
 * actor, or a joint at the origin), from a stale stack word in the ROM; here it is 0. */
void Obj020dd33c_UpdateMode4Kind0(Obj020dd33c *obj)
{
    Vec3 hold = {0, 0, 0};
    if (obj->frames < 9) {
        Obj020dd33c_HoldPoint(obj, &hold);
        approach(&obj->point.x, obj->target.x, obj->speed.x);
        obj->point.y = (int) ((u32) hold.y + (u32) obj->target.y);
        approach(&obj->point.z, obj->target.z, obj->speed.z);
        obj->frames++;
        if (obj->frames >= 9) {
            Vec3 difference;
            Vec_Subtract(&difference, &obj->point, &hold);
            obj->velocity = difference;
            Obj020dd33c_SetMoving(obj, 0);
        }
    } else if (obj->frames == 9) {
        Obj020dd33c_HoldPoint(obj, &obj->point);
        VEC_Add(&obj->point, &obj->velocity, &obj->point);
    }
}
CLEAN_AS(func_02058f54, Obj020dd33c_UpdateMode4Kind0)

/* The goal beside the first actor: `base` plus, for a fish, its class's first or `second`
 * offset, plus the hold offset of the first actor's class, turned and placed by the first
 * actor. */
static void place_goal(Obj020dd33c *obj, Vec3 *base, int second)
{
    if (holds_fish(obj)) {
        int offset_class = CreatureTable_OffsetClass((unsigned int) (obj->item - OBJ_020DD33C_FISH_FIRST));
        const Vec3 *fish_offset = second ? Obj020dd33c_FishSecondOffset(obj->actors[0], offset_class)
                                         : Obj020dd33c_FishFirstOffset(obj->actors[0], offset_class);
        VEC_Add(base, fish_offset, base);
    }
    Vec3 hold_offset;
    Obj020dd33c_HoldOffset(&hold_offset, obj, 0);
    VEC_Add(base, &hold_offset, base);
    Obj020dd33c_PlaceByActor(obj, &obj->goal, base, 0);
}

/* func_02058ffc: mode 4 kind 0 starts: the goal is placed beside the first actor (mode 1's
 * base offset data_021c93e4 and the fish's first offset) and is the target, reached on X and Z
 * in 2 frames; moving, from frame 0. The hold point is asked for and not used. */
void Obj020dd33c_EnterMode4Kind0(Obj020dd33c *obj)
{
    Vec3 hold;
    Obj020dd33c_HoldPoint(obj, &hold);
    obj->goal.x = 0;
    obj->goal.y = 0;
    obj->goal.z = 0;
    Vec3 base = data_021c93e4;
    place_goal(obj, &base, 0);
    obj->target = obj->goal;
    fx32 z = step_over(sub32(obj->target.z, obj->point.z), 2);
    fx32 x = step_over(sub32(obj->target.x, obj->point.x), 2);
    obj->speed.x = x;
    obj->speed.y = 0;
    obj->speed.z = z;
    obj->frames = 0;
    Obj020dd33c_SetMoving(obj, 1);
}
CLEAN_AS(func_02058ffc, Obj020dd33c_EnterMode4Kind0)

/* func_020590f8: mode 3 kind 0, each of 2 frames: the point steps towards the target. After
 * the second, the movement is over. */
void Obj020dd33c_UpdateMode3Kind0(Obj020dd33c *obj)
{
    if (obj->frames >= 2) {
        return;
    }
    point_to_target(obj);
    obj->frames++;
    if (obj->frames >= 2) {
        Obj020dd33c_SetMoving(obj, 0);
    }
}
CLEAN_AS(func_020590f8, Obj020dd33c_UpdateMode3Kind0)

/* func_0205915c: mode 3 kind 0 starts: the goal is placed beside the first actor (the base
 * offset data_021c939c and the fish's second offset); the target is the goal raised by the
 * hold point's height, reached in 2 frames; moving, from frame 0.
 * BUG: as Obj020dd33c_UpdateMode4Kind0, the hold point's height is read even when nothing
 * was written to it; here it is 0. */
void Obj020dd33c_EnterMode3Kind0(Obj020dd33c *obj)
{
    Vec3 hold = {0, 0, 0};
    Obj020dd33c_HoldPoint(obj, &hold);
    obj->goal.x = 0;
    obj->goal.y = 0;
    obj->goal.z = 0;
    Vec3 base = data_021c939c;
    place_goal(obj, &base, 1);
    obj->target.x = obj->goal.x;
    obj->target.y = (int) ((u32) hold.y + (u32) obj->goal.y);
    obj->target.z = obj->goal.z;
    steps_to_target(obj, 2);
    obj->frames = 0;
    Obj020dd33c_SetMoving(obj, 1);
}
CLEAN_AS(func_0205915c, Obj020dd33c_EnterMode3Kind0)

/* func_02059270: mode 2 kind 0 starts: moving (there is no update; it stays so). */
void Obj020dd33c_EnterMode2Kind0(Obj020dd33c *obj)
{
    Obj020dd33c_SetMoving(obj, 1);
}
CLEAN_AS(func_02059270, Obj020dd33c_EnterMode2Kind0)

/* The phases' handlers func_0205927c calls through: a function-local static the game fills from
 * these constants on its first call (ov004/member_pointer.h). */
extern u32 data_021c934c;
extern MemberPointer data_021c9440[4];
extern const MemberPointer data_020dd1ac, data_020dd1b4, data_020dd2bc, data_020dd2ec;

/* func_0205927c: mode 1 kind 0, each frame: phase 0 holds the item at the hold point, phases 1
 * to 3 raise it to the goal; nothing after. */
void Obj020dd33c_UpdateMode1Kind0(Obj020dd33c *obj)
{
    static const MemberPointer *const phases[4] = {
        &data_020dd2bc,
        &data_020dd2ec,
        &data_020dd1ac,
        &data_020dd1b4,
    };
    MemberTable_InitOnce(&data_021c934c, data_021c9440, phases, 4);
    switch (obj->phase) {
        case 0:
            Obj020dd33c_Mode1Kind0Hold(obj);
            break;
        case 1:
        case 2:
        case 3:
            Obj020dd33c_Mode1Kind0Rise(obj);
            break;
        default:
            break;
    }
}
CLEAN_AS(func_0205927c, Obj020dd33c_UpdateMode1Kind0)

/* func_02059304: mode 1 kind 0, phases 1 to 3: the scale steps towards the phase's size
 * (data_020cbb34, by data_021c9400; both scaled by the fish's class factor for a fish), and
 * the point towards the goal, its height above the hold point's. When the frame count reaches
 * the phase's end (data_020cbb00) the next phase; after the third the movement is over.
 * BUG: as Obj020dd33c_UpdateMode4Kind0, the hold point's height is read even when nothing
 * was written to it; here it is 0. */
void Obj020dd33c_Mode1Kind0Rise(Obj020dd33c *obj)
{
    int scale = obj->scale.x;
    fx32 size = data_020cbb34[obj->phase];
    fx32 step = data_021c9400[obj->phase];
    if (holds_fish(obj)) {
        fx32 factor = Obj020dd33c_FishScale(
            (unsigned int) CreatureTable_OffsetClass((unsigned int) (obj->item - OBJ_020DD33C_FISH_FIRST)));
        size = FX_MulFunc(size, factor);
        step = FX_MulFunc(step, factor);
    }
    Approach_S32(&scale, size, step);
    set_scale(obj, scale);

    Vec3 hold = {0, 0, 0};
    Obj020dd33c_HoldPoint(obj, &hold);
    approach(&obj->point.x, obj->goal.x, obj->speed.x);
    approach(&obj->point.y, (int) ((u32) hold.y + (u32) obj->goal.y), obj->speed.y);
    approach(&obj->point.z, obj->goal.z, obj->speed.z);

    obj->frames++;
    if (obj->frames >= data_020cbb00[obj->phase]) {
        obj->phase++;
        if (obj->phase >= 4) {
            Obj020dd33c_SetMoving(obj, 0);
        }
    }
}
CLEAN_AS(func_02059304, Obj020dd33c_Mode1Kind0Rise)

/* func_02059420: mode 1 kind 0, phase 0: the point is the hold point. When the frame count
 * reaches data_020cbb00[0], phase 1, with the steps that bring the point to the goal in
 * data_021c9348[0] frames (the height's from 0, as it rises above the hold point). */
void Obj020dd33c_Mode1Kind0Hold(Obj020dd33c *obj)
{
    Obj020dd33c_HoldPoint(obj, &obj->point);
    obj->frames++;
    if (obj->frames < data_020cbb00[obj->phase]) {
        return;
    }
    obj->phase++;
    int frames = data_021c9348[0];
    obj->speed.x = step_over(sub32(obj->goal.x, obj->point.x), frames);
    obj->speed.y = step_over(obj->goal.y, frames);
    obj->speed.z = step_over(sub32(obj->goal.z, obj->point.z), frames);
}
CLEAN_AS(func_02059420, Obj020dd33c_Mode1Kind0Hold)

/* func_020594c0: mode 1 kind 0 starts: the velocity, the offset and the goal at 0; the goal
 * placed beside the first actor (the base offset data_021c93e4 and the fish's first offset);
 * the scale at 0, the item shown; moving, from phase 0. */
void Obj020dd33c_EnterMode1Kind0(Obj020dd33c *obj)
{
    obj->velocity.x = 0;
    obj->velocity.y = 0;
    obj->velocity.z = 0;
    obj->offset.x = 0;
    obj->offset.y = 0;
    obj->offset.z = 0;
    obj->goal.x = 0;
    obj->goal.y = 0;
    obj->goal.z = 0;
    Vec3 base = data_021c93e4;
    place_goal(obj, &base, 0);
    set_scale(obj, 0);
    obj->shown = 1;
    obj->phase = 0;
    Obj020dd33c_SetMoving(obj, 1);
}
CLEAN_AS(func_020594c0, Obj020dd33c_EnterMode1Kind0)
