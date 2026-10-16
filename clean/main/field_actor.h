/* The main program's part of the field actor's class (vtable 0x020d82b4, second vtable
 * 0x020d832c for its message receiver at 0xec; include/cpp/main/Obj_020d82b4.h): the
 * allocation and freeing of its objects, the vtable slots that only pass on to the real work,
 * the constructor and destructors (field_actor.c), the placing of its models for drawing
 * (field_actor_model.c), its control by the buttons and the pen (field_actor_control.c), and
 * its state machine with the states 0 to 5, 7, 0x10, 0x13 to 0x15, 0x18 to 0x1b, 0x30 to 0x35,
 * 0x3f, 0x6f, 0x70, 0x76, 0x77, 0x79, 0x83 to 0x86 and 0x90 to 0x92 and its queue of requests
 * (field_actor_states.c; field_actor_parts.h has what they share), its looks
 * (field_actor_looks.c), its animations (field_actor_anim.c), and its moves and contact bodies
 * (field_actor_motion.c). Overlay 3's part is in
 * ov003/field_actor.h.
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
void FieldActor_Create(void);
struct FieldActor *FieldActorReceiver_DestructDelete(void *receiver);
void FieldActorReceiver_TalkClosing(void *receiver);
void FieldActorReceiver_TalkChoice(void *receiver);
void FieldActorReceiver_TalkMessage(void *receiver);
void FieldActorReceiver_TalkIgnore(void *receiver);
void *FieldActorReceiver_Destruct(void *receiver);

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

/* field_actor_states.c: state 0x19's numbered request, states 0x18, 0x15, 0x14, 0x13, 0x10, 7
 * and 5. */
struct State19Args;
struct State18Args;
struct State18Saved;
struct State7Work;
struct State7Args;
struct FramesArgs;
int FieldActor_RequestState19Numbered(struct FieldActor *actor, const int *tile, int number, int flag, int priority, s16 arg);
void FieldActor_SetArgs19(struct State19Args *args, const u32 *tile, u32 number, u16 item, u8 flag);
void FieldActor_UpdateState18(struct FieldActor *actor);
void FieldActor_RunState18(struct FieldActor *actor);
void FieldActor_WaitState18(struct FieldActor *actor);
void FieldActor_State18Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState18(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_GetSaved18(const struct State18Saved *saved, u32 *tile, u32 *number);
void FieldActor_SetSaved18(struct State18Saved *saved, const u32 *tile, u32 number);
int FieldActor_RequestState18(struct FieldActor *actor, const int *tile, int number, int priority, s16 arg);
void FieldActor_SetArgs18(struct State18Args *args, const u32 *tile, u32 number);
void FieldActor_UpdateState15(struct FieldActor *actor);
int FieldActor_EndState15(struct FieldActor *actor);
void FieldActor_RunState15(struct FieldActor *actor);
void FieldActor_State15Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState15(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState15(struct FieldActor *actor, int priority, int arg);
void FieldActor_UpdateState14(struct FieldActor *actor);
void FieldActor_EndState14(struct FieldActor *actor);
void FieldActor_RunState14(struct FieldActor *actor);
void FieldActor_ExitState14(struct FieldActor *actor);
void FieldActor_State14Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState14(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_GetSaved14(const u8 *saved, u8 *kind, u8 *count);
void FieldActor_SetSaved14(u8 *saved, int kind, int count);
int FieldActor_RequestState14(struct FieldActor *actor, u8 kind, u8 count, int priority, s16 arg);
void FieldActor_UpdateState13(struct FieldActor *actor);
void FieldActor_EndState13(struct FieldActor *actor);
void FieldActor_State13Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState13(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState13(struct FieldActor *actor, int priority, int arg);
void FieldActor_UpdateState10(struct FieldActor *actor);
void FieldActor_CheckState10Target(struct FieldActor *actor);
void FieldActor_FaceState10Target(struct FieldActor *actor);
void FieldActor_RunState10(struct FieldActor *actor);
void FieldActor_State10Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState10(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState10(struct FieldActor *actor, int frames, int priority, int arg);
void FieldActor_SetArgs10(struct FramesArgs *args, int frames);
void FieldActor_UpdateState7(struct FieldActor *actor);
void FieldActor_EndState7(struct FieldActor *actor);
void FieldActor_TurnState7(struct FieldActor *actor);
void FieldActor_RunState7(struct FieldActor *actor);
void FieldActor_ApplyState7Kind2(struct FieldActor *actor);
void FieldActor_ApplyState7Kind1(struct FieldActor *actor);
void FieldActor_ApplyState7Kind0(struct FieldActor *actor);
void FieldActor_EffectsState7(struct FieldActor *actor);
void FieldActor_ExitState7(struct FieldActor *actor);
void FieldActor_State7Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState7(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_GetSaved7(const u8 *saved, u16 *value, u8 *kind, u8 *next);
void FieldActor_SetSaved7(u8 *saved, int value, u8 kind, u8 next);
void FieldActor_SetWork7(struct State7Work *work, s16 value, int kind, int next, s16 yaw);
int FieldActor_RequestState7(struct FieldActor *actor, int value, int kind, int next, int priority, s16 arg);
void FieldActor_SetArgs7(struct State7Args *args, int value, int kind, int next);
void FieldActor_UpdateState5(struct FieldActor *actor);
void FieldActor_State5Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState5(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState5(struct FieldActor *actor, int frames, int priority, int arg);
void FieldActor_SetArgs5(struct FramesArgs *args, int frames);

/* field_actor_states.c: states 4 to 0 (turning back, walking, standing, waiting, the start)
 * and the queue of state requests. */
struct State4Work;
struct State4Args;
struct State3Work;
struct State3Args;
struct State0Work;
struct State0Args;
void FieldActor_UpdateState4(struct FieldActor *actor);
void FieldActor_EndState4(struct FieldActor *actor);
void FieldActor_TurnState4(struct FieldActor *actor);
void FieldActor_ExitState4(struct FieldActor *actor);
void FieldActor_State4Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState4(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_SetWork4(struct State4Work *work, int yaw);
int FieldActor_RequestState4(struct FieldActor *actor, int yaw, int priority, int arg);
void FieldActor_SetArgs4(struct State4Args *args, int yaw);
void FieldActor_UpdateState3(struct FieldActor *actor);
void FieldActor_EndState3(struct FieldActor *actor, const u8 *stopped);
int FieldActor_RunState3(struct FieldActor *actor, const s16 *heading);
void FieldActor_LeanState3(struct FieldActor *actor);
void FieldActor_MoveState3(struct FieldActor *actor);
int FieldActor_FollowState3(struct FieldActor *actor);
void FieldActor_SteerState3(struct FieldActor *actor);
void FieldActor_State3Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState3(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_ClearWork3(struct State3Work *work);
int FieldActor_RequestState3(struct FieldActor *actor, int quick_start, int priority, int arg);
void FieldActor_SetArgs3(struct State3Args *args, int quick_start);
void FieldActor_UpdateState2(struct FieldActor *actor);
void FieldActor_EndState2(struct FieldActor *actor, const u8 *moved);
void FieldActor_RunState2(struct FieldActor *actor);
int FieldActor_FollowState2(struct FieldActor *actor);
void FieldActor_ExitState2(struct FieldActor *actor);
void FieldActor_State2Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState2(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState2(struct FieldActor *actor, int frames, int priority, int arg);
void FieldActor_SetArgs2(struct FramesArgs *args, int frames);
void FieldActor_UpdateState1(struct FieldActor *actor);
void FieldActor_ExitState1(struct FieldActor *actor);
void FieldActor_State1Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState1(struct FieldActor *actor, const struct StateRequest *request, int previous);
int FieldActor_RequestState1(struct FieldActor *actor, int priority, int arg);
void FieldActor_UpdateState0(struct FieldActor *actor);
void FieldActor_StartState0(struct FieldActor *actor, const int *prepared);
int FieldActor_PrepareState0(struct FieldActor *actor);
void FieldActor_ExitState0(struct FieldActor *actor, int next);
void FieldActor_State0Message(struct FieldActor *actor, int arg);
void FieldActor_EnterState0(struct FieldActor *actor, const struct StateRequest *request, int previous);
void FieldActor_SetWork0(struct State0Work *work, int start_state);
int FieldActor_RequestState0(struct FieldActor *actor, int start_state, int priority, int arg);
void FieldActor_SetArgs0(struct State0Args *args, int start_state);
int FieldActor_QueuePriorityAbove(struct FieldActor *actor);
int FieldActor_QueuePriority(struct FieldActor *actor);
void FieldActor_ClearQueue(struct FieldActor *actor);
struct StateRequest *FieldActor_QueueEntry(struct FieldActor *actor, int index);
int FieldActor_QueueRequest(struct FieldActor *actor, const struct StateRequest *request);

/* field_actor_control.c: the control of this console's actor. */
void FieldActor_ReadControl(struct FieldActor *actor);
u32 FieldActor_Push(struct FieldActor *actor);
s16 FieldActor_PushAngle(struct FieldActor *actor);
s16 FieldActor_PushYaw(struct FieldActor *actor);
int FieldActor_PushQuadrant(struct FieldActor *actor);
int FieldActor_PushSide(struct FieldActor *actor);
u8 FieldActor_Act(struct FieldActor *actor);

/* field_actor.c: the set-up once the actor is made. */
int FieldActor_Init(struct FieldActor *actor);
void FieldActor_SetupPartC(struct FieldActor *actor);
void FieldActor_SetupPartB(struct FieldActor *actor);
void FieldActor_SetupLooks(struct FieldActor *actor);

/* field_actor_support.c: the state requests, the message receiver's hooks, the flags, sounds and
 * footsteps, turning and easing, following another console's actor, the sun level's messages
 * and date, the targets on the map, the steps of speeds, angles and values towards a target,
 * and the object under the actor. */
struct DateTime;
void StateRequest_Set(struct StateRequest *request, int state, int priority, int arg);
void StateRequest_DestructPart(void);
void StateRequest_ConstructPart(void);
int StateRequest_Destruct(struct StateRequest *request);
u32 StateRequest_Construct(struct StateRequest *request);
int FieldActor_ShouldWalkToward(struct FieldActor *actor, int dx, int dz, int distance2, s16 yaw, s16 *direction);
int FieldActor_ReportedPosition(struct FieldActor *actor, u8 *scene, int *x, int *z, s16 *yaw);
u8 FieldActor_StateGroup(struct FieldActor *actor, int state);
void FieldActor_TalkClosing(struct FieldActor *actor);
void FieldActor_TalkChoice(struct FieldActor *actor);
void FieldActor_TalkMessage(struct FieldActor *actor);
void FieldActor_TalkIgnore(struct FieldActor *actor);
int FieldActor_AnyPlayerUnreported(struct FieldActor *actor);
int FieldActor_LinkedNotPlayer0(struct FieldActor *actor);
void FieldActor_RebuildPose(struct FieldActor *actor);
void FieldActor_PoseHeldTool(struct FieldActor *actor);
void FieldActor_RunChecksAside(struct FieldActor *actor);
int FieldActor_StateFlagA20(struct FieldActor *actor, int state);
void FieldActor_TurnHeadBack(struct FieldActor *actor);
void FieldActor_SendSunLevel(struct FieldActor *actor);
void FieldActor_SendNoItem(struct FieldActor *actor);
void FieldActor_SendItem(struct FieldActor *actor, int kind, int item);
int FieldActor_JointBPoint(struct FieldActor *actor, Vec3 *out);
void FieldActor_TakeAimMode(struct FieldActor *actor);
void FieldActor_ClearFlag(struct FieldActor *actor, int bit);
u32 *FieldActor_SetFlag(struct FieldActor *actor, int bit);
int FieldActor_TestFlag(struct FieldActor *actor, int bit);
void FieldActor_PlaySoundAt(struct FieldActor *actor, int number, const Vec3 *at);
int FieldActor_PlaySound(struct FieldActor *actor, int number);
void FieldActor_NudgeByPlayer(struct FieldActor *actor);
void FieldActor_NudgeOne(struct FieldActor *actor);
int FieldActor_FollowReportedTo(struct FieldActor *actor, const Vec3 *point);
int FieldActor_FollowReportedToTile(struct FieldActor *actor, const int *tile);
int FieldActor_FollowReported(struct FieldActor *actor);
int FieldActor_ReportedPlace(struct FieldActor *actor, Vec3 *point, s16 *yaw);
void FieldActor_EasePoint824(struct FieldActor *actor, fx32 scale);
void FieldActor_JointBOffsetPoint(Vec3 *out, struct FieldActor *actor, const fx32 *scale);
int FieldActor_CheckBatteryAndLid(struct FieldActor *actor);
void FieldActor_StoreSunDate(struct FieldActor *actor, int record, const u16 *date);
int FieldActor_CompareSunDate(struct FieldActor *actor, struct DateTime *now, struct DateTime *stored);
int FieldActor_SunDatePassed(struct FieldActor *actor);
void FieldActor_PlayFootstep(struct FieldActor *actor);
void FieldActor_Footfall(struct FieldActor *actor);
void FieldActor_PointAhead(Vec3 *out, struct FieldActor *actor, const Vec3 *from, const u16 *yaw, const fx32 *distance);
void FieldActor_PointAheadOfSelf(Vec3 *out, struct FieldActor *actor);
void FieldActor_TileAhead(Vec3 *out, struct FieldActor *actor);
int FieldActor_TurnToHalfTurn(struct FieldActor *actor, int rate);
int FieldActor_TurnToZero(struct FieldActor *actor, int rate);
void FieldActor_TurnTowards(struct FieldActor *actor, int yaw);
void FieldActor_EaseToXZ(struct FieldActor *actor, int x, int z);
void FieldActor_EaseToPose(struct FieldActor *actor, int x, int z, int yaw);
void FieldActor_MoveToPose(struct FieldActor *actor, int x, int z, int yaw);
int FieldActor_HeldTool(struct FieldActor *actor);
int FieldActor_HeldToolNumber(struct FieldActor *actor);
int FieldActor_ActOnTarget(struct FieldActor *actor, const Vec3 *point, int overlay4);
int FieldActor_FindMapTarget(struct FieldActor *actor, const int *tile, int a, int b);
int FieldActor_PollTarget(struct FieldActor *actor);
void FieldActor_PollRequest810(struct FieldActor *actor);
int FieldActor_FindTarget(struct FieldActor *actor, const Vec3 *point, int mode, int tool);
int FieldActor_TargetKind(struct FieldActor *actor);
int FieldActor_SlowGently(int value, int floor);
int FieldActor_Slow(int value, int floor);
int FieldActor_StepDown(int value, int floor, int step);
int FieldActor_SpeedUp(int value, int ceiling);
int FieldActor_TurnAngleSlowly(s16 *angle, int target);
int FieldActor_TurnAngleStep(s16 *angle, int target);
int FieldActor_TurnAngle(s16 *angle, int target, int rate, int max_step, int min_step);
void FieldActor_EaseValue(fx32 *value, int target);
void FieldActor_EaseValueBy(fx32 *value, int target, fx32 rate, int max_step, int min_step);
int FieldActor_NoteObjectUnderfoot(int player);

/* field_actor_looks.c: the looks, from the player's record: the palettes, the clothes, the
 * head (part B), part C, and the sun level. */
void FieldActor_CopyPalette(struct FieldActor *actor, int from, int to, const void *from_name, const void *to_name);
void FieldActor_CopyTexture(struct FieldActor *actor, int from, int to, const void *from_name, const void *to_name);
int FieldActor_RequestHead(struct FieldActor *actor, const u16 *item, u8 kind, u8 hair_color, u8 with_face);
void FieldActor_PollHead(struct FieldActor *actor);
void FieldActor_ApplyHead(struct FieldActor *actor);
int FieldActor_RequestPartC(struct FieldActor *actor, const u16 *item);
void FieldActor_PollPartC(struct FieldActor *actor);
void FieldActor_ApplyPartC(struct FieldActor *actor);
int FieldActor_BindCloth(struct FieldActor *actor);
void FieldActor_SetCloth(struct FieldActor *actor, u16 *item);
void FieldActor_SetPalettes(struct FieldActor *actor, int hair_color, int sun_level);
void FieldActor_RecordHeldItem(u16 *item, struct FieldActor *actor);
int FieldActor_RecordFace(struct FieldActor *actor);
int FieldActor_RecordFlag0(struct FieldActor *actor);
void FieldActor_RecordPartCItem(u16 *item, struct FieldActor *actor);
u8 FieldActor_SunLevel(struct FieldActor *actor, int store);
unsigned int FieldActor_RecordSunLevel(struct FieldActor *actor);
unsigned int FieldActor_RecordHairColor(struct FieldActor *actor);
unsigned int FieldActor_RecordHeadKind(struct FieldActor *actor);
void FieldActor_RecordHeadItem(u16 *item, struct FieldActor *actor);
void FieldActor_RecordCloth(u16 *item, struct FieldActor *actor);
int FieldActor_RecordFlag249A(struct FieldActor *actor);
u8 *FieldActor_Record(struct FieldActor *actor);

/* field_actor_anim.c: the body's animations, the held item's and the face's. */
void FieldActor_PlayHeldAnimation(struct FieldActor *actor, u16 *item, int animation, int frames);
void FieldActor_AnimateHeldItem(struct FieldActor *actor, int animation, int frames);
void FieldActor_RestartAnimation(struct FieldActor *actor);
void FieldActor_PlayAnimationOnce(struct FieldActor *actor, int animation, int blend, u16 held_blend);
void FieldActor_SwitchAnimation(struct FieldActor *actor, int animation, int blend, int held_blend);
void FieldActor_PlayAnimationLoop(struct FieldActor *actor, int animation, int blend, int held_blend);
void FieldActor_PlayAnimation(struct FieldActor *actor, int animation, int blend, u8 flags, int speed, u16 start,
                              u16 held_blend, int resource);
unsigned short FieldActor_AnimationResource(struct FieldActor *actor, const unsigned int *animation);
void FieldActor_UpdateBody(struct FieldActor *actor);
void FieldActor_PlayFaceAnimB(struct FieldActor *actor, const int *number, const u8 *flags);
void FieldActor_PlayFaceAnimA(struct FieldActor *actor, const int *number, const u8 *flags);
void FieldActor_MatchFaceAnimB(struct FieldActor *actor, const int *animation, const u8 *flags);
void FieldActor_MatchFaceAnimA(struct FieldActor *actor, const int *animation, const u8 *flags);
void FieldActor_BindFaceAnims(struct FieldActor *actor);
void FieldActor_StepFaceAnimB(struct FieldActor *actor);
void FieldActor_StepFaceAnimA(struct FieldActor *actor);
void FieldActor_StepFaceAnims(struct FieldActor *actor);

/* field_actor_motion.c: acting with the tool, speed, lean and yaw, moving, the shadow and the
 * contact bodies. */
int FieldActor_TryTargetInScene(struct FieldActor *actor, int tool);
int FieldActor_TryToolInScene(struct FieldActor *actor);
int FieldActor_InToolReach(struct FieldActor *actor, const Vec3 *point, int tool);
int FieldActor_TryAct(struct FieldActor *actor);
int FieldActor_WalkSpeed(struct FieldActor *actor);
void FieldActor_SetSpeed(struct FieldActor *actor, const int *speed);
void FieldActor_LeanTowards(struct FieldActor *actor, int target);
void FieldActor_SetLean(struct FieldActor *actor, u16 lean);
void FieldActor_SetYaw(struct FieldActor *actor, const s16 *yaw);
int FieldActor_StepTowardReported(struct FieldActor *actor);
int FieldActor_MoveFree(struct FieldActor *actor);
int FieldActor_MoveWithCollision(struct FieldActor *actor);
int FieldActor_PlaceShadow(struct FieldActor *actor);
int FieldActor_ContactFlags(struct FieldActor *actor, const int *state);
void FieldActor_SetContactAt(struct FieldActor *actor, const Vec3 *point, const int *state);
void FieldActor_SetContact(struct FieldActor *actor, const int *state);
void FieldActor_SetContactOnGround(struct FieldActor *actor, const int *state);
void FieldActor_EnterContact(struct FieldActor *actor);
void FieldActor_EnterContacts(struct FieldActor *actor, const Vec3 *point);
void FieldActor_SetContactBSized(struct FieldActor *actor, const Vec3 *point, int size, int height);
void FieldActor_SetContactB(struct FieldActor *actor, const Vec3 *point);

#endif
