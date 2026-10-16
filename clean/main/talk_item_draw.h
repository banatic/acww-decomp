/* Items a villager's talk draws at random from the game's item lists (an item list is a kind
 * and a group: func_02063ccc constructs it, func_020638d4 draws an item of it, func_02063cc8
 * destroys it).
 *
 * TalkItemDraw_OfLists picks one of a few lists at random and draws from it; when that gives
 * nothing (0xfff1) it draws again from the list's kind with the group the first draw left
 * (func_02063884). Two sets of lists are used that way: kinds 2, 5, 6, 8 (groups 0, 0x1d,
 * 0x1d, 0x1d; TalkItemDraw_FourLists) and kinds 0, 3, 4 (group 0; TalkItemDraw_ThreeLists).
 * TalkItemDraw_OfKinds draws once from one of the kinds 0, 2, 3, 4. */
#ifndef CLEAN_MAIN_TALK_ITEM_DRAW_H
#define CLEAN_MAIN_TALK_ITEM_DRAW_H

#include "types.h"

/* An item list's kind and group, as the tables of lists hold them. */
typedef struct TalkItemDrawList {
    u32 kind;
    u32 group;
} TalkItemDrawList;

void TalkItemDraw_FourLists(u16 *item, int value);
void TalkItemDraw_ThreeLists(u16 *item, int value);
void TalkItemDraw_OfLists(u16 *item, const TalkItemDrawList *lists, u32 count, u32 value);
void TalkItemDraw_OfKinds(u16 *item);

#endif
