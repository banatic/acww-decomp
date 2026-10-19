/* More classes of the museum's aquarium fish (aquarium_fish_classes.h). */
#include "aquarium_fish_classes.h"

#include <stdint.h>
#include <string.h>

#include "aquarium_swim.h"
#include "autoload_2/approach.h"
#include "autoload_2/matrix.h"
#include "clean.h"
#include "main/frame_ctrl.h"
#include "main/model_object.h"
#include "member_pointer.h"

static_assert(offsetof(AquariumClimber, own.climb_frames) == 0x21c, "climber frames");
static_assert(offsetof(AquariumClimber, own.climb) == 0x255, "climber climb");
static_assert(offsetof(AquariumKind37, own.home) == 0x258, "kind 37 home");
static_assert(offsetof(AquariumKind37, own.pitch_count) == 0x268, "kind 37 pitch");
static_assert(offsetof(AquariumKind35, own.body_point) == 0x264, "kind 35 body point");
static_assert(offsetof(AquariumKind35, own.pitch_count) == 0x274, "kind 35 pitch");
static_assert(offsetof(AquariumKind36, own.pulse_frames) == 0x268, "kind 36 pulse frames");
static_assert(offsetof(AquariumKind36, own.body_point) == 0x26c, "kind 36 body point");
static_assert(offsetof(AquariumKind36, own.pulses) == 0x280, "kind 36 pulses");
static_assert(offsetof(AquariumKind36, own.dodge_yaw) == 0x282, "kind 36 dodge yaw");
static_assert(offsetof(AquariumKind36, own.pitch_count) == 0x288, "kind 36 pitch");
static_assert(sizeof(AquariumKind36) == 0x28c, "kind 36");
static_assert(offsetof(AquariumKind15, own.top_speed) == 0x208, "kind 15 top speed");
static_assert(offsetof(AquariumKind15, own.state) == 0x20e, "kind 15 state");
static_assert(offsetof(AquariumKind11, own.wait_frames) == 0x208, "kind 11 wait");
static_assert(offsetof(AquariumKind11, own.anim_speed) == 0x20c, "kind 11 anim speed");
static_assert(offsetof(AquariumKind11, own.state) == 0x211, "kind 11 state");
static_assert(offsetof(AquariumFish, model.object.unk_64) == 0xc8, "fish model matrix");
static_assert(offsetof(AquariumFish, previous) == 0x1b4, "fish previous");

/* What each kind is like, and the fish by kind (museum_aquarium.c). */
extern const AquariumFishInfo data_ov004_02247924[];
extern AquariumFish *data_ov004_022594d4[AQUARIUM_FISH_KINDS];
/* The fish of kinds 11, 36 and 35 (museum_aquarium.c). */
extern AquariumFish *data_ov004_022593ac;
extern AquariumFish *data_ov004_022593b4;
extern AquariumFish *data_ov004_022593b8;
/* Where the room's node "hasu1" is (room_shell.c). */
extern Vec3 data_ov004_02258a30;
/* The member functions of the modes; of the modes of the fish that never stop; of kind 15's
 * states. */
extern const MemberPointer data_ov004_0225949c[7];
extern const MemberPointer data_ov004_0225946c[6];
extern const MemberPointer data_ov004_02259444[5];
/* AquariumClimber_PlaceBody's heights, each taken once (bit 0 of its guard says it was). */
extern fx32 data_ov004_022593b0;
extern u32 data_ov004_022593bc;
extern fx32 data_ov004_022593a8;
extern u32 data_ov004_022593c0;

extern Mtx43 data_021fbe48; /* the matrix being built */
extern void MTX_MultVec43(const Vec3 *vec, const Mtx43 *mtx, Vec3 *dst);

/* The model hook handed to the game (aquarium_fish.c). */
extern void func_ov004_0223653c(G3dRenderState *state);

#define ONE 0x1000
#define QUARTER_TURN 0x4000

/* The kinds of some classes. */
#define KIND_FISH_52 52
#define KIND_FISH_53 53

/* Kind 11's place, until the room's node is drawn, and its sound. */
#define KIND11_X 0x14500
#define KIND11_Y 0x3700
#define KIND11_Z 0x15400
#define KIND11_SOUND 0x832

/* How the fish pacing the sea tank turn at its ends, and their lines along it. */
#define LANE_TURN_STEP 0x444
#define LANE_TURN_PUSH 0x133
#define LANE_Z_53 0x10800
#define LANE_Z_52 0x10000
#define LANE_Z_STEP 0xcd
#define NONSTOP_TURN_STEP 0x38e
#define NONSTOP_TURN_PUSH 0x19a

/* How fast kind 36 darts away, and turns to its way away. */
#define DODGE_TOP_SPEED 0x7b
#define DODGE_TURN_STEP 0x2d8

static int AquariumClasses_mul(int a, int b)
{
    return (int) ((u32) a * (u32) b);
}

static int AquariumClasses_add(int a, int b)
{
    return (int) ((u32) a + (u32) b);
}

static int AquariumClasses_sub(int a, int b)
{
    return (int) ((u32) a - (u32) b);
}

static int AquariumClasses_shl(int value, int shift)
{
    return (int) ((u32) value << shift);
}

/* The member function of the fish's mode. */
static void AquariumClasses_run_mode(AquariumFish *fish)
{
    MemberPointer_CallVoid(&data_ov004_0225949c[fish->mode], fish);
}

/* The last frame of the fish's animation, less 1, as FrameCtrl_Passed takes it. */
static u16 AquariumClasses_before_last_frame(const AquariumFish *fish)
{
    u32 frames = ((u32) fish->model.frames.end << 4) >> 16;
    return (u16) (frames - 1u);
}

/* A climber goes on in `climb`, its climb's frames counted afresh. */
static void AquariumClimber_set(AquariumClimber *fish, u8 climb)
{
    fish->own.climb_frames = 0;
    fish->own.climb = climb;
}

/* A climber's set-up: it pays attention to and makes way for nobody, keeps to area 0, swims
 * at `top_speed` speeding up and slowing down by `accel` a frame, turns up to `turn` degrees at
 * a new course; its times to cruise and rest from its kind's table entry. */
static void AquariumClimber_set_up(AquariumFish *fish, fx32 top_speed, int accel, u16 turn)
{
    fish->focus = (u8) fish->index;
    fish->yield_to = (u8) fish->index;
    fish->area = 0;
    fish->top_speed = top_speed;
    fish->swim_214 = accel;
    fish->swim_218 = accel;
    fish->swim_230 = turn;
    const u8 *swim = data_ov004_02247924[fish->index].swim;
    fish->swim_204[0] = swim[3];
    fish->swim_204[1] = swim[4];
    fish->swim_204[2] = swim[5];
    fish->swim_204[3] = swim[6];
}

/* The home kinds 35 and 37 keep near. */
static void AquariumClasses_set_point(Vec3 *point, fx32 x, fx32 y, fx32 z)
{
    point->x = x;
    point->y = y;
    point->z = z;
}

/* func_ov004_02237f38 (slot 1 of kind 37's class): it turns back towards its home from 1.0 away.
 * Climbing, 11 times in 100 it coasts; coasting, it sinks 9 times in 100 or once above 2.0, and
 * climbs again once it no longer rises; sinking, it coasts 4 times in 100 or once down to
 * 1.0. Its animation runs at 1.0 climbing, 0.7
 * coasting, 0.4 sinking. Its mode runs, its pitch rocks within 0x11c6, it turns to its course
 * unless setting off, and it climbs or sinks (by 8 a frame, at most 81); its timers and the
 * stylus. */
void AquariumKind37_Swim(AquariumKind37 *fish)
{
    AquariumFish *base = &fish->base;
    AquariumSwim_TurnTowards(&base->yaw, &base->position, &fish->own.home, ONE);
    switch (fish->own.climb) {
        case AQUARIUM_CLIMB_COAST:
            if (AquariumSwim_Random(0, 100) <= 8 || base->position.y >= 0x2000) {
                AquariumClimber_set(&fish->climber, AQUARIUM_CLIMB_SINK);
            } else if (base->position.y == base->previous.y) {
                AquariumClimber_set(&fish->climber, AQUARIUM_CLIMB_UP);
            }
            base->model.frames.speed = 0xb33;
            break;
        case AQUARIUM_CLIMB_UP:
            if (AquariumSwim_Random(0, 100) <= 10) {
                AquariumClimber_set(&fish->climber, AQUARIUM_CLIMB_COAST);
            }
            base->model.frames.speed = ONE;
            break;
        case AQUARIUM_CLIMB_SINK:
            if (AquariumSwim_Random(0, 100) <= 3 || base->position.y <= ONE) {
                AquariumClimber_set(&fish->climber, AQUARIUM_CLIMB_COAST);
            }
            base->model.frames.speed = 0x666;
            break;
    }
    AquariumClasses_run_mode(base);
    AquariumClimber_Sway(&base->pitch, &fish->own.pitch_up, &fish->own.pitch_count, 0x11c6, 150);
    if (base->mode != AQUARIUM_MODE_NEW_COURSE) {
        AquariumFish_Turn(base);
    }
    AquariumClimber_Drift(&fish->climber, 8, 81, fish->own.climb);
    fish->climber.own.climb_frames++;
    base->timer++;
    AquariumFish_CheckTapped(base);
}
CLEAN_AS(func_ov004_02237f38, AquariumKind37_Swim)

/* func_ov004_022380ac (slot 0 of kind 37's class): a climber of top speed 0x51 (speeding up and
 * slowing down by 2), turning up to 60 degrees; its home (7.0, 0, 20.625). */
void AquariumKind37_SetUp(AquariumKind37 *fish)
{
    AquariumClimber_set_up(&fish->base, 0x51, 2, 60);
    AquariumClasses_set_point(&fish->own.home, 0x7000, 0, 0x14a00);
}
CLEAN_AS(func_ov004_022380ac, AquariumKind37_SetUp)

/* func_ov004_02238178 (slot 1 of kind 35's class): speeding up or cruising, it turns back
 * towards its home from 1.0 away. Its mode runs and its pitch rocks within 0x2aac. Climbing,
 * 31 times in 100 it coasts; coasting, it sinks 2 times in 100 or once above 2.7 (when its
 * animation passes frame 1), else 31 times in 100 climbs again, as it does once it no longer
 * rises; sinking, it coasts 2 times in 100 or once down to 0.5. Its animation runs
 * at 1.0 climbing, 0.9 coasting, 0.4 sinking. It turns to its course unless setting off,
 * climbs or sinks (by 8 a frame, at most 20); its timers, the stylus and its body's point. */
void AquariumKind35_Swim(AquariumKind35 *fish)
{
    AquariumFish *base = &fish->base;
    if (base->mode == AQUARIUM_MODE_SPEED_UP || base->mode == AQUARIUM_MODE_CRUISE) {
        AquariumSwim_TurnTowards(&base->yaw, &base->position, &fish->own.home, ONE);
    }
    AquariumClasses_run_mode(base);
    AquariumClimber_Sway(&base->pitch, &fish->own.pitch_up, &fish->own.pitch_count, 0x2aac, 300);
    switch (fish->own.climb) {
        case AQUARIUM_CLIMB_COAST:
            if (AquariumSwim_Random(0, 100) <= 1 || base->position.y >= 0x2b33) {
                if (FrameCtrl_Passed(&base->model.frames, 1)) {
                    AquariumClimber_set(&fish->climber, AQUARIUM_CLIMB_SINK);
                }
            } else if (AquariumSwim_Random(0, 100) <= 30) {
                AquariumClimber_set(&fish->climber, AQUARIUM_CLIMB_UP);
            } else if (base->position.y == base->previous.y) {
                AquariumClimber_set(&fish->climber, AQUARIUM_CLIMB_UP);
            }
            base->model.frames.speed = 0xe66;
            break;
        case AQUARIUM_CLIMB_UP:
            if (AquariumSwim_Random(0, 100) <= 30) {
                AquariumClimber_set(&fish->climber, AQUARIUM_CLIMB_COAST);
            }
            base->model.frames.speed = ONE;
            break;
        case AQUARIUM_CLIMB_SINK:
            if (AquariumSwim_Random(0, 100) <= 1 || base->position.y <= 0x800) {
                AquariumClimber_set(&fish->climber, AQUARIUM_CLIMB_COAST);
            }
            base->model.frames.speed = 0x666;
            break;
    }
    if (base->mode != AQUARIUM_MODE_NEW_COURSE) {
        AquariumFish_Turn(base);
    }
    AquariumClimber_Drift(&fish->climber, 8, 20, fish->own.climb);
    fish->climber.own.climb_frames++;
    base->timer++;
    AquariumFish_CheckTapped(base);
    AquariumClimber_PlaceBody(base, &fish->own.body_point);
}
CLEAN_AS(func_ov004_02238178, AquariumKind35_Swim)

/* func_ov004_02238340 (slot 0 of kind 35's class): a climber of top speed 0x3a (speeding up and
 * slowing down by 1), turning up to 30 degrees; its home (6.0, 0, 20.625); the aquarium keeps a
 * pointer to it. */
void AquariumKind35_SetUp(AquariumKind35 *fish)
{
    AquariumClimber_set_up(&fish->base, 0x3a, 1, 30);
    AquariumClasses_set_point(&fish->own.home, 0x6000, 0, 0x14a00);
    data_ov004_022593b8 = &fish->base;
}
CLEAN_AS(func_ov004_02238340, AquariumKind35_SetUp)

/* Kind 15 goes on in `state`, its timer at 0. */
static void AquariumKind15_set(AquariumKind15 *fish, u8 state)
{
    fish->own.state = state;
    fish->base.timer = 0;
}

/* func_ov004_02238414 (kind 15 still): its animation stopped for its still time, then it starts
 * again. The fish. */
AquariumKind15 *AquariumKind15_Still(AquariumKind15 *fish)
{
    fish->base.model.frames.speed = 0;
    if (fish->base.timer >= fish->own.still_frames) {
        AquariumKind15_set(fish, AQUARIUM_KIND15_START);
    }
    return fish;
}
CLEAN_AS(func_ov004_02238414, AquariumKind15_Still)

/* func_ov004_02238448 (kind 15 slowing down): its animation speed falls from its top by
 * slow_down a frame; stopped, it keeps still. */
void AquariumKind15_SlowDown(AquariumKind15 *fish)
{
    fx32 speed = AquariumClasses_sub(fish->own.top_speed, AquariumClasses_mul(fish->own.slow_down, fish->base.timer));
    if (speed <= 0) {
        speed = 0;
        AquariumKind15_set(fish, AQUARIUM_KIND15_STILL);
    }
    fish->base.model.frames.speed = speed;
}
CLEAN_AS(func_ov004_02238448, AquariumKind15_SlowDown)

/* func_ov004_02238488 (kind 15 holding): its animation at its top speed for its hold time, then
 * it slows down. */
void AquariumKind15_Hold(AquariumKind15 *fish)
{
    if (fish->base.timer >= fish->own.hold_frames) {
        AquariumKind15_set(fish, AQUARIUM_KIND15_SLOW_DOWN);
    }
    fish->base.model.frames.speed = fish->own.top_speed;
}
CLEAN_AS(func_ov004_02238488, AquariumKind15_Hold)

/* func_ov004_022384c0 (kind 15 speeding up): its animation speed grows by five times speed_up a
 * frame; at its top speed it holds. */
void AquariumKind15_SpeedUp(AquariumKind15 *fish)
{
    fx32 speed = AquariumClasses_mul(5, AquariumClasses_mul(fish->own.speed_up, fish->base.timer));
    if (speed >= fish->own.top_speed) {
        speed = fish->own.top_speed;
        AquariumKind15_set(fish, AQUARIUM_KIND15_HOLD);
    }
    fish->base.model.frames.speed = speed;
}
CLEAN_AS(func_ov004_022384c0, AquariumKind15_SpeedUp)

/* func_ov004_02238504 (kind 15 starting): random values for its next turn: a top animation
 * speed of 1.1 to 1.4, speeding up by 0.02 to 0.049 and slowing down by 0.01 to 0.029, holding
 * 1 to 149 frames and keeping still 10 to 119; its animation stopped, it speeds up. */
void AquariumKind15_Start(AquariumKind15 *fish)
{
    fish->own.top_speed = AquariumClasses_shl(AquariumSwim_Random(11, 15), 12) / 10;
    fish->own.speed_up = AquariumClasses_shl(AquariumSwim_Random(20, 50), 12) / 1000;
    fish->own.slow_down = AquariumClasses_shl(AquariumSwim_Random(10, 30), 12) / 1000;
    fish->own.hold_frames = (u8) AquariumSwim_Random(1, 150);
    fish->own.still_frames = (u8) AquariumSwim_Random(10, 120);
    fish->base.timer = 0;
    fish->base.model.frames.speed = 0;
    fish->own.state = AQUARIUM_KIND15_SPEED_UP;
}
CLEAN_AS(func_ov004_02238504, AquariumKind15_Start)

/* func_ov004_02238598 (slot 1 of kind 15's class): its state runs, and its timer. */
void AquariumKind15_Swim(AquariumKind15 *fish)
{
    MemberPointer_CallVoid(&data_ov004_02259444[fish->own.state], fish);
    fish->base.timer++;
}
CLEAN_AS(func_ov004_02238598, AquariumKind15_Swim)

/* func_ov004_022385dc (slot 0 of kind 15's class): it has no body, and stays at the origin
 * facing +z. The fish. */
AquariumKind15 *AquariumKind15_SetUp(AquariumKind15 *fish)
{
    fish->base.solid = 0;
    fish->base.position.x = 0;
    fish->base.position.y = 0;
    fish->base.position.z = 0;
    fish->base.yaw = 0;
    return fish;
}
CLEAN_AS(func_ov004_022385dc, AquariumKind15_SetUp)

/* func_ov004_02238608 (kind 11 playing): each time its animation passes frame 1 its sound plays,
 * counting the loop; after its loops, at the end of the animation it stops, back at frame 0,
 * and waits. */
void AquariumKind11_PlayLoops(AquariumKind11 *fish)
{
    AquariumFish *base = &fish->base;
    if (FrameCtrl_Passed(&base->model.frames, 1)) {
        SoundSource_PlayHeld(&fish->own.sound, KIND11_SOUND);
        fish->own.loops_done++;
    }
    if (fish->own.loops_done >= fish->own.loops &&
        FrameCtrl_Passed(&base->model.frames, AquariumClasses_before_last_frame(base))) {
        fish->own.state = AQUARIUM_KIND11_WAIT;
        base->timer = 0;
        base->model.frames.frame = 0;
        base->model.frames.speed = 0;
    }
}
CLEAN_AS(func_ov004_02238608, AquariumKind11_PlayLoops)

/* func_ov004_02238698 (kind 11 starting): random values: to wait 40 to 199 frames after, to play
 * its animation 1 to 6 times at 0.5 to 0.74; it plays. */
void AquariumKind11_StartLoops(AquariumKind11 *fish)
{
    fish->own.wait_frames = (u16) AquariumSwim_Random(40, 200);
    fish->own.anim_speed = AquariumClasses_shl(AquariumSwim_Random(50, 75), 12) / 100;
    fish->base.model.frames.speed = fish->own.anim_speed;
    fish->own.loops = (u8) AquariumSwim_Random(1, 7);
    fish->own.loops_done = 0;
    fish->base.timer = 0;
    fish->own.state = AQUARIUM_KIND11_PLAY;
}
CLEAN_AS(func_ov004_02238698, AquariumKind11_StartLoops)

/* func_ov004_02238704 (slot 1 of kind 11's class): it sits where the room's node "hasu1" is, its
 * sound with it; its state runs (a wait ends after its wait time), and its timer. */
void AquariumKind11_Swim(AquariumKind11 *fish)
{
    AquariumFish *base = &fish->base;
    base->position = data_ov004_02258a30;
    Vec3 at = base->position;
    SoundSource_UpdateAt(&fish->own.sound, &at);
    switch (fish->own.state) {
        case AQUARIUM_KIND11_START:
            AquariumKind11_StartLoops(fish);
            break;
        case AQUARIUM_KIND11_PLAY:
            AquariumKind11_PlayLoops(fish);
            break;
        case AQUARIUM_KIND11_WAIT:
            if (base->timer >= fish->own.wait_frames) {
                fish->own.state = AQUARIUM_KIND11_START;
                base->timer = 0;
            }
            break;
    }
    base->timer++;
}
CLEAN_AS(func_ov004_02238704, AquariumKind11_Swim)

/* func_ov004_022387b0 (slot 0 of kind 11's class): it has no body, and is at (20.31, 3.44,
 * 21.25) facing +z until the room's node is drawn; the aquarium keeps a pointer to it; its
 * sound source. */
void AquariumKind11_SetUp(AquariumKind11 *fish)
{
    fish->base.solid = 0;
    AquariumClasses_set_point(&fish->base.position, KIND11_X, KIND11_Y, KIND11_Z);
    fish->base.yaw = 0;
    data_ov004_022593ac = &fish->base;
    SoundSource_Init(&fish->own.sound);
}
CLEAN_AS(func_ov004_022387b0, AquariumKind11_SetUp)

/* Kinds 53 and 54. */
static int AquariumLaneFish_is_53_or_54(int kind)
{
    return (u32) kind - (u32) KIND_FISH_53 <= 1;
}

/* At an end of the tank the fish turns (by 0x444 a frame) to face back along x, once facing it
 * pushed 0.075 that way, and moves 0.075 along its yaw, its animation at full speed and held at
 * `bend`. */
static void AquariumLaneFish_turn_at_end(AquariumFish *fish, int facing, int push, u8 bend)
{
    if (Approach_S16(&fish->yaw, facing, LANE_TURN_STEP)) {
        fish->position.x = AquariumClasses_add(fish->position.x, push);
    }
    AquariumSwim_Move(&fish->position, LANE_TURN_PUSH, fish->yaw);
    fish->model.frames.speed = ONE;
    fish->unk_1fe = bend;
    AquariumSwim_Bend(fish, (u16) (s8) fish->unk_1fe);
}

/* func_ov004_02238804: a fish of kinds 52 to 54 within 2.0 of the end at `low` or `high` (whole
 * units of x) turns back along the tank. Between them it goes on turning the way it turned
 * last, its mode runs, it keeps to its line along the tank (z 16.5 for kinds 53 and 54, 16.0
 * for kind 52, 0.05 a frame), straightens at the end of its bending, and its animation speed
 * (at least 0.2). */
void AquariumLaneFish_Pace(AquariumFish *fish, int low, int high)
{
    if (fish->position.x <= AquariumClasses_mul(AquariumClasses_add(low, 2), ONE)) {
        AquariumLaneFish_turn_at_end(fish, QUARTER_TURN, LANE_TURN_PUSH, AQUARIUM_BEND_RIGHT);
    } else if (fish->position.x >= AquariumClasses_mul(AquariumClasses_sub(high, 2), ONE)) {
        AquariumLaneFish_turn_at_end(fish, -QUARTER_TURN, -LANE_TURN_PUSH, AQUARIUM_BEND_LEFT);
    } else {
        if ((s8) fish->unk_1fe == AQUARIUM_BEND_RIGHT) {
            Approach_S16(&fish->yaw, QUARTER_TURN, LANE_TURN_STEP);
        } else if ((s8) fish->unk_1fe == AQUARIUM_BEND_LEFT) {
            Approach_S16(&fish->yaw, -QUARTER_TURN, LANE_TURN_STEP);
        }
        AquariumClasses_run_mode(fish);
        int *z = (int *) (void *) &fish->position.z;
        if (AquariumLaneFish_is_53_or_54(fish->index)) {
            Approach_S32(z, LANE_Z_53, LANE_Z_STEP);
        } else if (fish->index == KIND_FISH_52) {
            Approach_S32(z, LANE_Z_52, LANE_Z_STEP);
        }
        AquariumSwim_EndBend(fish);
        AquariumFish_SetAnimSpeed(fish, 0x333);
    }
}
CLEAN_AS(func_ov004_02238804, AquariumLaneFish_Pace)

/* func_ov004_0223896c (slot 1 of the class of kinds 52 to 54): it paces between x 2 and 32
 * (kinds 53 and 54) or -4 and 38 (kind 52); unless setting off or resting it climbs or dives
 * with its pitch (within 0x924 for kinds 53 and 54, 0x71c for kind 52); its timer. */
void AquariumLaneFish_Swim(AquariumFish *fish)
{
    int kind = fish->index;
    if (AquariumLaneFish_is_53_or_54(kind)) {
        AquariumLaneFish_Pace(fish, 2, 32);
    } else if (kind == KIND_FISH_52) {
        AquariumLaneFish_Pace(fish, -4, 38);
    }
    if (fish->mode != AQUARIUM_MODE_NEW_COURSE && fish->mode != AQUARIUM_MODE_REST) {
        AquariumSwim_Climb(fish);
        kind = fish->index;
        if (AquariumLaneFish_is_53_or_54(kind)) {
            AquariumSwim_TiltBySpeed(fish, 0x924, 0x28a);
        } else if (kind == KIND_FISH_52) {
            AquariumSwim_TiltBySpeed(fish, 0x71c, 0x28a);
        }
    }
    fish->timer++;
}
CLEAN_AS(func_ov004_0223896c, AquariumLaneFish_Swim)

/* func_ov004_022389f4 (slot 0 of the class of kinds 52 to 54): it pays attention to nobody and
 * has no body; kinds 53 and 54 get their model hooks; it faces +x or -x at random; its swimming
 * values. */
void AquariumLaneFish_SetUp(AquariumFish *fish)
{
    fish->focus = (u8) fish->index;
    fish->solid = 0;
    if (AquariumLaneFish_is_53_or_54(fish->index)) {
        ModelObject_SetInitHook(&fish->model.object, (void *) (uintptr_t) func_ov004_0223653c, fish);
    }
    int way = AquariumSwim_Random(0, 2) > 0 ? 1 : -1;
    fish->yaw = (s16) AquariumClasses_mul(way, QUARTER_TURN);
    AquariumFish_SetSwim(fish);
}
CLEAN_AS(func_ov004_022389f4, AquariumLaneFish_SetUp)

/* At an end of the tank the fish turns (by 0x38e a frame) to face back along x, once facing it
 * pushed 0.1 that way, goes to its height (the table's depth) and moves 0.1 along its yaw, its
 * animation at full speed and held at `bend`.
 * QUIRK: the height is the table's depth without the 1.0 below that placing a fish takes off
 * (museum_aquarium.c). */
static void AquariumNonstopFish_turn_at_end(AquariumFish *fish, int facing, int push, int bend)
{
    fish->glass_turning = 1;
    if (Approach_S16(&fish->yaw, facing, NONSTOP_TURN_STEP)) {
        fish->position.x = AquariumClasses_add(fish->position.x, push);
    }
    fish->position.y = (fx32) data_ov004_02247924[fish->index].depth << 6;
    AquariumSwim_Move(&fish->position, NONSTOP_TURN_PUSH, fish->yaw);
    fish->model.frames.speed = ONE;
    AquariumSwim_Bend(fish, bend);
}

/* func_ov004_02238a58: a fish of kinds 50 and 51 within 2.0 of the end at `left` or `right`
 * (whole units of x) turns back along the tank. Between them it turns its yaw further from the
 * glass it is kept off, reacts to whom it pays attention to, its mode runs (the modes of
 * data_ov004_0225946c), it turns to its course and keeps its yaw across the room, straightens at
 * the end of its bending, and its animation speed (at least 0.2). */
void AquariumNonstopFish_Pace(AquariumFish *fish, int left, int right)
{
    if (fish->position.x <= AquariumClasses_shl(AquariumClasses_add(left, 2), 12)) {
        AquariumNonstopFish_turn_at_end(fish, QUARTER_TURN, NONSTOP_TURN_PUSH, AQUARIUM_BEND_RIGHT);
    } else if (fish->position.x >= AquariumClasses_shl(AquariumClasses_sub(right, 2), 12)) {
        AquariumNonstopFish_turn_at_end(fish, -QUARTER_TURN, -NONSTOP_TURN_PUSH, AQUARIUM_BEND_LEFT);
    } else {
        AquariumFish_TurnFromGlass(fish);
        AquariumFish_ReactToFocus(fish);
        MemberPointer_CallVoid(&data_ov004_0225946c[fish->mode], fish);
        AquariumFish_Turn(fish);
        AquariumFish_KeepYawAcross(fish);
        AquariumSwim_EndBend(fish);
        AquariumFish_SetAnimSpeed(fish, 0x333);
    }
}
CLEAN_AS(func_ov004_02238a58, AquariumNonstopFish_Pace)

/* func_ov004_02238ba4 (slot 1 of the class of kinds 50 and 51): it paces between x -2 and 36;
 * unless setting off or resting it climbs or dives by whom it pays attention to; its animation
 * speed (at least 0.2), its timer and the stylus. */
void AquariumNonstopFish_Swim(AquariumFish *fish)
{
    AquariumNonstopFish_Pace(fish, -2, 36);
    if (fish->mode != AQUARIUM_MODE_NEW_COURSE && fish->mode != AQUARIUM_MODE_REST) {
        AquariumSwim_ClimbByFocus(fish);
    }
    AquariumFish_SetAnimSpeed(fish, 0x333);
    fish->timer++;
    AquariumFish_CheckTapped(fish);
}
CLEAN_AS(func_ov004_02238ba4, AquariumNonstopFish_Swim)

/* func_ov004_02238bf0 (slot 0 of the class of kinds 50 and 51): it is its body's owner, keeps to
 * area 2, gets its model hooks, pays attention to and makes way for nobody; its swimming
 * values. */
void AquariumNonstopFish_SetUp(AquariumFish *fish)
{
    fish->body.owner = fish;
    fish->area = 2;
    ModelObject_SetInitHook(&fish->model.object, (void *) (uintptr_t) func_ov004_0223653c, fish);
    fish->focus = (u8) fish->index;
    fish->yield_to = (u8) fish->index;
    AquariumFish_SetSwim(fish);
}
CLEAN_AS(func_ov004_02238bf0, AquariumNonstopFish_SetUp)

/* func_ov004_02238c38: the point a climber's body is at (`out`): midway in the ground plane
 * between its position and the top of its body as its model matrix turns it, at the lower of
 * its position and its body's front.
 * QUIRK: the body's height and radius are taken once, from the first fish to run this (kinds
 * 35 and 36 share them). */
void AquariumClimber_PlaceBody(AquariumFish *fish, Vec3 *out)
{
    const AquariumFishInfo *info = &data_ov004_02247924[fish->index];
    if ((data_ov004_022593bc & 1) == 0) {
        data_ov004_022593b0 = (fx32) info->body_height << 5;
        data_ov004_022593bc |= 1;
    }
    if ((data_ov004_022593c0 & 1) == 0) {
        data_ov004_022593a8 = (fx32) info->body_radius << 5;
        data_ov004_022593c0 |= 1;
    }
    Vec3 up = {0, data_ov004_022593b0, 0};
    Vec3 front = {0, 0, data_ov004_022593a8};
    Vec3 top, ahead;
    memcpy(&data_021fbe48, fish->model.object.unk_64, sizeof(Mtx43));
    MTX_MultVec43(&up, &data_021fbe48, &top);
    MTX_MultVec43(&front, &data_021fbe48, &ahead);
    out->x = AquariumClasses_add(fish->position.x, top.x) >> 1;
    out->z = AquariumClasses_add(fish->position.z, top.z) >> 1;
    out->y = ahead.y < fish->position.y ? ahead.y : fish->position.y;
}
CLEAN_AS(func_ov004_02238c38, AquariumClimber_PlaceBody)

/* Kind 36's scale, the same along each axis. */
static void AquariumKind36_set_scale(AquariumKind36 *fish, fx32 scale)
{
    fish->own.scale.x = scale;
    fish->own.scale.y = scale;
    fish->own.scale.z = scale;
}

/* func_ov004_02238d18 (kind 36 shrinking): its scale shrinks from 1.0 by its rate a frame; at
 * its least scale it starts a new pulse. */
void AquariumKind36_Shrink(AquariumKind36 *fish)
{
    fx32 scale = AquariumClasses_sub(ONE, AquariumClasses_mul(fish->own.pulse_rate, fish->own.pulse_frames));
    if (scale < fish->own.least_scale) {
        AquariumKind36_set_scale(fish, fish->own.least_scale);
        fish->own.pulse = AQUARIUM_PULSE_START;
        fish->own.pulse_frames = 0;
    } else {
        AquariumKind36_set_scale(fish, scale);
    }
}
CLEAN_AS(func_ov004_02238d18, AquariumKind36_Shrink)

/* func_ov004_02238d88 (kind 36 growing): its scale grows from its least by its rate a frame; at
 * 1.0 it shrinks again, and at the first of its fast pulses its least scale becomes 0.6. */
void AquariumKind36_Grow(AquariumKind36 *fish)
{
    fx32 scale = AquariumClasses_add(fish->own.least_scale, AquariumClasses_mul(fish->own.pulse_rate, fish->own.pulse_frames));
    if (scale >= ONE) {
        AquariumKind36_set_scale(fish, ONE);
        fish->own.pulse = AQUARIUM_PULSE_SHRINK;
        fish->own.pulse_frames = 0;
        if (fish->own.pulses == 4) {
            fish->own.least_scale = 0x99a;
        }
    } else {
        AquariumKind36_set_scale(fish, scale);
    }
}
CLEAN_AS(func_ov004_02238d88, AquariumKind36_Grow)

/* func_ov004_02238e08 (kind 36 starting a pulse): it grows; during fast pulses its rate eases
 * back towards 0x14 (by 0x29) and its least scale towards 0.8 (by 0.05), one pulse less; else
 * the rate is 0x14 and the least scale 0.8. */
void AquariumKind36_StartPulse(AquariumKind36 *fish)
{
    fish->own.pulse = AQUARIUM_PULSE_GROW;
    fish->own.pulse_frames = 0;
    if (fish->own.pulses != 0) {
        Approach_S32((int *) (void *) &fish->own.pulse_rate, 0x14, 0x29);
        Approach_S32((int *) (void *) &fish->own.least_scale, 0xccd, 0xcd);
        fish->own.pulses--;
    } else {
        fish->own.pulse_rate = 0x14;
        fish->own.least_scale = 0xccd;
    }
}
CLEAN_AS(func_ov004_02238e08, AquariumKind36_StartPulse)

/* func_ov004_02238e70: kind 36's pulse runs, and its frames. */
void AquariumKind36_Pulse(AquariumKind36 *fish)
{
    switch (fish->own.pulse) {
        case AQUARIUM_PULSE_START:
            AquariumKind36_StartPulse(fish);
            break;
        case AQUARIUM_PULSE_GROW:
            AquariumKind36_Grow(fish);
            break;
        case AQUARIUM_PULSE_SHRINK:
            AquariumKind36_Shrink(fish);
            break;
    }
    fish->own.pulse_frames++;
}
CLEAN_AS(func_ov004_02238e70, AquariumKind36_Pulse)

/* Darting, kind 36 turns to its way away (by 0x2d8 a frame) and moves `speed` along its yaw. */
static void AquariumKind36_dart(AquariumKind36 *fish, fx32 speed)
{
    AquariumFish *base = &fish->base;
    Approach_S16(&base->yaw, base->away_yaw, DODGE_TURN_STEP);
    AquariumSwim_Move(&base->position, speed, base->yaw);
}

/* func_ov004_02238eb0 (kind 36 darting, slowing down): its speed falls from 0x7b by 2 a frame;
 * stopped, it sets off on a new course. */
void AquariumKind36_DodgeSlowDown(AquariumKind36 *fish)
{
    fx32 speed = AquariumClasses_sub(DODGE_TOP_SPEED, AquariumClasses_shl(fish->base.timer, 1));
    if (speed < 0) {
        speed = 0;
        fish->own.dodge = AQUARIUM_DODGE_NONE;
        fish->base.timer = 0;
        fish->base.mode = AQUARIUM_MODE_NEW_COURSE;
    }
    AquariumKind36_dart(fish, speed);
}
CLEAN_AS(func_ov004_02238eb0, AquariumKind36_DodgeSlowDown)

/* func_ov004_02238f14 (kind 36 darting, speeding up): its speed grows by 2 a frame; above 0x7b
 * it slows down. */
void AquariumKind36_DodgeSpeedUp(AquariumKind36 *fish)
{
    fx32 speed = AquariumClasses_shl(fish->base.timer, 1);
    if (speed > DODGE_TOP_SPEED) {
        speed = DODGE_TOP_SPEED;
        fish->own.dodge = AQUARIUM_DODGE_SLOW_DOWN;
        fish->base.timer = 0;
    }
    AquariumKind36_dart(fish, speed);
}
CLEAN_AS(func_ov004_02238f14, AquariumKind36_DodgeSpeedUp)

/* func_ov004_02238f70 (kind 36 starting to dart): dodge_yaw a quarter turn from the yaw of the
 * fish it pays attention to (when there is one); it speeds up.
 * QUIRK: dodge_yaw is not read; it darts along its way away (away_yaw). */
void AquariumKind36_StartDodge(AquariumKind36 *fish)
{
    AquariumFish *other = data_ov004_022594d4[fish->base.focus];
    if (other != NULL) {
        fish->own.dodge_yaw = (s16) (other->yaw + QUARTER_TURN);
    }
    fish->own.dodge = AQUARIUM_DODGE_SPEED_UP;
    fish->base.timer = 0;
}
CLEAN_AS(func_ov004_02238f70, AquariumKind36_StartDodge)

/* func_ov004_02238fb4: kind 36's dart runs. */
void AquariumKind36_Dodge(AquariumKind36 *fish)
{
    switch (fish->own.dodge) {
        case AQUARIUM_DODGE_START:
            AquariumKind36_StartDodge(fish);
            break;
        case AQUARIUM_DODGE_SPEED_UP:
            AquariumKind36_DodgeSpeedUp(fish);
            break;
        case AQUARIUM_DODGE_SLOW_DOWN:
            AquariumKind36_DodgeSlowDown(fish);
            break;
    }
}
CLEAN_AS(func_ov004_02238fb4, AquariumKind36_Dodge)

/* func_ov004_02238fe4: a pitch rocking between 0 and `most`: `count` goes up while `up`, else
 * down, and the pitch is it times `rate` (cut to 16 bits); at `most` it rocks down, at 0 up. */
void AquariumClimber_Sway(s16 *pitch, u8 *up, int *count, int most, int rate)
{
    *count = AquariumClasses_add(*count, *up ? 1 : -1);
    int value = (s16) AquariumClasses_mul(*count, rate);
    if (value >= most) {
        value = most;
        *up = 0;
    } else if (value <= 0) {
        value = 0;
        *up = 1;
    }
    *pitch = (s16) value;
}
CLEAN_AS(func_ov004_02238fe4, AquariumClimber_Sway)

/* func_ov004_02239024 (slot 1 of kind 36's class): paying attention to a new fish, it starts
 * four fast pulses and darts away; while not darting its mode runs. Its pitch rocks within
 * 0x2aac. Climbing, 11 times in 100 it coasts; coasting, it sinks one time in 125 or once above
 * 2.7 (when its animation passes frame 1), and climbs again once it no longer rises; sinking,
 * it coasts one time in 125 or once down to 0.5. Its animation runs at 0.5 climbing, 0.4
 * coasting, 0.3 sinking. It turns to its course unless setting off, climbs or sinks (by 8 a
 * frame, at most 40); its timers, its pulse and its body's point. */
void AquariumKind36_Swim(AquariumKind36 *fish)
{
    AquariumFish *base = &fish->base;
    u8 focus = base->focus;
    if (base->last_focus != focus && focus != base->index) {
        base->last_focus = focus;
        fish->own.pulses = 4;
        fish->own.pulse_rate = 0xcd;
        fish->own.dodge = AQUARIUM_DODGE_START;
    }
    if (fish->own.dodge == AQUARIUM_DODGE_NONE) {
        AquariumClasses_run_mode(base);
    } else {
        AquariumKind36_Dodge(fish);
    }
    AquariumClimber_Sway(&base->pitch, &fish->own.pitch_up, &fish->own.pitch_count, 0x2aac, 300);
    switch (fish->own.climb) {
        case AQUARIUM_CLIMB_COAST:
            if (AquariumSwim_Random(0, 250) <= 1 || base->position.y >= 0x2b33) {
                if (FrameCtrl_Passed(&base->model.frames, 1)) {
                    AquariumClimber_set(&fish->climber, AQUARIUM_CLIMB_SINK);
                }
            } else if (base->position.y == base->previous.y) {
                AquariumClimber_set(&fish->climber, AQUARIUM_CLIMB_UP);
            }
            base->model.frames.speed = 0x666;
            break;
        case AQUARIUM_CLIMB_UP:
            if (AquariumSwim_Random(0, 100) <= 10) {
                AquariumClimber_set(&fish->climber, AQUARIUM_CLIMB_COAST);
            }
            base->model.frames.speed = 0x800;
            break;
        case AQUARIUM_CLIMB_SINK:
            if (AquariumSwim_Random(0, 250) <= 1 || base->position.y <= 0x800) {
                AquariumClimber_set(&fish->climber, AQUARIUM_CLIMB_COAST);
            }
            base->model.frames.speed = 0x4cd;
            break;
    }
    if (base->mode != AQUARIUM_MODE_NEW_COURSE) {
        AquariumFish_Turn(base);
    }
    AquariumClimber_Drift(&fish->climber, 8, 40, fish->own.climb);
    fish->climber.own.climb_frames++;
    base->timer++;
    AquariumKind36_Pulse(fish);
    AquariumClimber_PlaceBody(base, &fish->own.body_point);
}
CLEAN_AS(func_ov004_02239024, AquariumKind36_Swim)

/* func_ov004_022391f0 (slot 0 of kind 36's class): it is its body's owner; a climber of top
 * speed 0x5e (speeding up and slowing down by 1), turning up to 150 degrees; the aquarium keeps
 * a pointer to it. */
void AquariumKind36_SetUp(AquariumKind36 *fish)
{
    fish->base.body.owner = &fish->base;
    AquariumClimber_set_up(&fish->base, 0x5e, 1, 150);
    data_ov004_022593b4 = &fish->base;
}
CLEAN_AS(func_ov004_022391f0, AquariumKind36_SetUp)

/* func_ov004_022394c4: a climber climbs or sinks in `way` (AQUARIUM_CLIMB_*, 3 sinking ever
 * slower): faster, by `accel` more each frame of its climb up to `most`; slower, from `most`
 * by `accel` less each frame down to 0.
 * QUIRK: another way moves it by `accel`, down when its low byte is 2 or 3. */
void AquariumClimber_Drift(AquariumClimber *fish, int accel, int most, unsigned int way)
{
    int step = accel;
    if (way == 0 || way == 2) {
        step = AquariumClasses_mul(fish->own.climb_frames, accel);
        if (step >= most) {
            step = most;
        }
    } else if (way == 1 || way == 3) {
        step = AquariumClasses_sub(most, AquariumClasses_mul(fish->own.climb_frames, accel));
        if (step <= 0) {
            step = 0;
        }
    }
    fx32 *y = &fish->base.position.y;
    if (way <= 1) {
        *y = AquariumClasses_add(*y, step);
    } else if ((u8) (way - 2) <= 1) {
        *y = AquariumClasses_sub(*y, step);
    }
}
CLEAN_AS(func_ov004_022394c4, AquariumClimber_Drift)
