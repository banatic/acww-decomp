#include "diffcheck.h"

#include "types.h"

typedef struct SlotOwner SlotOwner;
BOOL func_02039444(const SlotOwner *owner, const void *item);

static void generate(DiffRng *rng, uint32_t args[4])
{
    uint32_t owner = DIFF_SCRATCH;
    uint32_t *slots = (uint32_t *) (uintptr_t) (owner + 0x2f4);
    for (int i = 0; i < 4; i++) {
        /* empty or holding an object */
        slots[i] = diff_range(rng, 0, 2) == 0 ? 0 : 0x02200000u + diff_range(rng, 0, 15) * 0x100;
    }
    args[0] = owner;
    switch (diff_range(rng, 0, 2)) {
        case 0:
            args[1] = slots[diff_range(rng, 0, 3)]; /* one of the slots, possibly empty */
            break;
        case 1:
            args[1] = 0; /* null: found exactly when a slot is empty */
            break;
        default:
            args[1] = 0x02200000u + diff_range(rng, 0, 15) * 0x100;
            break;
    }
}

static uint32_t run_clean(const uint32_t args[4])
{
    return (uint32_t) func_02039444((const SlotOwner *) (uintptr_t) args[0], (const void *) (uintptr_t) args[1]);
}

const DiffTest diff_test_func_02039444 = {
    .address = 0x02039444 | 1,
    .module = "main",
    .name = "func_02039444",
    .cases = 2000,
    .return_bits = 32,
    .generate = generate,
    .run_clean = run_clean,
};
