/* local_session: 5 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02269dcc @ 0x02269dcc, 0x1a0 bytes, ARM
 * func_ov066_02269c28 @ 0x02269c28, 0x1a4 bytes, ARM
 * func_ov066_02269b88 @ 0x02269b88, 0xa0 bytes, ARM
 * func_ov066_02269aa4 @ 0x02269aa4, 0xe4 bytes, ARM
 * func_ov066_02269a14 @ 0x02269a14, 0x90 bytes, ARM
 */

struct UnkStruct_02269dcc {
    char pad_00[0x1e];
    unsigned short unk_1E;
    char pad_20[0x28 - 0x20];
    unsigned char arr28[16][6];
    char pad_88[0x8c - 0x88];
    unsigned char unk_8C;
    unsigned char unk_8D;
    unsigned char unk_8E;
    unsigned char unk_8F;
    char pad_90[0xc0 - 0x90];
    unsigned int unk_C0;
};

struct UnkStruct_02269dcc_2 {
    char pad_00[8];
    unsigned char unk_08;
};

struct Dev {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned short unk_18;
    unsigned short unk_1A;
    unsigned short unk_1C;
    char pad_1E[0x22 - 0x1e];
    unsigned char unk_22;
    char pad_23[0x24 - 0x23];
    unsigned char unk_24;
    char pad_25[0xb8 - 0x25];
    unsigned int unk_B8;
};

struct Other {
    unsigned int unk_00;
    unsigned int unk_04;
    char pad_08[0xa - 8];
    unsigned char unk_0A;
    char pad_18[0x18 - 0xb];
    unsigned short unk_18;
    unsigned short unk_1A;
    unsigned short unk_1C;
    unsigned short unk_1E;
};

typedef struct {
    int pad_00;
    void *unk_04;
} UnkStruct_02269b88;

typedef struct {
    char pad_00[13];
    unsigned char unk_0D;
} OtherStruct;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_02269aa4;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
} UnkStruct_02269aa4_2;

typedef struct Unk9A14 {
    char pad_00[0x93];
    unsigned char unk_93;
    unsigned char unk_94;
    unsigned char unk_95;
    char pad_96[2];
    unsigned short unk_98;
    char pad_9A[2];
    unsigned int (*fn0x9c)(void);
    char pad_A0[0x20];
    unsigned int fl0xc0;
} Unk9A14;

extern struct UnkStruct_02269dcc *data_ov066_0226bdf4;
extern struct UnkStruct_02269dcc_2 *data_ov066_0226bdec;
extern void MI_CpuFill8(void *buf, int mode, int len);
extern int data_ov066_0226bdf8;
extern int func_ov066_02266908(int a, int b);
extern void func_ov066_02267ef8(void);
extern void OS_GetMacAddress(void *p);
extern int func_ov066_022683ec(void *p);
extern void func_ov066_022668c4(void *);
extern int WM_Init(void *, unsigned char);
extern int WM_Finish(void); // 0x0212073c
extern void func_ov066_02267e28(void);
extern void func_ov066_0226686c(int arg);
extern void func_ov066_02267e00(int);
extern void func_ov066_0226929c(void);
extern void func_ov066_0226a224(void);

void func_ov066_02269dcc(void)
{
    unsigned char buf[6];
    int i;
    data_ov066_0226bdf4->unk_1E = 0xffff;
    data_ov066_0226bdf4->unk_8C = 1;
    data_ov066_0226bdf4->unk_C0 &= ~1u;
    data_ov066_0226bdf4->unk_C0 &= ~2u;
    data_ov066_0226bdf4->unk_C0 &= ~4u;
    data_ov066_0226bdf4->unk_C0 &= ~8u;
    data_ov066_0226bdf4->unk_C0 &= ~0x10u;
    data_ov066_0226bdf4->unk_C0 &= ~0x20u;
    data_ov066_0226bdf4->unk_C0 &= ~0x40u;
    data_ov066_0226bdf4->unk_C0 &= ~0x400u;
    if (((unsigned char) (data_ov066_0226bdec->unk_08 + 2)) <= 1) {
        data_ov066_0226bdf4->unk_C0 |= 0x80;
        data_ov066_0226bdf4->unk_8D = 0;
        data_ov066_0226bdf4->unk_8E = 0;
        data_ov066_0226bdf4->unk_8F = 0;
    } else {
        data_ov066_0226bdf4->unk_C0 &= ~0x80u;
        data_ov066_0226bdf4->unk_8D = data_ov066_0226bdec->unk_08;
        data_ov066_0226bdf4->unk_8E = 0;
        data_ov066_0226bdf4->unk_8F = data_ov066_0226bdec->unk_08;
    }
    MI_CpuFill8(buf, 0, 6);
    {
        typedef struct {
            unsigned char a, b;
        } Pair;
        unsigned char *p = (unsigned char *) data_ov066_0226bdf4;
        for (i = 0; i < 16; i++) {
            *(Pair *) &p[0x28] = *(Pair *) &buf[0];
            *(Pair *) &p[0x2a] = *(Pair *) &buf[2];
            *(Pair *) &p[0x2c] = *(Pair *) &buf[4];
            p += 6;
        }
    }
}

void func_ov066_02269c28(void)
{
    unsigned int v0, v1;
    unsigned short a, b;

    (*(struct Dev **) &data_ov066_0226bdf4)->unk_00 = func_ov066_02266908(0x40, 0x20);
    (*(struct Dev **) &data_ov066_0226bdf4)->unk_08 = func_ov066_02266908(0x70, 0x20);
    (*(struct Dev **) &data_ov066_0226bdf4)->unk_18 = 8;

    v0 = ((*(struct Other **) &data_ov066_0226bdec)->unk_18 + 0xe) * (*(struct Other **) &data_ov066_0226bdec)->unk_0A + 0x29;
    v0 &= ~0x1fu;
    v1 = ((*(struct Other **) &data_ov066_0226bdec)->unk_1C + 0x55) & ~0x1fu;
    a = (unsigned short) (v0 * 2);
    b = (unsigned short) (v1 * 2);
    if (a <= b) {
        a = b;
    }
    (*(struct Dev **) &data_ov066_0226bdf4)->unk_1A = a;
    (*(struct Dev **) &data_ov066_0226bdf4)->unk_0C =
        func_ov066_02266908((*(struct Dev **) &data_ov066_0226bdf4)->unk_1A, 0x20);

    v0 = ((*(struct Other **) &data_ov066_0226bdec)->unk_1A + 0x23) & ~0x1fu;
    v1 = ((*(struct Other **) &data_ov066_0226bdec)->unk_1E + 0x21) & ~0x1fu;
    a = (unsigned short) v0;
    b = (unsigned short) v1;
    if (a <= b) {
        a = b;
    }
    (*(struct Dev **) &data_ov066_0226bdf4)->unk_1C = a;
    (*(struct Dev **) &data_ov066_0226bdf4)->unk_10 =
        func_ov066_02266908((*(struct Dev **) &data_ov066_0226bdf4)->unk_1C, 0x20);

    (*(struct Dev **) &data_ov066_0226bdf4)->unk_14 =
        func_ov066_02266908((*(struct Other **) &data_ov066_0226bdec)->unk_1E << 1, 0x20);
    (*(struct Dev **) &data_ov066_0226bdf4)->unk_B8 = 0;

    func_ov066_02267ef8();
    OS_GetMacAddress(&(*(struct Dev **) &data_ov066_0226bdf4)->unk_22);
    data_ov066_0226bdf8 = func_ov066_022683ec(&(*(struct Dev **) &data_ov066_0226bdf4)->unk_24);
    (*(struct Other **) &data_ov066_0226bdec)->unk_04 = 2;
    (*(struct Other **) &data_ov066_0226bdec)->unk_00 = 0;

    func_ov066_02269dcc();
}

void func_ov066_02269b88(void)
{
    if ((*(UnkStruct_02269b88 **) &data_ov066_0226bdf4)) {
        return;
    }

    (*(UnkStruct_02269b88 **) &data_ov066_0226bdf4) = (UnkStruct_02269b88 *) func_ov066_02266908(0xc4, 4);
    (*(UnkStruct_02269b88 **) &data_ov066_0226bdf4)->unk_04 = (void *) func_ov066_02266908(0xf00, 0x20);

    if (WM_Init((*(UnkStruct_02269b88 **) &data_ov066_0226bdf4)->unk_04, (*(OtherStruct **) &data_ov066_0226bdec)->unk_0D) ==
        0) {
        func_ov066_02269c28();
        return;
    }

    func_ov066_022668c4((*(UnkStruct_02269b88 **) &data_ov066_0226bdf4)->unk_04);
    return;
}

void func_ov066_02269aa4(void)
{
    if ((*(UnkStruct_02269aa4 **) &data_ov066_0226bdec)->unk_04 == 2) {
        if (WM_Finish() != 0) {
            return;
        }
        func_ov066_02267e28();
        func_ov066_022668c4((void *) ((*(UnkStruct_02269aa4_2 **) &data_ov066_0226bdf4)->unk_14));
        func_ov066_022668c4((void *) ((*(UnkStruct_02269aa4_2 **) &data_ov066_0226bdf4)->unk_10));
        func_ov066_022668c4((void *) ((*(UnkStruct_02269aa4_2 **) &data_ov066_0226bdf4)->unk_0C));
        func_ov066_022668c4((void *) ((*(UnkStruct_02269aa4_2 **) &data_ov066_0226bdf4)->unk_08));
        func_ov066_022668c4((void *) ((*(UnkStruct_02269aa4_2 **) &data_ov066_0226bdf4)->unk_00));
        func_ov066_022668c4((void *) ((*(UnkStruct_02269aa4_2 **) &data_ov066_0226bdf4)->unk_04));
        func_ov066_022668c4((void *) ((int) (*(UnkStruct_02269aa4_2 **) &data_ov066_0226bdf4)));
        (*(UnkStruct_02269aa4_2 **) &data_ov066_0226bdf4) = 0;
        (*(UnkStruct_02269aa4 **) &data_ov066_0226bdec)->unk_04 = 1;
    } else {
        func_ov066_0226686c(0x44);
    }
}

void func_ov066_02269a14(void)
{
    func_ov066_02267e00(0);
    (*(Unk9A14 **) &data_ov066_0226bdf4)->fl0xc0 &= ~4;
    (*(Unk9A14 **) &data_ov066_0226bdf4)->fn0x9c();
    (*(Unk9A14 **) &data_ov066_0226bdf4)->fl0xc0 &= ~1;
    (*(Unk9A14 **) &data_ov066_0226bdf4)->fl0xc0 &= ~2;
    (*(Unk9A14 **) &data_ov066_0226bdf4)->unk_93 = 0;
    (*(Unk9A14 **) &data_ov066_0226bdf4)->unk_94 = 0;
    (*(Unk9A14 **) &data_ov066_0226bdf4)->unk_95 = 0;
    (*(Unk9A14 **) &data_ov066_0226bdf4)->unk_98 = 0;
    func_ov066_0226929c();
    func_ov066_0226a224();
}
