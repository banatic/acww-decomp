/* func_ov004_02231454 @ 0x02231454, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206837c(int);
extern void func_020ab670(int, int, int);
extern void func_020ab628(int, int, void *, int, void *, int, int);
extern void func_020ab5f8(int);
extern void func_02068388(int, int);
extern char data_021f43f8;

typedef struct {
    u8 *p;
    u8 n;
} Src;

void func_ov004_02231454(char *self, Src *s, int v)
{
    int h0 = *(int *) (self + 0x2d0);
    int h = func_0206837c(h0);
    u8 *p = s->p;
    int n = s->n;
    int zero = 0;
    int neg = ~zero;
    int i;
    int j;
    u8 buf;
    if (v != neg) {
        func_020ab670(h, n, v);
    } else {
        func_020ab670(h, n, neg);
    }
    i = 0;
    zero = 0;
    j = i;
    for (; i < n; i++) {
        int f = zero;
        u8 c = p[i];
        if ((u8) (c + 0xec) <= 1) {
            f = 3;
        }
        buf = c;
        func_020ab628(h, i, &buf, 1, &data_021f43f8, j, f);
    }
    func_020ab5f8(h);
    func_02068388(h0, 1);
}
