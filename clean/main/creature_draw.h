/* Fish drawn from the creature tables (creature_table.h): the lists of a month's period, one per
 * time of day (CreatureTable_TimeSlot) and place (two), whose entries are a kind (the fish
 * 0x12e8 + kind for kinds below 0x38), a second number (the kind of water, which
 * CreatureDraw_PlaceGroup sorts) and a weight. A weight falls into one of five bands
 * (CreatureWeight_BandA: 0 for the heaviest, the commonest, to 4).
 *
 * A draw for a band picks a time of day among those of the given hours whose lists hold fish of
 * the band, then a place among those that do, then a fish of the band in that list, each at
 * random. Draws over several bands try the bands in a random order (CreatureDraw_FishOfBands)
 * or by weights (CreatureDraw_FishByWeights, 26, 23, 20, 17, 14) until one gives a fish. The
 * time slots and places a draw has seen are marked in two small tables of the game's
 * (data_021c1ce8, data_021c1ce4), and the weights in a third (data_021c1d18). */
#ifndef CLEAN_MAIN_CREATURE_DRAW_H
#define CLEAN_MAIN_CREATURE_DRAW_H

#include "creature_table.h"
#include "types.h"

#define CREATURE_DRAW_BANDS 5
#define CREATURE_DRAW_TIME_SLOTS 3
#define CREATURE_DRAW_PLACES 2

int CreatureDraw_PlaceGroup(int place);
int CreatureDraw_FishAvailable(u16 *item, int first_hour, int last_hour, int month, u8 day);
void CreatureDraw_FishNow(u16 *item);
int CreatureDraw_FishByWeights(u16 *item, int *band, int *second, int *time_slot, void *period);
int CreatureDraw_FishOfBands(u16 *item, int first, int last, int month, unsigned char day);
int CreatureDraw_FishOfBandsHours(u16 *item, int first, int last, int month, u8 day, u8 first_hour, u8 last_hour);
int CreatureDraw_FishOfBand(u16 *item, int *second, int *time_slot, int band, void *period);
int CreatureDraw_FishOfBandHours(u16 *item, int *second, int *time_slot, int band, CreatureTablePeriod *period, u8 first_hour,
                                 u8 last_hour);
int CreatureDraw_FishOfSlot(u16 *item, int *second, int band, CreatureTableList *const *slot);
int CreatureDraw_CountInSlot(int band, CreatureTableList *const *slot);
int CreatureDraw_FishOfList(u16 *item, int *second, int band, const CreatureTableList *list);
int CreatureDraw_CountInList(int band, const CreatureTableList *list);

#endif
