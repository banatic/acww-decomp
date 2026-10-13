/* func_ov003_02212818 @ 0x02212818, 0xa bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02212818 {
    int a;
    int b;
};
void func_ov003_02212818(u8 *d, struct UnkStruct_02212818 *p)
{
    d[0] = (u8) p->a;
    d[1] = (u8) p->b;
}
