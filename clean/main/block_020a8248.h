/* A 12-byte record of main: a word and eight bytes. A large object of main keeps one at 0x14ac
 * (func_0206726c fills it, func_0206741c and its neighbours read it) and another at 0x354
 * (func_020ab3a8 copies one of four candidates into it). Its byte at 4 is a kind from 0 to 24
 * that indexes three tables of the game. */
#ifndef CLEAN_MAIN_BLOCK_020A8248_H
#define CLEAN_MAIN_BLOCK_020A8248_H

#include "types.h"

typedef struct Block020a8248 {
    u32 unk_00;
    u8 kind; /* 0x04: 0 to 24, indexes data_020d1c44, data_020d1ca8 and data_020d1d0c */
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0a;
    u8 unk_0b;
} Block020a8248;

int Block020a8248_FlagOfKind(Block020a8248 *record);
void *Block020a8248_ValueOfKind(Block020a8248 *record);
int Block020a8248_GroupOfKind(Block020a8248 *record);
void Block020a8248_GetByte08(u8 *out, Block020a8248 *record);
int Block020a8248_Byte09(Block020a8248 *record);
int Block020a8248_Byte07(Block020a8248 *record);
int Block020a8248_Byte06(Block020a8248 *record);
int Block020a8248_Byte05(Block020a8248 *record);
int Block020a8248_Kind(Block020a8248 *record);
void *Block020a8248_Self(void *record);
void Block020a8248_Clear(Block020a8248 *record);
void Block020a8248_Copy(void *dst, const void *src);
void Block020a8248_Destruct(void *record);
Block020a8248 *Block020a8248_Construct(Block020a8248 *record);

#endif
