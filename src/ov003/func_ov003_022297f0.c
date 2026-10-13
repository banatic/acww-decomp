/* func_ov003_022297f0 @ 0x022297f0, 0x84 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0204fdbc(int h);
extern void func_0209129c(int h);
extern void func_ov003_02229590(char *self, void *b);

void func_ov003_022297f0(char *self, void *b)
{
    func_0204fdbc(*(int *) (self + 0x44));
    *(int *) (self + 0x44) = -1;
    *(int *) (self + 0x40) = 0;
    *(char *) (self + 0x78) = -1;
    *(u8 *) (self + 0x80) = 0;
    *(u8 *) (self + 0xa0) = 0;
    *(int *) (self + 0x7c) = 0;
    *(int *) (self + 0x84) = 0x1333;
    *(int *) (self + 0x88) = 0x1333;
    *(int *) (self + 0x8c) = 0x1333;
    *(u16 *) (self + 0x96) = 0;
    *(u16 *) (self + 0x98) = 0;
    *(u16 *) (self + 0x9a) = 0;
    func_0209129c(*(int *) (self + 0x9c));
    *(int *) (self + 0x9c) = -1;
    if (*(u8 *) (self + 0x94)) {
        func_ov003_02229590(self, b);
    }
}
