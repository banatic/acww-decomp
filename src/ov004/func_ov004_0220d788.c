/* func_ov004_0220d788 @ 0x0220d788, 0x42 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0220d788 {
    u8 pad_00[4];
};

extern void *func_ov004_0220d7f0(struct UnkStruct_0220d788 *self, u32 i);
extern int func_ov004_0220d94c(void *p);
extern void func_ov004_0220d904(void *p, int a, int b);

int func_ov004_0220d788(struct UnkStruct_0220d788 *self, int a, int b)
{
    u32 i;

    for (i = 0; i < 4; i++) {
        if (!func_ov004_0220d94c(func_ov004_0220d7f0(self, i))) {
            func_ov004_0220d904(func_ov004_0220d7f0(self, i), a, b);
            return 1;
        }
    }
    return 0;
}
