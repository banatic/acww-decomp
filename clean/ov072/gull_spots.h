/* Where overlay 72's character (gull.h) places item 0x1568 in the town: on the empty tiles of
 * the 4 x 4 inner acres of the town's map (acres 1-4 each way) whose unit byte 0x04 says yes
 * (AcreTile_UnitByte04InAcre) and whose two tiles to +z are free of buildings (0x5000-0x5021),
 * special codes and the item ranges GullSpots_TileFits lists. It places as many as such tiles
 * (at most five), each on a random fitting tile of a random acre that has one. */
#ifndef CLEAN_OV072_GULL_SPOTS_H
#define CLEAN_OV072_GULL_SPOTS_H

#include "main/acre_map.h"
#include "types.h"

void GullSpots_PlaceItems(void);
int GullSpots_PlaceOne(u8 *counts, int *acres, AcreMap *map);
int GullSpots_TileFits(int *acre, int *tile, AcreMap *map);

#endif
