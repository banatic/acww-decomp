/* order_catalog_list: 5 functions, module ov142
 * mwccarm 1.2/base -O4,s
 * func_ov142_022996f0 @ 0x022996f0, 0xa4 bytes, Thumb
 * func_ov142_0229967c @ 0x0229967c, 0x74 bytes, Thumb
 * func_ov142_02299668 @ 0x02299668, 0x12 bytes, Thumb
 * func_ov142_02299658 @ 0x02299658, 0xe bytes, Thumb
 * func_ov142_02299648 @ 0x02299648, 0xe bytes, Thumb
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
extern int func_020b9b6c(void *, const void *, u32, u32);
extern void func_ov142_0229ab80(void *self, int val);

void func_ov142_022996f0(SELF *self, u32 param)
{
    MIi_CpuCopy16(self->arr0, self->arr1, 0x20);
    MIi_CpuCopy16(self->arr2, self->arr3, 0x20);
    self->arr1[0xf] = func_ov142_02299794(self, self->arr0[0xf], self->arr0[8], param);
    self->arr3[0xf] = func_ov142_02299794(self, self->arr2[0xf], self->arr2[8], param);
    func_020b9b6c(self->dstA, self->arr1, 4, 3);
    func_020b9b6c(self->dstB, self->arr3, 4, 4);
}

void func_ov142_0229967c(char *self)
{
    unsigned char state = *(unsigned char *) (self + 0xc2);

    switch (state) {
        case 0:
            return;
        case 1:
            if (*(unsigned char *) (self + 0xc1) != 0) {
                *(unsigned char *) (self + 0xc1) = *(volatile unsigned char *) (self + 0xc1) - 1;
            } else {
                *(unsigned char *) (self + 0xc2) = 2;
                func_ov142_0229ab80(self, *(unsigned char *) (self + 0xbd));
            }
            break;
        case 2:
            if (*(unsigned char *) (self + 0xc1) < 3) {
                *(unsigned char *) (self + 0xc1) = *(volatile unsigned char *) (self + 0xc1) + 1;
            } else {
                *(unsigned char *) (self + 0xc2) = 0;
                return;
            }
            break;
        default:
            break;
    }

    func_ov142_022996f0((SELF *) self, *(unsigned char *) (self + 0xc1));
}

int func_ov142_02299668(unsigned short *p, int mask)
{
    int r = p[0x5b] & mask;
    if (r != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_ov142_02299658(unsigned char *p, unsigned short mask)
{
    *(unsigned short *) (p + 0xb6) |= mask;
}

void func_ov142_02299648(unsigned short *p, unsigned short mask)
{
    p[0x5B] &= ~mask;
}
