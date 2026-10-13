/* func_ov003_0223126c @ 0x0223126c, 0x1b0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020961a8(int n);
extern int func_ov003_0223141c(void *p);
extern void func_ov003_02234d70(void *self);
extern int func_020ea990(void *a, void *b);
extern void func_02056fcc(void *p, int a, int b, int c, int e);
extern void func_020550e4(void *p, int a);

void func_ov003_0223126c(char *self, u16 *out)
{
    void *t = func_020961a8(4);
    char *s = self + 0x204;
    int d;
    int st;
    u16 v;
    int c;

    if (func_ov003_0223141c(s) == 0) {
        *(u8 *) (self + 0x254) = 0xfe;
    }
    *(u8 *) (self + 0x24a) = 0;
    func_ov003_02234d70(self);
    if (t == 0) {
        return;
    }

    d = func_020ea990((char *) t + 0x5c, s);
    c = *(u8 *) (self + 0x254);
    if (d <= 0xccd) {
        *(u8 *) (self + 0x251) = 9;
        *out = 0;
        return;
    }

    st = *(s8 *) (self + 0x24d);
    if ((u8) (s8) (st - 0xe) <= 1) {
        if (c > 0x14) {
            v = (u16) (*(int *) (self + 0xf4) >> 12);
            func_02056fcc(self + 0xec, 9, 1, 0x1000, v);
            *(u8 *) (self + 0x252) = 0x3c;
            return;
        }
        if (*(u8 *) (self + 0x252) != 0) {
            *(u8 *) (self + 0x252) = *(u8 *) (self + 0x252) - 1;
            return;
        }
        if (d < *(int *) (self + 0x224)) {
            v = (u16) (*(int *) (self + 0xf4) >> 12);
            if (v == 0) {
                func_02056fcc(self + 0xec, 4, 1, 0x1000, 0);
                return;
            }
            if (v > 4) {
                func_02056fcc(self + 0xec, 4, 3, 0x1000, v);
            }
            return;
        }
        v = (u16) (*(int *) (self + 0xf4) >> 12);
        if (v != 0) {
            func_02056fcc(self + 0xec, 0, 3, 0x1000, v);
        }
        return;
    }
    if (st != 0x1a) {
        return;
    }
    if (c > 0x14) {
        v = (u16) (*(int *) (self + 0xf4) >> 12);
        if (v == 2) {
            func_020550e4(self + 0x50, 1);
            return;
        }
        if (v != 1) {
            return;
        }
        func_020550e4(self + 0x50, 0);
        *(u8 *) (self + 0x251) = 0x13;
        *(u8 *) (self + 0x252) = 0x3c;
        return;
    }
    {
        int w = *(int *) (self + 0xf4) >> 12;
        if ((u16) w == 0 && *(u8 *) (self + 0x252) == 0) {
            func_020550e4(self + 0x50, 1);
            return;
        }
        if ((u16) w == 1) {
            func_020550e4(self + 0x50, 2);
            return;
        }
        if (*(u8 *) (self + 0x252) != 0) {
            *(u8 *) (self + 0x252) = *(u8 *) (self + 0x252) - 1;
        }
    }
}
