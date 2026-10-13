/* func_0200cac0 @ 0x0200cac0, 0x13c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Vec3 {
    int x;
    int y;
    int z;
};

struct UnkStruct_0200cac0 {
    u8 pad_00[0x8e];
    s16 unk_8E;
    u8 pad_90[0x6c8 - 0x90];
    int unk_6C8;
    int unk_6CC;
    int unk_6D0;
    u8 pad_6D4[0x7d4 - 0x6d4];
    s16 unk_7D4;
    s16 unk_7D6;
};

extern void func_020109fc(struct UnkStruct_0200cac0 *self, int a, int b, int c);
extern void func_0200cbfc(unsigned short *p, int val);
extern int FX_MulFunc(int a, int b);
extern void func_020912d4(int a, struct Vec3 *pos, s16 *ang, int d);
extern void func_0200f328(struct UnkStruct_0200cac0 *self, int code);
extern s16 FX_SinCosTable_[];

void func_0200cac0(struct UnkStruct_0200cac0 *self, void *arg)
{
    s16 ang;
    struct Vec3 v;
    void *base;
    s16 self_ang;
    int shifted_self;
    int shifted_ang;
    int diff;
    int abs_diff;
    int t;
    int sv;
    int cv;

    ang = *(s16 *) ((char *) arg + 0xc);
    base = (char *) self + 0x7d4;
    func_020109fc(self, 4, 3, 0);
    func_0200cbfc((unsigned short *) base, ang);

    self_ang = self->unk_8E;
    shifted_self = self_ang << 12;
    shifted_ang = ang << 12;
    diff = shifted_ang - shifted_self;
    if (diff < 0) {
        abs_diff = -diff;
    } else {
        abs_diff = diff;
    }

    if (shifted_ang >= shifted_self) {
        if (abs_diff > 0x08000000) {
            ang += 0x6fd0;
        } else {
            ang += 0x9030;
        }
    } else {
        if (abs_diff > 0x08000000) {
            ang += 0x9030;
        } else {
            ang += 0x6fd0;
        }
    }

    v.x = self->unk_6C8;
    v.y = self->unk_6CC;
    v.z = self->unk_6D0;

    sv = FX_SinCosTable_[((u16) ang >> 4) * 2];
    cv = FX_SinCosTable_[((u16) ang >> 4) * 2 + 1];

    t = FX_MulFunc(cv, 0x666);
    t -= FX_MulFunc(sv, 0x666);
    sv = FX_MulFunc(sv, 0x666);
    cv = FX_MulFunc(cv, 0x666);
    sv += cv;
    v.x += sv;
    v.z += t;

    *(s16 *) ((char *) base + 2) = ang + 0x8000;
    *(s16 *) ((char *) base + 2) = *(s16 *) ((char *) base + 2) - 0x38e;

    func_020912d4(1, &v, &ang, 0);
    func_0200f328(self, 0x53);
}
