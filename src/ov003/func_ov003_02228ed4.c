/* func_ov003_02228ed4 @ 0x02228ed4, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020f5958(void *self);

void *func_ov003_02228ed4(char *self)
{
    func_020f5958(self);
    *(int *) (self + 0x40) = 0;
    *(int *) (self + 0x44) = -1;
    *(int *) (self + 0x48) = 0;
    *(char *) (self + 0x78) = -1;
    *(u8 *) (self + 0x80) = 0;
    *(int *) (self + 0x7c) = 0;
    *(int *) (self + 0x84) = 0x1333;
    *(int *) (self + 0x88) = 0x1333;
    *(int *) (self + 0x8c) = 0x1333;
    *(u8 *) (self + 0x94) = 0;
    *(u16 *) (self + 0x96) = 0;
    *(u16 *) (self + 0x98) = 0;
    *(u16 *) (self + 0x9a) = 0;
    *(int *) (self + 0x9c) = -1;
    *(u8 *) (self + 0xa0) = 0;
    *(int *) (self + 0x54) = 0x1000;
    *(int *) (self + 0x58) = 0x1000;
    *(int *) (self + 0x5c) = 0x1000;
    return self;
}
