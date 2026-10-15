/* func_ov003_0220e244 @ 0x0220e244, 0x1e0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;
struct UnkStruct_0220e244 {
    fx32 unk_00;
    fx32 unk_04;
    fx32 unk_08;
    fx32 unk_0C;
    fx32 unk_10;
    u16 unk_14;
};
struct Actor {
    unsigned char pad_00[0x7d4];
    fx32 unk_7D4;
    unsigned char pad_7D8[0x28];
    fx32 unk_800;
};
extern short FX_SinCosTable_[];
extern void *data_020ccf94;
extern u16 data_021fbe40[];
extern int func_02073908(void *, fx32);
extern fx32 FX_MulFunc(fx32, fx32);
extern fx32 FX_Div(fx32, fx32);
extern fx32 VEC_Mag(const VecFx32 *);
extern void func_020eaca0(VecFx32 *, const VecFx32 *, const VecFx32 *);
extern fx32 func_0200dc8c(struct Actor *);
extern fx32 func_0200dc80(struct Actor *);
extern int func_0200f328(struct Actor *, int);
extern int func_0200f290(struct Actor *, int);
extern void *func_ov003_0220e1f0(struct Actor *, int, int);
void func_ov003_0220e244(struct Actor *self)
{
    fx32 prev;
    int idx;
    fx32 a;
    fx32 b;
    VecFx32 v1;
    VecFx32 v2;
    u16 val;
    VecFx32 d;
    u16 val2;
    VecFx32 diff;
    struct UnkStruct_0220e244 *p;
    fx32 *acc;
    int idx2;
    fx32 r;
    int add;
    u16 f;
    if (func_02073908(data_020ccf94, self->unk_800) == 0) {
        return;
    }
    p = (struct UnkStruct_0220e244 *) (&self->unk_7D4);
    acc = &p->unk_10;
    prev = p->unk_00;
    val = p->unk_14;
    v2.y = 0;
    v1.y = 0;
    idx = (val >> 4) * 2;
    v1.x = FX_MulFunc(FX_SinCosTable_[idx], prev);
    v1.z = FX_MulFunc(FX_SinCosTable_[idx + 1], prev);
    a = func_0200dc8c(self);
    b = func_0200dc80(self);
    idx2 = (((u16) b) >> 4) * 2;
    v2.x = FX_MulFunc(FX_SinCosTable_[idx2], a);
    v2.z = FX_MulFunc(FX_SinCosTable_[idx2 + 1], a);
    self->unk_7D4 = a;
    p->unk_14 = (u16) b;
    r = 0;
    func_020eaca0(&diff, &v1, &v2);
    d.x = diff.x;
    d.y = diff.y;
    d.z = diff.z;
    if (VEC_Mag(&d) >= 0x59a) {
        r = FX_Div(FX_MulFunc(VEC_Mag(&d), 0x6400), 0x59a);
    }
    add = 0;
    f = data_021fbe40[1];
    if (f & 1) {
        add += 0x14;
    }
    if (f & 2) {
        add += 0x14;
    }
    if (f & 0x400) {
        add += 0x14;
    }
    val2 = f;
    if (val2 & 0x800) {
        add += 0x14;
    }
    if (val2 & 0x200) {
        add += 0x14;
    }
    if (val2 & 0x100) {
        add += 0x14;
    }
    if (val2 & 8) {
        add += 0x14;
    }
    if (val2 & 4) {
        add += 0x14;
    }
    r = r + (add << 12);
    if (r == 0) {
        r = r + 0x2000;
    }
    *acc = (*acc) + r;
    p->unk_0C = r >> 12;
    if ((*acc) < 0) {
        *acc = 0;
    }
    if (r != 0) {
        if ((a != 0) || (add != 0)) {
            func_0200f328(self, 0x7ef);
        }
        p->unk_08 = FX_Div(FX_MulFunc(FX_MulFunc(0x1c00, *acc), 0xa66), 0x190000) + 0x800;
    }
    if ((func_0200f290(self, 0xb) != 0) || (p->unk_10 >= 0x190000)) {
        func_ov003_0220e1f0(self, 6, -1);
    }
}
