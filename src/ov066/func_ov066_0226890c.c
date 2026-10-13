/* func_ov066_0226890c @ 0x0226890c, 0x110 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_0226890c {
    u8 pad_00[2];
    u16 unk_02;
    u8 pad_04[4];
    u16 unk_08;
} UnkStruct_0226890c;

typedef struct GStruct {
    u8 pad_00[0xc0];
    u32 unk_C0;
} GStruct;

extern GStruct *data_ov066_0226bdf4;

extern int func_ov066_02266e08(UnkStruct_0226890c *self);
extern void func_ov066_02268ea0(UnkStruct_0226890c *self);
extern void func_ov066_02268e9c(UnkStruct_0226890c *self);
extern void func_ov066_02268e14(UnkStruct_0226890c *self);
extern void func_ov066_0226686c();
extern void func_ov066_02266e64(void);
extern void func_ov066_02266a08(void (*cb)(void));
extern void func_ov066_02268410(void);

void func_ov066_0226890c(UnkStruct_0226890c *self)
{
    if (func_ov066_02266e08(self) != 0) {
        return;
    }

    if (self->unk_02 == 0) {
        switch (self->unk_08) {
            case 7:
                func_ov066_02268ea0(self);
                return;
            case 8:
                func_ov066_02268e9c(self);
                return;
            case 9:
                if (((int) (data_ov066_0226bdf4->unk_C0 << 29)) >> 31) {
                    func_ov066_02266e64();
                } else {
                    func_ov066_02268e14(self);
                }
                return;
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            default:
                func_ov066_0226686c(0x10);
                return;
            case 6:
                break;
        }
    } else if (self->unk_02 == 1) {
        if (((int) (data_ov066_0226bdf4->unk_C0 << 25)) >> 31) {
            func_ov066_02266a08(func_ov066_02268410);
            return;
        } else {
            func_ov066_02266e64();
            return;
        }
    } else {
        func_ov066_0226686c();
    }
}
