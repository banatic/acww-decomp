/* func_ov142_0229a1fc @ 0x0229a1fc, 0x9c bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_0220a784(void *, int);
extern int func_ov142_02299668(void *, int);
extern int func_ov142_0229a6d8(void *);

int func_ov142_0229a1fc(u8 *self, int arg1, int arg2)
{
    if (func_ov002_0220a784(self + 0x194, 6)) {
        return 0x13;
    }

    if (func_ov142_02299668(self, 0x20)) {
        if (arg1 >= 0xc4 && arg1 < 0xe8 && arg2 >= 0x4d && arg2 < 0x71) {
            return 0x12;
        }
    }

    if (arg1 <= 0x1b) {
        if (arg2 >= 0x18 && arg2 < 0xa8) {
            return (u8) ((arg2 - 0x18) >> 4);
        }
        return 0x19;
    } else {
        if (arg1 >= 0x38 && arg1 <= 0x9c) {
            if (arg2 >= 0x20 && arg2 < 0xa0) {
                int field = (*(u32 *) (self + 0xa0)) & 0xf;
                int v = (arg2 - (0x20 - field)) >> 4;
                if (v >= func_ov142_0229a6d8(self)) {
                    return 0x19;
                } else {
                    return (u8) (v + 9);
                }
            } else {
                return 0x19;
            }
        } else {
            return 0x19;
        }
    }
}
