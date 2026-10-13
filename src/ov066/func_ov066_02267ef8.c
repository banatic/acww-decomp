/* func_ov066_02267ef8 @ 0x02267ef8, 0xf0 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern void *func_ov066_02266908(u32 size, u32 align);
extern void func_ov066_0226a810(void *dest, u8 idx, u8 width);
extern void OS_CreateAlarm(void *p);

struct State {
    u8 pad_00[9];
    u8 count;
    u8 pad_0A[2];
    u8 unk_0C;
};

struct Context {
    void *unk_00;
    void *unk_04;
    void *unk_08;
};

extern struct Context *data_ov066_0226bdf0;
extern struct State *data_ov066_0226bdec;

void func_ov066_02267ef8(void)
{
    int i;

    data_ov066_0226bdf0 = (struct Context *) func_ov066_02266908(0x70, 4);
    data_ov066_0226bdf0->unk_00 = func_ov066_02266908(0x20, 0x20);
    data_ov066_0226bdf0->unk_04 = func_ov066_02266908(0xc0, 0x20);
    data_ov066_0226bdf0->unk_08 = func_ov066_02266908(data_ov066_0226bdec->count << 4, 4);

    for (i = 0; i < data_ov066_0226bdec->count; i++) {
        func_ov066_0226a810((char *) data_ov066_0226bdf0->unk_08 + i * 0x10, (u8) i, data_ov066_0226bdec->unk_0C);
    }

    OS_CreateAlarm((char *) data_ov066_0226bdf0 + 0x10);
    OS_CreateAlarm((char *) data_ov066_0226bdf0 + 0x3c);
}
