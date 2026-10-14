/* The function-level differential check: a Clean function against the ROM's code.
 *
 * Each check (in tests/clean/) says where the function is, how to call the Clean version with
 * the four argument registers, and how to make an entry state: it writes the arguments and
 * whatever memory the function reads. The checker runs the ROM's code in the interpreter and
 * the Clean version natively from the same state and compares the return value and every
 * byte written outside the stack.
 */
#ifndef RUNTIME_DIFFCHECK_H
#define RUNTIME_DIFFCHECK_H

#include <stdint.h>

/* xorshift32: small, and the same sequence on every host */
typedef struct DiffRng {
    uint32_t state;
} DiffRng;

static inline uint32_t diff_rand(DiffRng *rng)
{
    uint32_t x = rng->state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rng->state = x;
    return x;
}

/* A uniform value in [lo, hi] */
static inline int32_t diff_range(DiffRng *rng, int32_t lo, int32_t hi)
{
    return lo + (int32_t) (diff_rand(rng) % (uint32_t) (hi - lo + 1));
}

/* Free main RAM the checks may build their inputs in: above everything the modules load. */
#define DIFF_SCRATCH 0x023e0000u
#define DIFF_SCRATCH_SIZE 0x00010000u

typedef struct DiffTest {
    uint32_t address;   /* the function, bit 0 set for Thumb */
    const char *module; /* "main", "ov004", ... */
    const char *name;
    int cases;
    /* the return value's width in bits (0 for void) and whether it is signed: only those bits
     * of r0 are compared */
    int return_bits;
    int return_signed;
    /* nonzero: the reference runs the functions it calls too (the Clean version calls its own
     * Clean callees), so the whole call tree is compared; otherwise a call stops the check */
    int follow_calls;
    void (*generate)(DiffRng *rng, uint32_t args[4]);
    uint32_t (*run_clean)(const uint32_t args[4]);
} DiffTest;

/* One check: `symbol` is the function's symbol, `address` its DS address (bit 0 set for Thumb),
 * `bits_` the width of its result (0 for void), `follow_` whether calls are followed. */
#define DIFF_CHECK(symbol, module_, address_, bits_, follow_, gen_, run_)                                                     \
    const DiffTest diff_test_##symbol = {.address = (address_),                                                               \
                                         .module = (module_),                                                                 \
                                         .name = #symbol,                                                                     \
                                         .cases = 3000,                                                                       \
                                         .return_bits = (bits_),                                                              \
                                         .follow_calls = (follow_),                                                           \
                                         .generate = (gen_),                                                                  \
                                         .run_clean = (run_)};

#endif
