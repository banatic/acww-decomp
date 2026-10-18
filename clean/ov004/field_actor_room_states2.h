/* More of overlay 4's states of the field actor in the rooms (main's field_actor_parts.h has
 * the state tables; field_actor_room_states.h has others):
 *   0x0e  waiting for a place in the room (main's place_claim.h): the actor turns to the
 *         work's yaw where it stands; given, once it faces that yaw state 0x0f is asked for
 *         with the work's side, point and kind; refused, the state ends;
 *   0x0f  taking that place: animation 7 (side 1) or 8 (side 0) with sound 0x4c5; the actor
 *         eases along x or z (by the yaw's 0x4000 bit) to the point, a sound at the point at
 *         frame 0xd in a room, and at the animation's end FieldActorPlaceStates_RequestStay with the kind;
 *   0x12  the actor turns to yaw 0x8000 and eases to a fixed point of the overlay while
 *         animation 0x9b loops; the camera snaps to that point on entering;
 *   0x1c  an item taken from the room's floor or one of its objects (state 0x18 indoors):
 *         animation 0x19 while the console's verdict (0x818) comes; the item shrinks into
 *         the actor and goes into the pockets, or a talk ("obj_etc_player") says the pockets
 *         are full, or ("obj_etc_error") that there are too many visitors;
 *   0x1d  the actor stands at a piece of furniture's point and yaw while animation 0x1a
 *         plays; there, it takes hold (state 0x1e); A let go before, it toggles the
 *         furniture's switch once, then the state ends;
 *   0x1e  holding the furniture with A: pushed far enough (above 0x333) the stick's quadrant
 *         asks for FieldActorRoomStates_RequestPull (2), state 0x20 (0) or a turn (state 0x1f, quadrants 3
 *         and 1, only after the stick was let back below 0x333); with more than one visitor
 *         a talk ("obj_etc_error") opens instead; A let go ends it;
 *   0x1f  the furniture turned (animation 0x1b one way, 0x1c the other) and the animation
 *         played back; then state 0x1e again (A held) or the state ends;
 *   0x20  animation 0x1d (its update is elsewhere in the overlay).
 * Each message handler asks for the state again from the saved bytes (0x1d: priority 5;
 * 0x1e: priority 5; 0x20: priority 6; 0x0e and 0x0f: priority 6); 0x12, 0x1c and 0x1f's do
 * nothing. */
#ifndef CLEAN_OV004_FIELD_ACTOR_ROOM_STATES2_H
#define CLEAN_OV004_FIELD_ACTOR_ROOM_STATES2_H

#include "autoload_2/vector.h"
#include "types.h"

struct FieldActor;
struct StateRequest;

/* State 0x0e's work at 0x7d4. */
typedef struct FieldActorClaimPlaceWork {
    fx32 x; /* the place's point */
    fx32 z;
    s16 yaw;
    u8 side; /* handed to state 0x0f */
    u8 kind; /* handed to state 0x0f */
} FieldActorClaimPlaceWork;

/* State 0x0f's work at 0x7d4. */
typedef struct FieldActorTakePlaceWork {
    fx32 x; /* the place's point */
    fx32 z;
    s16 yaw; /* bit 0x4000 set: the actor eases along x, else along z */
    u8 kind; /* handed to FieldActorPlaceStates_RequestStay at the end */
} FieldActorTakePlaceWork;

/* What a request for state 0x0f carries. */
typedef struct FieldActorTakePlaceArgs {
    u8 side; /* 0: animation 8, yaw a quarter turn up; else animation 7, a quarter turn down */
    u8 pad_01[3];
    fx32 x;
    fx32 z;
    u8 kind;
} FieldActorTakePlaceArgs;

/* State 0x1c's work at 0x7d4. */
typedef struct FieldActorTakeItemWork {
    int number; /* the room object's number for RoomObjects_TakeWithItem; negative: the floor */
    u8 verdict; /* 0 waiting, 1 taken, 2 refused (the word at 0x818) */
    u8 step;    /* FARS2_TAKE_... */
} FieldActorTakeItemWork;

/* What a request for state 0x1c carries. */
typedef struct FieldActorTakeItemArgs {
    u8 x; /* the tile */
    u8 z;
    u8 pad_02[2];
    int number;
} FieldActorTakeItemArgs;

/* State 0x1d's work at 0x7d4; a request for it carries the first three. */
typedef struct FieldActorFurnitureReachWork {
    fx32 x; /* where the actor stands */
    fx32 z;
    s16 yaw;
    u8 toggled; /* the switch has been toggled */
} FieldActorFurnitureReachWork;

/* State 0x1e's work at 0x7d4. */
typedef struct FieldActorFurnitureHoldWork {
    u8 released; /* the stick was below 0x333 since the last turn */
    u8 phase;    /* 0 holding; 1 to 3 the talk */
} FieldActorFurnitureHoldWork;

/* The two bytes a request for state 0x1e carries, kept at 0x8f0 too. */
typedef struct FieldActorFurnitureHoldArgs {
    u8 released; /* nonzero: start as if the stick had been let go */
    u8 blend;    /* nonzero: the animation is blended over 3 frames */
} FieldActorFurnitureHoldArgs;

void FieldActorRoomStates2_UpdateClaimPlace(struct FieldActor *actor);
void FieldActorRoomStates2_ClaimPlacePose(struct FieldActor *actor);
void FieldActorRoomStates2_RunClaimPlace(struct FieldActor *actor);
void FieldActorRoomStates2_LeaveClaimPlace(struct FieldActor *actor, int next);
void FieldActorRoomStates2_ClaimPlaceMessage(struct FieldActor *actor, s16 arg);

void FieldActorRoomStates2_UpdateTakePlace(struct FieldActor *actor);
int FieldActorRoomStates2_EndTakePlace(struct FieldActor *actor);
void FieldActorRoomStates2_SoundTakePlace(struct FieldActor *actor);
void FieldActorRoomStates2_EaseTakePlace(struct FieldActor *actor);
void FieldActorRoomStates2_LeaveTakePlace(struct FieldActor *actor, int next);
void FieldActorRoomStates2_TakePlaceMessage(struct FieldActor *actor, s16 arg);
void FieldActorRoomStates2_EnterTakePlace(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates2_GetTakePlaceSaved(const u8 *saved, u8 *side, u32 *x, u32 *z);
void FieldActorRoomStates2_PutTakePlaceSaved(u8 *saved, u8 side, int x, int z);
void FieldActorRoomStates2_SetTakePlaceWork(FieldActorTakePlaceWork *work, int x, int z, s16 yaw, u8 kind);
int FieldActorRoomStates2_RequestTakePlace(struct FieldActor *actor, int side, int x, int z, u8 kind, int priority, s16 arg);
void FieldActorRoomStates2_SetTakePlaceArgs(FieldActorTakePlaceArgs *args, u8 side, int x, int z, u8 kind);

void FieldActorRoomStates2_UpdateFixedPoint(struct FieldActor *actor);
void FieldActorRoomStates2_MoveFixedPoint(struct FieldActor *actor);
void FieldActorRoomStates2_FixedPointMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates2_EnterFixedPoint(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates2_RequestFixedPoint(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates2_UpdateTakeItem(struct FieldActor *actor);
void FieldActorRoomStates2_RunTakeItem(struct FieldActor *actor);
void FieldActorRoomStates2_ShrinkTakeItem(struct FieldActor *actor);
void FieldActorRoomStates2_WaitTakeItem(struct FieldActor *actor);
void FieldActorRoomStates2_TakeItemMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates2_EnterTakeItem(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates2_RequestTakeItem(struct FieldActor *actor, const int *tile, int number, int priority, s16 arg);
void FieldActorRoomStates2_SetTakeItemArgs(FieldActorTakeItemArgs *args, const u32 *tile, u32 number);

void FieldActorRoomStates2_UpdateFurnitureReach(struct FieldActor *actor);
void FieldActorRoomStates2_RunFurnitureReach(struct FieldActor *actor);
void FieldActorRoomStates2_FurnitureReachPose(struct FieldActor *actor);
void FieldActorRoomStates2_LeaveFurnitureReach(struct FieldActor *actor, int next);
void FieldActorRoomStates2_FurnitureReachMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates2_EnterFurnitureReach(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates2_GetFurnitureReachSaved(const u8 *saved, u32 *x, u32 *z, s16 *yaw);
void FieldActorRoomStates2_PutFurnitureReachSaved(u8 *saved, int x, int z, int yaw);
void FieldActorRoomStates2_SetFurnitureReachWork(FieldActorFurnitureReachWork *work, int x, int z, u16 yaw);
int FieldActorRoomStates2_RequestFurnitureReach(struct FieldActor *actor, int x, int z, int yaw, int priority, s16 arg);
void FieldActorRoomStates2_SetFurnitureReachArgs(FieldActorFurnitureReachWork *args, int x, int z, int yaw);

void FieldActorRoomStates2_UpdateFurnitureHold(struct FieldActor *actor);
void FieldActorRoomStates2_RunFurnitureHold(struct FieldActor *actor);
void FieldActorRoomStates2_FurnitureHoldMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates2_EnterFurnitureHold(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates2_GetFurnitureHoldSaved(const FieldActorFurnitureHoldArgs *saved, u8 *released, u8 *blend);
void FieldActorRoomStates2_PutFurnitureHoldSaved(FieldActorFurnitureHoldArgs *saved, u8 released, u8 blend);
FieldActorFurnitureHoldWork *FieldActorRoomStates2_StartFurnitureHold(FieldActorFurnitureHoldWork *work, int push);
int FieldActorRoomStates2_RequestFurnitureHold(struct FieldActor *actor, int released, int blend, int priority, s16 arg);
void FieldActorRoomStates2_SetFurnitureHoldArgs(FieldActorFurnitureHoldArgs *args, u8 released, u8 blend);

void FieldActorRoomStates2_UpdateFurnitureTurn(struct FieldActor *actor);
void FieldActorRoomStates2_RunFurnitureTurn(struct FieldActor *actor);
void FieldActorRoomStates2_FurnitureTurnMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates2_EnterFurnitureTurn(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates2_SetFurnitureTurnReleased(u8 *released, u8 value);
int FieldActorRoomStates2_RequestFurnitureTurn(struct FieldActor *actor, int plus, int priority, s16 arg);
void FieldActorRoomStates2_SetFurnitureTurnArgs(u8 *plus, u8 value);

void FieldActorRoomStates2_State20Message(struct FieldActor *actor, int arg);
void FieldActorRoomStates2_EnterState20(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates2_RequestState20(struct FieldActor *actor, int priority, int arg);

#endif
