/* func_020425a8 @ 0x020425a8, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern int func_02098880(void *);
extern int func_0203fae4(void);
extern int func_0209e380(void *, void *);
extern void func_0204287c(void *, void *, void *);
extern void func_0204cc34(void *, void *);
extern void func_020428e8(void *, void *, void *);
extern void func_02042684(void *, void *, void *);
extern void func_0209e29c(void *, int);

void func_020425a8(void *a0, u8 *o, int n, const void *src, int wd)
{
    int flag;
    u32 b[2];
    u32 a[2];
    u32 c[2];
    u32 d[2];
    u8 *p3;
    int w;

    flag = 0;
    b[0] = 0;
    b[1] = 0;
    a[0] = 0;
    a[1] = 0;
    p3 = o + 0x1725c;
    MI_CpuCopy8(src, a, 8);
    w = wd;

    if (o[0x17276] != 0 || func_02098880(o + 0x14) > 1 || func_0203fae4() == 0) {
        flag = 1;
    }

    while (n > 0) {
        b[0] = 0;
        b[1] = 0;
        ((u8 *) b)[5] = p3[2];
        ((u8 *) b)[4] = p3[1];
        ((u8 *) b)[3] = p3[0];
        if (func_0209e380(a, b) == 0) {
            MI_CpuCopy8(b, c, 8);
            func_0204287c(a0, o, c);
            func_0204cc34(o + 0x17254, p3);
        }
        if (w == 1) {
            MI_CpuCopy8(a, d, 8);
            func_020428e8(a0, o, d);
        }
        if (flag != 0) {
            func_02042684(a0, o, a);
        }
        n = n - 1;
        w = (w + 1) % 7;
        func_0209e29c(a, 1);
    }
}
