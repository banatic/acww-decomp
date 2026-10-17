/* Putting a piece of furniture down in the room (an item code with a variant, ItemCode_HasVariant):
 * finding cells near an actor where its footprint (item_footprint.h) is free, on the floor or
 * on top of other furniture, and making the placement value (Placement_Make, room_object_body.h)
 * that RoomObjects_Spawn turns into the room object.
 *
 * What the searches give (enum RoomPlacementResult): 3 with the placement in `*out`. */
#ifndef CLEAN_OV004_ROOM_PLACEMENT_H
#define CLEAN_OV004_ROOM_PLACEMENT_H

#include "types.h"

#include "autoload_2/vector.h"
#include "main/lookups.h" /* ItemCode */

enum RoomPlacementResult {
    ROOM_PLACEMENT_NOT_FURNITURE = 0, /* not an item with a variant, not in a house's room, or no player */
    ROOM_PLACEMENT_ROOM_FULL = 1,     /* no free entry in the table of the room's objects */
    ROOM_PLACEMENT_NO_SPACE = 2,
    ROOM_PLACEMENT_PLACED = 3
};

/* RoomPlacement_Find's `mode` that makes the placement without a search (its mode 2). */
#define ROOM_PLACEMENT_MODE_UNPLACED 2

int RoomPlacement_PlaceSeries3F24(u32 *out, unsigned int item, int mode);
int RoomPlacement_PlaceSeries4224(u32 *out, unsigned int item, int mode);
int RoomPlacement_PlaceSeries3EA4(u32 *out, unsigned int item, int mode);
int RoomPlacement_PlaceSeries3D84(u32 *out, unsigned int item, int mode);
int RoomPlacement_PlayerIndex(void);
int RoomPlacement_FindNearPlayer(u32 *out, ItemCode *item, int mode);
int RoomPlacement_Find(u32 *out, ItemCode *item, const Vec3 *position, int angle, int mode);
int RoomPlacement_TryAt(u32 *out, int x, int z, int side, int number, u8 layer, int player_x, int player_z);

#endif
