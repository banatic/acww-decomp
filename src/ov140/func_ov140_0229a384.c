/* func_ov140_0229a384 @ 0x0229a384, 0x78 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern unsigned int func_ov140_0229a15c(void *receiver);
extern int func_ov140_0229a1a4(u8 *self, u8 *p);

int func_ov140_0229a384(u8 *self)
{
    int changed;
    int i;
    int idx;
    int off;
    int v;
    u8 *base;

    changed = 0;
    base = (u8 *) func_ov140_0229a15c(self);
    idx = self[0x8dd] * 6;
    for (i = 0; i < 6; i++) {
        off = idx;
        off = off * 0x23;
        if (func_ov140_0229a1a4(self, base + 0x180 + off) == 0) {
            v = 0;
        } else {
            v = (base + off)[0x1a2];
        }
        if (v != (self + i)[0x8e0]) {
            changed = 1;
            (self + i)[0x8e0] = (u8) v;
        }
        idx++;
    }
    return changed;
}
