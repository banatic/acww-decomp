/* More of overlay 4's states of the field actor in the rooms (main's field_actor_parts.h has
 * the state tables; field_actor_room_states2.h has state 0x0e's update and state 0x0f): a
 * place the actor stays at, claimed in the room (main's place_claim.h), and the ways off it to
 * either side. "Side 1" is the way of yaw + 0x4000, "side 0" that of yaw - 0x4000.
 *   0x0e  (its entry here) the request's point and yaw; this console's actor takes the point
 *         2.0 ahead of it and claims it (PlaceClaim_Request3); animation 0x1a loops;
 *   0x08  at the place: animation 0x11 loops. This console's actor, outside the scenes 6 to 8,
 *         pushed to a side asks the overlay whether that side 2.0 away is free: free, state
 *         0x0b that way; not free, state 0x09. The message handler keeps its argument
 *         (FieldActor.unk_C84) when the actor is already in the state. Left for state 0x0a in
 *         the scenes 6 to 8 with kind 0, sound 0x4cd or 0x4cc (by the record's flag 0x249a);
 *   0x09  the point 1.0 ahead and 2.0 to the side is claimed (PlaceClaim_Request2) and a
 *         contact body put there; given, state 0x0a that way unless an object was met there
 *         (then state 0x08 again); refused, state 0x08 again;
 *   0x0a  off the place over that side: animation 0x0a (side 1) or 9 (side 0), sound 0x4c6 at
 *         frame 21 (this console's actor then lets its claim go). At its end state 2, or with
 *         the request's flag set state 0x10 with the sun level stored. On leaving, the actor
 *         stands at that point turned a quarter that way;
 *   0x0b  the point 2.0 to the side is claimed (PlaceClaim_Request1) while animation 0x0c
 *         (side 1) or 0x0f (side 0) loops; from the third frame given asks for state 0x0d,
 *         refused for state 0x0c;
 *   0x0c  animation 0x0d (side 1) or 0x10 (side 0) and sound 0x4a4; then state 0x08;
 *   0x0d  animation 0x0b (side 1) or 0x0e (side 0) and sound 0x435; then state 0x08 (the
 *         byte at 0x8ea cleared). On leaving, the actor stands at the point 2.0 to the side.
 * Each message handler asks for its state again with priority 6 and the side kept at 0x8f0
 * (state 9's does nothing). In a room (data_020e54a8 1) entering state 0x0a plays the room
 * object's sound 2 at the actor's position (ov004/room_point_sound.h). */
#ifndef CLEAN_OV004_FIELD_ACTOR_PLACE_STATES_H
#define CLEAN_OV004_FIELD_ACTOR_PLACE_STATES_H

#include "autoload_2/vector.h"
#include "types.h"

struct FieldActor;
struct StateRequest;

/* What a request for state 0x0e carries, and that state's work at 0x7d4. */
typedef struct FieldActorPlaceArgs {
    fx32 x; /* 0x00: the place's point */
    fx32 z; /* 0x04 */
    s16 yaw;
    u8 side; /* 0x0a: handed on to state 0x0f */
    u8 kind; /* 0x0b: 1 when the request was made with priority 6; handed on to state 8 */
} FieldActorPlaceArgs;

/* State 0x0a's work: the point beside the place, the yaw to leave it at and the request's
 * flag; what a request for it carries is the side and the flag. */
typedef struct FieldActorPlaceOffWork {
    fx32 x;
    fx32 z;
    s16 yaw;
    u8 store_sun; /* nonzero: the state ends in state 0x10 with the sun level stored */
} FieldActorPlaceOffWork;

typedef struct FieldActorPlaceOffArgs {
    u8 side;
    u8 store_sun;
} FieldActorPlaceOffArgs;

/* State 9's work: the point claimed and the side. */
typedef struct FieldActorPlaceProbeWork {
    Vec3 point;
    u8 side;
} FieldActorPlaceProbeWork;

/* State 0x0b's work: its frames (counted to 3) and the side. */
typedef struct FieldActorPlaceClaimWork {
    u8 frames;
    u8 side;
} FieldActorPlaceClaimWork;

/* State 0x0d's work: the point 2.0 to the side. */
typedef struct FieldActorPlaceStepWork {
    fx32 x;
    fx32 z;
} FieldActorPlaceStepWork;

void FieldActorPlaceStates_EnterApproach(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorPlaceStates_GetApproachSaved(const u8 *saved, u32 *x, u32 *z, s16 *yaw, u8 *side);
void FieldActorPlaceStates_PutApproachSaved(u8 *saved, int x, int z, int yaw, u8 side);
void FieldActorPlaceStates_SetApproachWork(FieldActorPlaceArgs *work, int x, int z, s16 yaw, u8 side, u8 kind);
int FieldActorPlaceStates_RequestApproach(struct FieldActor *actor, int x, int z, int yaw, u8 side, int priority, s16 arg);
void FieldActorPlaceStates_PutApproachArgs(FieldActorPlaceArgs *args, int x, int z, s16 yaw, u8 side, u8 kind);

void FieldActorPlaceStates_UpdateStep(struct FieldActor *actor);
void FieldActorPlaceStates_EndStep(struct FieldActor *actor);
void FieldActorPlaceStates_LeaveStep(struct FieldActor *actor, int next);
void FieldActorPlaceStates_StepMessage(struct FieldActor *actor, int arg);
void FieldActorPlaceStates_EnterStep(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorPlaceStates_GetStepSaved(const u8 *saved, u8 *side);
void FieldActorPlaceStates_PutStepSaved(u8 *saved, u8 side);
void FieldActorPlaceStates_SetStepWork(FieldActorPlaceStepWork *work, int x, int z);
int FieldActorPlaceStates_RequestStep(struct FieldActor *actor, int side, int priority, int arg);
void FieldActorPlaceStates_PutStepArgs(u8 *payload, u8 side);

void FieldActorPlaceStates_UpdateRefused(struct FieldActor *actor);
void FieldActorPlaceStates_EndRefused(struct FieldActor *actor);
void FieldActorPlaceStates_RefusedMessage(struct FieldActor *actor, int arg);
void FieldActorPlaceStates_EnterRefused(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorPlaceStates_GetRefusedSaved(const u8 *saved, u8 *side);
void FieldActorPlaceStates_PutRefusedSaved(u8 *saved, u8 side);
int FieldActorPlaceStates_RequestRefused(struct FieldActor *actor, int side, int priority, int arg);
void FieldActorPlaceStates_PutRefusedArgs(u8 *payload, u8 side);

void FieldActorPlaceStates_UpdateClaim(struct FieldActor *actor);
void FieldActorPlaceStates_WaitClaim(struct FieldActor *actor);
void FieldActorPlaceStates_ClaimMessage(struct FieldActor *actor, int arg);
void FieldActorPlaceStates_EnterClaim(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorPlaceStates_GetClaimSaved(const u8 *saved, u8 *side);
void FieldActorPlaceStates_PutClaimSaved(u8 *saved, u8 side);
void FieldActorPlaceStates_SetClaimWork(FieldActorPlaceClaimWork *work, u8 side);
int FieldActorPlaceStates_RequestClaim(struct FieldActor *actor, int side, int priority, int arg);
void FieldActorPlaceStates_PutClaimArgs(u8 *payload, u8 side);

void FieldActorPlaceStates_UpdateOff(struct FieldActor *actor);
void FieldActorPlaceStates_EndOff(struct FieldActor *actor);
void FieldActorPlaceStates_ContactOff(struct FieldActor *actor);
void FieldActorPlaceStates_StepOff(struct FieldActor *actor);
void FieldActorPlaceStates_LeaveOff(struct FieldActor *actor, int next);
void FieldActorPlaceStates_OffMessage(struct FieldActor *actor, int arg);
void FieldActorPlaceStates_EnterOff(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorPlaceStates_GetOffSaved(const u8 *saved, u8 *side);
void FieldActorPlaceStates_PutOffSaved(u8 *saved, u8 side);
void FieldActorPlaceStates_SetOffWork(FieldActorPlaceOffWork *work, int x, int z, s16 yaw, u8 store_sun);
int FieldActorPlaceStates_RequestOff(struct FieldActor *actor, int side, int store_sun, int priority, s16 arg);
void FieldActorPlaceStates_PutOffArgs(FieldActorPlaceOffArgs *args, u8 side, u8 store_sun);

void FieldActorPlaceStates_UpdateProbe(struct FieldActor *actor);
void FieldActorPlaceStates_WaitProbe(struct FieldActor *actor);
void FieldActorPlaceStates_ContactProbe(struct FieldActor *actor);
void FieldActorPlaceStates_ProbeMessage(struct FieldActor *actor, int arg);
void FieldActorPlaceStates_EnterProbe(struct FieldActor *actor, const struct StateRequest *request, int previous);
void *FieldActorPlaceStates_SetProbeWork(FieldActorPlaceProbeWork *work, const Vec3 *point, int side);
int FieldActorPlaceStates_RequestProbe(struct FieldActor *actor, int side, int priority, int arg);
void FieldActorPlaceStates_PutProbeArgs(u8 *payload, u8 side);

void FieldActorPlaceStates_UpdateStay(struct FieldActor *actor);
void FieldActorPlaceStates_PushStay(struct FieldActor *actor);
void FieldActorPlaceStates_LeaveStay(struct FieldActor *actor, int next);
void FieldActorPlaceStates_StayMessage(struct FieldActor *actor, int arg);
void FieldActorPlaceStates_EnterStay(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorPlaceStates_SetStayWork(u8 *work, u8 kind);
int FieldActorPlaceStates_RequestStay(struct FieldActor *actor, int kind, int priority, int arg);

#endif
