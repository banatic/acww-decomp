/* check_in_gate_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0222d1e0 @ 0x0222d1e0, 0xa0 bytes, Thumb
 * func_ov004_0222d154 @ 0x0222d154, 0x8c bytes, Thumb, emits _ZN18Obj_ov004_02254e4c19func_ov004_0222d154Ev
 */

#include "types.h"
#include "cpp/ov004/Obj_ov004_02254e4c.h"

struct UnkStruct_0222d1e0;

typedef int (UnkStruct_0222d1e0::*PMF)(void);

struct UnkStruct_0222d1e0 {
    u8 pad_00[0x24c];
    u8 unk_24C;
};

extern PMF data_ov004_02254d84;
extern PMF data_ov004_02254d8c;
extern PMF data_ov004_02254db4;
extern PMF data_ov004_02254da4;

typedef void (Obj_ov004_02254e4c::*Pmf)(void);

extern "C" int func_ov004_0222d1e0(UnkStruct_0222d1e0 *self, unsigned int i)
{
    static PMF tbl[4] = {data_ov004_02254d84, data_ov004_02254d8c, data_ov004_02254db4, data_ov004_02254da4};
    if (i < 4) {
        if ((self->*tbl[i])() != 0) {
            self->unk_24C = i;
            return 1;
        }
        return 0;
    }
    return 0;
}

void Obj_ov004_02254e4c::func_ov004_0222d154()
{
    static Pmf tbl[] = {&Obj_ov004_02254e4c::func_ov004_0222d0bc, &Obj_ov004_02254e4c::func_ov004_0222cfbc,
                        &Obj_ov004_02254e4c::func_ov004_0222cf18, &Obj_ov004_02254e4c::func_ov004_0222ce1c};
    unsigned char i = unk_24c;
    if (i < 4) {
        (this->*(tbl[i]))();
    }
}
