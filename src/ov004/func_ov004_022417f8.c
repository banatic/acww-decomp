/* func_ov004_022417f8 @ 0x022417f8, 0x9c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02056fcc(void *, int, int, int, int);
extern int func_020644cc(int);
extern u8 data_ov004_02259a24;

void func_ov004_022417f8(char *self)
{
    unsigned int t = (unsigned int) (*(int *) (self + 0x154) << 4) >> 16;
    u8 g;
    if (t == 0xd || t < 9) {
        func_02056fcc(self + 0x14c, 9, 1, 0, 9);
    }
    g = data_ov004_02259a24;
    if (g > 0x50) {
        if (*(u8 *) (self + 0x22) != 0) {
            if (func_020644cc(0x64) > 0x5c && t < 0xa) {
                func_02056fcc(self + 0x14c, 0xe, 1, 0x1000, 9);
            }
        } else if (g % 5 == 0) {
            if (func_020644cc(0x64) > 0x5c && t < 0xa) {
                func_02056fcc(self + 0x14c, 0xe, 1, 0x1000, 9);
            }
        }
    }
}
