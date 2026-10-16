/* The main program's part of the field actor's class (vtable 0x020d82b4, second vtable
 * 0x020d832c for its message receiver at 0xec; include/cpp/main/Obj_020d82b4.h): the
 * allocation and freeing of its objects, the vtable slots that only pass on to the real work,
 * the constructor and destructors (field_actor.c), the placing of its models for drawing
 * (field_actor_model.c), and its state machine with the states 0x84 to 0x86 and 0x90 to 0x92
 * (field_actor_states.c; field_actor_parts.h has what they share). Overlay 3's part is in
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

#endif
