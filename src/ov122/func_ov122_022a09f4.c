/* func_ov122_022a09f4 @ 0x022a09f4, 0xdc bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u16 data_021fbe40;

extern int func_0208e484(void *p);
extern int func_ov095_02299a00(void *p);
extern int func_ov095_0229c448(void *p, int a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a574(void *p);
extern void func_ov002_0220a4bc(void);
extern int func_ov122_0229f958(void *self);
extern void func_ov122_0229f940(void *self);
extern void func_ov122_022a15b8(void *self, int a, int b);
extern void func_ov122_0229efd8(void *self, int a);
extern int func_ov122_022a0be4(void *self, int n);
extern void func_ov095_0229bf3c(void *p);
extern void func_ov095_0229c8e4(void *p, int a);
extern void func_ov095_0229cce0(void *p);
extern void func_ov122_0229f170(void *self);

void func_ov122_022a09f4(char *self)
{
    int a;
    int n;
    int m;

    if (func_0208e484(self + 0x4058) != 0) {
        a = func_ov095_02299a00(self + 0xc0);
        n = func_ov095_0229c448(self + 0xc0, a, 9);
        if (n == 0x112) {
            func_ov002_02208098((void *) (self), 0x10);
            func_ov002_0220a574(self + 0x4010);
            // clang-format off
            asm {
                ldr r0, =0x4010
                add r0, self, r0
            }
            // clang-format on
            func_ov002_0220a4bc();
            if (func_ov122_0229f958(self) != 0) {
                func_ov122_0229f940(self);
                func_ov122_022a15b8(self, 1, 1);
            } else {
                func_ov122_0229f940(self);
            }
            func_ov122_0229efd8(self, 0x200);
        } else {
            m = func_ov122_022a0be4(self, n);
            if (m == 1 && (data_021fbe40 & 1) != 0) {
                func_ov095_0229bf3c(self + 0xc0);
                func_ov002_02208098((void *) (self), 9);
                func_ov095_0229c8e4(self + 0xc0, a);
            } else if (m != 3) {
                if (m == 4) {
                    func_ov095_0229cce0(self + 0xc0);
                } else {
                    func_ov122_0229f170(self);
                }
            }
        }
    }
}
