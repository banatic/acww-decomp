/* An acre of a map of acres (acre_map.h): a 0x28-byte record of its model number, its
 * coordinates in the map, its position in the world, its two layers of 16 x 16 item codes, its
 * loaded background model (bg_models.h) and the bits of its tiles (acre_bits.h).
 *
 * Its flags are those of its model's kind (acre_kind.h). Each map registers the acre data of its
 * acres with its entry of the table at data_021c31ec (the map's slot). */
#ifndef CLEAN_MAIN_ACRE_RECORD_H
#define CLEAN_MAIN_ACRE_RECORD_H

#include "acre_bits.h"
#include "autoload_2/heap.h"
#include "autoload_2/vector.h"
#include "bg_models.h"
#include "types.h"

#define ACRE_RECORD_SIDE 16 /* tiles to a side */
#define ACRE_RECORD_TILES (ACRE_RECORD_SIDE * ACRE_RECORD_SIDE)
#define ACRE_RECORD_LAYERS 2

typedef struct AcreRecord {
    s32 model;                       /* 0x00: the model number */
    s32 x;                           /* 0x04: the acre's coordinates in its map */
    s32 z;                           /* 0x08 */
    Vec3 position;                   /* 0x0c: its corner in the world */
    u16 *layers[ACRE_RECORD_LAYERS]; /* 0x18: 16 x 16 item codes each, row by row, or NULL */
    BgModel *bg_model;               /* 0x20: its loaded model, or NULL */
    AcreBits *bits;                  /* 0x24: the bits of its tiles, or NULL */
} AcreRecord;

void AcreRecord_TileOfIndex(int *x, int *z, int index);
int AcreRecord_ClearTileBit(AcreRecord *acre, int x, int z);
int AcreRecord_SetTileBit(AcreRecord *acre, int x, int z);
int AcreRecord_HasAnyFlag(AcreRecord *acre, int flags);
int AcreRecord_HasAllFlags(AcreRecord *acre, unsigned int flags);
int AcreRecord_Flags(AcreRecord *acre);
int AcreRecord_FindCode(AcreRecord *acre, int *x, int *z, const u16 *first, const u16 *last, u8 layer);
u16 *AcreRecord_Tile(AcreRecord *acre, unsigned int x, unsigned int z, unsigned int layer);
int AcreRecord_SetTile(AcreRecord *acre, const u16 *code, int x, int z, unsigned char layer);
int AcreRecord_ModelIsListed(AcreRecord *acre);
int AcreRecord_Model(const AcreRecord *acre);
void AcreRecord_SetModel(AcreRecord *acre, int model);
int AcreRecord_Coordinates(AcreRecord *acre);
AcreRecord *AcreRecord_NewArray(int count, Heap *heap, int align);
void AcreRecord_SetBgModel(AcreRecord *acre, BgModel *bg_model, int data, int slot);
void AcreRecord_SetUpAt(AcreRecord *acre, int model, const Vec3 *position, u16 *items, u16 *layer1, AcreBits *bits,
                        BgModel *bg_model, int data, const int *coordinates, int slot);
void AcreRecord_SetUp(AcreRecord *acre, int model, const Vec3 *position, u16 *items, u16 *layer1, AcreBits *bits,
                      BgModel *bg_model, int data, int x, int z, int slot);
void AcreRecord_Init(AcreRecord *acre);

#endif
