/* The sources of a date and of random numbers the item draws take (date_random.h). */
#include "date_random.h"

#include "clean.h"
#include "date_time.h"
#include "item_lists.h"
#include "item_group_order.h"

static_assert(sizeof(DatedRandom) == 0x0c && offsetof(DatedRandom, random) == 0x04 && offsetof(DatedRandom, year) == 0x08,
              "DatedRandom layout");

extern const u8 data_020de664[]; /* the clock's vtable */
extern const u8 data_020de64c[]; /* the dated one's */
/* The game's main generator (main_random.h). */
extern Random data_021cb5a0;
/* The state block's nine bytes at 0x173d4, one per item kind (item_lists.h). */
extern u8 data_021f3b7c[];

/* The seed of a fresh dated source, before its date is set. */
#define DATED_RANDOM_FIRST_SEED 1

/* ---- the dated source */

/* func_02062fdc (vtable slot 0): its year. */
int DatedRandom_Year(DatedRandom *self)
{
    return self->year;
}
CLEAN_AS(func_02062fdc, DatedRandom_Year)

/* func_02062fe0 (vtable slot 1): its month. */
int DatedRandom_Month(DatedRandom *self)
{
    return self->month;
}
CLEAN_AS(func_02062fe0, DatedRandom_Month)

/* func_02062fe4 (vtable slot 2): its day. */
int DatedRandom_Day(DatedRandom *self)
{
    return self->day;
}
CLEAN_AS(func_02062fe4, DatedRandom_Day)

/* func_02063cd4 (vtable slot 3): a number below `bound` from its own generator. */
u32 DatedRandom_Below(DatedRandom *self, u32 bound)
{
    return Random_Below(&self->random, bound);
}
CLEAN_AS(func_02063cd4, DatedRandom_Below)

/* func_02063ce0: the date kept, and the generator seeded from it (DatedRandom_Seed). */
void DatedRandom_SetDate(DatedRandom *self, u8 year, u8 month, u8 day)
{
    self->year = year;
    self->month = month;
    self->day = day;
    Random_Init(&self->random, DatedRandom_Seed(year, month, day));
}
CLEAN_AS(func_02063ce0, DatedRandom_SetDate)

/* The state block's byte for kind `kind`. */
static u32 dated_random_byte(int kind)
{
    return (u8) ItemGroupOrder_Get(ItemLists_TierByte(data_021f3b7c, kind));
}

/* func_02063d04: the seed of a date: the date's three numbers packed (the year, the month from
 * bit 7, the day from bit 11) and repeated 16 bits up, mixed by exclusive or with the day from
 * bit 30 and with the state block's bytes for kinds 2, 3, 6, 1, 4 and 0, from bit 25 down by
 * steps of five (the bytes read in the order 0, 4, 1, 6, 3, 2). */
u32 DatedRandom_Seed(u32 year, u32 month, u32 day)
{
    u32 byte0 = dated_random_byte(0);
    u32 byte4 = dated_random_byte(4);
    u32 byte1 = dated_random_byte(1);
    u32 byte6 = dated_random_byte(6);
    u32 byte3 = dated_random_byte(3);
    u32 byte2 = dated_random_byte(2);

    u32 packed = year | (day << 11) | (month << 7);
    packed |= packed << 16;
    return (day << 30) ^ (byte2 << 25) ^ (byte3 << 20) ^ (byte6 << 15) ^ (byte1 << 10) ^ (byte4 << 5) ^ byte0 ^ packed;
}
CLEAN_AS(func_02063d04, DatedRandom_Seed)

/* func_02063db4: the date set to today's, from the clock. */
void DatedRandom_SetToday(DatedRandom *self)
{
    DateTime now = {0};
    DateTime_Now(&now);
    DatedRandom_SetDate(self, now.year, now.month, now.day);
}
CLEAN_AS(func_02063db4, DatedRandom_SetToday)

/* func_02063ddc: the destructor. */
DatedRandom *DatedRandom_Destruct(DatedRandom *self)
{
    self->base.vtable = (const DateRandomVtable *) data_020de64c;
    DateRandom_DestructBase(&self->base);
    return self;
}
CLEAN_AS(func_02063ddc, DatedRandom_Destruct)

/* func_02063df4: the constructor: the generator seeded with 1, then the date set to today's. */
DatedRandom *DatedRandom_Construct(DatedRandom *self)
{
    DateRandom_ConstructBase(&self->base);
    self->base.vtable = (const DateRandomVtable *) data_020de64c;
    Random_Init(&self->random, DATED_RANDOM_FIRST_SEED);
    DatedRandom_SetToday(self);
    return self;
}
CLEAN_AS(func_02063df4, DatedRandom_Construct)

/* ---- the clock's source */

/* func_02063e1c (vtable slot 2): today's day. */
int DateRandom_Day(void)
{
    DateTime now = {0};
    DateTime_Now(&now);
    return now.day;
}
CLEAN_AS(func_02063e1c, DateRandom_Day)

/* func_02063e38 (vtable slot 1): today's month. */
u8 DateRandom_Month(void)
{
    DateTime now = {0};
    DateTime_Now(&now);
    return now.month;
}
CLEAN_AS(func_02063e38, DateRandom_Month)

/* func_02063e54 (vtable slot 0): today's year. */
u8 DateRandom_Year(void)
{
    DateTime now = {0};
    DateTime_Now(&now);
    return now.year;
}
CLEAN_AS(func_02063e54, DateRandom_Year)

/* func_02063e70 (vtable slot 3): a number below `bound` from the game's main generator.
 * QUIRK: declared without a result; in the ROM the number is still in r0 when it returns, and
 * the item draws' callers of the slot use it. */
void DateRandom_Below(u32 self, u32 bound)
{
    (void) self;
    Random_Below(&data_021cb5a0, bound);
}
CLEAN_AS(func_02063e70, DateRandom_Below)

/* func_02063e80: the destructor the dated source calls. */
void DateRandom_DestructBase(DateRandom *self)
{
    self->vtable = (const DateRandomVtable *) data_020de664;
}
CLEAN_AS(func_02063e80, DateRandom_DestructBase)

/* func_02063e8c: the destructor. */
void DateRandom_Destruct(DateRandom *self)
{
    self->vtable = (const DateRandomVtable *) data_020de664;
}
CLEAN_AS(func_02063e8c, DateRandom_Destruct)

/* func_02063e98: the constructor. */
void DateRandom_Construct(DateRandom *self)
{
    self->vtable = (const DateRandomVtable *) data_020de664;
}
CLEAN_AS(func_02063e98, DateRandom_Construct)

/* func_02063ea4: the constructor the dated source calls. */
void DateRandom_ConstructBase(DateRandom *self)
{
    self->vtable = (const DateRandomVtable *) data_020de664;
}
CLEAN_AS(func_02063ea4, DateRandom_ConstructBase)
