/* func_02003564 @ 0x02003564, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Elem {
    u8 pad_00[8];
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
};

struct UnkStruct_02003564 {
    u32 unk_00;
    u8 pad_04[0xc - 0x4];
    u16 unk_0C;
    u8 pad_0E[0x50 - 0xe];
    u32 unk_50;
    u32 unk_54;
    struct UnkStruct_02003564 *unk_58;
    u32 unk_5C;
    u32 unk_60;
    u32 unk_64;
    u8 pad_68[0x8c - 0x68];
    s16 unk_8C;
    s16 unk_8E;
    s16 unk_90;
    s16 unk_92;
    s16 unk_94;
    s16 unk_96;
    u8 pad_98[0xb0 - 0x98];
    u32 unk_B0;
};

extern char data_020da13c;
extern char data_020d7244;
extern char data_0213ff78;
extern u32 *data_0213ff74;
extern s16 *data_0213ff70;
extern struct Elem **data_021fd044;

extern void *func_020ee660(void *);
extern int func_020e8ca8(void *, void *);
extern void func_02003330(struct UnkStruct_02003564 *, u32, u32, u32);

struct UnkStruct_02003564 *func_02003564(struct UnkStruct_02003564 *self)
{
    func_020ee660(self);
    self->unk_00 = (u32) &data_020da13c;
    self->unk_00 = (u32) &data_020d7244;
    self->unk_50 = 0;
    self->unk_54 = 0;
    self->unk_58 = self;
    func_020e8ca8(&data_0213ff78, &self->unk_50);
    {
        u32 *p = data_0213ff74;
        if (p != 0) {
            self->unk_5C = p[0];
            self->unk_60 = p[1];
            self->unk_64 = p[2];
        }
    }
    {
        s16 *q = data_0213ff70;
        if (q != 0) {
            self->unk_8C = q[0];
            self->unk_8E = q[1];
            self->unk_90 = q[2];
            q = data_0213ff70;
            self->unk_92 = q[0];
            self->unk_94 = q[1];
            self->unk_96 = q[2];
        }
    }
    {
        struct Elem *e = data_021fd044[self->unk_0C];
        self->unk_B0 = e->unk_08;
        func_02003330(self, e->unk_0C, e->unk_10, e->unk_14);
    }
    return self;
}
