/* func_ov003_02212824 @ 0x02212824, 0xa bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02212824 {
    int a;
    int b;
};
void func_ov003_02212824(u8 *d, struct UnkStruct_02212824 *p)
{
    d[0] = (u8) p->a;
    d[1] = (u8) p->b;
}
