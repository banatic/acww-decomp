/* The snowballs' states of overlay 68 (snowball.h). */
#include "snowball.h"

#include <stdint.h>

#include "autoload_2/approach.h" /* Approach_EaseS32, Math_AbsDiff16 */
#include "autoload_2/fx_math.h"  /* Math_Atan2 */
#include "autoload_2/process.h"  /* Process_RequestDelete */
#include "autoload_2/vector.h"
#include "clean.h"
#include "itcm/vector.h" /* Vec_Add */
#include "main/acre_map.h"
#include "main/acre_tile.h"
#include "main/actor_table.h" /* Position_Tile */
#include "main/effect_system.h"
#include "main/field_collision.h"
#include "main/map_code.h"
#include "main/session_players.h"
#include "main/snowmen.h"
#include "main/sound_emitter.h"
#include "main/unit_type_info.h"
#include "ov003/fish_shadow.h"
#include "ov003/snowman.h"

/* The parts of a ball that snowman.h leaves unnamed, by place. */
#define SNOWBALL_FALL_SPEED 0xa8   /* fx32: how fast it falls (rises while negative) */
#define SNOWBALL_DROP_FRAMES 0x368 /* u8: frames of the slow start of a fall (state 1) */
#define SNOWBALL_MOTION 0x36c      /* fx32[2]: the x velocity and the z move of the last frame */
#define SNOWBALL_TARGET 0x37c      /* Vec3: where it goes (states 5, 7, 8 and 10) */
#define SNOWBALL_CENTRE 0x388      /* Vec3: the middle of the tile it sinks into (state 4) */
#define SNOWBALL_WOBBLE 0x396      /* s16: the angle of its swaying */
#define SNOWBALL_TIMER 0x398       /* u8: frames left of shaking */
#define SNOWBALL_FRAMES 0x399      /* u8: frames of a move to the target */

/* The step to the target of states 7, 8 and 10 (x and z), in the rolling body's word at 0x70. */
#define SNOWBALL_STEP_X 0
#define SNOWBALL_STEP_Z 1

/* The collider's words (Snowman.collider): what it met. */
#define SNOWBALL_ON_GROUND 1     /* word 0: it stands on something */
#define SNOWBALL_TOUCHED_DOWN 2  /* word 1 */
#define SNOWBALL_WALL_ANGLES 0xc /* s16 each: the directions of what it hit, Snowman.collisions of them */

#define SNOWBALL_MOVE_FRAMES 16 /* a move to the target takes this many frames */
#define SNOWBALL_SHAKE_FRAMES 0xc
#define SNOWBALL_GRAVITY 0x6d
#define SNOWBALL_FALL_MAX 0x200
#define SNOWBALL_SINK_STEP 0x80
#define SNOWBALL_DROP_SLOW_FRAMES 0xc
#define SNOWBALL_FALL_SPEED_MIN 0x2b8 /* the speed a ball falls off the edge with at least */
#define SNOWBALL_SLIDE_END 0x3000     /* how far it slides before it drifts */
#define SNOWBALL_PLAYER 4
#define SNOWBALL_SIZE_FORGOTTEN 0x800 /* the size a forgotten ball is kept with */
#define SNOWBALL_SIZE_PUSHABLE 0xa00  /* smaller balls are not pushed (snowman.c) */
#define SNOWBALL_NO_ITEM 0xfff1
#define SNOWBALL_SINK_ITEM_FIRST 0xfc
#define SNOWBALL_SINK_ITEM_LAST 0xfd
#define SNOWBALL_SLIDE_GROUND_A 0x16
#define SNOWBALL_SLIDE_GROUND_B 0x17

/* The sounds and effects. */
#define SNOWBALL_SOUND_JUMP 0x81e
#define SNOWBALL_SOUND_BURST 0x81f
#define SNOWBALL_SOUND_SPLASH 0x821
#define SNOWBALL_EFFECT_BURST 0x3e
#define SNOWBALL_EFFECT_SPLASH 0x3f
#define SNOWBALL_STARTLE_REACH 0x5000 /* the fish within this of a splash are startled */

/* The town's map, the three snowmen main keeps and a point at the origin. */
extern AcreMap *data_021c80bc;
extern SnowmenRecord data_021f3b56[SNOWMEN_COUNT];
extern const Vec3 data_021fbee8;
/* The height of the water's surface. */
extern s32 data_020c904c;
/* The distance at which a slide ends (data_ov068_022786b8, a function-local static computed
 * once; bit 0 of data_ov068_022786bc says it was). */
extern fx32 data_ov068_022786b8;
extern u32 data_ov068_022786bc;
extern const s16 FX_SinCosTable_[];

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);

/* An arithmetic shift right, for negative values too. */
static int shift_right(int value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

static fx32 sine(int angle)
{
    return FX_SinCosTable_[2 * ((u16) angle >> 4)];
}

static fx32 cosine(int angle)
{
    return FX_SinCosTable_[2 * ((u16) angle >> 4) + 1];
}

static u8 *ball_at(Snowman *ball, u32 offset)
{
    return (u8 *) ball + offset;
}

static fx32 *ball_fall_speed(Snowman *ball)
{
    return (fx32 *) (void *) ball_at(ball, SNOWBALL_FALL_SPEED);
}

static Vec3 *ball_target(Snowman *ball)
{
    return (Vec3 *) (void *) ball_at(ball, SNOWBALL_TARGET);
}

static Vec3 *ball_centre(Snowman *ball)
{
    return (Vec3 *) (void *) ball_at(ball, SNOWBALL_CENTRE);
}

static s16 *ball_wobble(Snowman *ball)
{
    return (s16 *) (void *) ball_at(ball, SNOWBALL_WOBBLE);
}

static u8 *ball_frames(Snowman *ball)
{
    return ball_at(ball, SNOWBALL_FRAMES);
}

static u8 *ball_timer(Snowman *ball)
{
    return ball_at(ball, SNOWBALL_TIMER);
}

static fx32 *ball_step(Snowman *ball)
{
    return (fx32 *) (void *) ball->body.rolling.unk_70;
}

static int collider_word(const Snowman *ball, int index)
{
    return *(const int *) (const void *) (ball->collider + 4 * index);
}

static s16 wall_angle(const Snowman *ball, int index)
{
    return *(const s16 *) (const void *) (ball->collider + SNOWBALL_WALL_ANGLES + 2 * index);
}

static SoundEmitter *ball_sound(Snowman *ball)
{
    return (SoundEmitter *) (void *) ball->sound;
}

static void ball_delete(Snowman *ball)
{
    Process_RequestDelete((Process *) (void *) ball);
}

static void ball_turn(Snowman *ball, int by)
{
    *ball_wobble(ball) = (s16) (*ball_wobble(ball) + by);
}

/* Collisions with layer 0xb (or 0), with contact flag 2 (or not). */
static void ball_layer_b(Snowman *ball)
{
    ball->flags |= SNOWMAN_FLAG_LAYER_B;
    ball->flags &= (u16) ~SNOWMAN_FLAG_CONTACT_2;
}

static void ball_layer_0(Snowman *ball)
{
    ball->flags &= (u16) ~SNOWMAN_FLAG_LAYER_B;
    ball->flags |= SNOWMAN_FLAG_CONTACT_2;
}

/* What main keeps of it between visits forgotten: its entry (by the index's bit 0) back at the
 * origin with size 0x800. */
static void ball_forget(Snowman *ball)
{
    u32 which = ball->index & 1;
    SnowmenLooseBall *saved = Snowmen_LooseBalls();
    saved[which].position.x = 0;
    saved[which].position.y = 0;
    saved[which].position.z = 0;
    saved[which].size = SNOWBALL_SIZE_FORGOTTEN;
}

/* The step along x and z that takes it to the target in SNOWBALL_MOVE_FRAMES frames. */
static void ball_aim(Snowman *ball)
{
    ball_step(ball)[SNOWBALL_STEP_X] = FX_Div(ball_target(ball)->x - ball->position.x, 0x10000);
    ball_step(ball)[SNOWBALL_STEP_Z] = FX_Div(ball_target(ball)->z - ball->position.z, 0x10000);
}

static void ball_take_step(Snowman *ball)
{
    ball->position.x += ball_step(ball)[SNOWBALL_STEP_X];
    ball->position.z += ball_step(ball)[SNOWBALL_STEP_Z];
}

/* The frame count of the move noted; whether it had already reached SNOWBALL_MOVE_FRAMES. */
static int ball_count_frame(Snowman *ball)
{
    u8 frames = *ball_frames(ball);
    *ball_frames(ball) = (u8) (frames + 1);
    return frames >= SNOWBALL_MOVE_FRAMES;
}

/* The shaking of states 12 and 13 counted down; at the end the ball bursts and is deleted. */
static void ball_shake_tick(Snowman *ball)
{
    if (*ball_timer(ball) != 0) {
        (*ball_timer(ball))--;
    }
    if (*ball_timer(ball) == 0) {
        Snowball_Burst(ball);
        ball_delete(ball);
    }
}

/* The start of states 12 and 13: no rotation offset, no swaying, SNOWBALL_SHAKE_FRAMES. */
static void ball_shake_start(Snowman *ball)
{
    ball->body.rolling.model_offset = data_021fbee8;
    *ball_wobble(ball) = 0;
    *ball_timer(ball) = SNOWBALL_SHAKE_FRAMES;
}

/* func_ov068_0226ebc4 (update of state 13): the head sways (its models offset by 0.0625 along x
 * and back along z, with the cosine of its angle, which turns by 0x5000 a frame) until its
 * timer runs out. */
void Snowball_UpdateShakeHead(Snowman *ball)
{
    ball->last_size = ball->size;
    fx32 c = cosine(*ball_wobble(ball));
    ball->body.rolling.model_offset.x = FX_MulFunc(0x100, c);
    ball->body.rolling.model_offset.z = -FX_MulFunc(0x100, c);
    ball_turn(ball, 0x5000);
    ball_shake_tick(ball);
}
CLEAN_AS(func_ov068_0226ebc4, Snowball_UpdateShakeHead)

/* func_ov068_0226ec54 (entry of state 13) */
int Snowball_EnterShakeHead(Snowman *ball)
{
    ball_layer_0(ball);
    ball_shake_start(ball);
    return 1;
}
CLEAN_AS(func_ov068_0226ec54, Snowball_EnterShakeHead)

/* func_ov068_0226eca8 (update of state 12): as the head's, the other way along x and z and
 * turning by 0x3800 a frame. */
void Snowball_UpdateShakeBody(Snowman *ball)
{
    ball->last_size = ball->size;
    fx32 c = cosine(*ball_wobble(ball));
    ball->body.rolling.model_offset.x = -FX_MulFunc(0x100, c);
    ball->body.rolling.model_offset.z = FX_MulFunc(0x100, c);
    ball_turn(ball, 0x3800);
    ball_shake_tick(ball);
}
CLEAN_AS(func_ov068_0226eca8, Snowball_UpdateShakeBody)

/* func_ov068_0226ed38 (entry of state 12): the snowman's map object is taken off its tile
 * (Snowman_ClearTile) first. */
int Snowball_EnterShakeBody(Snowman *ball)
{
    ball_layer_0(ball);
    Snowman_ClearTile(&ball->position);
    ball_shake_start(ball);
    return 1;
}
CLEAN_AS(func_ov068_0226ed38, Snowball_EnterShakeBody)

/* func_ov068_0226ed9c (update of state 10): the head steps towards its place on the body and
 * rises by its speed, not above the place; after SNOWBALL_MOVE_FRAMES frames it is at the
 * place's height and stands as a head (SNOWMAN_STATE_HEAD). */
void Snowball_UpdateSettleHead(Snowman *ball)
{
    ball->last_size = ball->size;
    ball_take_step(ball);
    ball->position.y += *ball_fall_speed(ball);
    if (ball->position.y > ball_target(ball)->y) {
        ball->position.y = ball_target(ball)->y;
    }
    if (ball_count_frame(ball)) {
        ball->position.y = ball_target(ball)->y;
        Snowman_SetState(ball, SNOWMAN_STATE_HEAD);
    }
}
CLEAN_AS(func_ov068_0226ed9c, Snowball_UpdateSettleHead)

/* func_ov068_0226ee0c (entry of state 10): the speed that brings it up to its place in 0x1333
 * of a frame's units (FX_Div). */
int Snowball_EnterSettleHead(Snowman *ball)
{
    ball_layer_0(ball);
    *ball_wobble(ball) = 0;
    *ball_fall_speed(ball) = FX_Div(ball_target(ball)->y - ball->position.y, 0x1333);
    return 1;
}
CLEAN_AS(func_ov068_0226ee0c, Snowball_EnterSettleHead)

/* func_ov068_0226ee54 (update of state 8): the head steps towards the body and moves up by its
 * speed, which gravity (0xdf a frame) turns; once falling and lower than 0.125 below its place
 * it is put there and state 10 follows. After SNOWBALL_MOVE_FRAMES frames it is over the
 * body's middle.
 * QUIRK: the gravity is computed as FX_Div(0, 0x2710000) + 0xdf. */
void Snowball_UpdateJumpOn(Snowman *ball)
{
    ball->last_size = ball->size;
    ball_take_step(ball);
    fx32 none = FX_Div(0, 0x2710000);
    *ball_fall_speed(ball) += none + 0xdf;
    ball->position.y -= *ball_fall_speed(ball);
    if (*ball_fall_speed(ball) >= 0) {
        fx32 lowest = ball_target(ball)->y - 0x200;
        if (ball->position.y < lowest) {
            ball->position.y = lowest;
            Snowman_SetState(ball, SNOWBALL_STATE_SETTLE_HEAD);
        }
    }
    if (ball_count_frame(ball)) {
        ball->position.x = ball_target(ball)->x;
        ball->position.z = ball_target(ball)->z;
    }
}
CLEAN_AS(func_ov068_0226ee54, Snowball_UpdateJumpOn)

/* func_ov068_0226ef04 (entry of state 8): the head's place is the middle of the other loose
 * ball's tile, at the height a snowman's head sits on a body of that size (as Snowman_Setup);
 * it jumps (speed -0x8f2) and steps there in SNOWBALL_MOVE_FRAMES frames, playing sound 0x81e.
 * REQUIRES: another loose ball exists (func_ov003_02236128 finds the body it was put on). */
int Snowball_EnterJumpOn(Snowman *ball)
{
    ball_layer_0(ball);
    Snowman *body = Snowman_OtherRollable(ball);
    AcreTile_SnapToTileCentre(ball_target(ball), &body->position);
    int body_size = body->size;
    int head_size = ball->size;
    ball_target(ball)->y += 2 * body_size - shift_right(body_size, 3) - shift_right(head_size, 3) - 0x400;
    *ball_fall_speed(ball) = -(FX_Div(0, 0x3e8000) + 0x8f2);
    ball_forget(ball);
    ball_aim(ball);
    *ball_frames(ball) = 0;
    SoundEmitter_PlayB(ball_sound(ball), SNOWBALL_SOUND_JUMP, 0x7f, 0);
    return 1;
}
CLEAN_AS(func_ov068_0226ef04, Snowball_EnterJumpOn)

/* func_ov068_0226effc (update of state 7): the body steps to the middle of its tile on the
 * ground (height 0); after SNOWBALL_MOVE_FRAMES frames it is there, its snowman's map object
 * (by bits 0-1 of its flags) is put on the tile (when there is a map), the item that was there
 * kept in Snowman.item_under and handed to Snowman_KeepDisplacedItem, and it stands as a body
 * (SNOWMAN_STATE_BODY). */
void Snowball_UpdateSettleBody(Snowman *ball)
{
    ball->last_size = ball->size;
    ball->position.x += ball_step(ball)[SNOWBALL_STEP_X];
    ball->position.y = 0;
    ball->position.z += ball_step(ball)[SNOWBALL_STEP_Z];
    if (!ball_count_frame(ball)) {
        return;
    }
    ball->position = *ball_target(ball);
    AcreMap *map = data_021c80bc;
    if (map != NULL) {
        int x, z;
        Position_Tile(&x, &z, (const Position *) (const void *) &ball->position);
        int acre_x = shift_right(x, 4);
        int acre_z = shift_right(z, 4);
        u16 *there = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - acre_x * 16, z - acre_z * 16, 0);
        if (there != NULL) {
            ball->item_under = *there;
        }
        u16 object = MapCode_Snowman(ball->flags & SNOWMAN_NUMBER_MASK);
        AcreTile_SetItem(map, &object, x, z, 0);
    }
    Snowman_KeepDisplacedItem(&ball->item_under);
    Snowman_SetState(ball, SNOWMAN_STATE_BODY);
}
CLEAN_AS(func_ov068_0226effc, Snowball_UpdateSettleBody)

/* func_ov068_0226f0e0 (entry of state 7): the target is the middle of its tile. */
int Snowball_EnterSettleBody(Snowman *ball)
{
    ball_layer_0(ball);
    AcreTile_SnapToTileCentre(ball_target(ball), &ball->position);
    ball_forget(ball);
    ball_aim(ball);
    *ball_frames(ball) = 0;
    return 1;
}
CLEAN_AS(func_ov068_0226f0e0, Snowball_EnterSettleBody)

/* The ground under the ball (CollisionGround_Init): it drifts along the ground's direction by a
 * 32nd of it, shrinks by the factor `melt` and sways up and down by 0.0625 (its angle turning
 * by 0x400 a frame). Once smaller than `gone` it is deleted (size 0). */
static void ball_drift(Snowman *ball, CollisionGround *ground, fx32 melt, fx32 gone)
{
    CollisionGround_Init(ground, &ball->position, 0, 0);
    ball->position.x += shift_right(ground->normal.x, 5);
    ball->position.z += shift_right(ground->normal.z, 5);
    ball->size = FX_MulFunc(ball->size, melt);
    ball->body.rolling.model_offset.y = FX_MulFunc(0x100, sine(*ball_wobble(ball)));
    ball_turn(ball, 0x400);
    if (ball->size < gone) {
        ball->size = 0;
        ball_delete(ball);
    }
}

/* func_ov068_0226f178 (update of state 6): it drifts and melts (by 0xf85 a frame, deleted below
 * 0x100) and sinks by 0.25 a frame, not below 0.125 under the water's level less its size (the
 * ground's word at 0x3c). */
void Snowball_UpdateDrift(Snowman *ball)
{
    CollisionGround ground;
    ball_drift(ball, &ground, 0xf85, 0x100);
    fx32 lowest = ground.limit - ball->size - 0x200;
    ball->position.y -= 0x400;
    if (ball->position.y < lowest) {
        ball->position.y = lowest;
    }
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_ov068_0226f178, Snowball_UpdateDrift)

/* func_ov068_0226f230 (entry of state 6): its z velocity halved and a splash
 * (Snowball_Splash). */
int Snowball_EnterDrift(Snowman *ball)
{
    ball_layer_0(ball);
    ball_forget(ball);
    *ball_wobble(ball) = 0;
    ball->body.rolling.velocity_z = shift_right(ball->body.rolling.velocity_z, 1);
    Snowball_Splash(ball);
    return 1;
}
CLEAN_AS(func_ov068_0226f230, Snowball_EnterDrift)

/* func_ov068_0226f298 (update of state 5): its z velocity grows by 0x158 a frame and it moves
 * by its velocity; its height is -0.24 times how far it went along z from where it started;
 * once that is SNOWBALL_SLIDE_END or more, state 6.
 * QUIRK: the growth is FX_Div(0, 0x3e8000) + 0x158 and the end distance FX_Div(0, 0x64000) +
 * 0x3000, the latter computed only the first time (a function-local static). */
void Snowball_UpdateSlide(Snowman *ball)
{
    ball->body.rolling.velocity_z += FX_Div(0, 0x3e8000) + 0x158;
    ball->position.x += ball->body.rolling.velocity_x;
    ball->position.z += ball->body.rolling.velocity_z;
    fx32 along = ball->position.z - ball_target(ball)->z;
    if (along < 0) {
        along = -along;
    }
    ball->position.y = -FX_MulFunc(along, 0x3d7);
    if ((data_ov068_022786bc & 1) == 0) {
        data_ov068_022786b8 = FX_Div(0, 0x64000) + SNOWBALL_SLIDE_END;
        data_ov068_022786bc |= 1;
    }
    if (along >= data_ov068_022786b8) {
        Snowman_SetState(ball, SNOWBALL_STATE_DRIFT);
    }
}
CLEAN_AS(func_ov068_0226f298, Snowball_UpdateSlide)

/* func_ov068_0226f348 (entry of state 5): it notes where it starts. */
int Snowball_EnterSlide(Snowman *ball)
{
    ball_layer_0(ball);
    ball_forget(ball);
    *ball_target(ball) = ball->position;
    return 1;
}
CLEAN_AS(func_ov068_0226f348, Snowball_EnterSlide)

/* func_ov068_0226f3b0 (update of state 4): it rolls 0x80 a frame towards the middle of the
 * tile (Vec_NormalizeNonZero, Vec_Scale) and falls (Snowball_Fall); within 1.0 of the middle
 * it is kept no higher than a fifth of the way short of 1.0 below 0, and once it is held there
 * closer than 0x333 it bursts (Snowman_Knock). */
void Snowball_UpdateSink(Snowman *ball)
{
    ball->last_size = ball->size;
    Vec3 way;
    Vec_Subtract(&way, ball_centre(ball), &ball->position);
    Vec_NormalizeNonZero(&way);
    Vec_Scale(&way, SNOWBALL_SINK_STEP);
    ball->position.x += way.x;
    ball->position.z += way.z;
    Snowball_Fall(ball);
    fx32 distance = Vec_DistanceXZ(&ball->position, ball_centre(ball));
    fx32 lowest = 0;
    if (distance < 0x1000) {
        lowest = -((0x1000 - distance) / 5);
    }
    if (ball->position.y < lowest) {
        ball->position.y = lowest;
        if (distance < 0x333) {
            Snowman_Knock(ball, 1);
        }
    }
}
CLEAN_AS(func_ov068_0226f3b0, Snowball_UpdateSink)

/* func_ov068_0226f444 (entry of state 4): the middle of its tile noted. */
int Snowball_EnterSink(Snowman *ball)
{
    ball_layer_0(ball);
    AcreTile_SnapToTileCentre(ball_centre(ball), &ball->position);
    ball_forget(ball);
    return 1;
}
CLEAN_AS(func_ov068_0226f444, Snowball_EnterSink)

/* func_ov068_0226f49c (update of SNOWMAN_STATE_KNOCKED): deleted. */
void Snowball_UpdateBroken(Snowman *ball)
{
    ball->last_size = ball->size;
    ball_delete(ball);
}
CLEAN_AS(func_ov068_0226f49c, Snowball_UpdateBroken)

/* func_ov068_0226f4b4 (entry of SNOWMAN_STATE_KNOCKED): it bursts (Snowball_Burst). */
int Snowball_EnterBroken(Snowman *ball)
{
    ball_layer_b(ball);
    ball_forget(ball);
    Snowball_Burst(ball);
    return 1;
}
CLEAN_AS(func_ov068_0226f4b4, Snowball_EnterBroken)

/* func_ov068_0226f504 (update of state 2): the size its collisions use eases towards 1.5 times
 * its size (Approach_EaseS32); it drifts and melts (by 0xfd7 a frame, deleted below 0x80),
 * falls (Snowball_Fall) and floats 0.125 under the water's level less its size (the ground's
 * word at 0x3c). */
void Snowball_UpdateFloat(Snowman *ball)
{
    int wide = ball->size + shift_right(ball->size, 1);
    Approach_EaseS32((int *) (void *) &ball->last_size, wide, 0x200, wide);
    CollisionGround ground;
    ball_drift(ball, &ground, 0xfd7, 0x80);
    Snowball_Fall(ball);
    ball->position.y = ground.limit - ball->size - 0x200;
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_ov068_0226f504, Snowball_UpdateFloat)

/* func_ov068_0226f5cc (entry of state 2): no swaying, no rotation offset, no fall. */
int Snowball_EnterFloat(Snowman *ball)
{
    ball_layer_b(ball);
    *ball_wobble(ball) = 0;
    ball_forget(ball);
    ball->body.rolling.model_offset = data_021fbee8;
    *ball_fall_speed(ball) = 0;
    return 1;
}
CLEAN_AS(func_ov068_0226f5cc, Snowball_EnterFloat)

/* func_ov068_0226f648 (update of state 1): the size its collisions use eases towards 1.5 times
 * its size, it moves by its velocity and falls: for SNOWBALL_DROP_SLOW_FRAMES frames by 1/16
 * a frame (the speed growing by 1), then by its speed, which grows by 0xe9 a frame. Once its
 * collider says it came down (word 1 bit 1) and it is lower than 0.125 under the water's level
 * less its size, it splashes (Snowball_Splash), is put there and floats (state 2).
 * QUIRK: the growth is FX_Div(0, 0x2710000) + 0xe9. */
void Snowball_UpdateFall(Snowman *ball)
{
    int wide = ball->size + shift_right(ball->size, 1);
    Approach_EaseS32((int *) (void *) &ball->last_size, wide, 0xcc, wide);
    ball->position.x += ball->body.rolling.velocity_x;
    ball->position.z += ball->body.rolling.velocity_z;
    u8 *drop = ball_at(ball, SNOWBALL_DROP_FRAMES);
    if (*drop < SNOWBALL_DROP_SLOW_FRAMES) {
        (*ball_fall_speed(ball))++;
        ball->position.y -= 0x100;
        (*drop)++;
    } else {
        fx32 none = FX_Div(0, 0x2710000);
        *ball_fall_speed(ball) += none + 0xe9;
        ball->position.y -= *ball_fall_speed(ball);
    }
    if (collider_word(ball, 1) & SNOWBALL_TOUCHED_DOWN) {
        CollisionGround ground;
        CollisionGround_Init(&ground, &ball->position, 0, 0);
        fx32 lowest = ground.limit - ball->size - 0x200;
        if (ball->position.y < lowest) {
            Snowball_Splash(ball);
            ball->position.y = lowest;
            Snowman_SetState(ball, SNOWBALL_STATE_FLOAT);
        }
        CollisionGround_Destroy(&ground);
    }
}
CLEAN_AS(func_ov068_0226f648, Snowball_UpdateFall)

/* func_ov068_0226f730 (entry of state 1): the size its collisions use and its height are 0, its
 * fall stops, and its velocity grows by 1.1. Slower across the ground than
 * SNOWBALL_FALL_SPEED_MIN, it is brought up to that speed; a ball that did not move takes the
 * player's facing instead (when there is a player), and is put that far from where it was when
 * the frame began.
 * QUIRK: a ball that did not move keeps no velocity at all when there is no player. */
int Snowball_EnterFall(Snowman *ball)
{
    ball_layer_b(ball);
    ball->last_size = 0;
    ball_forget(ball);
    ball->position.y = 0;
    *ball_fall_speed(ball) = 0;
    ball->body.rolling.velocity_x = FX_MulFunc(ball->body.rolling.velocity_x, 0x119a);
    ball->body.rolling.velocity_z = FX_MulFunc(ball->body.rolling.velocity_z, 0x119a);
    *ball_at(ball, SNOWBALL_DROP_FRAMES) = 0;
    Vec3 velocity = {ball->body.rolling.velocity_x, 0, ball->body.rolling.velocity_z};
    fx32 speed = Vec_LengthXZ(&velocity);
    if (speed < SNOWBALL_FALL_SPEED_MIN) {
        if (speed == 0) {
            const SnowmanVisitor *player = SessionPlayers_ActorOf(SNOWBALL_PLAYER);
            if (player != NULL) {
                int yaw = (u16) player->yaw;
                ball->body.rolling.velocity_x = FX_MulFunc(SNOWBALL_FALL_SPEED_MIN, sine(yaw));
                ball->body.rolling.velocity_z = FX_MulFunc(SNOWBALL_FALL_SPEED_MIN, cosine(yaw));
                ball->position.x = ball->last_position.x + ball->body.rolling.velocity_x;
                ball->position.z = ball->last_position.z + ball->body.rolling.velocity_z;
            }
        } else {
            fx32 scale = FX_Div(SNOWBALL_FALL_SPEED_MIN, speed);
            ball->body.rolling.velocity_x = FX_MulFunc(ball->body.rolling.velocity_x, scale);
            ball->body.rolling.velocity_z = FX_MulFunc(ball->body.rolling.velocity_z, scale);
        }
    }
    return 1;
}
CLEAN_AS(func_ov068_0226f730, Snowball_EnterFall)

/* Whether `ball` (pushed, idle and loose, of a pushable size) is put on `body` as a snowman's
 * head: `body` pushable too, idle and loose, the two within their sizes plus 0.25 (Vec_Distance)
 * of each other, the body's tile free of special items and of kind 0 or 1 in main's tables. The
 * snowman is recorded (Snowmen_Add, with its face from the sizes' ratio): both get its number
 * and face and SNOWMAN_FLAG_FIRST_TALK, the head jumps on (state 8) and the body settles (state
 * 7); a snowman of face 0 sends the player a gift (Snowmen_MailGift). */
static int ball_build_snowman(Snowman *ball, Snowman *body, AcreMap *map)
{
    if (body->size < SNOWBALL_SIZE_PUSHABLE) {
        return 0;
    }
    fx32 distance = Vec_Distance(&ball->position, &body->position);
    fx32 reach = FX_Div(0, 0x64000) + 0x400;
    int x, z;
    Position_Tile(&x, &z, (const Position *) (const void *) &body->position);
    u16 item = SNOWBALL_NO_ITEM;
    if (map != NULL) {
        int acre_x = shift_right(x, 4);
        int acre_z = shift_right(z, 4);
        u16 *there = AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x - acre_x * 16, z - acre_z * 16, 0);
        if (there != NULL) {
            item = *there;
        }
    }
    if (MapCode_IsSpecial(&item) != 0) {
        return 0;
    }
    if (distance >= reach + (ball->size + body->size)) {
        return 0;
    }
    if (body->talk_state != SNOWMAN_TALK_IDLE || body->scene_state != SNOWMAN_STATE_LOOSE) {
        return 0;
    }
    if (UnitTypeInfo_Byte09At(x, z) > 1) {
        return 0;
    }
    int face = Snowball_Face(FX_Div(ball->size, body->size));
    int number = Snowmen_Add(data_021f3b56, ball->size, body->size, face);
    if (number == -1) {
        return 0;
    }
    u16 keep = (u16) ~(SNOWMAN_NUMBER_MASK | (3 << SNOWMAN_KIND_SHIFT));
    u16 marks = (u16) ((number & SNOWMAN_NUMBER_MASK) | ((face & 3) << SNOWMAN_KIND_SHIFT) | SNOWMAN_FLAG_FIRST_TALK);
    body->flags = (u16) ((body->flags & keep) | marks);
    ball->flags = (u16) ((ball->flags & keep) | marks);
    Snowman_SetState(ball, SNOWBALL_STATE_JUMP_ON);
    Snowman_SetState(body, SNOWBALL_STATE_SETTLE_BODY);
    if (face == 0) {
        Snowmen_MailGift();
    }
    return 1;
}

/* func_ov068_0226f854 (update of SNOWMAN_STATE_LOOSE). A ball pushed this frame while both
 * machines are idle, moving and of a pushable size may be built into a snowman with the first
 * other loose ball (ball_build_snowman); otherwise it falls and moves (Snowball_Fall), and:
 * - where the ground under it lies below 0 (CollisionGround_GetHeight), it falls (state 1);
 * - on ground of attribute 0x16 or 0x17 of the second set (unk_30 1), it slides (state 5);
 * - on a tile holding item 0xfc or 0xfd, within 1.0 of the tile's middle, it sinks (state 4),
 *   unless the other loose ball is already sinking (idle, state 4) and the two touch;
 * - not pushed, both machines idle, moving at least sqrt(0x12c000 / 0x2710000) (FX_Div), it
 *   bursts (Snowman_Knock) against what it hit when that faces it within 0x1000.
 * QUIRK: that last speed is taken from its x velocity and the z distance it moved this frame
 * (both kept at 0x36c). */
void Snowball_UpdateLoose(Snowman *ball)
{
    AcreMap *map = data_021c80bc;
    ball->last_size = ball->size;
    fx32 velocity_z = ball->body.rolling.velocity_z;
    fx32 speed = FX_MulFunc(ball->body.rolling.velocity_x, ball->body.rolling.velocity_x);
    speed += FX_MulFunc(velocity_z, velocity_z);
    if (ball->talk_state == SNOWMAN_TALK_IDLE && ball->scene_state == SNOWMAN_STATE_LOOSE && speed > 0 &&
        ball->size >= SNOWBALL_SIZE_PUSHABLE && (ball->flags & SNOWMAN_FLAG_PUSHED)) {
        Snowman *body = Snowman_OtherRollable(ball);
        if (body != NULL && ball_build_snowman(ball, body, map)) {
            return;
        }
    }

    Snowball_Fall(ball);
    CollisionGround ground;
    CollisionGround_Init(&ground, &ball->position, 0, 0);
    if (CollisionGround_GetHeight(&ground, 0) < 0) {
        Snowman_SetState(ball, SNOWBALL_STATE_FALL);
        CollisionGround_Destroy(&ground);
        return;
    }
    CollisionGround other_set;
    CollisionGround_Init(&other_set, &ball->position, 1, 0);
    if (other_set.unk_30 == 1 && (other_set.attr == SNOWBALL_SLIDE_GROUND_A || other_set.attr == SNOWBALL_SLIDE_GROUND_B)) {
        Snowman_SetState(ball, SNOWBALL_STATE_SLIDE);
        CollisionGround_Destroy(&other_set);
        CollisionGround_Destroy(&ground);
        return;
    }
    CollisionGround_Destroy(&other_set);

    if (map != NULL) {
        Vec3 middle;
        AcreTile_SnapToTileCentre(&middle, &ball->position);
        u16 *item = AcreTile_ItemAt(map, &ball->position, 0);
        if (item != NULL && *item >= SNOWBALL_SINK_ITEM_FIRST && *item <= SNOWBALL_SINK_ITEM_LAST &&
            Vec_DistanceXZ(&middle, &ball->position) < 0x1000) {
            Snowman *other = Snowman_OtherRollable(ball);
            int may_sink = 1;
            if (other != NULL && other->talk_state == SNOWMAN_TALK_IDLE && other->scene_state == SNOWBALL_STATE_SINK) {
                may_sink = Vec_DistanceXZ(&other->position, &ball->position) > other->size + ball->size;
            }
            if (may_sink && Snowman_SetState(ball, SNOWBALL_STATE_SINK) != 0) {
                CollisionGround_Destroy(&ground);
                return;
            }
        }
    }

    fx32 *motion = (fx32 *) (void *) ball_at(ball, SNOWBALL_MOTION);
    motion[0] = ball->body.rolling.velocity_x;
    motion[1] = ball->position.z - ball->last_position.z;
    if (ball->talk_state == SNOWMAN_TALK_IDLE && ball->scene_state == SNOWMAN_STATE_LOOSE &&
        !(ball->flags & SNOWMAN_FLAG_PUSHED)) {
        fx32 moved_z = motion[1];
        fx32 moved = FX_MulFunc(motion[0], motion[0]);
        moved += FX_MulFunc(moved_z, moved_z);
        if (moved >= FX_Div(0x12c000, 0x2710000)) {
            u32 walls = ball->collisions;
            if (walls != 0) {
                int direction = Math_Atan2(motion[0], motion[1]);
                for (u32 i = 0; i < walls; i++) {
                    if (Math_AbsDiff16((s16) (wall_angle(ball, (int) i) + 0x8000), direction) < 0x1000 &&
                        Snowman_Knock(ball, 1) != 0) {
                        CollisionGround_Destroy(&ground);
                        return;
                    }
                }
            }
        }
    }
    CollisionGround_Destroy(&ground);
}
CLEAN_AS(func_ov068_0226f854, Snowball_UpdateLoose)

/* func_ov068_0226fc2c (entry of SNOWMAN_STATE_LOOSE) */
int Snowball_EnterLoose(Snowman *ball)
{
    ball_layer_b(ball);
    return 1;
}
CLEAN_AS(func_ov068_0226fc2c, Snowball_EnterLoose)

/* func_ov068_0226fc48: a splash (effect 0x3f) at the ball's place on the water's surface (1/16
 * above data_020c904c), as big as the ball, with sound 0x821; the fish within 5.0 are startled
 * (func_ov003_02228400). */
void Snowball_Splash(Snowman *ball)
{
    Vec3 at = ball->position;
    at.y = data_020c904c + 0x100;
    s16 size = (s16) FX_Div(ball->size, 0x1000);
    EffectSystem_StartKind(SNOWBALL_EFFECT_SPLASH, &at, NULL, &size);
    SoundEmitter_PlayB(ball_sound(ball), SNOWBALL_SOUND_SPLASH, 0x7f, 0);
    FishShadow_ScareNear(&ball->position, SNOWBALL_STARTLE_REACH);
}
CLEAN_AS(func_ov068_0226fc48, Snowball_Splash)

/* func_ov068_0226fcbc: the ball bursts (effect 0x3e, as big as the ball) where its models are
 * drawn, its size less 0.25 above, with sound 0x81f. */
void Snowball_Burst(Snowman *ball)
{
    Vec3 at;
    Vec_Add(&at, &ball->position, &ball->body.rolling.model_offset);
    at.y += ball->size - 0x400;
    s16 size = (s16) FX_Div(ball->size, 0x1000);
    EffectSystem_StartKind(SNOWBALL_EFFECT_BURST, &at, NULL, &size);
    SoundEmitter_PlayB(ball_sound(ball), SNOWBALL_SOUND_BURST, 0x7f, 0);
}
CLEAN_AS(func_ov068_0226fcbc, Snowball_Burst)

/* func_ov068_0226fd28: a snowman's face from the ratio of its head's size to its body's (20.12):
 * 0 from 0.9 to below 1.0 (the best), 1 from 0.8 or up to 1.1, 2 from 0.7 or up to 1.2, else 3. */
int Snowball_Face(fx32 ratio)
{
    if (ratio < 0x99a) {
        return 3;
    }
    if (ratio < 0xb33) {
        return 2;
    }
    if (ratio < 0xccd) {
        return 1;
    }
    if (ratio < 0xe66) {
        return 0;
    }
    if (ratio < 0x1000) {
        return 1;
    }
    if (ratio < 0x119a) {
        return 2;
    }
    return 3;
}
CLEAN_AS(func_ov068_0226fd28, Snowball_Face)

/* func_ov068_0226fd80: standing on something its fall speed is 0, else it grows by
 * SNOWBALL_GRAVITY up to SNOWBALL_FALL_MAX; it falls by it, and unless pushed or placed this
 * frame it moves by its velocity. */
void Snowball_Fall(Snowman *ball)
{
    fx32 *speed = ball_fall_speed(ball);
    if (collider_word(ball, 0) & SNOWBALL_ON_GROUND) {
        *speed = 0;
    } else {
        *speed += SNOWBALL_GRAVITY;
        if (*speed > SNOWBALL_FALL_MAX) {
            *speed = SNOWBALL_FALL_MAX;
        }
    }
    ball->position.y -= *speed;
    if (ball->flags & SNOWMAN_FLAG_PUSHED) {
        return;
    }
    if (ball->flags & SNOWMAN_FLAG_PLACED) {
        return;
    }
    ball->position.x += ball->body.rolling.velocity_x;
    ball->position.z += ball->body.rolling.velocity_z;
}
CLEAN_AS(func_ov068_0226fd80, Snowball_Fall)
