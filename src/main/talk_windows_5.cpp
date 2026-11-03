/* talk_windows_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020aa6b4 @ 0x020aa6b4, 0x8c bytes, Thumb
 * func_020aa698 @ 0x020aa698, 0x1a bytes, Thumb
 */

#include "cpp/main/Obj_020e406c.h"

typedef void (Obj_020e406c::*Pmf)();

extern int data_021f45a4;
extern Pmf data_020e3f24;
extern Pmf data_020e3f2c;
extern Pmf data_020e3f34;
extern Pmf data_020e3f3c;
extern Pmf data_021f45f0[4];

class UnkStruct_020aa698 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

class UnkStruct_020aa698_2 {
  public:
    char pad_00[0xc];
    UnkStruct_020aa698 sub;
};

extern "C" void func_020ac3f8(UnkStruct_020aa698 *sub);

extern "C" void func_020aa6b4(Obj_020e406c *self)
{
    if (!(data_021f45a4 & 1)) {
        data_021f45f0[0] = data_020e3f3c;
        data_021f45f0[1] = data_020e3f34;
        data_021f45f0[2] = data_020e3f24;
        data_021f45f0[3] = data_020e3f2c;
        data_021f45a4 |= 1;
    }
    (self->*(data_021f45f0[self->unk_08]))();
    self->sub.vfunc_08();
}

extern "C" void func_020aa698(UnkStruct_020aa698_2 *self)
{
    self->sub.v3();
    func_020ac3f8(&self->sub);
}
