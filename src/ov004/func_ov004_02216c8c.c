/* func_ov004_02216c8c @ 0x02216c8c, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02216c8c {
    u8 pad_00[4];
};

extern int func_ov004_02217230(struct UnkStruct_02216c8c *self);
extern int func_ov004_0222c00c(int *p);
extern int func_02052738(struct UnkStruct_02216c8c *self, int a, int b, int c);

int func_ov004_02216c8c(struct UnkStruct_02216c8c *self)
{
    int v;

    v = func_ov004_02217230(self);
    if (v != -1) {
        if (func_ov004_0222c00c(&v)) {
            return func_02052738(self, 3, 0xff, 1);
        }
        return 0;
    }
    return func_02052738(self, 3, 0xff, 1);
}
