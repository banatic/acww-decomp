/* talk_windows_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020aa19c @ 0x020aa19c, 0x8c bytes, Thumb
 * func_020aa180 @ 0x020aa180, 0x1a bytes, Thumb
 */

#include "cpp/main/Obj_020e404c.h"

typedef void (Obj_020e404c::*Pmf)();

extern int data_021f45ac;
extern Pmf data_020e3edc;
extern Pmf data_020e3ef4;
extern Pmf data_020e3f6c;
extern Pmf data_020e3f74;
extern Pmf data_021f45d0[4];

class UnkStruct_020aa180 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

class UnkStruct_020aa180_2 {
  public:
    char pad_00[0xc];
    UnkStruct_020aa180 sub;
};

extern "C" void func_020ac3f8(UnkStruct_020aa180 *sub);

extern "C" void func_020aa19c(Obj_020e404c *self)
{
    if (!(data_021f45ac & 1)) {
        data_021f45d0[0] = data_020e3f6c;
        data_021f45d0[1] = data_020e3f74;
        data_021f45d0[2] = data_020e3edc;
        data_021f45d0[3] = data_020e3ef4;
        data_021f45ac |= 1;
    }
    (self->*(data_021f45d0[self->unk_08]))();
    self->sub.vfunc_08();
}

extern "C" void func_020aa180(UnkStruct_020aa180_2 *self)
{
    self->sub.v3();
    func_020ac3f8(&self->sub);
}
