/* Overlay 80: the turtle, the special character of the message archives "sp_npc_turtle" and
 * "sp_npc_turtle7" with the model npc_sp/model/ttl, object profile 0x56 (its record at
 * data_ov080_02279220, which the main module's profile table data_020e3134 points to). Main's
 * spawner (main/spawner.h) makes him from its spawn table's entry of code 0xd012
 * (Spawner_CheckProfile56, while flag 8 of the object at data_021d27ac is set), loading this
 * overlay with him. A scene object of class 0x020da088 (special_scene_object.h) with vtable
 * 0x022792ec, 0x710 bytes.
 *
 * On his start he plays animation 0x140, moves the nodes 0xc-0xe of his model to its first
 * set, is held (flag 2 at 0x4e8) and, unless the player record has flag 1, sets flag 0x20 of
 * main's event queue. His talk (TurtleTalk, turtle_talk.h, at 0x658) trades item 0x37e0 for
 * item 0x1559, and gives items 0x1375 and 0x1377 to the first player of the town whose
 * records hold all the fish and all the insects.
 *
 * His states (TURTLE_*), a table of C++ pointers to member functions (an entry and a run for
 * each state, data_ov080_022793e0, filled by __sinit_ov080_02279178):
 * - TURTLE_STAND: his motion of kind 0;
 * - TURTLE_TALK: he turns to the talk's partner (to angle 0 without one) and talks; once his
 *   action is idle his event is finished and TURTLE_TALKED;
 * - TURTLE_TALKED: nothing.
 * Told of event 0 (his vtable slot 0x4c, the player's act) he talks; told the event ended (8)
 * he stands. */
#ifndef CLEAN_OV080_TURTLE_H
#define CLEAN_OV080_TURTLE_H

#include "ov004/member_pointer.h"
#include "turtle_talk.h"
#include "types.h"

/* The states. */
#define TURTLE_STAND 0
#define TURTLE_TALK 1
#define TURTLE_TALKED 2
#define TURTLE_STATES 3

/* The size of the special character's scene object he derives from, as far as it is used. */
#define TURTLE_BASE_SIZE 0x654

typedef struct Turtle {
    u8 base[TURTLE_BASE_SIZE]; /* 0x000: the special character's scene object */
    s32 state;                 /* 0x654: TURTLE_* (Turtle_SetState) */
    TurtleTalk talk;           /* 0x658 */
} Turtle;

/* A state's row: its entry and its run (the null member pointer when it has none); the table,
 * filled by __sinit_ov080_02279178 (TurtleInit_Tables). */
typedef struct TurtleStateRow {
    MemberPointer enter;
    MemberPointer run;
} TurtleStateRow;
extern TurtleStateRow data_ov080_022793e0[TURTLE_STATES];

/* The object's life and vtable slots. */
Turtle *Turtle_Destruct(Turtle *self);
Turtle *Turtle_DestructDelete(Turtle *self);
void Turtle_OnEvent(Turtle *self, int code);
int Turtle_MayAct(Turtle *self);
int Turtle_ModelName(void);
int Turtle_TextureName(void);
int Turtle_Leave(Turtle *self);
int Turtle_Start(Turtle *self);
int Turtle_Init(Turtle *self);
Turtle *Turtle_Create(void);

/* His states. */
int Turtle_UpdateTalked(void);
int Turtle_UpdateTalk(Turtle *self);
int Turtle_EnterTalk(Turtle *self);
int Turtle_UpdateStand(void);
int Turtle_EnterStand(Turtle *self);
void Turtle_SetState(Turtle *self, int state);
int Turtle_Update(Turtle *self);

/* The overlay's static initialiser (ov080_static_init.c). */
int TurtleInit_Tables(void);

#endif
