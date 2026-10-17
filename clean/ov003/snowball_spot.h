/* Where overlay 3 puts the town's two loose snowballs when the day has none yet
 * (func_ov003_02236374, which spawns actor 0xbd at the points SnowballSpot_Pick gives).
 *
 * A mask of the town's 4 by 4 inner acres (data_ov003_02262b58, built once and kept): for each
 * acre one bit per tile, 16 rows of 16, set when the tile is taken, and a count of the tiles
 * still free. A spot is a free tile of a random acre among those with free tiles. */
#ifndef CLEAN_OV003_SNOWBALL_SPOT_H
#define CLEAN_OV003_SNOWBALL_SPOT_H

#include "autoload_2/vector.h"
#include "types.h"

#define SNOWBALL_SPOT_ACRES 4  /* acres across and down */
#define SNOWBALL_SPOT_TILES 16 /* tiles across and down an acre */

/* One acre of the mask (0x22 bytes). */
typedef struct SnowballSpotAcre {
    u16 rows[SNOWBALL_SPOT_TILES]; /* bit x of row z: tile (x, z) is taken */
    u16 free;                      /* the tiles not taken, 0x100 when cleared */
} SnowballSpotAcre;

/* The mask: acres[z][x] is inner acre (x + 1, z + 1). */
typedef struct SnowballSpotMask {
    SnowballSpotAcre acres[SNOWBALL_SPOT_ACRES][SNOWBALL_SPOT_ACRES];
} SnowballSpotMask;

int SnowballSpot_Pick(void *unused, Vec3 *spot, const Vec3 *away_from, int avoid_items);
SnowballSpotMask *SnowballSpot_DestroyMask(SnowballSpotMask *mask);
void SnowballSpot_DestroyAcre(SnowballSpotAcre *acre);
void SnowballSpot_ConstructAcre(SnowballSpotAcre *acre);
int SnowballSpot_PickTile(SnowballSpotMask *mask, int *x, int *z);
void SnowballSpot_Take(SnowballSpotMask *mask, int x, int z);
int SnowballSpot_OpenAcres(SnowballSpotMask *mask);
void SnowballSpot_Clear(SnowballSpotMask *mask);
int SnowballSpot_PickInAcre(SnowballSpotAcre *acre, int *x, int *z);
int SnowballSpot_IsTaken(SnowballSpotAcre *acre, int x, int z);
void SnowballSpot_TakeInAcre(SnowballSpotAcre *acre, int x, int z);
void SnowballSpot_ClearAcre(SnowballSpotAcre *acre);

#endif
