/* func_ov104_0229e864 @ 0x0229e864, 0x94 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(void *self, int a);
extern void func_ov104_0229dd20(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov104_0229d9bc(void *self, int a, int b, int c);
extern void func_ov104_0229dc68(void *self, int n);
extern int func_ov002_0220a784(void *p, int a);
extern void func_ov104_0229ca44(void *self);
extern void func_ov104_0229c9fc(void *self);

void func_ov104_0229e864(char *self)
{
    unsigned int ok;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov104_0229dd20(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    n = func_ov104_0229d9bc(self, data_021f6c58, data_021f6c54 + 0x10, 1);
    if (n != 0x21) {
        func_ov104_0229dc68(self, n);
        return;
    }

    if (func_ov002_0220a784(self + 0x41b4, 9) != 0) {
        func_ov104_0229ca44(self);
        return;
    }
    if (func_ov002_0220a784(self + 0x41b4, 7) != 0) {
        func_ov104_0229c9fc(self);
    }
}
