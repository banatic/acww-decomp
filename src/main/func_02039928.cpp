/* func_02039928 @ 0x02039928, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_02039928 {
  public:
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
};

struct UnkStruct_02039928_2 {
    u8 pad_00[0x10];
    int unk_10;
    u8 pad1[0x2c - 0x14];
    int unk_2C;
    u8 pad_30[0x38 - 0x30];
    u8 unk_38;
    u8 unk_39;
    u8 pad_3A[0x50 - 0x3a];
    int unk_50;
    u8 pad_54[0x55 - 0x54];
    u8 unk_55;
    u8 pad_56[0x58 - 0x56];
    int unk_58;
};

struct UnkStruct_02039928_3 {
    u8 pad_00[0xc];
    int unk_0C;
    u8 pad1[0x54 - 0x10];
    UnkStruct_02039928 sub54;
    u8 pad2[0xa0 - 0x54 - sizeof(UnkStruct_02039928)];
    UnkStruct_02039928_2 *unk_A0;
};

extern "C" UnkStruct_02039928_2 *func_020a9034(int a, int b, int c);
extern int data_021c8c9c;
extern "C" void func_02051694(UnkStruct_02039928_2 *);

extern "C" void func_02039928(UnkStruct_02039928_3 *self)
{
    UnkStruct_02039928_2 *obj;

    if (self->unk_A0 != 0) {
        return;
    }

    self->unk_A0 = func_020a9034((self->unk_0C << 6) + 0xc0, 0x14, 2);
    if (self->unk_A0 == 0) {
        return;
    }

    self->unk_A0->unk_2C = 4;
    obj = self->unk_A0;
    obj->unk_10 = self->sub54.v3();

    if (data_021c8c9c == 0) {
        self->unk_A0->unk_50 = 3;
    } else {
        self->unk_A0->unk_50 = 2;
    }
    self->unk_A0->unk_58 = 1;
    self->unk_A0->unk_55 = 1;
    self->unk_A0->unk_39 = 0xf;
    self->unk_A0->unk_38 = 0xd;
    func_02051694(self->unk_A0);
}
