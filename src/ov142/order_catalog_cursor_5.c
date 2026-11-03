/* order_catalog_cursor_5: 19 functions, module ov142
 * mwccarm 1.2/base -O4,s
 * func_ov142_0229b4cc @ 0x0229b4cc, 0x32 bytes, Thumb
 * func_ov142_0229b4a8 @ 0x0229b4a8, 0x24 bytes, Thumb
 * func_ov142_0229b43c @ 0x0229b43c, 0x6c bytes, Thumb
 * func_ov142_0229b394 @ 0x0229b394, 0xa8 bytes, Thumb
 * func_ov142_0229b350 @ 0x0229b350, 0x44 bytes, Thumb
 * func_ov142_0229b2f8 @ 0x0229b2f8, 0x58 bytes, Thumb
 * func_ov142_0229b290 @ 0x0229b290, 0x68 bytes, Thumb
 * func_ov142_0229b278 @ 0x0229b278, 0x16 bytes, Thumb
 * func_ov142_0229b23c @ 0x0229b23c, 0x3a bytes, Thumb
 * func_ov142_0229b214 @ 0x0229b214, 0x28 bytes, Thumb
 * func_ov142_0229b1fc @ 0x0229b1fc, 0x16 bytes, Thumb
 * func_ov142_0229b1d8 @ 0x0229b1d8, 0x24 bytes, Thumb
 * func_ov142_0229b1b8 @ 0x0229b1b8, 0x20 bytes, Thumb
 * func_ov142_0229b174 @ 0x0229b174, 0x44 bytes, Thumb
 * func_ov142_0229b138 @ 0x0229b138, 0x3c bytes, Thumb
 * func_ov142_0229b10c @ 0x0229b10c, 0x2c bytes, Thumb
 * func_ov142_0229b0d4 @ 0x0229b0d4, 0x36 bytes, Thumb
 * func_ov142_0229b04c @ 0x0229b04c, 0x88 bytes, Thumb
 * func_ov142_0229afb0 @ 0x0229afb0, 0x9c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229b4cc {
    char pad_00[0xc0];
    unsigned char unk_C0;
    char pad_C1[0xe8 - 0xc1];
    int unk_E8;
};

typedef struct UnkStruct_0229b43c {
    unsigned char pad_00[0x194];
    unsigned char unk_194;
} UnkStruct_0229b43c;

typedef struct UnkStruct_0229b394 {
    unsigned char pad_00[0xc0];
    unsigned char byte;
} UnkStruct_0229b394;

struct Obj0229b23c {
    unsigned char pad_00[0xc0];
    unsigned char unk_C0;
};

typedef struct UnkStruct_0229b04c {
    char pad_00[0xc0];
    u8 unk_C0;
} UnkStruct_0229b04c;

struct UnkStruct_0229afb0 {
    u8 pad_00[0xa0];
    u32 unk_A0;
    u8 pad_A4[0x1c];
    u8 unk_C0;
};

extern int func_0208e484(void *ptr);
extern int func_ov142_0229a298(void *self, unsigned char byte);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov142_0229aec4(void *self);
extern void func_ov142_0229af00(void *);
extern int func_ov002_02208054(void *, int);
extern int func_ov002_0220a784(void *, int);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov002_02208014(void *receiver);
extern char *func_ov002_02208008(UnkStruct_0229b394 *self);
extern int func_ov002_02207fe4(UnkStruct_0229b394 *self);
extern int func_ov002_02207fd8(UnkStruct_0229b394 *self);
extern void func_ov142_0229af4c(UnkStruct_0229b394 *self);
extern void func_ov142_0229aee8(UnkStruct_0229b394 *self);
extern unsigned short data_021fbe40[2];
extern void func_0200467c(int);
extern void *func_ov002_0220a720(void *, int);
extern void func_0206fc4c(int);
extern unsigned short *func_ov142_0229a644(void *, short);
extern void func_0206f68c(int);
extern void func_ov002_02207e9c(void *self, int arg1, int arg2);
extern void func_ov142_02299658(void *self, int arg);
extern void func_ov142_02299938(void *self);
extern int func_0208e4bc(void *);
extern void func_ov142_0229af94(void *);
extern int func_ov002_0220a700(void *);
extern int func_ov002_0220a6e0(void *);
extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a72c(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov142_02299668(struct Obj0229b23c *p, int n);
extern void func_ov142_02299648(struct Obj0229b23c *p, int n);
extern void func_ov002_02207fc0(struct Obj0229b23c *p);
extern int func_0206fe60(void);
extern unsigned char data_020e54a8;
extern void func_ov002_02208090(void *p, int n);
extern void *func_ov004_0223d03c(void);
extern void func_ov004_0223d064(void *argument0);
extern void func_ov142_022999a4(void *);
extern void func_ov002_0220a374(int, int);
extern int func_ov002_0220a4f8(void *);
extern int func_ov002_0220a4d4(void *p);

void func_ov142_0229b350(void *param);
void func_ov142_0229b2f8(void *self);
void func_ov142_0229b1fc(void *p);
void func_ov142_0229b1d8(void *p);
void func_ov142_0229b174(void *p);
void func_ov142_0229b0d4(int r0);
int func_ov142_0229b04c(UnkStruct_0229b04c *o);
int func_ov142_0229afb0(struct UnkStruct_0229afb0 *s);

void func_ov142_0229b4cc(struct UnkStruct_0229b4cc *p)
{
    if (func_0208e484(&p->unk_E8)) {
        if (func_ov142_0229a298(p, p->unk_C0) == 0) {
            func_ov002_02208098((void *) (p), 4);
            func_ov142_0229aec4(p);
        }
    }
}

void func_ov142_0229b4a8(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0xe8)) {
        func_ov142_0229af00(arg0);
        func_ov002_02208098((void *) (arg0), *(unsigned char *) ((char *) arg0 + 0xba));
    }
}

void func_ov142_0229b43c(UnkStruct_0229b43c *self)
{
    unsigned int flag;

    if (func_ov002_02208054(self, 1)) {
        func_ov142_0229b1d8(self);
        return;
    }

    flag = (data_021fbdd8 && data_021fbddc);
    if (flag > 0) {
        if (func_ov002_0220a784(&self->unk_194, 3)) {
            func_ov142_0229b350(self);
        } else if (func_ov002_0220a784(&self->unk_194, 4)) {
            func_ov142_0229b2f8(self);
        }
    }
}

void func_ov142_0229b394(UnkStruct_0229b394 *self)
{
    unsigned char saved;
    unsigned short flags;

    if (func_ov002_02208014(self) != 0) {
        func_ov142_0229b1fc((void *) self);
        return;
    }

    saved = self->byte;
    func_ov002_02208008(self);

    if (func_ov002_02207fe4(self) != 0) {
        self->byte = 0x17;
    } else if (func_ov002_02207fd8(self) != 0) {
        self->byte = 0x18;
    }

    if (saved != self->byte) {
        func_ov142_0229af4c(self);
        return;
    }

    flags = data_021fbe40[1];

    if (flags & 1) {
        func_ov142_0229aee8(self);
        return;
    }

    if (flags & 8) {
        func_ov142_0229af94((void *) self);
        func_ov142_0229b350((void *) self);
    }

    if (data_021fbe40[1] & 2) {
        func_ov142_0229af94((void *) self);
        func_ov142_0229b2f8((void *) self);
    }
}

void func_ov142_0229b350(void *param)
{
    func_0200467c(0x29);
    func_ov002_0220a720((char *) param + 0x194, 3);
    func_ov002_02208098((void *) (param), 0xd);
    func_0206fc4c(1);
    func_0206f68c(*func_ov142_0229a644(param, *(short *) ((char *) param + 0xb8)));
    func_ov142_0229b174(param);
}

void func_ov142_0229b2f8(void *self)
{
    func_0200467c(0x2a);
    func_ov002_0220a720((char *) self + 0x194, 4);
    *((unsigned char *) self + 0x8c) = 6;
    func_ov002_02207e9c(self, 0, 0);
    func_ov002_02208098((void *) (self), 0xd);
    func_ov142_02299658(self, 0x80);
    *((unsigned char *) self + 0xc0) = 0x12;
    *((unsigned char *) self + 0xbf) = 5;
    func_ov142_02299938(self);
}

void func_ov142_0229b290(void *self)
{
    int r4, r6;
    int r2;

    if (func_ov002_0220a700((char *) self + 0x194)) {
        if (func_0208e4bc((char *) self + 0xe8)) {
            r4 = func_ov002_0220a6e0((char *) self + 0x194);
            r6 = func_ov002_0220a768((char *) self + 0x194, -1);
            r2 = func_ov002_0220a72c((char *) self + 0x194, -1);
            func_ov002_0220a0b4((char *) self + 0xe8, r4 + r6, r4 + r2);
        }
    } else {
        func_ov142_0229af94(self);
        func_ov002_022080a0((void *) (self), 1);
    }
}

void func_ov142_0229b278(void *p)
{
    func_ov142_0229af94(p);
    func_ov002_02208098((void *) (p), 0);
}

void func_ov142_0229b23c(struct Obj0229b23c *p)
{
    if (func_ov142_02299668(p, 0x80)) {
        func_ov142_02299648(p, 0x80);
    } else {
        p->unk_C0 = 0;
    }
    func_ov142_0229b0d4((int) p);
    func_ov002_02207fc0(p);
    func_ov002_02208098((void *) (p), 4);
}

void func_ov142_0229b214(int param)
{
    if (func_0206fe60()) {
        func_ov142_0229b278((void *) param);
    } else {
        func_ov142_0229b23c((struct Obj0229b23c *) param);
    }
    func_ov142_02299648((struct Obj0229b23c *) param, 0x80);
}

void func_ov142_0229b1fc(void *p)
{
    func_ov142_0229af94(p);
    func_ov002_02208098((void *) (p), 0xb);
}

void func_ov142_0229b1d8(void *p)
{
    ((unsigned char *) p)[0xc0] = 0x18;
    func_ov142_0229b0d4((int) p);
    func_ov002_02207fc0((struct Obj0229b23c *) p);
    func_ov002_02208098((void *) (p), 0xc);
}

void func_ov142_0229b1b8(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov142_0229b1fc((void *) r4);
    } else {
        func_ov142_0229b1d8((void *) r4);
    }
}

void func_ov142_0229b174(void *p)
{
    unsigned int flag;
    func_ov002_02208090(p, 2);
    flag = (data_020e54a8 == 1) ? 1 : 0;
    if (flag > 0) {
        if (func_ov142_02299668((struct Obj0229b23c *) p, 0x40) != 0) {
            func_ov142_02299648((struct Obj0229b23c *) p, 0x40);

            func_ov004_0223d064(func_ov004_0223d03c());
        }
    }
}

void func_ov142_0229b138(void *p)
{
    char *q = (char *) p + 0xbf;
    *q = 7;
    func_ov142_0229af94(p);
    func_ov002_02208090(p, 4);
    func_ov002_022080a0((void *) (p), 1);
    func_ov002_02207e9c(p, 0, 0);
    func_ov142_022999a4(p);
    func_0200467c(0x59);
}

void func_ov142_0229b10c(void *param)
{
    func_0206fc4c(0);
    func_ov002_0220a720((char *) param + 0x194, 6);
    func_ov002_02208098((void *) (param), 0xd);
    func_ov142_0229b174(param);
}

void func_ov142_0229b0d4(int r0)
{
    int r4;
    int r5;
    int r2;

    r5 = r0;
    r4 = func_ov142_0229b04c((UnkStruct_0229b04c *) r0);
    r2 = func_ov142_0229afb0((struct UnkStruct_0229afb0 *) r0);
    func_ov002_0220a0b4((void *) (r0 + 0xe8), r4, r2);
    func_ov002_0220a374(r0 + 0xe8, 1);
    func_ov142_0229af00((void *) r0);
}

int func_ov142_0229b04c(UnkStruct_0229b04c *o)
{
    u8 v = o->unk_C0;

    if (v <= 8) {
        return 0x17;
    }
    if (v >= 9 && v <= 0x11) {
        return 0x40;
    }
    switch (v) {
        case 0x13:
            return func_ov002_0220a768((char *) o + 0x194, 6);
        case 0x12:
            return 0xe8;
        case 0x14:
            return func_ov002_0220a4f8((char *) o + 0x14c);
        case 0x17:
            return func_ov002_0220a768((char *) o + 0x194, 3);
        case 0x18:
            return func_ov002_0220a768((char *) o + 0x194, 4);
        case 0x15:
        case 0x16:
            return 0xc0;
    }
    return 0x80;
}

int func_ov142_0229afb0(struct UnkStruct_0229afb0 *s)
{
    u8 b;
    int idx;

    b = s->unk_C0;
    if (b <= 8) {
        return (int) (b << 4) + 31;
    }
    if (b >= 9 && b <= 17) {
        return (((int) (b - 9) << 4) + 0x28) - (int) (s->unk_A0 & 0xf);
    }

    idx = (int) b - 18;

    switch (idx) {
        case 1:
            return func_ov002_0220a72c((char *) s + 0x194, 6);
        case 0:
            return 0x57;
        case 2:
            return func_ov002_0220a4d4((char *) s + 0x14c);
        case 5:
            return func_ov002_0220a72c((char *) s + 0x194, 3);
        case 6:
            return func_ov002_0220a72c((char *) s + 0x194, 4);
        case 3:
            return 0x23;
        case 4:
            return 0x9b;
    }

    return 0x60;
}
