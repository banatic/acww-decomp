/* func_ov004_02235ddc @ 0x02235ddc, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_ov004_02247928[];

void func_ov004_02235ddc(char *self)
{
    int lim, hi, v;
    if (*(u8 *) (self + 0x1c8) == 1) {
        lim = 0;
        hi = 0x22;
    } else {
        lim = -2;
        hi = 0x24;
    }
    v = *(int *) (self + 0x1a8) >> 12;
    if (v <= lim) {
        *(s16 *) (self + 0x1c0) = 0x4000;
        *(int *) (self + 0x1ac) = (data_ov004_02247928[*(int *) (self + 0x15c) * 0x11] << 12) >> 6;
    } else if (v >= hi) {
        *(s16 *) (self + 0x1c0) = (s16) 0xffffc000;
        *(int *) (self + 0x1ac) = (data_ov004_02247928[*(int *) (self + 0x15c) * 0x11] << 12) >> 6;
    }
}
