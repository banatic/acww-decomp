/* insect_paths_2: 2 functions, module ov068
 * mwccarm 1.2/base -O1,s
 * func_ov068_022701b0 @ 0x022701b0, 0x178 bytes, Thumb
 * func_ov068_02270070 @ 0x02270070, 0x140 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int x, y, z;
} VecFx32_02270070;

extern int func_ov003_02234984(u8 *self);
extern int FX_Div(int a, int b);
extern int func_020644cc(int a);
extern void func_ov003_02230f88(u8 *self);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *dst);
extern void func_ov003_022321b8(VecFx32 *a, VecFx32 *b, int c);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *dst);
extern int func_ov003_02224718(VecFx32_02270070 *v, VecFx32_02270070 *p);
extern int func_ov003_02224768(VecFx32_02270070 *v, VecFx32_02270070 *p, int c);
extern int func_ov003_0223482c(int a);
extern void func_0204f818(int *a, int *b, VecFx32_02270070 *v);
extern void *func_0204f5e0(void *g, int ax, int az, int bx, int bz, int c);
extern int func_ov003_02235518(int a, void *tile);
extern int func_02049ec4(void *tile);
extern void func_ov068_02270008(int a, VecFx32_02270070 *v);
extern int func_0200322c(VecFx32_02270070 *a, VecFx32_02270070 *b);
extern int func_020ea990(VecFx32_02270070 *a, VecFx32_02270070 *b);
extern void *data_021c80bc;

int func_ov068_02270070(u8 *self, s16 *ang, int *dist, VecFx32_02270070 *v);

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

    if (func_ov068_02270070(self, &da, &db, (VecFx32_02270070 *) (&v)) == 0) {
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

int func_ov068_02270070(u8 *self, s16 *ang, int *dist, VecFx32_02270070 *v)
{
    VecFx32_02270070 *pos;
    void *tile;
    int a;
    int b;
    int o1;
    int o2;
    int ax;
    int bz;
    u8 st;
    int ok;

    pos = (VecFx32_02270070 *) (self + 0x204);
    st = self[0x24d];
    if (st == 0x33) {
        if (func_ov003_02224718(v, pos) != 0) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        if (func_ov003_02224768(v, pos, func_ov003_0223482c((s8) st)) != 0) {
            ok = 1;
        } else {
            ok = 0;
        }
    }
    if (ok != 0) {
        o1 = 0;
        o2 = 0;
        func_0204f818(&o1, &o2, v);
        a = o1;
        b = o2;
        ax = a >> 4;
        bz = o2 >> 4;
        tile = func_0204f5e0(data_021c80bc, ax, bz, a - (ax << 4), b - (bz << 4), 0);
        if (st == 2 || st == 3) {
            if (func_ov003_02235518((s8) st, tile) == 0) {
                return 0;
            }
        }
        if (st != 0x33) {
            func_ov068_02270008((s8) func_02049ec4(tile), v);
        } else {
            v->x = v->x + 0x1000;
            v->y = FX_Div(0xb000, 0x10000);
            v->z = v->z + 0x1000;
        }
        *ang = func_0200322c(pos, v);
        *ang = *ang - *(s16 *) (self + 0x23a);
        if (*ang > 0x38e) {
            *ang = 0x38e;
        } else if (*ang < -910) {
            *ang = -910;
        }
        *dist = func_020ea990(v, pos);
        return 1;
    }
    return 0;
}
