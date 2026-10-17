/* The gatekeeper of overlay 48: the special character of the message archive
 * "sp_npc_gatekeeper" with the model npc_sp/model/plc, object profile 0x72 (its record at
 * data_ov048_02264174, the main module's profile table data_020e3134 points to it). A scene
 * object of class 0x020da088 (special_scene_object.h) with vtable 0x02264298, 0xe74 bytes.
 *
 * It talks through its own scene (GatekeeperTalk, gatekeeper_talk.h, at 0x658), which opens
 * the gate to other towns: by the local wireless library or the Nintendo Wi-Fi Connection.
 * Its own states are set by func_ov048_022635f4 (GATEKEEPER_STATE_*). */
#ifndef CLEAN_OV048_GATEKEEPER_H
#define CLEAN_OV048_GATEKEEPER_H

#include "gatekeeper_talk.h"
#include "types.h"

/* States of its own machine that this code asks for (func_ov048_022635f4). */
#define GATEKEEPER_STATE_1 1
#define GATEKEEPER_STATE_2 2
#define GATEKEEPER_STATE_4 4
#define GATEKEEPER_STATE_C 0xc
#define GATEKEEPER_STATE_D 0xd
#define GATEKEEPER_STATE_E 0xe
#define GATEKEEPER_STATE_F 0xf
#define GATEKEEPER_STATE_10 0x10
#define GATEKEEPER_STATE_11 0x11

typedef struct Gatekeeper {
    u8 unk_000[0x560];   /* the scene object (special_scene_object.h, scene_object.h) */
    u8 participant;      /* 0x560: whom the last event of code 0 or 3 was for */
    u8 unk_561[2];       /* 0x561 */
    u8 local;            /* 0x563: not shared with a session */
    u8 unk_564[0xf4];    /* 0x564 */
    GatekeeperTalk talk; /* 0x658 */
    u8 unk_e6c[2];       /* 0xe6c */
    u16 countdown;       /* 0xe6e: the frames a wait of the talk has left */
    u8 unk_e70;          /* 0xe70 */
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

#endif
