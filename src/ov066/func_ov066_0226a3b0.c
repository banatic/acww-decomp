/* func_ov066_0226a3b0 @ 0x0226a3b0, 0x54 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_0226a3b0 {
    u8 pad_00;
    u8 unk_01;
    volatile u8 unk_02; // page count; volatile on purpose
    u8 pad_03;
    void *unk_04; // page buffer
} UnkStruct_0226a3b0;

void MIi_CpuClearFast(u32 data, void *destp, u32 size);
void DC_StoreRange(void *startAddr, u32 nBytes);
void func_ov066_0226a404(UnkStruct_0226a3b0 *p);

static inline void MI_CpuFillFast(void *dest, u32 data, u32 size)
{
    volatile u32 d = data;
    MIi_CpuClearFast(d, dest, size);
}

static inline void MI_CpuClearFast(void *dest, u32 size)
{
    MI_CpuFillFast(dest, 0, size);
}

void func_ov066_0226a3b0(UnkStruct_0226a3b0 *p)
{
    func_ov066_0226a404(p);
    p->unk_01 = 0;
    MI_CpuClearFast(p->unk_04, p->unk_02 * 0xe0);
    DC_StoreRange(p->unk_04, p->unk_02 * 0xe0);
}
