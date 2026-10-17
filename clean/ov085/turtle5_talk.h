/* The talk scene of overlay 85's turtle (turtle5.h: Turtle5Talk, vtable 0x0227945c).
 *
 * Its vtable slots, beyond those of main's scene class 0x020d9ff8: 0x00 and 0x04 its
 * destructors, 0x08 the scene base's reset, 0x14 a line ended (Turtle5Talk_OnLineEnded), 0x18
 * the player's answer (Turtle5Talk_OnAnswer), 0x78 the line the talk starts with
 * (Turtle5Talk_FirstLine) and 0x88 the list of villagers offered (Turtle5Talk_OfferVillagers).
 *
 * What he does in it, by the lines of "sp_npc_turtle5" (TURTLE5_LINE_*), with main's event
 * winner record (data_021f3aa4, event_winner.h):
 * - on days 0-5 of event 0x11 the player may name one of the town's villagers, from a list of
 *   four at a time; the one named is the record's NpcId at 0x2e (cleared again before the
 *   player's first talk of a day) and, at random half the time, its villager;
 * - on day 6 the first talk names the record's villager (else the player's fondest villager)
 *   the winner: in the talk, on the town's board ("bbs_snowfes") and in mail part 0; flag 0x11
 *   of the state block then says it was.
 * When the pockets hold the item 0x37e0 the talk is instead line 0 of the common file
 * "sp_npc_turtle" (Turtle5Talk.item_slot), where he takes it and gives the item 0x1559. */
#ifndef CLEAN_OV085_TURTLE5_TALK_H
#define CLEAN_OV085_TURTLE5_TALK_H

#include "turtle5.h"
#include "types.h"

/* What the first line function gives: the message file's name (an address) and the message. */
typedef struct Turtle5Line {
    u32 text;
    u8 message;
    u8 unk_05[3];
} Turtle5Line;

/* Turtle5Talk.item_slot when not looked for yet, and once the exchange of item 0x37e0 is
 * over. */
#define TURTLE5_TALK_SLOT_UNKNOWN (-1)
#define TURTLE5_TALK_SLOT_DONE (-2)

/* No line (the lines are bytes). */
#define TURTLE5_NO_LINE 0xff

/* The lines of "sp_npc_turtle5". */
/* The first talk of a day: 0 on day 0, 1 on days 1-2, 2 on days 3-4, 3 on day 5. */
#define TURTLE5_LINE_DAY_0 0x00
#define TURTLE5_LINE_DAY_1 0x01
#define TURTLE5_LINE_DAY_3 0x02
#define TURTLE5_LINE_DAY_5 0x03
#define TURTLE5_LINE_ASK 0x04         /* later talks: answered 0, 0x07-0x08, else 0x05-0x06 */
#define TURTLE5_LINE_DECLINED 0x05    /* 0x05-0x06 */
#define TURTLE5_LINE_NAME 0x07        /* 0x07-0x08: end with the list of villagers */
#define TURTLE5_LINE_NAMED 0x09       /* 0x09-0x0a: a villager named */
#define TURTLE5_LINE_NAMED_TODAY 0x0b /* 0x0b-0x0e: a villager was named today (its name in part 0) */
#define TURTLE5_LINE_RESULT 0x0f      /* the last day's first talk: ends with the winner named */
#define TURTLE5_LINE_WINNER 0x10
#define TURTLE5_LINE_AFTER_RESULT 0x11 /* 0x11-0x13: the last day, later (the winner in part 1) */
#define TURTLE5_LINE_MORE 0x14         /* 0x14-0x15: the next villagers; end with the list */
#define TURTLE5_LINE_MORE_AGAIN 0x15

/* The lines of the common file "sp_npc_turtle" while the pockets hold the item 0x37e0. */
#define TURTLE5_COMMON_LINE_ASK 0x00   /* answered 0: the item taken */
#define TURTLE5_COMMON_LINE_DONE 0x01  /* ends the exchange */
#define TURTLE5_COMMON_LINE_TAKEN 0x02 /* ends with the item 0x1559 given */
#define TURTLE5_COMMON_LINE_GIVEN 0x04 /* ends the exchange */

void Turtle5Talk_OnAnswer(Turtle5Talk *talk);
void Turtle5Talk_OnLineEnded(Turtle5Talk *talk);
void Turtle5Talk_FirstLine(Turtle5Talk *talk, Turtle5Line *out);
void Turtle5Talk_Begin(Turtle5Talk *talk, Turtle5 *owner);
void *Turtle5Talk_Delete(void *talk);
void *Turtle5Talk_Destroy(void *talk);
Turtle5Talk *Turtle5Talk_Construct(Turtle5Talk *talk);
void Turtle5Talk_OfferVillagers(Turtle5Talk *talk);

#endif
