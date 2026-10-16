/* A player record's daily bits (daily_bits.h). */
#include "daily_bits.h"

#include "calendar.h"
#include "clean.h"

static_assert(offsetof(DailyBits, words) == 4, "daily bits");

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* func_02088768: bit `bit` cleared; a bit past the 64 is ignored. */
void DailyBits_Clear(DailyBits *bits, u32 bit)
{
    u32 word = bit >> 5;
    if (word < DAILY_BITS_WORDS) {
        bits->words[word] &= ~(1u << (bit & 0x1f));
    }
}
CLEAN_AS(func_02088768, DailyBits_Clear)

/* func_0208878c: bit `bit` set (a bit past the 64 is ignored), and the date becomes today in
 * either case. */
void DailyBits_Set(DailyBits *bits, u32 bit)
{
    u32 word = bit >> 5;
    if (word < DAILY_BITS_WORDS) {
        bits->words[word] |= 1u << (bit & 0x1f);
    }
    Date today;
    Calendar_Today(&today);
    DailyBits_SetDate(&bits->day, &today.day);
}
CLEAN_AS(func_0208878c, DailyBits_Set)

/* func_020887c0: whether bit `bit` is set; 0 for a bit past the 64. */
int DailyBits_Test(DailyBits *bits, u32 bit)
{
    u32 word = bit >> 5;
    if (word >= DAILY_BITS_WORDS) {
        return 0;
    }
    return (bits->words[word] & (1u << (bit & 0x1f))) != 0;
}
CLEAN_AS(func_020887c0, DailyBits_Test)

/* func_020887e8: a date's day, month and year copied (the year first). */
void DailyBits_SetDate(u8 *date, const u8 *source)
{
    date[2] = source[2];
    date[1] = source[1];
    date[0] = source[0];
}
CLEAN_AS(func_020887e8, DailyBits_SetDate)

/* func_020887f8: every bit cleared (the date is kept). */
void DailyBits_ClearAll(DailyBits *bits)
{
    MI_CpuFill8(bits->words, 0, sizeof(bits->words));
}
CLEAN_AS(func_020887f8, DailyBits_ClearAll)

/* func_02088808: the destructor, which does nothing. */
void DailyBits_Destruct(DailyBits *bits)
{
    (void) bits;
}
CLEAN_AS(func_02088808, DailyBits_Destruct)

/* func_0208880c: the constructor, which does nothing. */
void DailyBits_Construct(DailyBits *bits)
{
    (void) bits;
}
CLEAN_AS(func_0208880c, DailyBits_Construct)
