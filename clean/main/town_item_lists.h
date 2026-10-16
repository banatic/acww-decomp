/* Two lists of 15 items kept in the large block of the game's state (state_block.h, at
 * data_021dc7a8): list A at 0x172c0 (data_021f3a68) and list B at 0x172de (data_021f3a86).
 * They are also what player messages 3 and 4 carry between linked consoles (ov100's
 * pockets_box.h). 0xfff1 marks an empty place.
 *
 * List A starts a new town with three random items (TownItemLists_StartListA); on each day that
 * passes it may get one more (TownItemLists_FillListA), until ten places are taken; an item a
 * snowman's map object replaces goes to it, the oldest item giving way when it is full
 * (TownItemLists_PushListA).
 *
 * List B takes the items villagers give away from their houses (villager_house_items.h,
 * TownItemLists_AddListB); it is emptied when a Monday or a Thursday has begun since the last
 * day played (TownItemLists_EmptyListBOnDays), as the town hall's recycle bin is in the game. */
#ifndef CLEAN_MAIN_TOWN_ITEM_LISTS_H
#define CLEAN_MAIN_TOWN_ITEM_LISTS_H

#include "calendar.h" /* DateTime */
#include "types.h"

#define TOWN_ITEM_LIST_PLACES 15
#define TOWN_ITEM_LIST_NONE 0xfff1

void TownItemLists_EmptyListBOnDays(u16 *list, const DateTime *today, int days);
void TownItemLists_ClearListB(u16 *list);
void TownItemLists_DestructListB(void *list);
void TownItemLists_ConstructListB(void *list);
void TownItemLists_FillListA(u16 *list, int days);
void TownItemLists_StartListA(u16 *list);
void TownItemLists_ClearListA(u16 *list);
void TownItemLists_DestructListA(void *list);
void TownItemLists_ConstructListA(void *list);
int TownItemLists_PutListB(u32 place, u16 item);
int TownItemLists_ListBItem(u32 place);
int TownItemLists_AddListB(int item);
int TownItemLists_CountListA(void);
int TownItemLists_AnyListA(void);
void TownItemLists_PushListA(u16 item);

#endif
