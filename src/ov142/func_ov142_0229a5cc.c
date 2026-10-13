/* func_ov142_0229a5cc @ 0x0229a5cc, 0x78 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229a5cc {
    char pad_00[0xB4];
    short unk_B4;
    char pad_B6[0x1860 - 0xB6];
    u8 unk_1860[0x800];
    u8 unk_2060[0x800];
};

extern void MIi_CpuClear16(u16, void *, unsigned int);
extern void MIi_CpuCopy16(void *, void *, unsigned int);
extern void func_ov142_02299658(struct UnkStruct_0229a5cc *, int);

void func_ov142_0229a5cc(struct UnkStruct_0229a5cc *p)
{
    int r4, r6, r7, zero;
    volatile u16 val;

    r4 = p->unk_B4;
    r6 = (r4 + 9) % 9;
    r4 &= 0xF;

    val = 0x10;
    MIi_CpuClear16(val, &p->unk_2060, 0x800);

    zero = 0;
    r7 = 0;
    do {
        MIi_CpuCopy16(&p->unk_1860[r6 * 128], &p->unk_2060[r4 * 128], 0x80);
        r6++;
        if (r6 >= 9) {
            r6 = zero;
        }
        r4++;
        r4 &= 0xF;
        r7++;
    } while (r7 < 9);

    func_ov142_02299658(p, 2);
}
