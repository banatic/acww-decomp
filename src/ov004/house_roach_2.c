/* house_roach_2: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223d958 @ 0x0223d958, 0x6c bytes, Thumb
 * func_ov004_0223d87c @ 0x0223d87c, 0xdc bytes, Thumb
 * func_ov004_0223d82c @ 0x0223d82c, 0x50 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0223d958 {
    int x;
    int y;
    int z;
};

extern void *func_020961a8(int);
extern void *data_ov004_02259a14;
extern int func_020644cc(int);
extern int func_020ea990(void *a, void *b);
extern int FX_MulFunc(int a, int b);
extern short func_0200322c(void *a, void *b);
extern void func_02089b80(void *, void *, void *, int, int, int, int, int, int, int);
extern void func_02089fc8(void *);

void *func_ov004_0223d958(char *self)
{
    // DECLS
    int dz;
    char *g;
    int ex;
    int dx;
    void *n;
    int ez;
    struct UnkStruct_0223d958 *pn;
    struct UnkStruct_0223d958 *pg;
    struct UnkStruct_0223d958 *ps;
    // ENDDECLS
    n = func_020961a8(4);
    g = (char *) data_ov004_02259a14;
    if (g == 0) {
        return n;
    }
    if (n != 0) {
        ps = (struct UnkStruct_0223d958 *) (self + 0x5c);
        pn = (struct UnkStruct_0223d958 *) ((char *) n + 0x5c);
        pg = (struct UnkStruct_0223d958 *) (g + 0x5c);
        dx = ps->x - pn->x;
        if (dx < 0) {
            dx = -dx;
        }
        dz = ps->z - pn->z;
        if (dz < 0) {
            dz = -dz;
        }
        ex = ps->x - pg->x;
        if (ex < 0) {
            ex = -ex;
        }
        ez = ps->z - pg->z;
        if (ez < 0) {
            ez = -ez;
        }
        if (dx + dz <= ex + ez) {
            return n;
        }
    }
    return g;
}

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
        r = (char *) func_ov004_0223d958((char *) self);
        if (r != 0) {
            m = (short *) (self + 0x92);
            m[1] = func_0200322c(r + 0x5c, q);
            *(short *) (self + 0x8e) = m[1];
        }
    }
}

void func_ov004_0223d82c(char *self)
{
    // DECLS
    // ENDDECLS
    func_02089b80(self + 0x1d8, self, self + 0x5c, 0x19a, 0x333, 0x81, 0xc, 0x0, 0xff, 0x1000);
    func_02089fc8(self + 0x1d8);
}
