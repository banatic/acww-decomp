/* func_ov066_022672b8 @ 0x022672b8, 0x90 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_022672b8 {
    int cur; // 0x00
    unsigned char pad_04[0x30 - 4];
    int unk_30; // 0x30
    int unk_34; // 0x34
    unsigned char pad_38[4];
    u32 lo : 11;  // 0x3c, bits 0..10
    int busy : 1; // bit 11
    u32 hi : 20;
} UnkStruct_022672b8;

extern UnkStruct_022672b8 *data_ov066_0226bdec;
void func_ov066_02266e70(void);

int func_ov066_022672b8(int state, int a, int b)
{
    if (data_ov066_0226bdec == 0) {
        return 0;
    }
    if (state >= 7 || state == data_ov066_0226bdec->cur) {
        return 0;
    }
    data_ov066_0226bdec->cur = state;
    data_ov066_0226bdec->unk_30 = a;
    data_ov066_0226bdec->unk_34 = b;
    if (data_ov066_0226bdec->busy == 0) {
        data_ov066_0226bdec->busy = 1;
        func_ov066_02266e70();
    }
    return 1;
}
