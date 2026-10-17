/* A place the field actor stays at in a room, and the ways off it (field_actor_place_states.h). */
#include "field_actor_place_states.h"

#include <stdint.h>

#include "autoload_2/vector.h"
#include "clean.h"
#include "main/collision_query.h"
#include "main/event_queue.h"
#include "main/field_actor.h"
#include "main/field_actor_parts.h"
#include "main/field_body.h"
#include "main/frame_ctrl.h"
#include "main/game_variables.h"
#include "main/packed_bytes.h"
#include "main/place_claim.h"
#include "main/player_record.h"
#include "main/scene_kinds.h"
#include "main/session.h"
#include "main/session_players.h"
#include "ov004/room_point_sound.h"

static_assert(offsetof(FieldActor, position) == 0x5c, "position");
static_assert(offsetof(FieldActor, yaw) == 0x8e, "yaw");
static_assert(offsetof(FieldActor, has_other) == 0x200, "an object met");
static_assert(offsetof(FieldActor, anim) == 0x2d0, "animation control");
static_assert(offsetof(FieldActor, animation) == 0x704, "animation");
static_assert(offsetof(FieldActor, work) == 0x7d4, "work");
static_assert(offsetof(FieldActor, state) == 0x7f0, "state");
static_assert(offsetof(FieldActor, next_state) == 0x7fc, "next state");
static_assert(offsetof(FieldActor, player) == 0x800, "player");
static_assert(offsetof(FieldActor, saved) == 0x8f0, "saved");
static_assert(offsetof(FieldActor, unk_C84) == 0xc84, "the kept argument");
static_assert(offsetof(Actor, last_position) == 0x68, "last position");
static_assert(offsetof(StateRequest, payload) == 0x0c, "payload");
static_assert(sizeof(FieldActorPlaceArgs) == 0x0c, "state 0x0e's arguments");
static_assert(offsetof(FieldActorPlaceArgs, side) == 0x0a, "side");
static_assert(offsetof(FieldActorPlaceArgs, kind) == 0x0b, "kind");
static_assert(offsetof(FieldActorPlaceOffWork, store_sun) == 0x0a, "state 0x0a's flag");
static_assert(offsetof(FieldActorPlaceProbeWork, side) == 0x0c, "state 9's side");
static_assert(sizeof(FieldActorPlaceArgs) <= sizeof(((StateRequest *) 0)->payload), "state 0x0e's request");
static_assert(sizeof(FieldActorPlaceProbeWork) <= sizeof(FieldActorWork), "state 9's work");

/* The states of this file. */
#define FAPS_STAY 0x08
#define FAPS_PROBE 0x09
#define FAPS_OFF 0x0a
#define FAPS_CLAIM 0x0b
#define FAPS_REFUSED 0x0c
#define FAPS_STEP 0x0d
#define FAPS_APPROACH 0x0e
/* The states state 8 is entered from without a blend. */
#define FAPS_FROM_0F 0x0f

#define FAPS_PRIORITY 6
#define FAPS_NO_ARG (-1)
#define FAPS_BLEND 3

/* The animations: side 1 first, side 0 second. */
#define FAPS_ANIM_APPROACH 0x1a
#define FAPS_ANIM_STAY 0x11
#define FAPS_ANIM_OFF_1 0x0a
#define FAPS_ANIM_OFF_0 0x09
#define FAPS_ANIM_CLAIM_1 0x0c
#define FAPS_ANIM_CLAIM_0 0x0f
#define FAPS_ANIM_REFUSED_1 0x0d
#define FAPS_ANIM_REFUSED_0 0x10
#define FAPS_ANIM_STEP_1 0x0b
#define FAPS_ANIM_STEP_0 0x0e

/* The sounds. */
#define FAPS_SOUND_STEP 0x435
#define FAPS_SOUND_REFUSED 0x4a4
#define FAPS_SOUND_OFF 0x4c6
#define FAPS_SOUND_LEAVE_STAY 0x4cc
#define FAPS_SOUND_LEAVE_STAY_FLAG 0x4cd
#define FAPS_OFF_SOUND_FRAME 0x15

/* How far to the side (2.0) and ahead (1.0) the ways off the place go, and a quarter turn. */
#define FAPS_SIDE_DISTANCE 0x2000
#define FAPS_AHEAD 0x1000
#define FAPS_QUARTER 0x4000

/* State 0x0b asks for the next state from its third frame on. */
#define FAPS_CLAIM_FRAMES 3

/* State 9's contact body: 1.0 wide and high. */
#define FAPS_PROBE_SIZE 0x1000
#define FAPS_PROBE_BODY 0x1c4

/* State 0x0a's end with the flag: state 0x10 (0, priority 5) and the sun level's countdown,
 * date, game variable (bank 0, index 80) and flags (17 while the date has not passed). */
#define FAPS_OFF_STATE10_PRIORITY 5
#define FAPS_OFF_STATE2_PRIORITY 1
#define FAPS_SUN_COUNTDOWN 0x4650
#define FAPS_SUN_VARIABLE 80
#define FAPS_SUN_FLAGS_WAITING 17

/* The answers of the overlay's side checks (func_ov004_0223c510, func_ov004_0223c4b8). */
#define FAPS_SIDE_FREE 1
#define FAPS_SIDE_BLOCKED 2

/* The session (main/session.h). */
extern NetSession *data_020ccf94;
/* 1 in a room. */
extern u8 data_020e54a8;
/* 2.0: how far ahead of the request's point state 0x0e's place is. */
extern const fx32 data_ov004_02247780;
extern const s16 FX_SinCosTable_[];

extern int FX_MulFunc(int a, int b);
/* Whether the point 2.0 to side 0 or side 1 of `point` (at `yaw`) is free: 1 free, 2 not. */
extern int func_ov004_0223c510(Vec3 *point, s16 yaw);
extern int func_ov004_0223c4b8(Vec3 *point, s16 yaw);
/* The byte of a request for state 8. */
extern void func_ov004_0222be30(u8 *payload, u8 kind);

/* The date the sun level was stored, as packed: bits 0-6, the month in bits 7-10, bits 11-15. */
#define FAPS_DATE_MONTH(date) (((unsigned int) (date) >> 7) & 0xf)
#define FAPS_DATE_HIGH(date) (((unsigned int) (date) >> 11) & 0x1f)

static int faps_is_local(FieldActor *actor)
{
    return Session_IsLocalPlayer(data_020ccf94, actor->player);
}

static FieldActorPlaceArgs *faps_place_of(FieldActor *actor)
{
    return (FieldActorPlaceArgs *) (void *) &actor->work;
}

static FieldActorPlaceStepWork *faps_step_of(FieldActor *actor)
{
    return (FieldActorPlaceStepWork *) (void *) &actor->work;
}

static FieldActorPlaceClaimWork *faps_claim_of(FieldActor *actor)
{
    return (FieldActorPlaceClaimWork *) (void *) &actor->work;
}

static FieldActorPlaceOffWork *faps_off_of(FieldActor *actor)
{
    return (FieldActorPlaceOffWork *) (void *) &actor->work;
}

static FieldActorPlaceProbeWork *faps_probe_of(FieldActor *actor)
{
    return (FieldActorPlaceProbeWork *) (void *) &actor->work;
}

static u8 *faps_stay_of(FieldActor *actor)
{
    return actor->work.bytes;
}

static fx32 faps_side_distance(int side)
{
    return side != 0 ? FAPS_SIDE_DISTANCE : -FAPS_SIDE_DISTANCE;
}

/* The point 2.0 to `side` of the actor (FieldActor_PointAhead at a quarter turn). */
static void faps_point_beside(Vec3 *out, FieldActor *actor, int side)
{
    fx32 distance = faps_side_distance(side);
    u16 yaw = (u16) (actor->yaw + FAPS_QUARTER);
    FieldActor_PointAhead(out, actor, &actor->position, &yaw, &distance);
}

/* The offsets in x and z of the point 1.0 ahead of the actor and 2.0 to `side`, multiplied in
 * the order the ROM does. */
static void faps_ahead_beside(FieldActor *actor, int side, fx32 *dx, fx32 *dz)
{
    fx32 across = faps_side_distance(side);
    int index = ((u16) actor->yaw >> 4) * 2;
    int sine = FX_SinCosTable_[index];
    int cosine = FX_SinCosTable_[index + 1];
    int ahead_z = FX_MulFunc(cosine, FAPS_AHEAD);
    int across_z = FX_MulFunc(sine, across);
    *dz = (fx32) ((u32) ahead_z - (u32) across_z);
    int ahead_x = FX_MulFunc(sine, FAPS_AHEAD);
    int across_x = FX_MulFunc(cosine, across);
    *dx = (fx32) ((u32) ahead_x + (u32) across_x);
}

/* ---- State 0x0e: to the place (its entry; the rest is in field_actor_room_states2.c) */

/* func_ov004_0222b0fc (state 0x0e's entry): the request's point, yaw, side and kind. This
 * console's actor takes the point 2.0 ahead of it (at that yaw) and claims it. The work and the
 * saved bytes get the point, yaw and side (the work also the kind); animation 0x1a loops
 * (blended over 3 frames). */
void FieldActorPlaceStates_EnterApproach(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const FieldActorPlaceArgs *args = (const FieldActorPlaceArgs *) (const void *) request->payload;
    Vec3 point;
    point.x = args->x;
    point.y = 0;
    point.z = args->z;
    u16 yaw = (u16) args->yaw;
    u8 side = args->side;
    if (faps_is_local(actor)) {
        Vec3 ahead;
        FieldActor_PointAhead(&ahead, actor, &point, &yaw, &data_ov004_02247780);
        point = ahead;
    }
    FieldActorPlaceStates_SetApproachWork(faps_place_of(actor), point.x, point.z, (s16) yaw, side, args->kind);
    FieldActorPlaceStates_PutApproachSaved(actor->saved.packed, point.x, point.z, (s16) yaw, side);
    if (faps_is_local(actor)) {
        PlaceClaim_Request3(&point);
    }
    FieldActor_PlayAnimationLoop(actor, FAPS_ANIM_APPROACH, FAPS_BLEND, 0);
}
CLEAN_AS(func_ov004_0222b0fc, FieldActorPlaceStates_EnterApproach)

/* func_ov004_0222b1b4: state 0x0e's saved bytes: the point (packed), the yaw at byte 5, the side
 * at byte 7. */
void FieldActorPlaceStates_GetApproachSaved(const u8 *saved, u32 *x, u32 *z, s16 *yaw, u8 *side)
{
    PackedBytes_UnpackPoint(saved, x, z);
    *yaw = PackedBytes_ReadS16(saved + 5);
    *side = saved[7];
}
CLEAN_AS(func_ov004_0222b1b4, FieldActorPlaceStates_GetApproachSaved)

/* func_ov004_0222b1d8: state 0x0e's saved bytes put. */
void FieldActorPlaceStates_PutApproachSaved(u8 *saved, int x, int z, int yaw, u8 side)
{
    PackedBytes_PackPoint(saved, x, z);
    PackedBytes_WriteS16(saved + 5, yaw);
    saved[7] = side;
}
CLEAN_AS(func_ov004_0222b1d8, FieldActorPlaceStates_PutApproachSaved)

/* func_ov004_0222b1fc: state 0x0e's work. */
void FieldActorPlaceStates_SetApproachWork(FieldActorPlaceArgs *work, int x, int z, s16 yaw, u8 side, u8 kind)
{
    work->x = x;
    work->z = z;
    work->yaw = yaw;
    work->side = side;
    work->kind = kind;
}
CLEAN_AS(func_ov004_0222b1fc, FieldActorPlaceStates_SetApproachWork)

/* func_ov004_0222b214: state 0x0e asked for with the point, yaw and side; the kind is 1 when
 * `priority` is 6. Whether it was queued. */
int FieldActorPlaceStates_RequestApproach(FieldActor *actor, int x, int z, int yaw, u8 side, int priority, s16 arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FAPS_APPROACH, priority, arg);
    FieldActorPlaceStates_PutApproachArgs((FieldActorPlaceArgs *) (void *) request.payload, x, z, (s16) yaw, side,
                                          priority == FAPS_PRIORITY);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_0222b214, FieldActorPlaceStates_RequestApproach)

/* func_ov004_0222b270: what a request for state 0x0e carries. */
void FieldActorPlaceStates_PutApproachArgs(FieldActorPlaceArgs *args, int x, int z, s16 yaw, u8 side, u8 kind)
{
    args->x = x;
    args->z = z;
    args->yaw = yaw;
    args->side = side;
    args->kind = kind;
}
CLEAN_AS(func_ov004_0222b270, FieldActorPlaceStates_PutApproachArgs)

/* ---- State 0x0d: a step off to the side */

/* func_ov004_0222b288 (state 0x0d's update): another console's actor follows what is reported;
 * the body; the end of the animation. */
void FieldActorPlaceStates_UpdateStep(FieldActor *actor)
{
    FieldActor_FollowReported(actor);
    FieldActor_UpdateBody(actor);
    FieldActorPlaceStates_EndStep(actor);
}
CLEAN_AS(func_ov004_0222b288, FieldActorPlaceStates_UpdateStep)

/* func_ov004_0222b2a4: once the animation is over state 8 is asked for (kind 0, priority 6);
 * queued, the byte at 0x8ea is cleared. */
void FieldActorPlaceStates_EndStep(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim) && FieldActorPlaceStates_RequestStay(actor, 0, FAPS_PRIORITY, FAPS_NO_ARG)) {
        FIELD_ACTOR_UNK_8EA(actor) = 0;
    }
}
CLEAN_AS(func_ov004_0222b2a4, FieldActorPlaceStates_EndStep)

/* func_ov004_0222b2d8 (state 0x0d's exit): the actor stands at the work's point (x and z). */
void FieldActorPlaceStates_LeaveStep(FieldActor *actor, int next)
{
    (void) next;
    const FieldActorPlaceStepWork *work = faps_step_of(actor);
    actor->position.x = work->x;
    actor->position.z = work->z;
}
CLEAN_AS(func_ov004_0222b2d8, FieldActorPlaceStates_LeaveStep)

/* func_ov004_0222b2f0 (state 0x0d's message handler): state 0x0d asked for with the saved side
 * (priority 6). */
void FieldActorPlaceStates_StepMessage(FieldActor *actor, int arg)
{
    u8 side;
    FieldActorPlaceStates_GetStepSaved(actor->saved.packed, &side);
    FieldActorPlaceStates_RequestStep(actor, side, FAPS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_0222b2f0, FieldActorPlaceStates_StepMessage)

/* func_ov004_0222b31c (state 0x0d's entry): animation 0x0b (side 1) or 0x0e plays once, blended
 * over 3 frames for this console's actor; the work is the point 2.0 to the side, the side is
 * saved; sound 0x435. */
void FieldActorPlaceStates_EnterStep(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 side = request->payload[0];
    int animation = side != 0 ? FAPS_ANIM_STEP_1 : FAPS_ANIM_STEP_0;
    if (faps_is_local(actor)) {
        FieldActor_PlayAnimationOnce(actor, animation, FAPS_BLEND, 0);
    } else {
        FieldActor_PlayAnimationOnce(actor, animation, 0, 0);
    }
    Vec3 point;
    faps_point_beside(&point, actor, side);
    FieldActorPlaceStates_SetStepWork(faps_step_of(actor), point.x, point.z);
    FieldActorPlaceStates_PutStepSaved(actor->saved.packed, side);
    FieldActor_PlaySound(actor, FAPS_SOUND_STEP);
}
CLEAN_AS(func_ov004_0222b31c, FieldActorPlaceStates_EnterStep)

/* func_ov004_0222b3d4: state 0x0d's saved side. */
void FieldActorPlaceStates_GetStepSaved(const u8 *saved, u8 *side)
{
    *side = *saved;
}
CLEAN_AS(func_ov004_0222b3d4, FieldActorPlaceStates_GetStepSaved)

/* func_ov004_0222b3dc */
void FieldActorPlaceStates_PutStepSaved(u8 *saved, u8 side)
{
    *saved = side;
}
CLEAN_AS(func_ov004_0222b3dc, FieldActorPlaceStates_PutStepSaved)

/* func_ov004_0222b3e0: state 0x0d's work. */
void FieldActorPlaceStates_SetStepWork(FieldActorPlaceStepWork *work, int x, int z)
{
    work->x = x;
    work->z = z;
}
CLEAN_AS(func_ov004_0222b3e0, FieldActorPlaceStates_SetStepWork)

/* func_ov004_0222b3e8: state 0x0d asked for with the side; whether it was queued. */
int FieldActorPlaceStates_RequestStep(FieldActor *actor, int side, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FAPS_STEP, priority, arg);
    FieldActorPlaceStates_PutStepArgs(request.payload, (u8) side);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_0222b3e8, FieldActorPlaceStates_RequestStep)

/* func_ov004_0222b428: what a request for state 0x0d carries. */
void FieldActorPlaceStates_PutStepArgs(u8 *payload, u8 side)
{
    payload[0] = side;
}
CLEAN_AS(func_ov004_0222b428, FieldActorPlaceStates_PutStepArgs)

/* ---- State 0x0c: the claim refused */

/* func_ov004_0222b42c (state 0x0c's update): the body, then the end of the animation. */
void FieldActorPlaceStates_UpdateRefused(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActorPlaceStates_EndRefused(actor);
}
CLEAN_AS(func_ov004_0222b42c, FieldActorPlaceStates_UpdateRefused)

/* func_ov004_0222b440: once the animation is over state 8 is asked for (kind 0, priority 6). */
void FieldActorPlaceStates_EndRefused(FieldActor *actor)
{
    if (FrameCtrl_IsDone(&actor->anim)) {
        FieldActorPlaceStates_RequestStay(actor, 0, FAPS_PRIORITY, FAPS_NO_ARG);
    }
}
CLEAN_AS(func_ov004_0222b440, FieldActorPlaceStates_EndRefused)

/* func_ov004_0222b468 (state 0x0c's message handler): state 0x0c asked for with the saved side
 * (priority 6). */
void FieldActorPlaceStates_RefusedMessage(FieldActor *actor, int arg)
{
    u8 side;
    FieldActorPlaceStates_GetRefusedSaved(actor->saved.packed, &side);
    FieldActorPlaceStates_RequestRefused(actor, side, FAPS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_0222b468, FieldActorPlaceStates_RefusedMessage)

/* func_ov004_0222b494 (state 0x0c's entry): the side saved; animation 0x0d (side 1) or 0x10
 * plays once (blended over 3 frames); sound 0x4a4. */
void FieldActorPlaceStates_EnterRefused(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 side = request->payload[0];
    FieldActorPlaceStates_PutRefusedSaved(actor->saved.packed, side);
    FieldActor_PlayAnimationOnce(actor, side != 0 ? FAPS_ANIM_REFUSED_1 : FAPS_ANIM_REFUSED_0, FAPS_BLEND, 0);
    FieldActor_PlaySound(actor, FAPS_SOUND_REFUSED);
}
CLEAN_AS(func_ov004_0222b494, FieldActorPlaceStates_EnterRefused)

/* func_ov004_0222b4d4: state 0x0c's saved side. */
void FieldActorPlaceStates_GetRefusedSaved(const u8 *saved, u8 *side)
{
    *side = *saved;
}
CLEAN_AS(func_ov004_0222b4d4, FieldActorPlaceStates_GetRefusedSaved)

/* func_ov004_0222b4dc */
void FieldActorPlaceStates_PutRefusedSaved(u8 *saved, u8 side)
{
    *saved = side;
}
CLEAN_AS(func_ov004_0222b4dc, FieldActorPlaceStates_PutRefusedSaved)

/* func_ov004_0222b4e0: state 0x0c asked for with the side; whether it was queued. */
int FieldActorPlaceStates_RequestRefused(FieldActor *actor, int side, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FAPS_REFUSED, priority, arg);
    FieldActorPlaceStates_PutRefusedArgs(request.payload, (u8) side);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_0222b4e0, FieldActorPlaceStates_RequestRefused)

/* func_ov004_0222b520: what a request for state 0x0c carries. */
void FieldActorPlaceStates_PutRefusedArgs(u8 *payload, u8 side)
{
    payload[0] = side;
}
CLEAN_AS(func_ov004_0222b520, FieldActorPlaceStates_PutRefusedArgs)

/* ---- State 0x0b: the point to the side claimed */

/* func_ov004_0222b524 (state 0x0b's update): another console's actor follows what is reported;
 * the body; the claim's answer. */
void FieldActorPlaceStates_UpdateClaim(FieldActor *actor)
{
    FieldActor_FollowReported(actor);
    FieldActor_UpdateBody(actor);
    FieldActorPlaceStates_WaitClaim(actor);
}
CLEAN_AS(func_ov004_0222b524, FieldActorPlaceStates_UpdateClaim)

/* func_ov004_0222b540: for this console's actor the frames are counted (to 3); from the third,
 * the claim given asks for state 0x0d with the side, refused for state 0x0c (priority 6). */
void FieldActorPlaceStates_WaitClaim(FieldActor *actor)
{
    if (!faps_is_local(actor)) {
        return;
    }
    FieldActorPlaceClaimWork *work = faps_claim_of(actor);
    if (work->frames < FAPS_CLAIM_FRAMES) {
        work->frames++;
    }
    switch (PlaceClaim_Answer1()) {
        case PLACE_CLAIM_WAITING:
            break;
        case PLACE_CLAIM_GIVEN:
            if (work->frames >= FAPS_CLAIM_FRAMES) {
                FieldActorPlaceStates_RequestStep(actor, work->side, FAPS_PRIORITY, FAPS_NO_ARG);
            }
            break;
        case PLACE_CLAIM_REFUSED:
            if (work->frames >= FAPS_CLAIM_FRAMES) {
                FieldActorPlaceStates_RequestRefused(actor, work->side, FAPS_PRIORITY, FAPS_NO_ARG);
            }
            break;
        default:
            break;
    }
}
CLEAN_AS(func_ov004_0222b540, FieldActorPlaceStates_WaitClaim)

/* func_ov004_0222b5b4 (state 0x0b's message handler): state 0x0b asked for with the saved side
 * (priority 6). */
void FieldActorPlaceStates_ClaimMessage(FieldActor *actor, int arg)
{
    u8 side;
    FieldActorPlaceStates_GetClaimSaved(actor->saved.packed, &side);
    FieldActorPlaceStates_RequestClaim(actor, side, FAPS_PRIORITY, arg);
}
CLEAN_AS(func_ov004_0222b5b4, FieldActorPlaceStates_ClaimMessage)

/* func_ov004_0222b5e0 (state 0x0b's entry): the work (no frames yet) and the saved bytes get
 * the side; this console's actor claims the point 2.0 to the side (PlaceClaim_Request1);
 * animation 0x0c (side 1) or 0x0f loops (blended over 3 frames). */
void FieldActorPlaceStates_EnterClaim(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    u8 side = request->payload[0];
    FieldActorPlaceStates_SetClaimWork(faps_claim_of(actor), side);
    FieldActorPlaceStates_PutClaimSaved(actor->saved.packed, side);
    int animation = side != 0 ? FAPS_ANIM_CLAIM_1 : FAPS_ANIM_CLAIM_0;
    if (faps_is_local(actor)) {
        Vec3 point;
        faps_point_beside(&point, actor, side);
        PlaceClaim_Request1(&point);
    }
    FieldActor_PlayAnimationLoop(actor, animation, FAPS_BLEND, 0);
}
CLEAN_AS(func_ov004_0222b5e0, FieldActorPlaceStates_EnterClaim)

/* func_ov004_0222b694: state 0x0b's saved side. */
void FieldActorPlaceStates_GetClaimSaved(const u8 *saved, u8 *side)
{
    *side = *saved;
}
CLEAN_AS(func_ov004_0222b694, FieldActorPlaceStates_GetClaimSaved)

/* func_ov004_0222b69c */
void FieldActorPlaceStates_PutClaimSaved(u8 *saved, u8 side)
{
    *saved = side;
}
CLEAN_AS(func_ov004_0222b69c, FieldActorPlaceStates_PutClaimSaved)

/* func_ov004_0222b6a0: state 0x0b's work: no frames counted, the side. */
void FieldActorPlaceStates_SetClaimWork(FieldActorPlaceClaimWork *work, u8 side)
{
    work->frames = 0;
    work->side = side;
}
CLEAN_AS(func_ov004_0222b6a0, FieldActorPlaceStates_SetClaimWork)

/* func_ov004_0222b6a8: state 0x0b asked for with the side; whether it was queued. */
int FieldActorPlaceStates_RequestClaim(FieldActor *actor, int side, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FAPS_CLAIM, priority, arg);
    FieldActorPlaceStates_PutClaimArgs(request.payload, (u8) side);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_0222b6a8, FieldActorPlaceStates_RequestClaim)

/* func_ov004_0222b6e8: what a request for state 0x0b carries. */
void FieldActorPlaceStates_PutClaimArgs(u8 *payload, u8 side)
{
    payload[0] = side;
}
CLEAN_AS(func_ov004_0222b6e8, FieldActorPlaceStates_PutClaimArgs)

/* ---- State 0x0a: off the place over the side */

/* func_ov004_0222b6ec (state 0x0a's update): the body and its sound, the contact bodies at the
 * work's point, the end of the animation. */
void FieldActorPlaceStates_UpdateOff(FieldActor *actor)
{
    FieldActorPlaceStates_StepOff(actor);
    FieldActorPlaceStates_ContactOff(actor);
    FieldActorPlaceStates_EndOff(actor);
}
CLEAN_AS(func_ov004_0222b6ec, FieldActorPlaceStates_UpdateOff)

/* func_ov004_0222b708: once the animation is over the state's bar for requests is its end
 * value. Without the work's flag state 2 is asked for (0, priority 1). With it, state 0x10 (0,
 * priority 5), and the sun level's countdown restarts at 0x4650, its date becomes the record's,
 * game variable 80 of bank 0 the level + 1000 * the date's month (bits 7-10) + 10 * its bits
 * 11-15, and
 * its flags 0 once the date has passed (FieldActor_SunDatePassed), else 17. */
void FieldActorPlaceStates_EndOff(FieldActor *actor)
{
    if (!FrameCtrl_IsDone(&actor->anim)) {
        return;
    }
    actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
    if (faps_off_of(actor)->store_sun == 0) {
        FieldActor_RequestState2(actor, 0, FAPS_OFF_STATE2_PRIORITY, FAPS_NO_ARG);
        return;
    }
    FieldActor_RequestState10(actor, 0, FAPS_OFF_STATE10_PRIORITY, FAPS_NO_ARG);
    *SessionPlayers_SunCountdown() = FAPS_SUN_COUNTDOWN;
    u16 date = (u16) PlayerRecord_SunDate(FieldActor_Record(actor));
    *SessionPlayers_SunDate() = date;
    int passed = FieldActor_SunDatePassed(actor);
    u16 *variable = GameVariables_Slot(0, FAPS_SUN_VARIABLE);
    unsigned int level = FieldActor_RecordSunLevel(actor);
    const u16 *first = SessionPlayers_SunDate();
    const u16 *second = SessionPlayers_SunDate();
    *variable = (u16) (level + 1000u * FAPS_DATE_MONTH(*first) + 10u * FAPS_DATE_HIGH(*second));
    *SessionPlayers_SunFlags() = passed ? 0 : FAPS_SUN_FLAGS_WAITING;
}
CLEAN_AS(func_ov004_0222b708, FieldActorPlaceStates_EndOff)

/* func_ov004_0222b7e4: the contact bodies at the work's point, at the floor's height. */
void FieldActorPlaceStates_ContactOff(FieldActor *actor)
{
    const FieldActorPlaceOffWork *work = faps_off_of(actor);
    Vec3 point;
    point.x = work->x;
    point.y = CollisionQuery_FloorHeight(0);
    point.z = work->z;
    FieldActor_EnterContacts(actor, &point);
}
CLEAN_AS(func_ov004_0222b7e4, FieldActorPlaceStates_ContactOff)

/* func_ov004_0222b814: the body; as the animation passes frame 21, sound 0x4c6, and this
 * console's actor lets its claim go (slot 0's). */
void FieldActorPlaceStates_StepOff(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    if (FrameCtrl_Passed(&actor->anim, FAPS_OFF_SOUND_FRAME)) {
        FieldActor_PlaySound(actor, FAPS_SOUND_OFF);
        if (faps_is_local(actor)) {
            PlaceClaim_ReleaseSlot0();
        }
    }
}
CLEAN_AS(func_ov004_0222b814, FieldActorPlaceStates_StepOff)

/* func_ov004_0222b85c (state 0x0a's exit): the actor stands at the work's point (x and z) at the
 * work's yaw, and that is its last position too. */
void FieldActorPlaceStates_LeaveOff(FieldActor *actor, int next)
{
    (void) next;
    const FieldActorPlaceOffWork *work = faps_off_of(actor);
    actor->position.x = work->x;
    actor->position.z = work->z;
    FieldActor_SetYaw(actor, &work->yaw);
    FieldActor_Base(actor)->last_position = actor->position;
}
CLEAN_AS(func_ov004_0222b85c, FieldActorPlaceStates_LeaveOff)

/* func_ov004_0222b88c (state 0x0a's message handler): state 0x0a asked for with the saved side,
 * without the flag (priority 6). */
void FieldActorPlaceStates_OffMessage(FieldActor *actor, int arg)
{
    u8 side;
    FieldActorPlaceStates_GetOffSaved(actor->saved.packed, &side);
    FieldActorPlaceStates_RequestOff(actor, side, 0, FAPS_PRIORITY, (s16) arg);
}
CLEAN_AS(func_ov004_0222b88c, FieldActorPlaceStates_OffMessage)

/* func_ov004_0222b8bc (state 0x0a's entry): in a room the room object's sound 2 at the actor's
 * position; animation 0x0a (side 1) or 9 plays once (blended over 3 frames). The work is the
 * point 1.0 ahead and 2.0 to the side, the yaw a quarter turn that way and the request's flag;
 * the side is saved. */
void FieldActorPlaceStates_EnterOff(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    const FieldActorPlaceOffArgs *args = (const FieldActorPlaceOffArgs *) (const void *) request->payload;
    u8 side = args->side;
    if (data_020e54a8 == 1) {
        RoomPointSound_Play2(&actor->position);
    }
    FieldActor_PlayAnimationOnce(actor, side != 0 ? FAPS_ANIM_OFF_1 : FAPS_ANIM_OFF_0, FAPS_BLEND, 0);
    s16 yaw = actor->yaw;
    fx32 dx, dz;
    faps_ahead_beside(actor, side, &dx, &dz);
    fx32 x = (fx32) ((u32) actor->position.x + (u32) dx);
    fx32 z = (fx32) ((u32) actor->position.z + (u32) dz);
    s16 turned = (s16) (side != 0 ? yaw + FAPS_QUARTER : yaw - FAPS_QUARTER);
    FieldActorPlaceStates_SetOffWork(faps_off_of(actor), x, z, turned, args->store_sun);
    FieldActorPlaceStates_PutOffSaved(actor->saved.packed, side);
}
CLEAN_AS(func_ov004_0222b8bc, FieldActorPlaceStates_EnterOff)

/* func_ov004_0222b9b4: state 0x0a's saved side. */
void FieldActorPlaceStates_GetOffSaved(const u8 *saved, u8 *side)
{
    *side = *saved;
}
CLEAN_AS(func_ov004_0222b9b4, FieldActorPlaceStates_GetOffSaved)

/* func_ov004_0222b9bc */
void FieldActorPlaceStates_PutOffSaved(u8 *saved, u8 side)
{
    *saved = side;
}
CLEAN_AS(func_ov004_0222b9bc, FieldActorPlaceStates_PutOffSaved)

/* func_ov004_0222b9c0: state 0x0a's work. */
void FieldActorPlaceStates_SetOffWork(FieldActorPlaceOffWork *work, int x, int z, s16 yaw, u8 store_sun)
{
    work->x = x;
    work->z = z;
    work->yaw = yaw;
    work->store_sun = store_sun;
}
CLEAN_AS(func_ov004_0222b9c0, FieldActorPlaceStates_SetOffWork)

/* func_ov004_0222b9d4: state 0x0a asked for with the side and the flag; whether it was
 * queued. */
int FieldActorPlaceStates_RequestOff(FieldActor *actor, int side, int store_sun, int priority, s16 arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FAPS_OFF, priority, arg);
    FieldActorPlaceStates_PutOffArgs((FieldActorPlaceOffArgs *) (void *) request.payload, (u8) side, (u8) store_sun);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_0222b9d4, FieldActorPlaceStates_RequestOff)

/* func_ov004_0222ba1c: what a request for state 0x0a carries. */
void FieldActorPlaceStates_PutOffArgs(FieldActorPlaceOffArgs *args, u8 side, u8 store_sun)
{
    args->side = side;
    args->store_sun = store_sun;
}
CLEAN_AS(func_ov004_0222ba1c, FieldActorPlaceStates_PutOffArgs)

/* ---- State 9: the point ahead to the side tried */

/* func_ov004_0222ba24 (state 9's update): the body, the contact bodies, the claim's answer and
 * the contact body at the work's point. */
void FieldActorPlaceStates_UpdateProbe(FieldActor *actor)
{
    FieldActor_UpdateBody(actor);
    FieldActor_EnterContact(actor);
    FieldActorPlaceStates_WaitProbe(actor);
    FieldActorPlaceStates_ContactProbe(actor);
}
CLEAN_AS(func_ov004_0222ba24, FieldActorPlaceStates_UpdateProbe)

/* func_ov004_0222ba44: by the claim's answer (PlaceClaim_Answer2): none yet, nothing; refused,
 * the state's bar for requests is its end value and state 8 is asked for (kind 0, priority 6);
 * given, the same bar, then state 8 if an object was met (FieldActor.has_other), else state
 * 0x0a with the side and no flag.
 * QUIRK: an answer above 2 (the game keeps 0 to 2) goes the way of a given one without the
 * bar. */
void FieldActorPlaceStates_WaitProbe(FieldActor *actor)
{
    switch (PlaceClaim_Answer2()) {
        case PLACE_CLAIM_WAITING:
            return;
        case PLACE_CLAIM_GIVEN:
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
            break;
        case PLACE_CLAIM_REFUSED:
            actor->next_state = FieldActor_StateEndPriority(actor, actor->state);
            FieldActorPlaceStates_RequestStay(actor, 0, FAPS_PRIORITY, FAPS_NO_ARG);
            return;
        default:
            break;
    }
    if (actor->has_other != 0) {
        FieldActorPlaceStates_RequestStay(actor, 0, FAPS_PRIORITY, FAPS_NO_ARG);
    } else {
        FieldActorPlaceStates_RequestOff(actor, faps_probe_of(actor)->side, 0, FAPS_PRIORITY, FAPS_NO_ARG);
    }
}
CLEAN_AS(func_ov004_0222ba44, FieldActorPlaceStates_WaitProbe)

/* func_ov004_0222bacc: the second contact body (1.0 wide and high) at the work's point, and the
 * body at 0x1c4 entered among the field's bodies. */
void FieldActorPlaceStates_ContactProbe(FieldActor *actor)
{
    Vec3 point = faps_probe_of(actor)->point;
    FieldActor_SetContactBSized(actor, &point, FAPS_PROBE_SIZE, FAPS_PROBE_SIZE);
    FieldBody_Enter((FieldBody *) (void *) ((u8 *) actor + FAPS_PROBE_BODY));
}
CLEAN_AS(func_ov004_0222bacc, FieldActorPlaceStates_ContactProbe)

/* func_ov004_0222bb08 (state 9's message handler): nothing. */
void FieldActorPlaceStates_ProbeMessage(FieldActor *actor, int arg)
{
    (void) actor;
    (void) arg;
}
CLEAN_AS(func_ov004_0222bb08, FieldActorPlaceStates_ProbeMessage)

/* func_ov004_0222bb0c (state 9's entry): the work is the point 1.0 ahead and 2.0 to the
 * request's side (at the actor's height) and the side; this console's actor claims it
 * (PlaceClaim_Request2). */
void FieldActorPlaceStates_EnterProbe(FieldActor *actor, const StateRequest *request, int previous)
{
    (void) previous;
    int side = request->payload[0];
    Vec3 point = actor->position;
    fx32 dx, dz;
    faps_ahead_beside(actor, side, &dx, &dz);
    point.x = (fx32) ((u32) actor->position.x + (u32) dx);
    point.z = (fx32) ((u32) actor->position.z + (u32) dz);
    Vec3 copy = point;
    FieldActorPlaceStates_SetProbeWork(faps_probe_of(actor), &copy, side);
    if (faps_is_local(actor)) {
        PlaceClaim_Request2(&point);
    }
}
CLEAN_AS(func_ov004_0222bb0c, FieldActorPlaceStates_EnterProbe)

/* func_ov004_0222bbd4: state 9's work; the work. */
void *FieldActorPlaceStates_SetProbeWork(FieldActorPlaceProbeWork *work, const Vec3 *point, int side)
{
    work->point.x = point->x;
    work->point.y = point->y;
    work->point.z = point->z;
    work->side = (u8) side;
    return work;
}
CLEAN_AS(func_ov004_0222bbd4, FieldActorPlaceStates_SetProbeWork)

/* func_ov004_0222bbe4: state 9 asked for with the side; whether it was queued. */
int FieldActorPlaceStates_RequestProbe(FieldActor *actor, int side, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FAPS_PROBE, priority, arg);
    FieldActorPlaceStates_PutProbeArgs(request.payload, (u8) side);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_0222bbe4, FieldActorPlaceStates_RequestProbe)

/* func_ov004_0222bc24: what a request for state 9 carries. */
void FieldActorPlaceStates_PutProbeArgs(u8 *payload, u8 side)
{
    payload[0] = side;
}
CLEAN_AS(func_ov004_0222bc24, FieldActorPlaceStates_PutProbeArgs)

/* ---- State 8: at the place */

/* func_ov004_0222bc28 (state 8's update): another console's actor follows what is reported;
 * the body; the shadow; this console's actor reads the stick. */
void FieldActorPlaceStates_UpdateStay(FieldActor *actor)
{
    FieldActor_FollowReported(actor);
    FieldActor_UpdateBody(actor);
    FieldActor_PlaceShadow(actor);
    if (faps_is_local(actor)) {
        FieldActorPlaceStates_PushStay(actor);
    }
}
CLEAN_AS(func_ov004_0222bc28, FieldActorPlaceStates_UpdateStay)

/* func_ov004_0222bc60: outside the scenes 6 to 8, with the stick pushed, once for each new side
 * pushed (kept + 1 in the byte at 0x8ea): whether the point 2.0 to that side is free (side 0 of
 * the push is the actor's side 1). Free, state 0x0b that way; not, state 9 that way (priority
 * 6).
 * BUG: pushed straight ahead or behind (FieldActor_PushSide 2) neither check runs and the ROM
 * tests a register it never set; here nothing is asked for. */
void FieldActorPlaceStates_PushStay(FieldActor *actor)
{
    if (SceneKinds_CurrentIn6To8()) {
        return;
    }
    if ((int) FieldActor_Push(actor) <= 0) {
        return;
    }
    int push_side = FieldActor_PushSide(actor);
    if (FIELD_ACTOR_UNK_8EA(actor) == push_side + 1) {
        return;
    }
    FIELD_ACTOR_UNK_8EA(actor) = (u8) (push_side + 1);
    int answer;
    switch (push_side) {
        case 0:
            answer = func_ov004_0223c510(&actor->position, actor->yaw);
            break;
        case 1:
            answer = func_ov004_0223c4b8(&actor->position, actor->yaw);
            break;
        default:
            answer = 0;
            break;
    }
    if (answer == FAPS_SIDE_FREE) {
        FieldActorPlaceStates_RequestClaim(actor, push_side == 0, FAPS_PRIORITY, FAPS_NO_ARG);
    } else if (answer == FAPS_SIDE_BLOCKED) {
        FieldActorPlaceStates_RequestProbe(actor, push_side == 0, FAPS_PRIORITY, FAPS_NO_ARG);
    }
}
CLEAN_AS(func_ov004_0222bc60, FieldActorPlaceStates_PushStay)

/* func_ov004_0222bcf4 (state 8's exit): in the scenes 6 to 8, leaving for state 0x0a with kind
 * 0, sound 0x4cd with the record's flag 0x249a, else 0x4cc. */
void FieldActorPlaceStates_LeaveStay(FieldActor *actor, int next)
{
    if (SceneKinds_CurrentIn6To8() && next == FAPS_OFF && *faps_stay_of(actor) == 0) {
        if (FieldActor_RecordFlag249A(actor)) {
            FieldActor_PlaySound(actor, FAPS_SOUND_LEAVE_STAY_FLAG);
        } else {
            FieldActor_PlaySound(actor, FAPS_SOUND_LEAVE_STAY);
        }
    }
}
CLEAN_AS(func_ov004_0222bcf4, FieldActorPlaceStates_LeaveStay)

/* func_ov004_0222bd40 (state 8's message handler): already in state 8 the argument is kept
 * (FieldActor.unk_C84); else state 8 is asked for (kind 0, priority 6). */
void FieldActorPlaceStates_StayMessage(FieldActor *actor, int arg)
{
    if (actor->state == FAPS_STAY) {
        actor->unk_C84 = (s16) arg;
    } else {
        FieldActorPlaceStates_RequestStay(actor, 0, FAPS_PRIORITY, arg);
    }
}
CLEAN_AS(func_ov004_0222bd40, FieldActorPlaceStates_StayMessage)

/* func_ov004_0222bd6c (state 8's entry): unless animation 0x11 plays already it loops, blended
 * over 3 frames for this console's actor coming from a state other than 0x0d and 0x0f. The
 * work is the request's kind; with kind 0 this console's actor finishes the event of kind 4 or
 * 12. */
void FieldActorPlaceStates_EnterStay(FieldActor *actor, const StateRequest *request, int previous)
{
    if (actor->animation != FAPS_ANIM_STAY) {
        if (previous == FAPS_FROM_0F || previous == FAPS_STEP || !faps_is_local(actor)) {
            FieldActor_PlayAnimationLoop(actor, FAPS_ANIM_STAY, 0, 0);
        } else {
            FieldActor_PlayAnimationLoop(actor, FAPS_ANIM_STAY, FAPS_BLEND, 0);
        }
    }
    FieldActorPlaceStates_SetStayWork(faps_stay_of(actor), request->payload[0]);
    if (*faps_stay_of(actor) == 0 && faps_is_local(actor)) {
        EventQueue_FinishKind4Or12();
    }
}
CLEAN_AS(func_ov004_0222bd6c, FieldActorPlaceStates_EnterStay)

/* func_ov004_0222bdec: state 8's work: the kind. */
void FieldActorPlaceStates_SetStayWork(u8 *work, u8 kind)
{
    *work = kind;
}
CLEAN_AS(func_ov004_0222bdec, FieldActorPlaceStates_SetStayWork)

/* func_ov004_0222bdf0: state 8 asked for with the kind; whether it was queued. */
int FieldActorPlaceStates_RequestStay(FieldActor *actor, int kind, int priority, int arg)
{
    StateRequest request;
    StateRequest_Construct(&request);
    StateRequest_Set(&request, FAPS_STAY, priority, arg);
    func_ov004_0222be30(request.payload, (u8) kind);
    int queued = FieldActor_QueueRequest(actor, &request);
    StateRequest_Destruct(&request);
    return queued;
}
CLEAN_AS(func_ov004_0222bdf0, FieldActorPlaceStates_RequestStay)
