/* func_ov003_0221100c @ 0x0221100c, 0x380 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct T12c {
    u8 pad[4];
    int unk_04;
    int unk_08;
} T12c;
typedef struct Pair {
    int x;
    int y;
} Pair;

typedef struct UnkStruct_0221100c {
    u8 pad_00[0xec];
    u8 sub_ec[0x10a - 0xec];
    u8 unk_10A;
    u8 pad_10B[0x12c - 0x10b];
    T12c *unk_12C;
    u8 pad_130[0x2d0 - 0x130];
    u8 sub_2d0[0x2d8 - 0x2d0];
    unsigned int unk_2D8;
    u8 pad_2DC[0x704 - 0x2dc];
    int unk_704;
    u8 pad_708[0x7d4 - 0x708];
    int unk_7D4[3];
    u8 unk_7E0;
    u8 pad_7E1[0x7f0 - 0x7e1];
    int unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
    u8 pad_804[0x80c - 0x804];
    int unk_80C;
    u8 pad_810[0x81c - 0x810];
    int unk_81C;
    u16 unk_820;
} UnkStruct_0221100c;

extern void *data_020ccf94;
extern int data_ov003_02238134;

extern int func_02056f94(void *p);
extern int func_02056f28(void *p, int a);
extern void func_020109a0(UnkStruct_0221100c *self, int b, int c, unsigned short d);
extern int func_02073908(void *g, int a);
extern void func_0203ae98(void);
extern int func_0200faf0(UnkStruct_0221100c *self, int a);
extern void func_0200f268(UnkStruct_0221100c *self, int a);
extern int func_02008258(UnkStruct_0221100c *self, int a);
extern int func_0203e1c4(void);
extern void func_0203ee14(UnkStruct_0221100c *self, void *b);
extern void func_0203ee08(UnkStruct_0221100c *self, void *b);
extern unsigned int *func_0200f27c(UnkStruct_0221100c *self, int a);
extern int func_020984e8(void);
extern void func_020a8164(void *p, void *g);
extern int func_02099020(int h, int a);
extern void func_02098ff8(int h, int a);
extern void *func_02062f90(void *d, void *s);
extern void func_020683b4(void *a, int b, void *c, int d);
extern void *func_02062f4c(void *d);
extern void func_02035624(int a);
extern void func_02035684(int a, int b, int c);
extern void func_020356c4(int a, int b, int c, int d);
extern int func_02099fe8(void);
extern int func_0203e19c(void);
extern void func_0204f818(int *a, int *b, int *c);
extern int func_ov003_02210f58(UnkStruct_0221100c *self, Pair *p, int c, int d, short e);
extern int func_0203b144(void);
extern int func_0206fbc0(void);
extern void *func_ov003_02210c24(UnkStruct_0221100c *self, int a, Pair *p, u16 b, int c, short d);

void func_ov003_0221100c(UnkStruct_0221100c *self)
{
    void *g;
    struct {
        int pad;
        int o1[2];
        int o2[2];
        int o3[2];
        Pair p1;
        Pair p2;
        Pair p3;
    } A;
    u8 buf[0x28];
    int v1[3];
    int v2[3];
    int v3[3];
    int *pay;
    u8 *statep;
    int n;
    int h;
    int ok;
    u16 kind;
    void *b;

    if (self->unk_704 == 0x49) {
        if (func_02056f94(self->sub_2d0) == 0) {
            return;
        }
        func_020109a0(self, 0x4f, 3, 0);
        return;
    }

    pay = self->unk_7D4;
    statep = (u8 *) pay + 0xc;
    n = (int) (((unsigned int) self->unk_2D8 << 4) >> 16);
    g = data_020ccf94;
    if (func_02073908(g, self->unk_800) != 0) {
        if (func_02056f28(self->sub_2d0, 0x13) != 0) {
            func_0203ae98();
        }
    }
    if (n < 0x19) {
        return;
    }
    if (func_0200faf0(self, 0x400) == 0) {
        return;
    }
    if (func_02056f94(self->sub_2d0) == 0) {
        return;
    }
    if (func_02073908(g, self->unk_800) == 0) {
        func_0200f268(self, 0x12);
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        return;
    }

    switch (*statep) {
        case 0:
            if (func_0203e1c4() == 0) {
                return;
            }
            *statep = 1;
            b = self;
            if (self != 0) {
                b = (char *) self + 0xec;
            }
            func_0203ee14(self, b);
            func_0200f27c(self, 0x11);
            h = func_020984e8();
            func_020a8164((char *) self + 0xec, &data_ov003_02238134);
            ok = 0;
            if (self->unk_820 >= 0x136a && self->unk_820 <= 0x136a) {
                ok = 1;
            }
            if (ok != 0 && func_02099020(h, 0x27) == 0) {
                self->unk_10A = 0x21;
                func_02098ff8(h, 0x27);
            } else {
                ok = 0;
                if (self->unk_820 >= 0x137b && self->unk_820 <= 0x137b) {
                    ok = 1;
                }
                if (ok != 0 && func_02099020(h, 0x28) == 0) {
                    self->unk_10A = 0x23;
                    func_02098ff8(h, 0x28);
                } else {
                    self->unk_10A = 1;
                    func_02062f90(buf, &self->unk_820);
                    func_020683b4(self->unk_12C, 0, buf, 7);
                    func_02062f4c(buf);
                }
            }
            self->unk_12C->unk_08 = 1;
            func_02035624(0x12);
            func_02035684(0xc, 0, 1);
            func_020356c4(0xd, 0x39, 0x7f, 1);
            self->unk_81C = 0xa;
            break;
        case 1:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 == 0) {
                break;
            }
            *statep = 2;
            break;
        case 2:
            if (func_02099fe8() == -1) {
                *statep = 3;
                self->unk_81C = 2;
                break;
            }
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            b = self;
            if (self != 0) {
                b = (char *) self + 0xec;
            }
            func_0203ee08(self, b);
            func_0200f268(self, 0x11);
            func_0203e19c();
            A.o1[0] = 0;
            A.o1[1] = 0;
            v1[0] = pay[0];
            v1[1] = pay[1];
            v1[2] = pay[2];
            func_0204f818(&A.o1[0], &A.o1[1], v1);
            A.p1.x = A.o1[0];
            A.p1.y = A.o1[1];
            func_ov003_02210f58(self, &A.p1, 0, 6, -1);
            func_0203b144();
            break;
        case 3:
            if (self->unk_81C >= 0xf) {
                *statep = 4;
                break;
            }
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            b = self;
            if (self != 0) {
                b = (char *) self + 0xec;
            }
            func_0203ee08(self, b);
            func_0200f268(self, 0x11);
            A.o2[0] = 0;
            A.o2[1] = 0;
            v2[0] = pay[0];
            v2[1] = pay[1];
            v2[2] = pay[2];
            func_0204f818(&A.o2[0], &A.o2[1], v2);
            A.p2.x = A.o2[0];
            A.p2.y = A.o2[1];
            func_ov003_02210f58(self, &A.p2, 1, 6, -1);
            func_0203b144();
            break;
        case 4:
            if (self->unk_12C == 0) {
                break;
            }
            if (self->unk_12C->unk_04 != 0) {
                break;
            }
            if (func_0206fbc0() == 0) {
                break;
            }
            b = self;
            if (self != 0) {
                b = (char *) self + 0xec;
            }
            func_0203ee08(self, b);
            func_0200f268(self, 0x11);
            func_0203e19c();
            *statep = 5;
            break;
        case 5:
            if (self->unk_80C != -1) {
                break;
            }
            A.o3[0] = 0;
            A.o3[1] = 0;
            v3[0] = pay[0];
            v3[1] = pay[1];
            v3[2] = pay[2];
            func_0204f818(&A.o3[0], &A.o3[1], v3);
            kind = self->unk_820;
            A.p3.x = A.o3[0];
            A.p3.y = A.o3[1];
            func_ov003_02210c24(self, 2, &A.p3, kind, 6, -1);
            func_0203b144();
            break;
    }
}
