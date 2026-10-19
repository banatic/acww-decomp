/* The record of items a player has had (item_record.h): marking an item, asking for it, and
 * counting the insects and the fish the current player has had. */
#include "item_record.h"

#include <string.h>

#include "clean.h"
#include "item_code.h"
#include "player_record.h"
#include "player_records.h"
#include "item_form.h"
#include "item_traits.h"

static_assert(offsetof(ItemRecord, wallpaper) == 0x100, "the wallpaper");
static_assert(offsetof(ItemRecord, carpets) == 0x109, "the carpets");
static_assert(offsetof(ItemRecord, songs) == 0x112, "the songs");
static_assert(offsetof(ItemRecord, pile_items) == 0x11b, "the items in piles");
static_assert(sizeof(ItemRecord) == 0x123, "the record of items");

#define WALLPAPER_FIRST 0x1100
#define WALLPAPER_LAST 0x1143
#define CARPET_FIRST 0x1144
#define CARPET_LAST 0x1187
#define SONG_FIRST 0x1323
#define SONG_LAST 0x1368

static int in_range(int code, int first, int last)
{
    return code >= first && code <= last;
}

/* func_0203cbd0: `*item` marked as had by the current player (0 when there is none or the item
 * has no bit). */
int ItemRecord_MarkHadByCurrent(const ItemCode *item)
{
    u8 *player = PlayerRecords_Current();
    if (player == NULL) {
        return 0;
    }
    return ItemRecord_Mark((ItemRecord *) PlayerRecord_ItemRecord(player), item, ITEM_RECORD_MARK_ANY);
}
CLEAN_AS(func_0203cbd0, ItemRecord_MarkHadByCurrent)

/* func_0203cbf4: how many kinds of insect the current player has had. */
int ItemRecord_CountInsects(void)
{
    return ItemRecord_CountHad(ITEM_RECORD_INSECT_FIRST, ITEM_RECORD_CREATURE_KINDS);
}
CLEAN_AS(func_0203cbf4, ItemRecord_CountInsects)

/* func_0203cc04: how many kinds of fish the current player has had. */
int ItemRecord_CountFish(void)
{
    return ItemRecord_CountHad(ITEM_RECORD_FISH_FIRST, ITEM_RECORD_CREATURE_KINDS);
}
CLEAN_AS(func_0203cc04, ItemRecord_CountFish)

/* func_0203cc14 */
int ItemRecord_InsectKinds(void)
{
    return ITEM_RECORD_CREATURE_KINDS;
}
CLEAN_AS(func_0203cc14, ItemRecord_InsectKinds)

/* func_0203cc18 */
int ItemRecord_FishKinds(void)
{
    return ITEM_RECORD_CREATURE_KINDS;
}
CLEAN_AS(func_0203cc18, ItemRecord_FishKinds)

/* func_0203cc1c */
int ItemRecord_HasAllInsects(void)
{
    int had = ItemRecord_CountInsects();
    return had == ItemRecord_InsectKinds();
}
CLEAN_AS(func_0203cc1c, ItemRecord_HasAllInsects)

/* func_0203cc38 */
int ItemRecord_HasAllFish(void)
{
    int had = ItemRecord_CountFish();
    return had == ItemRecord_FishKinds();
}
CLEAN_AS(func_0203cc38, ItemRecord_HasAllFish)

/* func_0203cc54: how many of the `count` items from `first` the current player has had,
 * counting only the listed ones (func_0204c2b4). `first` is either an item in a pile (then
 * each code from it is taken as its room code) or an item with variants (then the items that
 * follow it, each in variant 0); for any other code, and when there is no current player, 0.
 * QUIRK: the count is compared unsigned, so a negative `count` runs past every item. */
int ItemRecord_CountHad(int first, int count)
{
    u8 *player = PlayerRecords_Current();
    ItemCode first_code = (ItemCode) first;
    u32 had = 0;

    if (player == NULL) {
        return 0;
    }
    if (ItemCode_IsKind1(&first_code)) {
        for (u32 i = 0; i < (u32) count; i++) {
            ItemCode code = (ItemCode) (first + i);
            ItemCode room_code;
            ItemForm_ToPlaced(&room_code, &code, 1);
            code = room_code;
            if (ItemTraits_FlagBit3(&code) && ItemRecord_Has((ItemRecord *) PlayerRecord_ItemRecord(player), &code)) {
                had++;
            }
        }
    } else if (ItemCode_HasVariant(&first_code)) {
        ItemCode start = (ItemCode) first;
        int item = ItemCode_VariantItem(&start);
        for (u32 i = 0; i < (u32) count; i++) {
            ItemCode code = ItemCode_MakeVariant(item + (int) i, 0);
            if (ItemTraits_FlagBit3(&code) && ItemRecord_Has((ItemRecord *) PlayerRecord_ItemRecord(player), &code)) {
                had++;
            }
        }
    }
    return (int) had;
}
CLEAN_AS(func_0203cc54, ItemRecord_CountHad)

/* func_0203cd1c: `*item`
 * marked as had. */
int ItemRecord_Mark(ItemRecord *record, const ItemCode *item, int mode)
{
    return ItemRecord_SetBit(record, item, mode, 1);
}
CLEAN_AS(func_0203cd1c, ItemRecord_Mark)

/* func_0203cd2c: the bit of `*item` set (`set`) or cleared; 1 when the
 * item has a bit. With ITEM_RECORD_MARK_CHECKED the insects, the fish and the variant items
 * 0x42a4-0x4463 are refused (0, nothing written), by their code as given. */
int ItemRecord_SetBit(ItemRecord *record, const ItemCode *item, int mode, int set)
{
    if (mode == ITEM_RECORD_MARK_CHECKED) {
        int code = *item;
        if (in_range(code, ITEM_RECORD_FISH_FIRST, ITEM_RECORD_FISH_FIRST + ITEM_RECORD_CREATURE_KINDS - 1) ||
            in_range(code, ITEM_RECORD_INSECT_FIRST, ITEM_RECORD_INSECT_FIRST + ITEM_RECORD_CREATURE_KINDS - 1) ||
            in_range(code, 0x42a4, 0x4463)) {
            return 0;
        }
    }

    u8 mask;
    u8 *byte = ItemRecord_BitOf(record, &mask, item);
    if (byte == NULL) {
        return 0;
    }
    if (set) {
        *byte |= mask;
    } else {
        *byte &= (u8) ~mask;
    }
    return 1;
}
CLEAN_AS(func_0203cd2c, ItemRecord_SetBit)

/* func_0203cdcc: whether `*item` was had (0 for an item without a bit). */
int ItemRecord_Has(ItemRecord *record, const ItemCode *item)
{
    u8 mask;
    u8 *byte = ItemRecord_BitOf(record, &mask, item);
    if (byte == NULL) {
        return 0;
    }
    return (*byte & mask) != 0;
}
CLEAN_AS(func_0203cdcc, ItemRecord_Has)

/* func_0203cdf8: the byte holding the bit of `*item` (taken as its room code), with the bit in
 * `*mask`; NULL and a mask of 0 for an item without a bit. */
u8 *ItemRecord_BitOf(ItemRecord *record, u8 *mask, const ItemCode *item)
{
    ItemCode code;
    u8 *part;
    int index;

    ItemForm_ToPlaced(&code, (u16 *) item, 1);
    if (ItemCode_HasVariant(&code)) {
        part = record->variant_items;
        index = ItemCode_VariantItem(&code);
    } else if (in_range(code, WALLPAPER_FIRST, WALLPAPER_LAST)) {
        part = record->wallpaper;
        index = code - WALLPAPER_FIRST;
    } else if (in_range(code, CARPET_FIRST, CARPET_LAST)) {
        part = record->carpets;
        index = code - CARPET_FIRST;
    } else if (in_range(code, SONG_FIRST, SONG_LAST)) {
        part = record->songs;
        index = code - SONG_FIRST;
    } else if (in_range(code, ITEM_CODE_PILE_FIRST, ITEM_CODE_PILE_LAST)) {
        part = record->pile_items;
        index = ItemCode_PileItem(&code);
    } else {
        *mask = 0;
        return NULL;
    }
    *mask = (u8) (1u << (index & 7));
    return part + (index >> 3);
}
CLEAN_AS(func_0203cdf8, ItemRecord_BitOf)

/* func_0203cf38: emptied for a new player. */
void ItemRecord_Reset(ItemRecord *record)
{
    ItemRecord_Clear(record);
}
CLEAN_AS(func_0203cf38, ItemRecord_Reset)

/* func_0203cf40 */
void ItemRecord_Clear(ItemRecord *record)
{
    memset(record->variant_items, 0, sizeof(record->variant_items));
    memset(record->wallpaper, 0, sizeof(record->wallpaper));
    memset(record->carpets, 0, sizeof(record->carpets));
    memset(record->songs, 0, sizeof(record->songs));
    memset(record->pile_items, 0, sizeof(record->pile_items));
}
CLEAN_AS(func_0203cf40, ItemRecord_Clear)

/* func_0203cfa0: the destructor: nothing. */
void ItemRecord_Destruct(ItemRecord *record)
{
    (void) record;
}
CLEAN_AS(func_0203cfa0, ItemRecord_Destruct)

/* func_0203cfa4: the constructor: nothing (ItemRecord_Reset empties it). */
void ItemRecord_Construct(ItemRecord *record)
{
    (void) record;
}
CLEAN_AS(func_0203cfa4, ItemRecord_Construct)
