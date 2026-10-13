/* func_0205d3d4 @ 0x0205d3d4, 0x110 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_021c9d1c;

extern void func_0205d58c(void *addr, unsigned char b, unsigned short *out);
extern void func_0205d598(unsigned short *dst, void *addr, unsigned char b);
extern int func_0204bcdc(void *b);
extern int func_0204bc64(void *ptr);
extern int func_0205d528(void *addr, unsigned short *b);
extern void func_0205d270(unsigned char *a, int k);
extern void *func_0205d5a8(void *addr, unsigned char b);
extern int func_0203cfb8(void *x, unsigned short *y, int z);

static __inline int EqA(void *a, void *b)
{
    if (func_0204bc64(a) == func_0204bc64(b)) {
        return 1;
    }
    return 0;
}

static __inline int EqB(u16 a, u16 b)
{
    if (a == b) {
        return 1;
    }
    return 0;
}

void func_0205d3d4(unsigned char *a, unsigned short *b, int c, int d, int e)
{
    unsigned char byte = *a;
    unsigned short local;
    int r4, r2, r1;
    int r;
    int st;

    if (*b == 0xfff1) {
        func_0205d58c(&data_021c9d1c, byte, b);
    }

    r4 = 1;
    r2 = r4;
    r1 = 0;

    if (*b >= 0x12a8 && *b <= 0x12af) {
        r1 = r4;
    }

    if (r1 == 0) {
        if (!(*b >= 0x1429 && *b <= 0x1430)) {
            r2 = 0;
        }
    }

    if (r2 == 0) {
        if (!(*b >= 0x13a0 && *b <= 0x13a7)) {
            r4 = 0;
        }
    }

    if (e == 0 && r4 == 0) {
        func_0205d598(&local, &data_021c9d1c, byte);
        if (func_0204bcdc(b)) {
            r = EqA(b, &local);
        } else {
            r = EqB(*b, local);
        }
        if (r != 0) {
            return;
        }
    }

    if (d != 0 && r4 == 0) {
        st = func_0205d528(&data_021c9d1c, b);
        if (st != 10) {
            func_0205d270(a, st);
            return;
        }
    }

    if (func_0203cfb8(func_0205d5a8(&data_021c9d1c, byte), b, c) != 0) {
        func_0205d58c(&data_021c9d1c, byte, b);
    }
}
