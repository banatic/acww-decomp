/* func_0208e05c @ 0x0208e05c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" {

class UnkStruct_0208e05c_2 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

struct UnkStruct_0208e05c_3 {
    u8 pad_00[0x10];
    u32 unk_10;
    u8 pad1[0x2c - 0x14];
    u32 unk_2C;
    u8 pad2[0x38 - 0x30];
    u8 unk_38;
    u8 unk_39;
    u8 pad_3A[0x50 - 0x3a];
    u32 unk_50;
    u8 pad_54[0x55 - 0x54];
    u8 unk_55;
};

struct UnkStruct_0208e05c {
    u8 pad_00[0xc];
    u32 unk_0C;
    u8 pad1[0x38 - 0x10];
    UnkStruct_0208e05c_2 sub;
    u8 pad2[0x6c - 0x3c];
    UnkStruct_0208e05c_3 *unk_6C;
};

extern UnkStruct_0208e05c_3 *func_020a9034(int size, int a, int b);
extern void func_02051694(UnkStruct_0208e05c_3 *obj);
}

extern "C" void func_0208e05c(UnkStruct_0208e05c *self)
{
    if (self->unk_6C != 0) {
        return;
    }

    unsigned int flag = (self->unk_0C == 4) ? 1 : 0;
    int size;
    if (flag) {
        size = 0x1c8;
    } else {
        size = (self->unk_0C << 6) + 0xc0;
    }
    u8 mode = flag ? 0xe : 0xf;

    UnkStruct_0208e05c_3 *obj = func_020a9034(size, 0x14, 2);
    self->unk_6C = obj;
    if (self->unk_6C == 0) {
        return;
    }

    self->unk_6C->unk_2C = 4;
    UnkStruct_0208e05c_3 *tmp = self->unk_6C;
    tmp->unk_10 = self->sub.m3();
    self->unk_6C->unk_50 = 2;
    self->unk_6C->unk_55 = 1;
    self->unk_6C->unk_39 = mode;
    self->unk_6C->unk_38 = 0xd;
    func_02051694(self->unk_6C);
}
