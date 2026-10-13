/* func_02058964 @ 0x02058964, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a;
    int b;
    int c;
} Triple;
extern u8 data_020cbaf0;
extern Triple data_021c9390;
extern int _s32_div_f(int val, int frac);

typedef struct {
    u8 pad_00[0x6c];
    int unk_6C;
    int unk_70;
    int unk_74;
    int unk_78;
    int unk_7C;
    int unk_80;
    int unk_84;
    int unk_88;
    int unk_8C;
    int unk_90;
    int unk_94;
    int unk_98;
    u8 pad_9C[0xd4 - 0x9c];
    u8 unk_D4;
    u16 unk_D6;
} UnkStruct_02058964;

void func_02058964(UnkStruct_02058964 *self)
{
    int v70, v74, v6c;

    if (self->unk_D6 >= data_020cbaf0) {
        return;
    }
    self->unk_D6 += 1;
    if (self->unk_D6 < data_020cbaf0) {
        return;
    }

    self->unk_84 = 0;
    self->unk_88 = 0;
    self->unk_8C = 0;
    self->unk_78 = 0;
    self->unk_7C = 0;
    self->unk_80 = 0;

    self->unk_6C = data_021c9390.a;
    self->unk_70 = data_021c9390.b;
    self->unk_74 = data_021c9390.c;

    v74 = _s32_div_f(self->unk_74, 0xc);
    if (v74 < 0) {
        v74 = -v74;
    }
    v70 = _s32_div_f(self->unk_70, 0xc);
    if (v70 < 0) {
        v70 = -v70;
    }
    v6c = _s32_div_f(self->unk_6C, 0xc);
    if (v6c < 0) {
        v6c = -v6c;
    }

    self->unk_90 = v6c;
    self->unk_94 = v70;
    self->unk_98 = v74;
    self->unk_D4 = 1;
}
