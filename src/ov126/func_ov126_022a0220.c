/* func_ov126_022a0220 @ 0x022a0220, 0x5c bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov095_0229bcec(void *p1, void *p2, int p3, u8 *p4, u8 p5, u8 p6, int p7, int p8);
extern void func_ov126_022a0924(void *p, u8 b);

int func_ov126_022a0220(void *self, int param2)
{
    u8 local_b;

    local_b = ((u8 *) self)[0xa8];

    if (func_ov095_0229bcec((void *) ((char *) self + 0x19c), (void *) ((char *) self + 0x4248), param2, &local_b,
                            ((u8 *) self)[0xa6], ((u8 *) self)[0xaf], 0, 1)) {
        func_ov126_022a0924(self, local_b);
        return 1;
    } else {
        return 0;
    }
}
