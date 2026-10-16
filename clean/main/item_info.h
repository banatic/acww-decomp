/* What the game knows of each item code of kinds 1 and 0 (by the code's low 12 bits, 0-0x56d;
 * a number past the last is read as the last), from the record files at data_021cb5e0, opened
 * like those of furniture_info.h:
 *   - /item_info/always.bin, 12-byte records, kept in memory;
 *   - /item_info/indoor.bin, 4-byte records (loaded whole only in some scenes);
 *   - /item_info/dma.bin, 0x18-byte records;
 *   - /item_info/series.bin, 0x18-byte records, one per series (0-0x49), at 0x54.
 * A record that cannot be had reads as 0. An item in a pile (kind 1 codes 0x1000-0x10ff, the
 * low two bits the count less one) is read, for the functions that say so, as its full pile.
 *
 * Once the files are open (ItemInfo_Open) the game counts some items by their records: the
 * items with a held model (always.bin flag bit 0), numbered from the first of them, and a few
 * counts the shops and others read. Fields whose meaning is not known keep their offset in
 * their name. */
#ifndef CLEAN_MAIN_ITEM_INFO_H
#define CLEAN_MAIN_ITEM_INFO_H

#include "furniture_info.h" /* FurnitureRecordFile, FurnitureRecordFiles */
#include "types.h"

#define ITEM_INFO_NUMBERS 0x56e
#define ITEM_INFO_SERIES 0x4a
/* The looks with a model name (ItemInfo_LookModelName). */
#define ITEM_INFO_LOOKS 0x49

/* A record of always.bin. */
typedef struct ItemInfoAlways {
    u16 price;     /* 0x00: the bells the item is worth (for a pile: the full pile) */
    u16 unk_02;    /* 0x02 */
    u8 item_class; /* 0x04 */
    u8 series;     /* 0x05: its series (series.bin) */
    u8 unk_06;     /* 0x06 */
    u8 unk_07;     /* 0x07 */
    u8 unk_08;     /* 0x08: read for items of class 5 */
    u8 flags;      /* 0x09: bit 0 a held model; bits 1-4 */
    u8 unk_0a[2];  /* 0x0a */
} ItemInfoAlways;

/* A record of indoor.bin. */
typedef struct ItemInfoIndoor {
    u8 unk_00;    /* 0x00 */
    u8 unk_01;    /* 0x01: a ground sound attribute (ground_sound.c) */
    u8 unk_02[2]; /* 0x02 */
} ItemInfoIndoor;

/* A record of dma.bin. */
typedef struct ItemInfoDma {
    u8 unk_00[0x18];
} ItemInfoDma;

/* A record of series.bin. */
typedef struct ItemInfoSeries {
    u8 unk_00[0x16];
    u8 kind; /* 0x16: 0-2 (room_score.c), 3 when there is no record */
    u8 unk_17;
} ItemInfoSeries;

/* The four files. */
typedef struct ItemInfoFiles {
    FurnitureRecordFiles files; /* 0x00: always.bin, indoor.bin, dma.bin */
    FurnitureRecordFile series; /* 0x54 */
} ItemInfoFiles;

const char *ItemInfo_LookModelName(int look, int outdoors);
int ItemInfo_ScorePoints(int value);
const ItemInfoSeries *ItemInfo_SeriesRecord(int series);
u8 ItemInfo_SeriesKind(int series);
u8 ItemInfo_IndoorUnk00(const u16 *item);
u8 ItemInfo_IndoorUnk01(const u16 *item);
int ItemInfo_FlagBit4(const u16 *item);
int ItemInfo_FlagBit3(const u16 *item);
int ItemInfo_FlagBit2(const u16 *item);
int ItemInfo_FlagBit1(const u16 *item);
int ItemInfo_HasHeldModel(const u16 *item);
int ItemInfo_Class5Unk08(const u16 *item);
u8 ItemInfo_Unk07(const u16 *item);
int ItemInfo_Unk06(const u16 *item);
u8 ItemInfo_Class(const u16 *item);
int ItemInfo_Price(const u16 *item);
u8 ItemInfo_Series(const u16 *item);
int ItemInfo_NoneA(const u16 *item);
int ItemInfo_NoneB(const u16 *item);
int ItemInfo_NoneC(const u16 *item);
u16 ItemInfo_Unk02(const u16 *item);
const ItemInfoDma *ItemInfo_Dma(const u16 *item);
int ItemInfo_FreeIndoor(void);
void ItemInfo_LoadIndoor(int stream);
void ItemInfo_Close(void);
void ItemInfo_Open(void);
int ItemInfo_Zero(void);
void ItemInfo_CountUnk06Is1d(void);
void ItemInfo_CountSharedPairs(void);
void ItemInfo_FindHeldModels(void);
int ItemInfoFiles_FreeIndoor(ItemInfoFiles *files);
void ItemInfoFiles_LoadIndoor(ItemInfoFiles *files, int stream);

int ItemInfo_Count13a8Unk06Is1d(void);
u32 ItemInfo_Count13c8Unk06Is1d(void);
u32 ItemInfo_CountSecondOfPair(void);
int ItemInfo_CountFirstOfPair(void);
u32 ItemInfo_HeldModelNumber(const u16 *item);
void ItemInfo_HeldModelItem(u16 *out, int number);
u32 ItemInfo_HeldModelCount(void);

void ItemInfoFiles_Close(ItemInfoFiles *files);
int ItemInfoFiles_Open(ItemInfoFiles *files);
ItemInfoFiles *ItemInfoFiles_Destruct(ItemInfoFiles *files);
ItemInfoFiles *ItemInfoFiles_Construct(ItemInfoFiles *files);

#endif
