/* func_ov096_022a0cb8 @ 0x022a0cb8, 0xa8 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206f56c(void *self);
extern void func_ov096_0229d16c(void *self);
extern int func_ov002_02208054(void *self, int a);
extern void func_ov096_0229fb6c(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov002_02208aec(void *p, int a, int b);
extern void func_ov002_022090b0(void *p, int n);
extern int func_ov002_02208a8c(void *p, int a, int b);
extern void func_ov002_02208098(void *self, int a);

void func_ov096_022a0cb8(char *self)
{
    unsigned int ok;
    int n;

    if (func_0206f56c(self) != 0) {
        func_ov096_0229d16c(self);
        return;
    }
    if (func_ov002_02208054(self, 1) != 0) {
        func_ov096_0229fb6c(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    n = func_ov002_02208aec(self + 0x2564, data_021f6c58, data_021f6c54);
    if (n >= 0) {
        func_ov002_022090b0(self + 0x2564, n);
        *(u8 *) (self + 0xbe) = (u8) func_ov002_02208a8c(self + 0x2564, *(u8 *) (self + 0xbd), (u8) n);
        func_ov002_02208098(self, 0x23);
    } else {
        func_ov096_0229d16c(self);
    }
}
