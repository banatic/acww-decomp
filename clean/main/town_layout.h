/* The town's layout (data_021e9aac): the model number of each of its 6 x 6 acres, the 16 x 16
 * item codes of each of the 4 x 4 inner acres (the border acres have none), a 0x20-byte record
 * for each inner acre, and one byte of settings. A new town is laid out by
 * TownLayout_Generate; AcreMap_BuildTown (acre_map.h) makes the town's map from it.
 *
 * An acre is numbered (x, z) across the whole 6 x 6; the inner acres are 1-4 on both axes and
 * are stored from (1, 1). */
#ifndef CLEAN_MAIN_TOWN_LAYOUT_H
#define CLEAN_MAIN_TOWN_LAYOUT_H

#include "acre_map.h"
#include "types.h"

#define TOWN_LAYOUT_SIDE 6
#define TOWN_LAYOUT_ACRES (TOWN_LAYOUT_SIDE * TOWN_LAYOUT_SIDE)
#define TOWN_LAYOUT_INNER_SIDE 4
#define TOWN_LAYOUT_INNER_ACRES (TOWN_LAYOUT_INNER_SIDE * TOWN_LAYOUT_INNER_SIDE)
#define TOWN_LAYOUT_ACRE_ITEMS 256 /* 16 x 16 */

/* A model number a new layout starts with in every acre. */
#define TOWN_LAYOUT_MODEL_DEFAULT 0x86

typedef struct TownLayoutAcreRecord {
    u8 bytes[0x20];
} TownLayoutAcreRecord;

typedef struct TownLayout {
    u8 models[TOWN_LAYOUT_ACRES];                               /* 0x0000: row by row */
    u16 items[TOWN_LAYOUT_INNER_ACRES][TOWN_LAYOUT_ACRE_ITEMS]; /* 0x0024 */
    TownLayoutAcreRecord records[TOWN_LAYOUT_INNER_ACRES];      /* 0x2024 */
    u8 settings; /* 0x2224: bits 0-1 a number 0-2 chosen at random; bits 2-7 from func_020b7098 */
} TownLayout;

/* An acre's coordinates. */
typedef struct TownLayoutAcre {
    int x;
    int z;
} TownLayoutAcre;

void *TownLayout_BlockItems(void *block);
void TownLayout_ClearBlock(unsigned short *items);
void *TownLayout_DestructBlock(void *items);
int TownLayout_ConstructBlock(int items);
void *TownLayout_Get(void *layout);
void TownLayout_Generate(void *layout, void *heap);
void TownLayout_FillFromTemplates(u8 *layout, int heap);
int TownLayout_HasFiveE3ToE7(void *layout);
int TownLayout_HasNine500a(void *layout);
AcreMapSource *TownLayout_MakeSources(unsigned char *layout, int heap);
void TownLayout_SetUpperSettings(unsigned int layout);
unsigned int TownLayout_RandomSetting(TownLayout *layout);
int TownLayout_InnerAcre(int unused, TownLayoutAcre *inner, TownLayoutAcre *acre);
int TownLayout_IsInnerAcre(int unused, int x, int z);
void *TownLayout_AcreRecord(void *layout, int *acre);
int TownLayout_AcreItems(void *layout, int *acre);
void TownLayout_Clear(unsigned char *layout);
void *TownLayout_Destruct(void *layout);
void *TownLayout_Construct(void *layout);

#endif
