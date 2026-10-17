/* The process of overlay 3 that puts the town's balls of snow in place when the town is entered
 * (vtable data_ov003_0223c550, derived from data_020da13c's; 0x50 bytes, the base process and
 * nothing more; its profile, data_ov003_0223c540, makes it with SnowballSpawner_New).
 *
 * Its creation (vtable slot 0) spawns the snowball actors (actor 0xbd, ov003/snowman.h), with
 * itself as their parent:
 *
 *   - for each snowman map object (0xb001-0xb003, map_code.h) standing in the town's 4 x 4
 *     inner acres, the snowman's two balls (group 2 + 2n the head, 3 + 2n the body) at the
 *     centre of its tile, when main still records snowman n (snowmen.h); a snowman object main
 *     no longer records is taken off the map;
 *   - the two loose balls (groups 0 and 1), in the snow season, in the town itself (scene 0),
 *     when no snowman was built today and fewer than three are recorded: at the points main
 *     kept for them (Snowmen_LooseBalls), or a new spot each (SnowballSpot_Pick, the second
 *     away from the first). A ball that is made has its point kept.
 *
 * Its deletion, execution and drawing (slots 3, 6 and 9) are done at once. */
#ifndef CLEAN_OV003_SNOWBALL_SPAWNER_H
#define CLEAN_OV003_SNOWBALL_SPAWNER_H

#include "autoload_2/process.h"
#include "types.h"

typedef struct SnowballSpawner {
    Process base;
} SnowballSpawner;

void SnowballSpawner_SpawnSnowmen(SnowballSpawner *self);
void SnowballSpawner_SpawnLooseBalls(SnowballSpawner *self);
int SnowballSpawner_Delete(void);
int SnowballSpawner_Draw(void);
int SnowballSpawner_Execute(void);
int SnowballSpawner_Create(SnowballSpawner *self);
SnowballSpawner *SnowballSpawner_DestructFree(SnowballSpawner *self);
SnowballSpawner *SnowballSpawner_Destruct(SnowballSpawner *self);
SnowballSpawner *SnowballSpawner_Construct(SnowballSpawner *self);
SnowballSpawner *SnowballSpawner_New(void);

#endif
