/* func_02059304 @ 0x02059304, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern unsigned char data_020cbb00[];
extern unsigned int data_020cbb34[];
extern unsigned int data_021c9400[];
extern int func_0204fd3c(int);
extern int func_02059e10(int);
extern int FX_MulFunc(int, int);
extern int func_020e88dc(int *, int, int);
extern void func_0205967c(void *, void *);
extern int func_020e895c(int *, int, int);
extern void func_02059674(void *, int);

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
