/* The mole's talk scene (mole.h: MoleTalk, vtable 0x022797fc): a scene of class 0x020d9ff8
 * that shows the lines of the message file "sp_npc_reset".
 *
 * Its vtable slots, beyond those of the scene class:
 * - 0x78 (MoleTalk_FirstLine): the line the talk starts with, by the count 0x0d of the current
 *   player's record (PlayerField2416_Count0D): line 0x00 for a count up to 1, 0x04, 0x09, 0x13
 *   and 0x1b for the counts 2 to 5; above 5 one of the last four at random;
 * - 0x10 (MoleTalk_OnLineBegins): at line 0x17 a phrase is picked, one of the 16 messages of
 *   "st_general" (not the one picked before), and put in the talk's part 0;
 * - 0x14 (MoleTalk_OnLineEnded): line 0x17 opens the screen of mode 0xc, given the phrase;
 *   line 0x0f waits 90 frames before line 0x10;
 * - 0x18 (MoleTalk_OnAnswer): the player's answer to lines 0x0b and 0x1f-0x21;
 * - 0x1c (MoleTalk_OnTag): a message's tag handing 0 (the player's animation 99), 1 or 2 (his
 *   sounds 0x7f4 and 0x7f5);
 * - 0x70 (MoleTalk_OnClose) and 0x74 (MoleTalk_OnGoOn): his music;
 * - 0x80 and 0x84 (MoleTalk_RunEachFrame, MoleTalk_RunAfterCommand): the talk's sequence
 *   (MoleTalk.sequence, data_ov077_022797d0).
 *
 * Its sequences (MoleTalk_SetSequence, which also counts 90 frames down from then):
 *   0  none;
 *   1  after the phrase's screen (run once a command of the scene ends): line 0x18, or with
 *      the screen's result 1 line 0x19 or 0x1a at random;
 *   2  the wait (run each frame): when the 90 frames are up, line 0x10 and the next line. */
#ifndef CLEAN_OV077_MOLE_TALK_H
#define CLEAN_OV077_MOLE_TALK_H

#include "mole.h"
#include "ov004/member_pointer.h"
#include "types.h"

/* The sequences. */
#define MOLE_TALK_SEQ_NONE 0
#define MOLE_TALK_SEQ_AFTER_PHRASE 1
#define MOLE_TALK_SEQ_WAIT 2
#define MOLE_TALK_SEQUENCES 3

/* A sequence of data_ov077_022797d0: its function (filled by __sinit_ov077_02279608) and
 * whether it runs each frame (slot 0x80) or once a command of the scene ends (slot 0x84). */
typedef struct MoleTalkSequence {
    MemberPointer run;
    u8 each_frame;
    u8 unk_09[3];
} MoleTalkSequence;
extern MoleTalkSequence data_ov077_022797d0[MOLE_TALK_SEQUENCES];

/* What its slot 0x78 gives: the message file's name (an address) and the line to say. */
typedef struct MoleTalkLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} MoleTalkLine;

void MoleTalk_OnAnswer(MoleTalk *talk);
void MoleTalk_OnLineEnded(MoleTalk *talk);
void MoleTalk_OnLineBegins(MoleTalk *talk);
void MoleTalk_FirstLine(MoleTalk *talk, MoleTalkLine *out);
void MoleTalk_OnTag(MoleTalk *talk, int tag);
void MoleTalk_Begin(MoleTalk *talk, Mole *owner);
void MoleTalk_OnClose(MoleTalk *talk);
void MoleTalk_OnGoOn(MoleTalk *talk);
MoleTalk *MoleTalk_DestructDelete(MoleTalk *talk);
MoleTalk *MoleTalk_Destruct(MoleTalk *talk);
MoleTalk *MoleTalk_Construct(MoleTalk *talk);
void MoleTalk_AfterPhrase(MoleTalk *talk);
void MoleTalk_Wait(MoleTalk *talk);
void MoleTalk_SetSequence(MoleTalk *talk, int sequence);
void MoleTalk_RunAfterCommand(MoleTalk *talk);
void MoleTalk_RunEachFrame(MoleTalk *talk);

#endif
