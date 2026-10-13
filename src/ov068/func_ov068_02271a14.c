/* func_ov068_02271a14 @ 0x02271a14, 0x11c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O1,s
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
