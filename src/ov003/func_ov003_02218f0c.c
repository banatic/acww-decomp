/* func_ov003_02218f0c @ 0x02218f0c, 0xa bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02218f0c {
    int a;
    int b;
};
void func_ov003_02218f0c(u8 *d, struct UnkStruct_02218f0c *p)
{
    d[0] = (u8) p->a;
    d[1] = (u8) p->b;
}
