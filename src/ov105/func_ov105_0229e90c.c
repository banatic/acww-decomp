/* func_ov105_0229e90c @ 0x0229e90c, 0x98 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(void *self, int a);
extern void func_ov105_0229db34(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov105_0229d69c(void *self, int a, int b, int c);
extern void func_ov105_0229d9e0(void *self, int n);
extern int func_ov002_0220a784(void *p, int a);
extern void func_ov105_0229c668(void *self);
extern int func_ov105_0229c438(void *self, int a, int b);
extern void func_ov105_0229c3ec(void *self);

void func_ov105_0229e90c(char *self)
{
    unsigned int ok;
    int n;
    int a;
    int b;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov105_0229db34(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54 + 0x10;
    n = func_ov105_0229d69c(self, a, b, 1);
    if (n != 0x40) {
        func_ov105_0229d9e0(self, n);
        return;
    }

    if (func_ov002_0220a784(self + 0x5fb8, 9) != 0) {
        func_ov105_0229c668(self);
        return;
    }
    if (func_ov105_0229c438(self, a, b) != 0) {
        func_ov105_0229c3ec(self);
    }
}
