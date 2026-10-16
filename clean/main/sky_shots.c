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
#include "sky_object_sounds.h"
#include "state_block.h"

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

extern const Position *func_02095794(int player);             /* the player's position, NULL without one */
extern void func_02095764(u16 *item, int player);             /* the item the player holds */
extern int func_02095518(int pitch, int yaw, int player);     /* the player's look */
extern void func_020c14bc(fx32 *x, const Position *position); /* a position's x on the screen */
extern int func_ov003_02220c8c(int variant, int x);
extern void func_0204130c(int event, int a, int b);
extern void func_020bf2b8(Vec3 *point, fx32 x, fx32 y, fx32 scale); /* a sound's point */
extern void func_020beb98(SkyShotsHit *hit, int player);            /* the player's state ended at once */
extern void func_020beba4(SkyShotsHit *hit, int player);            /* waiting for this system's shot */
extern void func_020bebd8(SkyShotRequest *request);                 /* the request cleared */
extern void func_020bebec(SkyShotRequest *request, int player, const Position *from, int triple);
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
            func_020beb98((SkyShotsHit *) (void *) objects->unk_2fa8, request->player);
        }
        func_020bebd8(request);
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
    const Position *from = func_02095794(player);
    SkyShotsHit *hit = (SkyShotsHit *) (void *) objects->unk_2fa8;
    if (from == NULL) {
        func_020beb98(hit, player);
        return;
    }
    u16 item;
    func_02095764(&item, player);
    func_020bebec(SkyShots_Request(objects, index), player, from, item == SKY_SHOTS_TRIPLE_ITEM);
    func_020beba4(hit, player);
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
    func_02095518(hit->pitch, hit->yaw, SKY_SHOTS_THIS_PLAYER);
}
CLEAN_AS(func_020be6ac, SkyShots_EaseLook)

/* func_020be6e4: this system's player made to look up at what was hit: the yaw from how far
 * across the screen it is from the player (from the middle without a player), 10000 per 256
 * pixels the other way, at most 5000 either way. */
void SkyShots_LookAtHit(SkyShotsHit *hit)
{
    const Position *player = func_02095794(SKY_SHOTS_THIS_PLAYER);
    fx32 player_x = SKY_SHOTS_SCREEN_MIDDLE;
    if (player != NULL) {
        func_020c14bc(&player_x, player);
    }
    int yaw = (FX_Div(hit->x - player_x, 0x100000) * -10000) >> 12;
    if (yaw < -SKY_SHOTS_LOOK_YAW_MAX) {
        yaw = -SKY_SHOTS_LOOK_YAW_MAX;
    } else if (yaw > SKY_SHOTS_LOOK_YAW_MAX) {
        yaw = SKY_SHOTS_LOOK_YAW_MAX;
    }
    func_02095518(SKY_SHOTS_LOOK_PITCH, (s16) yaw, SKY_SHOTS_THIS_PLAYER);
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
    func_020bf2b8(&point, hit->x, hit->y, hit->scale);
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
    const Position *from = func_02095794(hit->player);
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
    func_0204130c(0x44, 0x63, 0);
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
            func_ov003_02220c8c(hit->variant != 0, ((hit->x + 0x800) >> 12) - (SKY_SHOTS_SCREEN_MIDDLE >> 12)) == 0) {
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
    func_020beb98(hit, hit->player);
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
