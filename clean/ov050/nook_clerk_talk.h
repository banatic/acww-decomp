/* The clerks' talk scene (NookClerkTalk, nook_clerk.h; class vtable data_ov050_02265b14,
 * derived from the scene class 0x020d9ff8).
 *
 * Its vtable slots, beyond the scene's: 0x00 and 0x04 its destructors, 0x08 its reset, 0x14 a
 * line ended (NookClerkTalk_OnLineEnded), 0x18 the player's answer (NookClerkTalk_OnAnswer),
 * 0x78 the line the talk starts with (NookClerkTalk_Line), 0x84 a command of the scene ended
 * (NookClerkTalk_RunSequence); 0x88 to 0xa4 the job's first line by the type of the errand
 * block's object (types 0xb to 0x12, NookClerkTalk_JobLine*), and 0xa8 the job's line ends
 * (NookClerkTalk_OnJobLineEnded).
 *
 * Its message files: "sp_npc_raccoon" (Tom Nook's lines), "sp_npc_twins" (the twins'),
 * "sp_npc_drama2" (Tom Nook's dated events of kind 3) and "sp_etc_sequence5_1" (the part-time
 * job's). The answers and the ends of lines go to handlers in tables keyed by the line shown
 * (the receiver's message, byte 0x1e); a handler that asks for a line puts it in
 * NookClerkTalk.line, which the dispatcher then shows from the file of the talk.
 *
 * What the talk does:
 * - an item on display: its price (the store's price, ItemTraits_StorePrice) and name, the
 *   pattern of a roof paint; bought when the player has a free pocket slot and the bells
 *   (NookClerkTalk_Buy); wallpaper and carpets can be tried on in the room first;
 * - the player's items sold (the pockets' screen in mode 0x1d, sequence 0): a quarter of each
 *   one's price, turnips at today's price (not on Sunday), fossils by their assessed kind;
 * - an order from the catalog (the screen in mode 0x3e, sequence 1), sent by mail;
 * - the roof's paint picked (data_ov050_022650b4) and the house loan's payments;
 * - an errand's item handed over (the pockets' screen, sequence 2);
 * - the part-time job: the uniform (item 0x11a8), the errands of the villager part's block 0
 *   (main's villager_part.h, types 11 to 18) with their items 0x1561, 0x1563, 0x1564 and
 *   0x1020, the items it hands out (0x14fe to 0x1512 and 0x151d) and the job's end. */
#ifndef CLEAN_OV050_NOOK_CLERK_TALK_H
#define CLEAN_OV050_NOOK_CLERK_TALK_H

#include "main/villager_part.h"
#include "nook_clerk.h"
#include "types.h"

/* NookClerkTalk.sequence, a member function from data_ov050_02265ed8 (filled on first use). */
#define NOOK_CLERK_SEQUENCE_SELL 0
#define NOOK_CLERK_SEQUENCE_ORDER 1
#define NOOK_CLERK_SEQUENCE_ERRAND 2
#define NOOK_CLERK_SEQUENCES 3

/* The talk's functions (nook_clerk_talk.c), in address order. */
void NookClerkTalk_Buy(NookClerkTalk *talk);
void NookClerkTalk_OnAnswerJobSlot(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnJobAnswer(NookClerkTalk *talk, int arg);
void NookClerkTalk_OnDatedAnswer(NookClerkTalk *talk);
void NookClerkTalk_OnAnswerPaintRow3(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnAnswerPaintRow2(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnAnswerPaintRow1(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnAnswerPaintRow0(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnAnswerSale(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnAnswerPackage(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnAnswerPaint(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnAnswerTryOn(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnAnswerEndTryOn(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnAnswerBuy(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnAnswerOrder(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnAnswerConvert(int unused, int answer);
void NookClerkTalk_OnAnswerErrand(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnAnswerCommon(NookClerkTalk *talk, int answer);
void NookClerkTalk_OnPlainAnswer(NookClerkTalk *talk, int arg);
void NookClerkTalk_OnAnswer(NookClerkTalk *talk, int arg);
void NookClerkTalk_PickPaint(NookClerkTalk *talk, int row, unsigned int answer);
void NookClerkTalk_PayLoanLine(void);
void NookClerkTalk_ReactToPurchase(NookClerkTalk *talk);
void NookClerkTalk_PaintBought(NookClerkTalk *talk);
void NookClerkTalk_OpenOrder(NookClerkTalk *talk);
void NookClerkTalk_PaySale(NookClerkTalk *talk);
void NookClerkTalk_OpenSell(NookClerkTalk *talk);
void NookClerkTalk_PackageDone(NookClerkTalk *talk);
void NookClerkTalk_GivePackage(NookClerkTalk *talk);
void NookClerkTalk_OnLineEnded(NookClerkTalk *talk);
void NookClerkTalk_Line(NookClerkTalk *talk, NookClerkLine *out);
void NookClerkTalk_JobLead(NookClerkTalk *talk, int unused);
void NookClerkTalk_JobEnd(int unused, int part);
void NookClerkTalk_JobPayLoan(NookClerkTalk *talk, int unused);
void NookClerkTalk_JobErrand18(NookClerkTalk *talk, VillagerPart *part);
void NookClerkTalk_JobShowItem1564(NookClerkTalk *talk, int unused);
void NookClerkTalk_JobGive1564(NookClerkTalk *talk, VillagerPart *part);
void NookClerkTalk_JobShowItem1561(NookClerkTalk *talk, int unused);
void NookClerkTalk_JobGive1561(NookClerkTalk *talk, VillagerPart *part);
void NookClerkTalk_JobStep0(NookClerkTalk *talk, VillagerPart *part);
void NookClerkTalk_JobStep0Again(NookClerkTalk *talk, VillagerPart *part);
void NookClerkTalk_JobAskAgain(NookClerkTalk *talk, int unused);
void NookClerkTalk_JobGive1020(NookClerkTalk *talk, int unused);
void NookClerkTalk_JobSecondPick(NookClerkTalk *talk, VillagerPart *part);
void NookClerkTalk_JobShowItem1563(NookClerkTalk *talk, int unused);
void NookClerkTalk_JobGive1563(NookClerkTalk *talk, VillagerPart *part);
void NookClerkTalk_JobType13(int unused, VillagerPart *part);
void NookClerkTalk_JobClearFlag(int unused, VillagerPart *part);
void NookClerkTalk_JobType12(NookClerkTalk *talk, VillagerPart *part);
void NookClerkTalk_JobCountFree(NookClerkTalk *talk, VillagerPart *part);
void NookClerkTalk_JobShowUniform(NookClerkTalk *talk, VillagerPart *part);
void NookClerkTalk_JobGiveUniform(NookClerkTalk *talk, VillagerPart *part);
void NookClerkTalk_OnJobLineEnded(NookClerkTalk *talk, int unused);
void NookClerkTalk_JobLine12(NookClerkTalk *talk, NookClerkLine *out);
void NookClerkTalk_JobLine11(NookClerkTalk *talk, NookClerkLine *out);
void NookClerkTalk_JobLine10(NookClerkTalk *talk, NookClerkLine *out);
void NookClerkTalk_JobLine0F(NookClerkTalk *talk, NookClerkLine *out);
void NookClerkTalk_JobLine0E(NookClerkTalk *talk, NookClerkLine *out);
void NookClerkTalk_JobLine0D(NookClerkTalk *talk, NookClerkLine *out);
void NookClerkTalk_JobLine0C(NookClerkTalk *talk, NookClerkLine *out);
void NookClerkTalk_JobLine0B(NookClerkTalk *talk, NookClerkLine *out);
int NookClerkTalk_JobNotInUniform(void *talk, NookClerkLine *out);
void NookClerkTalk_JobGiveItems(NookClerkTalk *talk);
int NookClerkTalk_IsEmptySlot(unsigned short *item);
int NookClerkTalk_LoanNews(NookClerkTalk *talk);
unsigned long NookClerkTalk_Mode(NookClerkTalk *talk);
void NookClerkTalk_SetMode(NookClerkTalk *talk, unsigned long mode);
void NookClerkTalk_Begin(NookClerkTalk *talk, NookClerk *owner);
void NookClerkTalk_Reset(NookClerkTalk *talk);
void *NookClerkTalk_DestructDelete(NookClerkTalk *talk);
void *NookClerkTalk_Destruct(NookClerkTalk *talk);
void *NookClerkTalk_Construct(NookClerkTalk *talk);
void NookClerkTalk_TakeErrandItem(NookClerkTalk *talk);
unsigned short NookClerkTalk_IsErrandItem(unsigned short *item, int state);
void NookClerkTalk_PriceOrder(NookClerkTalk *talk);
void NookClerkTalk_PriceSale(NookClerkTalk *talk);
void NookClerkTalk_SetSequence(NookClerkTalk *talk, int sequence);
void NookClerkTalk_RunSequence(NookClerkTalk *talk);

#endif
