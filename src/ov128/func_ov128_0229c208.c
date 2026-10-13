/* func_ov128_0229c208 @ 0x0229c208, 0x98 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(void *self, int a);
extern void func_ov128_0229be20(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov127_02299d20(void *p, int a, int b);
extern void func_ov127_02299c08(void *p, int v, int c);
extern void func_ov128_0229bb20(void *self);
extern void func_ov002_02208098(void *self, int a);
extern void func_ov128_0229bdd4(void *self);

void func_ov128_0229c208(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int v;

    if (func_ov002_02208054(self, 0) != 0) {
        func_ov128_0229be20(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    *(u8 *) (self + 0x2d6b) = (u8) func_ov127_02299d20(self + 0x4a4, a, b);
    v = *(u8 *) (self + 0x2d6b);
    if (v != 4) {
        func_ov127_02299c08(self + 0x4a4, v, 1);
        func_ov128_0229bb20(self);
        func_ov002_02208098(self, 1);
        return;
    }
    if (a < 0xc0) {
        return;
    }
    if (b <= 0xab) {
        return;
    }
    func_ov128_0229bdd4(self);
}
