/* The town pelican's talk scene (town_pelican.h: TownPelicanTalk, vtable 0x0227996c).
 *
 * Its vtable slots, beyond the scene base's: 0x00 and 0x04 its destructors, 0x14 a line ended
 * (TownPelicanTalk_OnLineEnded), 0x18 the player's answer (TownPelicanTalk_OnAnswer, which only
 * asks for it), 0x78 the line the talk starts with (TownPelicanTalk_Line), 0x80 before each step
 * of the scene and 0x84 a command of the scene ended (the sequences, below).
 *
 * Its lines, of "sp_npc_mpelican": 0x1a, unless he was met and the current player has flag 6,
 * when one of 0x0c to 0x0f at random. Once line 0x1a ends, the talk is told to wait in talk
 * mode 0 and sequence 1 begins: once the line is shown to its end he plays animation 0xd5; once
 * it is done he turns to the player; once the turn is done he counts as met, the next line is
 * asked for, the daily bit 0x12 is set and the line is 0x10 the first time the player meets him
 * (the player's flag 6 then set), else one of 0 to 11 at random.
 *
 * Its sequences (TownPelicanTalk.sequence), a member function each from the table
 * data_ov075_02279930 (filled at start-up): 0 none; 1 the waking (TownPelicanTalk_Wake). A
 * sequence runs before each step when its flag (byte 8 of its entry) is set, else when a
 * command ends and then goes back to 0; the flags are the overlay's data (sequence 1's is set). */
#ifndef CLEAN_OV075_TOWN_PELICAN_TALK_H
#define CLEAN_OV075_TOWN_PELICAN_TALK_H

#include "town_pelican.h"
#include "types.h"

#define TOWN_PELICAN_TALK_SEQUENCE_NONE 0
#define TOWN_PELICAN_TALK_SEQUENCE_WAKE 1
#define TOWN_PELICAN_TALK_SEQUENCES 2

/* The steps of sequence 1 (TownPelicanTalk.step). */
#define TOWN_PELICAN_TALK_STEP_ANIMATE 0
#define TOWN_PELICAN_TALK_STEP_TURN 1
#define TOWN_PELICAN_TALK_STEP_MEET 2

/* A sequence's function in data_ov075_02279930. */
typedef struct TownPelicanTalkStep {
    MemberPointer run; /* void (talk) */
    u8 each_step;      /* 0x08: run before each step, else when a command ends */
    u8 unk_09[3];
} TownPelicanTalkStep;

/* What its line function gives: the message file's name (an address) and the message. */
typedef struct TownPelicanLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} TownPelicanLine;

/* The lines of "sp_npc_mpelican". */
#define TOWN_PELICAN_LINE_AGAIN 0x0c /* 0x0c to 0x0f: met, and the player has flag 6 */
#define TOWN_PELICAN_LINE_MET 0x10   /* the first meeting of the player */
#define TOWN_PELICAN_LINE_FIRST 0x1a /* otherwise; its end begins sequence 1 */

void TownPelicanTalk_OnAnswer(TownPelicanTalk *talk);
void TownPelicanTalk_OnLineEnded(TownPelicanTalk *talk);
void TownPelicanTalk_Line(TownPelicanTalk *talk, TownPelicanLine *out);
void TownPelicanTalk_Begin(TownPelicanTalk *talk, int owner);
void *TownPelicanTalk_Delete(void *talk);
TownPelicanTalk *TownPelicanTalk_Destroy(TownPelicanTalk *talk);
void *TownPelicanTalk_Construct(void *talk);
void TownPelicanTalk_Wake(TownPelicanTalk *talk);
void TownPelicanTalk_SetSequence(TownPelicanTalk *talk, int sequence);
void TownPelicanTalk_RunCommandSequence(TownPelicanTalk *talk);
void TownPelicanTalk_RunStepSequence(TownPelicanTalk *talk);

#endif
