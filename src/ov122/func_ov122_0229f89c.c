/* func_ov122_0229f89c @ 0x0229f89c, 0xa2 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229f89c {
    u8 pad_00[0xaa];
    u8 mode;
    u8 pad_AB[2];
    u8 unk_AD;
    u8 unk_AE;
    u8 pad_AF[13];
    u8 *ptr;
    u8 unk_C0;
};

extern int func_ov122_0229f5f8(void *self);
extern int func_ov122_0229f5c8(void *self);
extern int func_ov095_0229bbc0(void *dst, int a, int b, int c, int d);
extern void func_ov122_0229f590(void *self, int r);
extern void func_ov122_0229f940(void *self);

void func_ov122_0229f89c(struct UnkStruct_0229f89c *self)
{
    unsigned int a, b, hi, lo;
    int c, d;
    u8 r;

    b = self->unk_AE;
    a = self->unk_AD;
    if (a > b) {
        lo = b;
        hi = a;
    } else {
        lo = a;
        hi = b;
    }

    c = func_ov122_0229f5f8(self);
    d = func_ov122_0229f5c8(self);

    switch (self->mode) {
        case 0: {
            u8 *p = self->ptr;
            p[0xf8] = p[0xf8] - (hi - lo);
            break;
        }
        case 1: {
            u8 *p = self->ptr;
            u8 v = p[0xf8];
            lo += v;
            hi += v;
            break;
        }
        default:
            break;
    }

    r = (u8) func_ov095_0229bbc0(&self->unk_C0, c, lo, hi, d);

    if (self->mode == 1) {
        r = (u8) (r - self->ptr[0xf8]);
    }

    func_ov122_0229f590(self, r);
    func_ov122_0229f940(self);
}
