/* dropped_items_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022335b8 @ 0x022335b8, 0x74 bytes, Thumb
 * func_ov004_0223356c @ 0x0223356c, 0x4c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_022335b8;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int a, b;
} UnkStruct_0223356c;

extern void func_0204f794(int *, int, int);
extern int func_ov004_0223c5b8(int, int);
extern int func_ov004_0223362c(void *, void *, int *, UnkStruct_022335b8 *, UnkStruct_022335b8 *, int, int, int, int);
extern int data_ov004_02258af4;

int func_ov004_022335b8(void *p0, int p1, int *p2, int *p3, u8 p5)
{
    int d[2];
    int a[3];
    UnkStruct_022335b8 b, c;
    func_0204f794(a, p2[0], p2[1]);
    if (p5 != 0) {
        a[1] = func_ov004_0223c5b8(p2[0], p2[1]);
    }
    b.x = p3[0];
    b.y = p3[1];
    b.z = p3[2];
    c.x = a[0];
    c.y = a[1];
    c.z = a[2];
    d[0] = p2[0];
    d[1] = p2[1];
    return func_ov004_0223362c(&data_ov004_02258af4, p0, d, &b, &c, 0, p1, 0, p5);
}

int func_ov004_0223356c(void *self, void *p2, Vec3 *a, Vec3 *b, u8 p5)
{
    UnkStruct_0223356c p;
    Vec3 v1, v2;
    v1.x = a->x;
    v1.y = a->y;
    v1.z = a->z;
    v2.x = b->x;
    v2.y = b->y;
    v2.z = b->z;
    p.a = 0;
    p.b = 0;
    return func_ov004_0223362c(((char *) &data_ov004_02258af4), self, (int *) (&p), (UnkStruct_022335b8 *) (&v1), (UnkStruct_022335b8 *) (&v2), 0, (int) p2, 0, (u8) p5);
}
