/* insect_paths_7: 2 functions, module ov068
 * mwccarm 1.2/base -O1,s
 * func_ov068_02271a14 @ 0x02271a14, 0x11c bytes, Thumb
 * func_ov068_02271960 @ 0x02271960, 0xb4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} VecFx32;

extern void func_020ea6e0(VecFx32 *v, int ang);
extern int FX_MulFunc(int a, int b);
extern void func_0204f818(int *px, int *pz, VecFx32 *p);
extern int func_02031b5c(int x, int z);
extern int func_ov003_02233c70(int a, int b);
extern int func_020644cc(int a);
extern int func_02091230(int a, VecFx32 *v, s16 *ang, int d);

void func_ov068_02271a14(u8 *self, s16 *buf)
{
    VecFx32 *p;
    VecFx32 *hi;
    VecFx32 *lo;
    int x, z;
    VecFx32 dir;
    volatile VecFx32 old;

    p = (VecFx32 *) (self + 0x204);
    old.x = p->x;
    old.y = p->y;
    old.z = p->z;
    hi = (VecFx32 *) (self + 0x1bc);
    lo = (VecFx32 *) (self + 0x1b0);
    x = 0;
    z = 0;
    dir.x = 0;
    dir.y = 0;
    dir.z = 0x29;
    func_020ea6e0(&dir, *(s16 *) (self + 0x23a));
    p->x += FX_MulFunc((*buf * self[0x257]) << 12, dir.x);
    p->z += FX_MulFunc((*buf * self[0x257]) << 12, dir.z);
    *buf = *buf - 1;
    func_0204f818(&x, &z, p);
    if (func_02031b5c(x, z) == 2 && p->x >= lo->x && p->x <= hi->x && p->z <= lo->z && p->z >= hi->z) {
        goto ok;
    }
    {
        int bias = -0x8000;
        p->x = old.x;
        p->y = old.y;
        p->z = old.z;
        *(s16 *) (self + 0x240) = func_ov003_02233c70(0xc, 1) + bias;
    }
    self[0x251] = 0xf;
    *buf = 0;
    return;
ok:
    if (*buf > 0) {
        return;
    }
    self[0x251] = 0x13;
    *(s16 *) (self + 0x232) = 3 * func_020644cc(0x14);
}

void func_ov068_02271960(u8 *self, s16 *buf)
{
    s16 ang;
    VecFx32 v;
    s16 d;
    s16 a;
    u8 i;
    VecFx32 *p;

    a = *(s16 *) (self + 0x23a);
    ang = a;
    d = 0;
    if (self[0x251] == 0xf) {
        d = a + *(s16 *) (self + 0x240);
    } else {
        for (i = 0; i < func_020644cc(5); i++) {
            d = d + 0xaaa;
        }
        if (func_020644cc(100) > 0x32) {
            d = -d;
        }
        d = d + ang;
    }
    self[0x251] = 4;
    *(s16 *) (self + 0x23a) = d;
    *buf = func_020644cc(8) + 8;
    p = (VecFx32 *) (self + 0x204);
    v.x = p->x;
    v.y = p->y;
    v.z = p->z;
    v.y = v.y + 0x100;
    func_02091230(0x1f, &v, &ang, 0);
}
