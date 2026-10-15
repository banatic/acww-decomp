/* func_0208d338 @ 0x0208d338, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_020e2218[];

extern void func_0208af30(void *p);
extern void func_0208a1f8(void *p);
extern void *func_0208e024(void *p);

struct UnkStruct_0208d338 {
    void *unk_00;
    u8 pad_04[0x20 - 4];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    u8 unk_34[0x50 - 0x34];
    u8 unk_50[0x6c - 0x50];
    u8 unk_6C[0x88 - 0x6c];
    u8 unk_88[0xa4 - 0x88];
    u8 unk_A4;
    u8 unk_A5;
    u8 unk_A6;
    u8 unk_A7;
    u8 unk_A8;
    u8 unk_A9;
    u8 pad_AA[0xac - 0xaa];
    int unk_AC;
    int unk_B0;
    int unk_B4;
    int unk_B8;
    int unk_BC;
    int unk_C0;
    int unk_C4;
    int unk_C8;
    int unk_CC;
    int unk_D0;
    int unk_D4;
    int unk_D8;
    int unk_DC;
    int unk_E0;
};

void *func_0208d338(void *thisArg)
{
    struct UnkStruct_0208d338 *self = (struct UnkStruct_0208d338 *) thisArg;

    func_0208af30(self);
    self->unk_00 = data_020e2218;
    func_0208a1f8((u8 *) self + 0xc);

    self->unk_20 = 0;
    self->unk_24 = 0;
    self->unk_28 = 0;
    self->unk_2C = 0;
    self->unk_30 = 0;

    func_0208e024((u8 *) self + 0x34);
    func_0208e024((u8 *) self + 0x50);
    func_0208e024((u8 *) self + 0x6c);
    func_0208e024((u8 *) self + 0x88);

    self->unk_A4 = 0;
    self->unk_A5 = 0;
    self->unk_A6 = 0;
    self->unk_A7 = 0;
    self->unk_A8 = 0;
    self->unk_A9 = 0;

    self->unk_AC = 0;
    self->unk_B0 = 0;
    self->unk_B4 = 0;
    self->unk_B8 = 0;
    self->unk_BC = 0;
    self->unk_C0 = 0;
    self->unk_C4 = 0;
    self->unk_C8 = 0;
    self->unk_CC = 0;
    self->unk_D0 = 0;
    self->unk_D4 = 0;
    self->unk_D8 = ~0;
    self->unk_DC = 0;
    self->unk_E0 = 0;

    return self;
}
