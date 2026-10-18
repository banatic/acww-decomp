/* Items a villager's talk draws at random from the game's item lists (talk_item_draw.h). */
#include "talk_item_draw.h"

#include "clean.h"
#include "item_lists.h"
#include "main_random.h"

#define TALK_ITEM_DRAW_NONE 0xfff1
#define TALK_ITEM_DRAW_FOUR 4
#define TALK_ITEM_DRAW_THREE 3
#define TALK_ITEM_DRAW_KINDS 4

/* The lists of the two sets, and the kinds TalkItemDraw_OfKinds picks from. */
extern const TalkItemDrawList data_020c8f98[TALK_ITEM_DRAW_FOUR];
extern const TalkItemDrawList data_020c8f4c[TALK_ITEM_DRAW_THREE];
extern const u32 data_020c8eb4[TALK_ITEM_DRAW_KINDS];

/* An item list object (constructed, copied by value into a call, destroyed). */
typedef struct TalkItemDrawObject {
    u32 kind;
    u32 group;
} TalkItemDrawObject;

/* func_0202d5cc: an item of the four lists of data_020c8f98. */
void TalkItemDraw_FourLists(u16 *item, int value)
{
    TalkItemDraw_OfLists(item, data_020c8f98, TALK_ITEM_DRAW_FOUR, (u32) value);
}
CLEAN_AS(func_0202d5cc, TalkItemDraw_FourLists)

/* func_0202d5e4: an item of the three lists of data_020c8f4c. */
void TalkItemDraw_ThreeLists(u16 *item, int value)
{
    TalkItemDraw_OfLists(item, data_020c8f4c, TALK_ITEM_DRAW_THREE, (u32) value);
}
CLEAN_AS(func_0202d5e4, TalkItemDraw_ThreeLists)

/* func_0202d5fc: an item of one of `count` lists picked at random into `*item` (0xfff1 for
 * none): drawn with `value`, and when that gives nothing drawn again the plain way from the
 * list's kind with the group the first draw left. Each list object handed to a draw is a copy,
 * destroyed after it. */
void TalkItemDraw_OfLists(u16 *item, const TalkItemDrawList *lists, u32 count, u32 value)
{
    u16 drawn;
    TalkItemDrawObject list;
    TalkItemDrawObject copy;
    const TalkItemDrawList *picked = &lists[MainRandom_Below(count)];
    *item = TALK_ITEM_DRAW_NONE;
    u32 group = picked->group;
    ItemList_Construct((ItemList *) &list, picked->kind, picked->group);
    copy = list;
    ItemLists_Draw(&drawn, (ItemList *) &copy, value, 0, 1, 1, (int) (uintptr_t) &group);
    *item = drawn;
    ItemList_Destruct(&copy);
    if (*item == TALK_ITEM_DRAW_NONE) {
        u16 again;
        TalkItemDrawObject list2;
        TalkItemDrawObject copy2;
        ItemList_Construct((ItemList *) &list2, picked->kind, group);
        copy2 = list2;
        ItemLists_DrawPlain((u32) (uintptr_t) &again, (ItemList *) &copy2);
        *item = again;
        ItemList_Destruct(&copy2);
        ItemList_Destruct(&list2);
    }
    ItemList_Destruct(&list);
}
CLEAN_AS(func_0202d5fc, TalkItemDraw_OfLists)

/* func_0202d694: an item drawn from the list of a kind picked at random of 0, 2, 3, 4 (group 0)
 * into `*item`. */
void TalkItemDraw_OfKinds(u16 *item)
{
    TalkItemDrawObject list;
    TalkItemDrawObject copy;
    u32 kind = data_020c8eb4[MainRandom_Below(TALK_ITEM_DRAW_KINDS)];
    ItemList_Construct((ItemList *) &list, kind, 0);
    copy = list;
    ItemLists_Draw(item, (ItemList *) &copy, 0, 0, 1, 1, (int) (uintptr_t) NULL);
    ItemList_Destruct(&copy);
    ItemList_Destruct(&list);
}
CLEAN_AS(func_0202d694, TalkItemDraw_OfKinds)
