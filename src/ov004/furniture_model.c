/* furniture_model: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220e220 @ 0x0220e220, 0x4 bytes, Thumb
 * func_ov004_0220e208 @ 0x0220e208, 0x18 bytes, Thumb
 * func_ov004_0220e1a0 @ 0x0220e1a0, 0x66 bytes, Thumb
 * func_ov004_0220e080 @ 0x0220e080, 0x120 bytes, Thumb
 * func_ov004_0220e068 @ 0x0220e068, 0x18 bytes, Thumb
 * func_ov004_0220e050 @ 0x0220e050, 0x18 bytes, Thumb
 * func_ov004_0220e028 @ 0x0220e028, 0x28 bytes, Thumb
 */

#include "types.h"

extern void func_020e9898(int);
extern int func_ov004_0220e448(void *self);
extern u16 func_0204bc50(void *b, int a);
extern int func_ov004_0220e224(void *self, void *a, void *b);
extern void *func_021077e8(int a);
extern int func_0209d320(void *a);
extern int func_0209d324(void *a);
extern int func_02056064(void *p, int a);
extern int func_020561cc(void *p, int a);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(void *p);
extern int func_02055954(void *p, void *a, int b, int c);
extern int func_0205594c(void *p);
extern void func_02055aac(void *);

int func_ov004_0220e028(char *self);

void *func_ov004_0220e220(void *p)
{
    return (char *) p + 0x44;
}

int func_ov004_0220e208(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self) != 0x0) {
        func_020e9898(*(int *) (self));
        *(void **) (self) = 0x0;
        return 0x0;
    }
    return *(int *) (self);
}

int func_ov004_0220e1a0(char *self, void *a, void *b, int d)
{
    void *h;

    *(u8 *) (self + 0x72) = (u8) d;
    if (func_ov004_0220e448(self)) {
        return 1;
    }
    *(u16 *) (self + 0x70) = func_0204bc50(b, 0);
    func_ov004_0220e224(self, a, b);
    h = func_021077e8(*(int *) self);
    func_02056064(h, func_0209d320(a));
    *(int *) (self + 0xc) = func_020561cc(h, func_0209d324(a));
    func_ov004_0220e028((char *) self);
    return 1;
}

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
        *(u16 *) ((char *) self + 0x70) = func_0204bc50((void *) a2, 0);
        *(u8 *) ((char *) self + 0x72) = (u8) a3;
    } else {
        id = func_0204bc50((void *) a2, 0);
        if (same(&id, (u16 *) ((char *) self + 0x70)) == 0) {
            return 0;
        }
    }
    func_ov004_0220e224(self, a1, (void *) a2);
    if (*(int *) ((char *) self + 0xc) == 0) {
        b = func_021077e8((int) (*(void **) self));
        c = func_0209d320(a1);
        d = func_0209d324(a1);
        if (func_02055954((char *) self + 0x10, b, c, d) == 3) {
            *(int *) ((char *) self + 0xc) = func_0205594c((char *) self + 0x10);
            func_ov004_0220e028((char *) self);
            return 1;
        }
    }
    return 0;
}

int func_ov004_0220e068(char *self)
{
    if (func_ov004_0220e448((void *) self)) {
        return *(int *) (self + 8);
    }
    return 0;
}

int func_ov004_0220e050(char *self)
{
    if (func_ov004_0220e448((void *) self)) {
        return *(int *) (self + 0xc);
    }
    return 0;
}

int func_ov004_0220e028(char *self)
{
    // DECLS
    // ENDDECLS
    *(u16 *) (self + 0x70) = 0xfff1;
    func_ov004_0220e208((char *) self);
    func_02055aac(self + 0x10);
    *(u8 *) (self + 0x72) = 0x0;
    return 0x0;
}
