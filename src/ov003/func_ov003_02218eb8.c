/* func_ov003_02218eb8 @ 0x02218eb8, 0xa bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02218eb8 {
    int a;
    int b;
};
void func_ov003_02218eb8(u8 *d, struct UnkStruct_02218eb8 *p)
{
    d[0] = (u8) p->a;
    d[1] = (u8) p->b;
}
