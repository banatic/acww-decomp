/* func_ov003_0220d5d8 @ 0x0220d5d8, 0x9c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_0220d5d8 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23(void *arg);

    u8 pad_04[0x2d4];
    u32 lo : 12;
    u32 idx : 16;
    u32 hi : 4;
    u8 pad_2DC[0x428];
    u32 unk_704;
    u8 pad_708[0xf8];
    u32 unk_800;
    u8 pad_804[0x1e];
    u16 unk_822;
    u8 unk_824;
    u8 pad_825[0xb];
    u32 unk_830;
    u32 unk_834;
    u32 unk_838;
};

extern "C" void func_02010f5c(UnkStruct_0220d5d8 *self);
extern "C" unsigned int *func_0200f27c(UnkStruct_0220d5d8 *self, int param);
extern "C" void func_0200f268(UnkStruct_0220d5d8 *self, int param);
extern "C" int func_ov003_0222c214(u32 value);

extern "C" void func_ov003_0220d5d8(UnkStruct_0220d5d8 *self)
{
    func_02010f5c(self);
    if (self->unk_704 == 0x8f) {
        int idx = self->idx;
        if (idx >= 6 && idx <= 25) {
            func_0200f27c(self, 0xd);
            self->v23(&self->unk_824);
            self->unk_822 = 0x1520;
            int val = (idx - 6) * 0x333;
            if (idx >= 11) {
                val = 0x1000;
            }
            self->unk_830 = val;
            self->unk_834 = val;
            self->unk_838 = val;
            if (idx == 25) {
                func_0200f268(self, 0xd);
                func_ov003_0222c214(self->unk_800);
            }
        }
    }
}