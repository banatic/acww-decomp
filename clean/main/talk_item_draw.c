/* Items a villager's talk draws at random from the game's item lists (talk_item_draw.h). */
#include "talk_item_draw.h"

#include "clean.h"

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

/* A random number below `bound`. */
extern u32 func_020644cc(u32 bound);
/* The item list constructed and destroyed; an item of it drawn into `*out` (`group` may be
 * changed for the draw after it); an item of it drawn the plain way. */
extern void func_02063ccc(TalkItemDrawObject *list, u32 kind, u32 group);
extern void func_02063cc8(TalkItemDrawObject *list);
extern void func_020638d4(u16 *out, TalkItemDrawObject *list, u32 value, int b, int c, int d, u32 *group);
extern void func_02063884(u16 *out, TalkItemDrawObject *list);

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
    const TalkItemDrawList *picked = &lists[func_020644cc(count)];
    *item = TALK_ITEM_DRAW_NONE;
    u32 group = picked->group;
    func_02063ccc(&list, picked->kind, picked->group);
    copy = list;
    func_020638d4(&drawn, &copy, value, 0, 1, 1, &group);
    *item = drawn;
    func_02063cc8(&copy);
    if (*item == TALK_ITEM_DRAW_NONE) {
        u16 again;
        TalkItemDrawObject list2;
        TalkItemDrawObject copy2;
        func_02063ccc(&list2, picked->kind, group);
        copy2 = list2;
        func_02063884(&again, &copy2);
        *item = again;
        func_02063cc8(&copy2);
        func_02063cc8(&list2);
    }
    func_02063cc8(&list);
}
CLEAN_AS(func_0202d5fc, TalkItemDraw_OfLists)

/* func_0202d694: an item drawn from the list of a kind picked at random of 0, 2, 3, 4 (group 0)
 * into `*item`. */
void TalkItemDraw_OfKinds(u16 *item)
{
    TalkItemDrawObject list;
    TalkItemDrawObject copy;
    u32 kind = data_020c8eb4[func_020644cc(TALK_ITEM_DRAW_KINDS)];
    func_02063ccc(&list, kind, 0);
    copy = list;
    func_020638d4(item, &copy, 0, 0, 1, 1, NULL);
    func_02063cc8(&copy);
    func_02063cc8(&list);
}
CLEAN_AS(func_0202d694, TalkItemDraw_OfKinds)
