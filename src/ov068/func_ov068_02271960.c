/* func_ov068_02271960 @ 0x02271960, 0xb4 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} VecFx32;

extern int func_020644cc(int a);
extern void func_02091230(int a, VecFx32 *v, s16 *ang, int d);

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
