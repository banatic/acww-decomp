/* func_ov066_02268098 @ 0x02268098, 0xf4 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

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

typedef struct Ctl {
    unsigned char pad_00[4];
    int state; // 0x04
    unsigned char pad_08[0x20 - 8];
    u16 unk_20; // 0x20
} Ctl;

extern UnkStruct_02268098 *data_ov066_0226bdf4;
extern Ctl *data_ov066_0226bdec;
int func_ov066_022677e0(u8 a);
int func_ov066_0226818c(void);
void func_ov066_02268ad0(void);
void func_ov066_02268268(void);
void func_ov066_02267cb0(u16 a);
void func_ov066_02268370(int kind);

void func_ov066_02268098(void)
{
    int done = 0;
    if (data_ov066_0226bdf4->scanning) {
        if (func_ov066_022677e0(data_ov066_0226bdf4->unk_95) > 0) {
            done = func_ov066_0226818c();
        }
    }
    if (done != 0) {
        return;
    }
    if (data_ov066_0226bdf4->unk_94 == data_ov066_0226bdf4->unk_93) {
        switch (data_ov066_0226bdec->state) {
            case 6:
                func_ov066_02268ad0();
                break;
            case 4:
            case 7:
                func_ov066_02268268();
                func_ov066_02267cb0(data_ov066_0226bdec->unk_20);
                break;
        }
    } else {
        switch (data_ov066_0226bdec->state) {
            case 4:
                func_ov066_02268370(0x2348);
            case 6:
                func_ov066_02268268();
                break;
        }
    }
}
