/* A byte of the state block (0xf52a) kept for building 0x5020 (event_buildings.h; the crashed
 * ship of tools/scenes.py's ship-crashed): in its low three bits how many spaceship parts
 * (item 0x1568, named so in item_info's dma.bin) overlay 72's gull has taken (it stops
 * counting at 5), and in bit 3 a mark overlay 72 sets. Cleared when the town is set up and when
 * building 0x5020 is placed; the spawner's placer func_02087a78 reads it too. */
#ifndef CLEAN_MAIN_SPACESHIP_PARTS_H
#define CLEAN_MAIN_SPACESHIP_PARTS_H

#include "types.h"

#define SPACESHIP_PARTS_COUNT_MASK 0x07
#define SPACESHIP_PARTS_MARK 0x08

void SpaceshipParts_SetMark(u8 *count);
int SpaceshipParts_HasMark(const u8 *count);
void SpaceshipParts_Increment(u8 *count);
int SpaceshipParts_Get(const u8 *count);
void SpaceshipParts_SetUp(u8 *count);
void SpaceshipParts_Clear(u8 *count);
void SpaceshipParts_Destruct(u8 *count);
void SpaceshipParts_Construct(u8 *count);

#endif
