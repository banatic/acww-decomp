/* The game's item lists: what shops, letters and villagers draw items from at random.
 *
 * The items are in nine kinds (the table at data_020ccab0, ItemListsKind): kind 0 the items
 * with a variant (furniture, 0x6e9 of them, read by furniture_info.h), kinds 1-8 items whose
 * season and group item_info.h reads (kind 1 the 64 piles, each drawn full; the others give
 * their codes by functions of main). Each kind gives the code of its item number n, the
 * season an item is drawn in (-1 or 4 for every season; the furniture's is always -1), the
 * item's group, how many items it has, and whether a code is one of its items.
 *
 * An item list (ItemList) is a kind and a group; an item drawn from it is one of the kind's
 * items of that group, in today's season (ItemLists_Season, by the date source's month and
 * day), not yet in a player's item record when one is given, and not one of those drawn with
 * it already. The group may first be turned by the town's order of the three groups 1-3 for
 * the kind: a byte for each kind in the state block at 0x173d4 (data_021f3b7c) picks one of
 * six orders (func_02063f94). When no item passes, any of the kind's items is drawn (unless a
 * record was given), and when that draw fails too, the kind's first item.
 *
 * ItemLists_DrawRange draws one code from a range of codes instead, by its own rules
 * (clothes of a style, groups 0x18 and 0x19 never), and ItemLists_DrawByGroup draws from
 * kinds 0, 4 and 3 with groups 1-3 weighed by the town's values (func_02063f40).
 *
 * The draws take their random numbers from a date source (date_random.h); given none, they
 * use the clock's. "Nothing" is ITEM_CODE_NONE (0xfff1). */
#ifndef CLEAN_MAIN_ITEM_LISTS_H
#define CLEAN_MAIN_ITEM_LISTS_H

#include "date_random.h"
#include "types.h"

#define ITEM_LISTS_KINDS 9

/* A kind of the table, its entries as DS addresses. */
typedef struct ItemListsKind {
    u32 code;    /* u16 (int number): the code of its item `number` */
    u32 season;  /* int (u16 *item): the season it is drawn in; -1 or 4 for all */
    u32 group;   /* int (u16 *item) */
    u32 count;   /* its items */
    u32 accepts; /* int (u16 *item): whether a code is one of its items */
} ItemListsKind;

/* An item list (8 bytes). */
typedef struct ItemList {
    int kind;  /* 0x00: 0-8 */
    int group; /* 0x04 */
} ItemList;

/* What ItemLists_Season answers. */
enum ItemListsSeason {
    ITEM_LISTS_SPRING = 0,
    ITEM_LISTS_SUMMER = 1,
    ITEM_LISTS_AUTUMN = 2,
    ITEM_LISTS_WINTER = 3,
};

int ItemLists_IsVariantGroup4(u16 *item);
int ItemLists_GroupOf(u16 *item, int raw);
int ItemLists_KindOf(u16 *item);
void ItemLists_DrawByGroup(u16 *out, int record, DateRandom *source);
void ItemLists_DrawRange(u16 *out, int first, u32 count, u16 *drawn, u32 drawn_count, void *record, int in_record, int style,
                         DateRandom *source, int filter);
int ItemLists_DrawRangeMany(u16 *items, unsigned int count, int first, int range, int record, int in_record, int style,
                            int source, int filter);
void ItemLists_DrawPlain(u32 out, ItemList *list);
int ItemLists_DrawOne(int out, int count, int lists, int record, int source, unsigned char filter, int turn, int group_out);
void ItemLists_Draw(unsigned short *out, ItemList *list, int record, int source, unsigned char filter, int turn,
                    int group_out);
int ItemLists_DrawMany(u16 *out, unsigned int count, ItemList *lists, int list_count, void *record, DateRandom *source,
                       int filter, int turn, int *group_out);
int ItemLists_InRecord(int record, int item);
int ItemLists_Season(int month, unsigned int day);
int ItemLists_InSeason(int item_season, int season);
int ItemLists_IndexOf(u16 *item, u16 *items, unsigned int count);
int ItemLists_AnySeason(void);
void ItemLists_PileCode(int number, int unused1, int unused2);
void ItemLists_VariantCode(int number);
int ItemList_Group(ItemList *list);
int ItemList_Kind(ItemList *list);
void ItemList_Destruct(void *list);
void ItemList_Construct(ItemList *list, int kind, int group);
u8 *ItemLists_TierByte(u8 *bytes, int kind);

#endif
