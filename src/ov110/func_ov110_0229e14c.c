/* func_ov110_0229e14c @ 0x0229e14c, 0x80 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(void *self, int a);
extern void func_ov110_0229d860(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov110_0229d504(void *self, int a, int b, int c);
extern void func_ov110_0229d7b8(void *self, int n);
extern void func_ov110_0229c3b8(void *self, int a);

void func_ov110_0229e14c(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov110_0229d860(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    n = func_ov110_0229d504(self, a, b, 1);
    if (n != 0x1f) {
        func_ov110_0229d7b8(self, n);
        return;
    }
    if (a < 0xc8) {
        return;
    }
    if (a > 0xf8) {
        return;
    }
    if (b < 0x60) {
        return;
    }
    if (b > 0x70) {
        return;
    }
    func_ov110_0229c3b8(self, 1);
}
