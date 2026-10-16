/* The band of a creature list entry's weight (its third byte, creature_table.h): the place of
 * the first of four falling thresholds the weight reaches, 4 when it reaches none. Two sets of
 * thresholds: 17, 11, 6, 3 (data_020d1a24, read by the lists of the 56 kinds of items
 * 0x12e8-0x131f) and 15, 10, 6, 3 (data_020d1a2c, read by func_0202d2a0). */
#ifndef CLEAN_MAIN_CREATURE_WEIGHT_H
#define CLEAN_MAIN_CREATURE_WEIGHT_H

#include "types.h"

#define CREATURE_WEIGHT_BANDS 4

int CreatureWeight_BandA(u32 weight);
int CreatureWeight_BandB(u32 weight);
int CreatureWeight_Band(u8 weight, const u8 *thresholds, int count);

#endif
