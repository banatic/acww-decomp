/* What the game knows of each piece of furniture, by its number (the item code's item without
 * its variant, ItemCode_FurnitureNumber: 0-0x6e8), from three files of fixed-size records held at
 * data_021c8c48 (func_02053ea4 opens them, each a record file of 0x1c bytes):
 *   - /ftr_info/always.bin, 8-byte records, all kept in memory (func_0206e6ec gives it);
 *   - /ftr_info/indoor.bin, 4-byte records, read eight at a time (func_0206e6e8, at 0x1c);
 *   - /ftr_info/dma.bin, 0x20-byte records (func_0206e6e4, at 0x38).
 * A number past the last is read as the last; a record that cannot be had reads as 0.
 *
 * The functions named FurnitureInfo_Item* take an item code and answer 0 for a code of a kind
 * without a variant (not furniture). Fields whose meaning is not known keep their offset in
 * their name. */
#ifndef CLEAN_MAIN_FURNITURE_INFO_H
#define CLEAN_MAIN_FURNITURE_INFO_H

#include "lookups.h" /* ItemCode */
#include "types.h"

#define FURNITURE_INFO_NUMBERS 0x6e9

/* A record of always.bin. */
typedef struct FurnitureAlways {
    u8 series;     /* 0x00: its series or set (0-11 the ten-piece series, st_furniture_taste) */
    u8 color_a;    /* 0x01: its two colours, 1-11 and 12 colourful (0 none) */
    u8 color_b;    /* 0x02 */
    u8 theme;      /* 0x03: 0 instrument, 1 painting, 2 model, 3 plant, 4 none */
    u8 list_group; /* 0x04: the item list group (ItemInfoAlways.list_group) */
    u8 shape;      /* 0x05: the footprint's shape (item_footprint.h) */
    u8 category;   /* 0x06 */
    u8 flags;      /* 0x07: bits 0-1 the era, 2-3 the feel (FurnitureInfo_Era, _Feel); bit 4 */
} FurnitureAlways;

/* A record of indoor.bin. */
typedef struct FurnitureIndoor {
    u8 kind;   /* 0x00: for the fossils, the creature each is of (0-23; one dinosaur's parts share it) */
    u8 flags;  /* 0x01: bit 4 and bit 5 the light kind */
    u8 flags2; /* 0x02: bit 0 */
    u8 unk_03; /* 0x03 */
} FurnitureIndoor;

/* A record of dma.bin. */
typedef struct FurnitureDma {
    u8 unk_00[0x18];
    u8 unk_18; /* 0x18: 0x23-0x25 for objects a spin does not turn (ov004/room_object.c) */
    u8 unk_19; /* 0x19 */
    u8 unk_1a; /* 0x1a */
    u8 scale;  /* 0x1b: in percent */
    s8 lift;   /* 0x1c: a preview is raised by 100 times this, less 600 */
    u8 unk_1d; /* 0x1d */
    u8 unk_1e; /* 0x1e: 0xff for none */
    u8 unk_1f; /* 0x1f */
} FurnitureDma;

/* What FurnitureInfo_LightKind answers. */
enum FurnitureLightKind {
    FURNITURE_LIGHT_NONE = 0,
    FURNITURE_LIGHT_BIT4 = 1,
    FURNITURE_LIGHT_BIT5 = 2,
};

u8 FurnitureInfo_CountInSeries(u32 group);
u8 FurnitureInfo_IndexInSeries(const ItemCode *item);
int FurnitureInfo_CountFossilKind(int kind);
int FurnitureInfo_FossilKind(const ItemCode *item);
u8 FurnitureInfo_Kind(int number);
s8 FurnitureInfo_Lift(int number);
int FurnitureInfo_Scale(int number);
int FurnitureInfo_ItemIndoorFlags2Bit0(const ItemCode *item);
int FurnitureInfo_IndoorFlags2Bit0(int number);
int FurnitureInfo_ItemIndoorBit7(const ItemCode *item);
int FurnitureInfo_IndoorBit7(int number);
int FurnitureInfo_IndoorBit6(int number);
const FurnitureDma *FurnitureInfo_Dma(int number);
int FurnitureInfo_LightKind(int number);
int FurnitureInfo_IndoorBit3(int number);
int FurnitureInfo_IndoorBit2(int number);
int FurnitureInfo_IndoorBit0(int number);
int FurnitureInfo_DmaUnk1A(int number);
int FurnitureInfo_ItemCategory(const ItemCode *item);
u8 FurnitureInfo_Category(int number);
int FurnitureInfo_ItemFeel(const ItemCode *item);
int FurnitureInfo_Feel(int number);
int FurnitureInfo_ItemEra(const ItemCode *item);
int FurnitureInfo_Era(int number);
int FurnitureInfo_FlagBit4(int number);
int FurnitureInfo_ItemTheme(const ItemCode *item);
int FurnitureInfo_Theme(int number);
int FurnitureInfo_ItemShape(const ItemCode *item);
u8 FurnitureInfo_Shape(int number);
int FurnitureInfo_ItemListGroup(const ItemCode *item);
u8 FurnitureInfo_ListGroup(int number);
int FurnitureInfo_ItemSeries(const ItemCode *item);
u8 FurnitureInfo_Series(int number);
int FurnitureInfo_ColorB(int number);
int FurnitureInfo_ColorA(int number);
int FurnitureInfo_DmaUnk1E(int number);

/* How many records each file is opened with room for. */
#define FURNITURE_FILE_RECORDS 0x800

/* One record file (0x1c bytes). */
typedef struct FurnitureRecordFile {
    u8 file_id[8];   /* 0x00: NitroSDK's FSFileID of the file */
    u32 record_size; /* 0x08 */
    u32 records;     /* 0x0c: FURNITURE_FILE_RECORDS */
    void *whole;     /* 0x10: the whole file, when it is read into memory */
    s32 cached;      /* 0x14: -1 when nothing is cached */
    void *cache;     /* 0x18: room for eight records */
} FurnitureRecordFile;

/* The three files at data_021c8c48 (0x54 bytes). */
typedef struct FurnitureRecordFiles {
    FurnitureRecordFile always; /* 0x00 */
    FurnitureRecordFile indoor; /* 0x1c */
    FurnitureRecordFile dma;    /* 0x38 */
} FurnitureRecordFiles;

int FurnitureInfo_DmaUnk1D(int number);
int FurnitureInfo_NoneA(int number);
int FurnitureInfo_NoneB(int number);
int FurnitureInfo_NoneC(int number);
int FurnitureInfo_DmaUnk19(int number);
u8 FurnitureInfo_DmaUnk18(int number);
u16 FurnitureInfo_Price(int number);
void FurnitureFiles_FreeIndoor(FurnitureRecordFiles *files);
int FurnitureFiles_LoadIndoor(FurnitureRecordFiles *files, int stream);
void FurnitureFiles_Close(FurnitureRecordFiles *files);
int FurnitureFiles_Open(FurnitureRecordFiles *files);
FurnitureRecordFiles *FurnitureFiles_Destruct(FurnitureRecordFiles *files);
FurnitureRecordFiles *FurnitureFiles_Construct(FurnitureRecordFiles *files);
void FurnitureInfo_FreeIndoor(void);
void *FurnitureInfo_LoadIndoor(void *stream);
void FurnitureInfo_Close(void);
void FurnitureInfo_Open(void);

#endif
