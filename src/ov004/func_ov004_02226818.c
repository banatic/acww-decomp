/* func_ov004_02226818 @ 0x02226818, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a, b, c;
} Triple;
void func_ov004_02226818(char *self, Triple v, int setting, int extent, u8 f)
{
    *(int *) (self) = v.a;
    *(int *) (self + 4) = v.b;
    *(int *) (self + 8) = v.c;
    *(int *) (self + 0xc) = setting;
    *(int *) (self + 0x10) = extent;
    *(u8 *) (self + 0x14) = 0;
    *(u8 *) (self + 0x15) = f;
}
