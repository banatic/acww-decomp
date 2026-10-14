#include "../../../clean/main/item_code.h"
#include "diffcheck.h"

#define CODE DIFF_SCRATCH
#define OTHER (DIFF_SCRATCH + 0x10)

/* A code the game stores: a map object, a kind 1 item (piles at 0x1000-0x10ff), a kind 3 or 4
 * item with its variant, an actor of kind 0xd or 0xe, the 0x5000 and 0xb000 groups, or one of
 * the kind 0xf codes 0xf030, 0xf031 and "nothing". */
static u16 random_code(DiffRng *rng)
{
    switch (diff_range(rng, 0, 9)) {
        case 0:
            return (u16) diff_range(rng, 0, 0x102);
        case 1:
        case 2:
            return (u16) diff_range(rng, 0x1000, 0x14ff);
        case 3:
        case 4:
            return (u16) diff_range(rng, 0x3000, 0x4fff);
        case 5:
            return (u16) (0xd000 | diff_range(rng, 0, 37));
        case 6:
            return (u16) (0xe000 | diff_range(rng, 0, 0xff));
        case 7:
            return (u16) (diff_range(rng, 0, 1) ? diff_range(rng, 0x5000, 0x5021) : diff_range(rng, 0xb001, 0xb003));
        case 8:
            return (u16) diff_range(rng, 0xf030, 0xf031);
        default:
            return ITEM_CODE_NONE;
    }
}

static void a_code(DiffRng *rng, uint32_t args[4])
{
    *(ItemCode *) (uintptr_t) CODE = random_code(rng);
    args[0] = CODE;
}

static void code_and_value(DiffRng *rng, uint32_t args[4])
{
    a_code(rng, args);
    args[1] = diff_range(rng, 0, 3) == 0 ? diff_rand(rng) : random_code(rng);
}

static void two_codes(DiffRng *rng, uint32_t args[4])
{
    *(ItemCode *) (uintptr_t) CODE = random_code(rng);
    *(ItemCode *) (uintptr_t) OTHER = random_code(rng);
    args[0] = CODE;
    args[1] = OTHER;
}

/* A range the callers ask for, with the code near it. */
static void code_and_range(DiffRng *rng, uint32_t args[4])
{
    u16 first = random_code(rng);
    u16 last = (u16) (first + diff_range(rng, 0, 8));
    if (last < first) {
        last = first;
    }
    *(ItemCode *) (uintptr_t) CODE = (u16) (first + diff_range(rng, -2, 10));
    args[0] = CODE;
    args[1] = first;
    args[2] = last;
}

/* A kind 3 or 4 item and a variant, sometimes past 3. */
static void item_and_variant(DiffRng *rng, uint32_t args[4])
{
    args[0] = (uint32_t) diff_range(rng, 0, 0x7ff);
    args[1] = (uint32_t) (diff_range(rng, 0, 4) == 0 ? diff_range(rng, 4, 7) : diff_range(rng, 0, 3));
}

static void code_and_variant(DiffRng *rng, uint32_t args[4])
{
    a_code(rng, args);
    args[1] = (uint32_t) diff_range(rng, 0, 3);
}

/* One of the 64 items, sometimes past them, and a count of 1-4, sometimes 0 or 5. */
static void item_and_count(DiffRng *rng, uint32_t args[4])
{
    args[0] = (uint32_t) (diff_range(rng, 0, 4) == 0 ? diff_range(rng, 64, 80) : diff_range(rng, 0, 63));
    args[1] = (uint32_t) (diff_range(rng, 0, 4) == 0 ? diff_range(rng, 0, 5) : diff_range(rng, 1, 4));
}

#define CODE_ARG(i) ((ItemCode *) (uintptr_t) args[i])

static uint32_t get(const uint32_t args[4])
{
    return (uint32_t) ItemCode_Get(CODE_ARG(0));
}

static uint32_t set(const uint32_t args[4])
{
    ItemCode_Set(CODE_ARG(0), (int) args[1]);
    return 0;
}

static uint32_t copy(const uint32_t args[4])
{
    ItemCode_Copy(CODE_ARG(0), CODE_ARG(1));
    return 0;
}

static uint32_t in_range(const uint32_t args[4])
{
    return (uint32_t) ItemCode_InRange(CODE_ARG(0), (u16) args[1], (u16) args[2]);
}

static uint32_t kind(const uint32_t args[4])
{
    return (uint32_t) ItemCode_Kind(CODE_ARG(0));
}

static uint32_t is_kind1(const uint32_t args[4])
{
    return (uint32_t) ItemCode_IsKind1(CODE_ARG(0));
}

static uint32_t is_f031(const uint32_t args[4])
{
    return (uint32_t) ItemCode_IsF031(CODE_ARG(0));
}

static uint32_t is_f031_or_variant(const uint32_t args[4])
{
    return (uint32_t) ItemCode_IsF031OrVariant(CODE_ARG(0));
}

static uint32_t has_variant(const uint32_t args[4])
{
    return (uint32_t) ItemCode_HasVariant(CODE_ARG(0));
}

static uint32_t test_has_variant(const uint32_t args[4])
{
    ItemCode_TestHasVariant(CODE_ARG(0));
    return 0;
}

static uint32_t variant_item(const uint32_t args[4])
{
    return (uint32_t) ItemCode_VariantItem(CODE_ARG(0));
}

static uint32_t variant(const uint32_t args[4])
{
    return (uint32_t) ItemCode_Variant(CODE_ARG(0));
}

static uint32_t make_variant(const uint32_t args[4])
{
    return ItemCode_MakeVariant((int) args[0], (int) args[1]);
}

static uint32_t set_variant(const uint32_t args[4])
{
    ItemCode_SetVariant(CODE_ARG(0), (int) args[1]);
    return 0;
}

static uint32_t is_pile(const uint32_t args[4])
{
    return (uint32_t) ItemCode_IsPile(CODE_ARG(0));
}

static uint32_t test_is_pile(const uint32_t args[4])
{
    ItemCode_TestIsPile(CODE_ARG(0));
    return 0;
}

static uint32_t make_pile(const uint32_t args[4])
{
    return ItemCode_MakePile(args[0], args[1]);
}

static uint32_t pile_count(const uint32_t args[4])
{
    return (uint32_t) ItemCode_PileCount(CODE_ARG(0));
}

static uint32_t pile_item(const uint32_t args[4])
{
    return (uint32_t) ItemCode_PileItem(CODE_ARG(0));
}

DIFF_CHECK(func_0204b42c, "main", 0x0204b42c | 1, 32, 0, a_code, get)
DIFF_CHECK(func_0204b79c, "main", 0x0204b79c | 1, 0, 0, code_and_value, set)
DIFF_CHECK(func_0204bf18, "main", 0x0204bf18 | 1, 0, 0, two_codes, copy)
DIFF_CHECK(func_0204b48c, "main", 0x0204b48c | 1, 32, 0, code_and_range, in_range)
DIFF_CHECK(func_0204bcf8, "main", 0x0204bcf8 | 1, 32, 0, a_code, kind)
DIFF_CHECK(func_0204bd08, "main", 0x0204bd08 | 1, 32, 1, a_code, is_kind1)
DIFF_CHECK(func_0204bcb4, "main", 0x0204bcb4 | 1, 32, 1, a_code, is_f031)
DIFF_CHECK(func_0204bc90, "main", 0x0204bc90 | 1, 32, 1, a_code, is_f031_or_variant)
DIFF_CHECK(func_0204bcdc, "main", 0x0204bcdc | 1, 32, 1, a_code, has_variant)
DIFF_CHECK(func_0204bcd4, "main", 0x0204bcd4 | 1, 0, 1, a_code, test_has_variant)
DIFF_CHECK(func_0204bc64, "main", 0x0204bc64 | 1, 32, 1, a_code, variant_item)
DIFF_CHECK(func_0204bc7c, "main", 0x0204bc7c | 1, 32, 1, a_code, variant)
DIFF_CHECK(func_0204bc50, "main", 0x0204bc50 | 1, 16, 0, item_and_variant, make_variant)
DIFF_CHECK(func_0204bc28, "main", 0x0204bc28 | 1, 0, 1, code_and_variant, set_variant)
DIFF_CHECK(func_0204b268, "main", 0x0204b268 | 1, 32, 0, a_code, is_pile)
DIFF_CHECK(func_0204b260, "main", 0x0204b260 | 1, 0, 1, a_code, test_is_pile)
DIFF_CHECK(func_0204bd20, "main", 0x0204bd20 | 1, 16, 0, item_and_count, make_pile)
DIFF_CHECK(func_0204bd40, "main", 0x0204bd40 | 1, 32, 1, a_code, pile_count)
DIFF_CHECK(func_0204bd5c, "main", 0x0204bd5c | 1, 32, 1, a_code, pile_item)
