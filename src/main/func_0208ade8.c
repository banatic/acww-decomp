/* func_0208ade8 @ 0x0208ade8, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_0208af30(void *self);
extern void func_0208a1f8(void *sub);
extern void func_0208aecc(void *sub);
extern void func_0208a738(void *self);
extern void func_0208a9a4(void *self);
extern int data_020e20ac;

typedef struct UnkStruct_0208ade8 {
    void *unk_00;
    u8 pad_04[8];
    u8 sub1[0x14];
    u8 sub2[0x14];
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    u8 bytes[9];
    u8 pad_5D[3];
    u8 sub3[0x30];
    u8 sub4[0x30];
    int c0;
    int c4;
    int c8;
} UnkStruct_0208ade8;

UnkStruct_0208ade8 *func_0208ade8(UnkStruct_0208ade8 *self, int param)
{
    func_0208af30(self);
    self->unk_00 = &data_020e20ac;
    func_0208a1f8(self->sub1);
    func_0208a1f8(self->sub2);
    self->unk_34 = 0;
    self->unk_38 = 0;
    self->unk_3C = 0;
    self->unk_40 = 0;
    self->unk_44 = -1;
    self->unk_48 = 0;
    self->unk_4C = 0;
    self->unk_50 = 0;
    self->bytes[0] = 0;
    self->bytes[1] = 0;
    self->bytes[2] = param;
    self->bytes[3] = 0;
    self->bytes[4] = 0;
    self->bytes[5] = 0;
    self->bytes[6] = 0;
    self->bytes[7] = 0;
    self->bytes[8] = 0;
    func_0208aecc(self->sub3);
    func_0208aecc(self->sub4);
    self->c0 = 0;
    self->c4 = 0;
    self->c8 = 0;
    func_0208a738(self);
    func_0208a9a4(self);
    return self;
}
