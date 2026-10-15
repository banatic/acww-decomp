/* func_ov132_0229b340 @ 0x0229b340, 0x8c bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(void *self, int a);
extern int func_ov132_0229b124(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov002_0220a784(void *p, int a);
extern void func_ov132_0229b0d0(void *self);
extern void func_ov132_0229aff8(void *self);
extern void func_ov132_0229af88(void *self);

void func_ov132_0229b340(char *self)
{
    unsigned int ok;
    int a;
    int b;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov132_0229b124(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    if (func_ov002_0220a784(self + 0xf8, 6) != 0) {
        func_ov132_0229b0d0(self);
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    if (a < 0x40) {
        return;
    }
    if (a >= 0xc0) {
        return;
    }
    if (b >= 0x38 && b < 0x58) {
        func_ov132_0229aff8(self);
        return;
    }
    if (b >= 0x60 && b < 0x80) {
        func_ov132_0229af88(self);
    }
}
