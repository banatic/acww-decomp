/* func_ov066_0226978c @ 0x0226978c, 0xf0 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

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

extern UnkStruct_0226978c *data_ov066_0226bdf4;
extern UnkStruct_0226978c_2 *data_ov066_0226bdec;
extern u32 data_ov066_0226bdf8;

extern void func_ov066_0226987c(u32 arg0, u8 arg1);
extern int WM_GetDispersionBeaconPeriod(void);

void func_ov066_0226978c(u32 arg0)
{
    Pkt *p;

    p = data_ov066_0226bdf4->pkt;
    data_ov066_0226bdf4->unk_8C = 1;
    func_ov066_0226987c(arg0, 1);

    p->unk_00 = data_ov066_0226bdf4->dest;
    p->unk_04 = data_ov066_0226bdf4->unk_18;
    p->unk_08 = data_ov066_0226bdec->unk_28;
    data_ov066_0226bdf8 = data_ov066_0226bdf8 * 0x5eedf715 + 0x1b0cb173;
    data_ov066_0226bdf4->unk_20 = (u16) data_ov066_0226bdf8;
    p->unk_0C = data_ov066_0226bdf4->unk_20;
    p->unk_0E = 1;
    p->unk_12 = 0;
    p->unk_14 = 0;
    p->unk_16 = 0;
    p->unk_10 = data_ov066_0226bdec->unk_0A;
    p->unk_18 = (u16) WM_GetDispersionBeaconPeriod();
    p->unk_32 = data_ov066_0226bdf4->unk_8D;
    p->unk_34 = data_ov066_0226bdec->unk_1A;
    p->unk_36 = data_ov066_0226bdec->unk_1E;
}
