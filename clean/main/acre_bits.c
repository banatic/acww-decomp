/* The bits of an acre's tiles (acre_bits.h). */
#include "acre_bits.h"

#include "clean.h"

static_assert(sizeof(AcreBits) == 0x20, "acre bits size");

extern void MI_CpuFill8(void *dst, u8 value, u32 size);

/* func_02037c78: the bit of tile (x, z) cleared; whether both are below 16. */
int AcreBits_Clear(AcreBits *bits, unsigned int x, unsigned int z)
{
    if (x < ACRE_BITS_SIDE && z < ACRE_BITS_SIDE) {
        return AcreBits_ClearInRow((int) (uintptr_t) bits, &bits->rows[z], (int) x);
    }
    return 0;
}
CLEAN_AS(func_02037c78, AcreBits_Clear)

/* func_02037c9c: the bit of tile (x, z) set; whether both are below 16. */
int AcreBits_Set(AcreBits *bits, unsigned int x, unsigned int z)
{
    if (x < ACRE_BITS_SIDE && z < ACRE_BITS_SIDE) {
        return AcreBits_SetInRow((int) (uintptr_t) bits, &bits->rows[z], (int) x);
    }
    return 0;
}
CLEAN_AS(func_02037c9c, AcreBits_Set)

/* func_02037cc0: bit `x` of a row cleared; whether x is 0-15. The first argument (the record)
 * is not used. */
int AcreBits_ClearInRow(int unused, u16 *row, int x)
{
    (void) unused;
    if (x >= 0 && x < ACRE_BITS_SIDE) {
        *row = (u16) (*row & ~(1u << x));
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02037cc0, AcreBits_ClearInRow)

/* func_02037ce0: bit `x` of a row set; whether x is 0-15. The first argument is not used. */
int AcreBits_SetInRow(int unused, u16 *row, int x)
{
    (void) unused;
    if (x >= 0 && x < ACRE_BITS_SIDE) {
        *row = (u16) (*row | 1u << x);
        return 1;
    }
    return 0;
}
CLEAN_AS(func_02037ce0, AcreBits_SetInRow)

/* func_02037d00: every bit cleared. */
void AcreBits_ClearAll(AcreBits *bits)
{
    MI_CpuFill8(bits, 0, sizeof(*bits));
}
CLEAN_AS(func_02037d00, AcreBits_ClearAll)
