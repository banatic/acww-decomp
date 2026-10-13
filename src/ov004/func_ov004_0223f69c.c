/* func_ov004_0223f69c @ 0x0223f69c, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0223f69c {
    int x;
    int y;
    int z;
};

struct UnkStruct_0223f69c_2 {
    u8 pad_00[0x58];
    int lo[2];
    int hi[2];
    u8 pad_68[0x2c8 - 0x68];
    struct UnkStruct_0223f69c cur;
};

void func_ov004_0223f69c(void *self, struct UnkStruct_0223f69c_2 *o, struct UnkStruct_0223f69c *def)
{
    int *hi;
    int *lo;
    struct UnkStruct_0223f69c *cur;

    hi = o->hi;
    lo = o->lo;
    cur = &o->cur;

    if (cur->x < lo[0] || cur->x > hi[0]) {
        cur->x = def->x;
    }
    if (cur->z < lo[1] || cur->z > hi[1]) {
        cur->z = def->z;
    }
}
