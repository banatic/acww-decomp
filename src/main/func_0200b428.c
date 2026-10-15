/* func_0200b428 @ 0x0200b428, 0x36c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    u16 unk_00;
    u16 pad_02;
    int unk_04;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
} UnkStruct_0200b428;

typedef struct {
    u8 pad_00[0xc];
    UnkStruct_0200b428 sub;
} Arg;

typedef struct {
    u8 unk_00;
    u8 pad_01[3];
    int unk_04;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
} Rec;

typedef struct {
    u8 pad_00[0x5c];
    int unk_5C;
    u8 pad_60[0x5a0 - 0x60];
    u8 unk_5A0[0x7d4 - 0x5a0];
    Rec unk_7D4;
    u8 pad_7E0[0x800 - 0x7e0];
    int unk_800;
    u8 pad_804[0x820 - 0x804];
    u16 unk_820;
    u16 unk_822;
    u8 unk_824[0x830 - 0x824];
    int unk_830;
    int unk_834;
    int unk_838;
    u8 pad_83C[0x8f0 - 0x83c];
    u8 unk_8F0[4];
} UnkStruct_0200b428_2;

extern void *data_021c80bc;
extern void *data_020ccf94;

extern void func_0204f794(void *, int, int);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern u16 *func_0204f5a8(void *, void *, int);
extern int func_02073908(void *, int);
extern void *func_020984e8(void);
extern int func_02099020(void *, int);
extern void func_02098ff8(void *, int);
extern int func_0200ad24(UnkStruct_0200b428_2 *, Pair *, int, int, int);
extern int func_0200f328(UnkStruct_0200b428_2 *, int);
extern unsigned int *func_0200f27c(UnkStruct_0200b428_2 *, int);
extern void func_02079664(void *);
extern void func_02045df8(Pair *, int);
extern void func_02045f08(Pair *, int);
extern void func_0200b7c0(void *, Pair *, int, int, int);
extern void func_020109a0(UnkStruct_0200b428_2 *, int, int, unsigned short);
extern int func_0200fbe0(UnkStruct_0200b428_2 *);
extern void func_0205eae0(void *, int, int, int);

void func_0200b428(UnkStruct_0200b428_2 *self, Arg *arg, int previous)
{
    int b4;
    void *p8;
    unsigned int H;
    int t28;
    unsigned int F;
    int t24;
    unsigned int G;
    unsigned int E;
    unsigned int D;
    unsigned int C;
    unsigned int B;
    unsigned int A;
    int R;
    u16 h[4];
    Pair pr1;
    Pair pr2;
    Pair pr3;
    Pair pr4;
    Pair pr5;
    UnkStruct_0200b428 *s;
    int i4;
    int i6;
    int i7;
    unsigned int ok;
    unsigned int k1, k2, k3;
    int hh;
    Rec *q;

    s = &arg->sub;
    i4 = s->unk_08;
    i6 = s->unk_09;
    i7 = s->unk_04;
    h[0] = arg->sub.unk_00;
    b4 = s->unk_0A;
    if (i7 < 0) {
        func_0204f794(self->unk_824, i4, i6);
        self->unk_830 = 0x1000;
        self->unk_834 = 0x1000;
        self->unk_838 = 0x1000;
        if (func_0204bcdc(&h[0]) != 0) {
            h[2] = 0xfff1;
            t24 = func_0204bc64(&h[0]);
            if (t24 == func_0204bc64(&h[2])) {
                ok = 1;
            } else {
                ok = 0;
            }
        } else {
            if (h[0] == 0xfff1) {
                ok = 1;
            } else {
                ok = 0;
            }
        }
        if (ok != 0) {
            self->unk_822 = *func_0204f5a8(data_021c80bc, self->unk_824, 0);
            self->unk_820 = self->unk_822;
        } else {
            self->unk_822 = h[0];
            self->unk_820 = self->unk_822;
        }
        if (func_02073908(data_020ccf94, self->unk_800) != 0) {
            p8 = func_020984e8();
            if (p8 != 0) {
                k1 = 0;
                if (self->unk_820 >= 0x137b && self->unk_820 <= 0x137b) {
                    k1 = 1;
                }
                if (k1 != 0) {
                    if (func_02099020(p8, 0x28) == 0) {
                        func_02098ff8(p8, 0x28);
                        pr1.a = i4;
                        pr1.b = i6;
                        func_0200ad24(self, &pr1, b4, 6, -1);
                        return;
                    }
                } else if (self->unk_820 >= 0x136a && self->unk_820 <= 0x136a) {
                    if (func_02099020(p8, 0x27) == 0) {
                        func_02098ff8(p8, 0x27);
                        pr2.a = i4;
                        pr2.b = i6;
                        func_0200ad24(self, &pr2, b4, 6, -1);
                        return;
                    }
                }
            }
        }
        B = C = D = E = F = G = H = 1;
        A = 0;
        if (self->unk_820 <= 5) {
            A = 1;
        }
        if (A == 0) {
            if (!(self->unk_820 >= 6 && self->unk_820 <= 0xb)) {
                B = 0;
            }
        }
        if (B == 0) {
            if (!(self->unk_820 >= 0xc && self->unk_820 <= 0x11)) {
                C = 0;
            }
        }
        if (C == 0) {
            if (!((self->unk_820 >= 0x12 && self->unk_820 <= 0x19) || self->unk_820 == 0x1c)) {
                D = 0;
            }
        }
        if (D == 0) {
            if (!((self->unk_820 >= 0x8a && self->unk_820 <= 0x8f) || (self->unk_820 >= 0x90 && self->unk_820 <= 0x95) ||
                  (self->unk_820 >= 0x96 && self->unk_820 <= 0x9b) || (self->unk_820 >= 0x9c && self->unk_820 <= 0xa3) ||
                  self->unk_820 == 0xa5)) {
                E = 0;
            }
        }
        if (E == 0) {
            if (self->unk_820 != 0x1a) {
                F = 0;
            }
        }
        if (F == 0) {
            if (self->unk_820 != 0xa4) {
                G = 0;
            }
        }
        if (G == 0) {
            if (self->unk_820 != 0x1d) {
                H = 0;
            }
        }
        if (H != 0) {
            func_0200f328(self, 0x7d7);
            func_0200f27c(self, 9);
        } else {
            func_0200f328(self, 0x5d);
            k2 = 0;
            if (self->unk_820 >= 0x1554 && self->unk_820 <= 0x155c) {
                k2 = 1;
            }
            if (k2 != 0) {
                func_02079664(&self->unk_5C);
            }
        }
        func_0200f27c(self, 0xd);
    }
    if (b4 != 0) {
        if (func_0204bcdc(&self->unk_820) != 0) {
            h[3] = 0xfff1;
            t28 = func_0204bc64(&self->unk_820);
            if (t28 == func_0204bc64(&h[3])) {
                ok = 1;
            } else {
                ok = 0;
            }
        } else {
            if (self->unk_820 == 0xfff1) {
                ok = 1;
            } else {
                ok = 0;
            }
        }
        if (ok == 0) {
            k3 = 0;
            if (self->unk_820 >= 0xa7 && self->unk_820 <= 0xc6) {
                k3 = 1;
            }
            if (k3 == 0) {
                R = 1;
                goto have;
            }
        }
    }
    R = 0;
have:
    if (R != 0) {
        pr3.a = i4;
        pr3.b = i6;
        func_02045df8(&pr3, 0);
    } else {
        pr4.a = i4;
        pr4.b = i6;
        func_02045f08(&pr4, 0);
    }
    q = &self->unk_7D4;
    q->unk_08 = 0;
    q->unk_04 = i7;
    q->unk_09 = (u8) i4;
    q->unk_0A = (u8) i6;
    q->unk_00 = (u8) R;
    hh = self->unk_820;
    pr5.a = i4;
    pr5.b = i6;
    func_0200b7c0(self->unk_8F0, &pr5, (char) i7, hh, R);
    if (i7 >= 0) {
        func_020109a0(self, 0x16, 6, 0);
    } else {
        func_020109a0(self, 0x16, 3, 0);
    }
    if (func_0200fbe0(self) == 4) {
        func_0205eae0(self->unk_5A0, 0xc, 3, 1);
    }
}
