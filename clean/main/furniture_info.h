/* What the game knows of each piece of furniture, by its number (the item code's item without
 * its variant, ItemCode_VariantItem: 0-0x6e8), from three files of fixed-size records held at
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
    u8 group;    /* 0x00: FurnitureInfo_CountInGroup counts the numbers sharing it */
    u8 unk_01;   /* 0x01 */
    u8 unk_02;   /* 0x02 */
    u8 unk_03;   /* 0x03 */
    u8 unk_04;   /* 0x04 */
    u8 shape;    /* 0x05: the footprint's shape (item_footprint.h) */
    u8 category; /* 0x06 */
    u8 flags;    /* 0x07: bits 0-4 */
} FurnitureAlways;

/* A record of indoor.bin. */
typedef struct FurnitureIndoor {
    u8 kind;   /* 0x00: for the museum's group A items, the kind they are counted by */
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

u8 FurnitureInfo_CountInGroup(u32 group);
u8 FurnitureInfo_IndexInGroup(const ItemCode *item);
int FurnitureInfo_CountMuseumKind(int kind);
int FurnitureInfo_MuseumKind(const ItemCode *item);
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
int FurnitureInfo_ItemFlagBits23(const ItemCode *item);
int FurnitureInfo_FlagBits23(int number);
int FurnitureInfo_ItemFlagBits01(const ItemCode *item);
int FurnitureInfo_FlagBits01(int number);
int FurnitureInfo_FlagBit4(int number);
int FurnitureInfo_ItemUnk03(const ItemCode *item);
int FurnitureInfo_Unk03(int number);
int FurnitureInfo_ItemShape(const ItemCode *item);
u8 FurnitureInfo_Shape(int number);
int FurnitureInfo_ItemUnk04(const ItemCode *item);
u8 FurnitureInfo_Unk04(int number);
int FurnitureInfo_ItemGroup(const ItemCode *item);
u8 FurnitureInfo_Group(int number);
int FurnitureInfo_Unk02(int number);
int FurnitureInfo_Unk01(int number);
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
u16 FurnitureInfo_DmaUnk16(int number);
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
