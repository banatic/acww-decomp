/* Insects drawn from the insect tables: for each month (func_020617d8, the table at
 * data_020dded8) six lists, one per time of day (func_02061798: hours 0-3 and 23, 4-7, 8-15,
 * 16, 17-18, 19-22). A list's entries are two bytes: the insect's kind (the item 0x12b0 + kind,
 * kinds below 0x38) and a running total of the weights, so an entry's own weight is the step
 * from the entry before it. An entry's weight falls into one of five bands
 * (CreatureWeight_BandB: 0 for the heaviest, the commonest, to 4), and its kind has a place
 * (func_02061550: where in the town the insect lives).
 *
 * A draw for a band counts the entries of the band whose place is not on a list of places to
 * leave out, and picks one of them at random. Draws over several bands try the bands in a
 * random order (InsectDraw_OfBands, InsectDraw_Now) or by weights (InsectDraw_ByWeights,
 * 26, 23, 20, 17, 14, kept in data_021c1d10) until one gives an insect; draws over the hours
 * pick a time of day at random among those whose list holds insects of the band (marked in
 * data_021c1d20).
 *
 * Also here: a pick among a few places by weights of a byte each (InsectDraw_PickByWeights),
 * which the fish draws use too. */
#ifndef CLEAN_MAIN_INSECT_DRAW_H
#define CLEAN_MAIN_INSECT_DRAW_H

#include "calendar.h"
#include "types.h"

#define INSECT_DRAW_BANDS 5
#define INSECT_DRAW_TIME_SLOTS 6
/* The places InsectDraw_MissingPlaces can name. */
#define INSECT_DRAW_MISSING_MAX 4

/* One time of day's list: `count` entries of two bytes. */
typedef struct InsectDrawList {
    const u8 *entries;
    u8 count;
    u8 unk_05[3];
} InsectDrawList;

int InsectDraw_Available(u16 *item, int first_hour, int last_hour, int month);
void InsectDraw_Now(u16 *item);
int InsectDraw_ByWeights(u16 *item, int *band, int *place, int *time_slot, DateTime *when);
int InsectDraw_OfBandsHours(u16 *item, int first, int last, u8 first_hour, u8 last_hour, u8 month);
int InsectDraw_OfBands(u16 *item, int first, int last, int month);
int InsectDraw_OfBandAnyHour(u16 *item, int *place, int *time_slot, int band, const InsectDrawList *lists, const int *missing,
                             int missing_count);
int InsectDraw_OfBand(u16 *item, int *place, int *time_slot, int band, const InsectDrawList *lists, const int *missing,
                      int missing_count, u8 first_hour, u8 last_hour);
int InsectDraw_OfList(u16 *item, int *place, int band, const u8 *entries, int count, const int *missing, int missing_count);
int InsectDraw_CountInList(int band, const u8 *entries, int count, const int *missing, int missing_count);
int InsectDraw_IsListed(int place, const int *list, int count);
void InsectDraw_MissingPlaces(int *places, int *count);
int InsectDraw_PickByWeights(const u8 *weights, int count);

#endif
