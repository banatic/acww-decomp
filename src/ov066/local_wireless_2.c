/* local_wireless_2: 3 functions, module ov066
 * mwccarm 1.2/base -O4,p
 * func_ov066_02266a08 @ 0x02266a08, 0x44 bytes, ARM
 * func_ov066_0226696c @ 0x0226696c, 0x9c bytes, ARM
 * func_ov066_02266950 @ 0x02266950, 0x1c bytes, ARM
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x3c];
    unsigned long unk_3C;
} UnkStruct_02266a08;

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

typedef struct {
    unsigned char pad_00[0x3c];
    unsigned int flags;
} UnkStruct_02266950;

extern UnkStruct_02266a08 *data_ov066_0226bdec;
extern int WM_Reset(void (*callback)(void *));
extern void func_ov066_0226686c(int mode);
void func_ov066_02266bf4(void);

void func_ov066_02266950(void);

void func_ov066_02266a08(void (*callback)(void *))
{
    int mode = WM_Reset(callback);
    data_ov066_0226bdec->unk_3C |= 0x400;
    if (mode == 2) {
        return;
    }
    func_ov066_0226686c(mode);
}

void func_ov066_0226696c(Pkt *p)
{
    (*(UnkStruct_0226696c * *) &data_ov066_0226bdec)->unk_16 = 0;
    func_ov066_02266950();
    if (p->unk_02 == 0) {
        (*(UnkStruct_0226696c * *) &data_ov066_0226bdec)->retries = 0;
        (*(UnkStruct_0226696c * *) &data_ov066_0226bdec)->unk_04 = 4;
        func_ov066_02266bf4();
    } else {
        (*(UnkStruct_0226696c * *) &data_ov066_0226bdec)->retries = (u8) ((*(UnkStruct_0226696c * *) &data_ov066_0226bdec)->retries + 1);
        if ((*(UnkStruct_0226696c * *) &data_ov066_0226bdec)->retries > 0x10) {
            func_ov066_0226686c((u16) p->unk_02);
        } else {
            func_ov066_02266a08((void (*)(void *)) func_ov066_0226696c);
        }
    }
}

void func_ov066_02266950(void)
{
    (*(UnkStruct_02266950 * *) &data_ov066_0226bdec)->flags &= ~0x400;
}
