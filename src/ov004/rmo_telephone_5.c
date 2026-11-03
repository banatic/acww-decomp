/* rmo_telephone_5: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022314dc @ 0x022314dc, 0xb4 bytes, Thumb
 * func_ov004_02231454 @ 0x02231454, 0x88 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 *p;
    u8 n;
} Src;

extern char data_ov004_022558e8;
extern char data_ov004_022558d8;
extern char data_ov004_022558e0;
extern int func_020b65c4(void);
extern void func_ov004_0223121c(void *, int);
extern void func_02068bbc(void *);
extern void func_02068bb0(void *);
extern int func_0206837c(int);
extern void func_020ab670(int, int, int);
extern void func_020ab628(int, int, void *, int, void *, int, int);
extern void func_020ab5f8(int);
extern void func_02068388(int, int);
extern char data_021f43f8;

void func_ov004_02231454(char *self, Src *s, int v);

void func_ov004_022314dc(char *self)
{
    char *p = *(char **) (self + 0x2d0);
    switch (*(unsigned char *) (self + 0x2ae)) {
        case 0x1b:
            func_ov004_02231454((char *) self, (Src *) (&data_ov004_022558e8), -1);
            break;
        case 0xe:
        case 0x1f:
            if (func_020b65c4() == 6) {
                func_ov004_02231454((char *) self, (Src *) (&data_ov004_022558d8), 3);
            } else {
                func_ov004_02231454((char *) self, (Src *) (&data_ov004_022558e0), 2);
            }
            break;
        case 0xf:
            *(int *) (p + 0x14) = 1;
            func_ov004_0223121c(self, 0xd);
            break;
        case 0x20:
            func_02068bbc(p + 0x1a2c);
            break;
        case 0x2a:
        case 0x2b:
        case 0x2c:
            func_02068bb0(p + 0x1a2c);
            break;
    }
}

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
