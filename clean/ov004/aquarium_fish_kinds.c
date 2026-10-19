/* The aquarium's fish that swim in a way of their own (aquarium_fish_kinds.h). */
#include "aquarium_fish_kinds.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "clean.h"
#include "main/actor.h"
#include "main/collision_query.h"
#include "main/field_body.h"
#include "main/frame_ctrl.h"
#include "main/model_object.h"
#include "main/player_actor_ops.h"
#include "main/session_players.h"
#include "member_pointer.h"
#include "aquarium_swim.h"

static_assert(sizeof(AquariumKind10) == sizeof(AquariumFish), "kind 10 view");
static_assert(offsetof(AquariumKind10, own.home) == 0x1fc, "kind 10 home");
static_assert(offsetof(AquariumKind10, own.speed) == 0x20c, "kind 10 speed");
static_assert(offsetof(AquariumKind10, own.rest_frames) == 0x212, "kind 10 rest");
static_assert(offsetof(AquariumKind10, own.anim_speed) == 0x218, "kind 10 anim speed");
static_assert(offsetof(AquariumKind10, own.state) == 0x21c, "kind 10 state");
static_assert(offsetof(AquariumKind47, own.second_anim) == 0x256, "kind 47 anim");
static_assert(offsetof(AquariumHomeFish, own.at_home) == 0x255, "home fish at home");
static_assert(offsetof(AquariumHomeFish, own.home) == 0x258, "home fish home");
static_assert(offsetof(AquariumHomeFish, own.rest_point) == 0x264, "home fish rest point");
static_assert(offsetof(AquariumHomeFish, own.since_rest) == 0x278, "home fish since rest");
static_assert(sizeof(AquariumHomeFish) == 0x27c, "home fish");
static_assert(offsetof(AquariumRisingFish, own.came_down) == 0x259, "rising fish came down");
static_assert(offsetof(AquariumKind30, own.count) == 0x259, "kind 30 count");
static_assert(offsetof(AquariumKind40, own.held) == 0x258, "kind 40 held");

/* What each kind is like, and the fish by kind (museum_aquarium.c). */
extern const AquariumFishInfo data_ov004_02247924[];
extern AquariumFish *data_ov004_022594d4[AQUARIUM_FISH_KINDS];
/* The river room's second tank's centre. */
extern Vec3 data_ov004_022593c4;
/* The member functions of the modes, and of kind 30's states. */
extern const MemberPointer data_ov004_0225949c[7];
extern const MemberPointer data_ov004_022593f4[3];

extern const s16 FX_SinCosTable_[];
extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* The model hook handed to the game (aquarium_fish.c). */
extern void func_ov004_0223653c(G3dRenderState *state);

#define ONE 0x1000

/* The kinds with classes of two kinds. */
#define KIND_FISH_12 12
#define KIND_FISH_30 30
#define KIND_FISH_38 38

/* The sea tank's front and back glass (z), and the part of the room past which kind 47 does
 * not mind it (x). */
#define SEA_GLASS_NEAR 0x11000
#define SEA_GLASS_FAR 0x15dc2
#define SEA_GLASS_LEFT 0x4000
#define SEA_GLASS_RIGHT 0x1e000

/* The height of the surface for the rising fish and for kind 30. */
#define SURFACE 0x299a
#define KIND30_HEIGHT 0x199a

/* How far from the player kind 30 notices, and snaps (squared distances in the ground plane). */
#define PLAYER_NEAR 0x10000
#define PLAYER_CLOSE 0x4000

/* This system's player. */
#define OWN_PLAYER 4

static int Kinds_mul(int a, int b)
{
    return (int) ((u32) a * (u32) b);
}

static int Kinds_shl(int value, int shift)
{
    return (int) ((u32) value << shift);
}

static fx32 Kinds_sin(u16 angle)
{
    return FX_SinCosTable_[(angle >> 4) * 2];
}

static fx32 Kinds_cos(u16 angle)
{
    return FX_SinCosTable_[(angle >> 4) * 2 + 1];
}

/* The fish's position, by address (the fish may be missing, as the game's code allows). */
static const Vec3 *Kinds_position_of(AquariumFish *fish)
{
    return (const Vec3 *) ((uintptr_t) fish + offsetof(AquariumFish, position));
}

/* The member function of the fish's mode. */
static void Kinds_run_mode(AquariumFish *fish)
{
    MemberPointer_CallVoid(&data_ov004_0225949c[fish->mode], fish);
}

/* The last frame of the fish's animation, less `back`, as FrameCtrl_Passed takes it. */
static u16 Kinds_last_frame(AquariumFish *fish, int back)
{
    u32 frames = ((u32) fish->model.frames.end << 4) >> 16;
    return (u16) (frames - (u32) back);
}

/* A fish paying attention to a new one is startled away from it, unless it flees already. */
static void Kinds_startle_from_new_focus(AquariumFish *fish)
{
    u8 focus = fish->focus;
    if (fish->last_focus != focus && focus != fish->index) {
        fish->last_focus = focus;
        if (fish->mode != AQUARIUM_MODE_FLEE) {
            AquariumFish_Startle(fish, Kinds_position_of(data_ov004_022594d4[fish->focus]));
        }
    }
}

/* func_ov004_0223687c (slot 0 of kind 48's class): it has no body, and stays at
 * (22.94, -0.75, 19.19) facing +z. The fish. */
AquariumFish *AquariumKind48_SetUp(AquariumFish *fish)
{
    fish->solid = 0;
    fish->position.x = 0x16f00;
    fish->position.y = -0xc00;
    fish->position.z = 0x13300;
    fish->yaw = 0;
    return fish;
}
CLEAN_AS(func_ov004_0223687c, AquariumKind48_SetUp)

/* func_ov004_022368bc: within the room's length (x 4.0 to 30.0), a fish reaching the sea tank's
 * front or back glass with an end of it (its radius times 1.5 from its position along z),
 * while heading for it or already turning, turns from it, unless it met others (fleeing, it
 * stops turning). A new turn is a turn by glass_step a frame three times in four, else a turn
 * round at its next course; after two turns round in a row it turns by glass_step. The turn
 * begun, the fish turns the other way a fifth of the time in the middle of the room
 * (x 11.0 to 23.0). While it turns it stops turning to its course, and a fish slowing down
 * cruises again.
 * QUIRK: while it turns, the near glass is tested with its far end. */
void AquariumKind47_TurnAtGlass(AquariumFish *fish)
{
    fx32 reach = FX_MulFunc(0x1800, (fx32) data_ov004_02247924[fish->index].body_radius << 5);
    fx32 far_end = (fx32) ((u32) fish->position.z + (u32) reach);
    fx32 near_end = (fx32) ((u32) fish->position.z - (u32) reach);
    if (fish->position.x < SEA_GLASS_LEFT || fish->position.x > SEA_GLASS_RIGHT) {
        return;
    }
    if (fish->mode == AQUARIUM_MODE_FLEE) {
        fish->glass_turning = 0;
        fish->glass_turn = AQUARIUM_GLASS_NONE;
        return;
    }
    int size = fish->yaw < 0 ? -fish->yaw : fish->yaw;
    s16 heading = (s16) size; /* QUIRK: a yaw of -0x8000 counts as heading for the far glass */
    int turning = fish->glass_turning;
    int at_glass = (far_end >= SEA_GLASS_FAR && turning) || (far_end <= SEA_GLASS_NEAR && turning) ||
                   (far_end >= SEA_GLASS_FAR && heading < 0x4000 && !turning) ||
                   (near_end <= SEA_GLASS_NEAR && heading > 0x4000 && !turning);
    if (!at_glass || fish->meetings) {
        fish->glass_turning = 0;
        fish->glass_turn = AQUARIUM_GLASS_NONE;
        return;
    }
    if (fish->glass_turn == AQUARIUM_GLASS_NONE) {
        if (AquariumSwim_Random(0, 100) < 75) {
            fish->glass_turn = AQUARIUM_GLASS_TURN;
        } else {
            fish->glass_turn = AQUARIUM_GLASS_ROUND;
            return;
        }
    } else if (fish->turnbacks >= 2) {
        fish->glass_turn = AQUARIUM_GLASS_TURN;
        fish->glass_turning = 0;
        fish->turnbacks = 0;
    }
    if (fish->glass_turn == AQUARIUM_GLASS_TURN) {
        if (!fish->glass_turning) {
            AquariumSwim_StartGlassTurn(fish, 0, 1, 4);
            fish->glass_turning = 1;
            if (fish->position.x >= 0xb000 && fish->position.x <= 0x17000 && AquariumSwim_Random(0, 100) < 20) {
                fish->glass_step = (s16) -fish->glass_step;
            }
        }
        fish->turning = 0;
        fish->yaw = (s16) (fish->yaw + fish->glass_step);
        if (fish->mode == AQUARIUM_MODE_SLOW_DOWN) {
            fish->mode = AQUARIUM_MODE_CRUISE;
            fish->timer = 0;
        }
    }
}
CLEAN_AS(func_ov004_022368bc, AquariumKind47_TurnAtGlass)

/* The fish's first animation again; its mode runs again. */
static void AquariumKind47_back_to_first(AquariumKind47 *fish)
{
    fish->own.second_anim = 0;
    AquariumSwim_PlayAnim(&fish->base, 0);
    fish->own.may_swim = 1;
}

/* func_ov004_02236a78 (slot 1 of kind 47's class): at the end of its first animation the second
 * plays; when it sets off, its mode waits for the end of the animation, and the first plays
 * again. While its mode runs it turns at the glass, and cruising it climbs or dives. Unless
 * resting or slowing down it turns to its course; its animation speed (at least 0.8, 0.4 in
 * the second animation), the room's and the tank's ends, whom it pays attention to, its timer;
 * a tap on the glass plays its first animation again. */
void AquariumKind47_Swim(AquariumKind47 *fish)
{
    AquariumFish *base = &fish->base;
    if (!fish->own.second_anim && FrameCtrl_Passed(&base->model.frames, Kinds_last_frame(base, 1))) {
        fish->own.second_anim = 1;
        AquariumSwim_PlayAnim(base, 1);
    }
    if (base->mode == AQUARIUM_MODE_NEW_COURSE) {
        fish->own.may_swim = 0;
        if (FrameCtrl_Passed(&base->model.frames, Kinds_last_frame(base, 1))) {
            AquariumKind47_back_to_first(fish);
        }
    } else if (fish->own.may_swim == 0) {
        fish->own.may_swim = 1;
    }
    if (fish->own.may_swim) {
        Kinds_run_mode(base);
        AquariumKind47_TurnAtGlass(base);
        if (base->mode == AQUARIUM_MODE_CRUISE) {
            AquariumSwim_ClimbByFocus(base);
            AquariumSwim_TiltEased(base, 0x1554);
        }
    }
    if (base->mode != AQUARIUM_MODE_REST && base->mode != AQUARIUM_MODE_SLOW_DOWN) {
        AquariumFish_Turn(base);
    }
    AquariumFish_SetAnimSpeed(base, !fish->own.second_anim ? 0xccd : 0x666);
    AquariumFish_KeepOffRoomEnds(base);
    AquariumFish_ReactToFocus(base);
    AquariumFish_TurnAtTankEnds(base);
    base->timer++;
    if (AquariumFish_CheckTapped(base)) {
        AquariumKind47_back_to_first(fish);
    }
}
CLEAN_AS(func_ov004_02236a78, AquariumKind47_Swim)

/* func_ov004_02236bd4 (slot 0 of kind 47's class): it is its body's owner, pays attention to
 * and makes way for nobody, keeps to area 1; its swimming values and model hooks. */
void AquariumKind47_SetUp(AquariumKind47 *fish)
{
    fish->base.body.owner = &fish->base;
    fish->base.focus = (u8) fish->base.index;
    fish->base.yield_to = (u8) fish->base.index;
    fish->base.area = 1;
    AquariumFish_SetSwim(&fish->base);
    ModelObject_SetInitHook(&fish->base.model.object, (void *) (uintptr_t) func_ov004_0223653c, fish);
}
CLEAN_AS(func_ov004_02236bd4, AquariumKind47_SetUp)

/* Kind 10 moved `speed` along its yaw and seven tenths of it along its sway, the sway turned an
 * eighth of a turn on.
 * BUG: the sway's z uses the sine of its angle as x does (BUGFIX: its cosine). */
static void AquariumKind10_move(AquariumKind10 *fish, fx32 speed)
{
    AquariumFish *base = &fish->base;
    base->position.x += FX_MulFunc(speed, Kinds_sin((u16) base->yaw));
    base->position.z += FX_MulFunc(speed, Kinds_cos((u16) base->yaw));
    fish->own.sway = (s16) (fish->own.sway + 0x2000);
    fx32 sway = Kinds_mul(speed, 7) / 10;
    base->position.x += FX_MulFunc(sway, Kinds_sin((u16) fish->own.sway));
#ifdef BUGFIX
    base->position.z += FX_MulFunc(sway, Kinds_cos((u16) fish->own.sway));
#else
    base->position.z += FX_MulFunc(sway, Kinds_sin((u16) fish->own.sway));
#endif
}

/* func_ov004_02236c1c (kind 10 gliding): it slows by 1/512 a frame for each frame it has
 * glided; stopped, it rests (its animation still). */
void AquariumKind10_Glide(AquariumKind10 *fish)
{
    fx32 speed = (fx32) ((u32) fish->own.speed - ((u32) fish->base.timer << 3));
    if (speed < 0) {
        speed = 0;
        fish->base.timer = 0;
        fish->base.model.frames.speed = 0;
        fish->own.state = AQUARIUM_KIND10_REST;
    }
    AquariumKind10_move(fish, speed);
}
CLEAN_AS(func_ov004_02236c1c, AquariumKind10_Glide)

/* func_ov004_02236cfc (kind 10 darting): it turns back towards its home from 1.375 away and
 * moves at its speed; after its darting time it glides, its animation at half speed. */
void AquariumKind10_Dart(AquariumKind10 *fish)
{
    AquariumSwim_TurnTowards(&fish->base.yaw, &fish->base.position, &fish->own.home, 0x1600);
    AquariumKind10_move(fish, fish->own.speed);
    if (fish->base.timer >= fish->own.dart_frames) {
        fish->base.timer = 0;
        fish->own.state = AQUARIUM_KIND10_GLIDE;
        fish->own.anim_speed >>= 1;
        fish->base.model.frames.speed = fish->own.anim_speed;
    }
}
CLEAN_AS(func_ov004_02236cfc, AquariumKind10_Dart)

/* func_ov004_02236e0c (kind 10 starting): it turns up to 90 degrees either way and darts at a
 * random speed (2 or 3 hundredths a frame) for 20 to 119 frames, then is to rest 60 to 239;
 * at height 0.4375, its animation at full speed. */
void AquariumKind10_StartDart(AquariumKind10 *fish)
{
    fish->base.yaw = (s16) (fish->base.yaw + AquariumSwim_RandomAngle(90, 0));
    fish->own.dart_frames = (u8) AquariumSwim_Random(20, 120);
    fish->own.rest_frames = (u16) AquariumSwim_Random(60, 240);
    fish->own.speed = AquariumSwim_RandomUnits(2, 4) / 100;
    fish->base.timer = 0;
    fish->base.position.y = 0x700;
    fish->own.anim_speed = ONE;
    fish->base.model.frames.speed = fish->own.anim_speed;
    fish->own.state = AQUARIUM_KIND10_DART;
}
CLEAN_AS(func_ov004_02236e0c, AquariumKind10_StartDart)

/* func_ov004_02236e9c (slot 1 of kind 10's class): its state runs (a rest ends after its rest
 * time), and its timer. */
void AquariumKind10_Swim(AquariumKind10 *fish)
{
    switch (fish->own.state) {
        case AQUARIUM_KIND10_START:
            AquariumKind10_StartDart(fish);
            break;
        case AQUARIUM_KIND10_DART:
            AquariumKind10_Dart(fish);
            break;
        case AQUARIUM_KIND10_GLIDE:
            AquariumKind10_Glide(fish);
            break;
        case AQUARIUM_KIND10_REST:
            if (fish->base.timer >= fish->own.rest_frames) {
                fish->base.timer = 0;
                fish->own.state = AQUARIUM_KIND10_START;
            }
            break;
    }
    fish->base.timer++;
}
CLEAN_AS(func_ov004_02236e9c, AquariumKind10_Swim)

/* func_ov004_02236f0c (slot 0 of kind 10's class): its home (12.5, 0, 20.625), where the
 * aquarium places it. The fish. */
AquariumKind10 *AquariumKind10_SetUp(AquariumKind10 *fish)
{
    fish->own.home.x = 0xc800;
    fish->own.home.y = 0;
    fish->own.home.z = 0x14a00;
    return fish;
}
CLEAN_AS(func_ov004_02236f0c, AquariumKind10_SetUp)

/* func_ov004_02236f34 (resting at the rest point): it keeps moving onto it at its top speed;
 * after its rest it sets off again. */
void AquariumHomeFish_Settle(AquariumHomeFish *fish)
{
    Approach_S32((int *) (void *) &fish->base.position.x, fish->own.rest_point.x, fish->base.top_speed);
    Approach_S32((int *) (void *) &fish->base.position.z, fish->own.rest_point.z, fish->base.top_speed);
    if (fish->base.timer > fish->own.rest_frames) {
        fish->own.homing = AQUARIUM_HOMING_OFF;
        fish->base.timer = 0;
        fish->base.mode = AQUARIUM_MODE_NEW_COURSE;
    }
}
CLEAN_AS(func_ov004_02236f34, AquariumHomeFish_Settle)

/* func_ov004_02236fa0: a fish away from its home stops going to rest (noting its own kind as
 * the focus it reacted to). Otherwise it sinks to the rest point's height (four times as fast
 * when `hurry`); within 0.5 of the point and down to it, it rests there 60 to 119 frames; else
 * it heads for the point at twice its top speed when `hurry`, else half. */
void AquariumHomeFish_GoToRest(AquariumHomeFish *fish, int hurry)
{
    AquariumFish *base = &fish->base;
    if (fish->own.at_home == 0) {
        base->last_focus = (u8) base->index;
        fish->own.homing = AQUARIUM_HOMING_OFF;
        return;
    }
    if (base->position.y > fish->own.rest_point.y) {
        Approach_S32((int *) (void *) &base->position.y, fish->own.rest_point.y,
                     hurry ? Kinds_shl(base->swim_224, 2) : base->swim_224);
    }
    if (Vec_Distance(&base->position, &fish->own.rest_point) <= 0x800) {
        if (base->position.y <= fish->own.rest_point.y) {
            fish->own.homing = AQUARIUM_HOMING_REST;
            base->timer = 0;
            fish->own.rest_frames = AquariumSwim_Random(60, 120);
        }
    } else {
        base->yaw = Vec_YawTo(&base->position, &fish->own.rest_point);
        AquariumSwim_Move(&base->position, hurry ? Kinds_shl(base->top_speed, 1) : base->top_speed >> 1, base->yaw);
    }
}
CLEAN_AS(func_ov004_02236fa0, AquariumHomeFish_GoToRest)

/* func_ov004_02237094: going to its rest point it hurries once it pays attention to a new fish;
 * at the point it rests. */
void AquariumHomeFish_RunHoming(AquariumHomeFish *fish)
{
    switch (fish->own.homing) {
        case AQUARIUM_HOMING_GO: {
            AquariumHomeFish_GoToRest(fish, 0);
            u8 focus = fish->base.focus;
            if (fish->base.last_focus != focus && focus != fish->base.index) {
                fish->base.last_focus = focus;
                fish->own.homing = AQUARIUM_HOMING_HURRY;
            }
            break;
        }
        case AQUARIUM_HOMING_HURRY:
            AquariumHomeFish_GoToRest(fish, 1);
            break;
        case AQUARIUM_HOMING_REST:
            AquariumHomeFish_Settle(fish);
            break;
    }
}
CLEAN_AS(func_ov004_02237094, AquariumHomeFish_RunHoming)

/* func_ov004_022370f4: a tap on the glass near kind 38 sends it hurrying to its rest point when
 * at home (unless resting there); away from home it startles it. */
void AquariumHomeFish_CheckTapped(AquariumHomeFish *fish)
{
    Vec3 tap;
    if (AquariumFish_FindTap(&fish->base, &tap)) {
        if (fish->own.at_home) {
            if (fish->own.homing != AQUARIUM_HOMING_REST) {
                fish->own.homing = AQUARIUM_HOMING_HURRY;
            }
        } else {
            AquariumFish_Startle(&fish->base, &tap);
        }
    }
}
CLEAN_AS(func_ov004_022370f4, AquariumHomeFish_CheckTapped)

/* func_ov004_02237134 (kind 12's frame): unless setting off or resting it climbs or dives with
 * its pitch; its mode runs and it turns to its course. Within 1.0 of its home it turns from
 * the glass; further, it turns back towards its home (and a turn from the glass ends, the fish
 * setting off). A fish paying attention to a new one is startled away from it; then the
 * stylus. */
void AquariumHomeFish_SwimKind12(AquariumHomeFish *fish)
{
    AquariumFish *base = &fish->base;
    if (base->mode != AQUARIUM_MODE_NEW_COURSE && base->mode != AQUARIUM_MODE_REST) {
        AquariumSwim_Climb(base);
        AquariumSwim_TiltFixed(base);
    }
    Kinds_run_mode(base);
    AquariumFish_Turn(base);
    if (AquariumSwim_TurnTowards(&base->yaw, &base->position, &fish->own.home, ONE)) {
        AquariumSwim_WatchGlass(base);
    } else if (base->glass_turning) {
        base->mode = AQUARIUM_MODE_NEW_COURSE;
        base->glass_turning = 0;
    }
    Kinds_startle_from_new_focus(base);
    AquariumFish_CheckTapped(base);
}
CLEAN_AS(func_ov004_02237134, AquariumHomeFish_SwimKind12)

/* func_ov004_02237218 (kind 38's frame): it notes whether it is within 1.0 of its home. Unless
 * going to rest: it climbs or dives with its pitch (unless setting off or resting), its mode
 * runs and it turns to its course. Near home, every 200 to 319 frames it goes to rest, and a
 * new fish to pay attention to sends it hurrying there; away from home it turns back towards
 * it, and a new fish to pay attention to startles it. Going to rest it does that instead.
 * Then a tap on the glass. */
void AquariumHomeFish_SwimKind38(AquariumHomeFish *fish)
{
    AquariumFish *base = &fish->base;
    fish->own.at_home = Vec_Distance(&base->position, &fish->own.home) <= ONE;
    if (fish->own.homing != AQUARIUM_HOMING_OFF) {
        AquariumHomeFish_RunHoming(fish);
        AquariumHomeFish_CheckTapped(fish);
        return;
    }
    if (base->mode != AQUARIUM_MODE_NEW_COURSE && base->mode != AQUARIUM_MODE_REST) {
        AquariumSwim_ClimbByFocus(base);
        AquariumSwim_TiltEased(base, 0x1554);
    }
    Kinds_run_mode(base);
    AquariumFish_Turn(base);
    if (AquariumSwim_TurnTowards(&base->yaw, &base->position, &fish->own.home, ONE)) {
        if (fish->own.since_rest >= fish->own.rest_interval) {
            fish->own.since_rest = 0;
            fish->own.homing = AQUARIUM_HOMING_GO;
            fish->own.rest_interval = (u32) AquariumSwim_Random(200, 320);
        }
        u8 focus = base->focus;
        if (base->last_focus != focus && focus != base->index) {
            base->last_focus = focus;
            fish->own.homing = AQUARIUM_HOMING_HURRY;
        }
    } else {
        Kinds_startle_from_new_focus(base);
    }
    fish->own.since_rest++;
    AquariumHomeFish_CheckTapped(fish);
}
CLEAN_AS(func_ov004_02237218, AquariumHomeFish_SwimKind38)

/* func_ov004_02237374 (slot 1 of the class of kinds 12 and 38): the kind's frame, its
 * animation speed (at least 0.4) and its timer. The timer's address. */
int *AquariumHomeFish_Swim(AquariumHomeFish *fish)
{
    if (fish->base.index == KIND_FISH_38) {
        AquariumHomeFish_SwimKind38(fish);
    } else if (fish->base.index == KIND_FISH_12) {
        AquariumHomeFish_SwimKind12(fish);
    }
    AquariumFish_SetAnimSpeed(&fish->base, 0x666);
    fish->base.timer++;
    return &fish->base.timer;
}
CLEAN_AS(func_ov004_02237374, AquariumHomeFish_Swim)

static void AquariumHomeFish_set(Vec3 *point, fx32 x, fx32 y, fx32 z)
{
    point->x = x;
    point->y = y;
    point->z = z;
}

/* func_ov004_022373b4 (slot 0 of the class of kinds 12 and 38): it is its body's owner and pays
 * attention to and makes way for nobody; kind 38's home (9.88, 1.0, 20.44, the sea room's
 * second rock) and rest point (10.06, 0.69, 20.63), kind 12's home (21.56, 1.0, 19.56, the
 * river room's fourth rock); its swimming values. */
void AquariumHomeFish_SetUp(AquariumHomeFish *fish)
{
    fish->base.body.owner = &fish->base;
    fish->base.focus = (u8) fish->base.index;
    fish->base.yield_to = (u8) fish->base.index;
    if (fish->base.index == KIND_FISH_38) {
        AquariumHomeFish_set(&fish->own.home, 0x9e00, ONE, 0x14700);
        AquariumHomeFish_set(&fish->own.rest_point, 0xa100, 0xb00, 0x14a00);
    } else if (fish->base.index == KIND_FISH_12) {
        AquariumHomeFish_set(&fish->own.home, 0x15900, ONE, 0x13900);
    }
    AquariumFish_SetSwim(&fish->base);
}
CLEAN_AS(func_ov004_022373b4, AquariumHomeFish_SetUp)

/* func_ov004_02237454 (a rising fish's climb): fleeing, it only sinks (twice its vertical speed,
 * to its bottom). Otherwise its pitch tilts with its climb (more each frame it speeds up, less
 * each frame it slows down, by its speed; at most 0x1554 either way) and it climbs. Going up,
 * after 20 frames cruising above the surface it slows down and comes down at 1.5 times that
 * speed (less its climb); resting it sets off down; once below its top it swims on, having
 * just come down. Its height is kept from its bottom to the surface. */
void AquariumRisingFish_Climb(AquariumRisingFish *fish)
{
    AquariumFish *base = &fish->base;
    switch (base->mode) {
        case AQUARIUM_MODE_SPEED_UP:
            base->pitch_steps++;
            break;
        case AQUARIUM_MODE_SLOW_DOWN:
            base->pitch_steps--;
            break;
        case AQUARIUM_MODE_CRUISE:
            if (!fish->own.stage) {
                base->timer = 0;
            }
            break;
        case AQUARIUM_MODE_FLEE:
            base->position.y = (fx32) ((u32) base->position.y - (u32) Kinds_mul(base->swim_224, 2));
            if (base->position.y < base->swim_228) {
                base->position.y = base->swim_228;
            }
            return;
    }
    int pitch = Kinds_mul((int) (0u - (u32) base->pitch_steps), fish->own.climb);
    pitch = Kinds_mul(pitch, Kinds_mul(base->speed, 1000) >> 12);
    base->pitch = (s16) pitch;
    if (base->pitch <= -0x1554) {
        base->pitch = -0x1554;
    } else if (base->pitch >= 0x1554) {
        base->pitch = 0x1554;
    }
    base->position.y += Kinds_mul(base->swim_224, fish->own.climb);
    switch (fish->own.stage) {
        case 0:
            if (base->position.y > SURFACE && base->mode == AQUARIUM_MODE_CRUISE) {
                fish->own.frames_up++;
                if (fish->own.frames_up >= 20) {
                    base->mode = AQUARIUM_MODE_SLOW_DOWN;
                    fish->own.stage = 1;
                    fish->own.frames_up = 0;
                }
            }
            break;
        case 1:
            base->position.y -= FX_MulFunc(0x1800, Kinds_mul(base->swim_224, fish->own.climb));
            if (base->mode == AQUARIUM_MODE_REST) {
                if (base->position.y < base->level) {
                    fish->own.climb = 1;
                    fish->own.rising = 0;
                    fish->own.stage = 0;
                    fish->own.came_down = 1;
                } else {
                    base->mode = AQUARIUM_MODE_NEW_COURSE;
                    fish->own.climb = -1;
                    fish->own.stage = 2;
                }
            }
            break;
        case 2:
            if (base->position.y < base->level && base->mode == AQUARIUM_MODE_NEW_COURSE) {
                fish->own.climb = 1;
                fish->own.rising = 0;
                fish->own.stage = 0;
                fish->own.came_down = 1;
            }
            break;
    }
    if (base->position.y > SURFACE) {
        base->position.y = SURFACE;
    } else if (base->position.y < base->swim_228) {
        base->position.y = base->swim_228;
    }
}
CLEAN_AS(func_ov004_02237454, AquariumRisingFish_Climb)

/* func_ov004_02237630 (a rising fish rising): its mode runs, then its climb. */
void AquariumRisingFish_Rise(AquariumRisingFish *fish)
{
    Kinds_run_mode(&fish->base);
    AquariumRisingFish_Climb(fish);
}
CLEAN_AS(func_ov004_02237630, AquariumRisingFish_Rise)

/* func_ov004_0223766c (a rising fish swimming on): setting off, it rises instead seven times in
 * ten (just come down, three in twenty, and then it has not). Otherwise its mode runs, it turns
 * from the glass, and unless setting off or resting it climbs or dives with its pitch and
 * turns to its course. */
void AquariumRisingFish_Wander(AquariumRisingFish *fish)
{
    AquariumFish *base = &fish->base;
    if (base->mode == AQUARIUM_MODE_NEW_COURSE) {
        if (fish->own.came_down) {
            if (AquariumSwim_Random(0, 100) < 15) {
                fish->own.rising = 1;
                return;
            }
            fish->own.came_down = 0;
        } else if (AquariumSwim_Random(0, 100) < 70) {
            fish->own.rising = 1;
            return;
        }
    }
    Kinds_run_mode(base);
    AquariumSwim_WatchGlass(base);
    if (base->mode != AQUARIUM_MODE_NEW_COURSE && base->mode != AQUARIUM_MODE_REST) {
        AquariumSwim_Climb(base);
        AquariumSwim_TiltBySpeed(base, 0x1554, 0x3e8);
        AquariumFish_Turn(base);
    }
}
CLEAN_AS(func_ov004_0223766c, AquariumRisingFish_Wander)

/* func_ov004_0223771c (slot 1 of the class of kinds 5 and 6): it swims on or rises; its
 * animation speed (at least 0.2), its timer and the stylus. */
void AquariumRisingFish_Swim(AquariumRisingFish *fish)
{
    switch (fish->own.rising) {
        case 0:
            AquariumRisingFish_Wander(fish);
            break;
        case 1:
            AquariumRisingFish_Rise(fish);
            break;
    }
    AquariumFish_SetAnimSpeed(&fish->base, 0x333);
    fish->base.timer++;
    AquariumFish_CheckTapped(&fish->base);
}
CLEAN_AS(func_ov004_0223771c, AquariumRisingFish_Swim)

/* func_ov004_02237764 (slot 0 of the class of kinds 5 and 6): it pays attention to nobody; its
 * model hooks and swimming values. */
void AquariumRisingFish_SetUp(AquariumRisingFish *fish)
{
    fish->base.focus = (u8) fish->base.index;
    ModelObject_SetInitHook(&fish->base.model.object, (void *) (uintptr_t) func_ov004_0223653c, fish);
    AquariumFish_SetSwim(&fish->base);
}
CLEAN_AS(func_ov004_02237764, AquariumRisingFish_SetUp)

/* func_ov004_02237794 (kind 30 drifting after a lunge): it drifts 0.05 a frame its yaw mirrored
 * (-yaw); on every fourth frame (the timer 1 more than a multiple of 4) it lunges again, until
 * its snapping time is over. */
void AquariumKind30_Drift(AquariumKind30 *fish)
{
    AquariumSwim_Move(&fish->base.position, 0xcd, (s16) -fish->base.yaw);
    if (fish->base.timer % 4 == 1) {
        fish->own.snap = AQUARIUM_SNAP_LUNGE;
    }
    if (fish->base.timer >= fish->own.snap_frames) {
        fish->own.snap = AQUARIUM_SNAP_WAIT;
    }
}
CLEAN_AS(func_ov004_02237794, AquariumKind30_Drift)

/* func_ov004_022377ec (kind 30 lunging): it moves 0.15 along its yaw and 0.02 a random way, then
 * drifts. 0x257.
 * QUIRK: the result is the offset of the field it set, left over in the game's code. */
int AquariumKind30_Lunge(AquariumKind30 *fish)
{
    AquariumSwim_Move(&fish->base.position, 0x266, fish->base.yaw);
    AquariumSwim_Move(&fish->base.position, 0x52, AquariumSwim_RandomAngle(360, 0));
    fish->own.snap = AQUARIUM_SNAP_DRIFT;
    return (int) offsetof(AquariumKind30, own.snap);
}
CLEAN_AS(func_ov004_022377ec, AquariumKind30_Lunge)

/* func_ov004_02237834 (kind 30 waiting to snap): three times in twenty it starts snapping, for
 * 8 to 12 frames. */
void AquariumKind30_Wait(AquariumKind30 *fish)
{
    if (AquariumSwim_Random(0, 100) < 15) {
        fish->own.snap = AQUARIUM_SNAP_LUNGE;
        fish->own.snap_frames = (u8) AquariumSwim_Random(8, 13);
        fish->base.timer = 0;
    }
}
CLEAN_AS(func_ov004_02237834, AquariumKind30_Wait)

/* func_ov004_02237870: kind 30 bobs up or down at its vertical speed, turning the other way
 * three times in twenty and at its top and bottom. */
void AquariumKind30_Bob(AquariumKind30 *fish)
{
    AquariumFish *base = &fish->base;
    base->position.y += Kinds_mul(base->swim_224, base->vertical);
    if (AquariumSwim_Random(0, 100) < 15) {
        base->vertical = (s8) -base->vertical;
    }
    if (base->position.y > base->level) {
        base->vertical = -1;
        base->position.y = base->level;
    } else if (base->position.y < base->swim_228) {
        base->vertical = 1;
        base->position.y = base->swim_228;
    }
}
CLEAN_AS(func_ov004_02237870, AquariumKind30_Bob)

/* func_ov004_022378ec (kind 30 at the player): without the player it wanders. It levels off at
 * height 1.6, snaps (waiting, lunging, drifting) and turns to the player's position at the
 * start of its frame; further than 4.0 from it, it wanders again, further than 2.0 it follows.
 * Its animation runs at full speed. */
void AquariumKind30_Snap(AquariumKind30 *fish)
{
    AquariumFish *base = &fish->base;
    Vec3 *player = PlayerActorOps_StartPosition(OWN_PLAYER);
    if (player == NULL) {
        fish->own.state = AQUARIUM_KIND30_WANDER;
        return;
    }
    if (base->pitch != 0) {
        Approach_S16(&base->pitch, 0, 0x16c);
    }
    if (base->position.y != KIND30_HEIGHT) {
        Approach_S32((int *) (void *) &base->position.y, KIND30_HEIGHT, base->swim_224);
    }
    switch (fish->own.snap) {
        case AQUARIUM_SNAP_LUNGE:
            AquariumKind30_Lunge(fish);
            break;
        case AQUARIUM_SNAP_DRIFT:
            AquariumKind30_Drift(fish);
            break;
        case AQUARIUM_SNAP_WAIT:
            AquariumKind30_Wait(fish);
            break;
    }
    Approach_S16(&base->yaw, Vec_YawTo(&base->position, player), 0x222);
    s64 distance = Vec_DistanceSquaredXZ(player, &base->position);
    if (distance > PLAYER_NEAR) {
        fish->own.state = AQUARIUM_KIND30_WANDER;
        base->timer = 0;
    } else if (distance > PLAYER_CLOSE) {
        fish->own.state = AQUARIUM_KIND30_FOLLOW;
        base->timer = 0;
    }
    base->model.frames.speed = ONE;
}
CLEAN_AS(func_ov004_022378ec, AquariumKind30_Snap)

/* func_ov004_022379ec (kind 30 following the player): without the player it wanders. It turns
 * to the player and swims at its top speed; while the player moves it levels off at height
 * 1.6, while the player stands it bobs, and after 70 frames of that it sets off on its own.
 * Within 2.0 of the player and against the glass it snaps; further than 4.0 it wanders. Its
 * animation runs at full speed. */
void AquariumKind30_Follow(AquariumKind30 *fish)
{
    AquariumFish *base = &fish->base;
    Actor *player = SessionPlayers_ActorOf(OWN_PLAYER);
    if (player == NULL) {
        fish->own.state = AQUARIUM_KIND30_WANDER;
        return;
    }
    Vec3 at = player->position;
    Approach_S16(&base->yaw, Vec_YawTo(&base->position, &at), 0x222);
    AquariumSwim_Move(&base->position, base->top_speed, base->yaw);
    if (player->speed != 0) {
        if (base->pitch != 0) {
            Approach_S16(&base->pitch, 0, 0x222);
        }
        if (base->position.y != KIND30_HEIGHT) {
            Approach_S32((int *) (void *) &base->position.y, KIND30_HEIGHT, base->swim_224);
        }
        fish->own.count = 0;
    } else {
        AquariumKind30_Bob(fish);
        fish->own.count++;
        if (fish->own.count >= 70) {
            fish->own.state = AQUARIUM_KIND30_WANDER;
            base->mode = AQUARIUM_MODE_NEW_COURSE;
            base->timer = 0;
            fish->own.count = 0;
            return;
        }
    }
    s64 distance = Vec_DistanceSquaredXZ(&at, &base->position);
    if (distance < PLAYER_CLOSE) {
        if (fish->own.at_glass) {
            fish->own.state = AQUARIUM_KIND30_SNAP;
            base->timer = 0;
        }
    } else if (distance > PLAYER_NEAR) {
        fish->own.state = AQUARIUM_KIND30_WANDER;
        base->timer = 0;
    }
    base->model.frames.speed = ONE;
}
CLEAN_AS(func_ov004_022379ec, AquariumKind30_Follow)

/* func_ov004_02237b2c (kind 30 wandering): its mode runs, it turns from the glass, and unless
 * setting off or resting it climbs or dives with its pitch and turns to its course; its
 * animation speed (at least 0.4). Within 4.0 of the player for more than 10 frames, it follows
 * the player once the player moves. */
void AquariumKind30_Wander(AquariumKind30 *fish)
{
    AquariumFish *base = &fish->base;
    Kinds_run_mode(base);
    AquariumSwim_WatchGlass(base);
    if (base->mode != AQUARIUM_MODE_NEW_COURSE && base->mode != AQUARIUM_MODE_REST) {
        AquariumSwim_Climb(base);
        AquariumSwim_TiltBySpeed(base, 0x1554, 0x384);
        AquariumFish_Turn(base);
    }
    AquariumFish_SetAnimSpeed(base, 0x666);
    Actor *player = SessionPlayers_ActorOf(OWN_PLAYER);
    if (player == NULL) {
        return;
    }
    Vec3 at = player->position;
    if (Vec_DistanceSquaredXZ(&at, &base->position) < PLAYER_NEAR) {
        fish->own.count++;
        if (fish->own.count > 10 && player->speed != 0) {
            fish->own.state = AQUARIUM_KIND30_FOLLOW;
            base->timer = 0;
            fish->own.count = 0;
        }
    } else {
        fish->own.count = 0;
    }
}
CLEAN_AS(func_ov004_02237b2c, AquariumKind30_Wander)

/* func_ov004_02237c14 (slot 1 of kind 30's class): its state runs; it is kept inside the river
 * room's second tank, its body (a rock's, index 0xff, of kind 30's sizes and weight a tenth
 * of its size) entered on the field; its previous position becomes this one, and its timer. */
void AquariumKind30_Swim(AquariumKind30 *fish)
{
    AquariumFish *base = &fish->base;
    MemberPointer_CallVoid(&data_ov004_022593f4[fish->own.state], fish);
    const AquariumFishInfo *info = &data_ov004_02247924[KIND_FISH_30];
    fx32 radius = (fx32) info->body_radius << 5;
    fish->own.at_glass = (u8) CollisionQuery_ClampToRect(&base->position, radius, &data_ov004_022593c4, 0x11c00, 0x5c00);
    FieldPointBody_Set(&base->body.base, &base->position, radius, (fx32) info->body_height << 5, 0x100, 0x140, 0, 0xff,
                       ((int) base->size << 12) / 10);
    FieldBody_Enter(&base->body.base.body);
    base->previous = base->position;
    base->timer++;
}
CLEAN_AS(func_ov004_02237c14, AquariumKind30_Swim)

/* func_ov004_02237d04 (slot 0 of kind 30's class): it pays attention to nobody, has no body of
 * the aquarium's (it enters its own); its swimming values. */
void AquariumKind30_SetUp(AquariumKind30 *fish)
{
    fish->base.focus = (u8) fish->base.index;
    fish->base.solid = 0;
    AquariumFish_SetSwim(&fish->base);
}
CLEAN_AS(func_ov004_02237d04, AquariumKind30_SetUp)

/* func_ov004_02237d28 (slot 1 of kind 40's class): it turns from the glass and its mode runs.
 * Once touched, at the end of its animation (a frame earlier above full speed) it plays
 * animation 1 at twice its top speed, then animation 2 for 60 to 79 frames more, then
 * animation 3 at its top speed again, then animation 0. Unless setting off or resting it
 * climbs or dives with its pitch and turns to its course; its animation speed (at least 0.4),
 * the room's and the tank's ends, whom it pays attention to, its timer; a tap on the glass
 * counts as a touch, or keeps animation 2 going. */
void AquariumKind40_Swim(AquariumKind40 *fish)
{
    AquariumFish *base = &fish->base;
    AquariumFish_TurnFromGlass(base);
    Kinds_run_mode(base);
    u16 last = Kinds_last_frame(base, 1);
    if (base->model.frames.speed > ONE) {
        last = Kinds_last_frame(base, 2);
    }
    switch (fish->own.phase) {
        case AQUARIUM_KIND40_CALM:
            if (base->body.base.body.touched) {
                fish->own.touched = 1;
            }
            if (fish->own.touched && FrameCtrl_Passed(&base->model.frames, last)) {
                fish->own.phase = AQUARIUM_KIND40_START;
                base->top_speed = Kinds_shl(base->top_speed, 1);
                AquariumSwim_PlayAnim(base, 1);
                fish->own.touched = 0;
            }
            break;
        case AQUARIUM_KIND40_START:
            if (FrameCtrl_Passed(&base->model.frames, last)) {
                fish->own.hold_frames = (u8) AquariumSwim_Random(60, 80);
                fish->own.held = 0;
                fish->own.phase = AQUARIUM_KIND40_HOLD;
                AquariumSwim_PlayAnim(base, 2);
            }
            break;
        case AQUARIUM_KIND40_HOLD:
            if (fish->own.held > fish->own.hold_frames) {
                if (FrameCtrl_Passed(&base->model.frames, last)) {
                    fish->own.phase = AQUARIUM_KIND40_END;
                    base->top_speed >>= 1;
                    AquariumSwim_PlayAnim(base, 3);
                }
            } else {
                fish->own.held++;
            }
            break;
        case AQUARIUM_KIND40_END:
            if (FrameCtrl_Passed(&base->model.frames, last)) {
                fish->own.phase = AQUARIUM_KIND40_CALM;
                AquariumSwim_PlayAnim(base, 0);
            }
            break;
    }
    if (base->mode != AQUARIUM_MODE_NEW_COURSE && base->mode != AQUARIUM_MODE_REST) {
        AquariumSwim_ClimbByFocus(base);
        AquariumSwim_TiltEased(base, 0x1554);
        AquariumFish_Turn(base);
    }
    AquariumFish_SetAnimSpeed(base, 0x666);
    AquariumFish_KeepOffRoomEnds(base);
    AquariumFish_ReactToFocus(base);
    AquariumFish_TurnAtTankEnds(base);
    base->timer++;
    if (AquariumFish_CheckTapped(base)) {
        if (fish->own.phase == AQUARIUM_KIND40_CALM) {
            fish->own.touched = 1;
        } else {
            fish->own.held = 0;
        }
    }
}
CLEAN_AS(func_ov004_02237d28, AquariumKind40_Swim)

/* func_ov004_02237ef0 (slot 0 of kind 40's class): it is its body's owner, pays attention to and
 * makes way for nobody, keeps to area 1; its swimming values and model hooks. */
void AquariumKind40_SetUp(AquariumKind40 *fish)
{
    fish->base.body.owner = &fish->base;
    fish->base.focus = (u8) fish->base.index;
    fish->base.yield_to = (u8) fish->base.index;
    fish->base.area = 1;
    AquariumFish_SetSwim(&fish->base);
    ModelObject_SetInitHook(&fish->base.model.object, (void *) (uintptr_t) func_ov004_0223653c, fish);
}
CLEAN_AS(func_ov004_02237ef0, AquariumKind40_SetUp)
