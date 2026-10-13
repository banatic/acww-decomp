/* func_ov068_02270070 @ 0x02270070, 0x140 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} VecFx32;

extern int func_ov003_02224718(VecFx32 *v, VecFx32 *p);
extern int func_ov003_02224768(VecFx32 *v, VecFx32 *p, int c);
extern int func_ov003_0223482c(int a);
extern void func_0204f818(int *a, int *b, VecFx32 *v);
extern void *func_0204f5e0(void *g, int ax, int az, int bx, int bz, int c);
extern int func_ov003_02235518(int a, void *tile);
extern int func_02049ec4(void *tile);
extern void func_ov068_02270008(int a, VecFx32 *v);
extern int FX_Div(int a, int b);
extern int func_0200322c(VecFx32 *a, VecFx32 *b);
extern int func_020ea990(VecFx32 *a, VecFx32 *b);
extern void *data_021c80bc;

int func_ov068_02270070(u8 *self, s16 *ang, int *dist, VecFx32 *v)
{
    VecFx32 *pos;
    void *tile;
    int a;
    int b;
    int o1;
    int o2;
    int ax;
    int bz;
    u8 st;
    int ok;

    pos = (VecFx32 *) (self + 0x204);
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
