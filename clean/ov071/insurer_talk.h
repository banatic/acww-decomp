/* The insurance seller's talk scene (insurer.h: InsurerTalk, vtable 0x0227a1e8).
 *
 * Its vtable slots, beyond those of main's scene class 0x020d9ff8: 0x00 and 0x04 its
 * destructors, 0x08 its reset (InsurerTalk_Reset), 0x14 a line ended
 * (InsurerTalk_OnLineEnded), 0x18 the player's answer (InsurerTalk_OnAnswer), 0x78 the line
 * the talk starts with (InsurerTalk_FirstLine) and 0x84 a command of the scene ended
 * (InsurerTalk_RunSequence).
 *
 * What he does in it, by the lines of "sp_npc_insurance" (INSURER_LINE_*):
 * - the insurance: for 3000 bells (lines 0x15, 0x17, 0x19) the player record's flag 0x17 and
 *   its date (PlayerField2416_SetToday), with item 0x149d; then the cover for 6000 bells
 *   (lines 0x1d, 0x27, 0x1e) flag 0x18, with item 0x14a0;
 * - explanations: one of five lines (0x0e-0x12) not said yet, four in a row, then the offer
 *   of the insurance or of the cover;
 * - claims: the player picks from the pockets an item of codes 0x3934-0x3983 (sequence 0,
 *   InsurerTalk_TakeClaim): it is taken and the player record's count of claims raised;
 * - two questions with five answers: the weekday the fox comes on (line 0x08, main's
 *   EventSchedule.fox_day) and whether his own event 0x3c is barred for a week (line 0x0c).
 *
 * Daily bit 0x28 of the current player (TalkChecks_TestSetDailyBit) is set once he pitched to
 * the player today. */
#ifndef CLEAN_OV071_INSURER_TALK_H
#define CLEAN_OV071_INSURER_TALK_H

#include "insurer.h"
#include "types.h"

/* What the talk starts with (InsurerTalk.first), each with its line in data_ov071_02279fbc. */
enum InsurerTalkFirst {
    INSURER_TALK_FIRST_PITCHED = 0, /* pitched to today, not insured: line 0x05 */
    INSURER_TALK_FIRST_TODAY = 1,   /* insured today: line 0x07 */
    INSURER_TALK_FIRST_COVERED = 2, /* insured and covered, pitched to today: line 0x20 */
    INSURER_TALK_FIRSTS = 3
};

/* What the first line function gives: the message file's name (an address) and the message. */
typedef struct InsurerLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} InsurerLine;

/* The talk's sequences (data_ov071_0227a364). */
enum InsurerTalkSequence { INSURER_TALK_SEQUENCE_CLAIM = 0, INSURER_TALK_SEQUENCE_NEXT_LINE = 1, INSURER_TALK_SEQUENCES = 2 };

/* No line (the lines are bytes). */
#define INSURER_NO_LINE 0xff

/* The lines of "sp_npc_insurance". */
#define INSURER_LINE_FOX_DAY 0x08 /* answered 0-4: the fox's weekday 1-5; then 0x09 */
#define INSURER_LINE_FOX_DAY_TAKEN 0x09
#define INSURER_LINE_BAR_EVENT 0x0c     /* answered 0-4: 0x0d, the explanations reset; 4 bars */
#define INSURER_LINE_EXPLAIN_START 0x0d /* 0x0d-0x12: end with an explanation */
#define INSURER_LINE_EXPLAIN_FIRST 0x0e /* the five explanations */
#define INSURER_LINE_EXPLAIN_END 0x12
#define INSURER_LINE_EXPLAINED 0x13 /* after four explanations, not covered */
#define INSURER_LINE_EXPLAINED_UNINSURED 0x14
#define INSURER_LINE_OFFER 0x15 /* answered 0: 3000 bells asked */
#define INSURER_LINE_NO_BELLS 0x16
#define INSURER_LINE_OFFER_17 0x17
#define INSURER_LINE_CAN_PAY 0x18
#define INSURER_LINE_INSURE 0x19 /* ends with the insurance taken */
#define INSURER_LINE_INSURED 0x1a
#define INSURER_LINE_EXPLAINED_COVERED 0x1b /* after four explanations, covered */
#define INSURER_LINE_EXPLAINED_INSURED 0x1c
#define INSURER_LINE_OFFER_COVER_1D 0x1d /* answered 0: 6000 bells asked */
#define INSURER_LINE_COVER 0x1e          /* ends with the cover taken */
#define INSURER_LINE_COVERED 0x1f
#define INSURER_LINE_ASK_CLAIM_20 0x20
#define INSURER_LINE_ASK_CLAIM_21 0x21
#define INSURER_LINE_CLAIM_SCREEN 0x23 /* ends with the pockets' screen for a claim */
#define INSURER_LINE_NO_CLAIM 0x24
#define INSURER_LINE_CLAIM_TAKEN 0x25
#define INSURER_LINE_NO_CLAIM_ITEM 0x26
#define INSURER_LINE_OFFER_COVER_27 0x27
#define INSURER_LINE_GREETINGS 0x28 /* 0x28-0x2c: before he pitched to the player today */
#define INSURER_LINE_GREETINGS_LAST 0x2c

void InsurerTalk_OnAnswer(InsurerTalk *talk);
void InsurerTalk_OnLineEnded(InsurerTalk *talk);
void InsurerTalk_FirstLine(InsurerTalk *talk, InsurerLine *out);
void InsurerTalk_Begin(InsurerTalk *talk, void *owner);
void InsurerTalk_Reset(InsurerTalk *talk);
void *InsurerTalk_Delete(void *talk);
void *InsurerTalk_Destroy(void *talk);
void *InsurerTalk_Construct(void *talk);
int InsurerTalk_PickExplanation(int unused, unsigned char *said, int count);
int InsurerTalk_CountUnsaid(int unused, const unsigned char *said, int count);
void InsurerTalk_NextLine(int talk);
void InsurerTalk_TakeClaim(InsurerTalk *talk);
unsigned short InsurerTalk_IsClaimItem(unsigned short *item, int state);
void InsurerTalk_SetNextSequence(InsurerTalk *talk, int sequence);
void InsurerTalk_SetSequence(void *talk, int sequence);
void InsurerTalk_SequenceInto(int talk, MemberPointer *out, int sequence);
void InsurerTalk_RunSequence(InsurerTalk *talk);

#endif
