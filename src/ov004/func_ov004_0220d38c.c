/* func_ov004_0220d38c @ 0x0220d38c, 0xa bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 a;
    volatile u8 b;
} UnkStruct_0220d38c;
void func_ov004_0220d38c(UnkStruct_0220d38c *p)
{
    p->b = 0;
    p->a = p->b;
}
