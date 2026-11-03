/* mailbox: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221e32c @ 0x0221e32c, 0xd8 bytes, Thumb
 * func_ov003_0221e254 @ 0x0221e254, 0xd8 bytes, Thumb
 * func_ov003_0221e1f4 @ 0x0221e1f4, 0x60 bytes, Thumb
 */

#include "types.h"

extern "C" int func_020b30e8(u16, unsigned int);

class UnkStruct_0221e32c {
  public:
    u8 pad_00[0x134];
    u8 unk_134;
    u8 pad_135;
    u16 unk_136;
    int method();
};

typedef int (UnkStruct_0221e32c::*PMF)();

extern PMF data_ov003_022393fc;
extern PMF data_ov003_0223940c;
extern PMF data_ov003_0223945c;
extern PMF data_ov003_02239454;
extern PMF data_ov003_022393c4;
extern PMF data_ov003_022393bc;
extern PMF data_ov003_022393b4;

class UnkStruct_0221e254 {};

typedef void (UnkStruct_0221e254::*TPMF)();

extern TPMF data_ov003_022393ec;
extern TPMF data_ov003_02239414;
extern TPMF data_ov003_02239424;
extern TPMF data_ov003_022393ac;
extern TPMF data_ov003_022393dc;
extern TPMF data_ov003_022393f4;
extern TPMF data_ov003_02239464;
extern "C" int func_02056f28(void *, int);
extern "C" void func_ov009_02262ef0(void *, int);

class UnkStruct_0221e1f4 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual void vf22();
    virtual void vf23();
    virtual void vf24();
    virtual int vf25();
};

extern "C" {
void func_02055060(void *p, int a, int b, int c, int d, int e);
int func_02055e00(void *p);
int func_ov009_02264cf8(void *p, int a);
void func_02056440(void *p, int a, int b, int c, int d, int e);
}

extern "C" int func_ov003_0221e32c(UnkStruct_0221e32c *self, unsigned int index)
{
    static PMF s_tbl[7] = {data_ov003_022393fc, data_ov003_0223940c, data_ov003_0223945c, data_ov003_02239454,
                           data_ov003_022393c4, data_ov003_022393bc, data_ov003_022393b4};

    if (index >= 7) {
        goto fail;
    }
    if ((self->*s_tbl[index])() == 0) {
        goto fail;
    }
    if (func_020b30e8(self->unk_136, index) == 0) {
        goto fail;
    }

    self->unk_134 = (u8) index;
    return 1;

fail:
    return 0;
}

extern "C" void func_ov003_0221e254(UnkStruct_0221e254 *self)
{
    static int guard;
    static TPMF tbl[7];

    if ((guard & 1) == 0) {
        tbl[0] = data_ov003_022393ec;
        tbl[1] = data_ov003_02239414;
        tbl[2] = data_ov003_02239424;
        tbl[3] = data_ov003_022393ac;
        tbl[4] = data_ov003_022393dc;
        tbl[5] = data_ov003_022393f4;
        tbl[6] = data_ov003_02239464;
        guard |= 1;
    }

    {
        unsigned char idx = ((unsigned char *) self)[0x134];
        if (idx < 7) {
            (self->*tbl[idx])();
        }
    }

    if (func_02056f28((char *) self + 0x2b8, 0x12)) {
        func_ov009_02262ef0((char *) self + 0x238, 0x7de);
    }
}

extern "C" int func_ov003_0221e1f4(UnkStruct_0221e1f4 *obj)
{
    int ret1;
    int ret2;
    int ret3;

    ret1 = obj->vf25();
    func_02055060((char *) obj + 0x13c, ret1, 1, 0x1000, 0, 0);
    ret2 = func_02055e00((char *) obj + 0x13c);
    ret3 = func_ov009_02264cf8(obj, 0);
    func_02056440((char *) obj + 0x2b8, ret2, ret3, 1, 0x1000, 0);
    return 1;
}
