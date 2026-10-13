/* func_ov136_0229ce7c @ 0x0229ce7c, 0x98 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(void *self, int a);
extern void func_ov136_0229c994(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov002_0220a784(void *p, int a);
extern void func_ov136_0229c92c(void *self);
extern int func_ov134_0229b168(void *p, int a, int b);
extern void func_ov002_02208098(void *self, int a);
extern int func_ov134_0229aad8(void *p, int a, int b);
extern void func_ov136_0229c900(void *self, int n);

void func_ov136_0229ce7c(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov136_0229c994(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    if (func_ov002_0220a784(self + 0xf8, 6) != 0) {
        func_ov136_0229c92c(self);
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    if (func_ov134_0229b168(self + 0x2c4, a, b) != 0) {
        func_ov002_02208098(self, 1);
    }
    n = func_ov134_0229aad8(self + 0x2c4, a, b);
    if (n != 6) {
        func_ov136_0229c900(self, n);
    }
}
