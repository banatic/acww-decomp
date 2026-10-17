/* The gatekeeper of overlay 48: the special character of the message archive
 * "sp_npc_gatekeeper" with the model npc_sp/model/plc, object profile 0x72 (its record at
 * data_ov048_02264174, the main module's profile table data_020e3134 points to it). A scene
 * object of class 0x020da088 (special_scene_object.h) with vtable 0x02264298, 0xe74 bytes.
 *
 * It talks through its own scene (GatekeeperTalk, gatekeeper_talk.h, at 0x658), which opens
 * the gate to other towns: by the local wireless library or the Nintendo Wi-Fi Connection.
 * Its own states are set by Gatekeeper_SetState (GATEKEEPER_STATE_*, gatekeeper_states.h). */
#ifndef CLEAN_OV048_GATEKEEPER_H
#define CLEAN_OV048_GATEKEEPER_H

#include "gatekeeper_talk.h"
#include "types.h"

/* The states of its own machine (Gatekeeper_SetState, gatekeeper_states.h). */
#define GATEKEEPER_STATE_0 0
#define GATEKEEPER_STATE_1 1
#define GATEKEEPER_STATE_2 2
#define GATEKEEPER_STATE_3 3
#define GATEKEEPER_STATE_4 4
#define GATEKEEPER_STATE_5 5
#define GATEKEEPER_STATE_6 6
#define GATEKEEPER_STATE_7 7
#define GATEKEEPER_STATE_8 8
#define GATEKEEPER_STATE_9 9
#define GATEKEEPER_STATE_A 0xa
#define GATEKEEPER_STATE_B 0xb
#define GATEKEEPER_STATE_C 0xc
#define GATEKEEPER_STATE_D 0xd
#define GATEKEEPER_STATE_E 0xe
#define GATEKEEPER_STATE_F 0xf
#define GATEKEEPER_STATE_10 0x10
#define GATEKEEPER_STATE_11 0x11

typedef struct Gatekeeper {
    u8 unk_000[0x8e];    /* the scene object (special_scene_object.h, scene_object.h) */
    s16 angle;           /* 0x08e: where it faces */
    u8 unk_090[4];       /* 0x090 */
    s16 walk_angle;      /* 0x094: where it walks */
    u8 unk_096[0x452];   /* 0x096: the members from 0x2a0 (scene_object.h names them) */
    u32 flags;           /* 0x4e8: the scene object's flags (2: held, scene_action.h) */
    u8 unk_4ec[0x24];    /* 0x4ec */
    u8 solid;            /* 0x510: it collides and moves with its carrier */
    u8 unk_511[0x4f];    /* 0x511 */
    u8 participant;      /* 0x560: whom the last event of code 0 or 3 was for */
    u8 unk_561[2];       /* 0x561 */
    u8 local;            /* 0x563: not shared with a session */
    u8 unk_564[0xf0];    /* 0x564 */
    s32 state;           /* 0x654: GATEKEEPER_STATE_* (Gatekeeper_SetState) */
    GatekeeperTalk talk; /* 0x658 */
    s16 home_angle;      /* 0xe6c: the angle it faced when it started */
    u16 countdown;       /* 0xe6e: the frames a wait of the talk or of a state has left */
    u8 anim_countdown;   /* 0xe70: the frames before the other gatekeeper's animation 0x81 */
    u8 setup_step;       /* 0xe71: the step of its setup sequence */
    u8 unk_e72[2];       /* 0xe72 */
} Gatekeeper;

Gatekeeper *Gatekeeper_Destruct(Gatekeeper *self);
Gatekeeper *Gatekeeper_DestructDelete(Gatekeeper *self);
int Gatekeeper_IsWaitingInPoseBA(Gatekeeper *self);
int Gatekeeper_HasActionSound(Gatekeeper *self);
int Gatekeeper_CallPlayer(Gatekeeper *self);
void Gatekeeper_OnEvent(Gatekeeper *self, int code, int participant);
int Gatekeeper_Ask58(Gatekeeper *self);
int Gatekeeper_MayAct(Gatekeeper *self);
int Gatekeeper_CheckPairedTown(void);
unsigned int Gatekeeper_ModelName(void);
int Gatekeeper_TextureName(void);
int Gatekeeper_Leave(Gatekeeper *self);
int Gatekeeper_Start(Gatekeeper *self);
int Gatekeeper_Init(Gatekeeper *self);
Gatekeeper *Gatekeeper_Create(void);

/* Its states (gatekeeper_states.c). */
void Gatekeeper_SetState(Gatekeeper *self, int state);
int Gatekeeper_UpdateState(Gatekeeper *self);

#endif
