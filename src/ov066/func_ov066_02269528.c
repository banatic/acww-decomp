/* func_ov066_02269528 @ 0x02269528, 0x84 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef void (*Send_t)(void *buf, u32 len, int a, int b);

typedef struct UnkStruct_02269528 {
    unsigned char pad_00[0x14];
    void *unk_14;
    unsigned char pad_18[0xac - 0x18];
    Send_t unk_AC;
} UnkStruct_02269528;

typedef struct Msg {
    u16 kind;
    u16 len;
    u32 val;
} Msg;

extern UnkStruct_02269528 *data_ov066_0226bdf4;
extern u32 data_ov066_0226bdf8;
void MI_CpuCopy8(const void *src, void *dest, u32 size);

void func_ov066_02269528(void)
{
    Msg m;
    data_ov066_0226bdf8 = data_ov066_0226bdf8 * 0x5eedf715 + 0x1b0cb173;
    m.kind = 2;
    m.len = 8;
    m.val = data_ov066_0226bdf8;
    MI_CpuCopy8(&m, data_ov066_0226bdf4->unk_14, 8);
    data_ov066_0226bdf4->unk_AC(data_ov066_0226bdf4->unk_14, 8, 1, 0);
}
