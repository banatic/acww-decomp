/* The town's order of the item groups 1-3, one for each of the nine item kinds of item_lists.h:
 * the bytes of the state block at 0x173d4 (data_021f3b7c), each set at random to one of six
 * orders when the town is set up. An order is a row of the game's table at data_020cca9c, the
 * weight (60, 30 or 10) it gives to each of the groups 1-3.
 *
 * ItemGroupOrder_PickGroup picks the group an item list draws from: one of three places (1-3)
 * chosen with the chances of the town's three values (ItemGroupOrder_Weight: 60 - x, 30 and
 * x + 10, x being a tenth of the house's room-edge sums of room_score.h), each place being the
 * group whose weight ranks as that value ranks among the three. */
#ifndef CLEAN_MAIN_ITEM_GROUP_ORDER_H
#define CLEAN_MAIN_ITEM_GROUP_ORDER_H

#include "date_random.h"
#include "types.h"

/* One byte for each item kind (ITEM_LISTS_KINDS). */
#define ITEM_GROUP_ORDER_KINDS 9
/* The orders of the table, and the groups each weighs. */
#define ITEM_GROUP_ORDER_ROWS 6
#define ITEM_GROUP_ORDER_GROUPS 3

/* The weights an order gives. */
enum ItemGroupOrderWeight {
    ITEM_GROUP_ORDER_LOW = 10,
    ITEM_GROUP_ORDER_MIDDLE = 30,
    ITEM_GROUP_ORDER_HIGH = 60,
};

/* What ItemGroupOrder_PickGroup is asked: a place at random, or one of the three. */
enum ItemGroupOrderPlace {
    ITEM_GROUP_ORDER_RANDOM = 0,
    ITEM_GROUP_ORDER_FIRST = 1,  /* ranked as the first value, 60 - x */
    ITEM_GROUP_ORDER_SECOND = 2, /* ranked as the second, 30 */
    ITEM_GROUP_ORDER_THIRD = 3,  /* ranked as the third, x + 10 */
};

void ItemGroupOrder_InitAll(u8 *orders);
void *ItemGroupOrder_DestructAll(void *orders);
void *ItemGroupOrder_ConstructAll(void *orders);
int ItemGroupOrder_GroupOfWeight(u8 *order, u8 weight);
int ItemGroupOrder_Get(u8 *order);
u8 ItemGroupOrder_Weight(u32 index);
int ItemGroupOrder_PickGroup(u8 *order, int place, DateRandom *source);
u8 *ItemGroupOrder_Row(u8 *order);
void ItemGroupOrder_Init(char *order);
void ItemGroupOrder_Destruct(void *order);
void ItemGroupOrder_Construct(void *order);

#endif
