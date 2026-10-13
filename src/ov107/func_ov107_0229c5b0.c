/* func_ov107_0229c5b0 @ 0x0229c5b0, 0x78 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206fca4(u8 *self);
extern int func_ov107_0229c354(u8 *self);
extern int func_ov003_022278e0(u8 *p, int x);
extern u8 *func_020961a8(int);
extern int func_0203162c(u8 *a, u8 *b, int c, int d, int e, int f);
extern short data_ov107_0229e280[];

int func_ov107_0229c5b0(u8 *self)
{
    int t;
    int x;
    int i;
    int base;
    u8 *obj;
    u8 *sub;

    t = func_0206fca4(self);
    x = func_ov107_0229c354(self);
    if (t == 0x2c) {
        return func_ov003_022278e0(self + 0xc0, x);
    }

    obj = func_020961a8(4);
    sub = obj + 0x5c;
    i = 0;
    base = *(short *) (obj + 0x8e);
    for (; i < 8; i++) {
        if (func_0203162c(self + 0xc0, sub, (short) (base + data_ov107_0229e280[i]), 0x7800, 0xa00, 0xc) != 0) {
            return 1;
        }
    }
    return 0;
}
