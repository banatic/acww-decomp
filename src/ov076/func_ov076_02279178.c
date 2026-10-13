/* func_ov076_02279178 @ 0x02279178, 0xb8 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02279178 UnkStruct_02279178;
struct UnkStruct_02279178 {
    u8 unk_00[0x64];
    int unk_64;
    u8 p1[0x8e - 0x68];
    short unk_8E;
    u8 p2[0x94 - 0x90];
    short unk_94;
    u8 p3[0x350 - 0x96];
    u8 unk_350[0x3b0 - 0x350];
    u8 unk_3B0[0x514 - 0x3b0];
    u8 unk_514[0x564 - 0x514];
    u8 unk_564[0x720 - 0x564];
    int unk_720;
    u16 unk_724;
};
extern void func_02019c20(u8 *, int, int, int, int, int);
extern void func_0200442c(u8 *, int, int, int);
extern void func_0201aff4(u8 *, int);
extern void func_0201ad18(u8 *, int, int, int, void *, int, int, int);
extern int data_020c814c;

extern unsigned char data_021fbee8[];

int func_ov076_02279178(UnkStruct_02279178 *self)
{
    int t;

    func_02019c20(self->unk_564, 1, 0xf9, 1, 0, 0);
    func_0200442c(self->unk_514, 0x814, 0x7f, 0);
    self->unk_8E = self->unk_8E + 0x8000;
    self->unk_94 = self->unk_8E;
    func_0201aff4(self->unk_350, self->unk_8E);
    t = -(self->unk_8E / 6);
    if (t < 0) {
        t = -t;
    }
    self->unk_724 = (u16) t;
    func_0201ad18(self->unk_3B0, 0, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    self->unk_720 = self->unk_64;
    return 1;
}
