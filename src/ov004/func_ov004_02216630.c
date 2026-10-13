/* func_ov004_02216630 @ 0x02216630, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_0220cdf8(void *self);
extern void func_ov004_02216598(void *self, int k, int c);
extern volatile u16 data_ov004_02256fec;

int func_ov004_02216630(char *self)
{
    int ok;
    u16 lo, hi;

    func_ov004_02216598(self, *(u8 *) (self + 0x845), func_ov004_0220cdf8(self));
    ok = 0;
    lo = data_ov004_02256fec;
    hi = data_ov004_02256fec;
    if (hi >= 0x1323 && lo <= 0x1368) {
        ok = 1;
    }
    if (ok) {
        data_ov004_02256fec = 0xfff1;
    }
    return 1;
}
