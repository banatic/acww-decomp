/* func_ov004_02220210 @ 0x02220210, 0x108 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern u16 func_0204bc50(int a, int b);
extern int func_020644cc(int n);
extern int func_ov004_02220084(void *self, int i);
extern void *func_ov004_0223ce84(void);
extern void *func_ov004_0223cd58(void *a, int b);
extern int func_ov004_0220fde0(void *p);
extern void func_ov004_0220fefc(void *e, void *dst);
extern void func_ov004_02220018(void *self, void *e);
extern void func_ov004_0222005c(void *self, int i);

static __inline int chk(u16 *p, u16 k)
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

int func_ov004_02220210(void *self)
{
    // DECLS
    int start;
    int i;
    void *e;
    int n;
    // ENDDECLS

    if (chk((u16 *) ((char *) self + 0x898), 0xfff1) == 0) {
        return 1;
    }
    n = *(int *) ((char *) self + 0xae4);
    if (n == 0 || *(u8 *) ((char *) self + 0xae0) >= 3) {
        if (*(int *) ((char *) self + 0xacc) == 0) {
            *(int *) ((char *) self + 0xacc) = 0x258;
        }
        return 0;
    }
    start = func_020644cc(n);
    i = start;
    do {
        if (func_ov004_02220084(self, i) != 0) {
            e = func_ov004_0223cd58(func_ov004_0223ce84(), i);
            *(u16 *) ((char *) self + 0x898) = func_0204bc50(func_ov004_0220fde0(e), 0);
            func_ov004_0220fefc(e, (char *) self + 0x89c);
            func_ov004_02220018(self, e);
            func_ov004_0222005c(self, i);
            *(int *) ((char *) self + 0x8a8) = i;
            goto ok;
        }
        i++;
        if (i >= *(int *) ((char *) self + 0xae4)) {
            i = 0;
        }
    } while (i != start);
    if (*(int *) ((char *) self + 0xacc) == 0) {
        *(int *) ((char *) self + 0xacc) = 0x258;
    }
    return 0;
ok:
    return 1;
}
