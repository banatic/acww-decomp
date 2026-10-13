/* func_ov003_0220d2d0 @ 0x0220d2d0, 0x140 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} VecFx32;

extern int func_ov003_0222a938(void *o);
extern VecFx32 *func_ov003_0222a918(void *o);
extern int func_020e8ed8(int a, int b);
extern int func_020ea990(VecFx32 *a, VecFx32 *b);
extern void func_02095518(int a, int b, void *o);
extern void func_02011404(void *p, int a, int b, int c, int d);
extern int func_02008258(u8 *self, int a);
extern void func_0200c9a8(u8 *self, int a, int b, int c);
extern void func_0200d4e8(u8 *self, int a, int b, int c);

void func_ov003_0220d2d0(u8 *self)
{
    VecFx32 a;
    VecFx32 b;
    u8 *p;
    void *o;
    VecFx32 *v;
    VecFx32 *w;
    int ang;
    int e;
    int d;
    u16 t;

    p = self + 0x7d4;
    if (*p == 0) {
        return;
    }
    o = *(void **) (self + 0x800);
    if (func_ov003_0222a938(o) != 0) {
        v = func_ov003_0222a918(o);
        a.x = v->x;
        a.y = v->y;
        a.z = v->z;
        w = (VecFx32 *) (self + 0x5c);
        b.x = w->x;
        b.y = w->y;
        b.z = w->z;
        b.y = b.y + 0x1b33;
        ang = func_020e8ed8(a.x - b.x, a.z - b.z);
        d = func_020ea990(&a, &b);
        e = func_020e8ed8(a.y - b.y, d);
        if (e >= 0x1800) {
            e = 0x1800;
        } else if (e <= -0x1000) {
            e = -0x1000;
        }
        ang = (s16) (ang - *(s16 *) (self + 0x8e));
        t = (u16) (ang + 0x2aaa);
        if (t >= 0x5554) {
            func_02095518(0, 0, *(void **) (self + 0x800));
        } else {
            func_02011404(self + 0x45c, e, 0x400, 0x1770000, 0xc0000);
            func_02011404(self + 0x45e, ang, 0x400, 0x1770000, 0xc0000);
        }
    } else {
        func_02095518(0, 0, *(void **) (self + 0x800));
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
        if (p[1] != 0) {
            func_0200c9a8(self, 3, 5, -1);
        } else {
            func_0200d4e8(self, 3, 1, -1);
        }
    }
}
