/* func_ov052_02260574 @ 0x02260574, 0x1a4 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02260574_3 {
    char pad_00[0x618];
    int unk_618;
    char pad1[0x71e - 0x61c];
    u16 unk_71E;
    char pad_720[0x728 - 0x720];
    int unk_728;
    int unk_72C;
    u8 unk_730;
} UnkStruct_02260574_3;

typedef struct UnkStruct_02260574 {
    char pad_00[0x5c];
    Vec3 unk_5C;
    char pad1[0x8e - 0x68];
    u16 unk_8E;
} UnkStruct_02260574;

typedef struct {
    u16 a;
    u16 b;
} UnkStruct_02260574_2;

extern UnkStruct_02260574 *func_020961a8(int);
extern int func_0203ec98(void);
extern int func_02014868(void *);
extern int FX_MulFunc(int, int);
extern void func_0204f818(int *, int *, Vec3 *);
extern int func_ov004_0223cd50(void);
extern int func_ov004_0223cc10(int, int, int, int);
extern int func_020b6590(void);
extern int func_020b7524(int, int, int);
extern int func_020b758c(int, Vec3 *);
extern u16 *func_ov004_02246378(int, int);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);

extern u8 data_021f6c38;
extern u8 data_021f6c34;
extern UnkStruct_02260574_2 data_021fbe40;
extern short FX_SinCosTable_[];

int func_ov052_02260574(UnkStruct_02260574_3 *self)
{
    u16 sent[2];
    UnkStruct_02260574 *o;
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

    sent[0] = *func_ov004_02246378(x, z);
    if (func_0204bcdc(&sent[0]) != 0) {
        sent[1] = 0xfff1;
        t = func_0204bc64(&sent[0]);
        if (t == func_0204bc64(&sent[1])) {
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

    self->unk_71E = sent[0];
    self->unk_728 = x;
    self->unk_72C = z;
    self->unk_730 = 0;
    return 1;
}
