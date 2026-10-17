/* The otter's talk scene (OtterTalk, otter.h; class vtable 0x02279744, derived from the scene
 * class 0x020d9ff8). Its lines are of "sp_npc_otter" (data_ov076_022796e0).
 *
 * The talk starts (slot 0x78, OtterTalk_Line) with line 2 when the player has the item 0x1559
 * in the pockets (OTTER_TALK_HAS_ITEM), else with line 0 or 1 at random.
 *
 * The player's answers (slot 0x18, OtterTalk_OnAnswer):
 *   after line 0 or 1: the first choice, one of the lines 0x0f to 0xfc at random; else line 5;
 *   after line 2:      the third choice, line 4;
 *   after line 8:      the first choice line 0xb, the second line 9, else line 0xa.
 *
 * The end of a line (slot 0x14, OtterTalk_OnLineEnd):
 *   lines 0x0f to 0xfc and 0xfd: line 0xd or 0xe at random;
 *   line 4:      the pockets' screen opens to pick the item 0x1559; once its command ends
 *                (slot 0x84), a picked pocket is emptied and the item handed to him (line 6),
 *                else line 5 (OtterTalk_AfterPockets);
 *   lines 10/11: he gives the item 0x4a38 (line 10) or 0x1373 (line 11) into the pockets, the
 *                current player's daily bit 0x18 is set, line 0xc;
 *   line 12:     line 0x33 when the item he gave is 0x4a38 (as its variant's item), else 0xfd;
 *   lines 13/14: unless he gave something already, with a free pocket he gives an item drawn
 *                from the item lists (kind 0 in 7 of 9 draws, kind 4 or kind 3 in one each, all
 *                of group 0x15) and the daily bit 0x18 is set; he gave. The current player
 *                takes part in the schedule's day with event 0x42. */
#ifndef CLEAN_OV076_OTTER_TALK_H
#define CLEAN_OV076_OTTER_TALK_H

#include "otter.h"
#include "types.h"

/* OtterTalk.sequence. */
#define OTTER_TALK_HAS_ITEM 0
#define OTTER_TALK_FIRST 1
#define OTTER_TALK_SECOND 2
#define OTTER_TALK_SEQUENCES 3

/* What the talk starts with (its slot 0x78): the message file and the line. */
typedef struct OtterTalkStart {
    const char *name;
    u8 message;
    u8 unk_05[3];
} OtterTalkStart;

/* The class. */
OtterTalk *OtterTalk_Construct(OtterTalk *talk);
OtterTalk *OtterTalk_Destruct(OtterTalk *talk);
OtterTalk *OtterTalk_DestructDelete(OtterTalk *talk);
void OtterTalk_Reset(OtterTalk *talk);
void OtterTalk_Begin(OtterTalk *talk, Otter *owner);
void OtterTalk_SetAfterCommand(OtterTalk *talk, int index);
void OtterTalk_OnCommandEnded(OtterTalk *talk);

/* Its lines. */
void OtterTalk_Line(OtterTalk *talk, OtterTalkStart *out);
void OtterTalk_OnAnswer(OtterTalk *talk);
void OtterTalk_OnLineEnd(OtterTalk *talk);
void OtterTalk_AfterPockets(OtterTalk *talk);
int OtterTalk_IsAskedItem(u16 *item, int state);

#endif
