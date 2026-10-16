/* What the rest of the game asks of a session player's field actor (ov003/field_actor.h): each
 * function finds the actor with func_02096718 (player 4 is the player at this console; NULL
 * when the player has none) and reads it, sets or tests one of its flags, changes its looks and
 * held item together with the player's record, or asks for one of its states. Without an actor
 * nothing happens and the answer is 0 (0x93 where a state is asked for). */
#ifndef CLEAN_MAIN_PLAYER_ACTOR_OPS_H
#define CLEAN_MAIN_PLAYER_ACTOR_OPS_H

#include "autoload_2/vector.h"
#include "types.h"

struct FieldActorBlock48;

/* func_02096718's player for the player at this console. */
#define PLAYER_ACTOR_OPS_OWN 4

/* The state answered when there is no actor. */
#define PLAYER_ACTOR_OPS_NO_STATE 0x93

void PlayerActorOps_Nothing(void);
void PlayerActorOps_NoteObjectKind(int *kind);
void PlayerActorOps_NoteObject(unsigned int *object);
u16 *PlayerActorOps_ItemAhead(void);
void PlayerActorOps_CopyBlock698(struct FieldActorBlock48 *out, int player);
int PlayerActorOps_HeadPoint(Vec3 *out, int player);
int PlayerActorOps_SetLook(int pitch, int yaw, int player);
int PlayerActorOps_SetSunLevel(int level, int player);
int PlayerActorOps_SetFlag0(int set, int player);
int PlayerActorOps_SetWorn(u16 *item, int part, int player);
int PlayerActorOps_SetHeldModel(unsigned int number, int player);
void PlayerActorOps_HeldItem(u16 *item, int player);
Vec3 *PlayerActorOps_StartPosition(int player);
int PlayerActorOps_RequestState14(unsigned char *kind);
int PlayerActorOps_RequestState13(void);
int PlayerActorOps_StepOffDoor(void);
int PlayerActorOps_RequestState10(void);
void PlayerActorOps_Approach(unsigned int approach);
int PlayerActorOps_RequestState79(void);
int PlayerActorOps_RequestState32(void);
int PlayerActorOps_RequestState30(u16 *item, int *a, unsigned char *b, int *c, int d);
int PlayerActorOps_Turn(int yaw, int player);
int PlayerActorOps_MoveTo(Vec3 *point, int accel, int player);
int PlayerActorOps_RequestState85(unsigned short *item);
int PlayerActorOps_RequestState3F(unsigned short *item);
int PlayerActorOps_RequestState7Kind2Next10(u16 *item);
void PlayerActorOps_RequestState7Kind1Next10(u16 *item);
int PlayerActorOps_RequestState7Kind0Next10(u16 *item);
int PlayerActorOps_RequestState7NoItem(void);
int PlayerActorOps_RequestState7Kind2Next5(u16 *item);
int PlayerActorOps_RequestState7Kind1Next5(u16 *item);
int PlayerActorOps_RequestState7Kind0Next5(u16 *item);
int PlayerActorOps_RequestState7(unsigned short *item, int kind, int next);
int PlayerActorOps_FinishState(void);
int PlayerActorOps_RequestState5(void);
int PlayerActorOps_QueueBelow5(void);
int PlayerActorOps_Flag0bInState28_2_8(void);
int PlayerActorOps_MayAct(void);
int PlayerActorOps_QueueBelow6(void);
int PlayerActorOps_MayActFree(void);
int PlayerActorOps_ClearFlag(int bit, int player);
int PlayerActorOps_SetFlag(int bit, int player);
int PlayerActorOps_SetOwnFlag17(void);
int PlayerActorOps_SwitchFlag10(int on, int player);
void PlayerActorOps_SwitchFlag0e(int on, int player);
int PlayerActorOps_SwitchOwnFlag0b(int on);
int PlayerActorOps_StateFlagA20(void);
int PlayerActorOps_InState3F(void);
int PlayerActorOps_EarlyInState7(void);
int PlayerActorOps_StateOrStartState(void);
int PlayerActorOps_PlaceAfterState(Vec3 *position, s16 *yaw);
int PlayerActorOps_State(int player);
int PlayerActorOps_InState(int state, int player);
int PlayerActorOps_TestFlag(int bit, int player);
int PlayerActorOps_InState90(void);
int PlayerActorOps_InState5(void);
int PlayerActorOps_IsBusy(int player);
int PlayerActorOps_TestOwnFlag4(void);
int PlayerActorOps_TestOwnFlag1(void);
int PlayerActorOps_StartState(int made_with);

#endif
