/* func_ov003_02225a90 @ 0x02225a90, 0x94 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

extern Vec3 data_ov003_02236b64[];
extern u16 data_ov003_0223667c[];
extern int func_0204b710(u16 *b);
extern void func_ov003_02225da0(void *a0, int id, Vec3 *va, int k, Vec3 *vb, short s1, short s2, short s3);

void func_ov003_02225a90(void *a0, u16 *b, Vec3 *base)
{
    struct {
        Vec3 a;
        Vec3 b;
    } o;
    Vec3 s;
    int c;
    u16 v;
    int id;
    int i;
    int z;
    c = 0;
    v = *b;
    if (v >= 0x57 && v <= 0x5b) {
        c = 1;
    }
    if (c) {
        id = 0x14b8;
    } else {
        id = data_ov003_0223667c[func_0204b710(b)];
    }
    i = 0;
    z = 0;
    for (; i < 3; i++) {
        Vec3 *e = &data_ov003_02236b64[i];
        o.a.x = base->x + e->x;
        o.a.y = base->y + e->y;
        o.a.z = base->z + e->z;
        o.b.x = o.a.x;
        o.b.y = o.a.y;
        o.b.z = o.a.z;
        s.x = 0x1000;
        s.y = 0x1000;
        s.z = 0x1000;
        func_ov003_02225da0(a0, id, &o.b, 0x1f, &s, z, z, z);
    }
}
