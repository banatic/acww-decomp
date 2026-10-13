/* func_ov066_02269638 @ 0x02269638, 0x7c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_02269638 {
    unsigned char pad_00[8];
    u8 *unk_08;
    unsigned char pad_0C[0x18 - 0xc];
    u16 unk_18;
    unsigned char pad_1A[0xc0 - 0x1a];
    u32 unk_C0;
} UnkStruct_02269638;

extern UnkStruct_02269638 *data_ov066_0226bdf4;
void MI_CpuCopy8(const void *src, void *dest, u32 size);

int func_ov066_02269638(const void *src, u32 len)
{
    UnkStruct_02269638 *c = data_ov066_0226bdf4;
    u8 *buf;
    if (c != 0 && len <= 0x68) {
        buf = c->unk_08;
        c->unk_C0 |= 0x10;
        MI_CpuCopy8(src, buf + 8, len);
        buf[7] = (u8) len;
        data_ov066_0226bdf4->unk_18 = (u16) ((len + 9) & ~1);
        return 1;
    }
    return 0;
}
