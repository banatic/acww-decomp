/* func_ov066_022682ec @ 0x022682ec, 0x84 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_022682ec {
    unsigned char pad_00[0x88];
    void *unk_88;
    unsigned char pad_8C[0xc0 - 0x8c];
    u32 unk_C0;
} UnkStruct_022682ec;

typedef struct Hdr {
    u16 unk_00;
    unsigned char pad_02[6];
    u16 unk_08;
} Hdr;

extern UnkStruct_022682ec *data_ov066_0226bdf4;
int func_ov066_022672b8(int, int, int);

int func_ov066_022682ec(Hdr *h, int b, int c)
{
    if (h != 0 && h->unk_00 != 0 && (h->unk_08 == 0x2348 || h->unk_08 == 0xbd8a)) {
        data_ov066_0226bdf4->unk_88 = h;
        data_ov066_0226bdf4->unk_C0 |= 0x200;
        return func_ov066_022672b8(5, b, c);
    }
    return 0;
}
