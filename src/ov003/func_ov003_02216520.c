/* func_ov003_02216520 @ 0x02216520, 0xc4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02216520 {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x8e - 0x60];
    s16 unk_8E;
    char pad_90[0x7d4 - 0x90];
    u8 unk_7D4;
    u8 unk_7D5;
    u8 unk_7D6;
    char pad_7D7[0x800 - 0x7d7];
    int unk_800;
} UnkStruct_02216520;

extern int func_0200fc90(UnkStruct_02216520 *self);
extern int func_0200f328(UnkStruct_02216520 *self, int arg);
extern unsigned int *func_0200f27c(UnkStruct_02216520 *self, int arg);
extern int func_02095694(int a, int b);
extern void func_0204f794(int *out, u8 a, u8 b);
extern int func_020912d4(int a, int *b, s16 *c, int d);
extern void func_ov003_02224234(int a, int *b, int c);
extern void func_0200f268(UnkStruct_02216520 *self, int arg);

void func_ov003_02216520(UnkStruct_02216520 *self)
{
    s16 angle;
    int pair1[2];
    int pair2[2];
    int res[2];
    u8 *p = (u8 *) self + 0x7d4;
    int v = func_0200fc90(self);
    u8 a, b;

    if (p[2] != 0) {
        v++;
        if (v == 7) {
            func_0200f328(self, 0x83e);
        } else if (v == 9) {
            func_0200f328(self, 0x83f);
        }
    }

    func_02095694(v, self->unk_800);
    func_0200f27c(self, 9);
    func_0200f328(self, 0x83b);

    a = p[0];
    b = p[1];
    func_0204f794(res, a, b);

    angle = (s16) (self->unk_8E + 0x2000);
    func_020912d4(2, res, &angle, 0);

    if (res[0] >= self->unk_5C) {
        pair1[0] = a;
        pair1[1] = b;
        func_ov003_02224234(self->unk_800, pair1, 5);
    } else {
        pair2[0] = a;
        pair2[1] = b;
        func_ov003_02224234(self->unk_800, pair2, 4);
    }

    func_0200f268(self, 0x1c);
}
