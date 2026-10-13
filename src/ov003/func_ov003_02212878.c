/* func_ov003_02212878 @ 0x02212878, 0xa bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02212878 {
    int a;
    int b;
};
void func_ov003_02212878(u8 *d, struct UnkStruct_02212878 *p)
{
    d[0] = (u8) p->a;
    d[1] = (u8) p->b;
}
