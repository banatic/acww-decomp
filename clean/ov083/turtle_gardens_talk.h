/* The garden judge's talk scene (TurtleGardensTalk, turtle_gardens.h; class vtable 0x022791fc,
 * derived from the scene class 0x020d9ff8). Its lines are of "sp_npc_turtle3"
 * (data_ov083_02279338), except those about the item 0x37e0, which are of "sp_npc_turtle"
 * (data_ov083_02279348), the file the turtle's other events share.
 *
 * With the item 0x37e0 in the pockets (looked for once a talk, TurtleGardensTalk.slot_37e0)
 * the talk starts with line 0 of "sp_npc_turtle"; the first answer to it takes the item
 * (line 2), and after line 2 he gives the item 0x1559 (line 4), as at the fishing tourney
 * (turtle_fishing_talk.h). Else the talk starts (slot 0x78, TurtleGardensTalk_Line) with:
 *   line 0 before 6:00 or from 18:00;
 *   the first time (flag 1 of main's object at data_021d27ac, set then): line 1 on the first
 *          day of event 0x0e, line 2 on its next five days, else line 3;
 *   line 0xa after that.
 *
 * The player's answers (slot 0x18, TurtleGardensTalk_OnAnswer): after line 0xa, the first
 * answer gives line 0xc one time in three, else one of the lines 0x1c to 0x26 at random.
 *
 * The end of a line (slot 0x14, TurtleGardensTalk_OnLineEnd):
 *   lines 5, 6 and 9: unless the current player had the daily bit 0x1d today (it is set now),
 *              the player is owed a gardening letter, and with a free pocket he picks a prize
 *              (one of the shops' twelve random items): line 7;
 *   line 7:    he gives the prize: line 8. */
#ifndef CLEAN_OV083_TURTLE_GARDENS_TALK_H
#define CLEAN_OV083_TURTLE_GARDENS_TALK_H

#include "turtle_gardens.h"
#include "types.h"

/* TurtleGardensTalk.slot_37e0: not looked for yet, and given (or the talk went on without
 * it). */
#define TURTLE_GARDENS_TALK_37E0_UNKNOWN (-1)
#define TURTLE_GARDENS_TALK_37E0_DONE (-2)

/* What the talk starts with (its slot 0x78): the message file and the line. */
typedef struct TurtleGardensTalkStart {
    const char *name;
    u8 message;
    u8 unk_05[3];
} TurtleGardensTalkStart;

/* The class. */
TurtleGardensTalk *TurtleGardensTalk_Construct(TurtleGardensTalk *talk);
TurtleGardensTalk *TurtleGardensTalk_Destruct(TurtleGardensTalk *talk);
TurtleGardensTalk *TurtleGardensTalk_DestructDelete(TurtleGardensTalk *talk);
void TurtleGardensTalk_Begin(TurtleGardensTalk *talk, TurtleGardens *owner);

/* Its lines. */
void TurtleGardensTalk_Line(TurtleGardensTalk *talk, TurtleGardensTalkStart *out);
void TurtleGardensTalk_OnAnswer(TurtleGardensTalk *talk);
void TurtleGardensTalk_OnLineEnd(TurtleGardensTalk *talk);

#endif
