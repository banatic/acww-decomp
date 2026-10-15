/* func_ov004_02220084 @ 0x02220084, 0x18c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223ce84(void);
extern void *func_ov004_0223cd58(void *a, int b);
extern int func_ov004_0223ba78(int b);
extern int func_ov004_0220fde0(void *p);
extern u16 func_0204bc50(int a, int b);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);

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
