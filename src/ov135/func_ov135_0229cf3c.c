/* func_ov135_0229cf3c @ 0x0229cf3c, 0xb4 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov002_02208054(void *self, int a);
extern void func_ov135_0229ca3c(void *self);
extern u8 data_021fbdd8;
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov002_0220a784(void *p, int a);
extern void func_ov135_0229c97c(void *self);
extern void func_ov135_0229c954(void *self);
extern int func_ov134_0229b168(void *p, int a, int b);
extern void func_0206f768(void);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov134_0229abd4(void *p, int a, int b);
extern void func_ov135_0229c924(void *self, int n);

void func_ov135_0229cf3c(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov135_0229ca3c(self);
        return;
    }

    ok = (data_021fbdd8 != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    if (func_ov002_0220a784(self + 0xfc, 6) != 0) {
        func_ov135_0229c97c(self);
        return;
    }
    if (func_ov002_0220a784(self + 0xfc, 7) != 0) {
        func_ov135_0229c954(self);
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    if (func_ov134_0229b168(self + 0x2c8, a, b) != 0) {
        func_0206f768();
        func_ov002_02208098((void *) (self), 1);
    }
    n = func_ov134_0229abd4(self + 0x2c8, a, b);
    if (n != 6) {
        func_ov135_0229c924(self, n);
    }
}
