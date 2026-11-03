/* town_spawn: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02047fac @ 0x02047fac, 0x54 bytes, Thumb
 * func_02047ee8 @ 0x02047ee8, 0xc4 bytes, Thumb
 * func_02047e54 @ 0x02047e54, 0x94 bytes, Thumb
 */

#include "types.h"

extern struct {
    unsigned char pad[0x30];
    unsigned int : 4;
    signed int bit : 1;
} data_021c79c4;
extern int func_020644cc(int);
extern int func_02048cb8(int a, int b, int c, int d, int e, int (*predicate)(int, int, int), int g);
extern int func_02048e4c(int, int, int);
extern void func_02063414(volatile u16 *, int, int, int, int, int, int, int, int, int);
extern int func_02048e54(void *, int, int);
extern int func_020ba4d4(void);
extern unsigned short *func_0204f5e0(int, int, int, int, int, int);
extern int func_0204f2b8(int, int, int, int, int);
extern void func_0204a200(int, int, int, int, int, int, int, int);

void func_02047fac(int a, int b, int c)
{
    int tmp;

    if (data_021c79c4.bit) {
        return;
    }
    if (func_020644cc(100) >= 10) {
        return;
    }
    tmp = func_020644cc(c) + 1;
    func_02048cb8(a, b, tmp, 4, 0x1548, (((int (*)(int, int, int)) func_02048e4c)), 0);
}

void func_02047ee8(int a, int b, int nx, int ny, u8 flag)
{
    volatile u16 w[2];
    int z;
    int cx;
    int cy;
    int i;
    int m;

    if (flag == 0) {
        return;
    }
    m = func_020ba4d4();
    if (m != 0 && m != 1 && m != 2) {
        return;
    }
    w[0] = 0xfff1;
    cx = func_020644cc(nx - 1);
    cy = func_020644cc(ny - 1);
    z = 0;
    for (i = 0; i < 3; i++) {
        func_02063414(&w[1], 0x45dc, 0x7f, z, z, z, 1, 0xa, z, 1);
        w[0] = w[1];
        cx = (cx + 1 + func_020644cc(nx - 1)) % nx;
        cy = (cy + 1 + func_020644cc(ny - 1)) % ny;
        func_02048cb8(a, b, cx + 1, cy + 1, w[0], (((int (*)(int, int, int)) func_02048e54)), 1);
    }
}

void func_02047e54(int p0, int p1, int p2, int p3)
{
    volatile int start = 1;
    volatile int something = 1;
    int r5, r6, r4, r7;
    unsigned short *p;

    for (r5 = 1; r5 < p3 + 1; r5++) {
        for (r6 = start; r6 < p2 + 1; r6++) {
            for (r4 = 0; r4 < 16; r4++) {
                for (r7 = 0; r7 < 16; r7++) {
                    if ((p = func_0204f5e0(p1, r6, r5, r7, r4, 0)) != 0) {
                        if (*p == 0x1369) {
                            if (func_0204f2b8(p1, r6, r5, r7, r4) != 0) {
                                func_0204a200(p0, p1, r6, r5, r7, r4, 0x136a, something);
                            }
                        }
                    }
                }
            }
        }
    }
}
