/* func_ov142_02299794 @ 0x02299794, 0x9c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

// RGB15 lerp, built at -O1,s.

u16 func_ov142_02299794(void *self, u16 c1, u16 c2, int w)
{
    u16 c2l;
    int iw;
    u8 b2;
    u8 g2;
    u8 red2;
    u16 c1l;
    u8 green;
    u8 rc;
    u8 blue;

    c2l = c2;
    b2 = (u8) (c2l & 0x1f);
    g2 = (u8) ((c2l & 0x3e0) >> 5);
    red2 = (u8) ((c2l & 0x7c00) >> 10);
    iw = 3 - w;
    c1l = c1;
    blue = (u8) (((u8) (c1l & 0x1f) * w + b2 * iw) / 3);
    green = (u8) (((u8) ((c1l & 0x3e0) >> 5) * w + g2 * iw) / 3);
    rc = (u8) (((u8) ((c1l & 0x7c00) >> 10) * w + red2 * iw) / 3);
    return (u16) (blue | (green << 5) | (rc << 10));
}
