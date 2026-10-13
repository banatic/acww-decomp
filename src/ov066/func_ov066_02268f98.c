/* func_ov066_02268f98 @ 0x02268f98, 0xf4 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern struct GWork *data_ov066_0226bdf4;
extern struct Other *data_ov066_0226bdec;

struct UnkStruct_02268f98 {
    u8 pad_00[0x10];
    u16 h;
};

struct Other {
    u8 pad_00[0xb];
    u8 unk_0B;
};

struct GWork {
    u8 pad_00[0x8c];
    u8 unk_8C;
    u8 pad_8D[11];
    u16 flags;
    u8 pad_9A[2];
    void (*fn_ptr)(void);
    u8 pad_A0[0x20];
    union {
        u32 word;
        struct {
            u32 : 2;
            int b2 : 1;
        } bits;
    } c0;
};

extern void func_ov066_0226848c(int);
extern void func_ov066_022695ac(u16, int);
extern void func_ov066_02266800(int, u16);
extern void func_ov066_02269204(u16);
extern void func_ov066_0226943c(void);

void func_ov066_02268f98(struct UnkStruct_02268f98 *self)
{
    if (data_ov066_0226bdf4->unk_8C == data_ov066_0226bdec->unk_0B) {
        func_ov066_0226848c(1);
    }

    data_ov066_0226bdf4->flags &= ~(1 << self->h);
    func_ov066_022695ac(self->h, 0);
    func_ov066_02266800(1, self->h);

    if (data_ov066_0226bdf4->unk_8C > 1) {
        goto high;
    }

    if (data_ov066_0226bdf4->c0.bits.b2) {
        return;
    }

    data_ov066_0226bdf4->fn_ptr();
    data_ov066_0226bdf4->c0.word &= ~1;
    data_ov066_0226bdf4->c0.word &= ~2;
    return;

high:
    func_ov066_02269204(self->h);
    func_ov066_0226943c();
    data_ov066_0226bdf4->c0.word |= 0x10;
}
