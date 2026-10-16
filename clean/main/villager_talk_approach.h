/* The approaches of a town villager's talk scene (VillagerTalk, villager_talk.h): the villager
 * comes up to the player with an offer, drawn by VillagerTalkApproach_Line among nine member
 * functions with the weights of data_020c8e68. Each says 1 when it applies, after drawing a line
 * of its text set ("ap_*") for the villager's personality into the talk's text and message; one
 * that says 0 takes no further part. When all are out, one of the first two (which always
 * apply) is run.
 *
 * The nine, in the table's order: the catchphrase ("ap_habit"), a letter of another player the
 * villager holds ("ap_mail"), the villager's picture ("ap_item"), the nickname ("ap_nickn"), a
 * gift from the villager's items ("ap_present1"), a gift ("ap_present2"), buying from the player
 * ("ap_buy"), a trade ("ap_trade") and selling to the player ("ap_sell").
 *
 * The talk keeps the item the player gives at 0x124, the item the player gets at 0x19c (with
 * 0x19e set when it comes from the villager's items) and the bells at 0x1a0. Prices are the
 * item's worth (func_0204c878) scaled by a random 0.8 to 1.0 (in 4096ths) and then rounded to
 * tens (VillagerTalkApproach_RoundBells). */
#ifndef CLEAN_MAIN_VILLAGER_TALK_APPROACH_H
#define CLEAN_MAIN_VILLAGER_TALK_APPROACH_H

#include "types.h"
#include "villager_talk.h"

#define VILLAGER_TALK_APPROACH_COUNT 9

void VillagerTalkApproach_Line(VillagerTalk *talk, VillagerTalkLine *out);
int VillagerTalkApproach_Sell(VillagerTalk *talk);
int VillagerTalkApproach_Trade(VillagerTalk *talk);
int VillagerTalkApproach_Buy(VillagerTalk *talk);
int VillagerTalkApproach_RoundBells(int bells);
void VillagerTalkApproach_PickPocketItem(u16 *out, unsigned int mode);
int VillagerTalkApproach_Present2(VillagerTalk *talk);
int VillagerTalkApproach_Present1(VillagerTalk *talk);
int VillagerTalkApproach_Mail(VillagerTalk *talk);
int VillagerTalkApproach_Nickname(VillagerTalk *talk);
int VillagerTalkApproach_Picture(VillagerTalk *talk);
int VillagerTalkApproach_Catchphrase(VillagerTalk *talk);

#endif
