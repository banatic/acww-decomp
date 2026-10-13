/* func_ov003_02210094 @ 0x02210094, 0xa bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02210094 {
    int a;
    int b;
};
void func_ov003_02210094(u8 *p, struct UnkStruct_02210094 *d)
{
    d->a = p[0];
    d->b = p[1];
}
