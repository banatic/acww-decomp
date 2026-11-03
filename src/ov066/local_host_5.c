/* local_host_5: 3 functions, module ov066
 * mwccarm 1.2/base -O4,s
 * func_ov066_0226987c @ 0x0226987c, 0x70 bytes, ARM
 * func_ov066_0226978c @ 0x0226978c, 0xf0 bytes, ARM
 * func_ov066_02269748 @ 0x02269748, 0x44 bytes, ARM
 */

#include "types.h"

struct Dest {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
};

struct GStruct {
    unsigned char pad_00[8];
    struct Dest *dest;
    unsigned char pad_0C[0x95 - 12];
    unsigned char unk_95;
};

typedef struct {
    void *unk_00;
    u16 unk_04;
    u16 unk_06;
    int unk_08;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u8 pad_1A[0x32 - 0x1a];
    u16 unk_32;
    u16 unk_34;
    u16 unk_36;
} Pkt;

typedef struct {
    Pkt *pkt;
    u8 pad0[4];
    void *dest;
    u8 pad1[0x18 - 0xc];
    u16 unk_18;
    u8 pad2[6];
    u16 unk_20;
    u8 pad3[0x8c - 0x22];
    u8 unk_8C;
    u8 unk_8D;
} UnkStruct_0226978c;

typedef struct {
    u8 pad0[0xa];
    u8 unk_0A;
    u8 pad1[0x1a - 0xb];
    u16 unk_1A;
    u8 pad2[2];
    u16 unk_1E;
    u8 pad3[8];
    int unk_28;
} UnkStruct_0226978c_2;

typedef struct {
    unsigned char pad_00[4];
    unsigned long unk_04;
} UnkStruct_02269748;

typedef struct {
    unsigned char pad_00[0x96];
    unsigned char unk_96;
} UnkStruct_02269748_2;

extern struct GStruct *data_ov066_0226bdf4;
extern unsigned int data_ov066_0226bdf8;
extern UnkStruct_0226978c_2 *data_ov066_0226bdec;
extern int WM_GetDispersionBeaconPeriod(void);
extern void func_ov066_02268c4c(void);

void func_ov066_0226987c(unsigned int arg0, unsigned char arg1)
{
    struct Dest *d = data_ov066_0226bdf4->dest;
    if (arg0 != 0xe34d) {
        d->unk_00 = (unsigned short) arg0;
    }
    data_ov066_0226bdf8 = data_ov066_0226bdf8 * 0x5eedf715 + 0x1b0cb173;
    d->unk_02 = (unsigned short) data_ov066_0226bdf8;
    d->unk_04 = data_ov066_0226bdf4->unk_95;
    d->unk_05 = arg1;
    d->unk_06 = 5;
}

void func_ov066_0226978c(u32 arg0)
{
    Pkt *p;

    p = (*(UnkStruct_0226978c * *) &data_ov066_0226bdf4)->pkt;
    (*(UnkStruct_0226978c * *) &data_ov066_0226bdf4)->unk_8C = 1;
    func_ov066_0226987c(arg0, (u8) 1);

    p->unk_00 = (*(UnkStruct_0226978c * *) &data_ov066_0226bdf4)->dest;
    p->unk_04 = (*(UnkStruct_0226978c * *) &data_ov066_0226bdf4)->unk_18;
    p->unk_08 = data_ov066_0226bdec->unk_28;
    (*(u32 *) &data_ov066_0226bdf8) = (*(u32 *) &data_ov066_0226bdf8) * 0x5eedf715 + 0x1b0cb173;
    (*(UnkStruct_0226978c * *) &data_ov066_0226bdf4)->unk_20 = (u16) (*(u32 *) &data_ov066_0226bdf8);
    p->unk_0C = (*(UnkStruct_0226978c * *) &data_ov066_0226bdf4)->unk_20;
    p->unk_0E = 1;
    p->unk_12 = 0;
    p->unk_14 = 0;
    p->unk_16 = 0;
    p->unk_10 = data_ov066_0226bdec->unk_0A;
    p->unk_18 = (u16) WM_GetDispersionBeaconPeriod();
    p->unk_32 = (*(UnkStruct_0226978c * *) &data_ov066_0226bdf4)->unk_8D;
    p->unk_34 = data_ov066_0226bdec->unk_1A;
    p->unk_36 = data_ov066_0226bdec->unk_1E;
}

void func_ov066_02269748(int a)
{
    (*(UnkStruct_02269748 * *) &data_ov066_0226bdec)->unk_04 = 6;
    (*(UnkStruct_02269748_2 * *) &data_ov066_0226bdf4)->unk_96 = 0;
    func_ov066_0226978c(a);
    func_ov066_02268c4c();
}
