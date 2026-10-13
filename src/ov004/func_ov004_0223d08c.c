/* func_ov004_0223d08c @ 0x0223d08c, 0x174 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02061b1c(void *p, u16 *item, int k);
extern unsigned int func_0204bd5c(void *p);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern void func_020ee470(void *o);
extern int func_ov004_0223b540(int *out, void *p, int k);
extern int func_ov004_0223c660(int a);

static __inline int same(u16 *p, u16 *q)
{
    int t1;

    if (func_0204bcdc((void *) p) != 0) {
        t1 = func_0204bc64((void *) p);
        return (t1 == func_0204bc64((void *) q)) ? 1 : 0;
    }
    return (*p == *q) ? 1 : 0;
}

int func_ov004_0223d08c(void *self, u16 *item)
{
    // DECLS
    unsigned int f;
    unsigned int lo;
    unsigned int hi;
    unsigned int g;
    unsigned int iid;
    unsigned int n;
    unsigned int k;
    unsigned int m;
    u16 *q;
    int *p;
    void *o;
    // ENDDECLS
    volatile u16 id;
    int out;

    func_02061b1c((void *) &id, item, 1);
    f = 0;
    lo = id;
    hi = id;
    if (hi >= 0x1100 && lo <= 0x1143) {
        f = 1;
    }
    if (f != 0) {
        g = 0;
        iid = *item;
        if (iid >= 0x1100 && iid <= 0x1143) {
            g = 1;
        }
        *(int *) ((char *) self + 0x10) = g ? (int) (iid - 0x1100) : -1;
        id = 0x4a64;
    } else if (lo >= 0x1144 && lo <= 0x1187) {
        g = 0;
        iid = *item;
        if (iid >= 0x1144 && iid <= 0x1187) {
            g = 1;
        }
        *(int *) ((char *) self + 0x10) = g ? (int) (iid - 0x1144) : -1;
        id = 0x4a60;
    } else if (lo >= 0x1000 && lo <= 0x10ff) {
        n = func_0204bd5c((void *) &id);
        id = (n < 0x40) ? (0x4a68 + n * 4) : 0x4a68;
    }
    k = *(u8 *) ((char *) self + 0xc) & 1;
    q = (u16 *) ((char *) self + 8) + k;
    if (same(item, q) == 0) {
        o = *(void **) ((char *) self + (*(u8 *) ((char *) self + 0xc) & 1) * 4);
        if (o != 0) {
            func_020ee470(o);
            *(void **) ((char *) self + (*(u8 *) ((char *) self + 0xc) & 1) * 4) = 0;
        }
        m = (u8) ((*(u8 *) ((char *) self + 0xc) + 1) & 1);
        p = (int *) ((char *) self + m * 4);
        if (*(int *) ((char *) self + m * 4) == 0) {
            if (func_ov004_0223b540(&out, (void *) &id, 2) == 3) {
                *p = func_ov004_0223c660(out);
                *(u16 *) ((char *) self + m * 2 + 8) = *item;
                *(u8 *) ((char *) self + 0xc) = (u8) m;
                return 1;
            }
        }
    }
    return 0;
}
