/* The talk scene of overlay 85's turtle (turtle_snow_festival.h: TurtleSnowFestivalTalk, vtable 0x0227945c).
 *
 * Its vtable slots, beyond those of main's scene class 0x020d9ff8: 0x00 and 0x04 its
 * destructors, 0x08 the scene base's reset, 0x14 a line ended (TurtleSnowFestivalTalk_OnLineEnded), 0x18
 * the player's answer (TurtleSnowFestivalTalk_OnAnswer), 0x78 the line the talk starts with
 * (TurtleSnowFestivalTalk_FirstLine) and 0x88 the list of villagers offered (TurtleSnowFestivalTalk_OfferVillagers).
 *
 * What he does in it, by the lines of "sp_npc_turtle5" (TURTLE_SNOW_FESTIVAL_LINE_*), with main's event
 * winner record (data_021f3aa4, event_winner.h):
 * - on days 0-5 of event 0x11 the player may name one of the town's villagers, from a list of
 *   four at a time; the one named is the record's NpcId at 0x2e (cleared again before the
 *   player's first talk of a day) and, at random half the time, its villager;
 * - on day 6 the first talk names the record's villager (else the player's fondest villager)
 *   the winner: in the talk, on the town's board ("bbs_snowfes") and in mail part 0; flag 0x11
 *   of the state block then says it was.
 * When the pockets hold the item 0x37e0 the talk is instead line 0 of the common file
 * "sp_npc_turtle" (TurtleSnowFestivalTalk.item_slot), where he takes it and gives the item 0x1559. */
#ifndef CLEAN_OV085_TURTLE_SNOW_FESTIVAL_TALK_H
#define CLEAN_OV085_TURTLE_SNOW_FESTIVAL_TALK_H

#include "turtle_snow_festival.h"
#include "types.h"

/* What the first line function gives: the message file's name (an address) and the message. */
typedef struct TurtleSnowFestivalLine {
    u32 text;
    u8 message;
    u8 unk_05[3];
} TurtleSnowFestivalLine;

/* TurtleSnowFestivalTalk.item_slot when not looked for yet, and once the exchange of item 0x37e0 is
 * over. */
#define TURTLE_SNOW_FESTIVAL_TALK_SLOT_UNKNOWN (-1)
#define TURTLE_SNOW_FESTIVAL_TALK_SLOT_DONE (-2)

/* No line (the lines are bytes). */
#define TURTLE_SNOW_FESTIVAL_NO_LINE 0xff

/* The lines of "sp_npc_turtle5". */
/* The first talk of a day: 0 on day 0, 1 on days 1-2, 2 on days 3-4, 3 on day 5. */
#define TURTLE_SNOW_FESTIVAL_LINE_DAY_0 0x00
#define TURTLE_SNOW_FESTIVAL_LINE_DAY_1 0x01
#define TURTLE_SNOW_FESTIVAL_LINE_DAY_3 0x02
#define TURTLE_SNOW_FESTIVAL_LINE_DAY_5 0x03
#define TURTLE_SNOW_FESTIVAL_LINE_ASK 0x04         /* later talks: answered 0, 0x07-0x08, else 0x05-0x06 */
#define TURTLE_SNOW_FESTIVAL_LINE_DECLINED 0x05    /* 0x05-0x06 */
#define TURTLE_SNOW_FESTIVAL_LINE_NAME 0x07        /* 0x07-0x08: end with the list of villagers */
#define TURTLE_SNOW_FESTIVAL_LINE_NAMED 0x09       /* 0x09-0x0a: a villager named */
#define TURTLE_SNOW_FESTIVAL_LINE_NAMED_TODAY 0x0b /* 0x0b-0x0e: a villager was named today (its name in part 0) */
#define TURTLE_SNOW_FESTIVAL_LINE_RESULT 0x0f      /* the last day's first talk: ends with the winner named */
#define TURTLE_SNOW_FESTIVAL_LINE_WINNER 0x10
#define TURTLE_SNOW_FESTIVAL_LINE_AFTER_RESULT 0x11 /* 0x11-0x13: the last day, later (the winner in part 1) */
#define TURTLE_SNOW_FESTIVAL_LINE_MORE 0x14         /* 0x14-0x15: the next villagers; end with the list */
#define TURTLE_SNOW_FESTIVAL_LINE_MORE_AGAIN 0x15

/* The lines of the common file "sp_npc_turtle" while the pockets hold the item 0x37e0. */
#define TURTLE_SNOW_FESTIVAL_COMMON_LINE_ASK 0x00   /* answered 0: the item taken */
#define TURTLE_SNOW_FESTIVAL_COMMON_LINE_DONE 0x01  /* ends the exchange */
#define TURTLE_SNOW_FESTIVAL_COMMON_LINE_TAKEN 0x02 /* ends with the item 0x1559 given */
#define TURTLE_SNOW_FESTIVAL_COMMON_LINE_GIVEN 0x04 /* ends the exchange */

void TurtleSnowFestivalTalk_OnAnswer(TurtleSnowFestivalTalk *talk);
void TurtleSnowFestivalTalk_OnLineEnded(TurtleSnowFestivalTalk *talk);
void TurtleSnowFestivalTalk_FirstLine(TurtleSnowFestivalTalk *talk, TurtleSnowFestivalLine *out);
void TurtleSnowFestivalTalk_Begin(TurtleSnowFestivalTalk *talk, TurtleSnowFestival *owner);
void *TurtleSnowFestivalTalk_Delete(void *talk);
void *TurtleSnowFestivalTalk_Destroy(void *talk);
TurtleSnowFestivalTalk *TurtleSnowFestivalTalk_Construct(TurtleSnowFestivalTalk *talk);
void TurtleSnowFestivalTalk_OfferVillagers(TurtleSnowFestivalTalk *talk);

#endif
