/* func_ov142_022996f0 @ 0x022996f0, 0xa4 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x990];
    u8 dstA[0x24];
    u8 dstB[1];
    u8 pad_mid[0x26ab];
    u16 arr0[0x10];
    u16 arr1[0x10];
    u16 arr2[0x10];
    u16 arr3[0x10];
} SELF;

extern void MIi_CpuCopy16(void *, const void *, u32);
extern u16 func_ov142_02299794(SELF *, u16, u16, u32);
extern void func_020b9b6c(void *, const void *, u32, u32);

void func_ov142_022996f0(SELF *self, u32 param)
{
    MIi_CpuCopy16(self->arr0, self->arr1, 0x20);
    MIi_CpuCopy16(self->arr2, self->arr3, 0x20);
    self->arr1[0xf] = func_ov142_02299794(self, self->arr0[0xf], self->arr0[8], param);
    self->arr3[0xf] = func_ov142_02299794(self, self->arr2[0xf], self->arr2[8], param);
    func_020b9b6c(self->dstA, self->arr1, 4, 3);
    func_020b9b6c(self->dstB, self->arr3, 4, 4);
}
