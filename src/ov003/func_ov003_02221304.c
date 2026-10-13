/* func_ov003_02221304 @ 0x02221304, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u32 data_ov003_0223cfe4;
extern void func_ov003_022213f8(u32 *data, u32 a0, u32 *a, u32 *b, u32 z1, u32 a1, u32 z2, u32 z3);

void func_ov003_02221304(u32 p0, u32 p1, u32 *p2, u32 *p3)
{
    u32 a[2];
    u32 b[3];

    b[0] = p3[0];
    b[1] = p3[1];
    b[2] = p3[2];
    a[0] = p2[0];
    a[1] = p2[1];
    func_ov003_022213f8(&data_ov003_0223cfe4, p0, a, b, 0, p1, 0, 0);
}
