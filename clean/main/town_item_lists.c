/* The two lists of 15 items in the game's state block (town_item_lists.h). */
#include "town_item_lists.h"

#include "clean.h"

/* The lists themselves, at 0x172c0 and 0x172de of the state block. */
extern u16 data_021f3a68[TOWN_ITEM_LIST_PLACES];
extern u16 data_021f3a86[TOWN_ITEM_LIST_PLACES];

/* List A gets no more items by the day once this many places are taken. */
#define LIST_A_DAILY_LIMIT 10
/* The item list A may get instead of one drawn from a list. */
#define LIST_A_PLAIN_ITEM 0x1566
/* The game's day begins at 6:00. */
#define DAY_START_HOUR 6

/* An item list (func_02063ccc constructs it, func_020638d4 draws an item of it, func_02063cc8
 * destroys it). */
typedef struct TownItemListsDraw {
    int kind;
    int group;
} TownItemListsDraw;

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_0209e100(DateTime *when, int hours); /* `when` moved back by `hours` */
extern int func_020644cc(int bound);                  /* a random number below `bound` */
extern void func_02063ccc(TownItemListsDraw *list, int kind, int group);
extern void func_020638d4(u16 *item, TownItemListsDraw *list, int a, int b, int c, int d, int e);
extern void func_02063cc8(TownItemListsDraw *list);
/* The form `*item` takes in list B, in `*out` (0xfff1 when none); whether it may go there. */
extern int func_0204c438(u16 *item, u16 *out);

/* An item drawn from the item list of `kind` (group 0). */
static u16 draw_item(int kind)
{
    TownItemListsDraw list;
    u16 item;
    func_02063ccc(&list, kind, 0);
    func_020638d4(&item, &list, 0, 0, 1, 1, 0);
    func_02063cc8(&list);
    return item;
}

/* func_0203a46c: list B emptied when a Monday or a Thursday is among the last `days` days, today
 * included (the date taken 6 hours back, as the game's day begins at 6:00); always after four
 * days or more. Nothing after no day. */
void TownItemLists_EmptyListBOnDays(u16 *list, const DateTime *today, int days)
{
    if (days == 0) {
        return;
    }
    if (days >= 4) {
        TownItemLists_ClearListB(list);
        return;
    }
    DateTime when = {0};
    MI_CpuCopy8(today, &when, sizeof when);
    func_0209e100(&when, DAY_START_HOUR);
    switch (Calendar_Weekday(when.year, when.month, when.day)) {
        case 1: /* Monday */
        case 4: /* Thursday */
            TownItemLists_ClearListB(list);
            break;
        case 2:
        case 5:
            if (days >= 2) {
                TownItemLists_ClearListB(list);
            }
            break;
        case 3:
        case 6:
            if (days >= 3) {
                TownItemLists_ClearListB(list);
            }
            break;
        default: /* Sunday: three days back is a Thursday, so four days are needed */
            break;
    }
}
CLEAN_AS(func_0203a46c, TownItemLists_EmptyListBOnDays)

/* func_0203a4ec */
void TownItemLists_ClearListB(u16 *list)
{
    for (int i = 0; i < TOWN_ITEM_LIST_PLACES; i++) {
        list[i] = TOWN_ITEM_LIST_NONE;
    }
}
CLEAN_AS(func_0203a4ec, TownItemLists_ClearListB)

/* func_0203a500: list B's destructor, which does nothing. */
void TownItemLists_DestructListB(void *list)
{
    (void) list;
}
CLEAN_AS(func_0203a500, TownItemLists_DestructListB)

/* func_0203a504: list B's constructor, which does nothing. */
void TownItemLists_ConstructListB(void *list)
{
    (void) list;
}
CLEAN_AS(func_0203a504, TownItemLists_ConstructListB)

/* func_0203a508: for each of `days` days, while fewer than ten places are taken, the first empty
 * place of list A may get an item, by a number below 100: 50-99 nothing, 30-49 item 0x1566,
 * 20-29 an item of list kind 1, 10-19 of kind 0, 0-9 of kind 2. No number is drawn on a day the
 * list has no empty place. */
void TownItemLists_FillListA(u16 *list, int days)
{
    int taken = 0;
    for (int i = 0; i < TOWN_ITEM_LIST_PLACES; i++) {
        if (list[i] != TOWN_ITEM_LIST_NONE) {
            taken++;
        }
    }
    for (int day = 0; day < days; day++) {
        if (taken >= LIST_A_DAILY_LIMIT) {
            return;
        }
        int place = 0;
        while (place < TOWN_ITEM_LIST_PLACES && list[place] != TOWN_ITEM_LIST_NONE) {
            place++;
        }
        if (place == TOWN_ITEM_LIST_PLACES) {
            continue;
        }
        int number = func_020644cc(100);
        int kind;
        if (number >= 30 && number < 50) {
            list[place] = LIST_A_PLAIN_ITEM;
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
        list[place] = draw_item(kind);
        taken++;
    }
}
CLEAN_AS(func_0203a508, TownItemLists_FillListA)

/* func_0203a5f4: list A's first three places filled with items drawn from list kind 1, 0 or 2,
 * picked at random for each. */
void TownItemLists_StartListA(u16 *list)
{
    static const int kinds[3] = {1, 0, 2};
    for (int i = 0; i < 3; i++) {
        list[i] = draw_item(kinds[func_020644cc(3)]);
    }
}
CLEAN_AS(func_0203a5f4, TownItemLists_StartListA)

/* func_0203a658 */
void TownItemLists_ClearListA(u16 *list)
{
    for (int i = 0; i < TOWN_ITEM_LIST_PLACES; i++) {
        list[i] = TOWN_ITEM_LIST_NONE;
    }
}
CLEAN_AS(func_0203a658, TownItemLists_ClearListA)

/* func_0203a66c: list A's destructor, which does nothing. */
void TownItemLists_DestructListA(void *list)
{
    (void) list;
}
CLEAN_AS(func_0203a66c, TownItemLists_DestructListA)

/* func_0203a670: list A's constructor, which does nothing. */
void TownItemLists_ConstructListA(void *list)
{
    (void) list;
}
CLEAN_AS(func_0203a670, TownItemLists_ConstructListA)

/* func_0203a694: the form of `item` func_0204c438 gives put at `place` of list B when the item
 * may go there; whether `place` is one of the list's.
 * QUIRK: an item that may not go there leaves the place as it was, and the answer is still 1. */
int TownItemLists_PutListB(u32 place, u16 item)
{
    if (place >= TOWN_ITEM_LIST_PLACES) {
        return 0;
    }
    u16 put = TOWN_ITEM_LIST_NONE;
    if (func_0204c438(&item, &put)) {
        data_021f3a86[place] = put;
    }
    return 1;
}
CLEAN_AS(func_0203a694, TownItemLists_PutListB)

/* func_0203a6d4: the item at `place` of list B; 0xfff1 past the list. */
int TownItemLists_ListBItem(u32 place)
{
    return place < TOWN_ITEM_LIST_PLACES ? data_021f3a86[place] : TOWN_ITEM_LIST_NONE;
}
CLEAN_AS(func_0203a6d4, TownItemLists_ListBItem)

/* func_0203a6ec: `item` put at the first empty place of list B; 0 when there is none. */
int TownItemLists_AddListB(int item)
{
    for (u32 place = 0; place < TOWN_ITEM_LIST_PLACES; place++) {
        if (TownItemLists_ListBItem(place) == TOWN_ITEM_LIST_NONE) {
            return TownItemLists_PutListB(place, (u16) item);
        }
    }
    return 0;
}
CLEAN_AS(func_0203a6ec, TownItemLists_AddListB)

/* func_0203a71c: how many places of list A hold an item. */
int TownItemLists_CountListA(void)
{
    int count = 0;
    for (int i = 0; i < TOWN_ITEM_LIST_PLACES; i++) {
        if (data_021f3a68[i] != TOWN_ITEM_LIST_NONE) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_0203a71c, TownItemLists_CountListA)

/* func_0203a744: whether any place of list A holds an item. */
int TownItemLists_AnyListA(void)
{
    for (int i = 0; i < TOWN_ITEM_LIST_PLACES; i++) {
        if (data_021f3a68[i] != TOWN_ITEM_LIST_NONE) {
            return 1;
        }
    }
    return 0;
}
CLEAN_AS(func_0203a744, TownItemLists_AnyListA)

/* func_0203a76c: `item` put at the first empty place of list A; when there is none, the items
 * move one place to the front, the first one dropped, and `item` goes last. */
void TownItemLists_PushListA(u16 item)
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
CLEAN_AS(func_0203a76c, TownItemLists_PushListA)
