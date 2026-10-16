/* The game's item lists and the draws from them (item_lists.h). */
#include "item_lists.h"

#include "clean.h"
#include "furniture_info.h"
#include "item_code.h"
#include "item_info.h"
#include "item_record.h"
#include "player_record.h"

static_assert(sizeof(ItemListsKind) == 0x14, "ItemListsKind size");
static_assert(sizeof(ItemList) == 8, "ItemList size");

/* The nine kinds. */
extern const ItemListsKind data_020ccab0[ITEM_LISTS_KINDS];
/* The groups 1-3, in the order ItemLists_GroupOf tries them. */
extern const int data_020cca90[3];
/* Which of the groups 1-3 ItemLists_DrawByGroup starts with (1, 1, 0). */
extern const u8 data_020de640[3];
/* The state block's nine bytes at 0x173d4, one per kind: the town's order of the groups. */
extern u8 data_021f3b7c[];

/* The group of one of the three places of a kind's order (`place` 1-3); `source` is used for
 * place 0 only (in the next block of main). */
extern int func_02063f94(u8 *order, int place, DateRandom *source);
/* The weight of group `index` + 1 (0-2), from the town's values. */
extern u8 func_02063f40(u32 index);
/* The style of a piece of clothing. */
extern int func_0204c228(u16 *item);
/* An item flag (bit 4 of item_info.h's flags for an item of kind 1); 1 for an item without one. */
extern int func_0204c260(u16 *item);
/* An array's elements built and destroyed; an item code's constructor (sets it to nothing) and
 * destructor, handed to them. */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void func_02034ce0(void *item);
extern void func_020051b0(void *item);

#define ITEM_LISTS_NONE 0xfff1
/* What ItemLists_GroupOf answers for a code of no kind. */
#define ITEM_LISTS_NO_GROUP 0x18
/* Groups ItemLists_DrawRange never draws. */
#define ITEM_LISTS_GROUP_18 0x18
#define ITEM_LISTS_GROUP_19 0x19
/* The group ItemLists_IsVariantGroup4 looks for. */
#define ITEM_LISTS_GROUP_4 4
/* An item season that is every season, beside -1. */
#define ITEM_LISTS_ALL_SEASONS 4
/* The clothes, whose style ItemLists_DrawRange may ask for; the style that is any. */
#define ITEM_LISTS_CLOTHES_FIRST 0x11a8
#define ITEM_LISTS_CLOTHES_LAST 0x12a7
#define ITEM_LISTS_ANY_STYLE 0xa
/* The ranges for which ItemLists_DrawRange drops its filter. */
#define ITEM_LISTS_UNFILTERED_A_FIRST 0x450c
#define ITEM_LISTS_UNFILTERED_A_LAST 0x45db
#define ITEM_LISTS_UNFILTERED_B_FIRST 0x45dc
#define ITEM_LISTS_UNFILTERED_B_LAST 0x47d7
#define ITEM_LISTS_UNFILTERED_C_FIRST 0x1323
#define ITEM_LISTS_UNFILTERED_C_LAST 0x1368
/* The days after which a season starts in its first month (February's is earlier). */
#define ITEM_LISTS_FEBRUARY_LAST_WINTER_DAY 24
#define ITEM_LISTS_LAST_DAY_BEFORE 26
/* The kinds and groups ItemLists_DrawByGroup draws from. */
#define ITEM_LISTS_BY_GROUP_GROUPS 3
#define ITEM_LISTS_BY_GROUP_KINDS 3
/* The pile ItemLists_PileCode makes: a full one. */
#define ITEM_LISTS_PILE_COUNT 4

typedef u16 ItemListsCode(int number);
typedef int ItemListsOfItem(u16 *item);
typedef u32 DateRandomBelow(DateRandom *self, u32 bound);
typedef int DateRandomValue(DateRandom *self);

/* The kind's entries, through their DS addresses. */
static u16 kind_code(const ItemListsKind *kind, int number)
{
    return ((ItemListsCode *) (uintptr_t) kind->code)(number);
}

static int kind_season(const ItemListsKind *kind, u16 *item)
{
    return ((ItemListsOfItem *) (uintptr_t) kind->season)(item);
}

static int kind_group(const ItemListsKind *kind, u16 *item)
{
    return ((ItemListsOfItem *) (uintptr_t) kind->group)(item);
}

static int kind_accepts(const ItemListsKind *kind, u16 *item)
{
    return ((ItemListsOfItem *) (uintptr_t) kind->accepts)(item);
}

/* The date source's entries (date_random.h). */
static u32 source_below(DateRandom *source, u32 bound)
{
    return ((DateRandomBelow *) (uintptr_t) source->vtable->below)(source, bound);
}

static int source_month(DateRandom *source)
{
    return ((DateRandomValue *) (uintptr_t) source->vtable->month)(source);
}

static int source_day(DateRandom *source)
{
    return ((DateRandomValue *) (uintptr_t) source->vtable->day)(source);
}

/* Whether two codes are the same item: by their numbers without the variant when `a` has a
 * variant, else as codes. */
static int same_item(u16 *a, u16 *b)
{
    if (ItemCode_HasVariant(a)) {
        int number = ItemCode_VariantItem(a);
        return number == ItemCode_VariantItem(b);
    }
    return *a == *b;
}

/* Whether a code is nothing (compared as same_item does). */
static int is_none(u16 *item)
{
    u16 none = ITEM_LISTS_NONE;
    return same_item(item, &none);
}

/* func_02062fe8: whether an item has a variant and is of group 4 (ItemLists_GroupOf, turned). */
int ItemLists_IsVariantGroup4(u16 *item)
{
    return ItemCode_HasVariant(item) && ItemLists_GroupOf(item, 0) == ITEM_LISTS_GROUP_4;
}
CLEAN_AS(func_02062fe8, ItemLists_IsVariantGroup4)

/* func_0206300c: the group of an item, by its kind; unless `raw`, the group 1-3 whose place in
 * the town's order for the kind gives it, when one does. 0x18 for an item of no kind. */
int ItemLists_GroupOf(u16 *item, int raw)
{
    int kind = ItemLists_KindOf(item);
    if (kind == ITEM_LISTS_KINDS) {
        return ITEM_LISTS_NO_GROUP;
    }
    int group = kind_group(&data_020ccab0[kind], item);
    if (raw) {
        return group;
    }
    u8 *order = ItemLists_TierByte(data_021f3b7c, kind);
    for (u32 i = 0; i < 3; i++) {
        if (group == func_02063f94(order, data_020cca90[i], NULL)) {
            return data_020cca90[i];
        }
    }
    return group;
}
CLEAN_AS(func_0206300c, ItemLists_GroupOf)

/* func_02063084: the first kind that accepts the item, or ITEM_LISTS_KINDS for none. */
int ItemLists_KindOf(u16 *item)
{
    for (u32 kind = 0; kind < ITEM_LISTS_KINDS; kind++) {
        if (kind_accepts(&data_020ccab0[kind], item)) {
            return (int) kind;
        }
    }
    return ITEM_LISTS_KINDS;
}
CLEAN_AS(func_02063084, ItemLists_KindOf)

/* func_020630bc: an item of kind 0, 4 or 3 drawn by group: first one item is drawn (turned,
 * filtered, ItemLists_Draw) for each of the nine pairs of groups 1-3 and kinds 0, 4, 3. Then
 * a group is picked among those still in play (1 and 2 at first), weighed by func_02063f40,
 * and one of the group's drawn items that is not nothing picked at random; a group with none
 * is put out of play and the pick made again. Nothing when no group is left. `record` and
 * `source` are handed to the draws; the picks use `source`, else the clock's. */
void ItemLists_DrawByGroup(u16 *out, int record, DateRandom *source)
{
    static const int kinds[ITEM_LISTS_BY_GROUP_KINDS] = {0, 4, 3};
    DateRandom clock;
    u8 in_play[ITEM_LISTS_BY_GROUP_GROUPS];
    u16 drawn[ITEM_LISTS_BY_GROUP_GROUPS][ITEM_LISTS_BY_GROUP_KINDS];

    DateRandom_Construct(&clock);
    DateRandom *picker = source != NULL ? source : &clock;
    for (u32 i = 0; i < ITEM_LISTS_BY_GROUP_GROUPS; i++) {
        in_play[i] = data_020de640[i];
    }
    __cxa_vec_ctor(drawn, ITEM_LISTS_BY_GROUP_GROUPS * ITEM_LISTS_BY_GROUP_KINDS, sizeof(u16), func_02034ce0, func_020051b0);

    for (int group = 0; group < ITEM_LISTS_BY_GROUP_GROUPS; group++) {
        for (int k = 0; k < ITEM_LISTS_BY_GROUP_KINDS; k++) {
            ItemList list;
            u16 item;
            ItemList_Construct(&list, kinds[k], group + 1);
            ItemLists_Draw(&item, &list, record, (int) (uintptr_t) source, 1, 1, 0);
            drawn[group][k] = item;
            ItemList_Destruct(&list);
        }
    }

    for (;;) {
        u32 total = 0;
        for (u32 i = 0; i < ITEM_LISTS_BY_GROUP_GROUPS; i++) {
            if (in_play[i]) {
                total += func_02063f40(i);
            }
        }
        if (total == 0) {
            break;
        }
        u32 pick = source_below(picker, total);
        u32 reach = 0;
        for (u32 group = 0; group < ITEM_LISTS_BY_GROUP_GROUPS; group++) {
            if (!in_play[group]) {
                continue;
            }
            reach += func_02063f40(group);
            if (pick >= reach) {
                continue;
            }
            int count = 0;
            for (u32 k = 0; k < ITEM_LISTS_BY_GROUP_KINDS; k++) {
                if (!is_none(&drawn[group][k])) {
                    count++;
                }
            }
            if (count == 0) {
                in_play[group] = 0;
                break;
            }
            int which = (int) source_below(picker, (u32) count);
            int seen = 0;
            for (u32 k = 0; k < ITEM_LISTS_BY_GROUP_KINDS; k++) {
                if (is_none(&drawn[group][k])) {
                    continue;
                }
                if (seen == which) {
                    *out = drawn[group][k];
                    __cxa_vec_cleanup(drawn, ITEM_LISTS_BY_GROUP_GROUPS * ITEM_LISTS_BY_GROUP_KINDS, sizeof(u16),
                                      func_020051b0);
                    DateRandom_Destruct(&clock);
                    return;
                }
                seen++;
            }
            /* QUIRK: a pick past the count (a source that answers out of its bound) goes on to
               the next group in play. */
        }
    }
    *out = ITEM_LISTS_NONE;
    __cxa_vec_cleanup(drawn, ITEM_LISTS_BY_GROUP_GROUPS * ITEM_LISTS_BY_GROUP_KINDS, sizeof(u16), func_020051b0);
    DateRandom_Destruct(&clock);
}
CLEAN_AS(func_020630bc, ItemLists_DrawByGroup)

/* Whether ItemLists_DrawRange's code passes its rules other than the record: not one of
 * `drawn` (unless `skip_drawn`), of the style asked for when it is clothes, not of group 0x18
 * or 0x19, and, when `filter`, refused by func_0204c260. */
static int range_candidate(u16 *code, u16 *drawn, u32 drawn_count, int skip_drawn, int style, int filter)
{
    if (!skip_drawn) {
        for (u32 j = 0; j < drawn_count; j++) {
            if (same_item(code, &drawn[j])) {
                return 0;
            }
        }
    }
    if (*code >= ITEM_LISTS_CLOTHES_FIRST && *code <= ITEM_LISTS_CLOTHES_LAST && style != ITEM_LISTS_ANY_STYLE &&
        style != func_0204c228(code)) {
        return 0;
    }
    int group = 0;
    if (ItemCode_IsKind1(code)) {
        group = ItemInfo_Unk06(code);
    } else if (ItemCode_HasVariant(code)) {
        group = FurnitureInfo_ItemUnk04(code);
    }
    if (group == ITEM_LISTS_GROUP_19 || group == ITEM_LISTS_GROUP_18) {
        return 0;
    }
    if (filter && func_0204c260(code)) {
        return 0;
    }
    return 1;
}

/* Whether the code passes ItemLists_DrawRange's record rule: with a record, in it when
 * `in_record`, else not in it. */
static int range_record_accepts(void *record, int in_record, u16 *code)
{
    if (record == NULL) {
        return 1;
    }
    int has = ItemRecord_Has((ItemRecord *) PlayerRecord_ItemRecord(record), code);
    return in_record ? has != 0 : has == 0;
}

/* func_02063414: a code drawn from the `count` codes from `first` (in steps of four when
 * `first` has a variant): one that is none of the `drawn_count` codes at `drawn`, of style
 * `style` when it is clothes (ITEM_LISTS_ANY_STYLE for any), not of group 0x18 or 0x19,
 * passing func_0204c260 when `filter` (dropped for the ranges 0x450c-0x47d7 and
 * 0x1323-0x1368, as `first` says), and, with a player's `record`, in its item record when
 * `in_record`, else not in it. When none passes: nothing with a record, else one is drawn by
 * the same rules but for the drawn codes.
 * QUIRK: that second draw counts every code of the range but keeps the other rules, so the
 * number drawn may fall on no code and the result be nothing. */
void ItemLists_DrawRange(u16 *out, int first, u32 count, u16 *drawn, u32 drawn_count, void *record, int in_record, int style,
                         DateRandom *source, int filter)
{
    DateRandom clock;
    DateRandom_Construct(&clock);
    DateRandom *picker = source != NULL ? source : &clock;

    u16 start = (u16) first;
    int shift = ItemCode_HasVariant(&start) ? 2 : 0;
    if ((start >= ITEM_LISTS_UNFILTERED_A_FIRST && start <= ITEM_LISTS_UNFILTERED_A_LAST) ||
        (start >= ITEM_LISTS_UNFILTERED_B_FIRST && start <= ITEM_LISTS_UNFILTERED_B_LAST) ||
        (start >= ITEM_LISTS_UNFILTERED_C_FIRST && start <= ITEM_LISTS_UNFILTERED_C_LAST)) {
        filter = 0;
    }

    int passing = 0;
    for (u32 i = 0; i < count; i++) {
        u16 code = (u16) (first + (int) (i << shift));
        if (range_candidate(&code, drawn, drawn_count, 0, style, filter) && range_record_accepts(record, in_record, &code)) {
            passing++;
        }
    }

    int any = 0;
    if (passing == 0) {
        if (record != NULL) {
            *out = ITEM_LISTS_NONE;
            DateRandom_Destruct(&clock);
            return;
        }
        any = 1;
        passing = (int) count;
    }
    int pick = (int) source_below(picker, (u32) passing);

    int seen = 0;
    for (u32 i = 0; i < count; i++) {
        u16 code = (u16) (first + (int) (i << shift));
        if (!range_candidate(&code, drawn, drawn_count, any, style, filter) ||
            !range_record_accepts(record, in_record, &code)) {
            continue;
        }
        if (pick == seen) {
            *out = code;
            DateRandom_Destruct(&clock);
            return;
        }
        seen++;
    }
    *out = ITEM_LISTS_NONE;
    DateRandom_Destruct(&clock);
}
CLEAN_AS(func_02063414, ItemLists_DrawRange)

/* func_020637d0: `count` codes drawn into `items` by ItemLists_DrawRange, each one different
 * from those before it; whether every draw gave an item (1), else 0 (the draws go on). */
int ItemLists_DrawRangeMany(u16 *items, unsigned int count, int first, int range, int record, int in_record, int style,
                            int source, int filter)
{
    int all = 1;
    for (u32 i = 0; i < count; i++) {
        u16 item;
        ItemLists_DrawRange(&item, first, (u32) range, items, i, (void *) (uintptr_t) (u32) record, in_record, style,
                            (DateRandom *) (uintptr_t) (u32) source, filter);
        items[i] = item;
        if (is_none(&items[i])) {
            all = 0;
        }
    }
    return all;
}
CLEAN_AS(func_020637d0, ItemLists_DrawRangeMany)

/* func_02063884: an item drawn from a copy of the list, the plain way: no record, the clock's
 * source, filtered, the group not turned. */
void ItemLists_DrawPlain(u32 out, ItemList *list)
{
    ItemList copy = *list;
    ItemLists_Draw((u16 *) (uintptr_t) out, &copy, 0, 0, 1, 0, 0);
    ItemList_Destruct(&copy);
}
CLEAN_AS(func_02063884, ItemLists_DrawPlain)

/* func_020638b0: ItemLists_DrawMany from the one list at `lists`. */
int ItemLists_DrawOne(int out, int count, int lists, int record, int source, unsigned char filter, int turn, int group_out)
{
    return ItemLists_DrawMany((u16 *) (uintptr_t) (u32) out, (unsigned int) count, (ItemList *) (uintptr_t) (u32) lists, 1,
                              (void *) (uintptr_t) (u32) record, (DateRandom *) (uintptr_t) (u32) source, filter, turn,
                              (int *) (uintptr_t) (u32) group_out);
}
CLEAN_AS(func_020638b0, ItemLists_DrawOne)

/* func_020638d4: one item drawn from a copy of the list (ItemLists_DrawMany); nothing first. */
void ItemLists_Draw(unsigned short *out, ItemList *list, int record, int source, unsigned char filter, int turn, int group_out)
{
    *out = ITEM_LISTS_NONE;
    ItemList copy = *list;
    ItemLists_DrawOne((int) (uintptr_t) out, 1, (int) (uintptr_t) &copy, record, source, filter, turn, group_out);
    ItemList_Destruct(&copy);
}
CLEAN_AS(func_020638d4, ItemLists_Draw)

/* Whether a code of the kind passes ItemLists_DrawMany's rules other than being drawn
 * already: of the group, in the season, not in the player's record, and when `filter` not
 * refused by func_0204c260. */
static int many_candidate(const ItemListsKind *kind, u16 *code, int group, int season, void *record, int filter)
{
    if (group != kind_group(kind, code)) {
        return 0;
    }
    if (!ItemLists_InSeason(kind_season(kind, code), season)) {
        return 0;
    }
    if (ItemLists_InRecord((int) (uintptr_t) record, (int) (uintptr_t) code)) {
        return 0;
    }
    if (filter && func_0204c260(code)) {
        return 0;
    }
    return 1;
}

/* func_02063914: `count` items drawn into `out` (nothing in each first), each from one of the
 * `list_count` lists at `lists` picked at random, of the list's group (turned by the town's
 * order for the kind when `turn` is 1) and of today's season, not in `record`'s item record
 * (a player's, or NULL), not drawn already, and when `filter` (dropped for groups other than
 * 0-3, 5 and 0x1d) not refused by func_0204c260. `*group_out`, when given, is set to 1, then
 * to each draw's group. When no item passes: 0 at once with a record; else any of the group's
 * items in season is drawn, and when that gives none, the kind's first item. 1 when every
 * item passed, else 0. */
int ItemLists_DrawMany(u16 *out, unsigned int count, ItemList *lists, int list_count, void *record, DateRandom *source,
                       int filter, int turn, int *group_out)
{
    int all = 1;
    DateRandom clock;
    DateRandom_Construct(&clock);
    DateRandom *picker = source != NULL ? source : &clock;
    int month = source_month(picker);
    int season = ItemLists_Season(month, (unsigned int) source_day(picker));

    for (u32 i = 0; i < count; i++) {
        out[i] = ITEM_LISTS_NONE;
    }
    if (group_out != NULL) {
        *group_out = 1;
    }

    u32 n = 0;
    while (n < count) {
        ItemList *list = &lists[(int) source_below(picker, (u32) list_count)];
        int kind_number = ItemList_Kind(list);
        u8 *order = ItemLists_TierByte(data_021f3b7c, kind_number);
        int group;
        if (turn == 1) {
            group = func_02063f94(order, ItemList_Group(list), picker);
        } else {
            group = ItemList_Group(list);
        }
        int filtered = filter;
        if (group != 0 && group != 1 && group != 2 && group != 3 && group != 0x1d && group != 5) {
            filtered = 0;
        }
        if (group_out != NULL) {
            *group_out = group;
        }

        const ItemListsKind *kind = &data_020ccab0[kind_number];
        int passing = 0;
        for (u32 j = 0; j < kind->count; j++) {
            u16 code = kind_code(kind, (int) j);
            if (many_candidate(kind, &code, group, season, record, filtered) && ItemLists_IndexOf(&code, out, n) == -1) {
                passing++;
            }
        }
        int any = 0;
        if (passing == 0) {
            if (record != NULL) {
                DateRandom_Destruct(&clock);
                return 0;
            }
            passing = (int) kind->count;
            any = 1;
        }

        int pick = (int) source_below(picker, (u32) passing);
        int found = 0;
        int seen = 0;
        for (u32 j = 0; j < kind->count; j++) {
            u16 code = kind_code(kind, (int) j);
            if (!many_candidate(kind, &code, group, season, record, filtered)) {
                continue;
            }
            if (!any && ItemLists_IndexOf(&code, out, n) != -1) {
                continue;
            }
            if (pick == seen) {
                out[n++] = code;
                found = 1;
                break;
            }
            seen++;
        }
        if (!found) {
            out[n++] = kind_code(kind, 0);
            all = 0;
        }
    }
    DateRandom_Destruct(&clock);
    return all;
}
CLEAN_AS(func_02063914, ItemLists_DrawMany)

/* func_02063b98: whether the item is in the item record of the player record `record`; 0
 * without one. */
int ItemLists_InRecord(int record, int item)
{
    if (record == 0) {
        return 0;
    }
    return ItemRecord_Has((ItemRecord *) PlayerRecord_ItemRecord((u8 *) (uintptr_t) (u32) record),
                          (const ItemCode *) (uintptr_t) (u32) item);
}
CLEAN_AS(func_02063b98, ItemLists_InRecord)

/* func_02063bb4: the season of a date: spring from February 25th, summer from May 27th,
 * autumn from August 27th, winter from November 27th. A month outside 1-11 is winter. */
int ItemLists_Season(int month, unsigned int day)
{
    switch (month) {
        case 1:
            return ITEM_LISTS_WINTER;
        case 2:
            return day > ITEM_LISTS_FEBRUARY_LAST_WINTER_DAY ? ITEM_LISTS_SPRING : ITEM_LISTS_WINTER;
        case 3:
        case 4:
            return ITEM_LISTS_SPRING;
        case 5:
            return day > ITEM_LISTS_LAST_DAY_BEFORE ? ITEM_LISTS_SUMMER : ITEM_LISTS_SPRING;
        case 6:
        case 7:
            return ITEM_LISTS_SUMMER;
        case 8:
            return day > ITEM_LISTS_LAST_DAY_BEFORE ? ITEM_LISTS_AUTUMN : ITEM_LISTS_SUMMER;
        case 9:
        case 10:
            return ITEM_LISTS_AUTUMN;
        case 11:
            return day > ITEM_LISTS_LAST_DAY_BEFORE ? ITEM_LISTS_WINTER : ITEM_LISTS_AUTUMN;
        default:
            return ITEM_LISTS_WINTER;
    }
}
CLEAN_AS(func_02063bb4, ItemLists_Season)

/* func_02063c24: whether an item of season `item_season` is drawn in `season`. */
int ItemLists_InSeason(int item_season, int season)
{
    return item_season == -1 || item_season == ITEM_LISTS_ALL_SEASONS || item_season == season;
}
CLEAN_AS(func_02063c24, ItemLists_InSeason)

/* func_02063c3c: the index of the first of the `count` codes at `items` that is the same item
 * as `item` (tested with the element first), or -1. */
int ItemLists_IndexOf(u16 *item, u16 *items, unsigned int count)
{
    for (u32 i = 0; i < count; i++) {
        if (same_item(&items[i], item)) {
            return (int) i;
        }
    }
    return -1;
}
CLEAN_AS(func_02063c3c, ItemLists_IndexOf)

/* func_02063ca0 (kind 0's season): every season. */
int ItemLists_AnySeason(void)
{
    return -1;
}
CLEAN_AS(func_02063ca0, ItemLists_AnySeason)

/* func_02063ca8 (kind 1's code): the full pile of item `number`.
 * QUIRK: declared without a result; in the ROM the code is still in r0 when it returns, and
 * the draws read it. */
void ItemLists_PileCode(int number, int unused1, int unused2)
{
    (void) unused1;
    (void) unused2;
    ItemCode_MakePile((u32) number, ITEM_LISTS_PILE_COUNT);
}
CLEAN_AS(func_02063ca8, ItemLists_PileCode)

/* func_02063cb4 (kind 0's code): the code of item `number` with variant 0.
 * QUIRK: declared without a result, as ItemLists_PileCode. */
void ItemLists_VariantCode(int number)
{
    ItemCode_MakeVariant(number, 0);
}
CLEAN_AS(func_02063cb4, ItemLists_VariantCode)

/* func_02063cc0 */
int ItemList_Group(ItemList *list)
{
    return list->group;
}
CLEAN_AS(func_02063cc0, ItemList_Group)

/* func_02063cc4 */
int ItemList_Kind(ItemList *list)
{
    return list->kind;
}
CLEAN_AS(func_02063cc4, ItemList_Kind)

/* func_02063cc8: the destructor: nothing to do. */
void ItemList_Destruct(void *list)
{
    (void) list;
}
CLEAN_AS(func_02063cc8, ItemList_Destruct)

/* func_02063ccc: the constructor. */
void ItemList_Construct(ItemList *list, int kind, int group)
{
    list->kind = kind;
    list->group = group;
}
CLEAN_AS(func_02063ccc, ItemList_Construct)

/* func_02063eb0: the town's byte for kind `kind` among `bytes`; the first for a kind past the
 * last. */
u8 *ItemLists_TierByte(u8 *bytes, int kind)
{
    if (kind < ITEM_LISTS_KINDS) {
        return bytes + kind;
    }
    return bytes;
}
CLEAN_AS(func_02063eb0, ItemLists_TierByte)
