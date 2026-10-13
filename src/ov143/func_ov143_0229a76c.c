/* func_ov143_0229a76c @ 0x0229a76c, 0x90 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(void *self, int a);
extern void func_ov143_0229a300(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov143_02299ed8(void *self, int a, int b);
extern void func_ov143_02299e18(void *self, int n);
extern int func_ov002_0220a784(void *p, int a);
extern void func_ov143_0229a230(void *self);
extern void func_ov143_0229a200(void *self);

void func_ov143_0229a76c(char *self)
{
    unsigned int ok;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov143_0229a300(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    n = func_ov143_02299ed8(self, data_021f6c58, data_021f6c54);
    if (n != 0x16) {
        func_ov143_02299e18(self, n);
        return;
    }

    if (func_ov002_0220a784(self + 0x110, 1) != 0) {
        func_ov143_0229a230(self);
        return;
    }
    if (func_ov002_0220a784(self + 0x110, 2) != 0) {
        func_ov143_0229a200(self);
    }
}
