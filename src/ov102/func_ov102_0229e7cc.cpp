/* func_ov102_0229e7cc @ 0x0229e7cc, 0xa8 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

class Sub218c {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
};

typedef struct UnkStruct_0229e7cc UnkStruct_0229e7cc;
struct UnkStruct_0229e7cc {
    unsigned char pad_00[0xcc];
    unsigned char unk_CC;
    unsigned char pad_CD[0xb2c - 0xcc - 1];
    unsigned char unk_B2C;
    unsigned char pad_B2D[0xb54 - 0xb2c - 1];
    unsigned char unk_B54;
    unsigned char pad_B55[0x218c - 0xb54 - 1];
    Sub218c sub;
    unsigned char pad4[0x2274 - 0x218c - sizeof(Sub218c)];
    unsigned char unk_2274;
    unsigned char pad_2275[0x24d0 - 0x2274 - 1];
    u32 unk_24D0;
    u32 unk_24D4;
};

extern int func_ov102_0229c2a8(UnkStruct_0229e7cc *self, int flag);
extern void func_ov102_0229cdb8(UnkStruct_0229e7cc *self);
extern void func_ov102_0229c3bc(UnkStruct_0229e7cc *self);
extern int func_0206fe54(int value);
extern void func_ov002_02209eb8(void *ptr);
extern void func_ov094_0229a7cc(void *ptr, int a, int b);
extern void func_ov094_0229a850(void *ptr, int a, int b);
extern void func_ov094_0229b738(void *ptr, int a, int b);
extern void func_ov094_02299d84(void *ptr, int a);

int func_ov102_0229e7cc(UnkStruct_0229e7cc *self)
{
    if (func_ov102_0229c2a8(self, 1) == 0) {
        return 1;
    }
    if (func_0206fe54(self->sub.f2()) != 0) {
        func_ov002_02209eb8(&self->unk_2274);
    }
    func_ov102_0229cdb8(self);
    if (func_ov102_0229c2a8(self, 0x80) != 0) {
        func_ov094_0229a7cc(&self->unk_CC, 0, self->unk_24D4);
        func_ov102_0229c3bc(self);
    }
    if (func_ov102_0229c2a8(self, 2) != 0) {
        func_ov094_0229a850(&self->unk_CC, 0, self->unk_24D0);
        func_ov094_0229b738(&self->unk_B2C, 0, self->unk_24D0);
        func_ov094_02299d84(&self->unk_B54, self->unk_24D0);
    }
    return 1;
}

#ifdef __cplusplus
}
#endif
