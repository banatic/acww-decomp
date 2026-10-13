/* func_0206dc1c @ 0x0206dc1c, 0xce bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0206dc1c;
struct UnkStruct_0206dc1c_2;

typedef struct UnkStruct_0206dc1c UnkStruct_0206dc1c;
typedef struct UnkStruct_0206dc1c_2 UnkStruct_0206dc1c_2;

struct UnkStruct_0206dc1c {
    u8 pad_00[0x2c];
    u32 unk_2C;
    u8 pad1[0x8];
    u8 unk_38;
    u8 unk_39;
    u8 pad_3A[0x16];
    u32 unk_50;
    u8 pad_54[0x1];
    u8 unk_55;
};

struct UnkStruct_0206dc1c_2 {
    u8 pad_00[0x64];
    UnkStruct_0206dc1c *unk_64;
    u16 unk_68;
    u8 unk_6A;
    u8 unk_6B;
    u8 pad1[0x1];
    u8 unk_6D;
    u8 unk_6E;
    u8 unk_6F;
    u8 unk_70;
    u8 unk_71;
};

extern UnkStruct_0206dc1c *func_020a9034(u16 a, int b, int c);
extern void func_020515cc(UnkStruct_0206dc1c *a, int b, int c, u8 d, u8 e, int f, int g, u8 h, u8 i);
extern void func_02051608(UnkStruct_0206dc1c *a, int b, int c, u8 d, u8 e);

void func_0206dc1c(UnkStruct_0206dc1c_2 *self)
{
    int arg1;
    int arg2;
    u8 f6e_val;

    if (self->unk_64 != 0) {
        return;
    }

    self->unk_64 = func_020a9034(self->unk_68, 20, 2);
    if (self->unk_64 == 0) {
        return;
    }

    self->unk_64->unk_2C = self->unk_6A;

    if (self->unk_6B != 0) {
        self->unk_64->unk_50 = 1;
    } else {
        self->unk_64->unk_50 = 2;
    }

    self->unk_64->unk_55 = 0;
    self->unk_64->unk_39 = 0;
    self->unk_64->unk_38 = 0xf;

    if (self->unk_6F != 0) {
        arg1 = 0xb;
        arg2 = 0;
    } else {
        arg1 = 0xe;
        arg2 = 0xd;
    }

    f6e_val = self->unk_6E;
    if (f6e_val != 0) {
        if (self->unk_71 != 0) {
            func_020515cc(self->unk_64, arg1, arg2, self->unk_6D, f6e_val, 12, 0, self->unk_70, self->unk_71);
        } else {
            func_02051608(self->unk_64, arg1, arg2, self->unk_6D, f6e_val);
        }
    } else {
        if (self->unk_71 != 0) {
            func_02051608(self->unk_64, 12, 0, self->unk_70, self->unk_71);
        }
    }
}
