/* func_ov004_022362ec @ 0x022362ec, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022362ec;
typedef void (UnkStruct_022362ec::*PMF)(void);
struct UnkStruct_022362ec {};

struct UnkStruct_022362ec_2 {
    PMF unk_00;
    PMF unk_08;
};

extern "C" {
extern UnkStruct_022362ec_2 data_ov004_02259424[];
extern u8 data_ov004_022593a0;
}

extern "C" void func_ov004_022362ec(UnkStruct_022362ec *self)
{
    (self->*(data_ov004_02259424[data_ov004_022593a0].unk_08))();
}
