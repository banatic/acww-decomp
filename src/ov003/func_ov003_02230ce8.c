/* func_ov003_02230ce8 @ 0x02230ce8, 0x130 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02034270(int *st, int *v, int a, int b);
extern void func_0203423c(int *st);
extern int FX_Div(int a, int b);

void func_ov003_02230ce8(char *self, short a1, u8 a2, int a3, short a5, short a6, int a7, int a8, u8 a9, u8 a10)
{
    int st[16];
    int *p;
    int *q;
    int *d;
    int v;
    int w;

    p = (int *) (self + 0x204);
    func_02034270(st, p, 0, 0);
    q = (int *) (self + 0x210);
    v = FX_Div(a7 << 12, 0x10000);
    w = FX_Div(a3 << 12, 0x10000);
    if (*(u8 *) (self + 0x251) != 0xb && *(u8 *) (self + 0x251) != 0x10) {
        *(u8 *) (self + 0x251) = 0x13;
        *(short *) (self + 0x23a) = a6;
        d = (int *) (self + 0x1d4);
        d[0] = p[0];
        d[1] = p[1];
        d[2] = p[2];
        if (a10 != 0) {
            p[1] = v + st[15];
        } else {
            p[1] = v;
        }
    }
    *(short *) (self + 0x238) = a5;
    *(u8 *) (self + 0x255) = a2;
    *(int *) (self + 0x224) = w;
    if (*(s8 *) (self + 0x24d) != 0x23) {
        *(int *) (self + 0x21c) = 0;
    }
    *(u8 *) (self + 0x257) = a9;
    *(short *) (self + 0x23e) = 0;
    *(u8 *) (self + 0x254) = 0;
    *(int *) (self + 0x228) = p[1] + a8;
    *(short *) (self + 0x244) = a1;
    q[0] = 0x1000;
    q[1] = 0x1000;
    q[2] = 0x1000;
    *(int *) (self + 0x220) = *(int *) (self + 0x228);
    *(short *) (self + 0x236) = 0;
    *(u8 *) (self + 0x24e) = 0;
    func_0203423c(st);
}
