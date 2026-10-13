/* func_ov066_0226696c @ 0x0226696c, 0x9c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_0226696c {
    unsigned char pad_00[4];
    int unk_04; // 0x04
    unsigned char pad_08[0x15 - 8];
    u8 retries; // 0x15
    u8 unk_16;  // 0x16
} UnkStruct_0226696c;

typedef struct Pkt {
    u16 unk_00;
    u16 unk_02;
} Pkt;

extern UnkStruct_0226696c *data_ov066_0226bdec;
void func_ov066_02266950(void);
void func_ov066_02266bf4(void);
void func_ov066_0226686c(u16);
void func_ov066_02266a08(void (*cb)(Pkt *));

void func_ov066_0226696c(Pkt *p)
{
    data_ov066_0226bdec->unk_16 = 0;
    func_ov066_02266950();
    if (p->unk_02 == 0) {
        data_ov066_0226bdec->retries = 0;
        data_ov066_0226bdec->unk_04 = 4;
        func_ov066_02266bf4();
    } else {
        data_ov066_0226bdec->retries = (u8) (data_ov066_0226bdec->retries + 1);
        if (data_ov066_0226bdec->retries > 0x10) {
            func_ov066_0226686c(p->unk_02);
        } else {
            func_ov066_02266a08(func_ov066_0226696c);
        }
    }
}
