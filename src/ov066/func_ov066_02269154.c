/* func_ov066_02269154 @ 0x02269154, 0xb0 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

extern void func_ov066_0226987c(unsigned int, unsigned char);
extern void func_ov066_022687f4(void);
extern void func_ov066_02266bf4(void);

struct UnkStruct_02269154 {
    u8 pad_00[0x8c];
    u8 unk_8C;
    u8 pad_8D[0x9];
    u8 unk_96;
    u8 pad_97[0x29];
    u32 c0 : 4;
    int flag : 1;
    u32 c0_rest : 27;
};

struct UnkStruct_02269154_2 {
    u8 pad_00[4];
    u32 unk_04;
    u8 pad_08[0xc];
    u8 unk_14;
};

extern struct UnkStruct_02269154 *data_ov066_0226bdf4;
extern struct UnkStruct_02269154_2 *data_ov066_0226bdec;

void func_ov066_02269154(void)
{
    if (data_ov066_0226bdf4->flag) {
        func_ov066_0226987c(0xe34d, data_ov066_0226bdf4->unk_8C);
        func_ov066_022687f4();
        data_ov066_0226bdf4->flag = 0;
    }
    if (data_ov066_0226bdec->unk_04 == 6) {
        data_ov066_0226bdf4->unk_96++;
        if (data_ov066_0226bdf4->unk_96 < data_ov066_0226bdec->unk_14) {
            return;
        }
        func_ov066_02266bf4();
    } else {
        return;
    }
}
