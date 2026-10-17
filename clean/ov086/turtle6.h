/* Overlay 86: the turtle of the message files "sp_npc_turtle6" and "sp_npc_turtle" (model
 * npc_sp/model/ttl, person code 0xd012) at the turn of the year: event 0x1a (December 31 from
 * 6:00) and event 0x1b (all of January 1) (data_020dac08). Main's spawner (spawner.h) asks for
 * his object profile 0x5c while either is on (data_020d06a4), and its spawn table
 * (data_020e1d8c) gives the profile the code 0xd012 and overlay 86, loaded with him; the
 * profile's record is at 0x022792c0, which main's profile table data_020e3134 points to.
 * Overlays 84 and 85 are the same turtle at other events.
 *
 * He is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x0227938c, 0x710 bytes, made by Turtle6_Create, with his talk scene (Turtle6Talk,
 * turtle6_talk.h) at 0x658. In his talks he counts down to the new year, hands out the item
 * 0x137d and on January 1 writes the player a fortune letter.
 *
 * His states (Turtle6.state), each an entry and an update function (C++ members taking him)
 * from the table data_ov086_02279480 (filled at start-up by __sinit_ov086_022791f0), set by
 * Turtle6_SetState:
 *   0  stand:  he takes motion 0 (priority 1);
 *   1  talk:   he turns to the talk's partner and talks; once his action is idle the event
 *              ends: state 2;
 *   2  talked: nothing. */
#ifndef CLEAN_OV086_TURTLE6_H
#define CLEAN_OV086_TURTLE6_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct Turtle6;

/* His talk scene (0xb8 bytes, a scene of main's class 0x020d9ff8 with vtable 0x022792fc). Its
 * receiver's message (byte 0x1e of the scene) is the line shown. */
typedef struct Turtle6Talk {
    SceneBase base;        /* 0x00 */
    u8 unk_80[0x30];       /* 0x80: the scene's commands (scene_command.h) */
    struct Turtle6 *owner; /* 0xb0 */
    s32 item_slot;         /* 0xb4: the pockets' slot of item 0x37e0, or TURTLE6_TALK_SLOT_* */
} Turtle6Talk;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define TURTLE6_BASE_SIZE 0x654

typedef struct Turtle6 {
    u8 base[TURTLE6_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                  /* 0x654: enum Turtle6State */
    Turtle6Talk talk;           /* 0x658 */
} Turtle6;

enum Turtle6State { TURTLE6_STAND = 0, TURTLE6_TALKING = 1, TURTLE6_TALKED = 2, TURTLE6_STATES = 3 };

/* A state's functions in data_ov086_02279480. */
typedef struct Turtle6Step {
    MemberPointer enter;  /* 0x00: int (him); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (him) */
} Turtle6Step;

Turtle6 *Turtle6_Destroy(Turtle6 *turtle);
void *Turtle6_Delete(void *turtle);
void Turtle6_OnEvent(Turtle6 *turtle, int code);
int Turtle6_MayAct(Turtle6 *turtle);
int Turtle6_UpdateTalked(void);
int Turtle6_UpdateTalk(Turtle6 *turtle);
int Turtle6_EnterTalk(Turtle6 *turtle);
int Turtle6_UpdateStand(void);
int Turtle6_EnterStand(Turtle6 *turtle);
void Turtle6_SetState(Turtle6 *turtle, int state);
int Turtle6_Update(Turtle6 *turtle);
int Turtle6_ModelName(void);
int Turtle6_TextureName(void);
int Turtle6_Start(Turtle6 *turtle);
int Turtle6_Init(Turtle6 *turtle);
void *Turtle6_Create(void);

#endif
