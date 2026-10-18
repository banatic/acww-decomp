/* The forms an item takes (item_form.h). */
#include "item_form.h"

#include "acre_tile.h"
#include "clean.h"
#include "item_code.h"
#include "item_record.h"
#include "player_pockets.h"
#include "player_record.h"
#include "player_records.h"
#include "player_storage.h"
#include "town_item_lists.h"
#include "item_traits.h"

/* The items replaced, and the first of their replacements. */
#define ITEM_FORM_REPLACED_FIRST 0x38e4
#define ITEM_FORM_REPLACED_LAST 0x3933
#define ITEM_FORM_REPLACED_ITEMS 20
#define ITEM_FORM_REPLACEMENT_FIRST 0x3934

/* The records looked at for pockets (0-6, PlayerRecords_Get), the rooms' maps, and the
 * players' storages. */
#define ITEM_FORM_PLAYER_RECORDS 7
#define ITEM_FORM_POCKET_SLOTS 15
#define ITEM_FORM_ROOM_MAPS 5
#define ITEM_FORM_STORAGES 4
#define ITEM_FORM_ACRE_TILES 16

/* The items 0x1408-0x1428 and 0x1471-0x1491, and the one the codes they share stand for when
 * neither test accepts them. */
#define ITEM_FORM_SHARED_ITEMS 0x21
#define ITEM_FORM_SHARED_FIRST_A 0x1408
#define ITEM_FORM_SHARED_FIRST_B 0x1471
#define ITEM_FORM_SHARED_OTHER 0x137c
#define ITEM_FORM_SHARED_PLACED_FIRST 0x4464
#define ITEM_FORM_SHARED_PLACED_LAST 0x44e7
#define ITEM_FORM_SHARED_OUTDOORS_LAST 0x20
/* The outdoor codes of 0x153b-0x1541: two runs of seven. */
#define ITEM_FORM_OUTDOOR_RUN_ITEM 0x153b
#define ITEM_FORM_OUTDOOR_RUN_FIRST 0xd4
#define ITEM_FORM_OUTDOOR_RUN_SECOND 0xdb
#define ITEM_FORM_OUTDOOR_RUN_LAST 0xe1

/* 0 outdoors, 1 in a room. */
extern u8 data_020e54a8;
/* The town's list A of 15 items (TownItemLists, at 0x172c0 of the state block). */
extern u16 data_021f3a68[TOWN_ITEM_LIST_PLACES];
extern PlayerStorage data_021f2fa8[ITEM_FORM_STORAGES];

/* A run of carried items and the codes they are placed as (four codes per item in a room, one
 * outdoors). */
typedef struct ItemFormRun {
    u16 first;
    u16 last;
    u16 placed;
} ItemFormRun;

/* In a room, in the order they are tested. */
static const ItemFormRun item_form_room_runs[] = {
    {0x11a8, 0x12a7, 0x3984}, {0x12b0, 0x12e7, 0x42a4}, {0x12e8, 0x131f, 0x4384}, {0x1380, 0x139f, 0x3e24},
    {0x13c8, 0x1407, 0x3fa4}, {0x13a8, 0x13c7, 0x40a4}, {0x1431, 0x1470, 0x4124}, {0x137c, 0x137c, 0x44dc},
    {0x1408, 0x1428, 0x4464}, {0x1471, 0x1491, 0x4464}, {0x1554, 0x155c, 0x44e8},
};

/* Outdoors. */
static const ItemFormRun item_form_outdoor_runs[] = {
    {0x137c, 0x137c, 0x1e},
    {0x1408, 0x1428, 0x00},
    {0x1471, 0x1491, 0x00},
    {0x153b, 0x1541, 0xd4},
};

/* The room codes converted back by a run each (the shared ones apart), in the order they are
 * tested: `first` and `last` the codes, `placed` the first carried item. */
static const ItemFormRun item_form_carried_runs[] = {
    {0x3984, 0x3d83, 0x11a8}, {0x42a4, 0x4383, 0x12b0}, {0x4384, 0x4463, 0x12e8}, {0x3e24, 0x3ea3, 0x1380},
    {0x3fa4, 0x40a3, 0x13c8}, {0x40a4, 0x4123, 0x13a8}, {0x4124, 0x4223, 0x1431}, {0x44e8, 0x450b, 0x1554},
};

#define ITEM_FORM_COUNT(a) ((int) (sizeof(a) / sizeof((a)[0])))

/* Whether two codes are the same item: by their numbers for codes with a variant (as `a`
 * has one), else by the codes. `a`'s number is asked for first. */
static int item_form_same(u16 *a, u16 *b)
{
    if (ItemCode_HasVariant(a)) {
        int number = ItemCode_VariantItem(a);
        return number == ItemCode_VariantItem(b);
    }
    return *a == *b;
}

static int item_form_in(unsigned int code, unsigned int first, unsigned int last)
{
    return code >= first && code <= last;
}

/* func_020617f0: the replaced items (ItemForm_Replacement) replaced on the town's map and the
 * five rooms' maps, in the pockets of every player record there is (a slot in state 0 only,
 * the replacement then also marked in the record's items had), in the town's lists B and A,
 * and in the four players' storages. For pockets the replacement is compared first; elsewhere
 * the item kept is. */
void ItemForm_ReplaceEverywhere(void)
{
    ItemForm_ReplaceOnMap((AcreMap *) (uintptr_t) AcreMap_Town());
    for (int room = 0; room < ITEM_FORM_ROOM_MAPS; room++) {
        ItemForm_ReplaceOnMap((AcreMap *) (uintptr_t) AcreMap_Room(room));
    }

    for (int number = 0; number < ITEM_FORM_PLAYER_RECORDS; number++) {
        u8 *player = PlayerRecords_Get(number);
        if (player == NULL) {
            continue;
        }
        for (int slot = 0; slot < ITEM_FORM_POCKET_SLOTS; slot++) {
            int state = PlayerPockets_SlotState(PlayerRecord_Pockets(player), slot);
            u16 item = *PlayerPockets_Slot(PlayerRecord_Pockets(player), slot);
            u16 replacement;
            ItemForm_Replacement(&replacement, &item);
            if (!item_form_same(&replacement, &item) && state == 0) {
                PlayerPockets_SetSlot(PlayerRecord_Pockets(player), &replacement, slot, 0);
                ItemRecord_Mark((ItemRecord *) PlayerRecord_ItemRecord(player), &replacement, 0);
            }
        }
    }

    for (u32 place = 0; place < TOWN_ITEM_LIST_PLACES; place++) {
        u16 item = (u16) TownItemLists_ListBItem(place);
        u16 replacement;
        ItemForm_Replacement(&replacement, &item);
        if (!item_form_same(&item, &replacement)) {
            TownItemLists_PutListB(place, replacement);
        }
    }

    for (int place = 0; place < TOWN_ITEM_LIST_PLACES; place++) {
        u16 item = data_021f3a68[place];
        u16 replacement;
        ItemForm_Replacement(&replacement, &item);
        if (!item_form_same(&item, &replacement)) {
            data_021f3a68[place] = replacement;
        }
    }

    for (int storage = 0; storage < ITEM_FORM_STORAGES; storage++) {
        u16 *items = PlayerStorage_Items(&data_021f2fa8[storage]);
        for (int place = 0; place < PLAYER_STORAGE_ITEMS; place++) {
            u16 item = items[place];
            u16 replacement;
            ItemForm_Replacement(&replacement, &item);
            if (!item_form_same(&item, &replacement)) {
                items[place] = replacement;
            }
        }
    }
}
CLEAN_AS(func_020617f0, ItemForm_ReplaceEverywhere)

/* func_02061a14: the replaced items replaced on layer 0 of `map`, tile by tile, row by row
 * (nothing for no map). */
void ItemForm_ReplaceOnMap(AcreMap *map)
{
    if (map == NULL) {
        return;
    }
    for (int z = 0; z < map->tiles_high; z++) {
        for (int x = 0; x < map->tiles_wide; x++) {
            int acre_x = x / ITEM_FORM_ACRE_TILES;
            int acre_z = z / ITEM_FORM_ACRE_TILES;
            u16 *item =
                AcreTile_ItemInAcre(map, (u32) acre_x, (u32) acre_z, x % ITEM_FORM_ACRE_TILES, z % ITEM_FORM_ACRE_TILES, 0);
            if (item == NULL) {
                continue;
            }
            u16 replacement;
            ItemForm_Replacement(&replacement, item);
            if (!item_form_same(item, &replacement)) {
                AcreTile_SetItem(map, &replacement, x, z, 0);
            }
        }
    }
}
CLEAN_AS(func_02061a14, ItemForm_ReplaceOnMap)

/* func_02061ac4: the item that stands for `*item`: for the 20 replaced items (any variant) the
 * matching one of the 20 after them, with variant 0; any other code is itself. */
void ItemForm_Replacement(u16 *out, const u16 *item)
{
    u16 code = *item;
    if (item_form_in(code, ITEM_FORM_REPLACED_FIRST, ITEM_FORM_REPLACED_LAST)) {
        unsigned int index = (unsigned int) (code - ITEM_FORM_REPLACED_FIRST) >> 2;
        if (index < ITEM_FORM_REPLACED_ITEMS) {
            *out = (u16) (ITEM_FORM_REPLACEMENT_FIRST + index * 4);
            return;
        }
    }
    *out = code;
}
CLEAN_AS(func_02061ac4, ItemForm_Replacement)

/* func_02061b1c: the code `*item` is placed as. In a room (data_020e54a8 is 1) or with
 * `in_room` set, a carried item's room code (variant 0); outdoors, the outdoor code of the few
 * that have one. Any other code is itself. */
void ItemForm_ToPlaced(u16 *out, u16 *item, int in_room)
{
    unsigned int code = *item;
    if (data_020e54a8 == 1 || in_room) {
        for (int i = 0; i < ITEM_FORM_COUNT(item_form_room_runs); i++) {
            const ItemFormRun *run = &item_form_room_runs[i];
            if (item_form_in(code, run->first, run->last)) {
                *out = (u16) (run->placed + (code - run->first) * 4);
                return;
            }
        }
    } else {
        for (int i = 0; i < ITEM_FORM_COUNT(item_form_outdoor_runs); i++) {
            const ItemFormRun *run = &item_form_outdoor_runs[i];
            if (item_form_in(code, run->first, run->last)) {
                *out = (u16) (run->placed + (code - run->first));
                return;
            }
        }
    }
    *out = (u16) code;
}
CLEAN_AS(func_02061b1c, ItemForm_ToPlaced)

/* func_02061e2c: the item a placed code stands for when carried (any variant). A code shared
 * by the items 0x1408-0x1428 and 0x1471-0x1491 (in a room or outdoors) is the first of the two
 * its test accepts (func_0204be38, then func_0204bd84), else 0x137c. Any other code is itself. */
void ItemForm_ToCarried(u16 *out, u16 *item)
{
    u16 code = *item;
    for (int i = 0; i < ITEM_FORM_COUNT(item_form_carried_runs); i++) {
        const ItemFormRun *run = &item_form_carried_runs[i];
        if (item_form_in(code, run->first, run->last)) {
            *out = (u16) (run->placed + ((code - run->first) >> 2));
            return;
        }
    }

    int index = -1;
    if (item_form_in(code, ITEM_FORM_SHARED_PLACED_FIRST, ITEM_FORM_SHARED_PLACED_LAST)) {
        index = (code - ITEM_FORM_SHARED_PLACED_FIRST) >> 2;
    }
    if (code <= ITEM_FORM_SHARED_OUTDOORS_LAST) {
        index = code;
    }
    if (index != -1) {
        u16 first = (u16) (ITEM_FORM_SHARED_FIRST_A + index);
        if (ItemTraits_IsPairHeadItem(&first)) {
            *out = first;
            return;
        }
        u16 second = (u16) (ITEM_FORM_SHARED_FIRST_B + index);
        if (ItemTraits_IsPairFaceItem(&second)) {
            *out = second;
            return;
        }
        *out = ITEM_FORM_SHARED_OTHER;
        return;
    }

    if (item_form_in(code, ITEM_FORM_OUTDOOR_RUN_FIRST, ITEM_FORM_OUTDOOR_RUN_LAST)) {
        int run =
            code < ITEM_FORM_OUTDOOR_RUN_SECOND ? code - ITEM_FORM_OUTDOOR_RUN_FIRST : code - ITEM_FORM_OUTDOOR_RUN_SECOND;
        *out = (u16) (ITEM_FORM_OUTDOOR_RUN_ITEM + run);
        return;
    }
    *out = code;
}
CLEAN_AS(func_02061e2c, ItemForm_ToCarried)
