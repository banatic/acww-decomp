/* func_ov100_0229e17c @ 0x0229e17c, 0x8c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(void *self, int a);
extern void func_ov100_0229d8d0(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov100_0229d550(void *self, int a, int b, int c);
extern void func_ov100_0229d824(void *self, int n);
extern void func_ov100_0229c4ec(void *self);
extern void func_ov100_0229c3c0(void *self);

void func_ov100_0229e17c(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov100_0229d8d0(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    n = func_ov100_0229d550(self, a, b, 1);
    if (n != 0x20) {
        func_ov100_0229d824(self, n);
        return;
    }
    if (a < 0xc8) {
        return;
    }
    if (a > 0xf8) {
        return;
    }
    if (b < 0x50) {
        return;
    }
    if (b > 0x70) {
        return;
    }
    if (b >= 0x60) {
        func_ov100_0229c4ec(self);
        return;
    }
    func_ov100_0229c3c0(self);
}
