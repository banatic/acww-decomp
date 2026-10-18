/* Shots into the sky from a player's position (sky_shots.h). */
#include "sky_shots.h"

#include "actor_table.h"
#include "autoload_2/approach.h"
#include "block_021d27ac.h"
#include "camera_control.h"
#include "clean.h"
#include "daily_bits.h"
#include "item_1568_count.h"
#include "near_spot.h"
#include "ov003/field_actor.h"
#include "ov004/member_pointer.h"
#include "player_record.h"
#include "player_records.h"
#include "sky_object_kinds.h"
#include "sky_object_sounds.h"
#include "state_block.h"
#include "event_announce.h"
#include "ov003/tile_event.h"
#include "player_actor_ops.h"
#include "player_actors.h"

static_assert(sizeof(SkyShotRequest) == 0x14, "a request");
static_assert(offsetof(SkyShotRequest, triple) == 0x10, "triple");
static_assert(sizeof(SkyShotsHit) == 0x24, "the hit");
static_assert(offsetof(SkyShotsHit, side) == 0x18, "side");
static_assert(offsetof(SkyShotsHit, pitch) == 0x1a, "pitch");
static_assert(offsetof(SkyShotsHit, done) == 0x1e, "done");
static_assert(offsetof(SkyShotsHit, variant) == 0x21, "variant");

#define SKY_SHOTS_TRIPLE_ITEM 0x137b /* the item held that shoots three */
#define SKY_SHOTS_SECOND 0x10        /* SkyObject.param: the second of three, and the third */
#define SKY_SHOTS_THIRD 0x20
#define SKY_SHOTS_LOOK_PITCH 4000
#define SKY_SHOTS_LOOK_YAW_MAX 5000
#define SKY_SHOTS_SCREEN_MIDDLE 0x80000 /* x 128 (fx32) */
#define SKY_SHOTS_EASE_SLOW 0x50
#define SKY_SHOTS_EASE_FAST 0x190
#define SKY_SHOTS_HITS_MAX 16
#define SKY_SHOTS_FLAG_14 0x14 /* the daily bit cleared for each player at the end of state 6 */

extern SkyObjectSounds data_021fbb14; /* the sounds of the sky's objects */
extern StateBlock data_021dc7a8;
extern u8 data_021ebcd2[]; /* Item1568Count */
extern u32 data_021f6cc4;  /* SkyShots_RunHit's table was filled */
extern MemberPointer data_021f6d48[SKY_SHOTS_HIT_STATES];
extern const MemberPointer __ptmf_null;
extern const MemberPointer data_020e5af8, data_020e5ac0, data_020e5a00, data_020e5bd0, data_020e5ce8, data_020e5a68,
    data_020e59a0, data_020e5988, data_020e5be0;

extern fx32 FX_Div(fx32 numerator, fx32 denominator);

static const MemberPointer *const sky_shots_hit_constants[SKY_SHOTS_HIT_STATES] = {
    &__ptmf_null,   &data_020e5af8, &data_020e5ac0, &data_020e5a00, &data_020e5bd0,
    &data_020e5ce8, &data_020e5a68, &data_020e59a0, &data_020e5988, &data_020e5be0,
};

/* func_020bcfbc: each pending request launched as objects in its player's three entries: one
 * (parameter: the player), or with the triple shot two more (the player with 0x10 and with
 * 0x20); when the first cannot be added the player's state is ended at once. The request is
 * then cleared. */
void SkyShots_Launch(SkyObjects *objects)
{
    for (int player = 0; player < SKY_SHOTS_PLAYERS; player++) {
        SkyShotRequest *request = SkyShots_Request(objects, player);
        if (request->pending == 0) {
            continue;
        }
        int triple = request->triple;
        int entry = SKY_ENTRY_SHOTS + 3 * player;
        if (SkyObjects_Add(objects, SKY_OBJECT_SHOT, entry, NULL, player) != NULL) {
            if (triple) {
                SkyObjects_Add(objects, SKY_OBJECT_SHOT, entry + 1, NULL, player | SKY_SHOTS_SECOND);
                SkyObjects_Add(objects, SKY_OBJECT_SHOT, entry + 2, NULL, player | SKY_SHOTS_THIRD);
            }
        } else {
            SkyShots_EndPlayerState((SkyShotsHit *) (void *) objects->unk_2fa8, request->player);
        }
        SkyShots_ClearRequest(request);
    }
}
CLEAN_AS(func_020bcfbc, SkyShots_Launch)

/* func_020bdf58: request `index`. */
SkyShotRequest *SkyShots_Request(SkyObjects *objects, int index)
{
    return (SkyShotRequest *) (void *) objects->unk_2f58 + index;
}
CLEAN_AS(func_020bdf58, SkyShots_Request)

/* func_020bdf68: a shot asked for by `player` (a player past 3 takes request 0): with a
 * position, the request filled (three objects when the player holds the triple shot's item)
 * and, for this system's player, the hit set to wait (func_020beba4); without one the
 * player's state is ended at once. */
void SkyShots_Fire(SkyObjects *objects, int player)
{
    int index = player < SKY_SHOTS_PLAYERS ? player : 0;
    const Position *from = (const Position *) PlayerActorOps_StartPosition(player);
    SkyShotsHit *hit = (SkyShotsHit *) (void *) objects->unk_2fa8;
    if (from == NULL) {
        SkyShots_EndPlayerState(hit, player);
        return;
    }
    u16 item;
    PlayerActorOps_HeldItem(&item, player);
    SkyShots_SetRequest(SkyShots_Request(objects, index), player, (const Vec3 *) (const void *) from,
                        item == SKY_SHOTS_TRIPLE_ITEM);
    SkyShots_StartWaiting(hit, player);
}
CLEAN_AS(func_020bdf68, SkyShots_Fire)

/* func_020be550: a request's destructor: nothing to do. */
void SkyShots_DestructRequest(SkyShotRequest *request)
{
    (void) request;
}
CLEAN_AS(func_020be550, SkyShots_DestructRequest)

/* func_020be6ac: the look given to this system's player eased back towards straight ahead by
 * the steps, and given. */
void SkyShots_EaseLook(SkyShotsHit *hit, int pitch_step, int yaw_step)
{
    Approach_S16Wrapped(&hit->pitch, 0, (s16) pitch_step);
    Approach_S16Wrapped(&hit->yaw, 0, (s16) yaw_step);
    PlayerActorOps_SetLook(hit->pitch, hit->yaw, SKY_SHOTS_THIS_PLAYER);
}
CLEAN_AS(func_020be6ac, SkyShots_EaseLook)

/* func_020be6e4: this system's player made to look up at what was hit: the yaw from how far
 * across the screen it is from the player (from the middle without a player), 10000 per 256
 * pixels the other way, at most 5000 either way. */
void SkyShots_LookAtHit(SkyShotsHit *hit)
{
    const Position *player = (const Position *) PlayerActorOps_StartPosition(SKY_SHOTS_THIS_PLAYER);
    fx32 player_x = SKY_SHOTS_SCREEN_MIDDLE;
    if (player != NULL) {
        SkyShots_ScreenX(&player_x, (const Vec3 *) player);
    }
    int yaw = (FX_Div(hit->x - player_x, 0x100000) * -10000) >> 12;
    if (yaw < -SKY_SHOTS_LOOK_YAW_MAX) {
        yaw = -SKY_SHOTS_LOOK_YAW_MAX;
    } else if (yaw > SKY_SHOTS_LOOK_YAW_MAX) {
        yaw = SKY_SHOTS_LOOK_YAW_MAX;
    }
    PlayerActorOps_SetLook(SKY_SHOTS_LOOK_PITCH, (s16) yaw, SKY_SHOTS_THIS_PLAYER);
    hit->pitch = SKY_SHOTS_LOOK_PITCH;
    hit->yaw = (s16) yaw;
}
CLEAN_AS(func_020be6e4, SkyShots_LookAtHit)

/* func_020be758: no hit (the shooter: this system's player, the scale 1). */
void SkyShots_ResetHit(SkyShotsHit *hit)
{
    hit->state = SKY_SHOTS_HIT_NONE;
    hit->player = SKY_SHOTS_THIS_PLAYER;
    hit->timer = 0;
    hit->x = 0;
    hit->y = 0;
    hit->scale = 0x1000;
    hit->side = 0;
    hit->pitch = 0;
    hit->yaw = 0;
    hit->done = 0;
    hit->sound_7f9 = 0;
    hit->sound_7fa = 0;
    hit->variant = 0;
}
CLEAN_AS(func_020be758, SkyShots_ResetHit)

/* The sound `number` asked for from the first of the sky's sources, at the hit's point. */
static void sky_shots_play(SkyShotsHit *hit, int number)
{
    Vec3 point;
    SkyObjectKinds_SoundPoint(&point, hit->x, hit->y, hit->scale);
    SkyObjectSounds_PlayHeld(&data_021fbb14, 0, number, &point);
}

/* func_020be784: state 9: the look eased back; when the timer runs out a spot picked near the
 * shooter (NearSpot_Pick on the side the hit fell), the player stopped, the camera's previous
 * mode back, and no hit. */
void SkyShots_HitEnd9(SkyShotsHit *hit)
{
    SkyShots_EaseLook(hit, SKY_SHOTS_EASE_FAST, SKY_SHOTS_EASE_FAST);
    hit->timer--;
    if (hit->timer > 0) {
        return;
    }
    const Position *from = (const Position *) PlayerActorOps_StartPosition(hit->player);
    if (from != NULL) {
        NearSpot_Pick((NearSpot *) (void *) Block021d27ac_Part24(Block021d27ac_Get()), from, hit->side);
    }
    FieldActor_PlayerStop();
    CameraControl_SetPreviousMode();
    SkyShots_ResetHit(hit);
}
CLEAN_AS(func_020be784, SkyShots_HitEnd9)

/* func_020be7d4: state 8 (what was hit has fallen): the look eased back slowly; when the timer
 * runs out the camera's mode 0x5c3, sound 0x800 at the hit and state 9 for 30 frames. */
void SkyShots_HitFall8(SkyShotsHit *hit)
{
    SkyShots_EaseLook(hit, SKY_SHOTS_EASE_SLOW, 0);
    if (hit->timer > 0) {
        hit->timer--;
        return;
    }
    CameraControl_SetMode17(0x5c3);
    sky_shots_play(hit, 0x800);
    hit->timer = 30;
    hit->state = SKY_SHOTS_HIT_END_9;
}
CLEAN_AS(func_020be7d4, SkyShots_HitFall8)

/* func_020be828: state 7: the player looks at the hit. */
void SkyShots_HitLook7(SkyShotsHit *hit)
{
    SkyShots_LookAtHit(hit);
}
CLEAN_AS(func_020be828, SkyShots_HitLook7)

/* func_020be830: state 6: the look eased back; when the timer runs out the player stopped, the
 * camera's previous mode back, daily bit 0x14 of each of the town's players cleared, the count
 * of data_021ebcd2 cleared, func_0204130c told of event 0x44, and no hit. */
void SkyShots_HitEnd6(SkyShotsHit *hit)
{
    SkyShots_EaseLook(hit, SKY_SHOTS_EASE_FAST, SKY_SHOTS_EASE_FAST);
    hit->timer--;
    if (hit->timer > 0) {
        return;
    }
    FieldActor_PlayerStop();
    CameraControl_SetPreviousMode();
    for (int player = 0; player < SKY_SHOTS_PLAYERS; player++) {
        u8 *record = PlayerRecords_TownRecord(data_021dc7a8.players, player);
        if (record != NULL && PlayerRecord_HasPlayer(record)) {
            DailyBits_Clear((DailyBits *) (void *) PlayerRecord_Field23EC(record), SKY_SHOTS_FLAG_14);
        }
    }
    Item1568Count_Clear(data_021ebcd2);
    EventAnnounce_Request(0x44, 0x63, 0);
    SkyShots_ResetHit(hit);
}
CLEAN_AS(func_020be830, SkyShots_HitEnd6)

/* func_020be8a8: state 5: the look eased back slowly; when the timer runs out the camera's
 * mode 0xa3d, sound 0x7fd at the hit and state 6 for 50 frames. */
void SkyShots_HitFall5(SkyShotsHit *hit)
{
    SkyShots_EaseLook(hit, SKY_SHOTS_EASE_SLOW, 0);
    hit->timer--;
    if (hit->timer > 0) {
        return;
    }
    CameraControl_SetMode17(0xa3d);
    sky_shots_play(hit, 0x7fd);
    hit->timer = 50;
    hit->state = SKY_SHOTS_HIT_END_6;
}
CLEAN_AS(func_020be8a8, SkyShots_HitFall5)

/* func_020be8fc: state 4: the player looks at the hit. */
void SkyShots_HitLook4(SkyShotsHit *hit)
{
    SkyShots_LookAtHit(hit);
}
CLEAN_AS(func_020be8fc, SkyShots_HitLook4)

/* func_020be904: state 3: the look eased back; as the timer reaches 0, func_ov003_02220c8c
 * given the variant and the hit's x from the screen's middle (pixels), done when it says no;
 * sound 0x7f9 or 0x7fa at the hit when asked for; once done the player stopped and no hit. */
void SkyShots_HitDrop3(SkyShotsHit *hit)
{
    SkyShots_EaseLook(hit, SKY_SHOTS_EASE_FAST, SKY_SHOTS_EASE_FAST);
    if (hit->timer > 0) {
        hit->timer--;
        if (hit->timer == 0 &&
            TileEvent_StartKindC(hit->variant != 0, ((hit->x + 0x800) >> 12) - (SKY_SHOTS_SCREEN_MIDDLE >> 12)) == 0) {
            hit->done = 1;
        }
    }
    if (hit->sound_7f9 != 0 || hit->sound_7fa != 0) {
        sky_shots_play(hit, hit->sound_7f9 != 0 ? 0x7f9 : 0x7fa);
        hit->sound_7f9 = 0;
        hit->sound_7fa = 0;
    }
    if (hit->done != 0) {
        FieldActor_PlayerStop();
        SkyShots_ResetHit(hit);
    }
}
CLEAN_AS(func_020be904, SkyShots_HitDrop3)

/* func_020be9b0: state 2: the player looks at the hit. */
void SkyShots_HitLook2(SkyShotsHit *hit)
{
    SkyShots_LookAtHit(hit);
}
CLEAN_AS(func_020be9b0, SkyShots_HitLook2)

/* func_020be9b8: state 1: when the timer runs out without a hit the shooter's state is ended
 * at once, and no hit. */
void SkyShots_HitWait(SkyShotsHit *hit)
{
    hit->timer--;
    if (hit->timer > 0) {
        return;
    }
    SkyShots_EndPlayerState(hit, hit->player);
    SkyShots_ResetHit(hit);
}
CLEAN_AS(func_020be9b8, SkyShots_HitWait)

/* func_020be9dc: this system's player has counted 16 hits. */
int SkyShots_HitCountFull(void)
{
    return PlayerRecord_Byte2452(PlayerRecords_Current()) >= SKY_SHOTS_HITS_MAX;
}
CLEAN_AS(func_020be9dc, SkyShots_HitCountFull)

/* func_020be9f8: a hit counted for this system's player, up to 16. */
void SkyShots_CountHit(void)
{
    u8 *record = PlayerRecords_Current();
    u8 hits = PlayerRecord_Byte2452(record);
    if (hits < SKY_SHOTS_HITS_MAX) {
        PlayerRecord_SetByte2452(record, (u8) (hits + 1));
    }
}
CLEAN_AS(func_020be9f8, SkyShots_CountHit)

/* func_020bea1c: the hit's state run through the table of members (data_021f6d48, filled once
 * from the constants), when the state has one.
 * REQUIRES: the state is 0 to 9. */
void SkyShots_RunHit(SkyShotsHit *hit)
{
    MemberTable_InitOnce(&data_021f6cc4, data_021f6d48, sky_shots_hit_constants, SKY_SHOTS_HIT_STATES);
    MemberPointer member = data_021f6d48[hit->state];
    if (member.function != 0) {
        MemberPointer_CallVoid(&member, hit);
    }
}
CLEAN_AS(func_020bea1c, SkyShots_RunHit)

/* ---- The hit's states set, the requests, and the shots' objects */

#define SKY_SHOTS_FALL8_FRAMES 20
#define SKY_SHOTS_FALL5_FRAMES 30
#define SKY_SHOTS_DROP3_FRAMES 2
#define SKY_SHOTS_WAIT_FRAMES 43
#define SKY_SHOTS_NO_PLAYER 4
#define SKY_SHOTS_END_NOW 0    /* FieldActor_PlayerEndState: end the state at once */
#define SKY_SHOTS_END_WATCH 1  /* ask for state 0x65 */
#define SKY_SHOTS_REACH 0x1000 /* a shot hits within 1.0 of its point */
#define SKY_SHOTS_ANIMATION 0x2d
#define SKY_SHOTS_PRIORITY 2
#define SKY_SHOTS_DELAY 24
#define SKY_SHOTS_START_Y 0xc5000 /* y 197: below the screen */
#define SKY_SHOTS_SPEED (-0xc000) /* 12 pixels a frame up */
#define SKY_SHOTS_SPREAD 0x2800   /* the second and third of three: 2.5 pixels a frame across */
#define SKY_SHOTS_SHOWN_Y 0xc0000 /* shown above line 0xc0 */
#define SKY_SHOTS_FAR_NORTH (-0x14000)
#define SKY_SHOTS_FAR_SOUTH 0xf000
#define SKY_SHOTS_FAR 0x80000000u /* SkyObjectBody.shot_flags: fired far from the camera */

extern SkyObject data_021f9a3c[SKY_SHOTS_PLAYERS * 3]; /* the shots' entries, 33 to 44 */
extern u8 data_021f8b48[];                             /* the sky's objects (SkyObjects) */
extern const Vec3 data_021c67d0;                       /* the point the camera looks at */
extern const fx32 data_020ca0e8;                       /* an acre's depth in world units */
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);

/* func_020beb00: where what was hit is on the screen, its scale, and the side it fell. */
void SkyShots_SetHitPoint(SkyShotsHit *hit, u32 x, u32 y, u32 scale, u8 side)
{
    hit->x = (fx32) x;
    hit->y = (fx32) y;
    hit->scale = (fx32) scale;
    hit->side = side;
}
CLEAN_AS(func_020beb00, SkyShots_SetHitPoint)

/* func_020beb14: state 8 for 20 frames. */
void SkyShots_StartFall8(SkyShotsHit *hit)
{
    hit->state = SKY_SHOTS_HIT_FALL_8;
    hit->timer = SKY_SHOTS_FALL8_FRAMES;
}
CLEAN_AS(func_020beb14, SkyShots_StartFall8)

/* func_020beb20: state 7: the shooter's actor asked to watch (state 0x65), and a hit counted. */
void SkyShots_StartLook7(SkyShotsHit *hit)
{
    hit->state = SKY_SHOTS_HIT_LOOK_7;
    FieldActor_PlayerEndState(SKY_SHOTS_END_WATCH, hit->player);
    SkyShots_CountHit();
}
CLEAN_AS(func_020beb20, SkyShots_StartLook7)

/* func_020beb3c: state 5 for 30 frames. */
void SkyShots_StartFall5(SkyShotsHit *hit)
{
    hit->state = SKY_SHOTS_HIT_FALL_5;
    hit->timer = SKY_SHOTS_FALL5_FRAMES;
}
CLEAN_AS(func_020beb3c, SkyShots_StartFall5)

/* func_020beb48: state 4: the shooter's actor asked to watch, and a hit counted. */
void SkyShots_StartLook4(SkyShotsHit *hit)
{
    hit->state = SKY_SHOTS_HIT_LOOK_4;
    FieldActor_PlayerEndState(SKY_SHOTS_END_WATCH, hit->player);
    SkyShots_CountHit();
}
CLEAN_AS(func_020beb48, SkyShots_StartLook4)

/* func_020beb64: state 3 for 2 frames, not done, no sound asked for. */
void SkyShots_StartDrop3(SkyShotsHit *hit)
{
    hit->state = SKY_SHOTS_HIT_DROP_3;
    hit->timer = SKY_SHOTS_DROP3_FRAMES;
    hit->done = 0;
    hit->sound_7f9 = 0;
    hit->sound_7fa = 0;
}
CLEAN_AS(func_020beb64, SkyShots_StartDrop3)

/* func_020beb78: state 2 with its variant: the shooter's actor asked to watch, and a hit
 * counted. */
void SkyShots_StartLook2(SkyShotsHit *hit, int variant)
{
    hit->variant = (u8) variant;
    hit->state = SKY_SHOTS_HIT_LOOK_2;
    FieldActor_PlayerEndState(SKY_SHOTS_END_WATCH, hit->player);
    SkyShots_CountHit();
}
CLEAN_AS(func_020beb78, SkyShots_StartLook2)

/* func_020beb98: `player`'s state ended at once (the hit is not touched). */
void SkyShots_EndPlayerState(SkyShotsHit *hit, int player)
{
    (void) hit;
    FieldActor_PlayerEndState(SKY_SHOTS_END_NOW, player);
}
CLEAN_AS(func_020beb98, SkyShots_EndPlayerState)

/* func_020beba4: for this system's player, the hit waiting 43 frames for its shot to hit. */
void SkyShots_StartWaiting(SkyShotsHit *hit, int player)
{
    if (player == PlayerActors_OwnPlayer()) {
        hit->state = SKY_SHOTS_HIT_WAITING;
        hit->player = player;
        hit->timer = SKY_SHOTS_WAIT_FRAMES;
    }
}
CLEAN_AS(func_020beba4, SkyShots_StartWaiting)

/* func_020bebc8: the hit's constructor: no hit. */
SkyShotsHit *SkyShots_ConstructHit(SkyShotsHit *hit)
{
    SkyShots_ResetHit(hit);
    return hit;
}
CLEAN_AS(func_020bebc8, SkyShots_ConstructHit)

/* func_020bebd8: no request. */
void SkyShots_ClearRequest(SkyShotRequest *request)
{
    request->player = SKY_SHOTS_NO_PLAYER;
    request->from.x = 0;
    request->from.y = 0;
    request->from.z = 0;
    request->triple = 0;
    request->pending = 0;
}
CLEAN_AS(func_020bebd8, SkyShots_ClearRequest)

/* func_020bebec: a request of `player` from `from`, pending. */
void SkyShots_SetRequest(SkyShotRequest *request, int player, const Vec3 *from, u8 triple)
{
    request->player = player;
    request->from.x = from->x;
    request->from.y = from->y;
    request->from.z = from->z;
    request->triple = triple;
    request->pending = 1;
}
CLEAN_AS(func_020bebec, SkyShots_SetRequest)

/* func_020bec04: a request's constructor (the requests', by __cxa_vec_ctor): no request. */
SkyShotRequest *SkyShots_ConstructRequest(SkyShotRequest *request)
{
    SkyShots_ClearRequest(request);
    return request;
}
CLEAN_AS(func_020bec04, SkyShots_ConstructRequest)

/* func_020bf308: whether a running shot that can hit is in the box of `width` by `height`
 * (scaled by the object's scale) centred `offset_y` (scaled) below the object; each such shot
 * is marked hit. A shot reaches 1.0 around its point, and below it by its speed. */
int SkyShots_HitsBox(SkyObject *object, fx32 width, fx32 height, fx32 offset_y)
{
    fx32 half_width = FX_MulFunc(width, object->scale_x) / 2;
    fx32 half_height = FX_MulFunc(height, object->scale_y) / 2;
    fx32 centre_y = object->position.y + FX_MulFunc(offset_y, object->scale_y);
    fx32 left = object->position.x - half_width;
    fx32 right = object->position.x + half_width;
    fx32 top = centre_y - half_height;
    fx32 bottom = centre_y + half_height;
    int hit = 0;
    for (int i = 0; i < SKY_SHOTS_PLAYERS * 3; i++) {
        SkyObjectBody *shot = SkyObject_Body(&data_021f9a3c[i]);
        if (shot->state != SKY_OBJECT_RUNNING || shot->can_hit == 0) {
            continue;
        }
        fx32 speed = shot->velocity.y < 0 ? -shot->velocity.y : shot->velocity.y;
        fx32 shot_left = shot->position.x - SKY_SHOTS_REACH;
        fx32 shot_top = shot->position.y - SKY_SHOTS_REACH;
        fx32 shot_bottom = shot->position.y + SKY_SHOTS_REACH + speed;
        fx32 shot_right = shot->position.x + SKY_SHOTS_REACH;
        if (left <= shot_right && right >= shot_left && top <= shot_bottom && bottom >= shot_top) {
            hit = 1;
            shot->hit = 1;
        }
    }
    return hit;
}
CLEAN_AS(func_020bf308, SkyShots_HitsBox)

/* func_020bfb18: a shot's object taken down. */
void SkyShots_ObjectTakeDown(SkyObject *object)
{
    SkyObjectKinds_Remove(object);
}
CLEAN_AS(func_020bfb18, SkyShots_ObjectTakeDown)

/* func_020bfb20: a frame of a shot's object: after its delay it moves (the second and third of
 * three start spreading two frames after that), done once out of view or once it hit; while
 * hidden it is shown once above line 0xc0, unless it was fired far from the camera. */
void SkyShots_ObjectRun(SkyObject *object)
{
    SkyObjectBody *shot = SkyObject_Body(object);
    u32 flags = shot->shot_flags;
    shot->shot_timer--;
    if (shot->shot_timer < 0) {
        if (shot->shot_timer == -2) {
            u32 which = (flags >> 4) & 0xf;
            if (which == SKY_SHOTS_SECOND >> 4) {
                shot->velocity.x = SKY_SHOTS_SPREAD;
            } else if (which == SKY_SHOTS_THIRD >> 4) {
                shot->velocity.x = -SKY_SHOTS_SPREAD;
            }
        }
        VEC_Add(&shot->position, &shot->velocity, &shot->position);
        if (SkyObject_OutOfView(&shot->position) || shot->hit != 0) {
            shot->state = SKY_OBJECT_DONE;
        }
    }
    if (shot->hidden != 0 && (flags & SKY_SHOTS_FAR) == 0 && shot->position.y < SKY_SHOTS_SHOWN_Y) {
        shot->hidden = 0;
    }
}
CLEAN_AS(func_020bfb20, SkyShots_ObjectRun)

/* func_020bfbec: a shot's object set up from its player's request (`param`: the player, with
 * 0x10 or 0x20 for the second and third of three): below the screen under the player's place,
 * rising after 24 frames; it can hit when it is this system's player's, fired in the town's
 * two northern rows of acres. Hidden.
 * QUIRK: the game hides it when it was fired far from the camera or starts at or below line
 * 0xc0, which it always does. */
void SkyShots_ObjectSetUp(SkyObject *object, int param)
{
    SkyObjectBody *shot = SkyObject_Body(object);
    const SkyShotRequest *request = SkyShots_Request((SkyObjects *) (void *) data_021f8b48, param & 0xf);
    shot->animation = SKY_SHOTS_ANIMATION;
    shot->priority = SKY_SHOTS_PRIORITY;
    shot->shot_timer = SKY_SHOTS_DELAY;
    int player = request->player;
    shot->shot_player = player;
    fx32 x;
    SkyShots_ScreenX(&x, (const Vec3 *) ((const Position *) (const void *) &request->from));
    shot->position.x = x;
    shot->position.y = SKY_SHOTS_START_Y;
    shot->position.z = 0;
    shot->velocity.x = 0;
    shot->velocity.y = SKY_SHOTS_SPEED;
    shot->velocity.z = 0;
    fx32 north_rows = data_020ca0e8 * 2;
    if (player == PlayerActors_OwnPlayer() && request->from.z < north_rows) {
        shot->can_hit = 1;
    }
    fx32 from_camera = request->from.z - data_021c67d0.z;
    u32 flags = (u32) param;
    if (from_camera < SKY_SHOTS_FAR_NORTH || from_camera > SKY_SHOTS_FAR_SOUTH) {
        flags |= SKY_SHOTS_FAR;
    }
    shot->hidden = 1;
    shot->shot_flags = flags;
}
CLEAN_AS(func_020bfbec, SkyShots_ObjectSetUp)

#include "camera_view.h"
#include "globe.h"

#define SKY_SHOTS_SCREEN_DEPTH 0x60000

extern Mtx43 data_021fbe48; /* a matrix kept for those who use it next */
extern CameraControl *data_021c67a4;
extern void MTX_MultVec43(const Vec3 *vec, const Mtx43 *mtx, Vec3 *dst);

/* func_020c14bc: a world point's x on the screen: bent onto the drawn world, taken into the
 * camera's view (the view matrix kept in data_021fbe48), scaled by the projection's 6.0 over
 * its depth, from the screen's middle. */
void SkyShots_ScreenX(fx32 *x, const Vec3 *point)
{
    data_021fbe48 = *CameraControl_ViewMatrix();
    Vec3 in = *point;
    Vec3 bent;
    Globe_Bend(&bent, &in);
    Vec3 view;
    MTX_MultVec43(&bent, &data_021fbe48, &view);
    fx32 projection = (fx32) CameraControl_Projection(data_021c67a4);
    fx32 scale = -FX_Div(SKY_SHOTS_SCREEN_DEPTH, projection);
    scale = FX_Div(scale, view.z);
    Vec_Scale(&view, scale);
    *x = view.x + SKY_SHOTS_SCREEN_MIDDLE;
}
CLEAN_AS(func_020c14bc, SkyShots_ScreenX)
