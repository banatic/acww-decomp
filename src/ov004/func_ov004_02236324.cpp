/* func_ov004_02236324 @ 0x02236324, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02236324;
typedef void (UnkStruct_02236324::*PMF)(void);
struct UnkStruct_02236324 {};

struct UnkStruct_02236324_2 {
    PMF unk_00;
    PMF unk_08;
};

extern "C" {
extern UnkStruct_02236324_2 data_ov004_02259424[];
extern u8 data_ov004_022593a0;
}

extern "C" void func_ov004_02236324(UnkStruct_02236324 *self)
{
    (self->*(data_ov004_02259424[data_ov004_022593a0].unk_00))();
}
