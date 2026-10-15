/* func_0200a80c @ 0x0200a80c, 0x1d4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Pair {
    int a, b;
} Pair;
typedef struct S7d4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S7d4;
typedef struct UnkStruct_0200a80c {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0200a80c;

typedef struct UnkStruct_0200a80c_2 {
    char unk_00[0xec];
    char unk_EC[0x10a - 0xec];
    u8 unk_10A;
    char unk_10B[0x12c - 0x10b];
    UnkStruct_0200a80c *unk_12C;
    char unk_130[0x2d0 - 0x130];
    char unk_2D0[8];
    u32 unk_2D8;
    char unk_2DC[0x7d4 - 0x2dc];
    S7d4 unk_7D4;
    char unk_7D8[0x7f0 - 0x7d8];
    int unk_7F0;
    char unk_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    char unk_800[0x81c - 0x800];
    int unk_81C;
    u16 unk_820;
} UnkStruct_0200a80c_2;

extern u8 data_020e54a8;
extern int data_020d83b4;

extern int func_02056f28(char *, int);
extern void func_0203ae98(void);
extern void func_02045df8(Pair *, int);
extern void func_02045f08(Pair *, int);
extern void func_0200f268(UnkStruct_0200a80c_2 *, int);
extern int func_0200f328(UnkStruct_0200a80c_2 *, int);
extern unsigned int *func_0200f27c(UnkStruct_0200a80c_2 *, int);
extern int func_0203e1c4(void);
extern void func_0203ee14(UnkStruct_0200a80c_2 *, char *);
extern void func_0203ee08(UnkStruct_0200a80c_2 *, char *);
extern void func_020a8164(char *, int *);
extern void func_02035624(int);
extern void func_02035684(int, int, int);
extern void func_020356c4(int, int, int, int);
extern int func_0203e19c(void);
extern int func_0203b144(void);
extern int func_02008258(UnkStruct_0200a80c_2 *, int);
extern int func_0200a6a0(UnkStruct_0200a80c_2 *, Pair *, int, int, int);

void func_0200a80c(UnkStruct_0200a80c_2 *self)
{
    struct {
        int pad;
        Pair a8;
        Pair a10;
        Pair a18;
    } W;
    S7d4 *s;
    u8 *st;
    char *base;
    int x, y, t;
    unsigned int f;
    u16 h;
    unsigned int ok;

    s = &self->unk_7D4;
    st = &s->unk_01;
    if (s->unk_01 == 0) {
        goto c0;
    }
    if (s->unk_01 == 1) {
        goto c1;
    }
    if (s->unk_01 == 2) {
        goto c2;
    }
    return;
c0: {
    if (func_02056f28(self->unk_2D0, 1) != 0) {
        func_0203ae98();
    }
    if (func_02056f28(self->unk_2D0, 6) != 0) {
        x = s->unk_02;
        y = s->unk_03;
        if (s->unk_00 != 0) {
            W.a8.a = x;
            W.a8.b = y;
            func_02045df8(&W.a8, 0);
        } else {
            W.a10.a = x;
            W.a10.b = y;
            func_02045f08(&W.a10, 0);
        }
        func_0200f268(self, 0x1c);
        if (data_020e54a8 == 0) {
            ok = 1;
        } else {
            ok = 0;
        }
        if (ok != 0) {
            func_0200f328(self, 0x5d);
        }
        func_0200f27c(self, 0xd);
    }
    if (((self->unk_2D8 << 4) >> 16) < 6) {
        return;
    }
    if (func_0203e1c4() == 0) {
        return;
    }
    *st = 1;
    base = (char *) self;
    if (self != 0) {
        base = self->unk_EC;
    }
    func_0203ee14(self, base);
    func_0200f27c(self, 0x11);
    func_020a8164(self->unk_EC, &data_020d83b4);
    f = 0;
    h = self->unk_820;
    if (h >= 0x137b && h <= 0x137b) {
        f = 1;
    }
    if (f != 0) {
        self->unk_10A = 0x23;
    } else if (h >= 0x136a && h <= 0x136a) {
        self->unk_10A = 0x21;
    } else {
        self->unk_10A = 0x25;
    }
    self->unk_12C->unk_08 = 1;
    func_02035624(0x12);
    func_02035684(0xc, 0, 0x10);
    func_020356c4(0xd, 0x39, 0x7f, 1);
    self->unk_81C = 0xa;
}
    return;
c1: {
    if (self->unk_12C != 0 && self->unk_12C->unk_04 != 0) {
        *st = 2;
    }
}
    return;
c2: {
    if (self->unk_12C != 0 && self->unk_12C->unk_04 == 0) {
        base = (char *) self;
        if (self != 0) {
            base = self->unk_EC;
        }
        func_0203ee08(self, base);
        func_0200f268(self, 0x11);
        t = s->unk_00;
        if (t == 0) {
            func_0203e19c();
        }
        func_0203b144();
        x = s->unk_02;
        y = s->unk_03;
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        W.a18.a = x;
        W.a18.b = y;
        func_0200a6a0(self, &W.a18, t, 6, -1);
    }
}
}
