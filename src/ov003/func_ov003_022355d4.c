/* func_ov003_022355d4 @ 0x022355d4, 0x118 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_02234d70(void *self);
extern int func_ov003_02234984(void *self);
extern void func_020550e4(void *p, int a);
extern void func_ov003_02231104(void *self);
extern int func_ov003_0223141c(void *p);
extern void func_02056fcc(void *p, int a, int b, int c, int d);
extern int func_020644cc(int n);

void func_ov003_022355d4(char *self)
{
    s8 k;
    u32 v;

    func_ov003_02234d70(self);
    if (func_ov003_02234984(self) == 0) {
        k = *(s8 *) (self + 0x24d);
        if (k == 0xa || k == 0x33) {
            if (((u32) * (int *) (self + 0xf4) << 4) >> 16 != 0) {
                func_020550e4(self + 0x50, 0);
            }
            func_ov003_02231104(self);
        } else if (k != 0x33) {
            if (func_ov003_0223141c(self + 0x204) == 0) {
                *(u8 *) (self + 0x254) = 0xfe;
            }
            if (((u32) * (int *) (self + 0xf0) << 4) >> 16 < 0xc) {
                func_02056fcc(self + 0xec, 0x11, 1, 0x1000, 9);
            } else if (((u32) * (int *) (self + 0xf4) << 4) >> 16 == 0x10) {
                if (func_020644cc(0x64) > 0x5f) {
                    func_02056fcc(self + 0xec, 0x11, 1, 0x1000, 9);
                }
            }
        }
    } else {
        *(u8 *) (self + 0x251) = 0x13;
        *(int *) (self + 0x220) = *(int *) (self + 0x228);
        *(short *) (self + 0x244) = (func_020644cc(6) + 7) * 0x14;
        k = *(s8 *) (self + 0x24d);
        if (k != 0xa && k != 0x33) {
            func_02056fcc(self + 0xec, 9, 0, *(int *) (self + 0x21c), 0);
        } else {
            func_020550e4(self + 0x50, 1);
        }
    }
}
