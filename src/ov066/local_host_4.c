/* local_host_4: 3 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02269154 @ 0x02269154, 0xb0 bytes, ARM
 * func_ov066_0226908c @ 0x0226908c, 0xc8 bytes, ARM
 * func_ov066_02268f98 @ 0x02268f98, 0xf4 bytes, ARM
 */

#include "types.h"

struct UnkStruct_02269154 {
    u8 pad_00[0x8c];
    u8 unk_8C;
    u8 pad_8D[0x9];
    u8 unk_96;
    u8 pad_97[0x29];
    u32 c0 : 4;
    int flag : 1;
    u32 c0_rest : 27;
};

struct UnkStruct_02269154_2 {
    u8 pad_00[4];
    u32 unk_04;
    u8 pad_08[0xc];
    u8 unk_14;
};

struct UnkStruct_0226908c {
    unsigned char pad_00[0x1e];
    short unk_1E;
    unsigned char pad1[0x8c - 0x20];
    unsigned char unk_8C;
    unsigned char pad_8D[0xc0 - 0x8d];
    int unk_C0;
};

struct UnkStruct_0226908c_2 {
    unsigned char pad_00[4];
    int unk_04;
    unsigned char pad1[0xb - 8];
    unsigned char unk_0B;
};

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
    unsigned int (*fn_ptr)(void);
    u8 pad_A0[0x20];
    union {
        u32 word;
        struct {
            u32 : 2;
            int b2 : 1;
        } bits;
    } c0;
};

extern void func_ov066_0226987c(unsigned int, unsigned char);
extern void func_ov066_022687f4(void);
extern void func_ov066_02266bf4(void);
extern struct UnkStruct_02269154 *data_ov066_0226bdf4;
extern struct UnkStruct_02269154_2 *data_ov066_0226bdec;
extern void func_ov066_0226929c(void);
extern void func_ov066_022695ac(int, void *);
extern void func_ov066_02266800(int, int);
extern void func_ov066_0226848c(int);
extern void func_ov066_02269204(u16);
extern void func_ov066_0226943c(void);

void func_ov066_02269154(void *p)
{
    if (data_ov066_0226bdf4->flag) {
        func_ov066_0226987c(0xe34d, data_ov066_0226bdf4->unk_8C);
        func_ov066_022687f4();
        data_ov066_0226bdf4->flag = 0;
    }
    if (data_ov066_0226bdec->unk_04 == 6) {
        data_ov066_0226bdf4->unk_96++;
        if (data_ov066_0226bdf4->unk_96 < data_ov066_0226bdec->unk_14) {
            return;
        }
        func_ov066_02266bf4();
    } else {
        return;
    }
}

void func_ov066_0226908c(void *a0)
{
    unsigned char *self = (unsigned char *) a0;

    (*(struct UnkStruct_0226908c **) &data_ov066_0226bdf4)->unk_C0 |= 0x10;

    if ((*(struct UnkStruct_0226908c_2 **) &data_ov066_0226bdec)->unk_04 == 6) {
        (*(struct UnkStruct_0226908c_2 **) &data_ov066_0226bdec)->unk_04 = 9;
        (*(struct UnkStruct_0226908c **) &data_ov066_0226bdf4)->unk_1E = 0;
        func_ov066_0226929c();

        (*(struct UnkStruct_0226908c **) &data_ov066_0226bdf4)->unk_C0 |= 0x20;
        func_ov066_0226987c(0xbd8a, (*(struct UnkStruct_0226908c **) &data_ov066_0226bdf4)->unk_8C);
        func_ov066_022687f4();
    }

    func_ov066_022695ac(*(unsigned short *) (self + 0x10), self + 0xa);
    func_ov066_02266800(0, *(unsigned short *) (self + 0x10));

    if ((*(struct UnkStruct_0226908c **) &data_ov066_0226bdf4)->unk_8C >=
        (*(struct UnkStruct_0226908c_2 **) &data_ov066_0226bdec)->unk_0B) {
        func_ov066_0226848c(0);
    }
}

void func_ov066_02268f98(struct UnkStruct_02268f98 *self)
{
    if ((*(struct GWork **) &data_ov066_0226bdf4)->unk_8C == (*(struct Other **) &data_ov066_0226bdec)->unk_0B) {
        func_ov066_0226848c(1);
    }

    (*(struct GWork **) &data_ov066_0226bdf4)->flags &= ~(1 << self->h);
    func_ov066_022695ac((u16) self->h, 0);
    func_ov066_02266800(1, (u16) self->h);

    if ((*(struct GWork **) &data_ov066_0226bdf4)->unk_8C > 1) {
        goto high;
    }

    if ((*(struct GWork **) &data_ov066_0226bdf4)->c0.bits.b2) {
        return;
    }

    (*(struct GWork **) &data_ov066_0226bdf4)->fn_ptr();
    (*(struct GWork **) &data_ov066_0226bdf4)->c0.word &= ~1;
    (*(struct GWork **) &data_ov066_0226bdf4)->c0.word &= ~2;
    return;

high:
    func_ov066_02269204(self->h);
    func_ov066_0226943c();
    (*(struct GWork **) &data_ov066_0226bdf4)->c0.word |= 0x10;
}
