/* func_ov003_022100a0 @ 0x022100a0, 0xa bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022100a0 {
    int a;
    int b;
};
void func_ov003_022100a0(u8 *d, struct UnkStruct_022100a0 *p)
{
    d[0] = (u8) p->a;
    d[1] = (u8) p->b;
}
