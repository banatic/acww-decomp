/* func_ov004_02244be0 @ 0x02244be0, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02244be0 {
    u8 pad_00[0x24];
    u8 sub[0x196 - 0x24];
    signed char id;
};

extern int func_ov004_02244ae4(int id, int arg1);
extern void func_020042a0(void *p, int a);
extern void func_02004290(void *p, int a);

int func_ov004_02244be0(struct UnkStruct_02244be0 *self, int mode)
{
    int r;

    r = func_ov004_02244ae4(self->id, mode);
    if (r >= 0) {
        if (mode == 1) {
            func_020042a0(&self->sub, r);
        } else {
            func_02004290(&self->sub, r);
        }
        return 1;
    }
    return 0;
}
