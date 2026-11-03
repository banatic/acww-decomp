/* local_mp: 4 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_022686f0 @ 0x022686f0, 0xa8 bytes, ARM
 * func_ov066_02268570 @ 0x02268570, 0x180 bytes, ARM
 * func_ov066_0226853c @ 0x0226853c, 0x34 bytes, ARM
 * func_ov066_022684c4 @ 0x022684c4, 0x78 bytes, ARM
 */

#include "types.h"

struct UnkStruct_022686f0 {
    unsigned char pad_00[0xc];
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned char pad2[6];
    unsigned short unk_1A;
    unsigned short unk_1C;
};

struct UnkStruct_022686f0_2 {
    unsigned char pad_00[0x17];
    unsigned char unk_17;
    unsigned char pad2[0x24];
    int b0 : 1;
    int b1 : 1;
    int b2 : 1;
};

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

typedef struct UnkStruct_022684c4 {
    u16 unk_00;
    u16 unk_02;
} UnkStruct_022684c4;

typedef struct UnkStruct_022684c4_2 {
    unsigned char pad_00[0x1e];
    u16 unk_1E;
    unsigned char pad_20[0xa0];
    unsigned long b0 : 3;
    signed long b3 : 1;
    unsigned long b4 : 28;
} UnkStruct_022684c4_2;

extern struct UnkStruct_022686f0 *data_ov066_0226bdf4;
extern struct UnkStruct_022686f0_2 *data_ov066_0226bdec;
extern void func_ov066_0226686c(int status);
extern int WM_StartMPEx(void (*cb)(void *), unsigned int a1, unsigned short a2, unsigned int a3, unsigned short a4,
                        unsigned char a5, int a6, int a7, int a8, int a9, int a10);
extern int func_ov066_02266e08(void);
extern void func_ov066_022695ac(int a, void *b);
extern void func_ov066_0226943c(void);
extern void func_ov066_02266bf4(void);
extern void func_ov066_02269528(void);
extern int func_ov066_02268c90(void);
extern int WM_EndMP(void (*)(void *));
extern void func_ov066_02268ad0(void);
extern int func_ov066_022688cc(int a);

void func_ov066_02268570(struct UnkStruct_02268570_3 *p);
void func_ov066_022684c4(UnkStruct_022684c4 *p);

void func_ov066_022686f0(void)
{
    int status = WM_StartMPEx((void (*)(void *)) (void (*)(void *)) func_ov066_02268570, data_ov066_0226bdf4->unk_0C, data_ov066_0226bdf4->unk_1A,
                              data_ov066_0226bdf4->unk_10, data_ov066_0226bdf4->unk_1C, data_ov066_0226bdec->unk_17, 4,
                              data_ov066_0226bdec->b0, data_ov066_0226bdec->b1, 1, data_ov066_0226bdec->b2);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
    return;
}

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
                (*(struct UnkStruct_02268570_2 * *) &data_ov066_0226bdf4)->unk_C0 &= ~0x20;
                (*(struct UnkStruct_02268570 * *) &data_ov066_0226bdec)->unk_3C |= 0x1000;
                (*(struct UnkStruct_02268570_2 * *) &data_ov066_0226bdf4)->unk_9C();
                (*(struct UnkStruct_02268570_2 * *) &data_ov066_0226bdf4)->unk_C0 &= ~1;
                (*(struct UnkStruct_02268570_2 * *) &data_ov066_0226bdf4)->unk_C0 &= ~2;
                q = (*(struct UnkStruct_02268570_2 * *) &data_ov066_0226bdf4);
                if (q->unk_1E == 0) {
                    func_ov066_022695ac(0, &q->unk_22);
                    a = (*(struct UnkStruct_02268570 * *) &data_ov066_0226bdec);
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
                if ((*(struct UnkStruct_02268570_2 * *) &data_ov066_0226bdf4)->unk_A0 != 0) {
                    (*(struct UnkStruct_02268570_2 * *) &data_ov066_0226bdf4)->unk_A0();
                }
                return;
            case 0xc:
                func_ov066_02268c90();
                return;
            case 0xd:
                if ((*(struct UnkStruct_02268570_2 * *) &data_ov066_0226bdf4)->unk_A4 != 0) {
                    (*(struct UnkStruct_02268570_2 * *) &data_ov066_0226bdf4)->unk_A4();
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

void func_ov066_0226853c(void)
{
    int status = WM_EndMP((void (*)(void *)) (void (*)(void *)) func_ov066_022684c4);
    if (status == 2) {
        return;
    }
    func_ov066_0226686c(status);
}

void func_ov066_022684c4(UnkStruct_022684c4 *p)
{
    if (func_ov066_02266e08()) {
        return;
    }
    if (p->unk_02 == 0) {
        UnkStruct_022684c4_2 *q = (*(UnkStruct_022684c4_2 * *) &data_ov066_0226bdf4);
        if (!q->b3) {
            return;
        }
        if (q->unk_1E == 0) {
            func_ov066_02268ad0();
            return;
        }
        func_ov066_022688cc(0);
        return;
    }
    func_ov066_0226686c(p->unk_02);
}
