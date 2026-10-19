/* What the game asks of an item code beyond its group (item_traits.h).
 *
 * The originals keep their item codes on the stack as small objects: the constructor stores
 * the code (ItemTraits_ConstructCode) and the destructor (func_020051b0) does nothing; here
 * they are plain halfwords. */
#include "item_traits.h"

#include "clean.h"
#include "creature_table.h"
#include "furniture_info.h"
#include "insect_tables.h"
#include "item_code.h"
#include "item_form.h"
#include "item_group.h"
#include "item_info.h"
#include "nook_store.h"
#include "player_record.h"
#include "player_records.h"
#include "shop_points.h"
#include "state_block.h"
#include "town_record.h"

/* The pair of this index is never paired. */
#define ITEM_TRAITS_UNPAIRED 30
#define ITEM_TRAITS_PAIRS 0x21
#define ITEM_TRAITS_BELL_BAGS 0x6c
#define ITEM_TRAITS_SMALLEST_BAG 0x1492
#define ITEM_TRAITS_BIGGEST_BAG 0x14fd
/* ItemCode_Kind of a carried item and of the two kinds of room codes. */
#define ITEM_TRAITS_KIND_CARRIED 1
#define ITEM_TRAITS_KIND_ROOM_A 3
#define ITEM_TRAITS_KIND_ROOM_B 4
/* ItemTraits_Class of the room codes outside kind 1 (item_lists.c, current_pockets.c). */
#define ITEM_TRAITS_CLASS_ROOM_450C 0x39
#define ITEM_TRAITS_CLASS_ROOM_45DC 0x3a
#define ITEM_TRAITS_CLASS_ROOM_OTHER 0x3b
/* ItemTraits_Unk02 of the room codes 0x450c-0x45db. */
#define ITEM_TRAITS_UNK02_ROOM_450C 0xa7
/* ItemTraits_FishValue and ItemTraits_FishGroupOrder of an item that is no fish. */
#define ITEM_TRAITS_NO_FISH_VALUE 10
#define ITEM_TRAITS_NO_FISH_ORDER 4
#define ITEM_TRAITS_HEAD_A_UNK07 8

/* An arithmetic shift right, as the ARM's ASR does it, for negative values too. */
static int shift_right(int value, int bits)
{
    return value >= 0 ? value >> bits : ~(~value >> bits);
}

/* The carried form of an item (ItemForm_ToCarried; it only reads the item). */
static ItemCode carried_form(const ItemCode *item)
{
    ItemCode carried;
    ItemForm_ToCarried(&carried, (u16 *) (uintptr_t) item);
    return carried;
}

/* func_0204b3cc: an item code's constructor with its
 * code. QUIRK: keeps the low 16 bits of `code`. */
void ItemTraits_ConstructCode(ItemCode *item, int code)
{
    *item = (ItemCode) code;
}
CLEAN_AS(func_0204b3cc, ItemTraits_ConstructCode)

/* func_0204c4b8 */
void ItemTraits_CopyCode(ItemCode *dst, const ItemCode *src)
{
    *dst = *src;
}
CLEAN_AS(func_0204c4b8, ItemTraits_CopyCode)

/* func_0204be38: a head item of a pair that counts (its always.bin flag bit 1). */
int ItemTraits_IsPairHeadItem(const ItemCode *item)
{
    if (ItemGroup_IsHeadC(item) && ItemGroup_HeadCIndex(item) != ITEM_TRAITS_UNPAIRED) {
        return ItemInfo_FlagBit1(item);
    }
    return 0;
}
CLEAN_AS(func_0204be38, ItemTraits_IsPairHeadItem)

/* func_0204bd84: a part C item of a pair that counts (its head item does not). */
int ItemTraits_IsPairFaceItem(const ItemCode *item)
{
    if (!ItemGroup_IsPartC2(item)) {
        return 0;
    }
    int index = ItemGroup_PartC2Index(item);
    if (index == ITEM_TRAITS_UNPAIRED) {
        return 0;
    }
    ItemCode head = ItemGroup_HeadC((u32) index);
    return !ItemTraits_IsPairHeadItem(&head);
}
CLEAN_AS(func_0204bd84, ItemTraits_IsPairFaceItem)

/* func_0204beb0: into `out` the part C item of a pair that counts with this number (0 when
 * the number is not below their count); the first part C item 0x1471 when none is found. */
void ItemTraits_PairFaceItem(ItemCode *out, u32 number)
{
    if (number >= ItemInfo_CountSecondOfPair()) {
        number = 0;
    }
    u32 found = 0;
    for (u32 i = 0; i < ITEM_TRAITS_PAIRS; i++) {
        ItemCode item = ItemGroup_PartC2(i);
        if (ItemTraits_IsPairFaceItem(&item)) {
            if (found == number) {
                *out = item;
                return;
            }
            found++;
        }
    }
    *out = ItemGroup_PartC2(0);
}
CLEAN_AS(func_0204beb0, ItemTraits_PairFaceItem)

/* func_0204bf38: the same for the head items of the pairs (0x1408 when none is found). */
void ItemTraits_PairHeadItem(ItemCode *out, u32 number)
{
    if (number >= (u32) ItemInfo_CountFirstOfPair()) {
        number = 0;
    }
    u32 found = 0;
    for (u32 i = 0; i < ITEM_TRAITS_PAIRS; i++) {
        ItemCode item = ItemGroup_HeadC(i);
        if (ItemTraits_IsPairHeadItem(&item)) {
            if (found == number) {
                *out = item;
                return;
            }
            found++;
        }
    }
    *out = ItemGroup_HeadC(0);
}
CLEAN_AS(func_0204bf38, ItemTraits_PairHeadItem)

/* func_0204bfa0: the number of a part C item of a pair that counts, -1 for another item. */
int ItemTraits_PairFaceNumber(const ItemCode *item)
{
    if (!ItemTraits_IsPairFaceItem(item)) {
        return -1;
    }
    for (u32 i = 0; i < ItemInfo_CountSecondOfPair(); i++) {
        ItemCode numbered;
        ItemTraits_PairFaceItem(&numbered, i);
        if (*item == numbered) {
            return (int) i;
        }
    }
    return -1;
}
CLEAN_AS(func_0204bfa0, ItemTraits_PairFaceNumber)

/* func_0204bff4: the number of a head item of a pair that counts, -1 for another item. */
int ItemTraits_PairHeadNumber(const ItemCode *item)
{
    if (!ItemTraits_IsPairHeadItem(item)) {
        return -1;
    }
    for (u32 i = 0; i < (u32) ItemInfo_CountFirstOfPair(); i++) {
        ItemCode numbered;
        ItemTraits_PairHeadItem(&numbered, i);
        if (*item == numbered) {
            return (int) i;
        }
    }
    return -1;
}
CLEAN_AS(func_0204bff4, ItemTraits_PairHeadNumber)

/* func_0204c120: the bag of bells for `bells`: with `round_up` the smallest bag worth at least
 * that much, else the biggest worth at most that much; 0xfff1 when no bag is. `*rest`, when
 * given, is set to the difference (0 for no bag). */
int ItemTraits_BellBagFor(int bells, int round_up, int *rest)
{
    if (rest != NULL) {
        *rest = 0;
    }
    if (round_up) {
        ItemCode bag = ITEM_TRAITS_BIGGEST_BAG;
        if (ItemTraits_Price(&bag) < bells) {
            return ITEM_CODE_NONE;
        }
        for (u32 i = 0; i < ITEM_TRAITS_BELL_BAGS; i++) {
            bag = ItemGroup_BellBag(i);
            int value = ItemTraits_Price(&bag);
            if (value >= bells) {
                if (rest != NULL) {
                    *rest = value - bells;
                }
                return bag;
            }
        }
    } else {
        ItemCode bag = ITEM_TRAITS_SMALLEST_BAG;
        if (ItemTraits_Price(&bag) > bells) {
            return ITEM_CODE_NONE;
        }
        for (u32 i = ITEM_TRAITS_BELL_BAGS; i != 0; i--) {
            bag = ItemGroup_BellBag(i - 1);
            int value = ItemTraits_Price(&bag);
            if (bells >= value) {
                if (rest != NULL) {
                    *rest = bells - value;
                }
                return bag;
            }
        }
    }
    return ITEM_CODE_NONE;
}
CLEAN_AS(func_0204c120, ItemTraits_BellBagFor)

/* func_0204c228: a cloth's style (its indoor.bin byte 0, villager_talk_part.c), 0 for another
 * item. */
u32 ItemTraits_ClothStyle(const ItemCode *item)
{
    if (!ItemGroup_IsCloth(item)) {
        return 0;
    }
    ItemCode code = *item;
    return ItemInfo_IndoorUnk00(&code);
}
CLEAN_AS(func_0204c228, ItemTraits_ClothStyle)

/* func_0204c260: for an item whose carried form is of kind 1 that form's always.bin flag bit
 * 4, for one with a variant its furniture's indoor flags 2 bit 0; 1 for any other. */
int ItemTraits_FlagBit4(const ItemCode *item)
{
    ItemCode carried = carried_form(item);
    if (ItemCode_Kind(&carried) == ITEM_TRAITS_KIND_CARRIED) {
        return ItemInfo_FlagBit4(&carried);
    }
    if (ItemCode_HasVariant(&carried)) {
        return FurnitureInfo_ItemIndoorFlags2Bit0(&carried);
    }
    return 1;
}
CLEAN_AS(func_0204c260, ItemTraits_FlagBit4)

/* func_0204c2b4: the same with always.bin flag bit 3 and indoor bit 7; 0 for any other. */
int ItemTraits_FlagBit3(const ItemCode *item)
{
    ItemCode carried = carried_form(item);
    if (ItemCode_Kind(&carried) == ITEM_TRAITS_KIND_CARRIED) {
        return ItemInfo_FlagBit3(&carried);
    }
    if (ItemCode_HasVariant(&carried)) {
        return FurnitureInfo_ItemIndoorBit7(&carried);
    }
    return 0;
}
CLEAN_AS(func_0204c2b4, ItemTraits_FlagBit3)

/* func_0204c308: an insect's size (InsectTables_Size), 0 for another item. */
u16 ItemTraits_InsectSize(const ItemCode *item)
{
    if (!ItemGroup_IsInsect(item)) {
        return 0;
    }
    return (u16) InsectTables_Size((u8) ItemGroup_InsectIndex(item));
}
CLEAN_AS(func_0204c308, ItemTraits_InsectSize)

/* func_0204c380: a fish's base value (CreatureTable_BaseValue), 10 for another item. */
int ItemTraits_FishValue(const ItemCode *item)
{
    if (!ItemGroup_IsFish(item)) {
        return ITEM_TRAITS_NO_FISH_VALUE;
    }
    return CreatureTable_BaseValue((u32) ItemGroup_FishIndex(item));
}
CLEAN_AS(func_0204c380, ItemTraits_FishValue)

/* func_0204c3f0: a fish's group (CreatureTable_Group) reordered: groups 1, 3, 2 and 0 give
 * 0 to 3; 4 for another group or another item. */
int ItemTraits_FishGroupOrder(const ItemCode *item)
{
    if (ItemGroup_IsFish(item)) {
        switch (CreatureTable_Group(ItemGroup_FishIndex(item))) {
            case 1:
                return 0;
            case 3:
                return 1;
            case 2:
                return 2;
            case 0:
                return 3;
            default:
                break;
        }
    }
    return ITEM_TRAITS_NO_FISH_ORDER;
}
CLEAN_AS(func_0204c3f0, ItemTraits_FishGroupOrder)

/* func_0204c438: whether an item's carried form is of kind 1 or has a variant and is neither
 * an insect nor a fish; into `out`, when given, that form, else 0xfff1. */
int ItemTraits_CarriedNonCreature(const ItemCode *item, ItemCode *out)
{
    ItemCode result = ITEM_CODE_NONE;
    int found = 0;
    ItemCode carried = carried_form(item);
    if ((ItemCode_IsKind1(&carried) || ItemCode_HasVariant(&carried)) && !ItemGroup_IsInsect(&carried) &&
        !ItemGroup_IsFish(&carried)) {
        result = carried;
        found = 1;
    }
    if (out != NULL) {
        *out = result;
    }
    return found;
}
CLEAN_AS(func_0204c438, ItemTraits_CarriedNonCreature)

/* func_0204c4c0: a head item 0x13a8-0x13c7 whose ItemTraits_Unk07 is 8. */
int ItemTraits_IsHeadAUnk07Is8(const ItemCode *item)
{
    return ItemGroup_IsHeadA(item) && ItemTraits_Unk07(item) == ITEM_TRAITS_HEAD_A_UNK07;
}
CLEAN_AS(func_0204c4c0, ItemTraits_IsHeadAUnk07Is8)

/* func_0204c4e8: for an item of kind 1 whether it has a held model, 0 for another. */
int ItemTraits_HasHeldModel(const ItemCode *item)
{
    if (ItemCode_Kind(item) != ITEM_TRAITS_KIND_CARRIED) {
        return 0;
    }
    ItemCode code = *item;
    return ItemInfo_HasHeldModel(&code);
}
CLEAN_AS(func_0204c4e8, ItemTraits_HasHeldModel)

/* func_0204c520: an item's class. When its carried form is of kind 1, the class of the item's
 * always.bin record; for an item with a variant 0x39 (0x450c-0x45db), 0x3a (0x45dc-0x47d7 and
 * 0x3894-0x38e3) or 0x3b; 0 for any other.
 * QUIRK: the record read is the item's own, not its carried form's: a room code whose carried
 * form is of kind 1 reads the record of the room code's low 12 bits (ItemInfo_Class). */
int ItemTraits_Class(const ItemCode *item)
{
    ItemCode carried = carried_form(item);
    if (ItemCode_Kind(&carried) == ITEM_TRAITS_KIND_CARRIED) {
        ItemCode code = *item;
        return ItemInfo_Class(&code);
    }
    if (!ItemCode_HasVariant(&carried)) {
        return 0;
    }
    if (ItemGroup_IsRoom450c(&carried)) {
        return ITEM_TRAITS_CLASS_ROOM_450C;
    }
    if (ItemGroup_IsRoom45dc(&carried) || ItemGroup_IsRoom3894(&carried)) {
        return ITEM_TRAITS_CLASS_ROOM_45DC;
    }
    return ITEM_TRAITS_CLASS_ROOM_OTHER;
}
CLEAN_AS(func_0204c520, ItemTraits_Class)

/* func_0204c63c: for an item whose carried form is of kind 1 that form's always.bin byte 7;
 * for one of kind 3 or 4 whether it is one of 0x45dc-0x47d7; 0 for any other. */
int ItemTraits_Unk07(const ItemCode *item)
{
    ItemCode carried = carried_form(item);
    switch (ItemCode_Kind(&carried)) {
        case ITEM_TRAITS_KIND_CARRIED: {
            ItemCode code = carried;
            return ItemInfo_Unk07(&code);
        }
        case ITEM_TRAITS_KIND_ROOM_A:
        case ITEM_TRAITS_KIND_ROOM_B:
            return ItemGroup_IsRoom45dc(&carried) ? 1 : 0;
        default:
            return 0;
    }
}
CLEAN_AS(func_0204c63c, ItemTraits_Unk07)

/* func_0204c6b8: for an item of kind 1 its always.bin halfword 2; for one of kind 3 or 4 0xa7
 * (0x450c-0x45db), 1 (0x45dc-0x47d7) or 0; 0 for any other. */
int ItemTraits_Unk02(const ItemCode *item)
{
    switch (ItemCode_Kind(item)) {
        case ITEM_TRAITS_KIND_CARRIED: {
            ItemCode code = *item;
            return ItemInfo_Unk02(&code);
        }
        case ITEM_TRAITS_KIND_ROOM_A:
        case ITEM_TRAITS_KIND_ROOM_B:
            if (ItemGroup_IsRoom450c(item)) {
                return ITEM_TRAITS_UNK02_ROOM_450C;
            }
            return ItemGroup_IsRoom45dc(item) ? 1 : 0;
        default:
            return 0;
    }
}
CLEAN_AS(func_0204c6b8, ItemTraits_Unk02)

/* func_0204c788: an item's price at the store, halved (rounded down) during the store's time
 * sale (NookStore_IsTimeSale, 0 or 1) except for a bag of bells. */
int ItemTraits_StorePrice(const ItemCode *item)
{
    int price = ItemTraits_MemberPrice(item);
    if (ItemTraits_IsBellBag(item)) {
        return price;
    }
    StateBlock *block = (StateBlock *) (uintptr_t) ItemTraits_StateBlockAddress();
    return shift_right(price, NookStore_IsTimeSale((NookStore *) (void *) block->nook_store));
}
CLEAN_AS(func_0204c788, ItemTraits_StorePrice)

/* ---- an item's price ---- */

extern StateBlock data_021dc7a8;
extern int FX_Div(int numerator, int denominator);

/* The five items 0x1518-0x151c, the fruit of town_record.h. */
#define ITEM_TRAITS_FIRST_FRUIT 0x1518
#define ITEM_TRAITS_LAST_FRUIT 0x151c
#define ITEM_TRAITS_FRUITS 5
/* A bag of bells is worth ten times its always.bin price; the town's own fruit a fifth of it;
 * the items 0x1406 and 0x1407 and the variant item 0x208 a hundred times. */
#define ITEM_TRAITS_BAG_FACTOR 10
#define ITEM_TRAITS_OWN_FRUIT_DIVISOR 5
#define ITEM_TRAITS_HUNDREDFOLD 100
#define ITEM_TRAITS_HUNDREDFOLD_A 0x1406
#define ITEM_TRAITS_HUNDREDFOLD_B 0x1407
#define ITEM_TRAITS_HUNDREDFOLD_VARIANT 0x208
/* The discount of each shop points level (ShopPoints_Level), in percent. */
#define ITEM_TRAITS_LEVEL_2_DISCOUNT 5
#define ITEM_TRAITS_LEVEL_3_DISCOUNT 10
#define ITEM_TRAITS_LEVEL_4_DISCOUNT 20
#define ITEM_TRAITS_PERCENT 100
#define ITEM_TRAITS_FX_SHIFT 12

static int item_traits_times(int value, int factor)
{
    return (int) ((u32) value * (u32) factor);
}

/* func_0204c7c0: the address of the state block (data_021dc7a8). */
int ItemTraits_StateBlockAddress(void)
{
    return (int) (uintptr_t) &data_021dc7a8;
}
CLEAN_AS(func_0204c7c0, ItemTraits_StateBlockAddress)

/* func_0204c7c8: whether an item is a bag of bells, 0x1492-0x14fd. */
int ItemTraits_IsBellBag(const ItemCode *item)
{
    return *item >= ITEM_TRAITS_SMALLEST_BAG && *item <= ITEM_TRAITS_BIGGEST_BAG;
}
CLEAN_AS(func_0204c7c8, ItemTraits_IsBellBag)

/* func_0204c7f0: an item's price (ItemTraits_Price) less the discount of the current player's
 * shop points level: 5% at level 2, 10% at 3, 20% at 4. None for a bag of bells or without a
 * player. A discounted price of 100 or more is rounded down by an integer division, a smaller
 * one through FX_Div in 20.12 fixed point.
 * QUIRK: the product is kept in 32 bits and wraps. */
int ItemTraits_MemberPrice(const ItemCode *item)
{
    int price = ItemTraits_Price(item);
    if (ItemTraits_IsBellBag(item)) {
        return price;
    }
    u8 *player = PlayerRecords_Current();
    if (player == NULL) {
        return price;
    }
    int percent;
    switch (ItemTraits_ShopPointsLevel(ShopPoints_Count(PlayerRecord_ShopPoints(player)))) {
        case 2:
            percent = ITEM_TRAITS_LEVEL_2_DISCOUNT;
            break;
        case 3:
            percent = ITEM_TRAITS_LEVEL_3_DISCOUNT;
            break;
        case 4:
            percent = ITEM_TRAITS_LEVEL_4_DISCOUNT;
            break;
        default:
            percent = 0;
            break;
    }
    if (percent == 0) {
        return price;
    }
    int scaled = item_traits_times(price, ITEM_TRAITS_PERCENT - percent);
    if (scaled >= ITEM_TRAITS_PERCENT) {
        return scaled / ITEM_TRAITS_PERCENT;
    }
    int quotient = FX_Div((int) ((u32) scaled << ITEM_TRAITS_FX_SHIFT), ITEM_TRAITS_PERCENT << ITEM_TRAITS_FX_SHIFT);
    return shift_right(quotient, ITEM_TRAITS_FX_SHIFT);
}
CLEAN_AS(func_0204c7f0, ItemTraits_MemberPrice)

/* func_0204c86c: the shop points level of a count (ShopPoints_Level). */
int ItemTraits_ShopPointsLevel(const u16 *count)
{
    return ShopPoints_Level(*count);
}
CLEAN_AS(func_0204c86c, ItemTraits_ShopPointsLevel)

/* func_0204c878: an item's price in bells, by its carried form. Of kind 1: its always.bin price
 * (ItemInfo_Price), ten times that for a bag of bells (so a bag's price is the bells it
 * holds), a fifth for the town's own fruit, a hundred times for the items 0x1406 and 0x1407.
 * Of kinds 3 and 4: its variant item's FurnitureInfo_DmaUnk16, a hundred times for variant
 * item 0x208. 0 for another kind.
 * QUIRK: 0x1406 and 0x1407 are looked for in the item as given, not its carried form. */
int ItemTraits_Price(const ItemCode *item)
{
    ItemCode carried = carried_form(item);
    switch (ItemCode_Kind(&carried)) {
        case ITEM_TRAITS_KIND_CARRIED: {
            ItemCode code;
            if (ItemTraits_IsBellBag(&carried)) {
                code = (ItemCode) ItemCode_Get(&carried);
                return item_traits_times(ItemInfo_Price(&code), ITEM_TRAITS_BAG_FACTOR);
            }
            if (ItemTraits_IsFruit(&carried)) {
                int record = ItemTraits_StateBlockAddress() + (int) offsetof(StateBlock, part_17254);
                ItemCode own = ItemTraits_Fruit((u32) TownRecord_OwnFruit((const TownRecord *) (uintptr_t) (u32) record));
                if (ItemTraits_SameItem(&carried, &own)) {
                    code = (ItemCode) ItemCode_Get(&carried);
                    return ItemInfo_Price(&code) / ITEM_TRAITS_OWN_FRUIT_DIVISOR;
                }
            } else if (ItemCode_Get(item) == ITEM_TRAITS_HUNDREDFOLD_A || ItemCode_Get(item) == ITEM_TRAITS_HUNDREDFOLD_B) {
                code = (ItemCode) ItemCode_Get(&carried);
                return item_traits_times(ItemInfo_Price(&code), ITEM_TRAITS_HUNDREDFOLD);
            }
            code = (ItemCode) ItemCode_Get(&carried);
            return ItemInfo_Price(&code);
        }
        case ITEM_TRAITS_KIND_ROOM_A:
        case ITEM_TRAITS_KIND_ROOM_B: {
            int variant_item = ItemCode_VariantItem(&carried);
            int price = FurnitureInfo_DmaUnk16(variant_item);
            if (variant_item == ITEM_TRAITS_HUNDREDFOLD_VARIANT) {
                return item_traits_times(price, ITEM_TRAITS_HUNDREDFOLD);
            }
            return price;
        }
        default:
            return 0;
    }
}
CLEAN_AS(func_0204c878, ItemTraits_Price)

/* func_0204ca08: whether two items are the same: by their variant items when the first has a
 * variant, else by their codes. */
int ItemTraits_SameItem(const ItemCode *a, const ItemCode *b)
{
    if (ItemCode_HasVariant(a)) {
        int own = ItemCode_VariantItem(a);
        return own == ItemCode_VariantItem(b);
    }
    return *a == *b;
}
CLEAN_AS(func_0204ca08, ItemTraits_SameItem)

/* func_0204ca48: fruit `index` (0x1518 + index); 0x1518 for an index past the five. */
u16 ItemTraits_Fruit(u32 index)
{
    if (index < ITEM_TRAITS_FRUITS) {
        return (u16) (ITEM_TRAITS_FIRST_FRUIT + index);
    }
    return ITEM_TRAITS_FIRST_FRUIT;
}
CLEAN_AS(func_0204ca48, ItemTraits_Fruit)

/* func_0204ca64: whether an item is one of the fruit, 0x1518-0x151c. */
int ItemTraits_IsFruit(const ItemCode *item)
{
    return *item >= ITEM_TRAITS_FIRST_FRUIT && *item <= ITEM_TRAITS_LAST_FRUIT;
}
CLEAN_AS(func_0204ca64, ItemTraits_IsFruit)
