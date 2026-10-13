/* func_ov003_02231d1c @ 0x02231d1c, 0x108 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_022353a4(void *self, int a, int b);
extern int func_020644cc(int n);
extern void func_02056fcc(void *p, int a, int b, int c, int d);

void func_ov003_02231d1c(char *self, volatile short *pn)
{
    signed char k;
    u8 f;
    u8 s;
    u8 rnd;
    u32 v;

    k = *(signed char *) (self + 0x24d);
    if ((u8) (signed char) (k - 0x10) <= 4) {
        f = *(u8 *) (self + 0x246);
        if (f != 0 && *(u8 *) (self + 0x254) < 0xa) {
            s = *(u8 *) (self + 0x252);
            if (s == 0 && f != 0) {
                func_ov003_022353a4(self, 0, 1);
            } else {
                *(u8 *) (self + 0x252) = s - 1;
            }
        } else {
            *(u8 *) (self + 0x252) = 0x3c;
        }
    } else {
        rnd = (u8) func_020644cc(0x64);
        if (*(signed char *) (self + 0x24d) == 9) {
            v = ((u32) * (int *) (self + 0xf4) << 4) >> 16;
            if (v == 0xd || v < 9) {
                func_02056fcc(self + 0xec, 9, 1, 0, 9);
            }
            if (*pn > 0x50) {
                if (rnd > 0x5c && v < 0xa) {
                    func_02056fcc(self + 0xec, 0xe, 1, 0x1000, 9);
                }
                if (*pn > 0xa0) {
                    *pn = 0;
                }
            }
            *pn = *pn + 1;
        } else if (rnd > 0x46) {
            *pn = *pn + 1;
            if (*pn % 0x14 == 0) {
                if (rnd < 0x55) {
                    *(u8 *) (self + 0x251) = 3;
                } else {
                    *(u8 *) (self + 0x251) = 2;
                }
                *pn = 0;
            }
        }
    }
}
