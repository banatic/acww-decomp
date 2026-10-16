/* Items the town villagers' talk scenes (villager_talk.h) draw for a villager to want or give:
 * clothes of any style but one the villager names, and insects or fish of today's date.
 *
 * Clothes (0x11a8-0x12a7) go through func_02063414 with a style number 0-9 drawn from a mask
 * (VillagerRoster_PickBit). The two style bytes are the villager data's 0x29 and 0x2a
 * (VillagerData_Byte29); VillagerTalkPart_ReactToClothes (villager_talk_part.h) tells them
 * apart.
 *
 * Insects (func_0202d190, by month) and fish (func_0202cbdc, by month and day) are drawn from
 * five classes 0-4: each picker tries a range of classes, then others, until one gives an item.
 * The pickers are reached by an index 0-4 through two tables of the game's functions
 * (data_020c8efc for insects, data_020c8f10 for fish; index 2 has none) with the date of now. */
#ifndef CLEAN_MAIN_VILLAGER_TALK_PICKS_H
#define CLEAN_MAIN_VILLAGER_TALK_PICKS_H

#include "calendar.h"
#include "types.h"

#define VILLAGER_TALK_PICKS_TABLE 5

void VillagerTalkPick_ClothesNotStyle1(u16 *out, const u8 *styles, int clothes);
void VillagerTalkPick_ClothesOfStyleMask(u16 *out, int mask, int count, u8 *player, u8 which, int clothes);
void VillagerTalkPick_Fish(u16 *out, int unused, unsigned int index);
void VillagerTalkPick_Fish4(u16 *out, const DateTime *now);
void VillagerTalkPick_Fish3(u16 *out, const DateTime *now);
void VillagerTalkPick_Fish1(u16 *out, const DateTime *now);
void VillagerTalkPick_Fish0(u16 *out, const DateTime *now);
void VillagerTalkPick_Insect(u16 *out, int unused, unsigned int index);
void VillagerTalkPick_Insect4(u16 *out, const DateTime *now);
void VillagerTalkPick_Insect3(u16 *out, const DateTime *now);
void VillagerTalkPick_Insect1(u16 *out, const DateTime *now);
void VillagerTalkPick_Insect0(u16 *out, const DateTime *now);

#endif
