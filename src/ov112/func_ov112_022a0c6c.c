/* func_ov112_022a0c6c @ 0x022a0c6c, 0xd4 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 data_021fbe40;

extern int func_0208e484(void *p);
extern int func_ov095_02299a00(void *p);
extern int func_ov095_0229c448(void *p, int a, int b);
extern void func_ov002_02208098(void *self, int a);
extern void func_ov002_0220a574(void *p);
extern void func_ov002_0220a4bc(void *p);
extern int func_ov112_0229f900(void *self);
extern void func_ov112_0229fd20(void *self);
extern void func_ov112_0229f8e4(void *self);
extern void func_ov112_0229fe60(void *self, int a);
extern int func_ov112_022a03ac(void *self, int n);
extern void func_ov095_0229bf3c(void *p);
extern void func_ov095_0229c8e4(void *p, int a);
extern void func_ov095_0229cce0(void *p);
extern void func_ov112_0229f270(void *self);

void func_ov112_022a0c6c(char *self)
{
    int a;
    int n;
    int m;

    if (func_0208e484(self + 0x4448) != 0) {
        a = func_ov095_02299a00(self + 0x384);
        n = func_ov095_0229c448(self + 0x384, a, 9);
        if (n == 0x112) {
            func_ov002_02208098(self, 0x10);
            func_ov002_0220a574(self + 0x4234);
            func_ov002_0220a4bc(self + 0x4234);
            if (func_ov112_0229f900(self) != 0) {
                func_ov112_0229fd20(self);
            }
            func_ov112_0229f8e4(self);
            func_ov112_0229fe60(self, 0x1000);
        } else {
            m = func_ov112_022a03ac(self, n);
            if (m == 1 && (data_021fbe40 & 1) != 0) {
                func_ov095_0229bf3c(self + 0x384);
                func_ov002_02208098(self, 9);
                func_ov095_0229c8e4(self + 0x384, a);
            } else if (m != 3) {
                if (m == 4) {
                    func_ov095_0229cce0(self + 0x384);
                } else {
                    func_ov112_0229f270(self);
                }
            }
        }
    }
}
