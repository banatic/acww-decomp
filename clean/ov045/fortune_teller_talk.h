/* The fortune teller's talk scene (fortune_teller.h: FortuneTellerTalk, vtable 0x02261460) and
 * the two small text classes it puts the villager's name through.
 *
 * Its vtable slots, beyond the scene base's: 0x00 and 0x04 its destructors, 0x10 a line begins
 * (FortuneTellerTalk_OnLineBegins), 0x14 a line ended (FortuneTellerTalk_OnLineEnded), 0x18
 * the player's answer (FortuneTellerTalk_OnAnswer), 0x38 the focus speaker's talking motion
 * (FortuneTellerTalk_SetTalkStyle: styles 0x1e to 0x20 move the tarot cards), 0x78 the line
 * the talk starts with (FortuneTellerTalk_Line), 0x80 before each step of the scene and 0x84
 * a command of the scene ended (the sequences, below).
 *
 * Its lines, of "sp_npc_panther" (FORTUNE_TELLER_LINE_*): the first line offers a reading for
 * 100 bells, or, both readings given today, the clearing of the day's luck for 10,000 bells.
 * A reading of the day's luck sets it from the card drawn (PlayerRecord_SetDayState); a
 * reading of a villager's friendship asks for the villager's name on the name screen (screen 2 in mode 0x13) and
 * changes the villager's fondness for the player (+10 good, -3 bad).
 *
 * The cards: FortuneTeller_DrawCard picks one of 22, upright or reversed; its line shows it
 * (FORTUNE_TELLER_LINE_CARDS + 2 * card + one of two, 44 more when reversed) and the next one
 * tells what it means (FORTUNE_TELLER_LINE_MEANINGS + card, 22 more when reversed), when the
 * reading takes effect.
 *
 * Its sequences (FortuneTellerTalk.sequence), a member function each from the table
 * data_ov045_022615a4 (filled at start-up): 0 none; 1 the name typed taken
 * (FortuneTellerTalk_TakeName), when the name screen's command ends. A sequence runs before
 * each step when its flag (byte 8 of its entry) is set, else when a command ends and then
 * goes back to 0; the flags are in the overlay's .bss and nothing sets them. */
#ifndef CLEAN_OV045_FORTUNE_TELLER_TALK_H
#define CLEAN_OV045_FORTUNE_TELLER_TALK_H

#include "fortune_teller.h"
#include "main/text_label.h" /* TextVtable */
#include "types.h"

#define FORTUNE_TELLER_TALK_SEQUENCE_NONE 0
#define FORTUNE_TELLER_TALK_SEQUENCE_TAKE_NAME 1
#define FORTUNE_TELLER_TALK_SEQUENCES 2

/* A sequence's function in data_ov045_022615a4. */
typedef struct FortuneTellerTalkStep {
    MemberPointer run; /* void (talk) */
    u8 each_step;      /* 0x08: run before each step, else when a command ends */
    u8 unk_09[3];
} FortuneTellerTalkStep;

/* What its line function gives: the message file's name (an address) and the message. */
typedef struct FortuneTellerLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} FortuneTellerLine;

/* The lines of "sp_npc_panther". */
#define FORTUNE_TELLER_LINE_OFFER 0x01            /* no reading of the day's luck yet today */
#define FORTUNE_TELLER_LINE_OFFER_3 0x03          /* answered as 0x01 */
#define FORTUNE_TELLER_LINE_OFFER_FRIENDSHIP 0x05 /* the luck read today, not the friendship */
#define FORTUNE_TELLER_LINE_NO_BELLS 0x06         /* the player cannot pay 100 bells */
#define FORTUNE_TELLER_LINE_WHICH 0x07            /* paid: which reading */
#define FORTUNE_TELLER_LINE_WHICH_AGAIN 0x08      /* that reading was given today */
#define FORTUNE_TELLER_LINE_ASK_NAME 0x09         /* ends with the name screen */
#define FORTUNE_TELLER_LINE_NAME_TAKEN 0x0a       /* the villager's name in part 0 */
#define FORTUNE_TELLER_LINE_NO_NAME 0x0b          /* ends with the name screen again */
#define FORTUNE_TELLER_LINE_FRIENDSHIP 0x0c       /* the friendship reading begins */
#define FORTUNE_TELLER_LINE_LUCK 0x0d             /* the luck reading begins */
#define FORTUNE_TELLER_LINE_DRAW 0x0e             /* begins with music value 0; ends drawing a card */
#define FORTUNE_TELLER_LINE_PAY 0x10              /* after the meaning: the 100 bells taken */
#define FORTUNE_TELLER_LINE_BOTH_READ 0x11        /* both readings given today */
#define FORTUNE_TELLER_LINE_CLOSED 0x13           /* before 6 a.m.: ends with state 3 */
#define FORTUNE_TELLER_LINE_OFFER_CLEARING 0x14   /* the clearing of the luck for 10,000 bells */
#define FORTUNE_TELLER_LINE_NO_BELLS_CLEARING 0x15
#define FORTUNE_TELLER_LINE_PAID 0x16
#define FORTUNE_TELLER_LINE_CLEARING 0x17 /* begins with music value 0 */
#define FORTUNE_TELLER_LINE_CLEARED 0x18  /* ends taking 10,000 bells, the luck cleared */
#define FORTUNE_TELLER_LINE_ALL_DONE 0x19 /* both readings and the clearing done today */
#define FORTUNE_TELLER_LINE_CARDS 0x1a
#define FORTUNE_TELLER_LINE_CARDS_REVERSED 0x2c /* added to the line of a reversed card */
#define FORTUNE_TELLER_LINE_MEANINGS 0x72
#define FORTUNE_TELLER_LINE_MEANINGS_REVERSED 0x16

/* The text classes: a wide text of 10 characters (vtable 0x0226142c) and an 8-bit text of 22
 * bytes (vtable 0x02261414), on main's text bases (text_base.h). */
#define FORTUNE_WIDE_TEXT_CAPACITY 10
#define FORTUNE_TEXT_CAPACITY 22

typedef struct FortuneWideText {
    const TextVtable *vtable;              /* 0x00: data_ov045_0226142c */
    u8 attributes[0x0a];                   /* 0x04: the wide text base's */
    u16 chars[FORTUNE_WIDE_TEXT_CAPACITY]; /* 0x0e */
    u8 unk_22[2];
} FortuneWideText;

typedef struct FortuneText {
    const TextVtable *vtable;          /* 0x00: data_ov045_02261414 */
    u32 length;                        /* 0x04: the text base's */
    u8 attributes[0x0a];               /* 0x08 */
    char chars[FORTUNE_TEXT_CAPACITY]; /* 0x12 */
} FortuneText;

int FortuneWideText_Chars(int text);
int FortuneWideText_Capacity(void);
void *FortuneWideText_Delete(void *text);
FortuneWideText *FortuneWideText_Destruct(FortuneWideText *text);
void *FortuneWideText_Construct(void *text);
int FortuneText_Chars(int text);
int FortuneText_Capacity(void);
void *FortuneText_Delete(FortuneText *text);
void *FortuneText_Destruct(void *text);
void *FortuneText_Construct(void *text);

void FortuneTellerTalk_TakeName(FortuneTellerTalk *talk);
void FortuneTellerTalk_SetSequence(FortuneTellerTalk *talk, unsigned long sequence);
void FortuneTellerTalk_RunCommandSequence(FortuneTellerTalk *talk);
void FortuneTellerTalk_RunStepSequence(FortuneTellerTalk *talk);
void FortuneTellerTalk_OnAnswer(FortuneTellerTalk *talk);
void FortuneTellerTalk_OnLineBegins(unsigned char *talk);
void FortuneTellerTalk_OnLineEnded(FortuneTellerTalk *talk);
void FortuneTellerTalk_Line(FortuneTellerTalk *talk, FortuneTellerLine *out);
void FortuneTellerTalk_Begin(FortuneTellerTalk *talk, void *owner);
void FortuneTellerTalk_SetTalkStyle(FortuneTellerTalk *talk, int style);
void *FortuneTellerTalk_Delete(void *talk);
void *FortuneTellerTalk_Destroy(void *talk);
FortuneTellerTalk *FortuneTellerTalk_Construct(FortuneTellerTalk *talk);

#endif
