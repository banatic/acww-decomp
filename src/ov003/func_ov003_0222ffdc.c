/* func_ov003_0222ffdc @ 0x0222ffdc, 0xbc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_0222fe18(void *a, void *self, int n);
extern void func_0209d238(void *a, void *b);
extern void func_0209d0a4(void *a);

int func_ov003_0222ffdc(char *a0, char *self)
{
    signed char k;
    u8 s;
    int t[3];
    int u[3];
    short w;
    int *p;

    if (*(u8 *) (self + 0x250) != 0) {
        k = *(signed char *) (self + 0x24d);
        s = *(u8 *) (self + 0x251);
        p = (int *) (self + 0x204);
        t[0] = p[0];
        t[1] = p[1];
        t[2] = p[2];
        p = (int *) (self + 0x1d4);
        u[0] = p[0];
        u[1] = p[1];
        u[2] = p[2];
        w = *(short *) (self + 0x23a);
        func_ov003_0222fe18(a0, self, 3);
        *(signed char *) (self + 0x24d) = k;
        *(u8 *) (self + 0x251) = s;
        p = (int *) (self + 0x204);
        p[0] = t[0];
        p[1] = t[1];
        p[2] = t[2];
        *(short *) (self + 0x23a) = w;
        p = (int *) (self + 0x1d4);
        p[0] = u[0];
        p[1] = u[1];
        p[2] = u[2];
    }
    *(u8 *) (self + 0x250) = 2;
    a0 = a0 + 0x80;
    func_0209d238(a0, self + 0x230);
    func_0209d0a4(self + 0x130);
    *(u8 *) (self + 0x249) = 1;
    return 1;
}
