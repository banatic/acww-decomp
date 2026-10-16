/* The main program's part of the field actor's class (vtable 0x020d82b4, second vtable
 * 0x020d832c for its message receiver at 0xec; include/cpp/main/Obj_020d82b4.h): the
 * allocation and freeing of its objects, the vtable slots that only pass on to the real work,
 * the constructor and destructors (field_actor.c), the placing of its models for drawing
 * (field_actor_model.c), and its state machine with the states 0x19 to 0x1b, 0x30 to 0x35,
 * 0x3f, 0x6f, 0x70, 0x76, 0x77, 0x79, 0x83 to 0x86 and 0x90 to 0x92 (field_actor_states.c;
 * field_actor_parts.h has what they share). Overlay 3's part is in ov003/field_actor.h.
 *
 * Its objects come from the heap at data_021c9ab4, zeroed and aligned to 4. */
#ifndef CLEAN_MAIN_FIELD_ACTOR_H
#define CLEAN_MAIN_FIELD_ACTOR_H

#include "autoload_2/vector.h"
#include "types.h"

struct FieldActor;

void FieldActor_Delete(void *actor);
void *FieldActor_New(int size);
void FieldActor_Teardown(struct FieldActor *actor);
int FieldActor_Vfunc24(struct FieldActor *actor);
int FieldActor_Update(struct FieldActor *actor);
void FieldActor_Setup(struct FieldActor *actor);
struct FieldActor *FieldActor_DestructDelete(struct FieldActor *actor);
void *FieldActor_Destruct(struct FieldActor *actor);
struct FieldActor *FieldActor_Construct(struct FieldActor *actor);
int FieldActor_Shutdown(struct FieldActor *actor);

/* field_actor_model.c: placing the actor's models for drawing. */
struct NodeRenderState;
void FieldActor_PlaceForDraw(struct FieldActor *actor);
int FieldActor_ModelY(struct FieldActor *actor, int y);
void FieldActor_PlaceModel(struct FieldActor *actor);
void FieldActor_PlaceAtPosition(struct FieldActor *actor);
void FieldActor_NodeAfter(struct NodeRenderState *state);
void FieldActor_NodeTransform(struct NodeRenderState *state);
void FieldActor_NodeBefore(struct NodeRenderState *state);
void FieldActor_UpdateModelMatrix(struct FieldActor *actor);

/* field_actor_states.c: the state machine. */
struct StateRequest;
void FieldActor_RunFrame(struct FieldActor *actor);
void FieldActor_SetMarkForState(struct FieldActor *actor, u32 state);
void FieldActor_SyncAimMode(struct FieldActor *actor, int state);
void FieldActor_ResetPitchForState(struct FieldActor *actor, int state, int force);
void FieldActor_TakeRequests(struct FieldActor *actor);
void FieldActor_TakeRemoteAction(struct FieldActor *actor);
void FieldActor_FollowRemoteState(struct FieldActor *actor);
void FieldActor_EnterState(struct FieldActor *actor, const struct StateRequest *request);
void FieldActor_ClearPitchForState(struct FieldActor *actor, int state);
void FieldActor_StopForState(struct FieldActor *actor, u32 state);
void FieldActor_ClearWork(struct FieldActor *actor);
void FieldActor_LeaveState(struct FieldActor *actor, int next);
u8 FieldActor_StateEndPriority(struct FieldActor *actor, int state);
u8 FieldActor_StatePriority(struct FieldActor *actor, int state);
int FieldActor_StatesFlaggedB48(struct FieldActor *actor, int state, int previous);
u8 FieldActor_StateFlagB48(struct FieldActor *actor, int state);

/* field_actor_states.c: states 0x84 to 0x86 and 0x90 to 0x92. */
void FieldActor_UpdateState92(struct FieldActor *actor);
void FieldActor_State92Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState92(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_UpdateState91(struct FieldActor *actor);
void FieldActor_ExitState91(void);
void FieldActor_State91Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState91(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_UpdateState90(struct FieldActor *actor);
void FieldActor_EndState90(struct FieldActor *actor);
void FieldActor_State90Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState90(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState90(struct FieldActor *actor, u16 value, int priority, int arg);
void FieldActor_UpdateState86(struct FieldActor *actor);
void FieldActor_EndState86(struct FieldActor *actor);
void FieldActor_State86Message(struct FieldActor *actor, u16 arg);
void FieldActor_EnterState86(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState86(struct FieldActor *actor, int priority, int arg);
void FieldActor_UpdateState85(struct FieldActor *actor);
void FieldActor_EndState85(struct FieldActor *actor);
void FieldActor_ShownItemPoint(Vec3 *point, struct FieldActor *actor, int frame);
void FieldActor_MoveShownItem(struct FieldActor *actor);
void FieldActor_State85Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState85(struct FieldActor *actor, const struct StateRequest *request, int previous);
void PackedItem_Get(const u8 *packed, u16 *item);
void PackedItem_Set(u8 *packed, u16 item);
int FieldActor_RequestState85(struct FieldActor *actor, const u16 *item, int priority, int arg);
void FieldActor_UpdateState84(struct FieldActor *actor);
void FieldActor_RunState84(struct FieldActor *actor);
void FieldActor_State84Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState84(struct FieldActor *actor, const struct StateRequest *request, int previous);

/* field_actor_states.c: states 0x83, 0x79, 0x77, 0x76, 0x70, 0x6f, 0x3f, 0x35 and 0x34. */
struct State6FWork;
struct State6FArgs;
int FieldActor_RequestState84(struct FieldActor *actor, u8 kind, int priority, int arg);
void FieldActor_UpdateState83(struct FieldActor *actor);
void FieldActor_EndState83(struct FieldActor *actor);
void FieldActor_RunState83(struct FieldActor *actor);
void FieldActor_State83Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState83(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState83(struct FieldActor *actor, int priority, int arg);
void FieldActor_UpdateState79(struct FieldActor *actor);
void FieldActor_RunState79(struct FieldActor *actor);
void FieldActor_State79Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState79(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState79(struct FieldActor *actor, int priority, int arg);
void FieldActor_UpdateState77(struct FieldActor *actor);
void FieldActor_EndState77(struct FieldActor *actor);
void FieldActor_TurnState77(struct FieldActor *actor);
void FieldActor_State77Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState77(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_GetSavedYaw77(const u8 *saved, u16 *yaw);
void FieldActor_SetSavedYaw77(u8 *saved, int yaw);
int FieldActor_RequestState77(struct FieldActor *actor, u16 yaw, int priority, int arg);
void FieldActor_UpdateState76(struct FieldActor *actor);
void FieldActor_RunState76(struct FieldActor *actor);
void FieldActor_State76Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState76(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_GetSaved76(const u8 *saved, u8 *mode, u8 *kind, u8 *slot);
void FieldActor_SetSaved76(u8 *saved, int mode, int kind, int slot);
void *FieldActor_RequestState76(struct FieldActor *actor, u8 mode, u8 kind, u8 slot, u32 priority, s16 arg);
void FieldActor_UpdateState70(struct FieldActor *actor);
void FieldActor_EndState70(struct FieldActor *actor);
void FieldActor_TurnState70(struct FieldActor *actor);
void FieldActor_State70Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState70(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_SetYaw70(u16 *target, int yaw);
int FieldActor_RequestState70(struct FieldActor *actor, int yaw, int priority, int arg);
void FieldActor_SetArgs70(u16 *payload, int yaw);
void FieldActor_UpdateState6F(struct FieldActor *actor);
void FieldActor_EndState6F(struct FieldActor *actor, int arrived);
void FieldActor_HeightState6F(struct FieldActor *actor);
void FieldActor_AnimateState6F(struct FieldActor *actor);
int FieldActor_MoveState6F(struct FieldActor *actor);
void FieldActor_State6FMessage(struct FieldActor *actor, int arg);
void FieldActor_EnterState6F(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_SetWork6F(struct State6FWork *work, Vec3 point, int accel, int previous);
int FieldActor_RequestState6F(struct FieldActor *actor, const Vec3 *point, int accel, int priority, s16 arg);
void FieldActor_SetArgs6F(struct State6FArgs *args, Vec3 point, int accel);
void FieldActor_UpdateState3F(struct FieldActor *actor);
void FieldActor_RunState3F(struct FieldActor *actor);
void FieldActor_ExitState3F(struct FieldActor *actor);
void FieldActor_State3FMessage(struct FieldActor *actor, int arg);
void FieldActor_EnterState3F(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_GetSavedItem3F(const u8 *saved, u16 *item);
void FieldActor_SetSavedItem3F(u8 *saved, u16 item);
int FieldActor_RequestState3F(struct FieldActor *actor, u16 item, int priority, int arg);
void FieldActor_UpdateState35(struct FieldActor *actor);
void FieldActor_EndState35(struct FieldActor *actor);
void FieldActor_State35Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState35(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState35(struct FieldActor *actor, int priority, int arg);
void FieldActor_UpdateState34(struct FieldActor *actor);
void FieldActor_EndState34(struct FieldActor *actor);
void FieldActor_State34Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState34(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState34(struct FieldActor *actor, int priority, int arg);

/* field_actor_states.c: states 0x33 to 0x30. */
struct State30Args;
void FieldActor_UpdateState33(struct FieldActor *actor);
void FieldActor_EndState33(struct FieldActor *actor);
void FieldActor_State33Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState33(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState33(struct FieldActor *actor, int priority, int arg);
void FieldActor_UpdateState32(struct FieldActor *actor);
void FieldActor_EndState32(struct FieldActor *actor);
void FieldActor_AnimateState32(struct FieldActor *actor);
void FieldActor_MoveState32(struct FieldActor *actor);
void FieldActor_State32Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState32(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_ClearSpeed32(fx32 *speed);
int FieldActor_RequestState32(struct FieldActor *actor, int priority, int arg);
void FieldActor_UpdateState31(struct FieldActor *actor);
int FieldActor_EndState31(struct FieldActor *actor);
void FieldActor_State31Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState31(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState31(struct FieldActor *actor, int priority, int arg);
void FieldActor_UpdateState30(struct FieldActor *actor);
void FieldActor_EndState30(struct FieldActor *actor);
void FieldActor_RunState30(struct FieldActor *actor);
void FieldActor_State30Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState30(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState30(struct FieldActor *actor, const u16 *item, int a, int b, int c, int d, int priority, s16 arg);
void FieldActor_SetArgs30(struct State30Args *args, int a, u8 b, int c, int d);

/* field_actor_states.c: states 0x1b to 0x19. */
struct State1AArgs;
void FieldActor_UpdateState1B(struct FieldActor *actor);
void FieldActor_ScaleState1B(struct FieldActor *actor);
void FieldActor_State1BMessage(struct FieldActor *actor, int arg);
void FieldActor_EnterState1B(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_GetSaved1B(const u8 *saved, u32 *tile, u8 *flag);
void FieldActor_SetSaved1B(u8 *saved, const u32 *tile, u8 flag);
int FieldActor_RequestState1B(struct FieldActor *actor, const int *tile, u32 flag, int priority, s16 arg);
void FieldActor_SetArgs1B(u8 *payload, const u32 *tile, u8 flag);
void FieldActor_UpdateState1A(struct FieldActor *actor);
void FieldActor_FinishState1A(struct FieldActor *actor);
void FieldActor_EndState1A(struct FieldActor *actor);
void FieldActor_RunState1A(struct FieldActor *actor);
void FieldActor_KeepPoseState1A(struct FieldActor *actor);
void FieldActor_ExitState1A(struct FieldActor *actor);
void FieldActor_State1AMessage(struct FieldActor *actor, u32 arg);
void FieldActor_EnterState1A(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_GetSaved1A(const u8 *saved, u32 *tile, u16 *item, u8 *flag);
void FieldActor_SetSaved1A(u8 *saved, const u32 *tile, u32 item, u8 flag);
int FieldActor_RequestState1A(struct FieldActor *actor, const int *tile, int item, int flag, int priority, s16 arg);
int FieldActor_RequestState1AFromMap(struct FieldActor *actor, const int *tile, int flag, int priority, s16 arg);
void FieldActor_SetArgs1A(struct State1AArgs *args, const u32 *tile, u16 item, u8 flag);
void FieldActor_UpdateState19(struct FieldActor *actor);
void FieldActor_EndState19(struct FieldActor *actor);
void FieldActor_RunState19(struct FieldActor *actor, u8 *step, int flag);
void FieldActor_ScaleState19(struct FieldActor *actor);
void FieldActor_SoundState19(struct FieldActor *actor);
void FieldActor_ExitState19(struct FieldActor *actor);
void FieldActor_State19Message(struct FieldActor *actor, s16 arg);
void FieldActor_EnterState19(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_GetSaved19(const u8 *saved, u32 *tile, s8 *number, u16 *item, u8 *flag);
void FieldActor_SetSaved19(u8 *saved, const u32 *tile, u8 number, int item, u8 flag);
int FieldActor_RequestState19(struct FieldActor *actor, const int *tile, int item, int flag, int priority, s16 arg);

#endif
