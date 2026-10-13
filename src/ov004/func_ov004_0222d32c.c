/* func_ov004_0222d32c @ 0x0222d32c, 0x1a8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 r, g, b, pad_03;
    int first, other;
} Entry;
extern Entry data_ov004_02247784[];
#define W(p, o) (*(unsigned *) ((p) + (o)))
#define P(p, o) (*(u8 **) ((p) + (o)))
extern void func_0209def4(u8 *);
extern int FX_Div(int, int), FX_MulFunc(int, int);
void func_ov004_0222d32c(u8 *self, void *id, u8 *model)
{
    u8 time[2];
    int t, inv, next, current, alpha0, alpha1;
    u16 color;
    u8 hour;
    func_0209def4(time);
    hour = time[1];
    t = FX_Div(time[0] << 12, 60 << 12);
    next = (u8) ((hour + 1) % 24);
    current = (u8) (hour % 24);

    color = (u8) (((0x1000 - t) * data_ov004_02247784[current].r + t * data_ov004_02247784[next].r) >> 12) |
            ((u8) (((0x1000 - t) * data_ov004_02247784[current].g + t * data_ov004_02247784[next].g) >> 12) << 5) |
            ((u8) (((0x1000 - t) * data_ov004_02247784[current].b + t * data_ov004_02247784[next].b) >> 12) << 10);
    alpha1 = ((0x1000 - t) * data_ov004_02247784[current].other + t * data_ov004_02247784[next].other) >> 12;
    alpha0 = ((0x1000 - t) * data_ov004_02247784[current].first + t * data_ov004_02247784[next].first) >> 12;
    if (id == P(self, 0x2b0) || id == P(self, 0x2b4) || id == P(self, 0x2b8)) {
        u8 alpha = (W(P(model, 0xb0), 0xc) >> 16) & 31;
        if (id == P(self, 0x2b0)) {
            alpha = (FX_MulFunc(alpha << 12, alpha0) >> 12) & 31;
        } else {
            alpha = (FX_MulFunc(alpha << 12, alpha1) >> 12) & 31;
        }
        W(P(model, 0xb0), 0xc) &= 0xffe0ffff;
        W(P(model, 0xb0), 0xc) |= alpha << 16;
        W(model, 8) &= 0xfffffeff;
        W(P(model, 0xb0), 4) &= 0xffff8000;
        W(P(model, 0xb0), 4) |= color;
    }
}
