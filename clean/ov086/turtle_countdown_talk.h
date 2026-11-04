/* The talk scene of overlay 86's turtle (turtle_countdown.h: TurtleCountdownTalk, vtable 0x022792fc).
 *
 * Its vtable slots, beyond those of main's scene class 0x020d9ff8: 0x00 and 0x04 its
 * destructors, 0x08 the scene base's reset, 0x14 a line ended (TurtleCountdownTalk_OnLineEnded), 0x18
 * the player's answer (TurtleCountdownTalk_OnAnswer) and 0x78 the line the talk starts with
 * (TurtleCountdownTalk_FirstLine).
 *
 * What he does in it, by the lines of "sp_npc_turtle6" (TURTLE_COUNTDOWN_LINE_*):
 * - in December his line follows the clock: the part of the day, then the last hour of the
 *   year by the minute (23:00, 23:30, 23:55, 23:59);
 * - in January (before 6:00 other lines) he offers a fortune: a letter of "ev_fortune" whose
 *   parts are drawn from "st_fortune" and "st_fortune2"; flag 4 of main's object at
 *   data_021d27ac then says it was written;
 * - after most lines, when the pockets have a free slot, at random he gives the item 0x137d.
 * When the pockets hold the item 0x37e0 the talk is instead line 0 of the common file
 * "sp_npc_turtle" (TurtleCountdownTalk.item_slot), where he takes it and gives the item 0x1559. */
#ifndef CLEAN_OV086_TURTLE_COUNTDOWN_TALK_H
#define CLEAN_OV086_TURTLE_COUNTDOWN_TALK_H

#include "turtle_countdown.h"
#include "types.h"

/* What the first line function gives: the message file's name (an address) and the message. */
typedef struct TurtleCountdownLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} TurtleCountdownLine;

/* A part of the fortune letter: the file its message comes from and the part it fills. */
typedef struct TurtleCountdownFortunePart {
    u32 name; /* the file's name (an address) */
    s32 part; /* the letter text's part (MailText_SetPartText) */
} TurtleCountdownFortunePart;

#define TURTLE_COUNTDOWN_FORTUNE_PARTS 4

/* TurtleCountdownTalk.item_slot when not looked for yet, and once the exchange of item 0x37e0 is
 * over. */
#define TURTLE_COUNTDOWN_TALK_SLOT_UNKNOWN (-1)
#define TURTLE_COUNTDOWN_TALK_SLOT_DONE (-2)

/* No line (the lines are bytes). */
#define TURTLE_COUNTDOWN_NO_LINE 0xff

/* The lines of "sp_npc_turtle6". */
#define TURTLE_COUNTDOWN_LINE_DECEMBER 0x00       /* 0x00-0x02 in the morning; 0x00 also at random later */
#define TURTLE_COUNTDOWN_LINE_AFTERNOON 0x03      /* 0x03-0x04 (or 0x00) */
#define TURTLE_COUNTDOWN_LINE_EVENING 0x05        /* 0x05-0x06 (or 0x00), before 23:00 */
#define TURTLE_COUNTDOWN_LINE_HOUR_LEFT 0x07      /* 0x07-0x08 (or 0x00), 23:00-23:29 */
#define TURTLE_COUNTDOWN_LINE_HALF_HOUR_LEFT 0x09 /* 0x09-0x0b, 23:30-23:54 */
#define TURTLE_COUNTDOWN_LINE_MINUTES_LEFT 0x0c   /* 0x0c-0x0d, 23:55-23:58 */
#define TURTLE_COUNTDOWN_LINE_LAST_MINUTE 0x0e    /* 0x0e-0x0f, 23:59 */
#define TURTLE_COUNTDOWN_LINE_EARLY 0x10          /* 0x10-0x12: not December, before 6:00 */
#define TURTLE_COUNTDOWN_LINE_OFFER_FORTUNE 0x13  /* ends with the fortune letter */
#define TURTLE_COUNTDOWN_LINE_NO_LETTER 0x14      /* no free letter in the pockets */
#define TURTLE_COUNTDOWN_LINE_FORTUNE 0x15        /* the letter written */
#define TURTLE_COUNTDOWN_LINE_AFTER_FORTUNE 0x16  /* 0x16-0x18 */
#define TURTLE_COUNTDOWN_LINE_GIFT 0x19           /* 0x19-0x1b: end with the item 0x137d given */
#define TURTLE_COUNTDOWN_LINE_GIVEN 0x1c          /* 0x1c-0x1e */

/* The lines of the common file "sp_npc_turtle" while the pockets hold the item 0x37e0. */
#define TURTLE_COUNTDOWN_COMMON_LINE_ASK 0x00   /* answered 0: the item taken */
#define TURTLE_COUNTDOWN_COMMON_LINE_DONE 0x01  /* ends the exchange */
#define TURTLE_COUNTDOWN_COMMON_LINE_TAKEN 0x02 /* ends with the item 0x1559 given */
#define TURTLE_COUNTDOWN_COMMON_LINE_GIVEN 0x04 /* ends the exchange */

void TurtleCountdownTalk_OnAnswer(TurtleCountdownTalk *talk);
void TurtleCountdownTalk_OnLineEnded(TurtleCountdownTalk *talk);
void TurtleCountdownTalk_FirstLine(TurtleCountdownTalk *talk, TurtleCountdownLine *out);
void TurtleCountdownTalk_Begin(TurtleCountdownTalk *talk, TurtleCountdown *owner);
void *TurtleCountdownTalk_Delete(void *talk);
void *TurtleCountdownTalk_Destroy(void *talk);
TurtleCountdownTalk *TurtleCountdownTalk_Construct(TurtleCountdownTalk *talk);

#endif
