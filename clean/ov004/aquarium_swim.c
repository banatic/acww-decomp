/* What the museum's aquarium fish share for swimming (aquarium_swim.h). */
#include "aquarium_swim.h"

#include "autoload_2/approach.h"
#include "autoload_2/fx_math.h"
#include "clean.h"
#include "main/actor.h"
#include "main/animated_model.h"
#include "main/collision_query.h"
#include "main/field_body.h"
#include "main/field_collision.h"
#include "main/frame_ctrl.h"
#include "main/main_random.h"

static_assert(offsetof(AquariumSwimmer, bend.bending) == 0x22e, "swimmer bending");
static_assert(offsetof(AquariumSwimmer, glass.glass_turned) == 0x250, "swimmer glass turned");
static_assert(sizeof(AquariumSwimmer) == sizeof(AquariumFish), "swimmer view");
static_assert(offsetof(AquariumFish, unk_1fe) == 0x1fe, "fish bend frame");
static_assert(offsetof(AquariumFish, model.frames.frame) == 0x108, "fish anim frame");

/* What each kind is like (museum_aquarium.c). */
extern const AquariumFishInfo data_ov004_02247924[];
/* The river room's tanks' centres: the first (also the sea room's only one) and the second. */
extern Vec3 data_ov004_022593dc;
extern Vec3 data_ov004_022593c4;
/* The game's main random generator. */
extern Random data_021cb5a0;
/* The fish body's vtable. */
extern const u32 data_ov004_02255d28[];

extern const s16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void *NNS_G3dGetJntAnmSet(u8 *file);
extern u8 *func_02107b44(void *set, u32 index);

#define ONE 0x1000

/* An angle of one degree. */
#define DEGREE 0xb6

/* How fast a fish's pitch goes towards its tilt, and back to level. */
#define TILT_STEP 0x186
#define TILT_FIXED 0x1aa9
#define TILT_FIXED_STEP 0x222

/* How fast a fish turns towards a point. */
#define TURN_TOWARDS_STEP 0x38e

/* The kinds that always keep to their own heights, and the kinds of the river room's first
 * tank (those below 17, and kind 25). */
#define KIND_FISH_25 25
#define KIND_FISH_45 45
#define FIRST_SECOND_TANK_KIND 17

/* The part of a river tank a fish keeps out of (the tank is 0x11c00 by 0x5c00), and how near
 * it may come to it: once turning from the glass, and before. */
#define GLASS_INNER_WIDTH 0xfc00
#define GLASS_INNER_DEPTH 0x3c00
#define GLASS_NEAR_TURNING ONE
#define GLASS_NEAR 0x400

/* The ground's height under the tanks, as AquariumSwim_EdgeNearerAlongX takes it. */
#define TANK_GROUND 0x800

/* The height and speed a fish paying attention to another climbs to. */
#define FOCUS_CLIMB_STEP 0x7b
#define FOCUS_CLIMB_TOP 0x5000

static int AquariumSwim_mul(int a, int b)
{
    return (int) ((u32) a * (u32) b);
}

static int AquariumSwim_add(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

static int AquariumSwim_neg(int a)
{
    return (int) (0u - (u32) a);
}

static fx32 AquariumSwim_sin(int angle)
{
    return FX_SinCosTable_[((u16) angle >> 4) * 2];
}

static fx32 AquariumSwim_cos(int angle)
{
    return FX_SinCosTable_[((u16) angle >> 4) * 2 + 1];
}

/* The last frame of the fish's animation, less 1, as FrameCtrl_Passed takes it. */
static u16 AquariumSwim_before_last_frame(const AquariumFish *fish)
{
    u32 frames = ((u32) fish->model.frames.end << 4) >> 16;
    return (u16) (frames - 1u);
}

/* func_ov004_02239424: unless `from` is within `near` of `to`, `yaw` turns towards `to` (by
 * 0x38e) and 0; else 1. */
int AquariumSwim_TurnTowards(s16 *yaw, const Vec3 *from, const Vec3 *to, fx32 near)
{
    if (Vec_Distance(from, to) > near) {
        Approach_S16(yaw, Vec_YawTo(from, to), TURN_TOWARDS_STEP);
        return 0;
    }
    return 1;
}
CLEAN_AS(func_ov004_02239424, AquariumSwim_TurnTowards)

/* func_ov004_02239460: `low` plus a random number below `high - low`. */
int AquariumSwim_Random(int low, int high)
{
    return AquariumSwim_add(low, (int) MainRandom_Below((int) ((u32) high - (u32) low)));
}
CLEAN_AS(func_ov004_02239460, AquariumSwim_Random)

/* func_ov004_02239474: a random angle of `low` up to (not including) `high` degrees, either way
 * (the way drawn first, from the main generator's next number taken as signed). */
s16 AquariumSwim_RandomAngle(int high, int low)
{
    int sign = (s32) Random_Next(&data_021cb5a0) > 0 ? 1 : -1;
    return (s16) AquariumSwim_mul(DEGREE, AquariumSwim_mul(AquariumSwim_Random(low, high), sign));
}
CLEAN_AS(func_ov004_02239474, AquariumSwim_RandomAngle)

/* func_ov004_022394ac: a random number of whole units, `low` up to (not including) `high`, but
 * at least 1. */
fx32 AquariumSwim_RandomUnits(int low, int high)
{
    int units = AquariumSwim_Random(low, high);
    if (units == 0) {
        units = 1;
    }
    return (fx32) ((u32) units << 12);
}
CLEAN_AS(func_ov004_022394ac, AquariumSwim_RandomUnits)

/* A climbing or diving fish levels off once it slows down, or once it reaches its top
 * (climbing) or its bottom (diving). */
static void AquariumSwim_check_levelling(AquariumFish *fish)
{
    if (fish->mode == AQUARIUM_MODE_SLOW_DOWN) {
        fish->levelling = 1;
        return;
    }
    int vertical = fish->vertical;
    if ((vertical == 1 && fish->position.y == fish->level) || (vertical == -1 && fish->position.y == fish->swim_228)) {
        fish->levelling = 1;
    }
}

/* Fleeing or setting off, a fish's pitch is left as it is. */
static int AquariumSwim_keeps_pitch(const AquariumFish *fish)
{
    return (u8) (fish->mode - 1) <= 1;
}

/* func_ov004_02239524: the fish's pitch eases (a quarter of what is left, at most 0x186 a frame)
 * towards `most` tilted the way it climbs or dives, then levels off (a third a frame) once
 * AquariumSwim_check_levelling says so; not while fleeing or setting off. */
void AquariumSwim_TiltEased(AquariumFish *fish, int most)
{
    if (AquariumSwim_keeps_pitch(fish)) {
        return;
    }
    if (fish->levelling) {
        if (fish->pitch == 0) {
            return;
        }
        Approach_DivideS16(&fish->pitch, 0, 3, TILT_STEP);
        return;
    }
    Approach_DivideS16(&fish->pitch, (s16) AquariumSwim_mul(AquariumSwim_neg(most), fish->vertical), 4, TILT_STEP);
    AquariumSwim_check_levelling(fish);
}
CLEAN_AS(func_ov004_02239524, AquariumSwim_TiltEased)

/* func_ov004_022395d0: the fish's pitch is its tilt steps times its speed (by `rate`, in
 * thousandths of a unit), against the way it climbs or dives, kept within `most`. The steps
 * grow each frame until it levels off (AquariumSwim_check_levelling), then shrink while it is
 * still tilted; not while fleeing or setting off. */
void AquariumSwim_TiltBySpeed(AquariumFish *fish, int most, int rate)
{
    if (AquariumSwim_keeps_pitch(fish)) {
        return;
    }
    int steps = AquariumSwim_mul(AquariumSwim_neg(fish->pitch_steps), fish->vertical);
    fish->pitch = (s16) AquariumSwim_mul(steps, AquariumSwim_mul(fish->speed, rate) >> 12);
    if (fish->pitch <= AquariumSwim_neg(most)) {
        fish->pitch = (s16) AquariumSwim_neg(most);
    } else if (fish->pitch >= most) {
        fish->pitch = (s16) most;
    }
    if (fish->levelling) {
        if (fish->pitch == 0) {
            return;
        }
        fish->pitch_steps = AquariumSwim_add(fish->pitch_steps, -1);
    } else {
        fish->pitch_steps = AquariumSwim_add(fish->pitch_steps, 1);
        AquariumSwim_check_levelling(fish);
    }
}
CLEAN_AS(func_ov004_022395d0, AquariumSwim_TiltBySpeed)

/* func_ov004_022396a0: speeding up the fish's pitch eases (a third a frame, at most 0x222)
 * towards 0x1aa9 against the way it climbs or dives; slowing down, back to level; not while
 * fleeing or setting off. */
void AquariumSwim_TiltFixed(AquariumFish *fish)
{
    u8 mode = fish->mode;
    if ((u8) (mode - 1) <= 1) {
        return;
    }
    if (mode == AQUARIUM_MODE_SPEED_UP) {
        Approach_DivideS16(&fish->pitch, (s16) AquariumSwim_mul(-TILT_FIXED, fish->vertical), 3, TILT_FIXED_STEP);
    } else if (mode == AQUARIUM_MODE_SLOW_DOWN) {
        Approach_DivideS16(&fish->pitch, 0, 3, TILT_FIXED_STEP);
    }
}
CLEAN_AS(func_ov004_022396a0, AquariumSwim_TiltFixed)

/* func_ov004_02239700: kinds 45 and 46, and a fish paying attention to nobody, climb or dive
 * within their own heights (AquariumSwim_Climb); a fish paying attention to another climbs at
 * 0x7b a frame with its top at 5.0. */
void AquariumSwim_ClimbByFocus(AquariumFish *fish)
{
    if ((u32) fish->index - (u32) KIND_FISH_45 <= 1 || fish->focus == fish->index) {
        AquariumSwim_ClimbWithin(fish, fish->swim_224, fish->level, fish->swim_228);
    } else {
        AquariumSwim_ClimbWithin(fish, FOCUS_CLIMB_STEP, FOCUS_CLIMB_TOP, fish->swim_228);
    }
}
CLEAN_AS(func_ov004_02239700, AquariumSwim_ClimbByFocus)

/* func_ov004_02239768: the fish climbs or dives at its vertical speed within its own heights
 * (level down to swim_228). */
void AquariumSwim_Climb(AquariumFish *fish)
{
    AquariumSwim_ClimbWithin(fish, fish->swim_224, fish->level, fish->swim_228);
}
CLEAN_AS(func_ov004_02239768, AquariumSwim_Climb)

/* func_ov004_02239790: the fish climbs or dives `step` a frame; above `top` it goes back towards
 * its level, below `bottom` towards its bottom (swim_228), `step` a frame.
 * QUIRK: above `top` it goes towards its level, not to `top`. */
void AquariumSwim_ClimbWithin(AquariumFish *fish, int step, fx32 top, fx32 bottom)
{
    int *y = (int *) (void *) &fish->position.y;
    *y = AquariumSwim_add(*y, AquariumSwim_mul(step, fish->vertical));
    if (*y > top) {
        Approach_S32(y, fish->level, step);
    } else if (*y < bottom) {
        Approach_S32(y, fish->swim_228, step);
    }
}
CLEAN_AS(func_ov004_02239790, AquariumSwim_ClimbWithin)

/* func_ov004_022397ec: the fish straightens and its turn from the glass is made a turn round
 * at its next course. 0x1fd.
 * QUIRK: the result is the offset of the field it set, left over in the game's code. */
int AquariumSwim_TurnRound(AquariumFish *fish)
{
    AquariumSwim_Straighten(fish);
    fish->glass_turn = AQUARIUM_GLASS_ROUND;
    return (int) offsetof(AquariumFish, glass_turn);
}
CLEAN_AS(func_ov004_022397ec, AquariumSwim_TurnRound)

/* func_ov004_02239804: the fish's first animation plays again; it no longer bends. 0x22e.
 * QUIRK: the result is the offset of the field it set, left over in the game's code. */
int AquariumSwim_Straighten(AquariumFish *fish)
{
    AquariumSwim_PlayAnim(fish, 0);
    ((AquariumSwimmer *) fish)->bend.bending = 0;
    return (int) offsetof(AquariumSwimmer, bend.bending);
}
CLEAN_AS(func_ov004_02239804, AquariumSwim_Straighten)

/* func_ov004_02239820: the fish's joint animation `anim` plays, blended in over 2 frames, at
 * full speed from its start. */
void AquariumSwim_PlayAnim(AquariumFish *fish, int anim)
{
    u8 *track = func_02107b44(NNS_G3dGetJntAnmSet(fish->anims[anim]), 0);
    AnimatedModel_Play(&fish->model, track, 2, 0, ONE, 0, 0);
}
CLEAN_AS(func_ov004_02239820, AquariumSwim_PlayAnim)

/* func_ov004_02239858: a fish of three animations whose bending animation reaches its last
 * frame straightens. Whether it did. */
int AquariumSwim_EndBend(AquariumFish *fish)
{
    if (fish->unk_1c6 != 0 && ((AquariumSwimmer *) fish)->bend.bending != 0) {
        u32 last = ((u32) fish->model.frames.end << 4) >> 16;
        if (FrameCtrl_Passed(&fish->model.frames, (int) last)) {
            AquariumSwim_Straighten(fish);
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_02239858, AquariumSwim_EndBend)

/* Once the fish's animation passes `frame`, it goes back to the frame before. */
static void AquariumSwim_hold(AquariumFish *fish, int frame)
{
    if (FrameCtrl_Passed(&fish->model.frames, frame)) {
        fish->model.frames.frame = (fx32) ((u32) (u16) (frame - 1) << 12);
    }
}

/* func_ov004_022398a8: the fish bends as it turns: its animation is held at `frame`; a fish of
 * three animations not bending yet starts its bending animation (2 for frame 10, else 1) at the
 * end of the one playing. */
void AquariumSwim_Bend(AquariumFish *fish, int frame)
{
    AquariumSwimmer *swimmer = (AquariumSwimmer *) fish;
    if (fish->unk_1c6 == 0 || swimmer->bend.bending) {
        AquariumSwim_hold(fish, frame);
        return;
    }
    if (FrameCtrl_Passed(&fish->model.frames, AquariumSwim_before_last_frame(fish))) {
        AquariumSwim_PlayAnim(fish, frame == AQUARIUM_BEND_LEFT ? 2 : 1);
        swimmer->bend.bending = 1;
    }
}
CLEAN_AS(func_ov004_022398a8, AquariumSwim_Bend)

/* func_ov004_02239944: the fish's turn from the glass: glass_step a random `low` up to (not
 * including) `high` degrees, and the way it bends. A fish heading towards +x and +z or -x and
 * -z turns left (glass_step negative) when `x_first`, else right; the other headings the other
 * way round. */
void AquariumSwim_StartGlassTurn(AquariumFish *fish, int x_first, int low, int high)
{
    fish->glass_step = (s16) AquariumSwim_mul(AquariumSwim_Random((u16) low, (u16) high), DEGREE);
    int same_signs = FX_MulFunc(AquariumSwim_sin(fish->yaw), AquariumSwim_cos(fish->yaw)) >= 0;
    if ((x_first != 0) == same_signs) {
        fish->glass_step = (s16) -fish->glass_step;
        fish->unk_1fe = AQUARIUM_BEND_LEFT;
    } else {
        fish->unk_1fe = AQUARIUM_BEND_RIGHT;
    }
}
CLEAN_AS(func_ov004_02239944, AquariumSwim_StartGlassTurn)

/* The point its radius ahead of the fish. */
static void AquariumSwim_ahead(const AquariumFish *fish, Vec3 *ahead)
{
    *ahead = fish->position;
    AquariumSwim_Move(ahead, (fx32) data_ov004_02247924[fish->index].body_radius << 5, fish->yaw);
}

/* func_ov004_022399ec (near the glass of a river tank): unless fleeing. A new turn is a turn by
 * glass_step a frame three times in four, else a turn round at its next course; after four
 * turns round in a row it turns by glass_step. Turning, a fish slowing down cruises again; the
 * turn begun, it turns away from the side along which the tank's edge is nearer
 * (AquariumSwim_EdgeNearerAlongX) by 2 to 5 degrees a frame, bending, and stops turning to its
 * course; cruising its timer starts again. Once it has turned half a turn (glass_turned
 * wraps), it is to turn round instead, unless it is still bending. A fish to turn round
 * straightens at the end of its bending animation. */
void AquariumSwim_TurnFromGlass(AquariumFish *fish)
{
    AquariumSwimmer *swimmer = (AquariumSwimmer *) fish;
    if (fish->mode == AQUARIUM_MODE_FLEE) {
        return;
    }
    if (fish->glass_turn == AQUARIUM_GLASS_NONE) {
        if (AquariumSwim_Random(0, 100) < 75) {
            fish->glass_turn = AQUARIUM_GLASS_TURN;
        } else {
            fish->glass_turn = AQUARIUM_GLASS_ROUND;
            return;
        }
    } else if (fish->turnbacks >= 4) {
        fish->glass_turn = AQUARIUM_GLASS_TURN;
        fish->glass_turning = 0;
        fish->turnbacks = 0;
    }
    if (fish->glass_turn == AQUARIUM_GLASS_TURN) {
        if (fish->mode == AQUARIUM_MODE_SLOW_DOWN) {
            fish->mode = AQUARIUM_MODE_CRUISE;
        }
        if (!fish->glass_turning) {
            Vec3 ahead;
            AquariumSwim_ahead(fish, &ahead);
            AquariumSwim_StartGlassTurn(fish, AquariumSwim_EdgeNearerAlongX(&ahead, fish->yaw), 2, 6);
            fish->glass_turning = 1;
            swimmer->glass.glass_turned = fish->glass_step;
        }
        if (fish->glass_step * swimmer->glass.glass_turned < 0) {
            if (AquariumSwim_EndBend(fish)) {
                fish->glass_turn = AQUARIUM_GLASS_ROUND;
            } else if (fish->unk_1c6 == 0) {
                fish->glass_turn = AQUARIUM_GLASS_ROUND;
            } else if (fish->unk_1c6 == 1 && !swimmer->bend.bending) {
                fish->glass_turn = AQUARIUM_GLASS_ROUND;
            }
        } else {
            fish->turning = 0;
            fish->yaw = (s16) (fish->yaw + fish->glass_step);
            swimmer->glass.glass_turned = (s16) (swimmer->glass.glass_turned + fish->glass_step);
            AquariumSwim_Bend(fish, (u16) (s8) fish->unk_1fe);
            if (fish->mode == AQUARIUM_MODE_CRUISE) {
                fish->timer = 0;
            }
        }
    } else if (fish->glass_turn == AQUARIUM_GLASS_ROUND) {
        AquariumSwim_EndBend(fish);
    }
}
CLEAN_AS(func_ov004_022399ec, AquariumSwim_TurnFromGlass)

/* func_ov004_02239b80 (a river fish's frame): near the glass ahead it turns from it; else its
 * turn ends, and it straightens at the end of its bending animation. */
void AquariumSwim_WatchGlass(AquariumFish *fish)
{
    if (AquariumSwim_NearGlass(fish)) {
        AquariumSwim_TurnFromGlass(fish);
    } else {
        fish->glass_turning = 0;
        fish->glass_turn = AQUARIUM_GLASS_NONE;
        AquariumSwim_EndBend(fish);
    }
}
CLEAN_AS(func_ov004_02239b80, AquariumSwim_WatchGlass)

/* func_ov004_022392a0: whether the point its radius ahead of a river fish comes within 0.25 of
 * the glass of its tank (1.0 once it is turning from it): the fish's tank is the first for the
 * kinds below 17 and kind 25, else the second. */
int AquariumSwim_NearGlass(AquariumFish *fish)
{
    Vec3 ahead;
    AquariumSwim_ahead(fish, &ahead);
    fx32 near = fish->glass_turning ? GLASS_NEAR_TURNING : GLASS_NEAR;
    int kind = fish->index;
    const Vec3 *tank = (kind == KIND_FISH_25 || kind < FIRST_SECOND_TANK_KIND) ? &data_ov004_022593dc : &data_ov004_022593c4;
    return CollisionQuery_ClampToRect(&ahead, near, tank, GLASS_INNER_WIDTH, GLASS_INNER_DEPTH) != 0;
}
CLEAN_AS(func_ov004_022392a0, AquariumSwim_NearGlass)

/* func_ov004_02239354: whether the ground under `point` is at height 0.5. */
int AquariumSwim_GroundIsHalf(const Vec3 *point)
{
    CollisionGround ground;
    CollisionGround_Init(&ground, point, 0, 0);
    int half = CollisionGround_GetHeight(&ground, 0) == TANK_GROUND;
    CollisionGround_Destroy(&ground);
    return half;
}
CLEAN_AS(func_ov004_02239354, AquariumSwim_GroundIsHalf)

/* func_ov004_0223938c: stepping out from `point` 0.2 at a time (up to 9.8), along x on the side
 * `yaw` heads to and along z likewise in turn, whether the ground stops being at 0.5 along x
 * first. */
int AquariumSwim_EdgeNearerAlongX(const Vec3 *point, int yaw)
{
    int x_step = yaw < 0 ? -2 : 2;
    int size = yaw < 0 ? AquariumSwim_neg(yaw) : yaw;
    int z_step = size > 0x4000 ? -2 : 2;
    for (int i = 0; i < 50; i++) {
        Vec3 at = *point;
        at.x = AquariumSwim_add(point->x, x_step * i * ONE / 10);
        if (!AquariumSwim_GroundIsHalf(&at)) {
            return 1;
        }
        at.x = point->x;
        at.z = AquariumSwim_add(point->z, z_step * i * ONE / 10);
        if (!AquariumSwim_GroundIsHalf(&at)) {
            return 0;
        }
    }
    return 0;
}
CLEAN_AS(func_ov004_0223938c, AquariumSwim_EdgeNearerAlongX)

/* func_ov004_02239bb4: `point` moved `distance` along `yaw` in the ground plane; its new z. */
int AquariumSwim_Move(Vec3 *point, fx32 distance, int yaw)
{
    AquariumSwim_MoveX(&point->x, distance, yaw);
    return AquariumSwim_MoveZ(&point->z, distance, yaw);
}
CLEAN_AS(func_ov004_02239bb4, AquariumSwim_Move)

/* func_ov004_02239bd4: `z` moved `distance` times the cosine of `yaw`; its new value. */
fx32 AquariumSwim_MoveZ(fx32 *z, fx32 distance, int yaw)
{
    *z = AquariumSwim_add(*z, FX_MulFunc(distance, AquariumSwim_cos(yaw)));
    return *z;
}
CLEAN_AS(func_ov004_02239bd4, AquariumSwim_MoveZ)

/* func_ov004_02239c00: `x` moved `distance` times the sine of `yaw`. */
void AquariumSwim_MoveX(fx32 *x, fx32 distance, int yaw)
{
    *x = AquariumSwim_add(*x, FX_MulFunc(distance, AquariumSwim_sin(yaw)));
}
CLEAN_AS(func_ov004_02239c00, AquariumSwim_MoveX)

/* func_ov004_02239c28: the fish body's destructor. */
AquariumFishBody *AquariumFishBody_Destruct(AquariumFishBody *body)
{
    body->base.body.vtable = data_ov004_02255d28;
    FieldPointBody_Destruct(&body->base);
    return body;
}
CLEAN_AS(func_ov004_02239c28, AquariumFishBody_Destruct)

/* func_ov004_02239c40: the fish body's constructor: a body at a point, of no fish yet. */
AquariumFishBody *AquariumFishBody_Construct(AquariumFishBody *body)
{
    FieldPointBody_Construct2(&body->base);
    body->base.body.vtable = data_ov004_02255d28;
    body->owner = NULL;
    return body;
}
CLEAN_AS(func_ov004_02239c40, AquariumFishBody_Construct)
