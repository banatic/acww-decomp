/* mailbox_4: 2 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221e580 @ 0x0221e580, 0xa8 bytes, Thumb, emits _ZN18Obj_ov003_0223948c19func_ov003_0221e580Ei
 * func_ov003_0221e4e8 @ 0x0221e4e8, 0x98 bytes, Thumb
 */

#include "cpp/ov003/Obj_ov003_0223948c.h"

struct ClassType;

typedef void (ClassType::*PMF)();

struct ClassType {
    char pad_00[0x2b4];
    int index;
};

extern PMF data_ov003_0223941c;
extern PMF data_ov003_022393cc;
extern PMF data_ov003_022393d4;
extern PMF data_ov003_02239404;
extern PMF data_ov003_022393e4;

int Obj_ov003_0223948c::func_ov003_0221e580(int state)
{
    typedef int (Obj_ov003_0223948c::*PMF)();
    static PMF table[5] = {&Obj_ov003_0223948c::func_ov003_0221e4e4, &Obj_ov003_0223948c::func_ov003_0221e4a4,
                           &Obj_ov003_0223948c::func_ov003_0221e46c, &Obj_ov003_0223948c::func_ov003_0221e45c,
                           &Obj_ov003_0223948c::func_ov003_0221e424};
    if (state < 5) {
        if ((this->*table[state])() != 0) {
            state_2b4 = state;
            return 1;
        }
    }
    return 0;
}

extern "C" void func_ov003_0221e4e8(ClassType *obj)
{
    static PMF pmf_arr[5] = {data_ov003_0223941c, data_ov003_022393cc, data_ov003_022393d4, data_ov003_02239404,
                             data_ov003_022393e4};
    if (obj->index >= 5) {
        return;
    }
    (obj->*pmf_arr[obj->index])();
}
