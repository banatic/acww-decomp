/* func_02058e0c @ 0x02058e0c, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkCC {
    u8 pad_00[0x8e];
    s16 unk_8E;
};

struct Unit {
    u8 pad_00[0x6c];
    u32 unk_6C;
    u32 unk_70;
    u32 unk_74;
    u32 unk_78;
    u32 unk_7C;
    u32 unk_80;
    s32 unk_84;
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
    u8 pad_9C[0x0c];
    s32 unk_A8;
    u8 pad_AC[0x14];
    s32 unk_C0;
    u8 pad_C4[0x8];
    struct UnkCC *unk_CC;
    u8 pad_D0[0x4];
    u8 unk_D4;
    u8 pad_D5[0x1];
    u16 unk_D6;
};

extern void func_0205967c(void *unit, void *tmp);
extern void func_020eaca0(void *dst, void *src1, void *src2);
extern int _s32_div_f(int val, int param);
extern void func_020ea6e0(s32 *dst, s16 val);
extern void func_02059674(void *unit, int param);

void func_02058e0c(struct Unit *unit)
{
    int tmp1[3];
    int tmp2[3];
    int r4, r6, abs84;
    s16 val;

    unit->unk_6C = 0;
    unit->unk_70 = 0;
    unit->unk_74 = 0;
    func_0205967c(unit, tmp1);
    func_020eaca0(tmp2, (char *) unit + 0x60, tmp1);
    unit->unk_84 = tmp2[0];
    unit->unk_88 = tmp2[1];
    unit->unk_8C = tmp2[2];

    if (unit->unk_CC != 0) {
        val = (s16) (-unit->unk_CC->unk_8E);
        func_020ea6e0(&unit->unk_84, val);
    }

    unit->unk_78 = 0;
    unit->unk_7C = 0;
    unit->unk_80 = 0;

    r6 = _s32_div_f(unit->unk_8C, 8);
    if (r6 < 0) {
        r6 = -r6;
    }
    r4 = _s32_div_f(unit->unk_88, 8);
    if (r4 < 0) {
        r4 = -r4;
    }
    abs84 = _s32_div_f(unit->unk_84, 8);
    if (abs84 < 0) {
        abs84 = -abs84;
    }

    unit->unk_90 = abs84;
    unit->unk_94 = r4;
    unit->unk_98 = r6;

    abs84 = _s32_div_f(unit->unk_A8, 8);
    if (abs84 < 0) {
        abs84 = -abs84;
    }
    unit->unk_C0 = abs84;

    func_02059674(unit, 1);

    unit->unk_D6 = 0;
    unit->unk_D4 = 0;
}
