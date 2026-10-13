/* func_ov004_02226c08 @ 0x02226c08, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a, b, c, d;
} BIG4;
void func_ov004_02226c08(char *self, BIG4 v, u8 g, u8 h)
{
    *(int *) (self) = v.a;
    *(int *) (self + 4) = v.b;
    *(int *) (self + 8) = v.c;
    *(int *) (self + 0xc) = 0;
    *(int *) (self + 0x10) = v.d;
    *(u8 *) (self + 0x14) = g;
    *(u8 *) (self + 0x15) = h;
}
