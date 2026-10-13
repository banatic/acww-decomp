/* func_ov003_0221280c @ 0x0221280c, 0xa bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221280c {
    int a;
    int b;
};
void func_ov003_0221280c(u8 *p, struct UnkStruct_0221280c *d)
{
    d->a = p[0];
    d->b = p[1];
}
