/* The two lists of 15 items in the game's state block (town_item_lists.h). */
#include "town_item_lists.h"

#include "clean.h"
#include "date_time.h"
#include "item_lists.h"
#include "item_traits.h"
#include "main_random.h"

/* The lists themselves, at 0x172c0 and 0x172de of the state block. */
extern u16 data_021f3a68[TOWN_ITEM_LIST_PLACES];
extern u16 data_021f3a86[TOWN_ITEM_LIST_PLACES];

/* The lost and found gets no more items by the day once this many places are taken. */
#define LOST_AND_FOUND_DAILY_LIMIT 10
/* The item (the pitfall seed) the lost and found may get instead of one drawn from a list. */
#define LOST_AND_FOUND_PITFALL_SEED 0x1566
/* The game's day begins at 6:00. */
#define DAY_START_HOUR 6

/* An item list (func_02063ccc constructs it, func_020638d4 draws an item of it, func_02063cc8
 * destroys it). */
typedef struct TownItemListsDraw {
    int kind;
    int group;
} TownItemListsDraw;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

/* An item drawn from the item list of `kind` (group 0). */
static u16 pick_item(int kind)
{
    TownItemListsDraw list;
    u16 item;
    ItemList_Construct((ItemList *) &list, kind, 0);
    ItemLists_Pick(&item, (ItemList *) &list, 0, 0, 1, 1, 0);
    ItemList_Destruct(&list);
    return item;
}

/* func_0203a46c: the recycle bin emptied when a Monday or a Thursday is among the last `days` days, today
 * included (the date taken 6 hours back, as the game's day begins at 6:00); always after four
 * days or more. Nothing after no day. */
void TownItemLists_EmptyRecycleBinOnDays(u16 *list, const DateTime *today, int days)
{
    if (days == 0) {
        return;
    }
    if (days >= 4) {
        TownItemLists_ClearRecycleBin(list);
        return;
    }
    DateTime when = {0};
    MI_CpuCopy8(today, &when, sizeof when);
    DateTime_SubtractHours(&when, DAY_START_HOUR);
    switch (Calendar_Weekday(when.year, when.month, when.day)) {
        case 1: /* Monday */
        case 4: /* Thursday */
            TownItemLists_ClearRecycleBin(list);
            break;
        case 2:
        case 5:
            if (days >= 2) {
                TownItemLists_ClearRecycleBin(list);
            }
            break;
        case 3:
        case 6:
            if (days >= 3) {
                TownItemLists_ClearRecycleBin(list);
            }
            break;
        default: /* Sunday: three days back is a Thursday, so four days are needed */
            break;
    }
}
CLEAN_AS(func_0203a46c, TownItemLists_EmptyRecycleBinOnDays)

/* func_0203a4ec */
void TownItemLists_ClearRecycleBin(u16 *list)
{
    for (int i = 0; i < TOWN_ITEM_LIST_PLACES; i++) {
        list[i] = TOWN_ITEM_LIST_NONE;
    }
}
CLEAN_AS(func_0203a4ec, TownItemLists_ClearRecycleBin)

/* func_0203a500: the recycle bin's destructor, which does nothing. */
void TownItemLists_DestructRecycleBin(void *list)
{
    (void) list;
}
CLEAN_AS(func_0203a500, TownItemLists_DestructRecycleBin)

/* func_0203a504: the recycle bin's constructor, which does nothing. */
void TownItemLists_ConstructRecycleBin(void *list)
{
    (void) list;
}
CLEAN_AS(func_0203a504, TownItemLists_ConstructRecycleBin)

/* func_0203a508: for each of `days` days, while fewer than ten places are taken, the first empty
 * place of the lost and found may get an item, by a number below 100: 50-99 nothing, 30-49 item 0x1566,
 * 20-29 an item of list kind 1, 10-19 of kind 0, 0-9 of kind 2. No number is drawn on a day the
 * list has no empty place. */
void TownItemLists_FillLostAndFound(u16 *list, int days)
{
    int taken = 0;
    for (int i = 0; i < TOWN_ITEM_LIST_PLACES; i++) {
        if (list[i] != TOWN_ITEM_LIST_NONE) {
            taken++;
        }
    }
    for (int day = 0; day < days; day++) {
        if (taken >= LOST_AND_FOUND_DAILY_LIMIT) {
            return;
        }
        int place = 0;
        while (place < TOWN_ITEM_LIST_PLACES && list[place] != TOWN_ITEM_LIST_NONE) {
            place++;
        }
        if (place == TOWN_ITEM_LIST_PLACES) {
            continue;
        }
        int number = MainRandom_Below(100);
        int kind;
        if (number >= 30 && number < 50) {
            list[place] = LOST_AND_FOUND_PITFALL_SEED;
            taken++;
            continue;
        } else if (number >= 20 && number < 30) {
            kind = 1;
        } else if (number >= 10 && number < 20) {
            kind = 0;
        } else if (number >= 0 && number < 10) {
            kind = 2;
        } else {
            continue;
        }
        list[place] = pick_item(kind);
        taken++;
    }
}
CLEAN_AS(func_0203a508, TownItemLists_FillLostAndFound)

/* func_0203a5f4: the lost and found's first three places filled with items drawn from list kind 1, 0 or 2,
 * picked at random for each. */
void TownItemLists_StartLostAndFound(u16 *list)
{
    static const int kinds[3] = {1, 0, 2};
    for (int i = 0; i < 3; i++) {
        list[i] = pick_item(kinds[MainRandom_Below(3)]);
    }
}
CLEAN_AS(func_0203a5f4, TownItemLists_StartLostAndFound)

/* func_0203a658 */
void TownItemLists_ClearLostAndFound(u16 *list)
{
    for (int i = 0; i < TOWN_ITEM_LIST_PLACES; i++) {
        list[i] = TOWN_ITEM_LIST_NONE;
    }
}
CLEAN_AS(func_0203a658, TownItemLists_ClearLostAndFound)

/* func_0203a66c: the lost and found's destructor, which does nothing. */
void TownItemLists_DestructLostAndFound(void *list)
{
    (void) list;
}
CLEAN_AS(func_0203a66c, TownItemLists_DestructLostAndFound)

/* func_0203a670: the lost and found's constructor, which does nothing. */
void TownItemLists_ConstructLostAndFound(void *list)
{
    (void) list;
}
CLEAN_AS(func_0203a670, TownItemLists_ConstructLostAndFound)

/* func_0203a694: the form of `item` func_0204c438 gives put at `place` of the recycle bin when the item
 * may go there; whether `place` is one of the list's.
 * QUIRK: an item that may not go there leaves the place as it was, and the answer is still 1. */
int TownItemLists_PutRecycleBin(u32 place, u16 item)
{
    if (place >= TOWN_ITEM_LIST_PLACES) {
        return 0;
    }
    u16 put = TOWN_ITEM_LIST_NONE;
    if (ItemTraits_CarriedNonCreature(&item, &put)) {
        data_021f3a86[place] = put;
    }
    return 1;
}
CLEAN_AS(func_0203a694, TownItemLists_PutRecycleBin)

/* func_0203a6d4: the item at `place` of the recycle bin; 0xfff1 past the list. */
int TownItemLists_RecycleBinItem(u32 place)
{
    return place < TOWN_ITEM_LIST_PLACES ? data_021f3a86[place] : TOWN_ITEM_LIST_NONE;
}
CLEAN_AS(func_0203a6d4, TownItemLists_RecycleBinItem)

/* func_0203a6ec: `item` put at the first empty place of the recycle bin; 0 when there is none. */
int TownItemLists_AddRecycleBin(int item)
{
    for (u32 place = 0; place < TOWN_ITEM_LIST_PLACES; place++) {
        if (TownItemLists_RecycleBinItem(place) == TOWN_ITEM_LIST_NONE) {
            return TownItemLists_PutRecycleBin(place, (u16) item);
        }
    }
    return 0;
}
CLEAN_AS(func_0203a6ec, TownItemLists_AddRecycleBin)

/* func_0203a71c: how many places of the lost and found hold an item. */
int TownItemLists_CountLostAndFound(void)
{
    int count = 0;
    for (int i = 0; i < TOWN_ITEM_LIST_PLACES; i++) {
        if (data_021f3a68[i] != TOWN_ITEM_LIST_NONE) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_0203a71c, TownItemLists_CountLostAndFound)

/* func_0203a744: whether any place of the lost and found holds an item. */
int TownItemLists_AnyLostAndFound(void)
{
    for (int i = 0; i < TOWN_ITEM_LIST_PLACES; i++) {
        if (data_021f3a68[i] != TOWN_ITEM_LIST_NONE) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0203a744, TownItemLists_AnyLostAndFound)

/* func_0203a76c: `item` put at the first empty place of the lost and found; when there is none, the items
 * move one place to the front, the first one dropped, and `item` goes last. */
void TownItemLists_PushLostAndFound(u16 item)
{
    u16 *list = data_021f3a68;
    int place = 0;
    while (place < TOWN_ITEM_LIST_PLACES && list[place] != TOWN_ITEM_LIST_NONE) {
        place++;
    }
    if (place == TOWN_ITEM_LIST_PLACES) {
        for (place = 0; place < TOWN_ITEM_LIST_PLACES - 1; place++) {
            list[place] = list[place + 1];
        }
    }
    list[place] = item;
}
CLEAN_AS(func_0203a76c, TownItemLists_PushLostAndFound)
