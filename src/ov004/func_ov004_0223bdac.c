/* func_ov004_0223bdac @ 0x0223bdac, 0x194 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Vec3 {
    int x;
    int y;
    int z;
};

extern void *func_020961a8(int k);
extern void *func_ov004_0223ce84(void);
extern void *func_ov004_0223cd58(void *a, unsigned int i);
extern unsigned int func_ov004_0223c130(void);
extern int func_ov004_022112c4(void *e);
extern int func_01ffd028(struct Vec3 *a, struct Vec3 *b);
extern void func_ov004_02215d74(void *e);
extern void *func_ov004_0223b2cc(void);
extern int func_ov004_0223b28c(void);
extern int func_ov004_0223b2ac(void);
extern int func_ov004_0223b258(void);
extern int func_ov004_0223b2ec(void);
extern void func_02003e00(void *a);
extern void func_02003e10(void *a, int b);
extern void func_02003e20(void *a, int b, struct Vec3 *c);
extern u8 data_ov004_022595b8;
extern struct Vec3 data_021fbee8;
extern int data_ov004_022595d8;

void func_ov004_0223bdac(void *self)
{
    // DECLS
    int best;
    void *e;
    void *p;
    void *w;
    struct Vec3 *q;
    unsigned int i;
    unsigned int bi;
    int d;
    int n;
    // ENDDECLS
    struct Vec3 out;
    struct Vec3 base;
    struct Vec3 tmp;
    struct Vec3 c1;
    struct Vec3 c2;
    int flag;

    if (data_ov004_022595b8 == 0) {
        return;
    }
    flag = 1;
    out.x = data_021fbee8.x;
    out.y = data_021fbee8.y;
    out.z = data_021fbee8.z;
    p = func_020961a8(4);
    if (p != 0) {
        q = (struct Vec3 *) ((char *) p + 0x5c);
        base.x = q->x;
        base.y = q->y;
        base.z = q->z;
        bi = ~0;
        best = data_ov004_022595d8;
        for (i = 0; i < func_ov004_0223c130(); i++) {
            e = func_ov004_0223cd58(func_ov004_0223ce84(), i);
            if (e == 0) {
                continue;
            }
            if (func_ov004_022112c4(e) == 0) {
                continue;
            }
            c1 = *(struct Vec3 *) ((char *) e + 0x7b8);
            tmp.x = c1.x;
            tmp.y = c1.y;
            tmp.z = c1.z;
            d = func_01ffd028(&tmp, &base);
            if (d < best) {
                bi = i;
                best = d;
            }
        }
        if (bi != ~0) {
            e = func_ov004_0223cd58(func_ov004_0223ce84(), bi);
            if (e != 0) {
                func_ov004_02215d74(e);
                c2 = *(struct Vec3 *) ((char *) e + 0x7b8);
                out.x = c2.x;
                out.y = c2.y;
                out.z = c2.z;
                flag = 0;
            }
        }
    }
    w = func_ov004_0223b2cc();
    if (w != 0) {
        if (flag != 0) {
            if (*(u8 *) ((char *) self + 0x2a9) == 0 || *(u8 *) ((char *) self + 0x2a8) == 0) {
                func_02003e00(w);
                *(u8 *) ((char *) self + 0x2a8) = 1;
            }
            func_02003e20(w, func_ov004_0223b28c(), 0);
        } else {
            if (*(u8 *) ((char *) self + 0x2a9) != 0 || *(u8 *) ((char *) self + 0x2a8) == 0 ||
                *(int *) ((char *) self + 0x2ac) != func_ov004_0223b2ec()) {
                n = func_ov004_0223b28c() - 1;
                if (n < 0) {
                    n = 0;
                }
                if (func_ov004_0223b2ac() == 0 && n == 0 && func_ov004_0223b258() != 0) {
                    d = 1;
                } else {
                    d = 0;
                }
                func_02003e10(w, d);
                *(u8 *) ((char *) self + 0x2a8) = 1;
            }
            func_02003e20(w, func_ov004_0223b28c(), &out);
        }
    }
    *(u8 *) ((char *) self + 0x2a9) = (u8) flag;
    *(int *) ((char *) self + 0x2ac) = func_ov004_0223b2ec();
}
