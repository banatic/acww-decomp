/* local_mp_2: 4 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02268da4 @ 0x02268da4, 0x70 bytes, ARM
 * func_ov066_02268d44 @ 0x02268d44, 0x60 bytes, ARM
 * func_ov066_02268d08 @ 0x02268d08, 0x3c bytes, ARM
 * func_ov066_02268c90 @ 0x02268c90, 0x78 bytes, ARM
 */

#include "types.h"

typedef struct UnkStruct_02268da4 {
    unsigned char pad_00[0xc];
    void *unk_0C;
    u16 unk_10;
} UnkStruct_02268da4;

typedef struct Hdr {
    u16 kind;
    u16 unk_02;
} Hdr;

typedef struct {
    unsigned char pad_00[0xc0];
    unsigned int : 2;
    signed int b : 1;
    signed int c : 1;
} UnkStruct_02268d08;

typedef struct {
    int bit0 : 1;
    int bit1 : 1;
    int bit2 : 1;
    int bit3 : 1;
    int : 28;
} Flags;

typedef struct {
    unsigned char pad_00[0xc0];
    Flags flags;
} UnkStruct_02268c90;

void MI_CpuCopy8(const void *src, void *dest, u32 size);
extern void func_ov066_02269320(void *a, void *b);
extern void func_ov066_022692c0(void);
extern void func_ov066_02266bf4(void);
extern char *data_ov066_0226bdf4;
extern int *data_ov066_0226bdec;
extern int OS_DisableInterrupts(void);
extern unsigned int OS_RestoreInterrupts(int);
extern void func_ov066_0226853c(void);

void func_ov066_02268d44(void *arg);

void func_ov066_02268da4(UnkStruct_02268da4 *p)
{
    Hdr hdr;

    if (p->unk_10 == 0) {
        return;
    }
    MI_CpuCopy8(p->unk_0C, &hdr, sizeof(hdr));
    switch (hdr.kind) {
        case 0:
            func_ov066_02268d44(p->unk_0C);
            break;
        case 1:
            break;
        case 2:
            break;
    }
}

void func_ov066_02268d44(void *arg)
{
    char local[8];
    MI_CpuCopy8((const void *) arg, (void *) (&local), 8);
    func_ov066_02269320(data_ov066_0226bdf4 + 0x28, (char *) arg + 8);
    func_ov066_022692c0();
    if (data_ov066_0226bdec[1] == 9) {
        data_ov066_0226bdec[1] = 0xb;
    }
    func_ov066_02266bf4();
}

void func_ov066_02268d08(void)
{
    int old = OS_DisableInterrupts();
    if ((*(UnkStruct_02268d08 **) &data_ov066_0226bdf4)->c == 0) {
        (*(UnkStruct_02268d08 **) &data_ov066_0226bdf4)->b = 1;
    }
    OS_RestoreInterrupts(old);
}

int func_ov066_02268c90(void)
{
    if ((*(UnkStruct_02268c90 **) &data_ov066_0226bdf4)->flags.bit2 &&
        !(*(UnkStruct_02268c90 **) &data_ov066_0226bdf4)->flags.bit3) {
        func_ov066_0226853c();
        (*(UnkStruct_02268c90 **) &data_ov066_0226bdf4)->flags.bit3 = 1;
        (*(UnkStruct_02268c90 **) &data_ov066_0226bdf4)->flags.bit2 = 0;
        return 1;
    }
    return 0;
}
