/* func_ov066_022695ac @ 0x022695ac, 0x8c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct Mac {
    u8 b[6];
} Mac;

typedef struct UnkStruct_022695ac {
    unsigned char pad_00[0x28];
    Mac macs[1];
} UnkStruct_022695ac;

extern UnkStruct_022695ac *data_ov066_0226bdf4;
void MI_CpuCopy8(const void *src, void *dest, u32 size);
void MI_CpuFill8(void *dest, u8 data, u32 size);
void func_ov066_022692c0(void);

void func_ov066_022695ac(int idx, const Mac *src)
{
    Mac tmp;
    if (src != 0) {
        MI_CpuCopy8(src, &tmp, 6);
    } else {
        MI_CpuFill8(&tmp, 0, 6);
    }
    data_ov066_0226bdf4->macs[idx] = tmp;
    func_ov066_022692c0();
}
