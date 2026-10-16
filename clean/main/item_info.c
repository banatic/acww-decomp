/* What the game knows of each item code of kinds 1 and 0 (item_info.h). */
#include "item_info.h"

#include "clean.h"
#include "item_code.h"

static_assert(sizeof(ItemInfoAlways) == 12, "ItemInfoAlways size");
static_assert(sizeof(ItemInfoIndoor) == 4, "ItemInfoIndoor size");
static_assert(sizeof(ItemInfoDma) == 0x18, "ItemInfoDma size");
static_assert(sizeof(ItemInfoSeries) == 0x18 && offsetof(ItemInfoSeries, kind) == 0x16, "ItemInfoSeries layout");
static_assert(offsetof(ItemInfoFiles, series) == 0x54, "ItemInfoFiles layout");

/* The four files. */
extern ItemInfoFiles data_021cb5e0;
/* The items with a held model: the first of them (ITEM_CODE_NONE before they are looked for)
 * and how many there are. */
extern u16 data_021cb5b0;
extern u32 data_021cb5c0;
/* The counts ItemInfo_CountSharedPairs and ItemInfo_CountUnk06Is1d keep. */
extern int data_021cb5b4; /* items 0x1408-0x1428 func_0204be38 accepts */
extern u32 data_021cb5b8; /* items 0x1471-0x1491 func_0204bd84 accepts (the first refused) */
extern int data_021cb5bc; /* items 0x13a8-0x13c7 with unk_06 0x1d */
extern u32 data_021cb5c4; /* items 0x13c8-0x1407 with unk_06 0x1d */
/* By look (0-0x48), the names of its two models: outdoors, and in a room. */
extern const char *const data_020de368[][2];
/* The points of each value 0-45 of FurnitureAlways.unk_04 (room_score.c). */
extern const u16 data_020cca34[];

/* The record files' own functions. */
extern void *func_0206e6e4(void *files);                    /* dma.bin */
extern void *func_0206e6e8(void *files);                    /* indoor.bin */
extern void *func_0206e6ec(void *files);                    /* always.bin */
extern void *func_0206e7bc(void *file, unsigned int index); /* a record, NULL when it cannot be had */
extern int func_0206e6f0(void *files);                      /* free indoor.bin's whole copy */
extern int func_0206e704(void *files, int stream);          /* unless `stream`, load it whole */
/* Close the files; open them and count the items (both past this block). */
extern void func_02062ca4(void *files);
extern int func_02062cbc(void *files);
/* Whether an item is the first or the second of its pair (item_form.h). */
extern int func_0204be38(u16 *item);
extern int func_0204bd84(u16 *item);

#define ITEM_INFO_LAST_NUMBER (ITEM_INFO_NUMBERS - 1)
#define ITEM_INFO_NUMBER_MASK 0xfff
#define ITEM_INFO_PILE_COUNT_MASK 3
#define ITEM_INFO_SCORE_VALUES 46
#define ITEM_INFO_NO_SERIES_KIND 3
#define ITEM_INFO_CLASS_WITH_UNK_08 5
/* The flag bits of ItemInfoAlways.flags. */
#define ITEM_INFO_FLAG_HELD_MODEL 0
/* The codes looked through for held models. */
#define ITEM_INFO_FIRST_CODE 0x1000
/* The items whose unk_06 0x1d ItemInfo_CountUnk06Is1d counts. */
#define ITEM_INFO_UNK_06_COUNTED 0x1d
#define ITEM_INFO_13C8_FIRST 0x13c8
#define ITEM_INFO_13C8_ITEMS 0x40
#define ITEM_INFO_13A8_FIRST 0x13a8
#define ITEM_INFO_13A8_ITEMS 0x20
/* The pairs ItemInfo_CountSharedPairs counts. */
#define ITEM_INFO_PAIR_FIRST_A 0x1408
#define ITEM_INFO_PAIR_FIRST_B 0x1471
#define ITEM_INFO_PAIRS 0x21

static int item_info_is_pile(u16 code)
{
    return code >= ITEM_CODE_PILE_FIRST && code <= ITEM_CODE_PILE_LAST;
}

/* The record number of a code (its low 12 bits, past the last read as the last). */
static unsigned int item_info_number(u16 code)
{
    unsigned int number = code & ITEM_INFO_NUMBER_MASK;
    return number >= ITEM_INFO_NUMBERS ? ITEM_INFO_LAST_NUMBER : number;
}

/* The record number of a code, an item in a pile read as its full pile. */
static unsigned int item_info_full_number(const u16 *item)
{
    u16 code = *item;
    if (item_info_is_pile(code)) {
        code |= ITEM_INFO_PILE_COUNT_MASK;
    }
    return item_info_number(code);
}

static const ItemInfoAlways *item_info_always(unsigned int number)
{
    return func_0206e7bc(func_0206e6ec(&data_021cb5e0), number);
}

static const ItemInfoIndoor *item_info_indoor(unsigned int number)
{
    return func_0206e7bc(func_0206e6e8(&data_021cb5e0), number);
}

/* Bit `bit` of the flags of the item's full pile; 0 without the record. */
static int item_info_flag(const u16 *item, int bit)
{
    const ItemInfoAlways *record = item_info_always(item_info_full_number(item));
    return record != NULL ? (record->flags >> bit) & 1 : 0;
}

/* Whether two codes are the same item: by their numbers for codes with a variant (as `a`
 * has one), else by the codes. `a`'s number is asked for first. */
static int item_info_same(const u16 *a, const u16 *b)
{
    if (ItemCode_HasVariant(a)) {
        int number = ItemCode_VariantItem(a);
        return number == ItemCode_VariantItem(b);
    }
    return *a == *b;
}

/* func_02062118 */
int ItemInfo_Count13a8Unk06Is1d(void)
{
    return data_021cb5bc;
}
CLEAN_AS(func_02062118, ItemInfo_Count13a8Unk06Is1d)

/* func_02062124 */
u32 ItemInfo_Count13c8Unk06Is1d(void)
{
    return data_021cb5c4;
}
CLEAN_AS(func_02062124, ItemInfo_Count13c8Unk06Is1d)

/* func_02062130 */
u32 ItemInfo_CountSecondOfPair(void)
{
    return data_021cb5b8;
}
CLEAN_AS(func_02062130, ItemInfo_CountSecondOfPair)

/* func_0206213c */
int ItemInfo_CountFirstOfPair(void)
{
    return data_021cb5b4;
}
CLEAN_AS(func_0206213c, ItemInfo_CountFirstOfPair)

/* func_02062148: the item's number among the items with a held model (from 0, in code order),
 * compared as ItemCode_HasVariant says; 0xffffffff when it has none or none was found. */
u32 ItemInfo_HeldModelNumber(const u16 *item)
{
    if (data_021cb5c0 == 0) {
        return 0xffffffff;
    }
    u32 number = 0;
    for (u16 code = data_021cb5b0; code < ITEM_INFO_NUMBERS + ITEM_INFO_FIRST_CODE; code++) {
        u16 candidate = code;
        if (!ItemInfo_HasHeldModel(&candidate)) {
            continue;
        }
        if (item_info_same(&candidate, item)) {
            return number;
        }
        number++;
    }
    return 0xffffffff;
}
CLEAN_AS(func_02062148, ItemInfo_HeldModelNumber)

/* func_020621d4: the item with a held model of number `number`; the first of them when there
 * is no such number. */
void ItemInfo_HeldModelItem(u16 *out, int number)
{
    if (data_021cb5c0 != 0) {
        int index = 0;
        for (u16 code = data_021cb5b0; code < ITEM_INFO_NUMBERS + ITEM_INFO_FIRST_CODE; code++) {
            u16 candidate = code;
            if (!ItemInfo_HasHeldModel(&candidate)) {
                continue;
            }
            if (index == number) {
                *out = candidate;
                return;
            }
            index++;
        }
    }
    *out = data_021cb5b0;
}
CLEAN_AS(func_020621d4, ItemInfo_HeldModelItem)

/* func_02062230: how many items have a held model. */
u32 ItemInfo_HeldModelCount(void)
{
    return data_021cb5c0;
}
CLEAN_AS(func_02062230, ItemInfo_HeldModelCount)

/* func_0206223c: the name of look `look`'s model outdoors (`outdoors` not 0) or in a room; a
 * look past the last is look 0's.
 * REQUIRES: `look` is not negative. */
const char *ItemInfo_LookModelName(int look, int outdoors)
{
    if (look >= ITEM_INFO_LOOKS) {
        return ItemInfo_LookModelName(0, outdoors);
    }
    return data_020de368[look][outdoors == 0];
}
CLEAN_AS(func_0206223c, ItemInfo_LookModelName)

/* func_0206226c: the points a value of FurnitureAlways.unk_04 gives a room; 0 from 46.
 * REQUIRES: `value` is not negative. */
int ItemInfo_ScorePoints(int value)
{
    if (value < ITEM_INFO_SCORE_VALUES) {
        return data_020cca34[value];
    }
    return 0;
}
CLEAN_AS(func_0206226c, ItemInfo_ScorePoints)

/* func_02062280: the record of series `series`; NULL past the last or when it cannot be had. */
const ItemInfoSeries *ItemInfo_SeriesRecord(int series)
{
    if (series < ITEM_INFO_SERIES) {
        const ItemInfoSeries *record = func_0206e7bc(&data_021cb5e0.series, (unsigned int) series);
        if (record != NULL) {
            return record;
        }
    }
    return NULL;
}
CLEAN_AS(func_02062280, ItemInfo_SeriesRecord)

/* func_020622a0: ItemInfoSeries.kind; 3 for a series past the last or without its record. */
u8 ItemInfo_SeriesKind(int series)
{
    if (series >= ITEM_INFO_SERIES) {
        return ITEM_INFO_NO_SERIES_KIND;
    }
    const ItemInfoSeries *record = func_0206e7bc(&data_021cb5e0.series, (unsigned int) series);
    return record != NULL ? record->kind : ITEM_INFO_NO_SERIES_KIND;
}
CLEAN_AS(func_020622a0, ItemInfo_SeriesKind)

/* func_020622c4: ItemInfoIndoor.unk_00. */
u8 ItemInfo_IndoorUnk00(const u16 *item)
{
    const ItemInfoIndoor *record = item_info_indoor(item_info_number(*item));
    return record != NULL ? record->unk_00 : 0;
}
CLEAN_AS(func_020622c4, ItemInfo_IndoorUnk00)

/* func_02062300: ItemInfoIndoor.unk_01. */
u8 ItemInfo_IndoorUnk01(const u16 *item)
{
    const ItemInfoIndoor *record = item_info_indoor(item_info_number(*item));
    return record != NULL ? record->unk_01 : 0;
}
CLEAN_AS(func_02062300, ItemInfo_IndoorUnk01)

/* func_0206233c: bit 4 of the flags (of the full pile). */
int ItemInfo_FlagBit4(const u16 *item)
{
    return item_info_flag(item, 4);
}
CLEAN_AS(func_0206233c, ItemInfo_FlagBit4)

/* func_02062408: bit 3 of the flags (of the full pile). */
int ItemInfo_FlagBit3(const u16 *item)
{
    return item_info_flag(item, 3);
}
CLEAN_AS(func_02062408, ItemInfo_FlagBit3)

/* func_020624d4: bit 2 of the flags (of the full pile). */
int ItemInfo_FlagBit2(const u16 *item)
{
    return item_info_flag(item, 2);
}
CLEAN_AS(func_020624d4, ItemInfo_FlagBit2)

/* func_020625a0: bit 1 of the flags (of the full pile). */
int ItemInfo_FlagBit1(const u16 *item)
{
    return item_info_flag(item, 1);
}
CLEAN_AS(func_020625a0, ItemInfo_FlagBit1)

/* func_0206266c: whether the item (its full pile) has a held model (bit 0 of the flags). */
int ItemInfo_HasHeldModel(const u16 *item)
{
    return item_info_flag(item, ITEM_INFO_FLAG_HELD_MODEL);
}
CLEAN_AS(func_0206266c, ItemInfo_HasHeldModel)

/* func_02062734: for an item of class 5, ItemInfoAlways.unk_08 (0 without the record); -1 for
 * any other. */
int ItemInfo_Class5Unk08(const u16 *item)
{
    if (ItemInfo_Class(item) != ITEM_INFO_CLASS_WITH_UNK_08) {
        return -1;
    }
    const ItemInfoAlways *record = item_info_always(item_info_number(*item));
    return record != NULL ? record->unk_08 : 0;
}
CLEAN_AS(func_02062734, ItemInfo_Class5Unk08)

/* func_02062780: ItemInfoAlways.unk_07. */
u8 ItemInfo_Unk07(const u16 *item)
{
    const ItemInfoAlways *record = item_info_always(item_info_number(*item));
    return record != NULL ? record->unk_07 : 0;
}
CLEAN_AS(func_02062780, ItemInfo_Unk07)

/* func_020627bc: ItemInfoAlways.unk_06 (of the full pile). */
int ItemInfo_Unk06(const u16 *item)
{
    const ItemInfoAlways *record = item_info_always(item_info_full_number(item));
    return record != NULL ? record->unk_06 : 0;
}
CLEAN_AS(func_020627bc, ItemInfo_Unk06)

/* func_02062870: ItemInfoAlways.item_class. */
u8 ItemInfo_Class(const u16 *item)
{
    const ItemInfoAlways *record = item_info_always(item_info_number(*item));
    return record != NULL ? record->item_class : 0;
}
CLEAN_AS(func_02062870, ItemInfo_Class)

/* func_020628ac: the bells the item is worth: its full pile's price, and for an item in a
 * pile that price for as many of the four as the pile holds (rounded down, in 16 bits). */
int ItemInfo_Price(const u16 *item)
{
    const ItemInfoAlways *record = item_info_always(item_info_full_number(item));
    int price = record != NULL ? record->price : 0;
    u16 code = *item;
    if (item_info_is_pile(code)) {
        int count = (code & ITEM_INFO_PILE_COUNT_MASK) + 1;
        price = (u16) ((price * count) >> 2);
    }
    return price;
}
CLEAN_AS(func_020628ac, ItemInfo_Price)

/* func_02062998: ItemInfoAlways.series. */
u8 ItemInfo_Series(const u16 *item)
{
    const ItemInfoAlways *record = item_info_always(item_info_number(*item));
    return record != NULL ? record->series : 0;
}
CLEAN_AS(func_02062998, ItemInfo_Series)

/* func_020629d4: -1 for every item. Read with ItemInfo_NoneB and ItemInfo_NoneC, as the
 * FurnitureInfo ones are (func_02062ea4). */
int ItemInfo_NoneA(const u16 *item)
{
    (void) item;
    return -1;
}
CLEAN_AS(func_020629d4, ItemInfo_NoneA)

/* func_020629dc: -1 for every item. */
int ItemInfo_NoneB(const u16 *item)
{
    (void) item;
    return -1;
}
CLEAN_AS(func_020629dc, ItemInfo_NoneB)

/* func_020629e4: -1 for every item. */
int ItemInfo_NoneC(const u16 *item)
{
    (void) item;
    return -1;
}
CLEAN_AS(func_020629e4, ItemInfo_NoneC)

/* func_020629ec: ItemInfoAlways.unk_02. */
u16 ItemInfo_Unk02(const u16 *item)
{
    const ItemInfoAlways *record = item_info_always(item_info_number(*item));
    return record != NULL ? record->unk_02 : 0;
}
CLEAN_AS(func_020629ec, ItemInfo_Unk02)

/* func_02062a28: the dma.bin record (of the full pile), or NULL. */
const ItemInfoDma *ItemInfo_Dma(const u16 *item)
{
    return func_0206e7bc(func_0206e6e4(&data_021cb5e0), item_info_full_number(item));
}
CLEAN_AS(func_02062a28, ItemInfo_Dma)

/* func_02062ad4: ItemInfoFiles_FreeIndoor on the game's files. */
int ItemInfo_FreeIndoor(void)
{
    return ItemInfoFiles_FreeIndoor(&data_021cb5e0);
}
CLEAN_AS(func_02062ad4, ItemInfo_FreeIndoor)

/* func_02062ae4: ItemInfoFiles_LoadIndoor on the game's files. */
void ItemInfo_LoadIndoor(int stream)
{
    ItemInfoFiles_LoadIndoor(&data_021cb5e0, stream);
}
CLEAN_AS(func_02062ae4, ItemInfo_LoadIndoor)

/* func_02062af4: the game's files closed. */
void ItemInfo_Close(void)
{
    func_02062ca4(&data_021cb5e0);
}
CLEAN_AS(func_02062af4, ItemInfo_Close)

/* func_02062b04: the game's files opened and the items counted. */
void ItemInfo_Open(void)
{
    func_02062cbc(&data_021cb5e0);
}
CLEAN_AS(func_02062b04, ItemInfo_Open)

/* func_02062b14: always 0 (overlay 4's animated room objects start from this frame). */
int ItemInfo_Zero(void)
{
    return 0;
}
CLEAN_AS(func_02062b14, ItemInfo_Zero)

/* func_02062b18: how many of the items 0x13c8-0x1407 and of 0x13a8-0x13c7 have unk_06 0x1d,
 * counted afresh. */
void ItemInfo_CountUnk06Is1d(void)
{
    u16 item;

    data_021cb5bc = 0;
    data_021cb5c4 = 0;
    for (u32 i = 0; i < ITEM_INFO_13C8_ITEMS; i++) {
        item = (u16) (ITEM_INFO_13C8_FIRST + i);
        if (ItemInfo_Unk06(&item) == ITEM_INFO_UNK_06_COUNTED) {
            data_021cb5c4++;
        }
    }
    for (u32 i = 0; i < ITEM_INFO_13A8_ITEMS; i++) {
        item = (u16) (ITEM_INFO_13A8_FIRST + i);
        if (ItemInfo_Unk06(&item) == ITEM_INFO_UNK_06_COUNTED) {
            data_021cb5bc++;
        }
    }
}
CLEAN_AS(func_02062b18, ItemInfo_CountUnk06Is1d)

/* func_02062b98: for each of the 33 pairs, its first item counted when func_0204be38 accepts
 * it, else its second when func_0204bd84 does.
 * QUIRK: the counts are only added to; nothing starts them at 0 again, as ItemInfo_Open does
 * the other counts. */
void ItemInfo_CountSharedPairs(void)
{
    for (u32 i = 0; i < ITEM_INFO_PAIRS; i++) {
        u16 pair[2];
        pair[0] = (u16) (ITEM_INFO_PAIR_FIRST_A + i);
        pair[1] = (u16) (ITEM_INFO_PAIR_FIRST_B + i);
        if (func_0204be38(&pair[0])) {
            data_021cb5b4++;
        } else if (func_0204bd84(&pair[1])) {
            data_021cb5b8++;
        }
    }
}
CLEAN_AS(func_02062b98, ItemInfo_CountSharedPairs)

/* func_02062c0c: the codes 0x1000-0x156d with a held model counted, and the first of them kept
 * unless one is kept already (compared with ITEM_CODE_NONE as ItemCode_HasVariant says).
 * QUIRK: the count is added to; ItemInfo_Open starts it at 0 first. */
void ItemInfo_FindHeldModels(void)
{
    for (u16 code = ITEM_INFO_FIRST_CODE; code < ITEM_INFO_FIRST_CODE + ITEM_INFO_NUMBERS; code++) {
        u16 candidate[2];
        candidate[0] = code;
        if (!ItemInfo_HasHeldModel(&candidate[0])) {
            continue;
        }
        int none;
        if (ItemCode_HasVariant(&data_021cb5b0)) {
            candidate[1] = ITEM_CODE_NONE;
            int number = ItemCode_VariantItem(&data_021cb5b0);
            none = number == ItemCode_VariantItem(&candidate[1]);
        } else {
            none = data_021cb5b0 == ITEM_CODE_NONE;
        }
        if (none) {
            data_021cb5b0 = candidate[0];
        }
        data_021cb5c0++;
    }
}
CLEAN_AS(func_02062c0c, ItemInfo_FindHeldModels)

/* func_02062c94: indoor.bin's copy in memory freed. */
int ItemInfoFiles_FreeIndoor(ItemInfoFiles *files)
{
    return func_0206e6f0(files);
}
CLEAN_AS(func_02062c94, ItemInfoFiles_FreeIndoor)

/* func_02062c9c: unless `stream`, indoor.bin read whole into memory. */
void ItemInfoFiles_LoadIndoor(ItemInfoFiles *files, int stream)
{
    func_0206e704(files, stream);
}
CLEAN_AS(func_02062c9c, ItemInfoFiles_LoadIndoor)

/* The record files' functions ItemInfoFiles uses beside those above (main's record file code,
 * as furniture_info.c names them): close the three; open the three; close one; read all of
 * one's records; open one; a record file's destructor and constructor. */
extern void func_0206e71c(FurnitureRecordFiles *files);
extern int func_0206e73c(FurnitureRecordFiles *files, const char *path0, u32 size0, const char *path1, u32 size1,
                         const char *path2, u32 size2, u32 records);
extern void func_0206e808(FurnitureRecordFile *file);
extern void func_0206e854(FurnitureRecordFile *file);
extern int func_0206e890(FurnitureRecordFile *file, const char *path, u32 record_size, u32 records);
extern FurnitureRecordFile *func_0206e8b4(FurnitureRecordFile *file);
extern void func_0206e8c4(FurnitureRecordFile *file);

extern const char data_020de5b0[]; /* "/item_info/always.bin" */
extern const char data_020de5c8[]; /* "/item_info/indoor.bin" */
extern const char data_020de5e0[]; /* "/item_info/dma.bin" */
extern const char data_020de5f4[]; /* "/item_info/series.bin" */

/* How many records the files are opened with room for. */
#define ITEM_INFO_FILE_RECORDS 0x600
#define ITEM_INFO_SERIES_RECORDS 0x80

/* func_02062ca4: the three files closed, then series.bin. */
void ItemInfoFiles_Close(ItemInfoFiles *files)
{
    func_0206e71c(&files->files);
    func_0206e808(&files->series);
}
CLEAN_AS(func_02062ca4, ItemInfoFiles_Close)

/* func_02062cbc: the files opened (always.bin read whole), the items counted, then series.bin
 * opened and read whole.
 * QUIRK: the answers of the two opens are not looked at: the items are counted, series.bin is
 * read and 1 is returned whether the files could be opened or not. */
int ItemInfoFiles_Open(ItemInfoFiles *files)
{
    data_021cb5c0 = 0;
    (void) func_0206e73c(&files->files, data_020de5b0, sizeof(ItemInfoAlways), data_020de5c8, sizeof(ItemInfoIndoor),
                         data_020de5e0, sizeof(ItemInfoDma), ITEM_INFO_FILE_RECORDS);
    ItemInfo_FindHeldModels();
    ItemInfo_CountSharedPairs();
    ItemInfo_CountUnk06Is1d();
    (void) func_0206e890(&files->series, data_020de5f4, sizeof(ItemInfoSeries), ITEM_INFO_SERIES_RECORDS);
    func_0206e854(&files->series);
    return 1;
}
CLEAN_AS(func_02062cbc, ItemInfoFiles_Open)

/* func_02062d44: the destructor: the files closed (as ItemInfoFiles_Close does), then each
 * destructed, the last first. */
ItemInfoFiles *ItemInfoFiles_Destruct(ItemInfoFiles *files)
{
    func_0206e71c(&files->files);
    func_0206e808(&files->series);
    func_0206e8b4(&files->series);
    func_0206e8b4(&files->files.dma);
    func_0206e8b4(&files->files.indoor);
    func_0206e8b4(&files->files.always);
    return files;
}
CLEAN_AS(func_02062d44, ItemInfoFiles_Destruct)

/* func_02062d7c: the constructor: the four record files constructed, in order. */
ItemInfoFiles *ItemInfoFiles_Construct(ItemInfoFiles *files)
{
    func_0206e8c4(&files->files.always);
    func_0206e8c4(&files->files.indoor);
    func_0206e8c4(&files->files.dma);
    func_0206e8c4(&files->series);
    return files;
}
CLEAN_AS(func_02062d7c, ItemInfoFiles_Construct)
