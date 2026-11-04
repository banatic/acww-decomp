/* Two lists of 15 items kept in the large block of the game's state (state_block.h, at
 * data_021dc7a8): the lost and found ("list A", at 0x172c0, data_021f3a68) and the recycle bin
 * ("list B", at 0x172de, data_021f3a86); overlay 110's box shows them with the art "lost.bch"
 * and "garb.bch" (ov110/public_box.h), and the gatekeeper tells how many items the lost and
 * found holds (ov004/gatekeeper2.c).
 * They are also what player messages 3 and 4 carry between linked consoles (ov100's
 * pockets_box.h). 0xfff1 marks an empty place.
 *
 * The lost and found starts a new town with three random items (TownItemLists_StartLostAndFound); on each day that
 * passes it may get one more (TownItemLists_FillLostAndFound), until ten places are taken; an item a
 * snowman's map object replaces goes to it, the oldest item giving way when it is full
 * (TownItemLists_PushLostAndFound).
 *
 * The recycle bin takes the items villagers give away from their houses (villager_house_items.h,
 * TownItemLists_AddRecycleBin); it is emptied when a Monday or a Thursday has begun since the last
 * day played (TownItemLists_EmptyRecycleBinOnDays). */
#ifndef CLEAN_MAIN_TOWN_ITEM_LISTS_H
#define CLEAN_MAIN_TOWN_ITEM_LISTS_H

#include "calendar.h" /* DateTime */
#include "types.h"

#define TOWN_ITEM_LIST_PLACES 15
#define TOWN_ITEM_LIST_NONE 0xfff1

void TownItemLists_EmptyRecycleBinOnDays(u16 *list, const DateTime *today, int days);
void TownItemLists_ClearRecycleBin(u16 *list);
void TownItemLists_DestructRecycleBin(void *list);
void TownItemLists_ConstructRecycleBin(void *list);
void TownItemLists_FillLostAndFound(u16 *list, int days);
void TownItemLists_StartLostAndFound(u16 *list);
void TownItemLists_ClearLostAndFound(u16 *list);
void TownItemLists_DestructLostAndFound(void *list);
void TownItemLists_ConstructLostAndFound(void *list);
int TownItemLists_PutRecycleBin(u32 place, u16 item);
int TownItemLists_RecycleBinItem(u32 place);
int TownItemLists_AddRecycleBin(int item);
int TownItemLists_CountLostAndFound(void);
int TownItemLists_AnyLostAndFound(void);
void TownItemLists_PushLostAndFound(u16 item);

#endif
