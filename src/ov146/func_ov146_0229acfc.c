/* func_ov146_0229acfc @ 0x0229acfc, 0xbc bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov002_0220b04c(u8 *);
extern void func_ov002_0220b06c(u8 *, int, int, int);
extern void func_0208aa70(u8 *);
extern void func_ov002_0220a580(u8 *);
extern void func_ov146_0229a0f8(u8 *);

void func_ov146_0229acfc(u8 *self)
{
    int i;
    int j;

    *(u16 *) (self + 0xac) = 0;
    *(self + 0xb2) = 3;
    *(self + 0xb0) = 9;
    *(self + 0xb1) = 8;
    func_ov002_0220b04c(self + 0x1ee8);
    func_ov002_0220b06c(self + 0x1ee8, 0x7f, 0x90, 0x10);
    func_0208aa70(self + 0x1ee8);
    *(self + 0xb5) = 0;
    func_ov002_0220a580(self + 0x1fb4);
    for (i = 0; i < 7; i++) {
        *(self + i + 0xbc) = 0x21;
        *(self + i + 0xc3) = 0xff;
    }
    for (j = 0; j < 0x20; j++) {
        *(self + j + 0xea) = 0x20;
        *(self + j + 0x10a) = 0;
    }
    func_ov146_0229a0f8(self);
    *(self + 0xb6) = 0x21;
    *(self + 0xb7) = 0xa;
    *(self + 0xb8) = 0;
    *(self + 0xb9) = 0xa;
    *(self + 0xbb) = 0x20;
}
