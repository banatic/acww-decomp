/* func_ov004_0221132c @ 0x0221132c, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    char pad_00[0xc];
    u16 h;
} UnkStruct_0221132c;
int func_ov004_0221132c(UnkStruct_0221132c *p)
{
    if (p != 0) {
        int t = (p->h == 0x3a) ? 1 : 0;
        if (t) {
            return 1;
        }
        return 0;
    }
    return 0;
}
