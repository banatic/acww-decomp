/* func_ov004_0220e080 @ 0x0220e080, 0x120 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern u16 func_0204bc50(int a, int b);
extern int func_ov004_0220e448(void *self);
extern int func_ov004_0220e224(void *self, void *a, int b);
extern void *func_021077e8(void *p);
extern int func_0209d320(void *a);
extern int func_0209d324(void *a);
extern int func_02055954(void *p, void *a, int b, int c);
extern int func_0205594c(void *p);
extern int func_ov004_0220e028(void *self);

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

static __inline int same(u16 *p, u16 *q)
{
    int t1;

    if (func_0204bcdc((void *) p) != 0) {
        t1 = func_0204bc64((void *) p);
        return (t1 == func_0204bc64((void *) q)) ? 1 : 0;
    }
    return (*p == *q) ? 1 : 0;
}

int func_ov004_0220e080(void *self, void *a1, int a2, int a3)
{
    // DECLS
    void *b;
    int c;
    int d;
    // ENDDECLS
    u16 id;

    if (func_ov004_0220e448(self) != 0) {
        return 1;
    }
    if (chk((u16 *) ((char *) self + 0x70), 0xfff1) != 0) {
        *(u16 *) ((char *) self + 0x70) = func_0204bc50(a2, 0);
        *(u8 *) ((char *) self + 0x72) = (u8) a3;
    } else {
        id = func_0204bc50(a2, 0);
        if (same(&id, (u16 *) ((char *) self + 0x70)) == 0) {
            return 0;
        }
    }
    func_ov004_0220e224(self, a1, a2);
    if (*(int *) ((char *) self + 0xc) == 0) {
        b = func_021077e8(*(void **) self);
        c = func_0209d320(a1);
        d = func_0209d324(a1);
        if (func_02055954((char *) self + 0x10, b, c, d) == 3) {
            *(int *) ((char *) self + 0xc) = func_0205594c((char *) self + 0x10);
            func_ov004_0220e028(self);
            return 1;
        }
    }
    return 0;
}
