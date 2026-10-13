/* func_ov119_0229af64 @ 0x0229af64, 0xa8 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

u16 func_ov119_0229af64(int unused, int c1, int c2, int w, int tot)
{
    int b2, g2, r2;
    int d;
    int b, g, r;

    b2 = (u8) (c2 & 0x1f);
    g2 = (u8) ((c2 & 0x3e0) >> 5);
    r2 = (u8) ((c2 & 0x7c00) >> 10);
    d = tot - w;
    b = (u8) (((u8) (c1 & 0x1f) * w + b2 * d) / tot);
    g = (u8) (((u8) ((c1 & 0x3e0) >> 5) * w + g2 * d) / tot);
    r = (u8) (((u8) ((c1 & 0x7c00) >> 10) * w + r2 * d) / tot);
    return (u16) (b | (g << 5) | (r << 10));
}
