/* func_0200bc38 @ 0x0200bc38, 0x168 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0200bc38_2 {
    int a;
    u8 b;
    u8 c;
} UnkStruct_0200bc38_2;
typedef struct Arg {
    u8 pad_00[0xc];
    UnkStruct_0200bc38_2 sub;
} Arg;
typedef struct UnkStruct_0200bc38 {
    int unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
} UnkStruct_0200bc38;

typedef struct UnkStruct_0200bc38_3 {
    u8 pad_00[0x5a0];
    u8 unk_5A0;
    u8 pad_5A1[0x704 - 0x5a1];
    int unk_704;
    u8 pad_708[0x7d4 - 0x708];
    UnkStruct_0200bc38 e;
    u8 pad_7DC[0x820 - 0x7dc];
    u16 unk_820;
    u16 unk_822;
    u8 unk_824;
    u8 pad_825[0x830 - 0x825];
    int unk_830;
    int unk_834;
    int unk_838;
    u8 pad_83C[0x8f0 - 0x83c];
    u8 unk_8F0;
} UnkStruct_0200bc38_3;

extern void *data_021c80bc;

extern void func_0200f268(UnkStruct_0200bc38_3 *s, int k);
extern void func_0200bdb0(u8 *dst, const unsigned int *src, unsigned int val);
extern void func_0204f794(void *p, int a, int b);
extern u16 *func_0204f5a8(void *h, void *p, int z);
extern int func_02099fe8(void);
extern int func_020b67d4(void);
extern void func_020109fc(UnkStruct_0200bc38_3 *s, int a, int b, int c);
extern unsigned int func_020b2300(void);
extern void func_ov004_0223bb20(int a, u16 *b, u16 *c);
extern void func_020109a0(UnkStruct_0200bc38_3 *s, int a, int b, int c);
extern int func_0200fbe0(UnkStruct_0200bc38_3 *s);
extern void func_0205eae0(void *p, int a, int b, int c);

void func_0200bc38(UnkStruct_0200bc38_3 *self, Arg *arg)
{
    unsigned int pair[2];
    UnkStruct_0200bc38_2 *s;
    UnkStruct_0200bc38 *e;
    int v;
    int a;
    int b;
    unsigned int ok;
    u16 h;

    s = &arg->sub;
    a = s->b;
    b = s->c;
    v = arg->sub.a;
    func_0200f268(self, 0xd);
    e = &self->e;
    e->unk_00 = v;
    e->unk_05 = (u8) a;
    e->unk_06 = (u8) b;
    e->unk_04 = 0;
    pair[0] = a;
    pair[1] = b;
    func_0200bdb0(&self->unk_8F0, pair, v);
    if (v < 0) {
        func_0204f794(&self->unk_824, a, b);
        self->unk_830 = 0x1000;
        self->unk_834 = 0x1000;
        self->unk_838 = 0x1000;
        self->unk_822 = *func_0204f5a8(data_021c80bc, &self->unk_824, 0);
        self->unk_820 = self->unk_822;
    }
    if (func_02099fe8() == -1) {
        if (func_020b67d4() != 0) {
            ok = 0;
            h = self->unk_820;
            if (h >= 0xa7 && h <= 0xc6) {
                ok = 1;
            }
            if (ok == 0) {
                func_020109fc(self, 0, 3, 0);
                e->unk_04 = 3;
                goto tail;
            }
        }
    }
    if (v >= 0) {
        if (func_020b2300() <= 1) {
            func_ov004_0223bb20(e->unk_00, &self->unk_820, &self->unk_822);
            func_020109a0(self, 0x15, 3, 0);
        } else {
            e->unk_04 = 7;
            func_020109fc(self, 0, 3, 0);
        }
    } else {
        if (v == -3) {
            e->unk_04 = 7;
            func_020109fc(self, 0, 3, 0);
        } else {
            func_020109fc(self, 0x15, 3, 0);
        }
    }
tail:
    if (self->unk_704 == 0x15) {
        if (func_0200fbe0(self) == 4) {
            func_0205eae0(&self->unk_5A0, 0xb, 3, 0);
        }
    }
}
