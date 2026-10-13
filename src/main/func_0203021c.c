/* func_0203021c @ 0x0203021c, 0x106 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct UnkStruct_0203021c {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
} UnkStruct_0203021c;

extern void func_020eaca0(VecFx32 *o, const VecFx32 *a, const VecFx32 *b);
extern int func_020ea838(const VecFx32 *v);
extern fx32 FX_Div(fx32 n, fx32 d);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern int func_020306a4(UnkStruct_0203021c *s, VecFx32 *v);

static __inline void VEC_Set(VecFx32 *p, fx32 x, fx32 y, fx32 z)
{
    p->x = x;
    p->y = y;
    p->z = z;
}

int func_0203021c(UnkStruct_0203021c *p0, VecFx32 *p1, const VecFx32 *p2)
{
    fx32 d;
    fx32 d2;
    VecFx32 a;
    VecFx32 b;
    VecFx32 v;
    VecFx32 w;
    VecFx32 w2;
    fx32 t;
    fx32 lim;

    VEC_Set(&a, p2->x, p2->y, p2->z);
    VEC_Set(&b, p1->x, p1->y, p1->z);
    func_020eaca0(&v, &b, &a);
    if (func_020ea838(&v)) {
        t = (v.y < 0) ? -v.y : v.y;
        if (t >= 4) {
            lim = p0->unk_04 + p0->unk_10;
            if (a.y > lim && b.y < lim) {
                d = FX_Div(lim - a.y, v.y);
                VEC_Set(&w, a.x + FX_MulFunc(v.x, d), a.y + FX_MulFunc(v.y, d), a.z + FX_MulFunc(v.z, d));
                if (func_020306a4(p0, &w)) {
                    p1->x = w.x;
                    p1->y = w.y;
                    p1->z = w.z;
                    return 1;
                }
            } else if (a.y < 0 && b.y > 0) {
                d2 = FX_Div(-a.y, v.y);
                VEC_Set(&w2, a.x + FX_MulFunc(v.x, d2), a.y + FX_MulFunc(v.y, d2), a.z + FX_MulFunc(v.z, d2));
                if (func_020306a4(p0, &w2)) {
                    p1->x = w2.x;
                    p1->y = w2.y;
                    p1->z = w2.z;
                    return 1;
                }
            }
        }
    }
    return 0;
}
