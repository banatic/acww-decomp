/* Overlay 4's part of the field actor (main's field_actor.h; its layout in ov003/field_actor.h)
 * in the rooms: acting with the tool on what is ahead (the room's objects first, then the
 * items on its floor), a walk towards a point, the fading of its models, a message to the
 * session, and its states at the room's doors (main's field_actor_parts.h has the state
 * tables):
 *   0x8e  walk in:  the actor starts 6.0 behind its place (its facing sorted into four
 *                   sectors) and walks forward to it (a start state of the rooms);
 *   0x8d  step off: it walks to the request's point (PlayerActorOps_StepOffDoor asks for it
 *                   6.0 beyond a door);
 *   0x8c  exit:     it walks through a door; at its 10th frame this console's actor takes
 *                   the scene's exit (its entry and walk are elsewhere in the overlay).
 * In each the work at 0x7d4 is a FieldActorRoomsWalk, and the point the actor walks to is kept
 * packed at 0x8f0 (x and z) for the message handler of another console's actor. */
#ifndef CLEAN_OV004_FIELD_ACTOR_ROOMS_H
#define CLEAN_OV004_FIELD_ACTOR_ROOMS_H

#include "autoload_2/vector.h"
#include "types.h"

struct FieldActor;
struct StateRequest;

/* The work at 0x7d4 of the door states. */
typedef struct FieldActorRoomsWalk {
    Vec3 point;     /* 0x00: where it walks to */
    fx32 speed;     /* 0x0c: its speed (20.12) */
    fx32 max_speed; /* 0x10 */
    u8 frames;      /* 0x14: state 0x8c: frames since its entry */
    u8 kind;        /* 0x15: state 0x8c: how it goes through the door (1 and 2 take the exit) */
} FieldActorRoomsWalk;

void FieldActorRooms_WalkToward(struct FieldActor *actor, const Vec3 *target, fx32 *speed, const fx32 *max_speed);
int FieldActorRooms_TryTool(struct FieldActor *actor);
void FieldActorRooms_SendPair(struct FieldActor *actor, unsigned int low, unsigned int high);
int FieldActorRooms_TryTarget(struct FieldActor *actor, int tool, int mode);
void FieldActorRooms_FadeAlpha(struct FieldActor *actor, unsigned int target, unsigned int step);

void FieldActorRooms_UpdateWalkIn(struct FieldActor *actor);
void FieldActorRooms_StepWalkIn(struct FieldActor *actor);
void FieldActorRooms_WalkInMessage(struct FieldActor *actor, int arg);
void FieldActorRooms_EnterWalkIn(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRooms_UnpackWalkInPoint(const u8 *packed, u32 *x, u32 *z);
void FieldActorRooms_PackWalkInPoint(u8 *packed, int x, int z);
void FieldActorRooms_SetWalkInWork(FieldActorRoomsWalk *work, Vec3 point, fx32 speed);
int FieldActorRooms_RequestWalkIn(struct FieldActor *actor, const Vec3 *point, int priority, int arg);
void FieldActorRooms_PutWalkInPoint(Vec3 *payload, Vec3 point);

void FieldActorRooms_UpdateStepOff(struct FieldActor *actor);
void FieldActorRooms_StepStepOff(struct FieldActor *actor);
void FieldActorRooms_StepOffMessage(struct FieldActor *actor, int arg);
void FieldActorRooms_EnterStepOff(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRooms_UnpackStepOffPoint(const u8 *packed, u32 *x, u32 *z);
void FieldActorRooms_PackStepOffPoint(u8 *packed, int x, int z);
void FieldActorRooms_SetStepOffWork(FieldActorRoomsWalk *work, Vec3 point, fx32 speed, fx32 max_speed);
int FieldActorRooms_RequestStepOff(struct FieldActor *actor, const Vec3 *point, int priority, int arg);
void FieldActorRooms_PutStepOffPoint(Vec3 *payload, Vec3 point);

void FieldActorRooms_UpdateExit(struct FieldActor *actor);

#endif
