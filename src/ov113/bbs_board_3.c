/* bbs_board_3: 15 functions, module ov113
 * mwccarm 1.2/base -O4,s
 * func_ov113_0229a7a8 @ 0x0229a7a8, 0x4 bytes, Thumb
 * func_ov113_0229a7a4 @ 0x0229a7a4, 0x4 bytes, Thumb
 * func_ov113_0229a794 @ 0x0229a794, 0x10 bytes, Thumb
 * func_ov113_0229a74c @ 0x0229a74c, 0x48 bytes, Thumb
 * func_ov113_0229a71c @ 0x0229a71c, 0x30 bytes, Thumb
 * func_ov113_0229a6d4 @ 0x0229a6d4, 0x48 bytes, Thumb
 * func_ov113_0229a6a4 @ 0x0229a6a4, 0x30 bytes, Thumb
 * func_ov113_0229a658 @ 0x0229a658, 0x4c bytes, Thumb
 * func_ov113_0229a5c0 @ 0x0229a5c0, 0x98 bytes, Thumb
 * func_ov113_0229a590 @ 0x0229a590, 0x30 bytes, Thumb
 * func_ov113_0229a504 @ 0x0229a504, 0x8a bytes, Thumb
 * func_ov113_0229a4a4 @ 0x0229a4a4, 0x60 bytes, Thumb
 * func_ov113_0229a474 @ 0x0229a474, 0x30 bytes, Thumb
 * func_ov113_0229a404 @ 0x0229a404, 0x70 bytes, Thumb
 * func_ov113_0229a3fc @ 0x0229a3fc, 0x8 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229a71c {
    unsigned char pad_00[0x94];
    int unk_94;
    unsigned char pad_98[2];
    unsigned char unk_9A;
};

typedef struct {
    char pad_00[0x94];
    int unk_94;
} self_t;

typedef struct {
    unsigned char pad_00[0x94];
    int unk_94;
} UnkStruct_0229a658;

struct UnkStruct_0229a5c0 {
    unsigned char pad_00[0x9b];
    unsigned char mode_byte;
};

struct UnkStruct_0229a504 {
    unsigned char pad_00[0x9a];
    unsigned char unk_9A;
    unsigned char unk_9B;
};

struct UnkStruct_0229a474 {
    u8 pad_00[0x94];
    u32 unk_94;
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 unk_9C;
    u8 unk_9D;
};

extern void func_020ee470(void *parameter0);
extern void func_ov113_0229a32c(void);
extern void func_ov113_0229a2c4(void *p);
extern void func_ov002_02207ee8(char *, int, int, int, int);
extern void func_02002708(int x);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov002_02208090(void *p, int a);
extern void func_ov113_02299df0(void *self);
extern void func_ov113_02299df4(struct UnkStruct_0229a71c *p, int x);
extern void func_ov113_02299d94(struct UnkStruct_0229a71c *p, int x);
extern int func_ov002_02207f48(void *self, int a);
extern unsigned char *func_ov002_022080a0(void *self, unsigned char value);
extern int func_0206fe60(void);
extern int func_ov002_02207f60(void *self);
extern void func_ov113_0229a108(void *self);
extern void func_ov113_0229a0ec(void *self);
extern void func_ov002_02207ecc(int, int, int, int, int);
extern int func_ov002_02207f3c(void *p, int a);
extern void func_0200277c(int a);
extern void func_0200284c(int a, int b, int c);
extern void func_ov113_02299d84(void *p, int a);
extern int func_ov113_02299da4(void *self, int a);
extern void func_0200467c(int cmd);
extern void func_ov113_02299c44(void *self, int a);
extern void func_ov002_02207fc0(void *self);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void func_ov113_02299a44(void *self);
extern void func_ov113_02299a80(struct UnkStruct_0229a474 *self);
extern void func_020b9ccc(void *);
extern void func_02070b84(void *);
extern void func_ov113_0229a398(void *parameter0);

int func_ov113_0229a7a8(void)
{
    return 1;
}

int func_ov113_0229a7a4(void)
{
    return 1;
}

int func_ov113_0229a794(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov113_0229a74c(void *p)
{
    func_ov113_0229a32c();
    func_ov113_0229a2c4(p);
    func_ov002_02207ee8((char *) (p), 8, 6, 0, 0x30);
    func_02002708(2);
    func_ov002_02207e80(p, 2, 0, 0);
    func_ov002_02208090(p, 1);
    func_ov113_02299df0(p);
}

void func_ov113_0229a71c(struct UnkStruct_0229a71c *p)
{
    func_ov002_02208090((void *) p, 2);
    func_ov113_02299df4(p, p->unk_9A);
    p->unk_94 = func_ov002_02207f60((void *) p);
    func_ov113_02299d94(p, 8);
}

void func_ov113_0229a6d4(self_t *self)
{
    if (func_ov002_02207f48(self, 1)) {
        func_ov002_022080a0(self, 2);
        if (func_0206fe60()) {
            func_ov113_0229a108(self);
        } else {
            func_ov113_0229a0ec(self);
        }
    }
    func_ov002_02207e80(self, 2, 0, 0);
    self->unk_94 = func_ov002_02207f60(self);
}

void func_ov113_0229a6a4(int r0)
{
    int r4 = r0;
    int sp0 = 0x30;
    int r1 = 8;
    int r2 = 0;
    int r3 = r2;
    func_ov002_02207ecc(r4, r1, r2, r3, sp0);
    func_ov002_02207e80((void *) r4, 2, 0, 0);
    func_ov002_02208090((void *) r4, 4);
}

void func_ov113_0229a658(UnkStruct_0229a658 *arg0)
{
    int z = 0;
    if (func_ov002_02207f3c(arg0, 1)) {
        func_0200277c(2);
        func_0200284c(2, z, z);
        func_ov002_022080a0(arg0, 5);
        func_ov113_02299d84(arg0, 8);
    } else {
        func_ov002_02207e80(arg0, 2, z, z);
        arg0->unk_94 = func_ov002_02207f60(arg0);
    }
}

void func_ov113_0229a5c0(struct UnkStruct_0229a5c0 *self)
{
    int mode;

    func_ov113_02299d94((struct UnkStruct_0229a71c *) self, 0x100);

    switch (self->mode_byte) {
        case 1:
        case 4:
            mode = 2;
            break;
        case 0:
        case 5:
            mode = 3;
            break;
        default:
            mode = (func_ov113_02299da4(self, 0x40) != 0) ? 2 : 3;
            break;
    }

    switch (self->mode_byte) {
        case 0:
        case 1:
            func_0200467c(0x3c);
            break;
        default:
            func_0200467c(0x39);
            break;
    }

    func_ov002_02207ecc((int) self, 8, 0, mode, 0x30);
    func_ov002_02207e80(self, 2, 0, 0);
    func_ov002_02208090(self, 6);
}

void func_ov113_0229a590(void *arg)
{
    int zero = 0;
    if (func_ov002_02207f3c(arg, 1)) {
        func_0200277c(2);
        func_ov002_02208090(arg, 7);
    } else {
        func_ov002_02207e80(arg, 2, zero, zero);
    }
}

void func_ov113_0229a504(struct UnkStruct_0229a504 *self)
{
    int v;

    switch (self->unk_9B) {
        case 1:
            func_ov113_02299c44(self, 0);
            // fall through
        case 4:
            v = 3;
            break;
        case 0:
            func_ov113_02299c44(self, 0);
            // fall through
        case 5:
            v = 2;
            break;
        default:
            if (func_ov113_02299da4(self, 0x40) == 0) {
                v = 2;
            } else {
                v = 3;
            }
            break;
    }

    func_ov002_02207ee8((char *) (self), 8, 6, v, 0x30);
    func_02002708(2);
    func_ov002_02207e80(self, 2, 0, 0);
    func_ov002_02208090(self, 8);
    func_ov113_02299df4((struct UnkStruct_0229a71c *) self, self->unk_9A);
}

void func_ov113_0229a4a4(void *self)
{
    if (func_ov002_02207f48(self, 1) != 0) {
        func_ov002_022080a0(self, 2);
        func_ov113_02299c44(self, 0);
        if (func_0206fe60() != 0) {
            func_ov113_0229a108(self);
        } else {
            func_ov002_02207fc0(self);
            func_ov002_02208098(self, 1);
            func_ov113_02299d84(self, 0x100);
            func_ov113_02299a44(self);
        }
    }
    func_ov002_02207e80(self, 2, 0, 0);
}

void func_ov113_0229a474(struct UnkStruct_0229a474 *self)
{
    self->unk_94 = 0;
    self->unk_98 = 0;
    self->unk_9B = 3;
    func_ov113_02299a80(self);
    self->unk_9A = self->unk_9D - 1;
}

void func_ov113_0229a404(void *p)
{
    char *base = (char *) p;
    int i;

    func_020b9ccc(base + 0x26a0);
    func_020b9ccc(base + 0x26c4);
    func_02070b84(base + 0x26e8);
    func_02070b84(base + 0x2754);
    func_02070b84(base + 0x27c0);
    func_02070b84(base + 0x282c);

    for (i = 0; i < 6; i++) {
        func_02070b84(base + 0x2898 + i * 0x6c);
    }
}

void func_ov113_0229a3fc(void *arg0)
{
    func_ov113_0229a398((void *) arg0);
}
