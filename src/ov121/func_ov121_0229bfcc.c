/* func_ov121_0229bfcc @ 0x0229bfcc, 0x194 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0229bfcc_2;
struct VT {
    void (*unk_00)(struct UnkStruct_0229bfcc_2 *);
    void (*unk_04)(struct UnkStruct_0229bfcc_2 *);
    void (*unk_08)(struct UnkStruct_0229bfcc_2 *);
};
typedef struct UnkStruct_0229bfcc_2 {
    struct VT *vt;
} UnkStruct_0229bfcc_2;

typedef struct UnkStruct_0229bfcc {
    u8 pad_00[4];
    u16 f : 10;
    u16 g : 6;
} UnkStruct_0229bfcc;
extern UnkStruct_0229bfcc data_ov121_0229c2c0;
extern UnkStruct_0229bfcc data_ov121_0229c380;

typedef struct UnkStruct_0229bfcc_3 {
    u8 pad_00[0x94];
    int unk_94;
    u8 pad_98[0xa4 - 0x98];
    s16 a4;
    s16 a6;
    u8 pad_A8[0xae - 0xa8];
    u8 ae;
    u8 af;
    u8 pad_B0[0x2d8 - 0xb0];
    UnkStruct_0229bfcc_2 obj;
    u8 pad_2DC[0x3a8 - 0x2dc];
    u8 unk_3A8[0x528 - 0x3a8];
    u8 unk_528[0x118c - 0x528];
    u8 arr[8];
} UnkStruct_0229bfcc_3;

extern int func_ov121_02299a5c(UnkStruct_0229bfcc_3 *, int);
extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *);
extern void func_ov002_0220919c(void *);
extern void func_ov121_0229a0b4(UnkStruct_0229bfcc_3 *);
extern void func_ov121_0229ad40(UnkStruct_0229bfcc_3 *);
extern int func_ov121_0229af40(UnkStruct_0229bfcc_3 *, int);
extern int func_ov121_0229af58(UnkStruct_0229bfcc_3 *, int);
extern int func_020896b8(int, UnkStruct_0229bfcc *, int, int, int, int, int);
extern void func_02088df8(int, UnkStruct_0229bfcc *, int, int, int, int, int, int, int, int, int, int);

int func_ov121_0229bfcc(UnkStruct_0229bfcc_3 *self)
{
    int base;
    int p2;
    int p;
    int a;
    int z;
    u8 idx;
    int i;
    u8 k;
    UnkStruct_0229bfcc_2 *o;

    base = self->unk_94;
    if (func_ov121_02299a5c(self, 1) == 0) {
        return 1;
    }
    o = &self->obj;
    o->vt->unk_08(o);
    if (func_0206fe54() != 0) {
        func_ov002_02209eb8(self->unk_3A8);
    }
    func_ov002_0220919c(self->unk_528);
    if (func_ov121_02299a5c(self, 4) != 0) {
        if (func_0206fe54() != 0) {
            func_ov121_0229a0b4(self);
        } else {
            func_ov121_0229ad40(self);
        }
        k = self->ae;
        data_ov121_0229c2c0.f = (u16) (self->arr[k] * 4 + 0xc0);
        func_020896b8(1, &data_ov121_0229c2c0, self->a4, self->a6, self->arr[k] + 4, 2, 0);
    }
    if (func_ov121_02299a5c(self, 8) != 0) {
        k = self->af;
        p2 = base + func_ov121_0229af40(self, k);
        func_02088df8(1, &data_ov121_0229c380, func_ov121_0229af58(self, k), p2, -1, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    }
    idx = 0;
    i = 0;
    z = 0;
    for (; i < 8; idx++, i++) {
        if (func_ov121_02299a5c(self, 4) != 0 && idx == self->ae) {
            continue;
        }
        data_ov121_0229c2c0.f = (u16) (self->arr[i] * 4 + 0xc0);
        a = self->arr[i] + 4;
        p = base + func_ov121_0229af40(self, idx);
        func_020896b8(1, &data_ov121_0229c2c0, func_ov121_0229af58(self, idx), p, a, 2, z);
    }
    return 1;
}
