/* func_ov068_0226fea4 @ 0x0226fea4, 0x164 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

#define FX_F32_TO_FX32(x) ((int) (((x) > 0) ? ((x) * 4096.0f + 0.5f) : ((x) * 4096.0f - 0.5f)))

extern int func_020644cc(int a);
extern void func_ov003_0223597c(VecFx32 *v, int ang);
extern int FX_MulFunc(int a, int b);

void func_ov068_0226fea4(u8 *self, s16 *buf, int step, int period, u8 limit, int scale)
{
    unsigned int r;
    int *p;
    VecFx32 v;
    int flag;

    flag = self[0x24b];
    r = (u8) func_020644cc(100);
    p = (int *) (self + 0x204);

    if (self[0x24f] % period == 0) {
        if (r > limit) {
            flag = (flag == 0) ? 1 : 0;
            self[0x24b] = flag;
        }
    }

    if (r > self[0x252]) {
        if (flag != 0) {
            *buf = *buf + step;
        } else {
            *buf = *buf - step;
        }
    }

    func_ov003_0223597c(&v, *buf);
    *(s16 *) (self + 0x23a) = *buf;

    if (self[0x24a] != 0) {
        float f = 1.25f;
        if (*(s8 *) (self + 0x24d) == 0xa || *(s8 *) (self + 0x24d) == 0x33) {
            f = 1.5f;
        }
        p[0] = p[0] + FX_MulFunc(FX_MulFunc(FX_F32_TO_FX32(f), scale), v.x);
        p[2] = p[2] + FX_MulFunc(FX_MulFunc(FX_F32_TO_FX32(f), scale), v.z);
    } else {
        p[0] = p[0] + FX_MulFunc(scale, v.x);
        p[2] = p[2] + FX_MulFunc(scale, v.z);
    }
}
