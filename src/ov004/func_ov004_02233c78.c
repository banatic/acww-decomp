/* func_ov004_02233c78 @ 0x02233c78, 0x148 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Vec3 {
    int x, y, z;
} Vec3;

extern void *data_021c67a4;
extern Vec3 data_021c67d0;
extern int data_021fbe48;

void func_0204f7e0(Vec3 *d, const Vec3 *s);
int func_0203f8d0(Vec3 *d, const Vec3 *s);
u16 *func_0204f5a8(void *b, const Vec3 *p, int layer);
int func_ov004_0223c5a4(const Vec3 *p);
void func_ov004_02233dc0(void *a, int kind, Vec3 *pos, Vec3 *scale, int p5, int p6, int p7);
void func_020e96c8(void *g, int x, int y, int z);
void func_020e9774(void *g, int v);

void func_ov004_02233c78(void *a, void *b)
{
    int n;
    Vec3 cur;
    Vec3 t;
    Vec3 base;
    Vec3 org;
    Vec3 conv;
    Vec3 posA;
    Vec3 scale;
    Vec3 posB;
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
                func_ov004_02233dc0(a, *cell, &posA, &scale, 0, 0, 0);
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
                func_ov004_02233dc0(a, *cell, &posB, &scale, 0, 0, 0);
            }
            cur.x = cur.x - 0x2000;
        }
        org.z = org.z - 0x2000;
    }
}
