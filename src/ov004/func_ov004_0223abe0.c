/* func_ov004_0223abe0 @ 0x0223abe0, 0x8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0223abe0 {
    u8 pad_00[0x18];
    unsigned int lo : 12;
    unsigned int mid : 16;
    unsigned int hi : 4;
};

int func_ov004_0223abe0(struct UnkStruct_0223abe0 *self)
{
    return self->mid;
}
