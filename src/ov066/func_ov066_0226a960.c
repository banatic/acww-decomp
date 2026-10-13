/* func_ov066_0226a960 @ 0x0226a960, 0x158 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_0226a960 {
    u8 pad_00;
    u8 flag1;
    u8 flag2;
    u8 flag3;
    u8 flag4;
    u8 pad_05[3];
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 *unk_18;
    u16 unk_1C;
    u16 unk_1E;
    u32 unk_20;
    u32 unk_24;
    u32 unk_28;
    u32 unk_2C;
} UnkStruct_0226a960;

typedef struct Count {
    u8 pad_00[0xb];
    u8 count;
} Count;

extern UnkStruct_0226a960 *data_ov066_0226be08;
extern Count *data_ov066_0226bdec;

extern int OS_DisableInterrupts(int arg);
extern void func_ov066_0226bb7c(int value, int n);
extern void OS_RestoreInterrupts(int value);

void func_ov066_0226a960(int arg)
{
    int saved;
    u16 i;

    saved = OS_DisableInterrupts(arg);

    data_ov066_0226be08->unk_10 = data_ov066_0226be08->unk_08;
    func_ov066_0226bb7c(data_ov066_0226be08->unk_08, 3);
    func_ov066_0226bb7c(data_ov066_0226be08->unk_0C, 3);

    i = 0;
    while (i < data_ov066_0226bdec->count) {
        data_ov066_0226be08->unk_18[i] = data_ov066_0226be08->unk_0C;
        i++;
    }

    data_ov066_0226be08->flag1 &= ~0xf;
    data_ov066_0226be08->flag1 &= ~0xf0;
    data_ov066_0226be08->flag2 = 0;
    data_ov066_0226be08->flag3 = 0;
    data_ov066_0226be08->flag4 = (data_ov066_0226be08->flag4 & ~1) | 1;
    data_ov066_0226be08->flag4 &= ~2;
    data_ov066_0226be08->flag4 &= ~4;
    data_ov066_0226be08->flag4 &= ~8;
    data_ov066_0226be08->unk_14 = 0;
    data_ov066_0226be08->unk_1C = 0;
    data_ov066_0226be08->unk_1E = 0;
    data_ov066_0226be08->unk_20 = 0;
    data_ov066_0226be08->unk_24 = 0;
    data_ov066_0226be08->unk_28 = -1;
    data_ov066_0226be08->unk_2C = 0;

    OS_RestoreInterrupts(saved);
}
