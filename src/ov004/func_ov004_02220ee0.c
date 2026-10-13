/* func_ov004_02220ee0 @ 0x02220ee0, 0x1e8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_02220318(void *self);
extern int func_020ea990(void *a, void *b);
extern void func_0201b458(void *m, void *self, void *p);
extern int func_02019e00(void *p);
extern void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_0201b044(void *p, void *m);
extern int func_020eaa6c(void *m, void *p);
extern void func_ov004_02221550(void *self, int a);
extern int FX_MulFunc(int a, int b);
extern void func_0204f818(int *x, int *y, int *v);
extern void *func_ov004_0223cd50(void);
extern void *func_ov004_0223cc5c(void *a, int x, int y, int k);
extern int func_ov004_02220084(void *self, int i);
extern void *func_ov004_0223ce84(void);
extern void *func_ov004_0223cd58(void *a, int b);
extern int func_ov004_0220fde0(void *p);
extern u16 func_0204bc50(int a, int b);
extern void func_ov004_0220fefc(void *e, void *dst);
extern void func_ov004_02220018(void *self, void *e);
extern void func_ov004_0222005c(void *self, int i);
extern u16 data_020c80f8;
extern const short FX_SinCosTable_[];

int func_ov004_02220ee0(void *self)
{
    // DECLS
    int d;
    int a;
    int idx;
    void *e;
    int r0;
    int r1;
    // ENDDECLS
    int x;
    int y;
    char m[12];
    int v[3];

    if (func_ov004_02220318(self) != 0) {
        return 1;
    }
    d = func_020ea990((char *) self + 0x5c, (char *) self + 0x89c);
    func_0201b458(m, self, (char *) self + 0x89c);
    if (d > *(int *) ((char *) self + 0xad8) + 0x1000) {
        if (func_02019e00((char *) self + 0x564) == 1) {
            func_02019d0c((char *) self + 0x564, 2, 1, 0, 0, 0x800, 0, 0, 0, data_020c80f8, 0);
        }
    } else {
        if (func_02019e00((char *) self + 0x564) == 2) {
            func_02019d0c((char *) self + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }
    func_0201b044((char *) self + 0x350, m);
    if (d <= *(int *) ((char *) self + 0xad8) || func_020eaa6c(m, (char *) self + 0x5c) != 0) {
        func_ov004_02221550(self, 3);
    }
    v[0] = *(int *) ((char *) self + 0x5c);
    v[1] = *(int *) ((char *) self + 0x60);
    v[2] = *(int *) ((char *) self + 0x64);
    a = *(u16 *) ((char *) self + 0x8e);
    x = 0;
    y = 0;
    idx = (a >> 4) << 1;
    v[0] += FX_MulFunc(0x2000, FX_SinCosTable_[idx]);
    v[2] += FX_MulFunc(0x2000, FX_SinCosTable_[idx + 1]);
    func_0204f818(&x, &y, v);
    r0 = (int) func_ov004_0223cc5c(func_ov004_0223cd50(), x, y, 0);
    r1 = (int) func_ov004_0223cc5c(func_ov004_0223cd50(), x, y, 1);
    if (func_ov004_02220084(self, r1) != 0) {
        e = func_ov004_0223cd58(func_ov004_0223ce84(), r1);
        *(u16 *) ((char *) self + 0x898) = func_0204bc50(func_ov004_0220fde0(e), 0);
        func_ov004_0220fefc(e, (char *) self + 0x89c);
        func_ov004_02220018(self, e);
        func_ov004_0222005c(self, r1);
        *(int *) ((char *) self + 0x8a8) = r1;
    } else if (func_ov004_02220084(self, r0) != 0) {
        e = func_ov004_0223cd58(func_ov004_0223ce84(), r0);
        *(u16 *) ((char *) self + 0x898) = func_0204bc50(func_ov004_0220fde0(e), 0);
        func_ov004_0220fefc(e, (char *) self + 0x89c);
        func_ov004_02220018(self, e);
        func_ov004_0222005c(self, r0);
        *(int *) ((char *) self + 0x8a8) = r0;
    }
    return 1;
}
