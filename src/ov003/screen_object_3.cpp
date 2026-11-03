/* screen_object_3: 2 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221b8b8 @ 0x0221b8b8, 0x8c bytes, Thumb, emits _ZN18Obj_ov003_0223843419func_ov003_0221b8b8Ei
 * func_ov003_0221b83c @ 0x0221b83c, 0x7c bytes, Thumb
 */

#include "cpp/ov003/Obj_ov003_02238434.h"

struct UnkStruct_0221b83c {
    char pad_00[0x2b4];
    int unk_2B4;
    void f0();
    void f1();
    void f2();
};

extern void (UnkStruct_0221b83c::*data_ov003_022383e4)();
extern void (UnkStruct_0221b83c::*data_ov003_022383fc)();
extern void (UnkStruct_0221b83c::*data_ov003_0223840c)();

int Obj_ov003_02238434::func_ov003_0221b8b8(int state)
{
    static int (Obj_ov003_02238434::*table[3])() = {&Obj_ov003_02238434::func_ov003_0221b838,
                                                    &Obj_ov003_02238434::func_ov003_0221b818,
                                                    &Obj_ov003_02238434::func_ov003_0221b808};
    if (state < 3) {
        if ((this->*table[state])()) {
            state_2b4 = state;
            return 1;
        }
    }
    return 0;
}

extern "C" void func_ov003_0221b83c(UnkStruct_0221b83c *p)
{
    static void (UnkStruct_0221b83c::*pmf[3])() = {data_ov003_022383e4, data_ov003_022383fc, data_ov003_0223840c};
    int idx = p->unk_2B4;
    if (idx < 3) {
        (p->*pmf[idx])();
    }
}
