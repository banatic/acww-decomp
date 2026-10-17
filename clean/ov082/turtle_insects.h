/* Overlay 82: the turtle (message files "sp_npc_turtle2" and "sp_npc_turtle", the model
 * npc_sp/model/ttl) as the host of the insect contest. He is made by main's spawner
 * (spawner.h): while event 0x15 of its table data_020d06a4 is on, its check 3 asks for object
 * profile 0x58, whose spawn table entry (person code 0xd012) loads overlay 82 with him; his
 * profile record at 0x02279750 (profile 0x58) has TurtleInsects_Create as its create function.
 * Overlay 81 is the same person at the fishing tourney (turtle_fishing.h), whose code this
 * overlay's follows closely.
 *
 * He is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x0227981c, 0x728 bytes. On his start he plays animation 0x140, is held (flag 2 at 0x4e8)
 * and, unless the town's record of the day's winner (data_021f3aa4, main's event_winner.h)
 * is of today, makes one up: an insect drawn for this month with its random size, and a random
 * villager of the town as its catcher. The player may talk to him while his action is idle.
 * His talk scene (TurtleInsectsTalk, turtle_insects_talk.h) gives the contest's net, measures
 * the insect the player shows him and records the winner.
 *
 * His states (TurtleInsects.state), each an entry and an update function (C++ members taking
 * him) from the table data_ov082_02279914 (filled at start-up by __sinit_ov082_02279684), set
 * by TurtleInsects_SetState:
 *   0  stand:  he stands;
 *   1  talk:   he turns to the talk's partner and talks; once his action is idle his event is
 *              finished (state 2);
 *   2  talked: nothing. */
#ifndef CLEAN_OV082_TURTLE_INSECTS_H
#define CLEAN_OV082_TURTLE_INSECTS_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct TurtleInsects;

/* His talk scene (0xcc bytes): a scene of class 0x020d9ff8 (main's obj_020d9ff8.h) with vtable
 * 0x0227978c (turtle_insects_talk.h). */
typedef struct TurtleInsectsTalk {
    SceneBase base;              /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];             /* 0x80: the scene's commands (scene_command.h) */
    struct TurtleInsects *owner; /* 0xb0 */
    MemberPointer after_command; /* 0xb4: run once when a command of the scene ends */
    MemberPointer then_command;  /* 0xbc: becomes after_command once that has run */
    u16 item;                    /* 0xc4: the insect shown, or the prize; 0xfff1 for none */
    u8 was_holder;               /* 0xc6: the player held the record before beating it */
    u8 unk_c7;                   /* 0xc7 */
    s32 slot_37e0;               /* 0xc8: TURTLE_INSECTS_TALK_37E0_*, or the pocket of item
                                   * 0x37e0 */
} TurtleInsectsTalk;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define TURTLE_INSECTS_BASE_SIZE 0x654

typedef struct TurtleInsects {
    u8 base[TURTLE_INSECTS_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                         /* 0x654: enum TurtleInsectsState */
    TurtleInsectsTalk talk;            /* 0x658 */
    s32 size;                          /* 0x724: the size of the insect shown (fx32) */
} TurtleInsects;

enum TurtleInsectsState {
    TURTLE_INSECTS_STAND = 0,
    TURTLE_INSECTS_TALK = 1,
    TURTLE_INSECTS_TALKED = 2,
    TURTLE_INSECTS_STATES = 3
};

/* A state's functions in data_ov082_02279914. */
typedef struct TurtleInsectsStep {
    MemberPointer enter;  /* 0x00: int (him); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (him) */
} TurtleInsectsStep;

/* His object. */
TurtleInsects *TurtleInsects_Destruct(TurtleInsects *turtle);
TurtleInsects *TurtleInsects_DestructDelete(TurtleInsects *turtle);
void TurtleInsects_OnEvent(TurtleInsects *turtle, int code);
int TurtleInsects_AgreesToTalk(TurtleInsects *turtle);
void TurtleInsects_SetState(TurtleInsects *turtle, int state);
int TurtleInsects_Update(TurtleInsects *turtle);
int TurtleInsects_ModelName(void);
int TurtleInsects_TextureName(void);
int TurtleInsects_Start(TurtleInsects *turtle);
int TurtleInsects_Init(TurtleInsects *turtle);
void *TurtleInsects_Create(void);

/* His states. */
int TurtleInsects_EnterStand(TurtleInsects *turtle);
int TurtleInsects_UpdateStand(void);
int TurtleInsects_EnterTalk(TurtleInsects *turtle);
int TurtleInsects_UpdateTalk(TurtleInsects *turtle);
int TurtleInsects_UpdateTalked(void);

#endif
