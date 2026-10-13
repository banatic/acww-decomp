/* func_ov004_02238698 @ 0x02238698, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov004_02239460(int, int);

void func_ov004_02238698(char *self)
{
    *(s16 *) (self + 0x208) = (s16) func_ov004_02239460(0x28, 0xc8);
    *(int *) (self + 0x20c) = (func_ov004_02239460(0x32, 0x4b) << 0xc) / 0x64;
    *(int *) (self + 0x110) = *(int *) (self + 0x20c);
    *(u8 *) (self + 0x20a) = (u8) func_ov004_02239460(1, 7);
    *(u8 *) (self + 0x210) = 0;
    *(int *) (self + 0x158) = 0;
    *(u8 *) (self + 0x211) = 4;
}
