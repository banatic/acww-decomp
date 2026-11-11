/* Overlay 84: the turtle as the host of the town's fireworks show (his lines in "sp_npc_turtle4"
 * speak of it), with the message files "sp_npc_turtle4" and "sp_npc_turtle" (model
 * npc_sp/model/ttl, person code 0xd012) at event 0x17: on the Saturdays of August, from 19:00
 * to 24:00 (data_020dac08). Main's spawner (spawner.h) asks for his object profile 0x5a while
 * the event is on (data_020d06a4), and its spawn table (data_020e1d8c) gives the profile the
 * code 0xd012 and overlay 84, loaded with him; the profile's record is at 0x022793e0, which
 * main's profile table data_020e3134 points to. Overlays 85 and 86 are the same turtle at other
 * events.
 *
 * He is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x022794ac, 0x718 bytes, made by TurtleFireworks_Create, with his talk scene (TurtleFireworksTalk,
 * turtle_fireworks_talk.h) at 0x658. On his start he notes which Saturday of the month it is
 * (TurtleFireworks.week). In his talks he hands out the fireworks 0x137e and 0x137f and writes the player
 * a fortune letter.
 *
 * His states (TurtleFireworks.state), each an entry and an update function (C++ members taking him)
 * from the table data_ov084_022795a0 (filled at start-up by __sinit_ov084_0227931c), set by
 * TurtleFireworks_SetState:
 *   0  stand:  he takes motion 0 (priority 1);
 *   1  talk:   he turns to the talk's partner and talks; once his action is idle the event
 *              ends: state 2;
 *   2  talked: nothing. */
#ifndef CLEAN_OV084_TURTLE_FIREWORKS_H
#define CLEAN_OV084_TURTLE_FIREWORKS_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct TurtleFireworks;

/* His talk scene (0xbc bytes, a scene of main's class 0x020d9ff8 with vtable 0x0227941c). Its
 * receiver's message (byte 0x1e of the scene) is the line shown. */
typedef struct TurtleFireworksTalk {
    SceneBase base;                /* 0x00 */
    u8 commands[0x30];             /* 0x80: the scene's commands (scene_command.h) */
    struct TurtleFireworks *owner; /* 0xb0 */
    s32 item_slot;                 /* 0xb4: the pockets' slot of item 0x37e0, or TURTLE_FIREWORKS_TALK_SLOT_* */
    u16 unk_b8;                    /* 0xb8: 0xfff1 when made, not read here */
    u8 unk_ba[2];                  /* 0xba */
} TurtleFireworksTalk;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define TURTLE_FIREWORKS_BASE_SIZE 0x654

typedef struct TurtleFireworks {
    u8 base[TURTLE_FIREWORKS_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                           /* 0x654: enum TurtleFireworksState */
    TurtleFireworksTalk talk;            /* 0x658 */
    u8 week;                             /* 0x714: today's week of the month, 1 for days 1-7 to 5 */
    u8 unk_715[3];                       /* 0x715 */
} TurtleFireworks;

enum TurtleFireworksState {
    TURTLE_FIREWORKS_STAND = 0,
    TURTLE_FIREWORKS_TALKING = 1,
    TURTLE_FIREWORKS_TALKED = 2,
    TURTLE_FIREWORKS_STATES = 3
};

/* A state's functions in data_ov084_022795a0. */
typedef struct TurtleFireworksStep {
    MemberPointer enter;  /* 0x00: int (him); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (him) */
} TurtleFireworksStep;

TurtleFireworks *TurtleFireworks_Destruct(TurtleFireworks *turtle);
void *TurtleFireworks_Delete(void *turtle);
void TurtleFireworks_OnEvent(TurtleFireworks *turtle, int code);
int TurtleFireworks_MayAct(TurtleFireworks *turtle);
int TurtleFireworks_UpdateTalked(void);
int TurtleFireworks_UpdateTalk(TurtleFireworks *turtle);
int TurtleFireworks_EnterTalk(TurtleFireworks *turtle);
int TurtleFireworks_UpdateStand(void);
int TurtleFireworks_EnterStand(TurtleFireworks *turtle);
void TurtleFireworks_SetState(TurtleFireworks *turtle, int state);
int TurtleFireworks_Update(TurtleFireworks *turtle);
int TurtleFireworks_ModelName(void);
int TurtleFireworks_TextureName(void);
int TurtleFireworks_Start(TurtleFireworks *turtle);
int TurtleFireworks_Init(TurtleFireworks *turtle);
void *TurtleFireworks_Create(void);

#endif
