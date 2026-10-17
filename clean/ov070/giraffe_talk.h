/* The giraffe's talk scene (giraffe.h: GiraffeTalk, vtable 0x02279dbc).
 *
 * Its vtable slots, beyond those of main's scene class 0x020d9ff8: 0x00 and 0x04 its
 * destructors, 0x08 its reset (GiraffeTalk_Reset), 0x14 a line ended (GiraffeTalk_OnLineEnded),
 * 0x18 the player's answer (GiraffeTalk_OnAnswer), 0x64 a value the talk hands on, added to the
 * player's score (GiraffeTalk_AddScore), 0x78 the line the talk starts with
 * (GiraffeTalk_FirstLine) and 0x84 a command of the scene ended (GiraffeTalk_RunSequence).
 *
 * What she does in it, by the lines of "sp_npc_giraffe" (GIRAFFE_LINE_*):
 * - the score: GiraffeTalk_Score adds to the player record's count 0x0e (PlayerField2416, up
 *   to 100) twice a grade of each item the player wears (by its price, GiraffeTalk_Grade), or a
 *   small random amount for an empty place; at line 0x24 she writes the player a letter whose
 *   message follows the score, with an item for the lower scores;
 * - advice: one of 20 lines (0x0f-0x22) not said yet in the round, up to five in a row, then
 *   line 0x23 and the round starts again (Giraffe.advice_said, Giraffe.advice_count);
 * - the dressing: the player chooses on a screen how many bells to pay (sequence 0,
 *   GiraffeTalk_TakePayment), and GiraffeTalk_Dress gives a hat or an accessory and clothes
 *   from the tier of what was paid (data_ov070_02279be0), the items worn before going back into
 *   the pockets; she first checks that the pockets have room for them (GiraffeTalk_HasRoom).
 *
 * Its daily bits (TalkChecks_TestSetDailyBit): 7 talked today, 8 a round of advice ended
 * today, 9 dressed today. Flag 10 of main's object at data_021d27ac is set when the player did
 * not pay. */
#ifndef CLEAN_OV070_GIRAFFE_TALK_H
#define CLEAN_OV070_GIRAFFE_TALK_H

#include "giraffe.h"
#include "types.h"

/* What the talk starts with (GiraffeTalk.first), each with its line in data_ov070_02279ba8. */
enum GiraffeTalkFirst {
    GIRAFFE_TALK_FIRST_TODAY = 0,    /* first talk today: line 0x00 */
    GIRAFFE_TALK_FIRST_ADVICE = 1,   /* no round of advice ended today: line 0x09 */
    GIRAFFE_TALK_FIRST_COUNTING = 2, /* fewer than three lines of advice said: 0x4c + that count */
    GIRAFFE_TALK_FIRST_HIGH = 3,     /* a score of 61 or more: line 0x29 */
    GIRAFFE_TALK_FIRST_LOW = 4,      /* else: line 0x28 */
    GIRAFFE_TALK_FIRST_REFUSED = 5,  /* 2 to 4 after the player did not pay: line 0x31 */
    GIRAFFE_TALK_FIRST_DRESSED = 6,  /* dressed today: line 0x27 */
    GIRAFFE_TALK_FIRSTS = 7
};

/* What the first line function gives: the message file's name (an address) and the message. */
typedef struct GiraffeLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} GiraffeLine;

/* A tier of the dressing (data_ov070_02279be0, seven of them): the first whose `max_paid` is
 * at least what was paid. */
typedef struct GiraffeTier {
    u16 items[3];       /* 0x00: the hat or accessory given, one of three (a fourth: none) */
    u8 is_accessory[3]; /* 0x06: 0 for a hat, else an accessory */
    u8 special_chance;  /* 0x09: in percent, the chance the clothes come from group 0x22 */
    u8 unk_0a[2];       /* 0x0a */
    s32 max_paid;       /* 0x0c */
} GiraffeTier;

#define GIRAFFE_TIERS 7

/* No line (the lines are bytes). */
#define GIRAFFE_NO_LINE 0xff

/* The lines of "sp_npc_giraffe". */
#define GIRAFFE_LINE_GREETING 0x00
#define GIRAFFE_LINE_LETTER_ASK 0x09 /* answered 0: 0x0b with room for a letter, else 0x0c */
#define GIRAFFE_LINE_LETTER_ROOM 0x0b
#define GIRAFFE_LINE_LETTER_NO_ROOM 0x0c
#define GIRAFFE_LINE_ADVICE_START 0x0e /* ends with a line of advice */
#define GIRAFFE_LINE_ADVICE_FIRST 0x0f /* the 20 lines of advice */
#define GIRAFFE_LINE_ADVICE_LAST 0x22
#define GIRAFFE_LINE_ADVICE_DONE 0x23 /* five said: the round ends */
#define GIRAFFE_LINE_LETTER 0x24      /* ends with her letter written */
#define GIRAFFE_LINE_REMARK 0x25      /* ends with one of ten remarks, 0x3a-0x43 */
#define GIRAFFE_LINE_REMARKS 0x3a
#define GIRAFFE_LINE_OFFER 0x28 /* ends with 0x2c when the pockets have room */
#define GIRAFFE_LINE_OFFER_2B 0x2b
#define GIRAFFE_LINE_ASK_PAYMENT 0x2c /* ends with the payment screen */
#define GIRAFFE_LINE_ASK_PAYMENT_31 0x31
#define GIRAFFE_LINE_PAID_UP_TO_1000 0x2d
#define GIRAFFE_LINE_PAID_UP_TO_2000 0x2e
#define GIRAFFE_LINE_PAID_UP_TO_4000 0x2f
#define GIRAFFE_LINE_PAID_MORE 0x30
#define GIRAFFE_LINE_SPECIAL_CLOTHES 0x34 /* dressed with clothes of group 0x22 */
#define GIRAFFE_LINE_DRESS 0x36           /* ends with the player dressed */
#define GIRAFFE_LINE_CLOTHES 0x37         /* dressed with other clothes */
#define GIRAFFE_LINE_LEAVE 0x38           /* ends with event 0x40 taken part in */
#define GIRAFFE_LINE_NO_ROOM 0x39
#define GIRAFFE_LINE_ADVICE_NEXT 0x46 /* 0x46-0x4a: after the n-th line of advice */
#define GIRAFFE_LINE_ADVICE_NEXT_LAST 0x4a
#define GIRAFFE_LINE_NOT_PAID 0x4b
#define GIRAFFE_LINE_COUNTING 0x4c /* 0x4c-0x4e: by the count of lines of advice */

void GiraffeTalk_OnAnswer(GiraffeTalk *talk);
void GiraffeTalk_OnLineEnded(GiraffeTalk *talk);
int GiraffeTalk_Dress(GiraffeTalk *talk);
int GiraffeTalk_HasRoom(GiraffeTalk *talk);
int GiraffeTalk_IsEmptyPocket(void *item);
void GiraffeTalk_Score(GiraffeTalk *talk);
unsigned char GiraffeTalk_Grade(int unused, int price, int place);
void GiraffeTalk_AddScore(void *talk, unsigned char value);
void GiraffeTalk_FirstLine(GiraffeTalk *talk, GiraffeLine *out);
void GiraffeTalk_Begin(GiraffeTalk *talk, Giraffe *owner);
void *GiraffeTalk_Delete(void *talk);
void *GiraffeTalk_Destroy(void *talk);
void *GiraffeTalk_Construct(void *talk);
int GiraffeTalk_PickAdvice(int unused, unsigned char *said, int count);
int GiraffeTalk_CountUnsaid(int unused, const unsigned char *said, int count);
void GiraffeTalk_TakePayment(GiraffeTalk *talk);
void GiraffeTalk_SetSequence(void *talk, int sequence);
void GiraffeTalk_RunSequence(GiraffeTalk *talk);
void GiraffeTalk_Reset(GiraffeTalk *talk);

#endif
