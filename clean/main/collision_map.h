/* The maps of units the collision code reads (field_collision.h, CollisionWorld): setting up,
 * releasing and choosing the current one (data_020da1a8), filling in their blocks, and what a
 * map keeps per unit besides its type.
 *
 * A map is one of the eight FieldBlockMap entries of the world (its `slot`); the current one is
 * the map every question about units reads (itcm/field_units.h). Each block entry holds two
 * pointers: the unit types (16 by 16 bytes) and, 0x100 bytes after them, the units' path
 * directions, four bits a unit (the even unit in the low half of a byte, the odd one in the
 * high half). The directions are bits 1 (towards -Z), 2 (towards -X), 4 (towards +Z) and 8
 * (towards +X), the order of a unit's sides in CollisionCell.
 *
 * Unit types 0x68 to 0x6e stand for the map's objects 0 to 6; one of them may be claimed (the
 * word at 0x12c, -1 for none), and a claimed object is not reported on the field. */
#ifndef CLEAN_MAIN_COLLISION_MAP_H
#define CLEAN_MAIN_COLLISION_MAP_H

#include "autoload_2/vector.h"
#include "field_collision.h"
#include "types.h"

/* The words after a map's blocks (FieldBlockMap.unk_12C). */
typedef struct CollisionMapState {
    s32 claimed;   /* 0x12c: the claimed object, -1 for none */
    u8 complete;   /* 0x130: every block of the map's size has its data */
    u8 unk_131;    /* 0x131 */
    s16 value_old; /* 0x132: the value 0x134 had before it last changed */
    s16 value;     /* 0x134 */
    u8 unk_136[2];
} CollisionMapState;

/* The objects of the map, as unit types. */
#define COLLISION_MAP_OBJECT_FIRST 0x68
#define COLLISION_MAP_OBJECT_LAST 0x6e
#define COLLISION_MAP_NO_OBJECT (-1)

/* The path directions of a unit. */
#define COLLISION_PATH_MINUS_Z 1
#define COLLISION_PATH_MINUS_X 2
#define COLLISION_PATH_PLUS_Z 4
#define COLLISION_PATH_PLUS_X 8

int CollisionMap_GetRoomBounds(fx32 *min_x, fx32 *max_x, fx32 *min_z, fx32 *max_z);
int CollisionMap_ClearClaim(void);
int CollisionMap_IsClaimedAtPoint(const Vec3 *point);
int CollisionMap_Claim(int object);
int CollisionMap_UnclaimedObjectAtPoint(const Vec3 *point);
int CollisionMap_UnclaimedObjectAt(int x, int z);
void CollisionMap_UnlinkPathUnit(int x, int z);
int CollisionMap_RetypeWithSides(int x, int z, int sides);
int CollisionMap_RetypeToPlain(int x, int z);
void CollisionMap_SetValue134(s16 value);
void CollisionMap_Release(int slot);
void CollisionMap_ClearBlocks(int slot);
void CollisionMap_Reset(int slot);
int CollisionMap_SetBlock(int x, int z, int data, int slot);
void CollisionMap_ClearPathDirections(u32 x, u32 z, u32 directions);
void CollisionMap_SetPathDirections(int x, int z, int directions);
int CollisionMap_AddExtraPost(int x, int z);
void CollisionMap_AgeExtraPosts(void);
int CollisionMap_Setup(u32 blocks_wide, u32 blocks_high, CollisionPostSource *source, int slot);
void CollisionMap_Select(int slot);
u8 CollisionMap_IsComplete(int slot);
int CollisionMap_PathDirections(int x, int z);
u8 CollisionMap_CompleteByte(int slot);

#endif
