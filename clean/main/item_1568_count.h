/* A byte of the state block (0xf52a) kept for building 0x5020 (event_buildings.h): in its low
 * three bits how many of item 0x1568 overlay 72 has taken (it stops counting at 5), and in
 * bit 3 a mark overlay 72 sets. Cleared when the town is set up and when building 0x5020 is
 * placed; the spawner's placer func_02087a78 reads it too. */
#ifndef CLEAN_MAIN_ITEM_1568_COUNT_H
#define CLEAN_MAIN_ITEM_1568_COUNT_H

#include "types.h"

#define ITEM_1568_COUNT_MASK 0x07
#define ITEM_1568_COUNT_MARK 0x08

void Item1568Count_SetMark(u8 *count);
int Item1568Count_HasMark(const u8 *count);
void Item1568Count_Increment(u8 *count);
int Item1568Count_Get(const u8 *count);
void Item1568Count_SetUp(u8 *count);
void Item1568Count_Clear(u8 *count);
void Item1568Count_Destruct(u8 *count);
void Item1568Count_Construct(u8 *count);

#endif
