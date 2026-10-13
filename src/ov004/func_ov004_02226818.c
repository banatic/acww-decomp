/* func_ov004_02226818 @ 0x02226818, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a, b, c, d, e;
} BIG5;
void func_ov004_02226818(char *self, BIG5 v, u8 f)
{
    *(int *) (self) = v.a;
    *(int *) (self + 4) = v.b;
    *(int *) (self + 8) = v.c;
    *(int *) (self + 0xc) = v.d;
    *(int *) (self + 0x10) = v.e;
    *(u8 *) (self + 0x14) = 0;
    *(u8 *) (self + 0x15) = f;
}
