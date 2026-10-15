/* func_ov144_0229ab88 @ 0x0229ab88, 0xb8 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(void *self, int a);
extern unsigned char *func_ov144_0229a7e8(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov144_02299a30(void *self, int a, int b);
extern int func_ov144_02299ac4(void *self, int n);
extern int func_ov144_0229a540(void *self, int a, int b);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void func_ov002_0220a574(void *p);

void func_ov144_0229ab88(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov144_0229a7e8(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    n = func_ov144_02299a30(self, a, b);
    if (n != 0xe) {
        func_ov144_02299ac4(self, n);
        return;
    }

    if (*(int *) (self + 0xa4) <= 0) {
        return;
    }
    if (func_ov144_0229a540(self, a, b) != 0) {
        func_ov002_02208098(self, 1);
        return;
    }
    if (a < 0xcf) {
        return;
    }
    if (a > 0xdf) {
        return;
    }
    if (b < 0x1d) {
        return;
    }
    if (b > 0x93) {
        return;
    }
    func_ov002_0220a574(self + 0x128);
    *(int *) (self + 0xb0) = *(int *) (self + 0xa8);
    func_ov002_02208098(self, 2);
}
