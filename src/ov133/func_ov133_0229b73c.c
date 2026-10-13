/* func_ov133_0229b73c @ 0x0229b73c, 0x54 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern const u8 data_ov133_0229c7a8[];

int func_ov133_0229b73c(char *self, int x, int y)
{
    int cx, cy;

    cx = x - 0x50;
    cy = y - 0x60;
    if (cx >= 0 && cx < 0x60 && cy >= 0 && cy < 0x40) {
        *(u8 *) (self + 0x9c) = data_ov133_0229c7a8[(cx >> 5) + 3 * (cy >> 4)];
        return *(u8 *) (self + 0x9c);
    }
    if (y >= 0x40 && y <= 0x50) {
        *(u8 *) (self + 0x9c) = 0xc;
        return *(u8 *) (self + 0x9c);
    }
    return 0xf;
}
