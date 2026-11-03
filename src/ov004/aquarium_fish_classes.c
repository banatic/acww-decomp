/* aquarium_fish_classes: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02238504 @ 0x02238504, 0x94 bytes, Thumb
 * func_ov004_022384c0 @ 0x022384c0, 0x44 bytes, Thumb
 * func_ov004_02238488 @ 0x02238488, 0x38 bytes, Thumb
 * func_ov004_02238448 @ 0x02238448, 0x40 bytes, Thumb
 * func_ov004_02238414 @ 0x02238414, 0x34 bytes, Thumb
 * func_ov004_02238340 @ 0x02238340, 0xd4 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02238448 {
    u8 pad_00[0x110];
    int left;
    u8 pad_114[0x158 - 0x114];
    int done;
    u8 pad_15C[0x204 - 0x15c];
    int step;
    int total;
    u8 pad_20C[0x20e - 0x20c];
    u8 phase;
};

struct UnkStruct_02238340 {
    u8 unk_00[0x11];
};

struct UnkStruct_02238340_2 {
    u8 pad_00[0x15c];
    int unk_15C;
    u8 pad_160[0x1c8 - 0x160];
    u8 unk_1C8;
    u8 pad_1C9[0x1e8 - 0x1c9];
    u8 unk_1E8;
    u8 unk_1E9;
    u8 pad_1EA[0x204 - 0x1ea];
    u8 unk_204;
    u8 unk_205;
    u8 unk_206;
    u8 unk_207;
    u8 pad_208[0x210 - 0x208];
    int unk_210;
    int unk_214;
    int unk_218;
    u8 pad_21C[0x230 - 0x21c];
    s16 unk_230;
    u8 pad_232[0x258 - 0x232];
    int unk_258;
    int unk_25C;
    int unk_260;
};

extern int func_ov004_02239460(int a, int b);
extern int _s32_div_f(int a, int b);
extern struct UnkStruct_02238340 data_ov004_02247924[];
extern struct UnkStruct_02238340_2 *data_ov004_022593b8;

void func_ov004_02238504(void *self)
{
    *(int *) ((char *) self + 0x208) = _s32_div_f(func_ov004_02239460(0xb, 0xf) << 12, 0xa);
    *(int *) ((char *) self + 0x200) = _s32_div_f(func_ov004_02239460(0x14, 0x32) << 12, 0x3e8);
    *(int *) ((char *) self + 0x204) = _s32_div_f(func_ov004_02239460(0xa, 0x1e) << 12, 0x3e8);
    *((char *) self + 0x20c) = (char) func_ov004_02239460(1, 0x96);
    *((char *) self + 0x20d) = (char) func_ov004_02239460(0xa, 0x78);
    *(int *) ((char *) self + 0x158) = 0;
    *(int *) ((char *) self + 0x110) = 0;
    *((char *) self + 0x20e) = 1;
}

void func_ov004_022384c0(char *self)
{
    int v = 5 * (*(int *) (self + 0x200) * *(int *) (self + 0x158));
    int lim = *(int *) (self + 0x208);
    if (v >= lim) {
        v = lim;
        *(char *) (self + 0x20e) = 2;
        *(int *) (self + 0x158) = 0;
    }
    *(int *) (self + 0x110) = v;
}

void func_ov004_02238488(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x158) >= *(u8 *) (self + 0x20c)) {
        *(u8 *) (self + 0x20e) = 0x3;
        *(void **) (self + 0x158) = 0x0;
    }
    *(int *) (self + 0x110) = *(int *) (self + 0x208);
}

void func_ov004_02238448(struct UnkStruct_02238448 *self)
{
    int n;

    n = self->total - self->step * self->done;
    if (n <= 0) {
        n = 0;
        self->phase = 4;
        self->done = 0;
    }
    self->left = n;
}

void *func_ov004_02238414(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self + 0x110) = 0x0;
    if (*(int *) (self + 0x158) >= *(u8 *) (self + 0x20d)) {
        *(u8 *) (self + 0x20e) = 0x0;
        *(void **) (self + 0x158) = 0x0;
        return self;
    }
    return self;
}

void func_ov004_02238340(struct UnkStruct_02238340_2 *self)
{
    self->unk_1E8 = self->unk_15C;
    self->unk_1E9 = self->unk_15C;
    self->unk_1C8 = 0;
    self->unk_210 = 0x3a;
    self->unk_214 = 1;
    self->unk_218 = 1;
    self->unk_230 = 0x1e;
    self->unk_258 = 0x6000;
    self->unk_25C = 0;
    self->unk_260 = 0x14a00;
    self->unk_204 = data_ov004_02247924[self->unk_15C].unk_00[8];
    self->unk_205 = data_ov004_02247924[self->unk_15C].unk_00[9];
    self->unk_206 = data_ov004_02247924[self->unk_15C].unk_00[0xa];
    self->unk_207 = data_ov004_02247924[self->unk_15C].unk_00[0xb];
    data_ov004_022593b8 = self;
}
