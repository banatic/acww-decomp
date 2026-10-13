/* func_ov066_02268da4 @ 0x02268da4, 0x70 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_02268da4 {
    unsigned char pad_00[0xc];
    void *unk_0C;
    u16 unk_10;
} UnkStruct_02268da4;

typedef struct Hdr {
    u16 kind;
    u16 unk_02;
} Hdr;

void MI_CpuCopy8(const void *src, void *dest, u32 size);
void func_ov066_02268d44(void *p);

void func_ov066_02268da4(UnkStruct_02268da4 *p)
{
    Hdr hdr;

    if (p->unk_10 == 0) {
        return;
    }
    MI_CpuCopy8(p->unk_0C, &hdr, sizeof(hdr));
    switch (hdr.kind) {
        case 0:
            func_ov066_02268d44(p->unk_0C);
            break;
        case 1:
            break;
        case 2:
            break;
    }
}
