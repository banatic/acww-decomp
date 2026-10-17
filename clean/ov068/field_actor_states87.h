/* Overlay 68's states of the field actor (the player's actor, ov003/field_actor.h): 0x87 and
 * 0x88, which Sequence4 (sequence4.h) asks of this console's player (FieldActor_PlayerRequest*).
 *
 *   state 0x87: animation 0x82 at yaw 0; a footstep at frame 0x16; at its end the
 *               actor asks for state 0x10 and the player's byte of sun flags is cleared.
 *               Entering it also clears flag 0 and, for a player with a record, keeps
 *               yesterday as the record's sun date (FieldActor_StoreSunDate).
 *   state 0x88: animation 0x83 (blended over 3 frames) at yaw 0; a footstep at frame 8; at
 *               its end the actor asks for state 1 (priority 9).
 *
 * Each state's end (its exit function) turns the actor half round and moves it by 1.75 along x
 * and 2.75 along z: by (-1.75, +2.75) after 0x88, by (+1.75, -2.75) after 0x87. Their message
 * handlers do nothing. */
#ifndef CLEAN_OV068_FIELD_ACTOR_STATES87_H
#define CLEAN_OV068_FIELD_ACTOR_STATES87_H

#include "ov003/field_actor.h"
#include "types.h"

void FieldActor_UpdateState88(FieldActor *actor);
void FieldActor_EndState88(FieldActor *actor);
void FieldActor_StepState88(FieldActor *actor);
void FieldActor_ExitState88(FieldActor *actor);
void FieldActor_State88Message(FieldActor *actor, int arg);
void FieldActor_EnterState88(FieldActor *actor, const StateRequest *request, int previous);
u32 FieldActor_RequestState88(FieldActor *actor, unsigned int priority, unsigned int arg);
void FieldActor_UpdateState87(FieldActor *actor);
void FieldActor_EndState87(FieldActor *actor);
void FieldActor_StepState87(FieldActor *actor);
void FieldActor_ExitState87(FieldActor *actor);
void FieldActor_State87Message(FieldActor *actor, int arg);
void FieldActor_EnterState87(FieldActor *actor, const StateRequest *request, int previous);
void *FieldActor_RequestState87(FieldActor *actor, int priority, int arg);
int FieldActor_PlayerRequestState88(void);
void *FieldActor_PlayerRequestState87(void);

#endif
