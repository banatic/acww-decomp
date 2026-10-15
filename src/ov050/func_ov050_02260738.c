/* func_ov050_02260738 @ 0x02260738, 0x2a0 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x;
    int y;
    int z;
} Vec3;
typedef struct UnkStruct_02260738_3 {
    char pad_00[0x618];
    int unk_618;
    char pad1[0x658 - 0x61c];
    int unk_658;
    char pad_65C[0x732 - 0x65c];
    u16 unk_732;
    int unk_734;
    int unk_738;
    u8 unk_73C;
} UnkStruct_02260738_3;
typedef struct UnkStruct_02260738 {
    char pad_00[0x5c];
    Vec3 unk_5C;
    char pad1[0x8e - 0x68];
    u16 unk_8E;
} UnkStruct_02260738;
typedef struct {
    u16 a;
    u16 b;
} UnkStruct_02260738_2;
extern UnkStruct_02260738 *func_020961a8(int);
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
extern int func_02073d90(int);
extern short *func_0209d358(int, int);
extern int func_ov050_022604e0(UnkStruct_02260738_3 *);
extern int func_ov050_022604bc(UnkStruct_02260738_3 *);
extern int func_ov050_022609f0(UnkStruct_02260738_3 *);
extern int func_020984e8(void);
extern int func_0202e9fc(void);
extern int func_02062fe8(u16 *);
extern void func_ov050_02263640(void *, int);
extern int data_020ccf94;
extern int data_ov050_022650e4[][2];
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern u8 data_021f6c38;
extern u8 data_021f6c34;
extern UnkStruct_02260738_2 data_021fbe40;
extern short FX_SinCosTable_[];
int func_ov050_02260738(UnkStruct_02260738_3 *self)
{
    u16 sent[2];
    UnkStruct_02260738 *o;
    Vec3 *sp5c;
    int x;
    int z;
    int x2;
    int z2;
    Vec3 v;
    Vec3 v2;
    unsigned int a;
    unsigned int b;
    int r;
    int val;
    int t;
    int ok;
    u16 h;
    u16 c1;
    u16 c2;
    int q;
    int k;
    int i;
    o = func_020961a8(4);
    if ((data_021f6c38 != 0) && (data_021f6c34 != 0)) {
        a = 1;
    } else {
        a = 0;
    }
    if (a != 0) {
        b = 1;
    } else {
        b = 0;
    }
    if ((((o == 0) || (func_0203ec98() != 0)) || (func_02014868(&self->unk_618) != 0)) ||
        (((data_021fbe40.b & 1) == 0) && (b == 0))) {
        return 0;
    }
    if ((func_02073d90(data_020ccf94) != 0) || ((*func_0209d358(0, 0x4a)) != 0)) {
        if (func_ov050_022604e0(self) != 0) {
            return 0;
        }
    } else if ((func_ov050_022604bc(self) != 0) && (func_ov050_022609f0(self) == 0)) {
        return 0;
    }
    self->unk_732 = 0xfff1;
    sp5c = &o->unk_5C;
    v.x = sp5c->x;
    v.y = sp5c->y;
    v.z = sp5c->z;
    h = o->unk_8E;
    x = 0;
    z = 0;
    i = (h >> 4) * 2;
    v.x = v.x + FX_MulFunc(0x2000, FX_SinCosTable_[i]);
    v.z += FX_MulFunc(0x2000, FX_SinCosTable_[i + 1]);
    func_0204f818(&x, &z, &v);
    if (b != (0)) {
        val = func_ov004_0223cc10(func_ov004_0223cd50(), x, z, 0);
        r = val;
        if (r != 0) {
            if (r != func_020b7524(func_020b6590(), 0, 0)) {
                return 0;
            }
        } else {
            x2 = 0;
            z2 = 0;
            func_020b758c(func_020b6590(), &v2);
            func_0204f818(&x2, &z2, &v2);
            if ((x2 != x) || (z2 != z)) {
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
        ok = (sent[0] == 0xfff1) ? (1) : (0);
    }
    if (ok != 0) {
        return 0;
    }
    r = 0;
    q = 0;
    k = 5;
    if (func_ov050_022604bc(self) != 0) {
        q = 1;
    }
    r = 0;
    c1 = sent[0];
    c2 = *((volatile u16 *) (&sent[0]));
    if ((c2 >= 0x1100) && (c1 <= 0x1143)) {
        r = 1;
    }
    if ((r != 0) || ((c1 >= 0x1144) && (c1 <= 0x1187))) {
        k = 0;
    } else if ((c1 >= 0x1000) && (c1 <= 0x10ff)) {
        k = 1;
    } else if ((c1 >= 0x1521) && (c1 <= 0x1530)) {
        if (((void) (func_020984e8()), func_0202e9fc()) != 0) {
            k = 2;
        } else {
            k = 3;
        }
    } else if (func_02062fe8(&sent[0]) != 0) {
        k = 4;
    }
    func_ov050_02263640(&self->unk_658, data_ov050_022650e4[k][q]);
    self->unk_732 = sent[0];
    self->unk_734 = x;
    self->unk_738 = z;
    self->unk_73C = 0;
    return 1;
}
