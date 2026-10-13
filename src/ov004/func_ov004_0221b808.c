/* func_ov004_0221b808 @ 0x0221b808, 0x100 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int w[10];
} T28;
typedef struct {
    int w[8];
} T20;

extern int func_ov004_0221b98c(char *self);
extern void func_02062f90(T28 *t, u16 *h);
extern void func_02062f4c(T28 *t);
extern void func_020683b4(void *a, unsigned int i, T28 *t, int k);
extern void func_ov004_0221b9a0(char *self);
extern void func_02094fd4(T20 *o);
extern void func_02094fbc(T20 *o);
extern void func_02070fe4(void *a, T20 *o, u16 *h);
extern void func_02068404(void *a, int b, T20 *o);
extern int data_021f38f8;

void func_ov004_0221b808(char *self)
{
    // DECLS
    u16 h[2];
    T28 t1;
    T20 o;
    T28 t2;
    unsigned int n;
    unsigned int i;
    // ENDDECLS

    if (func_ov004_0221b98c(self) != 0) {
        return;
    }
    if (*(unsigned int *) (self + 0x15c) <= 1) {
        n = 0;
        switch (*(u8 *) (self + 0x10a)) {
            case 5:
                n = 1;
                break;
            case 6:
                n = 2;
                break;
            case 7:
                n = 3;
                break;
        }
        for (i = 0; i < n; i++) {
            h[0] = (*(u16 **) (self + 0x164))[*(u8 *) (self + 0x155)];
            func_02062f90(&t1, &h[0]);
            func_020683b4(*(void **) (self + 0x12c), i, &t1, 7);
            func_ov004_0221b9a0(self);
            func_02062f4c(&t1);
        }
    } else if (*(u8 *) (self + 0x155) < *(unsigned int *) (self + 0x168)) {
        h[1] = (*(u16 **) (self + 0x164))[*(u8 *) (self + 0x155)];
        func_02094fd4(&o);
        func_02070fe4(&data_021f38f8, &o, &h[1]);
        func_02068404(*(void **) (self + 0x12c), 0, &o);
        func_02062f90(&t2, &h[1]);
        func_020683b4(*(void **) (self + 0x12c), 0, &t2, 7);
        if (*(unsigned int *) (self + 0x15c) != 3) {
            func_ov004_0221b9a0(self);
        }
        func_02062f4c(&t2);
        func_02094fbc(&o);
    }
}
