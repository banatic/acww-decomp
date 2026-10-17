/* The insect contest host's talk scene (TurtleInsectsTalk, turtle_insects.h; class vtable
 * 0x0227978c, derived from the scene class 0x020d9ff8). Its lines are of "sp_npc_turtle2"
 * (data_ov082_022798c8), except those about the item 0x37e0, which are of "sp_npc_turtle"
 * (data_ov082_022798d8), the file the turtle's other events share. It follows the fishing
 * tourney's talk (overlay 81, turtle_fishing_talk.h) with the insects, the nets and whole
 * sizes in place of the fish, the rods and tenths.
 *
 * With the item 0x37e0 in the pockets (looked for once a talk, TurtleInsectsTalk.slot_37e0)
 * the talk starts with line 0 of "sp_npc_turtle"; the first answer to it takes the item
 * (line 2), and after line 2 he gives the item 0x1559 (line 4). Else the talk starts
 * (slot 0x78, TurtleInsectsTalk_Line) with:
 *   line 2 before 12:00 or from 18:00;
 *   line 1 when the current player has not had the contest's daily bit 0x1c today and has
 *          neither net (0x1376, 0x1377) in the pockets or held, line 0 when the pockets are
 *          also full;
 *   line 8 when the daily bit was set, else line 3 (the bit is set now).
 *
 * The player's answers (slot 0x18, TurtleInsectsTalk_OnAnswer): after line 8, the first
 * answer gives line 11; another shows the record (TurtleInsectsTalk_ShowRecord) with line 9
 * when the current player holds it, line 10 when someone else does, line 0x1e when no one does.
 *
 * The end of a line (slot 0x14, TurtleInsectsTalk_OnLineEnd):
 *   line 1:    he gives the net 0x1376 and sets the daily bit 0x1c: line 4;
 *   line 0xb:  the pockets' screen opens to pick an insect; once its command ends (slot 0x84)
 *              the insect picked is measured (TurtleInsectsTalk_AfterPockets): line 0xd, else
 *              line 0xc;
 *   line 0xd:  line 0x16 when the record holds no insect; else the player's entry is noted, and
 *              an insect bigger (in whole units) than the record's gives line 0x10, else line
 *              0x1d when the current player holds the record, line 0xe when someone else does;
 *   line 0x10: line 0x11 when the current player held the record, else line 0x12;
 *   lines 0x13 and 0x16: the player's insect becomes the record (and a winner is to be
 *              announced), and he gives a prize from the item list of kind 0, group 0: line
 *              0x14 when the player held the record before, else 0x15. */
#ifndef CLEAN_OV082_TURTLE_INSECTS_TALK_H
#define CLEAN_OV082_TURTLE_INSECTS_TALK_H

#include "ov004/member_pointer.h"
#include "turtle_insects.h"
#include "types.h"

/* TurtleInsectsTalk.slot_37e0: not looked for yet, and given (or the talk went on without
 * it). */
#define TURTLE_INSECTS_TALK_37E0_UNKNOWN (-1)
#define TURTLE_INSECTS_TALK_37E0_DONE (-2)

/* What the talk starts with (its slot 0x78): the message file and the line. */
typedef struct TurtleInsectsTalkStart {
    const char *name;
    u8 message;
    u8 unk_05[3];
} TurtleInsectsTalkStart;

/* The class. */
TurtleInsectsTalk *TurtleInsectsTalk_Construct(TurtleInsectsTalk *talk);
TurtleInsectsTalk *TurtleInsectsTalk_Destruct(TurtleInsectsTalk *talk);
TurtleInsectsTalk *TurtleInsectsTalk_DestructDelete(TurtleInsectsTalk *talk);
void TurtleInsectsTalk_Begin(TurtleInsectsTalk *talk, TurtleInsects *owner);
void TurtleInsectsTalk_PickCommandFunction(TurtleInsectsTalk *talk, MemberPointer *slot, int index);
void TurtleInsectsTalk_SetAfterCommand(TurtleInsectsTalk *talk, int index);
void TurtleInsectsTalk_SetThenCommand(TurtleInsectsTalk *talk, int index);
void TurtleInsectsTalk_OnCommandEnded(TurtleInsectsTalk *talk);

/* Its lines. */
void TurtleInsectsTalk_Line(TurtleInsectsTalk *talk, TurtleInsectsTalkStart *out);
void TurtleInsectsTalk_OnAnswer(TurtleInsectsTalk *talk);
void TurtleInsectsTalk_OnLineEnd(TurtleInsectsTalk *talk);
int TurtleInsectsTalk_ShowRecord(TurtleInsectsTalk *talk);
void TurtleInsectsTalk_AfterPockets(TurtleInsectsTalk *talk);
void TurtleInsectsTalk_NextLine(TurtleInsectsTalk *talk);
u16 TurtleInsectsTalk_IsInsect(u16 *item, int state);

#endif
