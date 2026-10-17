/* Overlay 84: the turtle of the message files "sp_npc_turtle4" and "sp_npc_turtle" (model
 * npc_sp/model/ttl, person code 0xd012) at event 0x17: on the Saturdays of August, from 19:00
 * to 24:00 (data_020dac08). Main's spawner (spawner.h) asks for his object profile 0x5a while
 * the event is on (data_020d06a4), and its spawn table (data_020e1d8c) gives the profile the
 * code 0xd012 and overlay 84, loaded with him; the profile's record is at 0x022793e0, which
 * main's profile table data_020e3134 points to. Overlays 85 and 86 are the same turtle at other
 * events.
 *
 * He is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x022794ac, 0x718 bytes, made by Turtle4_Create, with his talk scene (Turtle4Talk,
 * turtle4_talk.h) at 0x658. On his start he notes which Saturday of the month it is
 * (Turtle4.week). In his talks he hands out the items 0x137e and 0x137f and writes the player
 * a fortune letter.
 *
 * His states (Turtle4.state), each an entry and an update function (C++ members taking him)
 * from the table data_ov084_022795a0 (filled at start-up by __sinit_ov084_0227931c), set by
 * Turtle4_SetState:
 *   0  stand:  he takes motion 0 (priority 1);
 *   1  talk:   he turns to the talk's partner and talks; once his action is idle the event
 *              ends: state 2;
 *   2  talked: nothing. */
#ifndef CLEAN_OV084_TURTLE4_H
#define CLEAN_OV084_TURTLE4_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct Turtle4;

/* His talk scene (0xbc bytes, a scene of main's class 0x020d9ff8 with vtable 0x0227941c). Its
 * receiver's message (byte 0x1e of the scene) is the line shown. */
typedef struct Turtle4Talk {
    SceneBase base;        /* 0x00 */
    u8 unk_80[0x30];       /* 0x80: the scene's commands (scene_command.h) */
    struct Turtle4 *owner; /* 0xb0 */
    s32 item_slot;         /* 0xb4: the pockets' slot of item 0x37e0, or TURTLE4_TALK_SLOT_* */
    u16 unk_b8;            /* 0xb8: 0xfff1 when made, not read here */
    u8 unk_ba[2];          /* 0xba */
} Turtle4Talk;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define TURTLE4_BASE_SIZE 0x654

typedef struct Turtle4 {
    u8 base[TURTLE4_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                  /* 0x654: enum Turtle4State */
    Turtle4Talk talk;           /* 0x658 */
    u8 week;                    /* 0x714: today's week of the month, 1 for days 1-7 to 5 */
    u8 unk_715[3];              /* 0x715 */
} Turtle4;

enum Turtle4State { TURTLE4_STAND = 0, TURTLE4_TALKING = 1, TURTLE4_TALKED = 2, TURTLE4_STATES = 3 };

/* A state's functions in data_ov084_022795a0. */
typedef struct Turtle4Step {
    MemberPointer enter;  /* 0x00: int (him); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (him) */
} Turtle4Step;

Turtle4 *Turtle4_Destroy(Turtle4 *turtle);
void *Turtle4_Delete(void *turtle);
void Turtle4_OnEvent(Turtle4 *turtle, int code);
int Turtle4_MayAct(Turtle4 *turtle);
int Turtle4_UpdateTalked(void);
int Turtle4_UpdateTalk(Turtle4 *turtle);
int Turtle4_EnterTalk(Turtle4 *turtle);
int Turtle4_UpdateStand(void);
int Turtle4_EnterStand(Turtle4 *turtle);
void Turtle4_SetState(Turtle4 *turtle, int state);
int Turtle4_Update(Turtle4 *turtle);
int Turtle4_ModelName(void);
int Turtle4_TextureName(void);
int Turtle4_Start(Turtle4 *turtle);
int Turtle4_Init(Turtle4 *turtle);
void *Turtle4_Create(void);

#endif
