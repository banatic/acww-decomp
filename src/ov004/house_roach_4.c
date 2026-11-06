/* house_roach_4: 7 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0223df48 @ 0x0223df48, 0x40 bytes, Thumb
 * func_ov004_0223de70 @ 0x0223de70, 0xd8 bytes, Thumb
 * func_ov004_0223de14 @ 0x0223de14, 0x5c bytes, Thumb
 * func_ov004_0223dd90 @ 0x0223dd90, 0x84 bytes, Thumb
 * func_ov004_0223dd04 @ 0x0223dd04, 0x8c bytes, Thumb
 * func_ov004_0223dccc @ 0x0223dccc, 0x38 bytes, Thumb
 * func_ov004_0223dc68 @ 0x0223dc68, 0x64 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0223df48 {
    u8 pad_00[0x5c];
    int a;
    int b;
    int c;
    u8 pad_68[0x6c - 0x68];
    int d;
    u8 pad_70[0x98 - 0x70];
    int e;
    u8 pad_9C[0xd4 - 0x9c];
    int unk_D4;
    u8 pad_D8[0x114 - 0xd8];
    u8 out[4];
};

typedef struct {
    int m[12];
} Mtx;

typedef struct UnkStruct_0223de70 {
    char unk_00[8];
    unsigned int unk_08;
    char unk_0C[0x184 - 0xc];
    Mtx unk_184;
} UnkStruct_0223de70;

extern void func_ov004_0223df88(struct UnkStruct_0223df48 *self);
extern void func_020042c0(void *p, int *t);
extern int data_ov004_02259a14;
extern void func_ov004_0223e3ec(UnkStruct_0223de70 *self);
extern void func_ov004_0223d82c(UnkStruct_0223de70 *self);
extern void func_ov004_0223e1f0(UnkStruct_0223de70 *self);
extern void func_02055124(char *p);
extern int func_0203f8d0(char *a, char *b);
extern void func_020031d4(UnkStruct_0223de70 *self, Mtx *m);
extern void func_ov004_0223e3d4(UnkStruct_0223de70 *self, int k);
extern int func_02034270(void *buf, void *vec, int a, int b);
extern int func_020341c8(void *buf, int flag);
extern void func_0203423c(void *buf);
extern void *func_020961a8(int);
extern int func_02089cc0(void *p, unsigned int mask);
extern void func_02055d80(void *, int);
extern void NNSi_G3dModifyPolygonAttrMask(int, int, int);
extern void func_02055d38(void *, u8);
extern void func_0205510c(void *, int);
extern void func_020acc0c(void *, int, int, int);
extern void func_02004280(void *argument0);
extern int func_02055454(int argument0);
extern int func_ov004_0223e3e0(void *self);
extern void func_02004290(void *self, int arg);
extern void func_020042a0(void *self, int arg);

int func_ov004_0223de14(char *self);
int func_ov004_0223dd90(char *self);
int func_ov004_0223dccc(char *self);

void func_ov004_0223df48(struct UnkStruct_0223df48 *self)
{
    int t[4];
    int *p;

    self->e = self->unk_D4;
    func_ov004_0223df88(self);
    self->b = self->d;
    p = (int *) ((char *) self + 0x5c);
    t[0] = p[0];
    t[1] = p[1];
    t[2] = p[2];
    func_020042c0(&self->out, t);
}

int func_ov004_0223de70(UnkStruct_0223de70 *self)
{
    Mtx m;
    unsigned int n;

    *((unsigned char *) self + 0x263) = 0;
    n = self->unk_08;
    if (n >= 0x1f) {
        if (*(int *) ((char *) self + 0x110) == 1) {
            if (data_ov004_02259a14 == 0) {
                func_ov004_0223e3ec(self);
            }
            func_ov004_0223dd90((char *) self);
            func_ov004_0223d82c(self);
            func_ov004_0223e1f0(self);
            func_ov004_0223de14((char *) self);
            if (*((unsigned char *) self + 0x22a) != 0) {
                func_02055124((char *) self + 0x120);
            }
        } else {
            self->unk_08 = n - 1;
        }
    } else if (*(int *) ((char *) self + 0x110) == 1) {
        self->unk_08 = n + 2;
        func_ov004_0223df48((struct UnkStruct_0223df48 *) self);
    } else {
        self->unk_08 = n - 1;
    }
    if (self->unk_08 != 0) {
        *(short *) ((char *) self + 0xd0) = (short) func_0203f8d0((char *) self + 0xc4, (char *) self + 0x5c);
        func_020031d4(self, &m);
        self->unk_184 = m;
    } else {
        func_ov004_0223dccc((char *) self);
    }
    if (*((unsigned char *) self + 0x263) == 0) {
        func_ov004_0223e3d4(self, 0);
    }
    return 1;
}

int func_ov004_0223de14(char *self)
{
    char buf[0x40];
    if (*(int *) (self + 0x60) >= 0xc00) {
        *(int *) (self + 0x60) = *(int *) (self + 0x6c);
        if ((*(int *) (self + 0xe0) & 1) != 0) {
            *(int *) (self + 0x10c) = 2;
            func_02034270(buf, self + 0x5c, 0, 0);
            *(int *) (self + 0x60) = func_020341c8(buf, 1);
            func_0203423c(buf);
            return 1;
        }
    }
    return 0;
}

int func_ov004_0223dd90(char *self)
{
    char *n = (char *) func_020961a8(4);
    char *g;
    if (*(u8 *) (self + 0x214) != 0 && *(u8 *) (self + 0x22a) == 0) {
        if (n != 0 && *(int *) (n + 0x98) > 0 && func_02089cc0(self + 0x1d8, 4) != 0) {
            *(int *) (self + 0x10c) = 2;
            return 1;
        }
        g = (char *) (*(void **) &data_ov004_02259a14);
        if (g != 0 && *(int *) (g + 0x98) > 0 && func_02089cc0(self + 0x1d8, 8) != 0) {
            *(int *) (self + 0x10c) = 2;
            return 1;
        }
    }
    return 0;
}

int func_ov004_0223dd04(char *self)
{
    char *p;
    if (*(int *) (self + 0x110) != 4) {
        p = self + 0x5c;
        if (*(unsigned int *) (self + 8) > 0x1f) {
            *(int *) (self + 8) = 0x1f;
        }
        func_02055d80(self + 0x120, 3);
        NNSi_G3dModifyPolygonAttrMask(*(int *) (self + 0x17c), 1, 0x1f0000);
        func_02055d38(self + 0x120, (u8) * (int *) (self + 8));
        func_0205510c(self + 0x120, 0);
        if (*(unsigned int *) (self + 8) >= 0x1f && *(int *) (self + 0x110) == 1) {
            func_020acc0c(p, 0x400, 0x4000, 0x1000);
        }
    }
    return 1;
}

int func_ov004_0223dccc(char *self)
{
    // DECLS
    // ENDDECLS
    func_02055454((int) (self + 0x120));
    *(int *) (self + 0x110) = 0x4;
    *(int *) (self + 0x8) = 0xffff;
    func_02004280(self + 0x114);
    return 0x1;
}

void func_ov004_0223dc68(char *self, int mode)
{
    switch (mode) {
        case 0:
            *(u8 *) (self + 0x263) = 1;
            if (func_ov004_0223e3e0(self) == 2) {
                func_02004290(self + 0x114, 0x225);
            } else {
                func_ov004_0223e3d4((UnkStruct_0223de70 *) self, 1);
            }
            break;
        case 1:
            func_020042a0(self + 0x114, 0x226);
            break;
        default:
            func_020042a0(self + 0x114, 0x227);
            break;
    }
}
