/* A special character indoors drawn with the model npc_sp/model/tti, without a talk scene of
 * its own: a special character's scene object (main's special_scene_object.h) of vtable
 * data_ov004_02254a38, 0x65c bytes (made by func_ov004_02225cd4). data_ov004_02258200 points
 * to it from its start (func_ov004_02225c68) until it may leave (func_ov004_02225c44).
 *
 * Its states (0x654), each an entry and an update function (C++ members taking it), from the
 * table data_ov004_02258204 (filled at start-up by __sinit_ov004_0224e968), set by
 * TtiNpc_SetState:
 *   0  stand:   it stands, its countdown (0x658) at 10; each time its animation reaches its
 *               last frame the countdown runs down, and once it is out with no job of the
 *               activities running (main's activity_job.h), state 1;
 *   1  gesture: it plays the animation 0x100, then 0x101, then stands again.
 * Overlay 54 asks whether it stands in its standard animation (TtiNpc_IsIdle). */
#ifndef CLEAN_OV004_TTI_NPC_H
#define CLEAN_OV004_TTI_NPC_H

#include "member_pointer.h"
#include "types.h"

enum TtiNpcState { TTI_NPC_STAND = 0, TTI_NPC_GESTURE = 1, TTI_NPC_STATES = 2 };

/* A state's functions in data_ov004_02258204. */
typedef struct TtiNpcStep {
    MemberPointer enter;  /* 0x00: int (npc); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (npc) */
} TtiNpcStep;

/* The size of the special character's scene object it derives from, as far as it is used. */
#define TTI_NPC_BASE_SIZE 0x654

typedef struct TtiNpc {
    u8 base[TTI_NPC_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                  /* 0x654: enum TtiNpcState */
    u8 countdown;               /* 0x658: the last frames of its animation before a gesture */
    u8 unk_659[3];              /* 0x659 */
} TtiNpc;

TtiNpc *TtiNpc_Destroy(TtiNpc *npc);
TtiNpc *TtiNpc_Delete(TtiNpc *npc);
int TtiNpc_IsIdle(void);
int TtiNpc_UpdateGesture(TtiNpc *npc);
int TtiNpc_EnterGesture(TtiNpc *npc);
int TtiNpc_UpdateStand(TtiNpc *npc);
int TtiNpc_EnterStand(TtiNpc *npc);
void TtiNpc_SetState(TtiNpc *npc, int state);
int TtiNpc_Update(TtiNpc *npc);
const char *TtiNpc_ModelName(void);
const char *TtiNpc_TextureName(void);
int TtiNpc_Leave(TtiNpc *npc);
int TtiNpc_Start(TtiNpc *npc);
int TtiNpc_Init(TtiNpc *npc);
TtiNpc *TtiNpc_Create(void);

#endif
