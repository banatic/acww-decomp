/* atm_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220c144 @ 0x0220c144, 0x8c bytes, Thumb
 * func_ov004_0220c0c8 @ 0x0220c0c8, 0x7c bytes, Thumb
 */

#include "cpp/ov004/Obj_ov004_0224fc4c.h"

extern "C" {
extern int data_ov004_0224fbf0[2];
extern int data_ov004_0224fc00[2];
extern int data_ov004_0224fc18[2];
}

class UnkStruct_0220c0c8 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    char pad_04[0x130];
    int unk_134;
};

extern "C" int func_ov004_0220c144(Obj_ov004_0224fc4c *obj, int idx)
{
    static int (Obj_ov004_0224fc4c::*pmf[3])() = {&Obj_ov004_0224fc4c::func_ov004_0220c0c4,
                                                  &Obj_ov004_0224fc4c::func_ov004_0220c078,
                                                  &Obj_ov004_0224fc4c::func_ov004_0220c050};
    if (idx < 3) {
        if ((obj->*pmf[idx])()) {
            obj->unk_134 = idx;
            return 1;
        }
    }
    return 0;
}

extern "C" void func_ov004_0220c0c8(UnkStruct_0220c0c8 *self)
{
    static void (UnkStruct_0220c0c8::*mtbl[3])() = {*reinterpret_cast<void (UnkStruct_0220c0c8::**)()>(data_ov004_0224fbf0),
                                                    *reinterpret_cast<void (UnkStruct_0220c0c8::**)()>(data_ov004_0224fc00),
                                                    *reinterpret_cast<void (UnkStruct_0220c0c8::**)()>(data_ov004_0224fc18)};
    int idx = self->unk_134;
    if (idx < 3) {
        (self->*(mtbl[idx]))();
    }
}
