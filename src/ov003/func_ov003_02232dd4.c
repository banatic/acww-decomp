/* func_ov003_02232dd4 @ 0x02232dd4, 0xb4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov003_02235b54(u8 *self, int a, int b);

int func_ov003_02232dd4(u8 *self, int a1, int a2, u8 dir)
{
    int r;
    int v;
    s8 k;

    r = func_ov003_02235b54(self, 0x50, 0xe38);
    v = 0;
    dir = *(self + 0x252);
    if (r != 0) {
        k = *(s8 *) (self + 0x24d);
        if (k == 0x35) {
            v = *(s16 *) (self + 0x23c);
        } else {
            v = *(s16 *) (self + 0x23a);
        }
        if (r == 3) {
            if (dir == 1 || dir == 0xa) {
                v = (s16) (v - 0xaaa);
            } else {
                v = (s16) (v + 0xaaa);
            }
        } else if (r == 1 || dir == 1) {
            v = (s16) (v - 0x38e);
            dir = 1;
        } else if (r == 2 || dir == 2) {
            v = (s16) (v + 0x38e);
            dir = 2;
        }
        if (k == 0x35) {
            *(s16 *) (self + 0x23c) = v;
        } else {
            *(s16 *) (self + 0x23a) = v;
        }
        v = 1;
    } else {
        if (dir < 0xa) {
            dir = dir * 10;
        }
    }
    *(self + 0x252) = dir;
    return v;
}
