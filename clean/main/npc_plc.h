/* The special character with the model npc_sp/model/plc (its record at data_020e82f8): a scene
 * object of class 0x020da088 (special_scene_object.h) with vtable 0x020e877c, 0x714 bytes, of
 * person 0xd000. Its talk scene (vtable 0x020e86ec, at 0x658) has a single line: message 0 of
 * the archive "test".
 *
 * Like the characters of missing_npc1.h and missing_npc2.h it lives in a state machine of C++
 * pointers to member functions (an entry and an update per state; the table data_021fbd90,
 * func_020c3dac sets a state):
 * - NPC_PLC_IDLE: standing;
 * - NPC_PLC_TALK: it turns to the object its talk names and talks; once its action ends, its
 *   event is finished and it takes NPC_PLC_TALKED;
 * - NPC_PLC_TALKED: nothing;
 * - NPC_PLC_TURN_BACK: it turns back to the angle it started at (home_angle), then
 *   NPC_PLC_IDLE.
 * Told of event 0 (its vtable slot 0x4c) it talks; told its act ended (code 8) it turns back.
 * The player may act on it within 0x2000 of it. */
#ifndef CLEAN_MAIN_NPC_PLC_H
#define CLEAN_MAIN_NPC_PLC_H

#include "autoload_2/vector.h"
#include "scene_base.h"
#include "types.h"

/* The states. */
#define NPC_PLC_IDLE 0
#define NPC_PLC_TALK 1
#define NPC_PLC_TALKED 2
#define NPC_PLC_TURN_BACK 3

struct NpcPlc;

/* Its talk scene (vtable 0x020e86ec): a scene base (scene_base.h). Its message and line
 * handlers act only while `lines` is 0 (NpcPlcTalk_OnMessage, NpcPlcTalk_Line). */
typedef struct NpcPlcTalk {
    SceneBase scene;      /* 0x00 */
    u8 unk_80[0x30];      /* 0x80 */
    s32 lines;            /* 0xb0: 0 while its line is given, 1 after NpcPlcTalk_SetOwner */
    struct NpcPlc *owner; /* 0xb4 */
} NpcPlcTalk;

/* What its talk's slot 0x78 gives: the archive's name and the line to say. */
typedef struct NpcPlcLine {
    u32 name;   /* 0x00: "test" */
    u8 message; /* 0x04 */
    u8 unk_05[3];
} NpcPlcLine;

typedef struct NpcPlc {
    u8 unk_000[0x5c];  /* the scene object (special_scene_object.h, scene_object.h) */
    Vec3 position;     /* 0x05c */
    u8 unk_068[0x26];  /* 0x068 */
    s16 angle;         /* 0x08e: where it faces */
    u8 unk_090[0x5c4]; /* 0x090 */
    s32 state;         /* 0x654: NPC_PLC_* */
    NpcPlcTalk talk;   /* 0x658 */
    s16 home_angle;    /* 0x710: where it faced when it started */
    u8 unk_712[2];     /* 0x712 */
} NpcPlc;

/* The object's vtable slots. */
NpcPlc *NpcPlc_Destruct(NpcPlc *self);
NpcPlc *NpcPlc_DestructDelete(NpcPlc *self);
int NpcPlc_MayAct(NpcPlc *self, u8 *other);
void NpcPlc_OnEvent(NpcPlc *self, int code);

/* The states' entries and updates. */
int NpcPlc_UpdateIdle(void);
int NpcPlc_EnterTalk(NpcPlc *self);
int NpcPlc_UpdateTalk(NpcPlc *self);
int NpcPlc_UpdateTalked(void);
int NpcPlc_EnterTurnBack(NpcPlc *self);
int NpcPlc_UpdateTurnBack(NpcPlc *self);

/* Its talk scene. */
NpcPlcTalk *NpcPlcTalk_Construct(NpcPlcTalk *talk);
NpcPlcTalk *NpcPlcTalk_Destruct(NpcPlcTalk *talk);
NpcPlcTalk *NpcPlcTalk_DestructDelete(NpcPlcTalk *talk);
void NpcPlcTalk_SetOwner(NpcPlcTalk *talk, struct NpcPlc *owner);
void NpcPlcTalk_SetLines(NpcPlcTalk *talk, u32 lines);
void NpcPlcTalk_OnMessage(NpcPlcTalk *talk, void *message);
void NpcPlcTalk_OnMessage0(NpcPlcTalk *talk, void *message);
void NpcPlcTalk_Line(NpcPlcTalk *talk, NpcPlcLine *line);
void NpcPlcTalk_LineBySet(NpcPlcTalk *talk, NpcPlcLine *line);
void NpcPlcTalk_Line0(NpcPlcTalk *talk, NpcPlcLine *line);

#endif
