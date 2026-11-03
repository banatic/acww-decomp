/* flea_market_buyer: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02220084 @ 0x02220084, 0x18c bytes, Thumb
 * func_ov004_0222005c @ 0x0222005c, 0x28 bytes, Thumb
 * func_ov004_02220018 @ 0x02220018, 0x44 bytes, Thumb
 * func_ov004_0221ffec @ 0x0221ffec, 0x2c bytes, Thumb
 * func_ov004_0221ffc4 @ 0x0221ffc4, 0x28 bytes, Thumb
 */

#include "types.h"

extern void *func_ov004_0223ce84(void);
extern void *func_ov004_0223cd58(void *a, int b);
extern int func_ov004_0223ba78(int b);
extern int func_ov004_0220fde0(void *p);
extern u16 func_0204bc50(int a, int b);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern int func_02053be0(int);
extern void *func_ov004_02220d24(void *);
extern void *func_0202e5e0(void *);
extern void func_020edf54(void *);
extern char data_ov004_02253e10[];

static __inline int chk(volatile u16 *p, u16 k)
{
    u16 t;
    int t1;

    if (func_0204bcdc((void *) p) != 0) {
        t = k;
        t1 = func_0204bc64((void *) p);
        return (t1 == func_0204bc64((void *) &t)) ? 1 : 0;
    }
    return (*p == k) ? 1 : 0;
}

int func_ov004_02220084(void *self, int arg)
{
    // DECLS
    unsigned int f;
    unsigned int lo;
    unsigned int hi;
    int i;
    void *e;
    // ENDDECLS
    volatile u16 id;

    e = func_ov004_0223cd58(func_ov004_0223ce84(), arg);
    if (e == 0) {
        return 0;
    }
    if (func_ov004_0223ba78(arg) == 0) {
        return 0;
    }
    id = func_0204bc50(func_ov004_0220fde0(e), 0);
    f = 0;
    lo = id;
    hi = id;
    if (hi >= 0x3d84 && lo <= 0x3e03) {
        f = 1;
    }
    if (f != 0 || (lo >= 0x3ea4 && lo <= 0x3f23) || (lo >= 0x4224 && lo <= 0x42a3) || (lo >= 0x3f24 && lo <= 0x3fa3) ||
        chk(&id, 0x409c) || chk(&id, 0x40a0) || chk(&id, 0x3820)) {
        return 0;
    }
    for (i = 0; i < 0x64; i++) {
        if (arg == *((u8 *) self + i + 0x8ac)) {
            return 0;
        }
    }
    return 1;
}

void func_ov004_0222005c(u8 *self, u8 v)
{
    int i = 0;
    do {
        int j = i + 1;
        *(self + i + 0x8ac) = *(self + j + 0x8ac);
        i = j;
    } while (i < 0x63);
    *(self + 0x90f) = v;
}

void func_ov004_02220018(u8 *self, void *a)
{
    switch (func_02053be0((int) func_ov004_0220fde0(a))) {
        case 0:
            *(int *) (self + 0xad8) = 0x3000;
            break;
        case 1:
            *(int *) (self + 0xad8) = 0x4000;
            break;
        case 2:
            *(int *) (self + 0xad8) = 0x4000;
            break;
    }
}

void *func_ov004_0221ffec(void *s)
{
    *(void **) s = &data_ov004_02253e10;
    func_ov004_02220d24((char *) s + 0x918);
    func_0202e5e0(s);
    func_020edf54(s);
    return s;
}

void *func_ov004_0221ffc4(char *self)
{
    *(const void **) self = ((void *const *) data_ov004_02253e10);
    func_ov004_02220d24(self + 0x918);
    func_0202e5e0(self);
    return self;
}
