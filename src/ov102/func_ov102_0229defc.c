/* func_ov102_0229defc @ 0x0229defc, 0x98 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(void *self, int a);
extern void func_ov102_0229d760(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov102_0229d37c(void *self, int a, int b, int c);
extern void func_ov102_0229d6b4(void *self, int n);
extern void func_ov102_0229c460(void *self, int a);
extern int func_ov102_0229c364(void *self, int a, int b);
extern void func_ov102_0229c318(void *self);

void func_ov102_0229defc(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov102_0229d760(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    n = func_ov102_0229d37c(self, a, b, 1);
    if (n != 0x25) {
        func_ov102_0229d6b4(self, n);
        return;
    }
    if (a >= 0xc8 && a <= 0xf8 && b >= 0x68 && b <= 0x78) {
        func_ov102_0229c460(self, 1);
        return;
    }
    if (func_ov102_0229c364(self, a, b) != 0) {
        func_ov102_0229c318(self);
    }
}
