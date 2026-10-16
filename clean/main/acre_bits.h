/* A bit for each of the 16 x 16 tiles of an acre, 16 rows of 16 bits. The town layout's acre
 * records (town_layout.h) are cleared as these, and the bits an acre points to at 0x24 are set
 * and cleared through them (func_02037d48, func_02037d2c). */
#ifndef CLEAN_MAIN_ACRE_BITS_H
#define CLEAN_MAIN_ACRE_BITS_H

#include "types.h"

#define ACRE_BITS_SIDE 16

typedef struct AcreBits {
    u16 rows[ACRE_BITS_SIDE]; /* bit x of row z: tile (x, z) */
} AcreBits;

int AcreBits_Clear(AcreBits *bits, unsigned int x, unsigned int z);
int AcreBits_Set(AcreBits *bits, unsigned int x, unsigned int z);
int AcreBits_ClearInRow(int unused, u16 *row, int x);
int AcreBits_SetInRow(int unused, u16 *row, int x);
void AcreBits_ClearAll(AcreBits *bits);
void AcreBits_Destruct(AcreBits *bits);
void AcreBits_Construct(AcreBits *bits);

#endif
