/* The turtle's talk scene (class vtable 0x0227925c, at 0x658 of the turtle, turtle.h): a scene
 * of class 0x020d9ff8 (obj_020d9ff8.h) with the lines of the archives "sp_npc_turtle",
 * "sp_npc_turtle7" and "sp_etc_sequence5_2".
 *
 * What he talks of (TurtleTalk_Line), by the current player's record:
 * - with flag 1: "sp_etc_sequence5_2", line 0 the first time (flag 0xd, set then), else one of
 *   the lines 3-6; flag 0xa set;
 * - once in his visit, when the pockets hold item 0x37e0: line 0 of "sp_npc_turtle", which asks
 *   for it; answered 0 the item is taken (line 2) and item 0x1559 given in return (line 4);
 * - "sp_npc_turtle7": when the player's records hold all the fish and the player has not had
 *   item 0x1375 (flag 0x21), line 0 (2 when another player of the town has had it, 9 without a
 *   free slot); line 0 or 2 shown, the item is given (flag 0x21) and line 1 follows. The same
 *   with all the insects and item 0x1377 (flag 0x22): lines 3, 5, 0xa and 4. Else one of the
 *   lines 6-8.
 *
 * Its vtable slots, beyond those of its base class: 0x00 and 0x04 its destructors, 0x14 what
 * follows the line shown (TurtleTalk_OnLineShown), 0x18 the player's answer
 * (TurtleTalk_OnAnswer) and 0x78 the first line (TurtleTalk_Line); its reset (slot 0x08) is the
 * scene base's. */
#ifndef CLEAN_OV080_TURTLE_TALK_H
#define CLEAN_OV080_TURTLE_TALK_H

#include "main/scene_base.h"
#include "types.h"

struct Turtle;

/* TurtleTalk.slot, besides a slot of the pockets. */
#define TURTLE_TALK_SLOT_UNKNOWN (-1) /* the pockets not looked at yet */
#define TURTLE_TALK_SLOT_DONE (-2)    /* item 0x37e0 traded or refused in this visit */

/* The talk scene (0xb8 bytes). */
typedef struct TurtleTalk {
    SceneBase scene;      /* 0x00: the receiver's message (byte 0x1e) is the line shown */
    u8 unk_80[0x30];      /* 0x80: the scene's commands (scene_command.h) */
    struct Turtle *owner; /* 0xb0 */
    s32 slot;             /* 0xb4: the pockets' slot of item 0x37e0, or TURTLE_TALK_SLOT_* */
} TurtleTalk;

/* What its slot 0x78 gives: the archive's name and the line to say. */
typedef struct TurtleTalkLine {
    const char *name;
    u8 message;
    u8 unk_05[3];
} TurtleTalkLine;

/* Its slots. */
void TurtleTalk_OnAnswer(TurtleTalk *talk);
void TurtleTalk_OnLineShown(TurtleTalk *talk);
void TurtleTalk_Line(TurtleTalk *talk, TurtleTalkLine *line);
void TurtleTalk_Begin(TurtleTalk *talk, struct Turtle *owner);

/* Its life. */
TurtleTalk *TurtleTalk_DestructDelete(TurtleTalk *talk);
TurtleTalk *TurtleTalk_Destruct(TurtleTalk *talk);
TurtleTalk *TurtleTalk_Construct(TurtleTalk *talk);

#endif
