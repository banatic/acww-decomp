/* The changes to tiles of the map under way (data_021c7880): twenty records of what a session
 * slot is doing to a tile, of the kinds of tile_requests.h. func_02046024 puts an item on a
 * tile through one of them (a free one has the tile 0xffff), func_0204629c finishes a change
 * and func_020465b0 frees its record.
 *
 * A change is held while its slot's player is at it (bit 7 of `state`); a slot's changes are
 * found by their tile and layer, or by a tag of three bits. */
#ifndef CLEAN_MAIN_TILE_CHANGES_H
#define CLEAN_MAIN_TILE_CHANGES_H

#include "types.h"

#define TILE_CHANGES_COUNT 20
#define TILE_CHANGES_NONE (-1)
#define TILE_CHANGES_NO_TILE 0xffff /* TileChange.tile of a free record */

/* TileChange.who */
#define TILE_CHANGE_SLOT_MASK 0x07 /* the session slot; 7 in a free record */
#define TILE_CHANGE_KIND_SHIFT 3   /* 5 bits: the kind of the request */
/* TileChange.state */
#define TILE_CHANGE_TAG_SHIFT 2 /* 3 bits */
#define TILE_CHANGE_HELD 0x80
/* TileChange.flags */
#define TILE_CHANGE_LAYER 0x02 /* the second of the tile's two codes */

typedef struct TileChange {
    u8 who;   /* 0x00 */
    u8 state; /* 0x01: bits 0-1 a result, bits 2-4 the tag, bits 5-6, bit 7 held */
    u8 flags; /* 0x02: bit 0, bit 1 the layer, bits 2-5 a signed number, bits 6-7 */
    u8 unk_03[5];
    u16 tile;   /* 0x08: x in the high byte, z in the low */
    u16 item;   /* 0x0a */
    u16 unk_0c; /* 0x0c */
    u16 unk_0e;
} TileChange;

/* data_021c7880 */
typedef struct TileChanges {
    int active;                             /* 0x00: other systems' actions are taken in */
    TileChange changes[TILE_CHANGES_COUNT]; /* 0x04: data_021c7884 */
} TileChanges;

/* A tile of the map, as the callers hand it. */
typedef struct TileChangesTile {
    int x;
    int z;
} TileChangesTile;

void TileChanges_Init(TileChanges *changes);
u16 *TileChanges_HeldTileOf(int slot);
int TileChanges_At(int index);
int TileChanges_FindByTag(int slot, int tag);
int TileChanges_FindHeld(int slot);
int TileChanges_FindFree(void);
int TileChanges_FindOwnAtFor(u32 player, const TileChangesTile *tile, u32 layer);
int TileChanges_FindOwnAt(u32 slot, const TileChangesTile *tile, u32 layer);
int TileChanges_FindAt(const TileChangesTile *tile, int layer);
void TileChanges_FinishAll(void);
void TileChanges_Activate(void);
int TileChanges_IndexAt(const TileChangesTile *tile, int layer);
void TileChanges_FreeHeld(int slot);
void TileChanges_Release(TileChange *change);
void TileChanges_ReleaseAt(const TileChangesTile *tile, int layer);
void TileChanges_LetGoAt(const TileChangesTile *tile, int layer);
void TileChanges_FinishOwnAt(const TileChangesTile *tile, int slot, int layer);
void TileChanges_FinishAt(int index);

void TileChanges_FinishAtTile(const TileChangesTile *tile, int layer);
int TileChanges_Replace(int slot, const TileChangesTile *tile, u32 item, int code, u8 kind, u8 result, u8 unk_20, u8 tag,
                        u8 layer, s8 number);
int TileChanges_Put(int slot, const TileChangesTile *tile, u32 item, u32 code, u8 kind, u8 result, u8 unk_20, u8 tag, u8 layer,
                    s8 number);
int TileChanges_PutNew(int slot, const TileChangesTile *tile, int item, int code, u8 kind, u8 result, u8 unk_20, u8 tag,
                       u8 layer, s8 number);
int TileChanges_MakeRoomAt(const TileChangesTile *tile);
int TileChanges_FillAt(u32 index, u32 slot, const TileChangesTile *tile, u32 item, u16 code, u8 kind, u8 result, u8 unk_20,
                       u8 tag, u8 layer, s8 number);
void TileChanges_Done(TileChange *change);
void TileChanges_InitRecord(TileChange *change);
void TileChanges_LetGo(TileChange *change);
void TileChanges_Finish(TileChange *change);
void TileChanges_NoteItem(const TileChange *change);
void TileChanges_Report(TileChange *change);
int TileChanges_Fill(TileChange *change, u32 slot, u16 tile, u32 item, u16 code, u8 kind, u8 result, u8 unk_20, u8 tag,
                     u8 layer, s8 number);
void TileChanges_Free(TileChange *change);

#endif
