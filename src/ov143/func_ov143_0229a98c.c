/* func_ov143_0229a98c @ 0x0229a98c, 0x68 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229a98c {
    char pad_00[0x98];
    u16 unk_98;
    short unk_9A;
    char pad_9C[4];
    void *unk_A0;
    u8 unk_A4;
};

struct G040 {
    char pad_00[0x14];
    u16 unk_14;
};

struct G028 {
    char pad_00[0x14];
    unsigned short lo10 : 10;
};

extern struct G040 data_ov143_0229b040;
extern struct G028 data_ov143_0229b028;
extern void func_0206ea5c(void *a, void *b);

extern unsigned char data_021cfbbc[];
extern unsigned char data_021f3b68[];

void func_ov143_0229a98c(struct UnkStruct_0229a98c *self)
{
    self->unk_98 = 0;
    self->unk_A0 = (void *) data_021cfbbc;
    func_0206ea5c((void *) data_021f3b68, self->unk_A0);
    data_ov143_0229b040.unk_14 =
        (u16) ((data_ov143_0229b040.unk_14 & 0xfffffc00) | ((u16) (data_ov143_0229b028.lo10 + 4) & 0x3ff));
    self->unk_9A = -1;
    self->unk_A4 = 0;
}
