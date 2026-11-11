/* Overlay 86: the turtle as the host of the new year's countdown (his lines in "sp_npc_turtle6"
 * speak of it), with the message files "sp_npc_turtle6" and "sp_npc_turtle" (model
 * npc_sp/model/ttl, person code 0xd012) at the turn of the year: event 0x1a (December 31 from
 * 6:00) and event 0x1b (all of January 1) (data_020dac08). Main's spawner (spawner.h) asks for
 * his object profile 0x5c while either is on (data_020d06a4), and its spawn table
 * (data_020e1d8c) gives the profile the code 0xd012 and overlay 86, loaded with him; the
 * profile's record is at 0x022792c0, which main's profile table data_020e3134 points to.
 * Overlays 84 and 85 are the same turtle at other events.
 *
 * He is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x0227938c, 0x710 bytes, made by TurtleCountdown_Create, with his talk scene (TurtleCountdownTalk,
 * turtle_countdown_talk.h) at 0x658. In his talks he counts down to the new year, hands out the party
 * popper 0x137d and on January 1 writes the player a fortune letter.
 *
 * His states (TurtleCountdown.state), each an entry and an update function (C++ members taking him)
 * from the table data_ov086_02279480 (filled at start-up by __sinit_ov086_022791f0), set by
 * TurtleCountdown_SetState:
 *   0  stand:  he takes motion 0 (priority 1);
 *   1  talk:   he turns to the talk's partner and talks; once his action is idle the event
 *              ends: state 2;
 *   2  talked: nothing. */
#ifndef CLEAN_OV086_TURTLE_COUNTDOWN_H
#define CLEAN_OV086_TURTLE_COUNTDOWN_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct TurtleCountdown;

/* His talk scene (0xb8 bytes, a scene of main's class 0x020d9ff8 with vtable 0x022792fc). Its
 * receiver's message (byte 0x1e of the scene) is the line shown. */
typedef struct TurtleCountdownTalk {
    SceneBase base;                /* 0x00 */
    u8 commands[0x30];             /* 0x80: the scene's commands (scene_command.h) */
    struct TurtleCountdown *owner; /* 0xb0 */
    s32 item_slot;                 /* 0xb4: the pockets' slot of item 0x37e0, or TURTLE_COUNTDOWN_TALK_SLOT_* */
} TurtleCountdownTalk;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define TURTLE_COUNTDOWN_BASE_SIZE 0x654

typedef struct TurtleCountdown {
    u8 base[TURTLE_COUNTDOWN_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                           /* 0x654: enum TurtleCountdownState */
    TurtleCountdownTalk talk;            /* 0x658 */
} TurtleCountdown;

enum TurtleCountdownState {
    TURTLE_COUNTDOWN_STAND = 0,
    TURTLE_COUNTDOWN_TALKING = 1,
    TURTLE_COUNTDOWN_TALKED = 2,
    TURTLE_COUNTDOWN_STATE_COUNT = 3
};

/* A state's functions in data_ov086_02279480. */
typedef struct TurtleCountdownStep {
    MemberPointer enter;  /* 0x00: int (him); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (him) */
} TurtleCountdownStep;

TurtleCountdown *TurtleCountdown_Destruct(TurtleCountdown *turtle);
void *TurtleCountdown_Delete(void *turtle);
void TurtleCountdown_OnEvent(TurtleCountdown *turtle, int code);
int TurtleCountdown_MayAct(TurtleCountdown *turtle);
int TurtleCountdown_UpdateTalked(void);
int TurtleCountdown_UpdateTalk(TurtleCountdown *turtle);
int TurtleCountdown_EnterTalk(TurtleCountdown *turtle);
int TurtleCountdown_UpdateStand(void);
int TurtleCountdown_EnterStand(TurtleCountdown *turtle);
void TurtleCountdown_SetState(TurtleCountdown *turtle, int state);
int TurtleCountdown_Update(TurtleCountdown *turtle);
int TurtleCountdown_ModelName(void);
int TurtleCountdown_TextureName(void);
int TurtleCountdown_Start(TurtleCountdown *turtle);
int TurtleCountdown_Init(TurtleCountdown *turtle);
void *TurtleCountdown_Create(void);

#endif
