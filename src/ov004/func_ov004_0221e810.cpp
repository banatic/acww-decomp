/* func_ov004_0221e810 @ 0x0221e810, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0221e810;
typedef void (UnkStruct_0221e810::*PMF)(int);

extern PMF data_ov004_02253984;
extern PMF data_ov004_0225393c;

struct UnkStruct_0221e810 {
    u8 pad_00[0xc];
    u8 unk_0C;
};

extern "C" {

int func_ov004_0221e810(UnkStruct_0221e810 *self, int arg)
{
    static PMF tbl[2] = {data_ov004_02253984, data_ov004_0225393c};
    u8 i;

    i = self->unk_0C;
    if (i < 2) {
        (self->*tbl[i])(arg);
    }
    return 0;
}
}
