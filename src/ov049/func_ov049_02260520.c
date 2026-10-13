/* func_ov049_02260520 @ 0x02260520, 0x260 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02260520_3 {
    char pad_00[0x618];
    int unk_618;
    char pad1[0x658 - 0x61c];
    int unk_658;
    char pad_65C[0x728 - 0x65c];
    int unk_728;
    int unk_72C;
    char pad_730[0x738 - 0x730];
    u16 unk_738;
    char pad_73A[0x974 - 0x73a];
    u8 unk_974;
} UnkStruct_02260520_3;

typedef struct UnkStruct_02260520 {
    char pad_00[0x5c];
    Vec3 unk_5C;
    char pad1[0x8e - 0x68];
    u16 unk_8E;
} UnkStruct_02260520;

typedef struct {
    u16 a;
    u16 b;
} UnkStruct_02260520_2;

extern UnkStruct_02260520 *func_020961a8(int);
extern int func_0203ec98(void);
extern int func_02014868(void *);
extern int FX_MulFunc(int, int);
extern void func_0204f818(int *, int *, Vec3 *);
extern int func_ov004_0223cd50(void);
extern int func_ov004_0223cc10(int, int, int, int);
extern int func_020b6590(void);
extern int func_020b7524(int, int, int);
extern void func_020b758c(int, Vec3 *);
extern u16 *func_ov004_022460c8(int, int);
extern void func_02061e2c(u16 *, u16 *);
extern void func_ov049_0226208c(void *, int);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);

extern u8 data_021f6c38;
extern u8 data_021f6c34;
extern UnkStruct_02260520_2 data_021fbe40;
extern short FX_SinCosTable_[];

int func_ov049_02260520(UnkStruct_02260520_3 *self)
{
    u16 sent[3];
    UnkStruct_02260520 *o;
    Vec3 *sp5c;
    int x, z;
    int x2, z2;
    Vec3 v;
    Vec3 v2;
    unsigned int a;
    unsigned int b;
    int r;
    int t;
    int ok;
    u16 h;
    u16 c1;
    u16 c2;
    int i;

    o = func_020961a8(4);
    if (data_021f6c38 != 0 && data_021f6c34 != 0) {
        a = 1;
    } else {
        a = 0;
    }
    if (a != 0) {
        b = 1;
    } else {
        b = 0;
    }

    if (o == 0 || func_0203ec98() != 0 || func_02014868(&self->unk_618) != 0 || ((data_021fbe40.b & 1) == 0 && b == 0)) {
        return 0;
    }

    self->unk_738 = 0xfff1;
    sp5c = &o->unk_5C;
    v.x = sp5c->x;
    v.y = sp5c->y;
    v.z = sp5c->z;
    h = o->unk_8E;
    x = 0;
    z = 0;
    i = (h >> 4) * 2;
    v.x = v.x + FX_MulFunc(0x2000, FX_SinCosTable_[i]);
    v.z = v.z + FX_MulFunc(0x2000, FX_SinCosTable_[i + 1]);
    func_0204f818(&x, &z, &v);

    if (b != 0) {
        r = func_ov004_0223cc10(func_ov004_0223cd50(), x, z, 0);
        if (r != 0) {
            if (r != func_020b7524(func_020b6590(), 0, 0)) {
                return 0;
            }
        } else {
            x2 = 0;
            z2 = 0;
            func_020b758c(func_020b6590(), &v2);
            func_0204f818(&x2, &z2, &v2);
            if (x2 != x || z2 != z) {
                return 0;
            }
        }
    }

    sent[0] = *func_ov004_022460c8(x, z);
    if (func_0204bcdc(&sent[0]) != 0) {
        sent[2] = 0xfff1;
        t = func_0204bc64(&sent[0]);
        if (t == func_0204bc64(&sent[2])) {
            ok = 1;
        } else {
            ok = 0;
        }
    } else {
        ok = (sent[0] == 0xfff1) ? 1 : 0;
    }
    if (ok != 0) {
        return 0;
    }

    r = 0;
    c1 = sent[0];
    c2 = *(volatile u16 *) &sent[0];
    if (c2 >= 0x3984 && c1 <= 0x3d83) {
        r = 1;
    }
    if (r != 0 || (sent[0] >= 0x3fa4 && sent[0] <= 0x40a3) || (sent[0] >= 0x40a4 && sent[0] <= 0x4123) ||
        (sent[0] >= 0x4124 && sent[0] <= 0x4223) || (sent[0] >= 0x3e24 && sent[0] <= 0x3ea3)) {
        func_02061e2c(&sent[1], &sent[0]);
        sent[0] = sent[1];
        func_ov049_0226208c(&self->unk_658, 4);
    } else if (sent[0] >= 0x3e04 && sent[0] <= 0x3e23) {
        func_ov049_0226208c(&self->unk_658, 5);
    } else {
        return 0;
    }

    self->unk_738 = sent[0];
    self->unk_728 = x;
    self->unk_72C = z;
    self->unk_974 = 0;
    return 1;
}
