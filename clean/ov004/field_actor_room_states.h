/* More of overlay 4's states of the field actor (main's field_actor_parts.h has the state
 * tables; field_actor_rooms.h the door states):
 *   0x44  the actor fades in (its models' alpha up to 31 by 6 a frame) while its animation
 *         plays, with footsteps at frames 1, 6, 12 and 20; at its end it nudges one thing and
 *         state 2 is asked for;
 *   0x7a  the head's kind is cleared (from frame 3; the hair colour kept), then state 0x7b;
 *   0x7b  an animation, then state 0x7c with the same two bytes;
 *   0x7c  an effect at frame 10; from frame 11 the head takes the request's kind and hair
 *         colour, which go into the player's record; at its end, the stick pushed towards where
 *         the actor faces asks for state 0x2c. On leaving, this console's actor sends both to the session;
 *   0x7d  the telephone picked up: this console's actor stands at the tile ahead moved 2.0
 *         in z, at yaw 0x8000, while the telephone's animation plays from its start; then
 *         state 0x7e;
 *   0x7e  on the telephone: the actor follows what is reported, the telephone's animation
 *         plays from its end;
 *   0x7f  the telephone hung up: the pick-up animation plays backwards, as does the
 *         telephone's; then state 2;
 *   0x8a  animations 0x95, 0x96 and 0x97 one after another (after 0x98, state 0x28).
 * Each request carries its two bytes (0x7a to 0x7c) or nothing; each message handler asks for
 * the state again with priority 6 (0x7a to 0x7c and 0x8a do nothing). */
#ifndef CLEAN_OV004_FIELD_ACTOR_ROOM_STATES_H
#define CLEAN_OV004_FIELD_ACTOR_ROOM_STATES_H

#include "autoload_2/vector.h"
#include "types.h"

struct FieldActor;
struct StateRequest;

/* The work at 0x7d4 of states 0x7a to 0x7c: the head's kind and hair colour asked for. */
typedef struct FieldActorHairWork {
    u8 kind;
    u8 hair_color;
    u8 applied; /* state 0x7c: the head has taken them */
} FieldActorHairWork;

void FieldActorRoomStates_UpdateFadeIn(struct FieldActor *actor);
int FieldActorRoomStates_EndFadeIn(struct FieldActor *actor);
void FieldActorRoomStates_FadeInSteps(struct FieldActor *actor);

void FieldActorRoomStates_UpdateHairOff(struct FieldActor *actor);
void FieldActorRoomStates_StepHairOff(struct FieldActor *actor);
void FieldActorRoomStates_HairOffMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterHairOff(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestHairOff(struct FieldActor *actor, int kind, int hair_color, int priority, s16 arg);

void FieldActorRoomStates_UpdateHairWait(struct FieldActor *actor);
void FieldActorRoomStates_EndHairWait(struct FieldActor *actor);
void FieldActorRoomStates_HairWaitMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterHairWait(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestHairWait(struct FieldActor *actor, int kind, int hair_color, int priority, s16 arg);

void FieldActorRoomStates_UpdateHairOn(struct FieldActor *actor);
void FieldActorRoomStates_EndHairOn(struct FieldActor *actor);
void FieldActorRoomStates_StepHairOn(struct FieldActor *actor);
void FieldActorRoomStates_LeaveHairOn(struct FieldActor *actor);
void FieldActorRoomStates_HairOnMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterHairOn(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestHairOn(struct FieldActor *actor, int kind, int hair_color, int priority, s16 arg);

void FieldActorRoomStates_UpdatePickUp(struct FieldActor *actor);
void FieldActorRoomStates_EndPickUp(struct FieldActor *actor);
void FieldActorRoomStates_StandPickUp(struct FieldActor *actor);
void FieldActorRoomStates_PickUpMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterPickUp(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActorRoomStates_PutPickUpPoint(Vec3 *work, Vec3 point);
int FieldActorRoomStates_RequestPickUp(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateOnPhone(struct FieldActor *actor);
void FieldActorRoomStates_OnPhoneMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterOnPhone(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestOnPhone(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateHangUp(struct FieldActor *actor);
void FieldActorRoomStates_EndHangUp(struct FieldActor *actor);
void FieldActorRoomStates_HangUpMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterHangUp(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestHangUp(struct FieldActor *actor, int priority, int arg);

void FieldActorRoomStates_UpdateSequence8A(struct FieldActor *actor);
void FieldActorRoomStates_StepSequence8A(struct FieldActor *actor);
void FieldActorRoomStates_Sequence8AMessage(struct FieldActor *actor, int arg);
void FieldActorRoomStates_EnterSequence8A(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActorRoomStates_RequestSequence8A(struct FieldActor *actor, int priority, int arg);

#endif
