/* obj_020dd33c_modes_5: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020594c0 @ 0x020594c0, 0xd8 bytes, Thumb
 * func_02059420 @ 0x02059420, 0xa0 bytes, Thumb
 * func_02059304 @ 0x02059304, 0x11c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x50];
    unsigned short unk_50;
    unsigned char pad_52[0x26];
    int unk_78;
    int unk_7C;
    int unk_80;
    int unk_84;
    int unk_88;
    int unk_8C;
    unsigned char pad_90[0x0c];
    int unk_9C;
    int unk_A0;
    int unk_A4;
    int unk_A8;
    int unk_AC;
    int unk_B0;
    unsigned char pad_B4[0x18];
    void *unk_CC;
    unsigned char pad_D0[0x04];
    char unk_D4;
    unsigned char pad_D5[0x03];
    char unk_D8;
} StructDef;

struct UnkStruct_02059420 {
    unsigned char pad_00[0x60];
    int unk_60;
    unsigned char pad_64[0x68 - 0x64];
    int unk_68;
    unsigned char pad_6C[0x90 - 0x6c];
    int unk_90;
    int unk_94;
    int unk_98;
    int unk_9C;
    int unk_A0;
    int unk_A4;
    unsigned char pad_A8[0xd4 - 0xa8];
    unsigned char d4;
    unsigned short d6;
};

typedef struct {
    u8 pad_00[0x50];
    u16 unk_50;
    u8 pad_52[0x60 - 0x52];
    int unk_60;
    int unk_64;
    int unk_68;
    u8 pad_6C[0x90 - 0x6c];
    int unk_90;
    int unk_94;
    int unk_98;
    int unk_9C;
    int unk_A0;
    int unk_A4;
    int unk_A8;
    int unk_AC;
    int unk_B0;
    u8 pad_B4[0xd4 - 0xb4];
    u8 unk_D4;
    u8 pad_D5[0xd6 - 0xd5];
    u16 unk_D6;
} UnkStruct_02059304;

extern int data_021c93e4[3];
extern int func_0204fd3c(int);
extern int func_02059cf8(void *a, int b);
extern void func_02059598(int *dst, void *self, int c);
extern void func_020595fc(void *self, int *dst, int *src, int d);
extern void func_02059674(void *self, int a);
extern void VEC_Add(void *a, void *b, void *c);
extern void func_0205967c(void *obj, void *field);
extern unsigned char data_020cbb00[];
extern unsigned char data_021c9348;
extern unsigned int data_020cbb34[];
extern unsigned int data_021c9400[];
extern int func_02059e10(int);
extern int FX_MulFunc(int, int);
extern int func_020e88dc(int *, int, int);
extern int func_020e895c(int *, int, int);

void func_020594c0(StructDef *self)
{
    unsigned int flag = 0;
    int local1[3];
    int local2[3];
    unsigned short value;

    self->unk_84 = flag;
    self->unk_88 = flag;
    self->unk_8C = flag;
    self->unk_78 = flag;
    self->unk_7C = flag;
    self->unk_80 = flag;
    self->unk_9C = flag;
    self->unk_A0 = flag;
    self->unk_A4 = flag;

    local1[0] = data_021c93e4[0];
    local1[1] = data_021c93e4[1];
    local1[2] = data_021c93e4[2];

    value = self->unk_50;
    if (value >= 0x12e8 && value <= 0x131f) {
        flag = 1;
    }
    if (flag > 0) {
        int diff = value - 0x12e8;
        int x = func_0204fd3c(diff);
        int y = func_02059cf8(self->unk_CC, x);
        VEC_Add(local1, (void *) y, local1);
    }

    func_02059598(local2, self, 0);
    VEC_Add(local1, local2, local1);
    func_020595fc(self, &self->unk_9C, local1, 0);

    self->unk_A8 = 0;
    self->unk_AC = 0;
    self->unk_B0 = 0;
    self->unk_D8 = 1;
    self->unk_D4 = 0;
    func_02059674(self, 1);
}

void func_02059420(void *self_raw)
{
    struct UnkStruct_02059420 *self;
    int d, v1, v2, v3;

    self = (struct UnkStruct_02059420 *) self_raw;
    func_0205967c(self, &self->unk_60);
    self->d6++;
    if (self->d6 < data_020cbb00[self->d4]) {
        return;
    }
    self->d4++;
    d = data_021c9348;

    v1 = (self->unk_9C - self->unk_60) / d;
    if (v1 < 0) {
        v1 = -v1;
    }
    self->unk_90 = v1;

    v2 = self->unk_A0 / d;
    if (v2 < 0) {
        v2 = -v2;
    }
    self->unk_94 = v2;

    v3 = (self->unk_A4 - self->unk_68) / d;
    if (v3 < 0) {
        v3 = -v3;
    }
    self->unk_98 = v3;
}

void func_02059304(UnkStruct_02059304 *self)
{
    int v;
    int nv;
    u8 idx;
    int r4, r6;
    unsigned int flag;
    u16 f;
    int diff, temp;
    struct UnkStruct_02059304_2 {
        int a;
        int b;
        int c;
    } local;

    v = self->unk_A8;
    idx = self->unk_D4;
    r4 = (int) data_020cbb34[idx];
    r6 = (int) data_021c9400[idx];
    flag = 0;
    f = self->unk_50;
    if (f >= 0x12e8 && f <= 0x131f) {
        flag = 1;
    }
    if (flag > 0) {
        diff = f - 0x12e8;
        temp = func_02059e10(func_0204fd3c(diff));
        r4 = FX_MulFunc(r4, temp);
        r6 = FX_MulFunc(r6, temp);
    }
    func_020e88dc(&v, r4, r6);
    nv = v;
    self->unk_A8 = nv;
    self->unk_AC = nv;
    self->unk_B0 = nv;

    func_0205967c(self, &local);
    func_020e895c(&self->unk_60, self->unk_9C, self->unk_90);
    func_020e895c(&self->unk_64, local.b + self->unk_A0, self->unk_94);
    func_020e895c(&self->unk_68, self->unk_A4, self->unk_98);

    self->unk_D6 = self->unk_D6 + 1;
    if (self->unk_D6 >= data_020cbb00[self->unk_D4]) {
        self->unk_D4++;
        if (self->unk_D4 >= 4) {
            func_02059674(self, 0);
        }
    }
}
