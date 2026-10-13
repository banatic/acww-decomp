/* func_ov004_0221ed0c @ 0x0221ed0c, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221ed0c;
typedef int (UnkStruct_0221ed0c::*PMF)(void);

struct UnkStruct_0221ed0c {
    u8 pad_00[0x898];
    PMF unk_898;
};

extern "C" {

int func_ov004_0221ed0c(UnkStruct_0221ed0c *self)
{
    int r;

    r = 1;
    if (self->unk_898) {
        r = (self->*(self->unk_898))();
    }
    return r;
}
}
