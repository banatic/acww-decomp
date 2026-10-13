/* func_ov004_0221df58 @ 0x0221df58, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221df58_2 {
    u8 pad_00[0x830];
    int handle;
};

struct UnkStruct_0221df58 {
    u8 pad_00[0x1a4];
    struct UnkStruct_0221df58_2 *sub;
};

extern int func_020984e8(void);
extern int func_02099870(int a);
extern int func_020804b8(int a, int b);

int func_ov004_0221df58(struct UnkStruct_0221df58 *self)
{
    if (self->sub != 0 && self->sub->handle != 0) {
        return func_020804b8(self->sub->handle, func_02099870(func_020984e8()));
    }
    return 0;
}
