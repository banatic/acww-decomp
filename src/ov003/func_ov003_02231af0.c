/* func_ov003_02231af0 @ 0x02231af0, 0xf4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020644cc(int n);

void func_ov003_02231af0(char *self, volatile short *pn)
{
    short h;
    short n;

    h = *(short *) (self + 0x23a);
    n = *pn;
    if (n == 0) {
        if (func_020644cc(0x64) < 0x32) {
            *pn = 1;
        } else {
            *pn = -1;
        }
    } else if ((n > 0 && n <= 6) || (n > 0x12 && n <= 0x18) || (n < -6 && n >= -0x12)) {
        if (n > 0) {
            *pn = *pn + 1;
            *(short *) (self + 0x238) = *(short *) (self + 0x238) + 0xb6;
        } else {
            *pn = *pn - 1;
            *(short *) (self + 0x238) = *(short *) (self + 0x238) - 0xb6;
        }
        h = h + 0x16b;
    } else if ((n > 6 && n <= 0x12) || (n < 0 && n >= -6) || (n < -0x12 && n >= -0x18)) {
        if (n > 0) {
            *pn = *pn + 1;
            *(short *) (self + 0x238) = *(short *) (self + 0x238) - 0xb6;
        } else {
            *pn = *pn - 1;
            *(short *) (self + 0x238) = *(short *) (self + 0x238) + 0xb6;
        }
        h = h - 0x16b;
    } else {
        *pn = 0;
        *(u8 *) (self + 0x251) = 0x13;
    }
    *(short *) (self + 0x23a) = h;
}
