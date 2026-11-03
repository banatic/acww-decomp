/* villager_mode_record_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209c270 @ 0x0209c270, 0x50 bytes, Thumb
 * func_0209c214 @ 0x0209c214, 0x5a bytes, Thumb
 * func_0209c1cc @ 0x0209c1cc, 0x48 bytes, Thumb
 * func_0209c1c0 @ 0x0209c1c0, 0xc bytes, Thumb
 */

#include "types.h"

extern int func_0209c330(void *);
extern void func_0209c32c(void *, int);
extern void func_0209e474(void *);
extern void MI_CpuCopy8(void *, void *, int);
extern int func_0209c2c0(void *p);
extern int func_0209dffc(int a);
extern int func_0209c380(int a);
extern int func_0209e350(int a, int b);

void func_0209c270(unsigned char *arg0)
{
    if (func_0209c330(arg0) == 2) {
        arg0[0x21] = (arg0[0x21] & ~1) | 1;
    } else {
        arg0[0x21] = arg0[0x21] & ~1;
    }
    func_0209c32c(arg0, 8);
    func_0209e474(arg0);
    MI_CpuCopy8(arg0, arg0 + 8, 8);
}

void func_0209c214(void *p)
{
    if (func_0209c330(p) == 2 || func_0209c2c0(p) != 0) {
        *((u8 *) p + 0x21) = (*((u8 *) p + 0x21) & ~1) | 1;
    } else {
        *((u8 *) p + 0x21) &= ~1;
    }
    func_0209c32c(p, 0xb);
    func_0209e474(p);
    MI_CpuCopy8(p, (u8 *) p + 8, 8);
}

int func_0209c1cc(int a, int b, unsigned int c)
{
    int t;

    if (func_0209dffc(a) != 0) {
        goto ret0;
    }
    if (func_0209c380(a) == 0) {
        goto ret0;
    }
    t = func_0209e350(a, b);
    if (t < 0) {
        t = -t;
    }
    return (t / 0x5a0 >= c) ? 1 : 0;

ret0:
    return 0;
}

int func_0209c1c0(int a, int b)
{
    return func_0209c1cc(a, b, 7);
}
