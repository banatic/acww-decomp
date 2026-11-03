/* icon_models_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02233dc0 @ 0x02233dc0, 0x58 bytes, Thumb
 * func_ov004_02233c78 @ 0x02233c78, 0x148 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct Vec3_02233c78 {
    int x, y, z;
} Vec3_02233c78;

extern void *func_0204c63c(void *);
extern int func_ov004_02233e18(void *, void *, Vec3 *, Vec3 *, short, short, short);
extern void *data_021c67a4;
extern Vec3_02233c78 data_021c67d0;
extern int data_021fbe48;
void func_0204f7e0(Vec3_02233c78 *d, const Vec3_02233c78 *s);
int func_0203f8d0(Vec3_02233c78 *d, const Vec3_02233c78 *s);
u16 *func_0204f5a8(void *b, const Vec3_02233c78 *p, int layer);
int func_ov004_0223c5a4(const Vec3_02233c78 *p);
void func_020e96c8(void *g, int x, int y, int z);
void func_020e9774(void *g, int v);

void func_ov004_02233dc0(void *self, unsigned short id, Vec3 *a, Vec3 *b, short p5, short p6, short p7)
{
    volatile unsigned short t = 0xfff1;
    Vec3 va, vb;
    void *r;
    t = id;
    va.x = a->x;
    va.y = a->y;
    va.z = a->z;
    vb.x = b->x;
    vb.y = b->y;
    vb.z = b->z;
    r = func_0204c63c((void *) &t);
    func_ov004_02233e18(self, r, &va, &vb, p5, p6, p7);
}

void func_ov004_02233c78(void *a, void *b)
{
    int n;
    Vec3_02233c78 cur;
    Vec3_02233c78 t;
    Vec3_02233c78 base;
    Vec3_02233c78 org;
    Vec3_02233c78 conv;
    Vec3_02233c78 posA;
    Vec3_02233c78 scale;
    Vec3_02233c78 posB;
    u16 *cell;
    int r;
    int j;
    int i;

    if (data_021c67a4 == 0) {
        return;
    }

    base.x = data_021c67d0.x;
    base.y = data_021c67d0.y;
    base.z = data_021c67d0.z;
    func_0204f7e0(&conv, &base);
    org.x = conv.x + 0x10000;
    org.y = 0;
    org.z = conv.z + 0x10000;

    n = 8;
    for (i = n; i >= -8; i--) {
        func_0204f7e0(&cur, &org);
        r = func_0203f8d0(&t, &cur);
        func_020e96c8(&data_021fbe48, t.x, t.y, t.z);
        func_020e9774(&data_021fbe48, r);
        for (j = n; j >= -8; j--) {
            cell = func_0204f5a8(b, &cur, 0);
            if (cell != 0 && ((*cell & 0xf000) >> 12) == 1) {
                int z = cur.z;
                int y = cur.y + func_ov004_0223c5a4(&cur);
                posA.x = cur.x;
                posA.y = y;
                posA.z = z;
                scale.x = 0x1000;
                scale.y = 0x1000;
                scale.z = 0x1000;
                func_ov004_02233dc0(a, *cell, (Vec3 *) (&posA), (Vec3 *) (&scale), 0, 0, 0);
            }
            cell = func_0204f5a8(b, &cur, 1);
            if (cell != 0 && ((*cell & 0xf000) >> 12) == 1) {
                int z = cur.z;
                int y = cur.y + func_ov004_0223c5a4(&cur);
                posB.x = cur.x;
                posB.y = y;
                posB.z = z;
                scale.x = 0x1000;
                scale.y = 0x1000;
                scale.z = 0x1000;
                func_ov004_02233dc0(a, *cell, (Vec3 *) (&posB), (Vec3 *) (&scale), 0, 0, 0);
            }
            cur.x = cur.x - 0x2000;
        }
        org.z = org.z - 0x2000;
    }
}
