/* func_ov145_0229a5b0 @ 0x0229a5b0, 0xc8 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(void *self, int a);
extern void func_ov145_0229a330(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov002_0220a784(void *p, int a);
extern void func_ov145_0229a2e0(void *self);
extern int func_ov145_022998c4(void *self, int a, int b);
extern void func_ov145_022998f0(void *self, int n);
extern int func_ov145_0229a298(void *self, int a, int b);
extern void func_ov002_02208098(void *self, int a);
extern void func_ov002_0220a574(void *p);

void func_ov145_0229a5b0(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov145_0229a330(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    if (func_ov002_0220a784(self + 0x174, 6) != 0) {
        func_ov145_0229a2e0(self);
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    n = func_ov145_022998c4(self, a, b);
    if (n != 6) {
        func_ov145_022998f0(self, n);
        return;
    }

    if (*(int *) (self + 0xa4) <= 0) {
        return;
    }
    if (func_ov145_0229a298(self, a, b) != 0) {
        func_ov002_02208098(self, 1);
        return;
    }
    if (a < 0xe4) {
        return;
    }
    if (a > 0xec) {
        return;
    }
    if (b < 0x15) {
        return;
    }
    if (b > 0x8d) {
        return;
    }
    func_ov002_0220a574(self + 0x12c);
    func_ov002_02208098(self, 2);
}
