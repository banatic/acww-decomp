/* func_02067c74 @ 0x02067c74, 0x108 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02067c74 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x14];
    u8 unk_1C[0x80];
    s32 unk_9C;
    s16 unk_A0;
    s16 unk_A2;
    s32 unk_A4;
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
} UnkStruct_02067c74;

extern s16 FX_SinCosTable_[];

extern int func_020e88dc(s32 *, s32, s32);
extern s32 FX_MulFunc(s32, s32);
extern void func_02068d44(void *, s32, s32);

static __inline int fsin(s16 a)
{
    return FX_SinCosTable_[(((u16) a) >> 4) * 2 + 1];
}
static __inline int fcos(s16 a)
{
    return FX_SinCosTable_[(((u16) a) >> 4) * 2];
}

void func_02067c74(UnkStruct_02067c74 *p)
{
    int ok;
    int busy;
    s32 m1, m2;
    s16 ang;

    if (p->unk_A4 != 0) {
        ok = (p->unk_04 == 3 || p->unk_04 == 2);
        busy = (func_020e88dc(&p->unk_A4, 0, p->unk_A8) != 0);
        if (ok && !busy) {
            p->unk_A0 = p->unk_A0 + 0x4000;
            m1 = FX_MulFunc(p->unk_A4, p->unk_AC);
            m2 = FX_MulFunc(p->unk_A4, p->unk_B0);
            ang = p->unk_A0;
            m1 = FX_MulFunc(fsin(ang + 0x2000), m1);
            m2 = FX_MulFunc(fcos(ang * 2 - 0x4000), m2);
            func_02068d44(p->unk_1C, -(m1 >> 12), p->unk_9C + (m2 >> 12));
        } else {
            p->unk_A0 = 0;
            p->unk_A4 = 0;
            p->unk_A8 = 0;
            p->unk_AC = 0;
            p->unk_B0 = 0;
            func_02068d44(p->unk_1C, 0, p->unk_9C);
        }
    }
}
