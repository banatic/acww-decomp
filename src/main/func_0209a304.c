/* func_0209a304 @ 0x0209a304, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern fx32 FX_MulFunc(fx32 a, fx32 b);

struct Quat {
    fx32 x, y, z, w;
};

struct Mtx33 {
    fx32 m[9];
};

void func_0209a304(struct Quat *self, struct Mtx33 *out)
{
    fx32 xx, xy, xz, zz, zy, yy, wx, wy, wz;

    xx = FX_MulFunc(self->x, self->x);
    xy = FX_MulFunc(self->x, self->y);
    xz = FX_MulFunc(self->x, self->z);
    zz = FX_MulFunc(self->z, self->z);
    zy = FX_MulFunc(self->z, self->y);
    yy = FX_MulFunc(self->y, self->y);
    wx = FX_MulFunc(self->w, self->x);
    wy = FX_MulFunc(self->w, self->y);
    wz = FX_MulFunc(self->w, self->z);

    out->m[0] = 0x1000 - ((yy + zz) << 1);
    out->m[1] = (xy + wz) << 1;
    out->m[2] = (xz - wy) << 1;
    out->m[3] = (xy - wz) << 1;
    out->m[4] = 0x1000 - ((xx + zz) << 1);
    out->m[5] = (zy + wx) << 1;
    out->m[6] = (wy + xz) << 1;
    out->m[7] = (zy - wx) << 1;
    out->m[8] = 0x1000 - ((xx + yy) << 1);
}
