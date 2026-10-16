/* What the game knows of each piece of furniture (furniture_info.h). */
#include "furniture_info.h"

#include "clean.h"
#include "item_code.h"
#include "museum_record.h"

static_assert(sizeof(FurnitureAlways) == 8, "FurnitureAlways size");
static_assert(sizeof(FurnitureIndoor) == 4, "FurnitureIndoor size");
static_assert(sizeof(FurnitureDma) == 0x20, "FurnitureDma size");
static_assert(offsetof(FurnitureDma, unk_1e) == 0x1e, "FurnitureDma unk_1e");

extern u8 data_021c8c48[]; /* the three record files */

extern void *func_0206e6e4(void *files);                    /* dma.bin */
extern void *func_0206e6e8(void *files);                    /* indoor.bin */
extern void *func_0206e6ec(void *files);                    /* always.bin */
extern void *func_0206e7bc(void *file, unsigned int index); /* a record, NULL when it cannot be had */
extern u8 func_02053de4(int number);                        /* byte 0x18 of the number's dma.bin record */

/* The kinds of FurnitureDma.unk_18 FurnitureInfo_IndoorBit7 answers 0 for. */
#define DMA_18_NO_TURN_FIRST 0x23
#define DMA_18_NO_TURN_LAST 0x25

/* A number past the last reads as the last. QUIRK: a negative number is not caught. */
static unsigned int clamp_number(int number)
{
    return (unsigned int) (number >= FURNITURE_INFO_NUMBERS ? FURNITURE_INFO_NUMBERS - 1 : number);
}

static const FurnitureAlways *always_record(int number)
{
    return func_0206e7bc(func_0206e6ec(data_021c8c48), clamp_number(number));
}

static const FurnitureIndoor *indoor_record(int number)
{
    return func_0206e7bc(func_0206e6e8(data_021c8c48), clamp_number(number));
}

static const FurnitureDma *dma_record(int number)
{
    return func_0206e7bc(func_0206e6e4(data_021c8c48), clamp_number(number));
}

/* Bit `bit` of an indoor.bin record's flags; 0 without the record. */
static int indoor_flag(const FurnitureIndoor *record, int bit)
{
    return record != NULL ? (record->flags >> bit) & 1 : 0;
}

/* Bit `bit` of an always.bin record's flags; 0 without the record. */
static int always_flag(const FurnitureAlways *record, int bit)
{
    return record != NULL ? (record->flags >> bit) & 1 : 0;
}

/* func_020534ec: how many numbers are in `group`.
 * QUIRK: each number's code with variant 0 is made and dropped. The count is kept in 8 bits. */
u8 FurnitureInfo_CountInGroup(u32 group)
{
    u8 count = 0;
    for (u32 number = 0; number < FURNITURE_INFO_NUMBERS; number++) {
        (void) ItemCode_MakeVariant((int) number, 0);
        if (group == FurnitureInfo_Group((int) number)) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_020534ec, FurnitureInfo_CountInGroup)

/* func_0205352c: how many numbers below the item's are in the item's group (its place in its
 * group); 0 when no number matches the item. Each number is made into a code with variant 0 and
 * compared with the item by number (or by code, for a code without a variant, which never
 * happens). The count is cut to 8 bits. */
u8 FurnitureInfo_IndexInGroup(const ItemCode *item)
{
    int group = FurnitureInfo_ItemGroup(item);
    int count = 0;
    for (u32 number = 0; number < FURNITURE_INFO_NUMBERS; number++) {
        ItemCode code = ItemCode_MakeVariant((int) number, 0);
        int found;
        if (ItemCode_HasVariant(&code)) {
            int own = ItemCode_VariantItem(&code);
            found = own == ItemCode_VariantItem(item);
        } else {
            found = code == *item;
        }
        if (found) {
            return (u8) count;
        }
        if (group == FurnitureInfo_Group((int) number)) {
            count++;
        }
    }
    return 0;
}
CLEAN_AS(func_0205352c, FurnitureInfo_IndexInGroup)

/* func_020535b4: how many of the museum's group A items are of `kind`. */
int FurnitureInfo_CountMuseumKind(int kind)
{
    int count = 0;
    for (u32 i = 0; i < MUSEUM_A_ITEMS; i++) {
        ItemCode item = (ItemCode) (MUSEUM_A_FIRST + i * 4);
        if (kind == FurnitureInfo_MuseumKind(&item)) {
            count++;
        }
    }
    return count;
}
CLEAN_AS(func_020535b4, FurnitureInfo_CountMuseumKind)

/* func_020535f0: the kind of a museum group A item (FurnitureIndoor.kind); 0 for other codes. */
int FurnitureInfo_MuseumKind(const ItemCode *item)
{
    if (*item >= MUSEUM_A_FIRST && *item <= MUSEUM_A_LAST) {
        return FurnitureInfo_Kind(ItemCode_VariantItem(item));
    }
    return 0;
}
CLEAN_AS(func_020535f0, FurnitureInfo_MuseumKind)

/* func_02053624: FurnitureIndoor.kind. */
u8 FurnitureInfo_Kind(int number)
{
    const FurnitureIndoor *record = indoor_record(number);
    return record != NULL ? record->kind : 0;
}
CLEAN_AS(func_02053624, FurnitureInfo_Kind)

/* func_02053658: FurnitureDma.lift. */
s8 FurnitureInfo_Lift(int number)
{
    const FurnitureDma *record = dma_record(number);
    return record != NULL ? record->lift : 0;
}
CLEAN_AS(func_02053658, FurnitureInfo_Lift)

/* func_02053690: FurnitureDma.scale in 20.12 fixed point (percent). */
int FurnitureInfo_Scale(int number)
{
    const FurnitureDma *record = dma_record(number);
    int scale = record != NULL ? record->scale : 0;
    return scale << 12;
}
CLEAN_AS(func_02053690, FurnitureInfo_Scale)

/* func_020536c8 */
int FurnitureInfo_ItemIndoorFlags2Bit0(const ItemCode *item)
{
    if (ItemCode_HasVariant(item)) {
        return FurnitureInfo_IndoorFlags2Bit0(ItemCode_VariantItem(item));
    }
    return 0;
}
CLEAN_AS(func_020536c8, FurnitureInfo_ItemIndoorFlags2Bit0)

/* func_020536e8: bit 0 of FurnitureIndoor.flags2. */
int FurnitureInfo_IndoorFlags2Bit0(int number)
{
    const FurnitureIndoor *record = indoor_record(number);
    return record != NULL ? record->flags2 & 1 : 0;
}
CLEAN_AS(func_020536e8, FurnitureInfo_IndoorFlags2Bit0)

/* func_02053728 */
int FurnitureInfo_ItemIndoorBit7(const ItemCode *item)
{
    if (ItemCode_HasVariant(item)) {
        return FurnitureInfo_IndoorBit7(ItemCode_VariantItem(item));
    }
    return 0;
}
CLEAN_AS(func_02053728, FurnitureInfo_ItemIndoorBit7)

/* func_02053748: bit 7 of FurnitureIndoor.flags, but 0 for the furniture whose
 * FurnitureDma.unk_18 is 0x23-0x25 (read after the flag, by the unclamped number). */
int FurnitureInfo_IndoorBit7(int number)
{
    int flag = indoor_flag(indoor_record(number), 7);
    int kind = func_02053de4(number);
    if (kind >= DMA_18_NO_TURN_FIRST && kind <= DMA_18_NO_TURN_LAST) {
        return 0;
    }
    return flag;
}
CLEAN_AS(func_02053748, FurnitureInfo_IndoorBit7)

/* func_020537a8: bit 6 of FurnitureIndoor.flags. */
int FurnitureInfo_IndoorBit6(int number)
{
    return indoor_flag(indoor_record(number), 6);
}
CLEAN_AS(func_020537a8, FurnitureInfo_IndoorBit6)

/* func_020537e8: the dma.bin record, or NULL. */
const FurnitureDma *FurnitureInfo_Dma(int number)
{
    return dma_record(number);
}
CLEAN_AS(func_020537e8, FurnitureInfo_Dma)

/* func_02053818: the light kind: FURNITURE_LIGHT_BIT4 when bit 4 of FurnitureIndoor.flags is
 * set, else FURNITURE_LIGHT_BIT5 when bit 5 is, else FURNITURE_LIGHT_NONE. The record is looked
 * up a second time for bit 5. */
int FurnitureInfo_LightKind(int number)
{
    if (indoor_flag(indoor_record(number), 4)) {
        return FURNITURE_LIGHT_BIT4;
    }
    if (indoor_flag(indoor_record(number), 5)) {
        return FURNITURE_LIGHT_BIT5;
    }
    return FURNITURE_LIGHT_NONE;
}
CLEAN_AS(func_02053818, FurnitureInfo_LightKind)

/* func_0205389c: bit 3 of FurnitureIndoor.flags. */
int FurnitureInfo_IndoorBit3(int number)
{
    return indoor_flag(indoor_record(number), 3);
}
CLEAN_AS(func_0205389c, FurnitureInfo_IndoorBit3)

/* func_020538dc: bit 2 of FurnitureIndoor.flags. */
int FurnitureInfo_IndoorBit2(int number)
{
    return indoor_flag(indoor_record(number), 2);
}
CLEAN_AS(func_020538dc, FurnitureInfo_IndoorBit2)

/* func_0205391c: bit 0 of FurnitureIndoor.flags. */
int FurnitureInfo_IndoorBit0(int number)
{
    return indoor_flag(indoor_record(number), 0);
}
CLEAN_AS(func_0205391c, FurnitureInfo_IndoorBit0)

/* func_0205395c: FurnitureDma.unk_1a. */
int FurnitureInfo_DmaUnk1A(int number)
{
    const FurnitureDma *record = dma_record(number);
    return record != NULL ? record->unk_1a : 0;
}
CLEAN_AS(func_0205395c, FurnitureInfo_DmaUnk1A)

/* func_02053990 */
int FurnitureInfo_ItemCategory(const ItemCode *item)
{
    if (ItemCode_HasVariant(item)) {
        return FurnitureInfo_Category(ItemCode_VariantItem(item));
    }
    return 0;
}
CLEAN_AS(func_02053990, FurnitureInfo_ItemCategory)

/* func_020539b0: FurnitureAlways.category. */
u8 FurnitureInfo_Category(int number)
{
    const FurnitureAlways *record = always_record(number);
    return record != NULL ? record->category : 0;
}
CLEAN_AS(func_020539b0, FurnitureInfo_Category)

/* func_020539e4 */
int FurnitureInfo_ItemFlagBits23(const ItemCode *item)
{
    if (ItemCode_HasVariant(item)) {
        return FurnitureInfo_FlagBits23(ItemCode_VariantItem(item));
    }
    return 0;
}
CLEAN_AS(func_020539e4, FurnitureInfo_ItemFlagBits23)

/* func_02053a04: 1 when bit 2 of FurnitureAlways.flags is set, else 2 when bit 3 is, else 0.
 * The record is looked up twice, both times before bit 2 is tested. */
int FurnitureInfo_FlagBits23(int number)
{
    const FurnitureAlways *first = always_record(number);
    int bit2 = always_flag(first, 2);
    const FurnitureAlways *second = always_record(number);
    if (bit2) {
        return 1;
    }
    if (always_flag(second, 3)) {
        return 2;
    }
    return 0;
}
CLEAN_AS(func_02053a04, FurnitureInfo_FlagBits23)

/* func_02053a88 */
int FurnitureInfo_ItemFlagBits01(const ItemCode *item)
{
    if (ItemCode_HasVariant(item)) {
        return FurnitureInfo_FlagBits01(ItemCode_VariantItem(item));
    }
    return 0;
}
CLEAN_AS(func_02053a88, FurnitureInfo_ItemFlagBits01)

/* func_02053aa8: 1 when bit 0 of FurnitureAlways.flags is set, else 2 when bit 1 is, else 0.
 * The record is looked up twice, both times before bit 0 is tested. */
int FurnitureInfo_FlagBits01(int number)
{
    const FurnitureAlways *first = always_record(number);
    int bit0 = always_flag(first, 0);
    const FurnitureAlways *second = always_record(number);
    if (bit0) {
        return 1;
    }
    if (always_flag(second, 1)) {
        return 2;
    }
    return 0;
}
CLEAN_AS(func_02053aa8, FurnitureInfo_FlagBits01)

/* func_02053b2c: bit 4 of FurnitureAlways.flags. */
int FurnitureInfo_FlagBit4(int number)
{
    return always_flag(always_record(number), 4);
}
CLEAN_AS(func_02053b2c, FurnitureInfo_FlagBit4)

/* func_02053b6c */
int FurnitureInfo_ItemUnk03(const ItemCode *item)
{
    if (ItemCode_HasVariant(item)) {
        return FurnitureInfo_Unk03(ItemCode_VariantItem(item));
    }
    return 0;
}
CLEAN_AS(func_02053b6c, FurnitureInfo_ItemUnk03)

/* func_02053b8c: FurnitureAlways.unk_03. */
int FurnitureInfo_Unk03(int number)
{
    const FurnitureAlways *record = always_record(number);
    return record != NULL ? record->unk_03 : 0;
}
CLEAN_AS(func_02053b8c, FurnitureInfo_Unk03)

/* func_02053bc0 */
int FurnitureInfo_ItemShape(const ItemCode *item)
{
    if (ItemCode_HasVariant(item)) {
        return FurnitureInfo_Shape(ItemCode_VariantItem(item));
    }
    return 0;
}
CLEAN_AS(func_02053bc0, FurnitureInfo_ItemShape)

/* func_02053be0: FurnitureAlways.shape. */
u8 FurnitureInfo_Shape(int number)
{
    const FurnitureAlways *record = always_record(number);
    return record != NULL ? record->shape : 0;
}
CLEAN_AS(func_02053be0, FurnitureInfo_Shape)

/* func_02053c14 */
int FurnitureInfo_ItemUnk04(const ItemCode *item)
{
    if (ItemCode_HasVariant(item)) {
        return FurnitureInfo_Unk04(ItemCode_VariantItem(item));
    }
    return 0;
}
CLEAN_AS(func_02053c14, FurnitureInfo_ItemUnk04)

/* func_02053c34: FurnitureAlways.unk_04. */
u8 FurnitureInfo_Unk04(int number)
{
    const FurnitureAlways *record = always_record(number);
    return record != NULL ? record->unk_04 : 0;
}
CLEAN_AS(func_02053c34, FurnitureInfo_Unk04)

/* func_02053c68 */
int FurnitureInfo_ItemGroup(const ItemCode *item)
{
    if (ItemCode_HasVariant(item)) {
        return FurnitureInfo_Group(ItemCode_VariantItem(item));
    }
    return 0;
}
CLEAN_AS(func_02053c68, FurnitureInfo_ItemGroup)

/* func_02053c88: FurnitureAlways.group. */
u8 FurnitureInfo_Group(int number)
{
    const FurnitureAlways *record = always_record(number);
    return record != NULL ? record->group : 0;
}
CLEAN_AS(func_02053c88, FurnitureInfo_Group)

/* func_02053cbc: FurnitureAlways.unk_02. */
int FurnitureInfo_Unk02(int number)
{
    const FurnitureAlways *record = always_record(number);
    return record != NULL ? record->unk_02 : 0;
}
CLEAN_AS(func_02053cbc, FurnitureInfo_Unk02)

/* func_02053cf0: FurnitureAlways.unk_01. */
int FurnitureInfo_Unk01(int number)
{
    const FurnitureAlways *record = always_record(number);
    return record != NULL ? record->unk_01 : 0;
}
CLEAN_AS(func_02053cf0, FurnitureInfo_Unk01)

/* func_02053d24: FurnitureDma.unk_1e, with 0xff (none) read as -1. */
int FurnitureInfo_DmaUnk1E(int number)
{
    const FurnitureDma *record = dma_record(number);
    int value = record != NULL ? record->unk_1e : 0;
    return value == 0xff ? -1 : value;
}
CLEAN_AS(func_02053d24, FurnitureInfo_DmaUnk1E)
