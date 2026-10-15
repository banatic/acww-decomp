/* func_ov066_022676a0 @ 0x022676a0, 0xa0 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

struct UnkStruct_022676a0_3 {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[4];
    u16 unk_08;
};

struct UnkStruct_022676a0 {
    u8 pad_00[8];
    u32 base;
    unsigned int : 1;
    signed int flag : 1;
};

struct UnkStruct_022676a0_2 {
    u8 pad_00[0x95];
    u8 unk_95;
};

extern struct UnkStruct_022676a0 *data_ov066_0226bdf0;
extern struct UnkStruct_022676a0_2 *data_ov066_0226bdf4;

extern int func_ov066_02266e08(void);
extern void func_ov066_02267958(struct UnkStruct_022676a0_3 *self);
extern void func_ov066_02267c0c(void);
extern void func_ov066_0226a404(u32 arg);
extern void func_ov066_0226768c(void);
extern void func_ov066_0226686c(int status);

void func_ov066_022676a0(struct UnkStruct_022676a0_3 *self)
{
    if (func_ov066_02266e08() != 0) {
        return;
    }
    if (self->unk_02 == 0) {
        u16 v = self->unk_08;
        if (v == 4) {
        } else if (v == 5) {
            func_ov066_02267958(self);
        } else {
            return;
        }
        if (data_ov066_0226bdf0->flag) {
            func_ov066_02267c0c();
            return;
        }
        func_ov066_0226a404(data_ov066_0226bdf4->unk_95 * 16 + data_ov066_0226bdf0->base);
        func_ov066_0226768c();
    } else {
        func_ov066_0226686c(self->unk_02);
    }
}
