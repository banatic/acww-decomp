#include "../../../clean/main/state_flags.h"
#include "diffcheck.h"

#define FLAGS 0x021cfc6cu
#define VALUE 0x021cfc7cu

/* The flags as the game keeps them: a few low bits, sometimes none or all; the value is a
 * fixed-point number around 1.0. */
static void set_state(DiffRng *rng)
{
    u16 flags = (u16) diff_range(rng, 0, 0x1f);
    if (diff_range(rng, 0, 7) == 0) {
        flags = (u16) diff_rand(rng);
    }
    *(u16 *) (uintptr_t) FLAGS = flags;
    *(fx32 *) (uintptr_t) VALUE = diff_range(rng, 0, 3) == 0 ? 0x1000 : diff_range(rng, -0x2000, 0x2000);
}

/* A mask of the flags the callers pass (single bits), several of them, none, or one with bits
 * above the flag word. */
static uint32_t random_mask(DiffRng *rng)
{
    switch (diff_range(rng, 0, 4)) {
        case 0:
            return 0;
        case 1:
            return (uint32_t) diff_range(rng, 1, 0x1f);
        case 2:
            return diff_rand(rng);
        default:
            return 1u << diff_range(rng, 0, 15);
    }
}

static void flags_and_mask(DiffRng *rng, uint32_t args[4])
{
    set_state(rng);
    args[0] = random_mask(rng);
}

/* The 16-bit parameters, as mwccarm's callers widen them. */
static void flags_and_short_mask(DiffRng *rng, uint32_t args[4])
{
    set_state(rng);
    args[0] = random_mask(rng) & 0xffff;
}

static void flags_and_value(DiffRng *rng, uint32_t args[4])
{
    set_state(rng);
    args[0] = diff_rand(rng);
}

static uint32_t test(const uint32_t args[4])
{
    return (uint32_t) StateFlags_Test(args[0]);
}

static uint32_t clear(const uint32_t args[4])
{
    StateFlags_Clear((u16) args[0]);
    return 0;
}

static uint32_t set(const uint32_t args[4])
{
    StateFlags_Set((u16) args[0]);
    return 0;
}

#define NO_ARGS(name, call)                                                                                                   \
    static uint32_t name(const uint32_t args[4])                                                                              \
    {                                                                                                                         \
        (void) args;                                                                                                          \
        return (uint32_t) (call);                                                                                             \
    }

#define NO_ARGS_VOID(name, call)                                                                                              \
    static uint32_t name(const uint32_t args[4])                                                                              \
    {                                                                                                                         \
        (void) args;                                                                                                          \
        call;                                                                                                                 \
        return 0;                                                                                                             \
    }

NO_ARGS(test1, StateFlags_Test1())
NO_ARGS_VOID(set1, StateFlags_Set1())
NO_ARGS_VOID(clear1, StateFlags_Clear1())
NO_ARGS(test2, StateFlags_Test2())
NO_ARGS(is_clear2, StateFlags_IsClear2())
NO_ARGS(test4, StateFlags_Test4())
NO_ARGS_VOID(set4, StateFlags_Set4())
NO_ARGS_VOID(clear4, StateFlags_Clear4())
NO_ARGS(test10, StateFlags_Test10())
NO_ARGS_VOID(set10, StateFlags_Set10())
NO_ARGS_VOID(clear10, StateFlags_Clear10())
NO_ARGS(value_or_one, StateFlags_ValueOrOne())
NO_ARGS(value_or_zero, StateFlags_ValueOrZero())
NO_ARGS_VOID(reset, StateFlags_Reset())

static uint32_t set_value(const uint32_t args[4])
{
    StateFlags_SetValue((fx32) args[0]);
    return 0;
}

DIFF_CHECK(func_0206fec8, "main", 0x0206fec8 | 1, 32, 0, flags_and_mask, test)
DIFF_CHECK(func_0206fee0, "main", 0x0206fee0 | 1, 0, 0, flags_and_short_mask, clear)
DIFF_CHECK(func_0206fef0, "main", 0x0206fef0 | 1, 0, 0, flags_and_short_mask, set)
DIFF_CHECK(func_0206fea4, "main", 0x0206fea4 | 1, 32, 1, flags_and_mask, test1)
DIFF_CHECK(func_0206feb0, "main", 0x0206feb0 | 1, 0, 1, flags_and_mask, set1)
DIFF_CHECK(func_0206febc, "main", 0x0206febc | 1, 0, 1, flags_and_mask, clear1)
DIFF_CHECK(func_0206fe54, "main", 0x0206fe54 | 1, 32, 1, flags_and_mask, test2)
DIFF_CHECK(func_0206fe60, "main", 0x0206fe60 | 1, 32, 1, flags_and_mask, is_clear2)
DIFF_CHECK(func_0206fd04, "main", 0x0206fd04 | 1, 32, 1, flags_and_mask, test4)
DIFF_CHECK(func_0206fcf8, "main", 0x0206fcf8 | 1, 0, 1, flags_and_mask, set4)
DIFF_CHECK(func_0206fcec, "main", 0x0206fcec | 1, 0, 1, flags_and_mask, clear4)
DIFF_CHECK(func_0206fce0, "main", 0x0206fce0 | 1, 32, 1, flags_and_mask, test10)
DIFF_CHECK(func_0206fcd4, "main", 0x0206fcd4 | 1, 0, 1, flags_and_mask, set10)
DIFF_CHECK(func_0206fcc8, "main", 0x0206fcc8 | 1, 0, 1, flags_and_mask, clear10)
DIFF_CHECK(func_0206fd10, "main", 0x0206fd10 | 1, 32, 1, flags_and_mask, value_or_one)
DIFF_CHECK(func_0206fd34, "main", 0x0206fd34 | 1, 32, 1, flags_and_mask, value_or_zero)
DIFF_CHECK(func_0206fd54, "main", 0x0206fd54 | 1, 0, 0, flags_and_value, set_value)
DIFF_CHECK(func_020700b8, "main", 0x020700b8 | 1, 0, 0, flags_and_mask, reset)
