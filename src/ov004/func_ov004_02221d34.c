/* func_ov004_02221d34 @ 0x02221d34, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern unsigned short data_020c80f8;
extern void func_02019c90(void *, int, int, int);
int func_ov004_02221d34(u8 *self)
{
    if (*(int *) (self + 0x89c) == 1) {
        func_02019c90(self + 0x564, 2, 0, data_020c80f8);
    }
    return 1;
}
