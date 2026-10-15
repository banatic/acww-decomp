/* func_ov066_02268570 @ 0x02268570, 0x180 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

struct UnkStruct_02268570 {
    char pad_00[4];
    int unk_04;
    char pad1[0x34];
    unsigned int unk_3C;
};

struct UnkStruct_02268570_2 {
    char pad_00[0x1e];
    u16 unk_1E;
    char pad1[2];
    char unk_22;
    char pad_23[0x9c - 0x23];
    unsigned int (*unk_9C)(void);
    void (*unk_A0)(void);
    void (*unk_A4)(void);
    char pad_A8[0xc0 - 0xa8];
    unsigned int unk_C0;
};

struct UnkStruct_02268570_3 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
};

extern struct UnkStruct_02268570 *data_ov066_0226bdec;
extern struct UnkStruct_02268570_2 *data_ov066_0226bdf4;

extern int func_ov066_02266e08(void);
extern void func_ov066_022695ac(int a, void *b);
extern void func_ov066_0226943c(void);
extern void func_ov066_02266bf4(void);
extern void func_ov066_02269528(void);
extern int func_ov066_02268c90(void);
extern void func_ov066_0226686c(int code);

void func_ov066_02268570(struct UnkStruct_02268570_3 *p)
{
    struct UnkStruct_02268570_2 *q;
    struct UnkStruct_02268570 *a;
    u16 v;

    if (func_ov066_02266e08() != 0) {
        return;
    }
    v = p->unk_02;
    if (v == 0) {
        switch (p->unk_04) {
            case 0xa:
                data_ov066_0226bdf4->unk_C0 &= ~0x20;
                data_ov066_0226bdec->unk_3C |= 0x1000;
                data_ov066_0226bdf4->unk_9C();
                data_ov066_0226bdf4->unk_C0 &= ~1;
                data_ov066_0226bdf4->unk_C0 &= ~2;
                q = data_ov066_0226bdf4;
                if (q->unk_1E == 0) {
                    func_ov066_022695ac(0, &q->unk_22);
                    a = data_ov066_0226bdec;
                    if (a->unk_04 != 0xa) {
                        a->unk_04 = 0xa;
                    }
                    func_ov066_0226943c();
                    func_ov066_02266bf4();
                    return;
                }
                func_ov066_02269528();
                return;
            case 0xb:
                func_ov066_02268c90();
                if (data_ov066_0226bdf4->unk_A0 != 0) {
                    data_ov066_0226bdf4->unk_A0();
                }
                return;
            case 0xc:
                func_ov066_02268c90();
                return;
            case 0xd:
                if (data_ov066_0226bdf4->unk_A4 != 0) {
                    data_ov066_0226bdf4->unk_A4();
                }
                return;
        }
    } else {
        if (v == 9) {
            return;
        }
        if (v == 0xd) {
            return;
        }
        if (v == 0xf) {
            return;
        }
        func_ov066_0226686c(v);
    }
}
