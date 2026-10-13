/* func_ov068_022701b0 @ 0x022701b0, 0x178 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern int func_ov003_02234984(u8 *self);
extern int func_ov068_02270070(u8 *self, s16 *a, int *b, VecFx32 *v);
extern int FX_Div(int a, int b);
extern int func_020644cc(int a);
extern void func_ov003_02230f88(u8 *self);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *dst);
extern void func_ov003_022321b8(VecFx32 *a, VecFx32 *b, int c);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *dst);

int func_ov068_022701b0(u8 *self, s16 *buf)
{
    s16 da;
    int db;
    VecFx32 v;
    int ok;
    VecFx32 *p;
    VecFx32 *q;
    int lim;

    ok = func_ov003_02234984(self);
    p = (VecFx32 *) (self + 0x204);

    if (func_ov068_02270070(self, &da, &db, &v) == 0) {
        goto zero;
    }
    if (ok == 0) {
        goto one;
    }

    if (db <= FX_Div(0x1000, 0x4000) && p->y <= v.y + FX_Div(0x1000, 0x8000) && p->y >= v.y - FX_Div(0x1000, 0x8000)) {
        self[0x251] = 6;
        *(s16 *) (self + 0x244) = 0x14 * (func_020644cc(5) + 0x10);
        *(s16 *) (self + 0x242) = 0;
        if (*(s8 *) (self + 0x24d) == 0x33) {
            if (*(int *) (self + 0x21c) != 1) {
                self[0x251] = 0;
            } else {
                func_ov003_02230f88(self);
            }
        }
    } else {
        lim = self[0x252];
        if (func_020644cc(100) > lim - 0x14) {
            q = (VecFx32 *) (self + 0x1d4);
            if (q->x != v.x || q->z != v.z) {
                q = (VecFx32 *) (self + 0x1d4);
                q->x = v.x;
                q->y = v.y;
                q->z = v.z;
                q = (VecFx32 *) (self + 0x1c8);
                q->x = p->x;
                q->y = p->y;
                q->z = p->z;
            }
            if (db <= 0x3000) {
                *(int *) (self + 0x220) = v.y;
            } else {
                *(int *) (self + 0x220) = *(int *) (self + 0x228);
            }
            *buf = *buf + da;
            VEC_Subtract(&v, p, &v);
            func_ov003_022321b8(&v, &v, 1);
            VEC_Add(p, &v, p);
        }
    }
    goto done;

one:
    *(int *) (self + 0x220) = *(int *) (self + 0x228);
done:
    return 1;
zero:
    *(int *) (self + 0x220) = *(int *) (self + 0x228);
    return 0;
}
