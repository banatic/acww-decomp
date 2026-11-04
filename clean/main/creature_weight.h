/* The band of a creature list entry's weight: the place of the first of four falling
 * thresholds the weight reaches, 4 when it reaches none. Two sets of thresholds: 17, 11, 6, 3
 * (data_020d1a24) for the fish lists (CreatureWeight_FishBand: the entry's third byte,
 * creature_table.h, of the 56 fish 0x12e8-0x131f) and 15, 10, 6, 3 (data_020d1a2c) for the
 * insect lists (CreatureWeight_InsectBand: the step of an entry's running total,
 * InsectDraw_OfList, insect_draw.h). */
#ifndef CLEAN_MAIN_CREATURE_WEIGHT_H
#define CLEAN_MAIN_CREATURE_WEIGHT_H

#include "types.h"

#define CREATURE_WEIGHT_BANDS 4

int CreatureWeight_FishBand(u32 weight);
int CreatureWeight_InsectBand(u32 weight);
int CreatureWeight_Band(u8 weight, const u8 *thresholds, int count);

#endif
