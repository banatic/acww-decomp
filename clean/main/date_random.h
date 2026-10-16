/* The sources of a date and of random numbers that the item draws take (item_lists.h): a small
 * class whose four vtable entries give a year, a month and a day (as DateTime holds them,
 * calendar.h) and a random number below a bound.
 *
 * - The clock's (vtable data_020de664, 4 bytes): today's date from the clock, and the numbers
 *   of the game's main generator (main_random.h). The item draws build one on their stack when
 *   they are given none.
 * - A dated one (vtable data_020de64c, 0x0c bytes): a date it keeps and a generator of its own
 *   seeded from it, so that the same date gives the same numbers (Nook's store seeds one with
 *   the day's date, nook_store.c). The seed mixes the date with the nine bytes of the state
 *   block at 0x173d4 (data_021f3b7c, one per item kind of item_lists.h). */
#ifndef CLEAN_MAIN_DATE_RANDOM_H
#define CLEAN_MAIN_DATE_RANDOM_H

#include "autoload_2/fx_math.h" /* Random */
#include "types.h"

/* The vtable's entries, as DS addresses. */
typedef struct DateRandomVtable {
    u32 year;  /* int (DateRandom *self) */
    u32 month; /* int (DateRandom *self) */
    u32 day;   /* int (DateRandom *self) */
    u32 below; /* u32 (DateRandom *self, u32 bound): a number below `bound` */
} DateRandomVtable;

typedef struct DateRandom {
    const DateRandomVtable *vtable; /* data_020de664, or a derived class's */
} DateRandom;

typedef struct DatedRandom {
    DateRandom base; /* 0x00: vtable data_020de64c */
    Random random;   /* 0x04 */
    u8 year;         /* 0x08 */
    u8 month;        /* 0x09 */
    u8 day;          /* 0x0a */
    u8 pad_0b;
} DatedRandom;

int DatedRandom_Year(DatedRandom *self);
int DatedRandom_Month(DatedRandom *self);
int DatedRandom_Day(DatedRandom *self);
u32 DatedRandom_Below(DatedRandom *self, u32 bound);
void DatedRandom_SetDate(DatedRandom *self, u8 year, u8 month, u8 day);
u32 DatedRandom_Seed(u32 year, u32 month, u32 day);
void DatedRandom_SetToday(DatedRandom *self);
DatedRandom *DatedRandom_Destruct(DatedRandom *self);
DatedRandom *DatedRandom_Construct(DatedRandom *self);
int DateRandom_Day(void);
u8 DateRandom_Month(void);
u8 DateRandom_Year(void);
void DateRandom_Below(u32 self, u32 bound);
void DateRandom_DestructBase(DateRandom *self);
void DateRandom_Destruct(DateRandom *self);
void DateRandom_Construct(DateRandom *self);
void DateRandom_ConstructBase(DateRandom *self);

#endif
