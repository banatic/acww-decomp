/* func_02066f8c @ 0x02066f8c, 0x16c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_02066f8c_2 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual signed char *f3(); // vtable offset 0x0c
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void f18();
    virtual void f19();
    virtual void f20();
    virtual void f21();
    virtual void f22();
    virtual void f23();
    virtual void f24();
    virtual void f25();
    virtual int f26(); // vtable offset 0x68
};

struct UnkStruct_02066f8c {
    u8 pad_00[0x64];
    void *unk_64;
};

struct UnkStruct_02066f8c_3 {
    u8 pad_00[0x0c];
    u32 unk_0C; // 0x0c
    u8 pad_10[0x04];
    u32 unk_14; // 0x14
    u8 pad_18[0x04];
    u8 sub_1c[0x80];              // 0x1c
    u32 unk_9C;                   // 0x9c
    u8 pad_A0[0x684 - 0xa0];      // 0xa0 .. 0x683
    u8 sub_684[1];                // 0x684
    u8 pad_685[0x14a8 - 0x685];   // 0x685 .. 0x14a7
    UnkStruct_02066f8c_2 *vobj;   // 0x14a8
    u32 unk_14AC;                 // 0x14ac
    u8 pad_14B0[0x1a2c - 0x14b0]; // 0x14b0 .. 0x1a2b
    u8 sub_1a2c[1];               // 0x1a2c
    u8 pad_1A2D[0x1e98 - 0x1a2d]; // 0x1a2d .. 0x1e97
    u8 unk_1E98;                  // 0x1e98
    u8 unk_1E99;                  // 0x1e99
};

extern signed short data_020def1c[];
extern UnkStruct_02066f8c *data_020ccf94;

extern "C" void func_02067e68(void *self);
extern "C" void func_02067218(void *self);
extern "C" void func_020671fc(void *self);
extern "C" int func_020a8278(void *p);
extern "C" UnkStruct_02066f8c_2 *func_020668d4(void *obj);
extern "C" void *func_020668c8(void *obj);
extern "C" int func_020668cc(void *obj);
extern "C" int func_02068e78(void *sub, int a, int b, void *c, int d);
extern "C" void func_02068a00(void *sub, int a);
extern "C" void func_02068e04(void *sub);
extern "C" void func_02068db0(void *sub);
extern "C" void func_02068d98(void *sub);
extern "C" void func_02068e44(void *sub);
extern "C" void func_02068d74(void *sub, int val);
extern "C" void func_02068d38(void *sub);
extern "C" void func_020675e0(void *self);
extern "C" void func_0206c154(void *sub);
extern "C" void func_020398d4(void *p);
extern "C" void func_0200467c(int cmd);
extern "C" void func_02036488(void *p);

extern unsigned char data_021c526c[];

extern "C" void func_02066f8c(UnkStruct_02066f8c_3 *self)
{
    int r4;
    int r6;
    int r7;
    signed char *tmp1;
    void *tmp2;
    int r2;

    func_02067e68(self);

    if (self->unk_14 != 4) {
        r4 = 1;
    } else {
        r4 = 0;
    }

    if (r4 != 0) {
        func_02067218(self);
    } else {
        func_020671fc(self);
    }

    r6 = func_020a8278(&self->unk_14AC);

    tmp1 = func_020668d4(self->vobj)->f3();
    tmp2 = func_020668c8(self->vobj);
    r7 = (self->vobj->f26() == 0) ? 1 : 0;
    r2 = func_020668cc(self->vobj);

    if (r2 == 0 && r6 == 0 && tmp1[0] == 0 && tmp1[1] == 0) {
        r6 = 5;
    }

    func_02068e78(&self->sub_1c, r6, r2, tmp2, r7);
    func_02068a00(&self->sub_1a2c, r6);
    func_02068e04(&self->sub_1c);
    func_02068db0(&self->sub_1c);
    func_02068d98(&self->sub_1c);
    func_02068e44(&self->sub_1c);

    self->unk_0C = 5;
    self->unk_9C = data_020def1c[self->unk_0C];
    func_02068d74(&self->sub_1c, self->unk_9C);
    func_02068d38(&self->sub_1c);
    func_020675e0(self);
    func_0206c154(&self->sub_684);

    if (data_020ccf94) {
        func_020398d4(data_020ccf94->unk_64);
    }

    if (self->unk_1E99 == 0) {
        func_0200467c(9);
    }

    if (self->unk_1E98 == 0 && self->unk_14 != 1 && self->unk_14 != 2 && self->unk_14 != 3) {
        func_02036488((char *) (*(void **) data_021c526c) + 0x1c4);
    }

    if (r4 != 0) {
        self->unk_14 = 4;
    }
}
