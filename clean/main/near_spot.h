/* A spot near a position (part 0x24 of the object at data_021d27ac, block_021d27ac.h): the
 * centre of a tile picked at random near a position (NearSpot_Pick, called by func_020be784)
 * among the tiles TownSpot_TileSuits accepts, with a quarter turn to face. The spawner's
 * placer Spawner_PlaceFromPart24 puts the actor there; the spawner clears the "served" bit
 * when it is created and sets it when it serves an entry. */
#ifndef CLEAN_MAIN_NEAR_SPOT_H
#define CLEAN_MAIN_NEAR_SPOT_H

#include "acre_map.h"
#include "actor_table.h"
#include "autoload_2/vector.h"
#include "types.h"

#define NEAR_SPOT_FOUND 0x01       /* NearSpot_Pick found a tile */
#define NEAR_SPOT_SERVED 0x02      /* the spawner served an entry since it was created */
#define NEAR_SPOT_FACING_MASK 0x0c /* the quarter turn faced, 0-3 */
#define NEAR_SPOT_FACING_SHIFT 2

typedef struct NearSpot {
    fx32 x;   /* 0x00 */
    fx32 z;   /* 0x04 */
    u8 flags; /* 0x08 */
    u8 unused_09[3];
} NearSpot;

/* A test NearSpot_PickInRange asks of each tile of a row or column: `fixed` is the row's z or
 * the column's x, `i` the other coordinate. */
typedef int NearSpotTest(int fixed, int i, AcreMap *map);

int NearSpot_Pick(NearSpot *spot, const Position *from, int side);
int NearSpot_PickInRange(int *out, NearSpotTest *test, int fixed, int first, int last, AcreMap *map, u16 *bits, int rows);
int NearSpot_ColumnTileSuits(int x, int z, AcreMap *map);
int NearSpot_RowTileSuits(int z, int x, AcreMap *map);
int NearSpot_Facing(const NearSpot *spot);
void NearSpot_SetServed(NearSpot *spot);
void NearSpot_ClearServed(NearSpot *spot);
int NearSpot_WasServed(const NearSpot *spot);
void NearSpot_ClearFound(NearSpot *spot);
void NearSpot_SetFound(NearSpot *spot);
int NearSpot_Found(const NearSpot *spot);
void NearSpot_ToPosition(const NearSpot *spot, Vec3 *position);
void NearSpot_SetFromPosition(NearSpot *spot, const Vec3 *position);
void NearSpot_Clear(NearSpot *spot);
void NearSpot_Construct(NearSpot *spot);
void NearSpot_Destruct(NearSpot *spot);

#endif
