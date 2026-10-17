/* Overlay 81: the turtle (message files "sp_npc_turtle1" and "sp_npc_turtle", the model
 * npc_sp/model/ttl) as the host of the fishing tourney. He is made by main's spawner
 * (spawner.h): while event 0x14 of its table data_020d06a4 is on, its check 3 asks for object
 * profile 0x57, whose spawn table entry (person code 0xd012) loads overlay 81 with him; his
 * profile record at 0x022796f0 (profile 0x57) has TurtleFishing_Create as its create function.
 * Overlays 80 and 82 to 86 load the same person for the town's other events.
 *
 * He is a scene object of class 0x020da088 (main's special_scene_object.h) with vtable
 * 0x022797bc, 0x728 bytes. On his start he plays animation 0x140, is held (flag 2 at 0x4e8)
 * and, unless the town's record of the day's winner (data_021f3aa4, main's event_winner.h)
 * already holds a fish, makes one up: a fish drawn for today and a random villager of the
 * town as its catcher. The player may talk to him while his action is idle. His talk scene
 * (TurtleFishingTalk, turtle_fishing_talk.h) gives the tourney's rod, weighs the fish the
 * player shows him and records the winner.
 *
 * His states (TurtleFishing.state), each an entry and an update function (C++ members taking
 * him) from the table data_ov081_022798b4 (filled at start-up by __sinit_ov081_02279620), set
 * by TurtleFishing_SetState:
 *   0  stand:  he stands;
 *   1  talk:   he turns to the talk's partner and talks; once his action is idle his event is
 *              finished (state 2);
 *   2  talked: nothing. */
#ifndef CLEAN_OV081_TURTLE_FISHING_H
#define CLEAN_OV081_TURTLE_FISHING_H

#include "main/scene_base.h"
#include "ov004/member_pointer.h"
#include "types.h"

struct TurtleFishing;

/* His talk scene (0xcc bytes): a scene of class 0x020d9ff8 (main's obj_020d9ff8.h) with vtable
 * 0x0227972c (turtle_fishing_talk.h). */
typedef struct TurtleFishingTalk {
    SceneBase base;              /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];             /* 0x80: the scene's commands (scene_command.h) */
    struct TurtleFishing *owner; /* 0xb0 */
    MemberPointer after_command; /* 0xb4: run once when a command of the scene ends */
    MemberPointer then_command;  /* 0xbc: becomes after_command once that has run */
    u16 item;                    /* 0xc4: the fish shown, or the prize; 0xfff1 for none */
    u8 was_holder;               /* 0xc6: the player held the record before beating it */
    u8 unk_c7;                   /* 0xc7 */
    s32 slot_37e0;               /* 0xc8: TURTLE_FISHING_TALK_37E0_*, or the pocket of item
                                   * 0x37e0 */
} TurtleFishingTalk;

/* The size of the special character's scene object he derives from, as far as it is used. */
#define TURTLE_FISHING_BASE_SIZE 0x654

typedef struct TurtleFishing {
    u8 base[TURTLE_FISHING_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                         /* 0x654: enum TurtleFishingState */
    TurtleFishingTalk talk;            /* 0x658 */
    s32 size;                          /* 0x724: the size of the fish shown (fx32) */
} TurtleFishing;

enum TurtleFishingState {
    TURTLE_FISHING_STAND = 0,
    TURTLE_FISHING_TALK = 1,
    TURTLE_FISHING_TALKED = 2,
    TURTLE_FISHING_STATES = 3
};

/* A state's functions in data_ov081_022798b4. */
typedef struct TurtleFishingStep {
    MemberPointer enter;  /* 0x00: int (him); the state is taken unless it answers 0 */
    MemberPointer update; /* 0x08: int (him) */
} TurtleFishingStep;

/* His object. */
TurtleFishing *TurtleFishing_Destruct(TurtleFishing *turtle);
TurtleFishing *TurtleFishing_DestructDelete(TurtleFishing *turtle);
void TurtleFishing_OnEvent(TurtleFishing *turtle, int code);
int TurtleFishing_AgreesToTalk(TurtleFishing *turtle);
void TurtleFishing_SetState(TurtleFishing *turtle, int state);
int TurtleFishing_Update(TurtleFishing *turtle);
int TurtleFishing_ModelName(void);
int TurtleFishing_TextureName(void);
int TurtleFishing_Start(TurtleFishing *turtle);
int TurtleFishing_Init(TurtleFishing *turtle);
void *TurtleFishing_Create(void);

/* His states. */
int TurtleFishing_EnterStand(TurtleFishing *turtle);
int TurtleFishing_UpdateStand(void);
int TurtleFishing_EnterTalk(TurtleFishing *turtle);
int TurtleFishing_UpdateTalk(TurtleFishing *turtle);
int TurtleFishing_UpdateTalked(void);

#endif
