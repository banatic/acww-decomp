/* Overlay 87: the special character of the message file "sp_npc_acorn" with the model
 * npc_sp/model/dnk (person code 0xd01e), who takes the items 0x1542-0x1546 the player brings
 * (TownDay drops them beside the town's trees; the message file's name calls them acorns) for
 * points toward a table of rewards, and writes the player a fortune ("ev_fortune") once a day.
 * Main's spawn table (spawner.h, data_020e1d8c) makes the character as object profile 0x5f with
 * the code 0xd01e and loads overlay 87 with it; the profile's record is at 0x02279420, which
 * main's profile table data_020e3134 points to.
 *
 * It is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x022794ec, 0x70c bytes, made by AcornNpc_Create, with its talk scene (AcornNpcTalk,
 * acorn_npc_talk.h) at 0x658.
 *
 * Its states (AcornNpc.state), each an entry and an update function (C++ members taking it)
 * from the table data_ov087_022795c0 (filled at start-up by __sinit_ov087_02279354), set by
 * AcornNpc_SetState:
 *   0  stand:  it takes motion 0 (priority 1);
 *   1  talk:   it turns to the talk's partner and talks; once its action is idle the event
 *              ends: state 2;
 *   2  talked: nothing. */
#ifndef CLEAN_OV087_ACORN_NPC_H
#define CLEAN_OV087_ACORN_NPC_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct AcornNpc;

/* Its talk scene (0xb4 bytes, a scene of main's class 0x020d9ff8, vtable 0x0227945c). Its
 * receiver's message (byte 0x1e of the scene) is the line shown. */
typedef struct AcornNpcTalk {
    SceneBase base;         /* 0x00 */
    u8 unk_80[0x30];        /* 0x80: the scene's commands (scene_command.h) */
    struct AcornNpc *owner; /* 0xb0 */
} AcornNpcTalk;

/* The size of the special character's scene object it derives from, as far as it is used. */
#define ACORN_NPC_BASE_SIZE 0x654

typedef struct AcornNpc {
    u8 base[ACORN_NPC_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                    /* 0x654: enum AcornNpcState */
    AcornNpcTalk talk;            /* 0x658 */
} AcornNpc;

enum AcornNpcState { ACORN_NPC_STAND = 0, ACORN_NPC_TALKING = 1, ACORN_NPC_TALKED = 2, ACORN_NPC_STATES = 3 };

/* A state's functions in data_ov087_022795c0. */
typedef struct AcornNpcStep {
    MemberPointer enter;  /* 0x00: int (character); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (character) */
} AcornNpcStep;

AcornNpc *AcornNpc_Destroy(AcornNpc *npc);
AcornNpc *AcornNpc_Delete(AcornNpc *npc);
void AcornNpc_OnEvent(AcornNpc *npc, int code);
int AcornNpc_MayAct(AcornNpc *npc);
int AcornNpc_UpdateStand(void);
int AcornNpc_UpdateTalk(AcornNpc *npc);
int AcornNpc_EnterTalk(AcornNpc *npc);
int AcornNpc_UpdateTalked(void);
int AcornNpc_EnterStand(AcornNpc *npc);
void AcornNpc_SetState(AcornNpc *npc, int state);
int AcornNpc_Update(AcornNpc *npc);
int AcornNpc_ModelName(void);
int AcornNpc_TextureName(void);
int AcornNpc_Start(AcornNpc *npc);
int AcornNpc_Init(AcornNpc *npc);
void *AcornNpc_Create(void);

#endif
