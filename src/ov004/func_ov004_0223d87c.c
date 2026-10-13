/* func_ov004_0223d87c @ 0x0223d87c, 0xdc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_020961a8(int);
extern void *data_ov004_02259a14;
extern int func_020644cc(int);
extern int func_020ea990(void *a, void *b);
extern int FX_MulFunc(int a, int b);
extern char *func_ov004_0223d958(void *self);
extern short func_0200322c(void *a, void *b);

void func_ov004_0223d87c(char *self)
{
    char *q = self;
    int zero;
    int t;
    int state;
    u8 k;
    char *o;
    char *r;
    short *m;
    q = self + 0x5c;
    state = 0;
    k = 0;
    zero = 0;
    for (k = 0; k < 2; k++) {
        if (k == 0) {
            o = (char *) func_020961a8(4);
        } else {
            o = (char *) data_ov004_02259a14;
        }
        if (o != 0 && state == 0) {
            char *b = o + 0x5c;
            *(short *) (self + 0x22c) = (short) (*(short *) (self + 0x22c) - 1);
            *(int *) (self + 0x98) = zero;
            if (*(short *) (self + 0x22c) <= 0) {
                *(int *) (self + 0x10c) = 1;
                *(short *) (self + 0x22c) = (short) (0x14 * (func_020644cc(4) + 1));
                state = 1;
            } else if (*(int *) (o + 0x98) > 0) {
                t = func_020ea990(q, b);
                if (t < FX_MulFunc(0x1000, 0x4000)) {
                    *(short *) (self + 0x22c) = (short) (0x14 * (func_020644cc(4) + 2));
                    *(int *) (self + 0x10c) = 1;
                    state = 2;
                }
            }
        }
    }
    if (state == 2) {
        r = func_ov004_0223d958(self);
        if (r != 0) {
            m = (short *) (self + 0x92);
            m[1] = func_0200322c(r + 0x5c, q);
            *(short *) (self + 0x8e) = m[1];
        }
    }
}
