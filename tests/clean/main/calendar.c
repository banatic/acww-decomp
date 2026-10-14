#include "../../../clean/main/calendar.h"
#include "diffcheck.h"

#define DATE_A (DIFF_SCRATCH + 0x10)
#define DATE_B (DIFF_SCRATCH + 0x20)
#define CLOCK_DATE 0x021dc744u
#define CLOCK_TIME 0x021dc754u

static uint32_t *word_at(uint32_t address)
{
    return (uint32_t *) (uintptr_t) address;
}

static Date *date_at(uint32_t address)
{
    return (Date *) (uintptr_t) address;
}

/* A valid date in 2000-2099, the clock's range. */
static Date random_date(DiffRng *rng)
{
    Date d;
    d.year = (u8) diff_range(rng, 0, 99);
    d.month = (u8) diff_range(rng, 1, 12);
    d.day = (u8) diff_range(rng, 1, Calendar_DaysInMonth(d.year, d.month));
    d.unused = 0;
    return d;
}

/* The clock as the ARM7 leaves it: a valid date with any weekday, and a time of day. */
static void set_clock(DiffRng *rng)
{
    Date today = random_date(rng);
    word_at(CLOCK_DATE)[0] = today.year;
    word_at(CLOCK_DATE)[1] = today.month;
    word_at(CLOCK_DATE)[2] = today.day;
    word_at(CLOCK_DATE)[3] = (uint32_t) diff_range(rng, 0, 6);
    word_at(CLOCK_TIME)[0] = (uint32_t) diff_range(rng, 0, 23);
    word_at(CLOCK_TIME)[1] = (uint32_t) diff_range(rng, 0, 59);
    word_at(CLOCK_TIME)[2] = (uint32_t) diff_range(rng, 0, 59);
}

/* Two dates, sometimes equal or in the same month. */
static void two_dates(DiffRng *rng, uint32_t args[4])
{
    *date_at(DATE_A) = random_date(rng);
    *date_at(DATE_B) = diff_range(rng, 0, 3) == 0 ? *date_at(DATE_A) : random_date(rng);
    if (diff_range(rng, 0, 3) == 0) {
        date_at(DATE_B)->year = date_at(DATE_A)->year;
        date_at(DATE_B)->month = date_at(DATE_A)->month;
    }
    args[0] = DATE_A;
    args[1] = DATE_B;
}

static uint32_t is_on_or_after(const uint32_t args[4])
{
    return (uint32_t) Calendar_IsOnOrAfter(date_at(args[0]), date_at(args[1]));
}

static uint32_t days_from(const uint32_t args[4])
{
    return (uint32_t) Calendar_DaysFrom(date_at(args[0]), date_at(args[1]));
}

/* A time and a delta as the game passes them: two bytes in each argument register. */
static void two_times(DiffRng *rng, uint32_t args[4])
{
    args[0] = (uint32_t) diff_range(rng, 0, 59) | (uint32_t) diff_range(rng, 0, 23) << 8;
    args[1] = (uint32_t) diff_range(rng, 0, 59) | (uint32_t) diff_range(rng, 0, 23) << 8;
    args[2] = DATE_A;
}

static uint32_t add_time(const uint32_t args[4])
{
    Time time = {(u8) args[0], (u8) (args[0] >> 8)};
    Time delta = {(u8) args[1], (u8) (args[1] >> 8)};
    Calendar_AddTime(time, delta, (Time *) (uintptr_t) args[2]);
    return 0;
}

static void year_month(DiffRng *rng, uint32_t args[4])
{
    set_clock(rng);
    args[0] = (uint32_t) diff_range(rng, 0, 99);
    args[1] = (uint32_t) diff_range(rng, 1, 12);
    args[2] = (uint32_t) diff_range(rng, 0, 6); /* weekday */
    args[3] = (uint32_t) diff_range(rng, 1, 5); /* the nth */
}

static uint32_t days_in_month(const uint32_t args[4])
{
    return Calendar_DaysInMonth(args[0], args[1]);
}

static uint32_t nth_weekday(const uint32_t args[4])
{
    return (uint32_t) Calendar_NthWeekday((int) args[0], (int) args[1], (int) args[2], (int) args[3]);
}

static void a_date(DiffRng *rng, uint32_t args[4])
{
    set_clock(rng);
    Date d = random_date(rng);
    args[0] = d.year;
    args[1] = d.month;
    args[2] = d.day;
}

static uint32_t weekday(const uint32_t args[4])
{
    return (uint32_t) Calendar_Weekday((s8) args[0], (s8) args[1], (s8) args[2]);
}

static void clock_only(DiffRng *rng, uint32_t args[4])
{
    set_clock(rng);
    args[0] = DATE_A;
}

static uint32_t part_of_day(const uint32_t args[4])
{
    (void) args;
    return (uint32_t) Calendar_PartOfDay();
}

static uint32_t today(const uint32_t args[4])
{
    Calendar_Today(date_at(args[0]));
    return 0;
}

static uint32_t today_weekday(const uint32_t args[4])
{
    (void) args;
    return (uint32_t) Calendar_TodayWeekday();
}

static uint32_t now(const uint32_t args[4])
{
    Calendar_Now((Time *) (uintptr_t) args[0]);
    return 0;
}

/* Any day of the year, including the periods' boundaries. */
static void a_day(DiffRng *rng, uint32_t args[4])
{
    *date_at(DATE_A) = random_date(rng);
    args[0] = DATE_A;
}

static uint32_t period_a(const uint32_t args[4])
{
    return (uint32_t) Calendar_PeriodA(date_at(args[0]));
}

static uint32_t period_b(const uint32_t args[4])
{
    return (uint32_t) Calendar_PeriodB(date_at(args[0]));
}

static void a_date_time(DiffRng *rng, uint32_t args[4])
{
    DateTime *when = (DateTime *) (uintptr_t) DATE_B;
    Date d = random_date(rng);
    when->second = (u8) diff_range(rng, 0, 59);
    when->minute = (u8) diff_range(rng, 0, 59);
    when->hour = (u8) diff_range(rng, 0, 23);
    when->day = d.day;
    when->month = d.month;
    when->year = d.year;
    args[0] = DATE_B;
}

static uint32_t period_a_of(const uint32_t args[4])
{
    return (uint32_t) Calendar_PeriodAOf((const DateTime *) (uintptr_t) args[0]);
}

static uint32_t period_b_of(const uint32_t args[4])
{
    return (uint32_t) Calendar_PeriodBOf((const DateTime *) (uintptr_t) args[0]);
}

DIFF_CHECK(func_0209dd9c, "main", 0x0209dd9c | 1, 32, 0, two_dates, is_on_or_after)
DIFF_CHECK(func_0209dcdc, "main", 0x0209dcdc | 1, 32, 1, two_dates, days_from)
DIFF_CHECK(func_0209ddd4, "main", 0x0209ddd4 | 1, 0, 0, two_times, add_time)
DIFF_CHECK(func_0209de24, "main", 0x0209de24 | 1, 8, 0, year_month, days_in_month)
DIFF_CHECK(func_0209de44, "main", 0x0209de44 | 1, 32, 1, year_month, nth_weekday)
DIFF_CHECK(func_0209de88, "main", 0x0209de88 | 1, 32, 1, a_date, weekday)
DIFF_CHECK(func_0209dcac, "main", 0x0209dcac | 1, 32, 1, clock_only, part_of_day)
DIFF_CHECK(func_0209df64, "main", 0x0209df64 | 1, 0, 0, clock_only, today)
DIFF_CHECK(func_0209ded0, "main", 0x0209ded0 | 1, 32, 0, clock_only, today_weekday)
DIFF_CHECK(func_0209def4, "main", 0x0209def4 | 1, 0, 0, clock_only, now)
DIFF_CHECK(func_0209dc10, "main", 0x0209dc10 | 1, 32, 0, a_day, period_a)
DIFF_CHECK(func_0209dc74, "main", 0x0209dc74 | 1, 32, 0, a_day, period_b)
DIFF_CHECK(func_0209dbe4, "main", 0x0209dbe4 | 1, 32, 1, a_date_time, period_a_of)
DIFF_CHECK(func_0209dc48, "main", 0x0209dc48 | 1, 32, 1, a_date_time, period_b_of)
