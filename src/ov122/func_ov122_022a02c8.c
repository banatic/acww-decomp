/* func_ov122_022a02c8 @ 0x022a02c8, 0xe8 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern int func_0208e4bc(void *p);
extern int func_0208e484(void *p);
extern int func_ov002_0220a700(void *p);
extern int func_ov002_0220a6e0(void *p);
extern int func_ov002_0220a768(void *p, int x);
extern int func_ov002_0220a72c(void *p, int x);
extern void func_ov002_0220a0b4(void *p, int x, int y);
extern void func_ov122_022a0e04(void *p);
extern void func_ov122_0229effc(void *p);
extern void func_ov122_022a1e40(void *p, int x);
extern void func_ov002_022080a0(void *p, int x);
extern void func_ov122_022a15b8(void *p, int x, int y);
extern void func_ov122_0229f2d0(void *p);

void func_ov122_022a02c8(void *self)
{
    if (func_0208e4bc((u8 *) self + 0x4058) != 0 && func_0208e484((u8 *) self + 0x4058) == 0) {
        return;
    }
    if (func_ov002_0220a700((u8 *) self + 0x4698) != 0) {
        if (func_0208e4bc((u8 *) self + 0x4058) == 0) {
            return;
        }
        {
            int a = func_ov002_0220a6e0((u8 *) self + 0x4698);
            int b = func_ov002_0220a768((u8 *) self + 0x4698, -1);
            func_ov002_0220a0b4((u8 *) self + 0x4058, a + b, a + func_ov002_0220a72c((u8 *) self + 0x4698, -1));
        }
        return;
    }
    switch (((u8 *) self)[0xb8]) {
        case 0:
            ((u8 *) self)[0xb5] = 0xc;
            func_ov122_022a0e04(self);
            break;
        case 1:
            ((u8 *) self)[0xb5] = 6;
            func_ov122_0229effc(self);
            func_ov122_022a0e04(self);
            break;
        case 3:
            func_ov122_022a1e40(self, 0);
            break;
        case 4:
            ((u8 *) self)[0x8c] = 8;
            func_ov002_022080a0(self, 1);
            func_ov122_022a15b8(self, 1, 1);
            break;
    }
    func_ov122_0229f2d0(self);
}
