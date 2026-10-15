#include "../../../clean/main/date_time.h"
#include "diffcheck.h"

#define WHEN (DIFF_SCRATCH + 0x10)
#define OTHER (DIFF_SCRATCH + 0x20)
#define CLOCK_DATE 0x021dc744u
#define CLOCK_TIME 0x021dc754u

static uint32_t *word_at(uint32_t address)
{
    return (uint32_t *) (uintptr_t) address;
}

static DateTime *at(uint32_t address)
{
    return (DateTime *) (uintptr_t) address;
}

/* A valid date and time in 2000-2099, the clock's range. */
static DateTime random_date_time(DiffRng *rng)
{
    DateTime t;
    t.year = (u8) diff_range(rng, 0, 99);
    t.month = (u8) diff_range(rng, 1, 12);
    t.day = (u8) diff_range(rng, 1, Calendar_DaysInMonth(t.year, t.month));
    t.hour = (u8) diff_range(rng, 0, 23);
    t.minute = (u8) diff_range(rng, 0, 59);
    t.second = (u8) diff_range(rng, 0, 59);
    t.unused[0] = t.unused[1] = 0;
    return t;
}

/* The clock as the ARM7 leaves it. */
static void set_clock(DiffRng *rng)
{
    DateTime now = random_date_time(rng);
    word_at(CLOCK_DATE)[0] = now.year;
    word_at(CLOCK_DATE)[1] = now.month;
    word_at(CLOCK_DATE)[2] = now.day;
    word_at(CLOCK_DATE)[3] = (uint32_t) diff_range(rng, 0, 6);
    word_at(CLOCK_TIME)[0] = now.hour;
    word_at(CLOCK_TIME)[1] = now.minute;
    word_at(CLOCK_TIME)[2] = now.second;
}

/* An amount of some unit: mostly small, sometimes several carries' worth. */
static int random_amount(DiffRng *rng)
{
    switch (diff_range(rng, 0, 3)) {
        case 0:
            return diff_range(rng, 0, 3);
        case 1:
            return diff_range(rng, 0, 70);
        case 2:
            return diff_range(rng, 0, 400);
        default:
            return diff_range(rng, 0, 2000);
    }
}

static void a_time_and_amount(DiffRng *rng, uint32_t args[4])
{
    *at(WHEN) = random_date_time(rng);
    args[0] = WHEN;
    args[1] = (uint32_t) random_amount(rng);
}

static void a_time_and_amounts(DiffRng *rng, uint32_t args[4])
{
    *at(WHEN) = random_date_time(rng);
    u8 *amount = (u8 *) at(OTHER);
    for (int i = 0; i < 6; i++) {
        amount[i] = (u8) (diff_range(rng, 0, 1) ? diff_range(rng, 0, 70) : diff_range(rng, 0, 255));
    }
    amount[6] = amount[7] = 0;
    args[0] = WHEN;
    args[1] = OTHER;
}

/* Two times, often close: the same, or one field changed. */
static void two_times(DiffRng *rng, uint32_t args[4])
{
    *at(WHEN) = random_date_time(rng);
    *at(OTHER) = diff_range(rng, 0, 2) == 0 ? random_date_time(rng) : *at(WHEN);
    if (diff_range(rng, 0, 1)) {
        u8 *field = (u8 *) at(OTHER) + diff_range(rng, 0, 5);
        *field = (u8) (*field + diff_range(rng, -1, 1));
    }
    args[0] = WHEN;
    args[1] = OTHER;
    args[2] = (uint32_t) diff_range(rng, 0, 63);
}

static void a_week(DiffRng *rng, uint32_t args[4])
{
    set_clock(rng);
    *at(WHEN) = random_date_time(rng);
    *at(OTHER) = random_date_time(rng);
    args[0] = WHEN;
    switch (diff_range(rng, 0, 3)) {
        case 0:
            args[1] = WHEN;
            break;
        case 1:
            args[1] = 0;
            break;
        default:
            args[1] = OTHER;
    }
}

static void clock_only(DiffRng *rng, uint32_t args[4])
{
    set_clock(rng);
    args[0] = WHEN;
}

#define BY_AMOUNT(fn)                                                                                                         \
    static uint32_t run_##fn(const uint32_t args[4])                                                                          \
    {                                                                                                                         \
        DateTime_##fn(at(args[0]), (int) args[1]);                                                                            \
        return 0;                                                                                                             \
    }

BY_AMOUNT(SubtractSeconds)
BY_AMOUNT(SubtractMinutes)
BY_AMOUNT(SubtractHours)
BY_AMOUNT(SubtractDays)
BY_AMOUNT(SubtractMonths)
BY_AMOUNT(SubtractYears)
BY_AMOUNT(AddSeconds)
BY_AMOUNT(AddMinutes)
BY_AMOUNT(AddHours)
BY_AMOUNT(AddDays)
BY_AMOUNT(AddMonths)
BY_AMOUNT(AddYears)

static uint32_t subtract(const uint32_t args[4])
{
    DateTime_Subtract(at(args[0]), at(args[1]));
    return 0;
}

static uint32_t start_of_week(const uint32_t args[4])
{
    DateTime_StartOfWeek(at(args[0]), args[1] ? at(args[1]) : NULL);
    return 0;
}

static uint32_t minutes_between(const uint32_t args[4])
{
    return (uint32_t) DateTime_MinutesBetween(at(args[0]), at(args[1]));
}

static uint32_t days_between(const uint32_t args[4])
{
    return (uint32_t) DateTime_DaysBetween(at(args[0]), at(args[1]));
}

static uint32_t compare(const uint32_t args[4])
{
    return (uint32_t) DateTime_Compare(at(args[0]), at(args[1]), (int) args[2]);
}

static uint32_t now(const uint32_t args[4])
{
    DateTime_Now(at(args[0]));
    return 0;
}

DIFF_CHECK(func_0209e040, "main", 0x0209e040 | 1, 0, 1, a_time_and_amounts, subtract)
DIFF_CHECK(func_0209e080, "main", 0x0209e080 | 1, 0, 1, a_time_and_amount, run_SubtractSeconds)
DIFF_CHECK(func_0209e0c0, "main", 0x0209e0c0 | 1, 0, 1, a_time_and_amount, run_SubtractMinutes)
DIFF_CHECK(func_0209e100, "main", 0x0209e100 | 1, 0, 1, a_time_and_amount, run_SubtractHours)
DIFF_CHECK(func_0209e140, "main", 0x0209e140 | 1, 0, 1, a_time_and_amount, run_SubtractDays)
DIFF_CHECK(func_0209e1ac, "main", 0x0209e1ac | 1, 0, 1, a_time_and_amount, run_SubtractMonths)
DIFF_CHECK(func_0209e1f0, "main", 0x0209e1f0 | 1, 0, 0, a_time_and_amount, run_SubtractYears)
DIFF_CHECK(func_0209e200, "main", 0x0209e200 | 1, 0, 1, a_time_and_amount, run_AddSeconds)
DIFF_CHECK(func_0209e234, "main", 0x0209e234 | 1, 0, 1, a_time_and_amount, run_AddMinutes)
DIFF_CHECK(func_0209e268, "main", 0x0209e268 | 1, 0, 1, a_time_and_amount, run_AddHours)
DIFF_CHECK(func_0209e29c, "main", 0x0209e29c | 1, 0, 1, a_time_and_amount, run_AddDays)
DIFF_CHECK(func_0209e2d0, "main", 0x0209e2d0 | 1, 0, 1, a_time_and_amount, run_AddMonths)
DIFF_CHECK(func_0209e304, "main", 0x0209e304 | 1, 0, 0, a_time_and_amount, run_AddYears)
DIFF_CHECK(func_0209e314, "main", 0x0209e314 | 1, 0, 1, a_week, start_of_week)
DIFF_CHECK(func_0209e350, "main", 0x0209e350 | 1, 32, 1, two_times, minutes_between)
DIFF_CHECK(func_0209e380, "main", 0x0209e380 | 1, 32, 1, two_times, days_between)
DIFF_CHECK(func_0209e3ac, "main", 0x0209e3ac | 1, 32, 0, two_times, compare)
DIFF_CHECK(func_0209e474, "main", 0x0209e474 | 1, 0, 0, clock_only, now)
