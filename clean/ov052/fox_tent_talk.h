/* The fox's talk scene in his tent (FoxTentTalk, fox_tent.h; class vtable 0x02261eb0, derived
 * from the scene class 0x020d9ff8): the line it starts with (slot 0x78, FoxTentTalk_Line), the
 * player's answers (slot 0x18, FoxTentTalk_OnAnswer) and what follows the end of a line (slot
 * 0x14, FoxTentTalk_OnLineEnd). Its lines are of "sp_npc_fox" (data_ov052_02261e50).
 *
 * FoxTentTalk.sequence picks the line a talk starts with (the table data_ov052_02261be0):
 *   0  0x06  greeting, as the player comes in;
 *   1  0x1c  at the exit, nothing sold in this visit;
 *   2  0x1b  at the exit, after a sale;
 *   3  0x07  not a member (the current player's record lacks flag 0xc): the membership's offer;
 *   4  0x12  the offer again;
 *   5  0x2c  a member with the item 0x34a8 in the pockets, unlinked: it is asked for;
 *   6  0x1a  the three items of the fox's shop are sold (each the marker 0x1547);
 *   7  0x14  the first talk of the day (the current player's daily bit 1);
 *   8  0x16  the last sale, to another player than the buyer (the buyer's name in slot 1);
 *   9  0x15  the last sale, to its buyer;
 *  10  0x17  the plain talk (one of four lines at random, 0x17 to 0x19 or 0x30);
 *  11  0x1e  (not set here);
 *  12  0x33  closing, before 6 a.m.
 * A member facing an item hears its name and price (twice the item's price) instead: 0x1d when
 * he told it already, else one of five offers (0x1e to 0x22), each said once before any again.
 *
 * Answering an offer with the first choice buys the item when the player can pay and has a free
 * pocket (one of five thanks, 0x24 to 0x28, after which the sale is made); else 0x29 (cannot
 * pay) or 0x2a (no room). The membership costs 3,000 bells (line 0x10, the card 0x149d). */
#ifndef CLEAN_OV052_FOX_TENT_TALK_H
#define CLEAN_OV052_FOX_TENT_TALK_H

#include "fox_tent.h"
#include "types.h"

/* FoxTentTalk.sequence. */
#define FOX_TENT_TALK_GREETING 0
#define FOX_TENT_TALK_EXIT 1
#define FOX_TENT_TALK_EXIT_AFTER_SALE 2
#define FOX_TENT_TALK_OFFER_MEMBERSHIP 3
#define FOX_TENT_TALK_OFFER_AGAIN 4
#define FOX_TENT_TALK_ASK_ITEM 5
#define FOX_TENT_TALK_SOLD_OUT 6
#define FOX_TENT_TALK_FIRST_TODAY 7
#define FOX_TENT_TALK_LAST_SALE_OTHER 8
#define FOX_TENT_TALK_LAST_SALE_OWN 9
#define FOX_TENT_TALK_PLAIN 10
#define FOX_TENT_TALK_11 11
#define FOX_TENT_TALK_CLOSING 12
#define FOX_TENT_TALK_SEQUENCES 13

/* What the talk starts with (its slot 0x78): the message file and the line. */
typedef struct FoxTentTalkStart {
    const char *name;
    u8 message;
    u8 unk_05[3];
} FoxTentTalkStart;

/* The class. */
FoxTentTalk *FoxTentTalk_Construct(FoxTentTalk *talk);
FoxTentTalk *FoxTentTalk_Destruct(FoxTentTalk *talk);
FoxTentTalk *FoxTentTalk_DestructDelete(FoxTentTalk *talk);
void FoxTentTalk_Reset(FoxTentTalk *talk);
void FoxTentTalk_Begin(FoxTentTalk *talk, FoxTent *owner);
u32 FoxTentTalk_Sequence(FoxTentTalk *talk);
void FoxTentTalk_SetSequence(FoxTentTalk *talk, u32 sequence);

/* Its lines. */
void FoxTentTalk_Line(FoxTentTalk *talk, FoxTentTalkStart *out);
void FoxTentTalk_OnAnswer(FoxTentTalk *talk);
void FoxTentTalk_OnLineEnd(FoxTentTalk *talk);
void FoxTentTalk_Sell(FoxTentTalk *talk);
int FoxTentTalk_ShopSoldOut(FoxTentTalk *talk);

/* Picking one of a set of variants, each once before any again. */
int FoxTent_PickUnused(int unused, const u8 *used, int count);
int FoxTent_CountUnused(int unused, const u8 *used, int count);

#endif
