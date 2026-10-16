/* Shots into the sky from a player's position (Sky_Objects020bdf68, run as the field actor
 * enters state 0x64): objects of kind SKY_OBJECT_SHOT, and what the player of this system
 * does while one of its shots is up.
 *
 * A shot is asked for (SkyShots_Fire) into one of four requests at 0x2f58 of the sky's
 * objects, one per player: from the player's position, three objects instead of one when the
 * player holds item 0x137b. At the next frame each request becomes objects in that player's
 * entries 33 + 3 * player (SkyShots_Launch); when none can be added the player's state ends
 * at once (func_020beb98).
 *
 * The hit (SkyShotsHit, at 0x2fa8) follows the shot of this system's player through states
 * run each frame by SkyShots_RunHit: waiting for the shot to hit (1; the player's state ends
 * after 43 frames without one), then one of three ways the shots' objects (func_020c09b0,
 * func_020c06d4, func_020c0494) set: the player looking at what was hit (2, 4, 7) and then
 * what it does (3; 5 and 6; 8 and 9) while the look eases back. The hits are counted in the
 * player's record (SkyShots_CountHit, up to 16). */
#ifndef CLEAN_MAIN_SKY_SHOTS_H
#define CLEAN_MAIN_SKY_SHOTS_H

#include "autoload_2/vector.h"
#include "sky_objects.h"
#include "types.h"

#define SKY_SHOTS_PLAYERS 4
#define SKY_SHOTS_THIS_PLAYER 4 /* the player of this system, to func_02095794 and others */

/* A shot asked for (0x14 bytes; four at 0x2f58 of the objects). */
typedef struct SkyShotRequest {
    s32 player; /* 0x00: 4 when there is none */
    Vec3 from;  /* 0x04: the player's position */
    u8 triple;  /* 0x10: three objects */
    u8 pending; /* 0x11 */
    u8 unk_12[2];
} SkyShotRequest;

/* SkyShotsHit.state. */
enum SkyShotsHitState {
    SKY_SHOTS_HIT_NONE = 0,
    SKY_SHOTS_HIT_WAITING = 1, /* SkyShots_HitWait */
    SKY_SHOTS_HIT_LOOK_2 = 2,  /* set by func_020beb78 */
    SKY_SHOTS_HIT_DROP_3 = 3,  /* func_020beb64 */
    SKY_SHOTS_HIT_LOOK_4 = 4,  /* func_020beb48 */
    SKY_SHOTS_HIT_FALL_5 = 5,  /* func_020beb3c */
    SKY_SHOTS_HIT_END_6 = 6,
    SKY_SHOTS_HIT_LOOK_7 = 7, /* func_020beb20 */
    SKY_SHOTS_HIT_FALL_8 = 8, /* func_020beb14 */
    SKY_SHOTS_HIT_END_9 = 9,
    SKY_SHOTS_HIT_STATES = 10,
};

/* The hit (0x24 bytes, at 0x2fa8 of the objects). */
typedef struct SkyShotsHit {
    s32 state;    /* 0x00: SkyShotsHitState */
    s32 player;   /* 0x04: the shooter */
    s32 timer;    /* 0x08 */
    fx32 x;       /* 0x0c: where what was hit is on the screen (func_020beb00) */
    fx32 y;       /* 0x10 */
    fx32 scale;   /* 0x14 */
    u8 side;      /* 0x18: NearSpot_Pick's side */
    u8 unk_19;    /* 0x19 */
    s16 pitch;    /* 0x1a: the look given to the player */
    s16 yaw;      /* 0x1c */
    u8 done;      /* 0x1e: state 3 ends */
    u8 sound_7f9; /* 0x1f: state 3 plays sound 0x7f9 */
    u8 sound_7fa; /* 0x20: or 0x7fa */
    u8 variant;   /* 0x21: func_020beb78's flag, handed to func_ov003_02220c8c */
    u8 unk_22[2];
} SkyShotsHit;

void SkyShots_Launch(SkyObjects *objects);
SkyShotRequest *SkyShots_Request(SkyObjects *objects, int index);
void SkyShots_Fire(SkyObjects *objects, int player);
void SkyShots_DestructRequest(SkyShotRequest *request);
void SkyShots_EaseLook(SkyShotsHit *hit, int pitch_step, int yaw_step);
void SkyShots_LookAtHit(SkyShotsHit *hit);
void SkyShots_ResetHit(SkyShotsHit *hit);
void SkyShots_HitEnd9(SkyShotsHit *hit);
void SkyShots_HitFall8(SkyShotsHit *hit);
void SkyShots_HitLook7(SkyShotsHit *hit);
void SkyShots_HitEnd6(SkyShotsHit *hit);
void SkyShots_HitFall5(SkyShotsHit *hit);
void SkyShots_HitLook4(SkyShotsHit *hit);
void SkyShots_HitDrop3(SkyShotsHit *hit);
void SkyShots_HitLook2(SkyShotsHit *hit);
void SkyShots_HitWait(SkyShotsHit *hit);
int SkyShots_HitCountFull(void);
void SkyShots_CountHit(void);
void SkyShots_RunHit(SkyShotsHit *hit);

/* ---- The hit's states set, the requests, and the shots' objects.
 *
 * A shot's object (kind 11, set up by SkyShots_ObjectSetUp) starts below the screen under its
 * player's place, hidden, and after 24 frames rises 12 pixels a frame; the second and third of
 * a triple shot then spread right and left. It is shown once it rises above line 0xc0 unless
 * it was fired far from the point the camera looks at (more than 20.0 north of it or 15.0
 * south), and it is done once out of view or once it hits. Only a shot of this system's player
 * fired in the town's two northern rows of acres can hit: SkyShots_HitsBox, called by the kinds
 * a shot can hit, finds the running ones in a box around the object and marks them hit. */
void SkyShots_SetHitPoint(SkyShotsHit *hit, u32 x, u32 y, u32 scale, u8 side);
void SkyShots_StartFall8(SkyShotsHit *hit);
void SkyShots_StartLook7(SkyShotsHit *hit);
void SkyShots_StartFall5(SkyShotsHit *hit);
void SkyShots_StartLook4(SkyShotsHit *hit);
void SkyShots_StartDrop3(SkyShotsHit *hit);
void SkyShots_StartLook2(SkyShotsHit *hit, int variant);
void SkyShots_EndPlayerState(SkyShotsHit *hit, int player);
void SkyShots_StartWaiting(SkyShotsHit *hit, int player);
SkyShotsHit *SkyShots_ConstructHit(SkyShotsHit *hit);
void SkyShots_ClearRequest(SkyShotRequest *request);
void SkyShots_SetRequest(SkyShotRequest *request, int player, const Vec3 *from, u8 triple);
SkyShotRequest *SkyShots_ConstructRequest(SkyShotRequest *request);
int SkyShots_HitsBox(SkyObject *object, fx32 width, fx32 height, fx32 offset_y);
void SkyShots_ObjectTakeDown(SkyObject *object);
void SkyShots_ObjectRun(SkyObject *object);
void SkyShots_ObjectSetUp(SkyObject *object, int param);

/* A world point's x on the screen as the camera shows it (SkyShots_Launch's shots start
 * there). */
void SkyShots_ScreenX(fx32 *x, const Vec3 *point);

#endif
