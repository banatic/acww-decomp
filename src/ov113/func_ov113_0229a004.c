/* func_ov113_0229a004 @ 0x0229a004, 0xe8 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 func_020781d0(u32);
extern u32 func_020782cc(u32);
extern void func_0206de88(u32, void *, void *, u32, u32, u32, u32);
extern void func_020a8c1c(void *, u32);
extern void func_02070870(void *, u32, u32, u32, u32);
extern void func_02070a54(void *, void *, u32, u32, u32);
extern void func_02070a04(void *, u32, u32);
extern void func_020b9c10(void *, void *, u32, u32, u32, u32);
extern unsigned char data_021eed68[];

void func_ov113_0229a004(unsigned char *self)
{
    u32 a;
    u32 arr[7];
    u32 tmp;
    u32 zero1;
    u32 zero2;
    int i;
    a = func_020781d0((unsigned int) data_021eed68);
    func_0206de88(func_020782cc(a), arr, &tmp, 0x60, 0x10, 0xa0, 6);
    zero1 = 0;
    for (i = 0; i < 6; i++) {
        unsigned char *base1;
        unsigned char *p;
        u32 offset;
        u32 diff;
        u32 t;
        diff = arr[i + 1] - arr[i];
        offset = i;
        offset = offset * 0x6c;
        base1 = self + 0x2898;
        p = base1;
        p = p + offset;
        func_020a8c1c(p, offset);
        if (diff != 0) {
            t = func_020782cc(a);
            func_02070870(p, t + (2 * arr[i]), diff, zero1, zero1);
        }
    }

    zero2 = 0;
    for (i = 0; i < 6; i++) {
        unsigned char *base1;
        unsigned char *base2;
        unsigned char *p;
        unsigned char *dst;
        base1 = self + 0x2898;
        base2 = self + 0x8a0;
        p = base1 + (i * 0x6c);
        dst = base2 + (i * 0x500);
        func_02070a54(p, dst, 0x14, 0xe, 0xd);
        func_02070a04(p, zero2, zero2);
    }

    func_020b9c10(self + 0x26a0, self + 0x8a0, 2, 0x11, 0x11, 0x100);
}
