/* field_label_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b8b88 @ 0x020b8b88, 0x9c bytes, Thumb
 * func_020b8b74 @ 0x020b8b74, 0x12 bytes, Thumb
 */

#include "cpp/main/Base_020b8b88.h"

extern "C" void func_020b8af0(Base_020b8b88 *self);

typedef void (Base_020b8b88::*MFN)();

extern int data_021f6af0;
extern MFN data_020e5820;
extern MFN data_020e5828;
extern MFN data_020e5830;
extern MFN data_020e5838;
extern MFN data_021f6b00[4];

class UnkStruct_020b8b74 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
};

class UnkStruct_020b8b74_2 {
  public:
    char pad_00[8];
    UnkStruct_020b8b74 sub;
};

extern "C" void func_020b8b88(Base_020b8b88 *self)
{
    if (!(data_021f6af0 & 1)) {
        data_021f6b00[0] = data_020e5830;
        data_021f6b00[1] = data_020e5820;
        data_021f6b00[2] = data_020e5838;
        data_021f6b00[3] = data_020e5828;
        data_021f6af0 |= 1;
    }
    func_020b8af0(self);
    (self->*data_021f6b00[self->index])();
    self->flag = 0;
    self->sub.vfunc_0c();
}

extern "C" void func_020b8b74(UnkStruct_020b8b74_2 *self)
{
    self->sub.v2();
}
