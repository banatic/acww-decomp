/* A process of overlay 4 (class vtable 0x02255a38 on the Process base, 0x50 bytes, profile
 * data_ov004_02255a28) whose creation puts each player's item at 0x240e of the player's record
 * (PlayerRecord_Item240E, a furniture code with a variant) on the map of the scene shown: the
 * player numbers 0 to 3 at the tiles (6, 9), (9, 9), (6, 12) and (9, 12), turned to variant 3;
 * an item two tiles wide (FurnitureInfo_ItemShape 2) on the left half (x below 8) one tile
 * further left. Players without a record and empty items are skipped. */
#ifndef CLEAN_OV004_ROOM_PLAYER_ITEMS_H
#define CLEAN_OV004_ROOM_PLAYER_ITEMS_H

#include "autoload_2/process.h"
#include "types.h"

void RoomPlayerItems_Place(void);
int RoomPlayerItems_Create(void);
Process *RoomPlayerItems_Delete(Process *self);
Process *RoomPlayerItems_Destruct(Process *self);
Process *RoomPlayerItems_Construct(Process *self);
void RoomPlayerItems_New(void);

#endif
