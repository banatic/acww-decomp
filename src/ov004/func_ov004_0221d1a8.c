/* func_ov004_0221d1a8 @ 0x0221d1a8, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221d1a8 {
    u8 pad_00[0x618];
    u8 sub[0x898 - 0x618];
    int phase;
};

extern int func_02014868(void *p);

int func_ov004_0221d1a8(struct UnkStruct_0221d1a8 *self)
{
    if (func_02014868(&self->sub)) {
        return 0;
    }
    if (self->phase <= 3) {
        return 1;
    }
    return 0;
}
