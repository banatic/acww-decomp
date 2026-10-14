#include "../../../clean/main/lookups.h"
#include "diffcheck.h"

#define BUFFER DIFF_SCRATCH

static void a_kind(DiffRng *rng, uint32_t args[4])
{
    args[0] = diff_range(rng, 0, 3) == 0 ? diff_rand(rng) : (uint32_t) diff_range(rng, 0, 7);
}

static uint32_t day_window(const uint32_t args[4])
{
    return (uint32_t) (uintptr_t) Lookups_DayWindow(args[0]);
}

/* A valid day of the year, often a sign's first or last day. */
static MonthDay random_birthday(DiffRng *rng)
{
    static const u8 last_day[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    MonthDay d;
    d.month = (u8) diff_range(rng, 1, 12);
    d.day = diff_range(rng, 0, 1) == 0 ? (u8) diff_range(rng, 18, 24) : (u8) diff_range(rng, 1, last_day[d.month - 1]);
    if (d.day > last_day[d.month - 1]) {
        d.day = last_day[d.month - 1];
    }
    return d;
}

static void a_birthday(DiffRng *rng, uint32_t args[4])
{
    MonthDay d = random_birthday(rng);
    *(MonthDay *) (uintptr_t) BUFFER = d;
    args[0] = BUFFER;
}

static void month_and_day(DiffRng *rng, uint32_t args[4])
{
    MonthDay d = random_birthday(rng);
    args[0] = d.month;
    args[1] = d.day;
}

static uint32_t star_sign_of(const uint32_t args[4])
{
    return Lookups_StarSignOf((const MonthDay *) (uintptr_t) args[0]);
}

static uint32_t star_sign(const uint32_t args[4])
{
    return Lookups_StarSign(args[0], args[1]);
}

/* A group and a number in it, sometimes out of range. */
static void a_pair(DiffRng *rng, uint32_t args[4])
{
    u8 *pair = (u8 *) (uintptr_t) BUFFER;
    pair[0] = (u8) diff_range(rng, 0, 6);
    pair[1] = diff_range(rng, 0, 7) == 0 ? (u8) diff_rand(rng) : (u8) diff_range(rng, 0, 13);
    args[0] = BUFFER;
}

static uint32_t slot_index(const uint32_t args[4])
{
    return Lookups_SlotIndex((const u8 *) (uintptr_t) args[0]);
}

/* An item code, mostly of kind 0xd and around the table's 38 entries. */
static void an_item(DiffRng *rng, uint32_t args[4])
{
    u16 kind = diff_range(rng, 0, 2) == 0 ? (u16) diff_range(rng, 0, 15) : 0xd;
    u16 index = diff_range(rng, 0, 3) == 0 ? (u16) diff_range(rng, 0, 0xfff) : (u16) diff_range(rng, 0, 40);
    *(ItemCode *) (uintptr_t) BUFFER = (ItemCode) (kind << 12 | index);
    args[0] = BUFFER;
}

static uint32_t kind_d_record(const uint32_t args[4])
{
    return (uint32_t) (uintptr_t) Lookups_KindDRecord((const ItemCode *) (uintptr_t) args[0]);
}

static uint32_t kind_d_first(const uint32_t args[4])
{
    return (uint32_t) Lookups_KindDFirst((const ItemCode *) (uintptr_t) args[0]);
}

DIFF_CHECK(func_0208222c, "main", 0x0208222c | 1, 32, 0, a_kind, day_window)
DIFF_CHECK(func_02082264, "main", 0x02082264 | 1, 32, 1, a_birthday, star_sign_of)
DIFF_CHECK(func_02082274, "main", 0x02082274 | 1, 32, 0, month_and_day, star_sign)
DIFF_CHECK(func_020822b0, "main", 0x020822b0 | 1, 8, 0, a_pair, slot_index)
DIFF_CHECK(func_020824d0, "main", 0x020824d0 | 1, 32, 0, an_item, kind_d_record)
DIFF_CHECK(func_02082374, "main", 0x02082374 | 1, 32, 1, an_item, kind_d_first)
