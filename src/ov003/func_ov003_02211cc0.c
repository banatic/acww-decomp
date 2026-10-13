/* func_ov003_02211cc0 @ 0x02211cc0, 0x7c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 x, y, z;
} Vec3;

extern void *func_ov003_02211d3c(void *r0, unsigned char r1, Vec3 *r2);
extern void func_020109a0(void *p, u32 a, u32 b, u32 c);
extern void func_0200f27c(void *p, u32 msg);

void func_ov003_02211cc0(void *self, void *src)
{
    u8 *q;
    u8 b;
    Vec3 tmp;
    Vec3 v;
    void *p;
    u32 val;
    u8 *cp;

    q = (u8 *) src + 0xc;
    b = *(u8 *) ((u8 *) src + 0xc);
    tmp.x = *(u32 *) (q + 4);
    tmp.y = *(u32 *) (q + 8);
    tmp.z = *(u32 *) (q + 0xc);
    cp = (u8 *) &tmp;
    *cp = *cp;
    p = (u8 *) self + 0x7d4;
    v.x = tmp.x;
    v.y = tmp.y;
    v.z = tmp.z;

    func_ov003_02211d3c(p, b, &v);

    val = *(u32 *) ((u8 *) self + 0x704);
    if ((val - 0x49) <= 1) {
        if (*(u8 *) p != 0) {
            func_020109a0(self, 0x4e, 3, 0);
        } else {
            func_020109a0(self, 0x4b, 3, 0);
        }
    } else {
        func_020109a0(self, 0x49, 3, 0);
    }
    func_0200f27c(self, 0x1c);
}
