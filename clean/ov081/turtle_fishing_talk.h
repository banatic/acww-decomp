/* The fishing tourney host's talk scene (TurtleFishingTalk, turtle_fishing.h; class vtable
 * 0x0227972c, derived from the scene class 0x020d9ff8). Its lines are of "sp_npc_turtle1"
 * (data_ov081_02279868), except those about the item 0x37e0, which are of "sp_npc_turtle"
 * (data_ov081_02279878), the file the turtle's other events share.
 *
 * With the item 0x37e0 in the pockets (looked for once a talk, TurtleFishingTalk.slot_37e0)
 * the talk starts with line 0 of "sp_npc_turtle"; the first answer to it takes the item
 * (line 2), and after line 2 he gives the item 0x1559 (line 4). Else the talk starts
 * (slot 0x78, TurtleFishingTalk_Line) with:
 *   line 2 before 12:00 or from 18:00;
 *   line 1 when the current player has not had the tourney's daily bit 0x1b today and has
 *          neither rod (0x1374, 0x1375) in the pockets or held, line 0 when the pockets are
 *          also full;
 *   line 8 when the daily bit was set, else line 3 (the bit is set now).
 *
 * The player's answers (slot 0x18, TurtleFishingTalk_OnAnswer): after line 8, the first
 * answer gives line 11; another shows the record (TurtleFishingTalk_ShowRecord) with line 9
 * when the current player holds it, line 10 when someone else does.
 *
 * The end of a line (slot 0x14, TurtleFishingTalk_OnLineEnd):
 *   line 1:    he gives the rod 0x1374 and sets the daily bit 0x1b: line 4;
 *   line 0xb:  the pockets' screen opens to pick a fish; once its command ends (slot 0x84)
 *              the fish picked is weighed (TurtleFishingTalk_AfterPockets): line 0xd, else 0xc;
 *   line 0xd:  the player's entry is noted; a fish longer (in tenths) than the record's gives
 *              line 0x10, else line 0x16 when the current player holds the record, line 0xe
 *              when someone else does;
 *   line 0x10: line 0x11 when the current player held the record, else line 0x12;
 *   line 0x13: the player's fish becomes the record (and a winner is to be announced), and he
 *              gives a prize from the item list of kind 0, group 0: line 0x14 when the player
 *              held the record before, else 0x15. */
#ifndef CLEAN_OV081_TURTLE_FISHING_TALK_H
#define CLEAN_OV081_TURTLE_FISHING_TALK_H

#include "ov004/member_pointer.h"
#include "turtle_fishing.h"
#include "types.h"

/* TurtleFishingTalk.slot_37e0: not looked for yet, and given (or the talk went on without
 * it). */
#define TURTLE_FISHING_TALK_37E0_UNKNOWN (-1)
#define TURTLE_FISHING_TALK_37E0_DONE (-2)

/* What the talk starts with (its slot 0x78): the message file and the line. */
typedef struct TurtleFishingTalkStart {
    const char *name;
    u8 message;
    u8 unk_05[3];
} TurtleFishingTalkStart;

/* The class. */
TurtleFishingTalk *TurtleFishingTalk_Construct(TurtleFishingTalk *talk);
TurtleFishingTalk *TurtleFishingTalk_Destruct(TurtleFishingTalk *talk);
TurtleFishingTalk *TurtleFishingTalk_DestructDelete(TurtleFishingTalk *talk);
void TurtleFishingTalk_Begin(TurtleFishingTalk *talk, TurtleFishing *owner);
void TurtleFishingTalk_PickCommandFunction(TurtleFishingTalk *talk, MemberPointer *slot, int index);
void TurtleFishingTalk_SetAfterCommand(TurtleFishingTalk *talk, int index);
void TurtleFishingTalk_SetThenCommand(TurtleFishingTalk *talk, int index);
void TurtleFishingTalk_OnCommandEnded(TurtleFishingTalk *talk);

/* Its lines. */
void TurtleFishingTalk_Line(TurtleFishingTalk *talk, TurtleFishingTalkStart *out);
void TurtleFishingTalk_OnAnswer(TurtleFishingTalk *talk);
void TurtleFishingTalk_OnLineEnd(TurtleFishingTalk *talk);
int TurtleFishingTalk_ShowRecord(TurtleFishingTalk *talk);
void TurtleFishingTalk_AfterPockets(TurtleFishingTalk *talk);
void TurtleFishingTalk_NextLine(TurtleFishingTalk *talk);
u16 TurtleFishingTalk_IsFish(u16 *item, int state);

#endif
