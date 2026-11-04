/* The cafe's guests of the day: one byte of the state block (0xf52b) drawn at random each day
 * (CafeGuests_Draw, from the town's setting up and its daily update) and read only by
 * overlay 68's cafe guest (cafe_guest.h), which picks the special character sitting in the
 * cafe by it at set times of the day:
 *
 * - bit 0: a morning guest at 6:00-6:54;
 * - bits 1-3: none or one of four guests at 12:00-13:29;
 * - bits 4-6: none or one of three at 14:30-15:59 (never the same as bits 1-3 unless both are 0);
 * - bit 7: a late guest at 23:00-23:59 on weekdays, when Nook's store is at level 3.
 *
 * The weekday (Saturday, Sunday or another) sets the odds of each value. */
#ifndef CLEAN_MAIN_CAFE_GUESTS_H
#define CLEAN_MAIN_CAFE_GUESTS_H

#include "types.h"

#define CAFE_GUESTS_MORNING_SHIFT 0
#define CAFE_GUESTS_MORNING_MASK 0x01
#define CAFE_GUESTS_NOON_SHIFT 1
#define CAFE_GUESTS_NOON_MASK 0x0e
#define CAFE_GUESTS_AFTERNOON_SHIFT 4
#define CAFE_GUESTS_AFTERNOON_MASK 0x70
#define CAFE_GUESTS_NIGHT_SHIFT 7
#define CAFE_GUESTS_NIGHT_MASK 0x80

int CafeGuests_Night(const u8 *plan);
int CafeGuests_Afternoon(const u8 *plan);
int CafeGuests_Noon(const u8 *plan);
int CafeGuests_Morning(const u8 *plan);
void CafeGuests_Draw(u8 *plan);
void CafeGuests_SetUp(u8 *plan);
void CafeGuests_Clear(u8 *plan);
void CafeGuests_Destruct(u8 *plan);
void CafeGuests_Construct(u8 *plan);

#endif
