/* The talk scene of overlay 84's turtle (turtle4.h: Turtle4Talk, vtable 0x0227941c).
 *
 * Its vtable slots, beyond those of main's scene class 0x020d9ff8: 0x00 and 0x04 its
 * destructors, 0x08 the scene base's reset, 0x14 a line ended (Turtle4Talk_OnLineEnded), 0x18
 * the player's answer (Turtle4Talk_OnAnswer) and 0x78 the line the talk starts with
 * (Turtle4Talk_FirstLine).
 *
 * What he does in it, by the lines of "sp_npc_turtle4" (TURTLE4_LINE_*):
 * - the first talk of the day greets the player by the Saturday it is (the first, the last of
 *   the month or another);
 * - later talks hand out one of the items 0x137e and 0x137f (the one the pockets lack), at
 *   most ten in all (the tally of the player record's field 0x2416, PlayerField2416);
 * - once the player has both (or holds one in hand), he offers a fortune: a letter of
 *   "ev_fortune" whose parts are drawn from "st_fortune" and "st_fortune2"; flag 3 of main's
 *   object at data_021d27ac then says it was written.
 * When the pockets hold the item 0x37e0 the talk is instead line 0 of the common file
 * "sp_npc_turtle" (Turtle4Talk.item_slot), where he takes it and gives the item 0x1559. */
#ifndef CLEAN_OV084_TURTLE4_TALK_H
#define CLEAN_OV084_TURTLE4_TALK_H

#include "turtle4.h"
#include "types.h"

/* What the first line function gives: the message file's name (an address) and the message. */
typedef struct Turtle4Line {
    u32 text;
    u8 message;
    u8 unk_05[3];
} Turtle4Line;

/* A part of the fortune letter: the file its message comes from and the part it fills. */
typedef struct Turtle4FortunePart {
    u32 name; /* the file's name (an address) */
    s32 part; /* the letter text's part (MailText_SetPartText) */
} Turtle4FortunePart;

#define TURTLE4_FORTUNE_PARTS 4

/* Turtle4Talk.item_slot when not looked for yet, and once the exchange of item 0x37e0 is
 * over. */
#define TURTLE4_TALK_SLOT_UNKNOWN (-1)
#define TURTLE4_TALK_SLOT_DONE (-2)

/* No line (the lines are bytes). */
#define TURTLE4_NO_LINE 0xff

/* The lines of "sp_npc_turtle4". */
#define TURTLE4_LINE_FIRST_SATURDAY 0x00 /* the first talk of the day, on the month's first Saturday */
#define TURTLE4_LINE_SATURDAY 0x01       /* ... on another Saturday */
#define TURTLE4_LINE_LAST_SATURDAY 0x02  /* ... on its last Saturday; these and 0x06 end with a gift */
#define TURTLE4_LINE_GIVEN 0x03          /* the item given (byte 0x1c of the player 0) */
#define TURTLE4_LINE_GIVEN_OTHER 0x04    /* the item given (byte 0x1c of the player not 0) */
#define TURTLE4_LINE_NO_ROOM 0x05        /* the pockets are full */
#define TURTLE4_LINE_NOT_BOTH 0x06       /* later talks: the player lacks one of the two items */
#define TURTLE4_LINE_OFFER_FORTUNE 0x07  /* answered 0: the fortune letter */
#define TURTLE4_LINE_FORTUNE 0x09        /* the letter written; ends with the letters' motion */
#define TURTLE4_LINE_FORTUNE_SENT 0x0a
#define TURTLE4_LINE_ALL_GIVEN 0x0b     /* ten items were given */
#define TURTLE4_LINE_NO_LETTER 0x0c     /* no free letter in the pockets */
#define TURTLE4_LINE_AFTER_FORTUNE 0x0d /* 0x0d-0x10: at random, after the fortune */

/* The lines of the common file "sp_npc_turtle" while the pockets hold the item 0x37e0. */
#define TURTLE4_COMMON_LINE_ASK 0x00   /* answered 0: the item taken */
#define TURTLE4_COMMON_LINE_DONE 0x01  /* ends the exchange */
#define TURTLE4_COMMON_LINE_TAKEN 0x02 /* ends with the item 0x1559 given */
#define TURTLE4_COMMON_LINE_GIVEN 0x04 /* ends the exchange */

void Turtle4Talk_OnAnswer(Turtle4Talk *talk);
void Turtle4Talk_OnLineEnded(Turtle4Talk *talk);
void Turtle4Talk_FirstLine(Turtle4Talk *talk, Turtle4Line *out);
void Turtle4Talk_Begin(Turtle4Talk *talk, Turtle4 *owner);
void *Turtle4Talk_Delete(void *talk);
void *Turtle4Talk_Destroy(void *talk);
Turtle4Talk *Turtle4Talk_Construct(Turtle4Talk *talk);

#endif
