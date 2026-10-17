/* Items on their way to the ground: when a player puts an item down, its model flies from where
 * it was held to where it will lie in an arc of 9 frames (12 when it lands above the ground),
 * growing from flat as it goes, bounces once and lands; the tile change waiting for it is
 * finished then (TileChanges_FinishAtTile), so the item appears on the map.
 *
 * Fifteen of them (data_ov004_02258af4, a C++ array built and destroyed by the overlay's
 * static initialiser), three for each player; the process of the items' models (icon_models.h)
 * moves and draws them each frame. */
#ifndef CLEAN_OV004_DROPPED_ITEMS_H
#define CLEAN_OV004_DROPPED_ITEMS_H

#include "autoload_2/vector.h"
#include "main/acre_map.h"
#include "main/tile_changes.h"
#include "types.h"

#define DROPPED_ITEMS 15
#define DROPPED_ITEMS_PER_PLAYER 3

/* DroppedItem.state */
enum {
    DROPPED_ITEM_FREE = 0,
    DROPPED_ITEM_SET = 1, /* only while it is being set */
    DROPPED_ITEM_FLYING = 2,
};

/* No item (DroppedItem.item). */
#define DROPPED_ITEM_NONE 0xfff1

typedef struct DroppedItem {
    int player;           /* 0x00 */
    int state;            /* 0x04: DROPPED_ITEM_* */
    u16 item;             /* 0x08: what is drawn */
    u16 item_0a;          /* 0x0a: the same */
    int landed;           /* 0x0c: it does not move */
    TileChangesTile tile; /* 0x10: the tile whose change is finished when it lands */
    Vec3 target;          /* 0x18: where it lands */
    Vec3 position;        /* 0x24 */
    Vec3 velocity;        /* 0x30 */
    Vec3 scale;           /* 0x3c: x and z grow from 0 to 1.0 */
    s16 unk_48;           /* 0x48 */
    s16 unk_4a;           /* 0x4a */
    u8 sound[0x40];       /* 0x4c: a sound emitter of the base class (main/sound_emitter.h) */
    s8 bounces;           /* 0x8c */
    u8 frames;            /* 0x8d: frames flown */
    u8 unk_8e;            /* 0x8e: 0 for items of kinds 3 and 4 */
    u8 tile_pending;      /* 0x8f: its tile change is still to be finished */
    u8 layer;             /* 0x90: the tile's layer */
    u8 pad_91[3];
} DroppedItem;

int DroppedItems_DropFrom(int player, int item, const Vec3 *from, const Vec3 *to, u8 layer);
int DroppedItems_DropOnTile(int player, int item, const TileChangesTile *tile, const Vec3 *from, u8 layer);
int DroppedItems_Start(DroppedItem *items, int player, const TileChangesTile *tile, const Vec3 *from, const Vec3 *to,
                       int landed, u16 item, short unk_48, u8 layer);
void DroppedItems_Release(DroppedItem *items);
void DroppedItems_Draw(DroppedItem *items);
void DroppedItems_Update(DroppedItem *items);
void DroppedItems_Reset(DroppedItem *items);
void DroppedItem_Fly(DroppedItem *drop);
void DroppedItem_Launch(DroppedItem *drop, const TileChangesTile *tile, const Vec3 *from, const Vec3 *to, u16 item);
void DroppedItem_Finish(DroppedItem *drop);
void DroppedItem_Set(DroppedItem *drop, int player, const TileChangesTile *tile, const Vec3 *from, const Vec3 *to, int landed,
                     u16 item, AcreMap *map, short unk_48, u8 layer);
void DroppedItem_FinishTile(DroppedItem *drop);
void DroppedItems_PutOnMap(int x, int z, u16 item, int layer);
int DroppedItems_DropFromLocalPlayer(const u16 *item, const Vec3 *to);
DroppedItem *DroppedItems_Destruct(DroppedItem *items);
DroppedItem *DroppedItem_Destruct(DroppedItem *drop);
DroppedItem *DroppedItem_Construct(DroppedItem *drop);

#endif
