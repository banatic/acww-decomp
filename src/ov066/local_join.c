/* local_join: 3 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02268268 @ 0x02268268, 0x64 bytes, ARM
 * func_ov066_0226818c @ 0x0226818c, 0xdc bytes, ARM
 * func_ov066_02268098 @ 0x02268098, 0xf4 bytes, ARM
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x93];
    unsigned char unk_93;
    unsigned char unk_94;
} UnkStruct_02268268;

typedef struct UnkStruct_0226818c {
    u16 unk_00;
    unsigned char pad_02[6];
    volatile u16 kind;
} UnkStruct_0226818c;

typedef struct Ctl {
    unsigned char pad_00[0xc];
    u8 count;
} Ctl;

typedef struct Cfg {
    unsigned char pad_00[0x95];
    u8 unk_95;
} Cfg;

typedef struct UnkStruct_02268098 {
    unsigned char pad_00[0x93];
    u8 unk_93; // 0x93
    u8 unk_94; // 0x94
    u8 unk_95; // 0x95
    unsigned char pad_96[0xc0 - 0x96];
    u32 lo8 : 8;      // 0xc0 bits 0..7
    int scanning : 1; // bit 8
    u32 hi : 23;
} UnkStruct_02268098;

typedef struct Ctl_02268098 {
    unsigned char pad_00[4];
    int state; // 0x04
    unsigned char pad_08[0x20 - 8];
    u16 unk_20; // 0x20
} Ctl_02268098;

extern UnkStruct_02268268 *data_ov066_0226bdf4;
extern unsigned int data_ov066_0226bdf8;
extern Ctl *data_ov066_0226bdec;
UnkStruct_0226818c *func_ov066_02267784(int a, int idx);
int func_ov066_022683b4(const void *a, const void *b);
void func_ov066_022696b4(UnkStruct_0226818c *e, int flag);
int func_ov066_022677e0(u8 a);
void func_ov066_02268ad0(void);
void func_ov066_02267cb0(u16 a);
void func_ov066_02268370(int kind);

void func_ov066_02268268(void)
{
    data_ov066_0226bdf4->unk_94++;
    if (data_ov066_0226bdf4->unk_94 < 4) {
        return;
    }
    data_ov066_0226bdf4->unk_94 = 0;
    data_ov066_0226bdf8 = data_ov066_0226bdf8 * 0x5eedf715u + 0x1b0cb173u;
    data_ov066_0226bdf4->unk_93 = data_ov066_0226bdf8 & 3;
}

int func_ov066_0226818c(void)
{
    u8 i;
    UnkStruct_0226818c *best;
    best = 0;
    for (i = 0; i < data_ov066_0226bdec->count; i = (u8) (i + 1)) {
        UnkStruct_0226818c *e = func_ov066_02267784((*(Cfg * *) &data_ov066_0226bdf4)->unk_95, i);
        if (e->unk_00 != 0) {
            if (e->kind == 0xbd8a) {
                best = e;
                break;
            }
            if (e->kind == 0x2348) {
                if (best != 0) {
                    if (func_ov066_022683b4((u8 *) e + 2, (u8 *) best + 2) != 0) {
                        best = e;
                    }
                } else {
                    best = e;
                }
            }
        }
    }
    if (best == 0) {
        return 0;
    }
    func_ov066_022696b4(best, 1);
    return 1;
}

void func_ov066_02268098(void)
{
    int done = 0;
    if ((*(UnkStruct_02268098 * *) &data_ov066_0226bdf4)->scanning) {
        if (func_ov066_022677e0((*(UnkStruct_02268098 * *) &data_ov066_0226bdf4)->unk_95) > 0) {
            done = func_ov066_0226818c();
        }
    }
    if (done != 0) {
        return;
    }
    if ((*(UnkStruct_02268098 * *) &data_ov066_0226bdf4)->unk_94 == (*(UnkStruct_02268098 * *) &data_ov066_0226bdf4)->unk_93) {
        switch ((*(Ctl_02268098 * *) &data_ov066_0226bdec)->state) {
            case 6:
                func_ov066_02268ad0();
                break;
            case 4:
            case 7:
                func_ov066_02268268();
                func_ov066_02267cb0((*(Ctl_02268098 * *) &data_ov066_0226bdec)->unk_20);
                break;
        }
    } else {
        switch ((*(Ctl_02268098 * *) &data_ov066_0226bdec)->state) {
            case 4:
                func_ov066_02268370(0x2348);
            case 6:
                func_ov066_02268268();
                break;
        }
    }
}
