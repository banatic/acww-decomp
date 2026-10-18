/* A spot beside a requested position (part 0x31 of the object at data_021d27ac,
 * block_021d27ac.h): one byte of bits. The first time it is placed it picks at random a side
 * (two tiles to +z, -x or +x of the request's position) and a quarter turn to face; the
 * spawner's placer Spawner_PlaceFromPart31 puts the actor there (BesideSpot_Place). The
 * spawner clears its "served" bit when it is created and sets it when it serves an entry. */
#ifndef CLEAN_MAIN_BESIDE_SPOT_H
#define CLEAN_MAIN_BESIDE_SPOT_H

#include "autoload_2/vector.h"
#include "spawner.h"
#include "types.h"

#define BESIDE_SPOT_SERVED 0x01    /* the spawner served an entry since it was created */
#define BESIDE_SPOT_CHOSEN 0x02    /* the side and the facing were picked */
#define BESIDE_SPOT_SIDE_MASK 0x0c /* 0-2: an entry of data_020d06ec and data_020d06e4 */
#define BESIDE_SPOT_SIDE_SHIFT 2
#define BESIDE_SPOT_FACING_MASK 0x30 /* the quarter turn faced, 0-3 */
#define BESIDE_SPOT_FACING_SHIFT 4

/* An offset of data_020d06ec from the request's position. */
typedef struct BesideSpotOffset {
    fx32 x;
    fx32 z;
} BesideSpotOffset;

void BesideSpot_Place(u8 *spot, Vec3 *position, u16 *angle_y, const SpawnerRequest *request);
void BesideSpot_SetServed(u8 *spot);
void BesideSpot_ClearServed(u8 *spot);
int BesideSpot_WasServed(const u8 *spot);
void BesideSpot_Choose(u8 *spot);
void BesideSpot_Clear(u8 *spot);
void BesideSpot_Destruct(u8 *spot);
void BesideSpot_Construct(u8 *spot);

#endif
