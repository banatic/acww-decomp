/* field_actor_46: 14 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02217608 @ 0x02217608, 0x70 bytes, Thumb
 * func_ov003_02217590 @ 0x02217590, 0x78 bytes, Thumb
 * func_ov003_022174a4 @ 0x022174a4, 0xec bytes, Thumb
 * func_ov003_02217488 @ 0x02217488, 0x1a bytes, Thumb
 * func_ov003_02217450 @ 0x02217450, 0x36 bytes, Thumb
 * func_ov003_02217440 @ 0x02217440, 0xe bytes, Thumb
 * func_ov003_0221740c @ 0x0221740c, 0x34 bytes, Thumb
 * func_ov003_02217400 @ 0x02217400, 0xc bytes, Thumb
 * func_ov003_022173e0 @ 0x022173e0, 0x20 bytes, Thumb
 * func_ov003_02217378 @ 0x02217378, 0x68 bytes, Thumb
 * func_ov003_0221730c @ 0x0221730c, 0x6c bytes, Thumb
 * func_ov003_022172c4 @ 0x022172c4, 0x48 bytes, Thumb
 * func_ov003_022172bc @ 0x022172bc, 0x8 bytes, Thumb
 * func_ov003_02217234 @ 0x02217234, 0x88 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int kind;
    int unk_04;
    int unk_08;
    short unk_0C;
    unsigned char unk_0E;
} UnkStruct_022174a4;

typedef struct {
    char pad_00[0x2d0];
    int unk_2D0;
    char pad_2D4[0x7d4 - 0x2d4];
    UnkStruct_022174a4 q;
    char pad_7E4[0x7f0 - 0x7e4];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
} UnkStruct_022174a4_2;

typedef struct {
    char pad_00[0x7D8];
    int unk_7D8;
} UnkStruct_022173e0;

typedef struct {
    char pad_00[0x62c];
    int unk_62C, unk_630, unk_634;
    char pad_638[0x1a0];
    int unk_7D8;
} UnkStruct_02217378;

typedef struct {
    char pad_00[0x800];
    int unk_800;
} UnkStruct_022172c4;

struct UnkStruct_022172bc {
    int a;
    int b;
    u8 c;
};

typedef struct UnkStruct_02217234 {
    char pad_00[0x144];
    int unk_144;
    unsigned char unk_148;
    char pad_149[3];
    int unk_14C;
    int unk_150;
    int unk_154;
    int unk_158;
    int unk_15C;
    int unk_160;
} UnkStruct_02217234;

extern unsigned short func_ov003_022177d0(int, unsigned char *, int *, int *, unsigned char *);
extern int func_ov003_02217838(int, int, int, int, int, int, int, int);
extern int func_02056f28(void *ptr, int arg);
extern void func_0200f268(void *ptr, int arg);
extern unsigned int *func_0200f27c(void *ptr, int arg);
extern int func_0200f328(void *ptr, int arg);
extern void func_02010f5c(void *ptr);
extern int func_02056f94(void *p);
extern int func_ov003_022188d0(void *self, int a, int b, short c, int d, int e);
extern int func_ov003_022186cc(void *self, unsigned char k, int a, int b, short c, int d, int e);
extern int func_02008258(void *self, int a);
extern int func_0200c3b0(void *self, int a, int b, int c);
extern int func_0203e110(void);
extern int func_0200d4e8(void *self, int a, int b, int c);
extern void func_02010d64(void *);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void *func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_020109a0(void *p, int b, int c, unsigned short d);
extern void func_0209129c(int value);
extern int func_0203f7d0(int *, int *);
extern int func_020912d4(int, int *, void *, int);
extern void func_02091278(int, int *, void *, int);
extern int func_02073908(void *, unsigned int);
extern int func_ov003_0220d268(void *);
extern void *data_020ccf94;
extern int func_0201100c(void *);
extern int func_0200f554(void *);
extern int func_02010ca4(void *);

void func_ov003_02217608(int a, int b)
{
    unsigned char arr[4];
    int v1;
    int v2;
    int sel;

    func_ov003_022177d0(a + 0x8f0, arr, &v1, &v2, arr + 2);
    switch (arr[0] & 0xf0) {
        case 0x00:
            sel = 0x38;
            break;
        case 0x10:
            sel = 0x39;
            break;
        case 0x20:
            sel = 0x10;
            break;
        default:
            sel = 2;
            break;
    }
    func_ov003_02217838(a, sel, (unsigned char) (arr[0] & 0xf), v1, v2, *(short *) (arr + 2), 6, b);
}

void func_ov003_02217590(unsigned char *self)
{
    func_02010f5c(self);
    if ((self[0x7e2] & 3) != 2) {
        unsigned int field = *(unsigned int *) (self + 0x2d8);
        if (((field << 4) >> 16) < 6) {
            if (func_02056f28(self + 0x2d0, 5) != 0) {
                func_0200f268(self, 0);
            }
        }
    } else {
        unsigned int field = *(unsigned int *) (self + 0x2d8);
        if (((field << 4) >> 16) < 8) {
            if (func_02056f28(self + 0x2d0, 7) != 0) {
                func_0200f27c(self, 0);
                func_0200f328(self, 0x857);
            }
        }
    }
}

void func_ov003_022174a4(UnkStruct_022174a4_2 *self)
{
    UnkStruct_022174a4 *q;

    q = &self->q;
    if (func_02056f94(&self->unk_2D0) == 0) {
        return;
    }
    func_0200f27c(self, 1);
    switch (q->kind) {
        case 0x38:
            func_0200f268(self, 0);
            func_ov003_022188d0(self, q->unk_04, q->unk_08, q->unk_0C, 6, -1);
            break;
        case 0x39:
            func_0200f268(self, 0);
            func_ov003_022186cc(self, (unsigned char) ((q->unk_0E & 0xc) >> 2), q->unk_04, q->unk_08, q->unk_0C, 6, -1);
            break;
        case 0x10:
            func_0200f268(self, 0);
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200c3b0(self, 3, 5, -1);
            break;
        case 2:
            func_0203e110();
            self->unk_7FC = func_02008258(self, self->unk_7F0);
            func_0200d4e8(self, 3, 1, -1);
            break;
    }
}

void func_ov003_02217488(void *arg)
{
    func_ov003_02217590((unsigned char *) arg);
    func_02010d64(arg);
    func_ov003_022174a4((UnkStruct_022174a4_2 *) arg);
}

void *func_ov003_02217450(void *a, void *b, void *c)
{
    void *stack[8];
    void *result;

    func_0200e92c(stack);
    func_0200e90c(stack, 0x45, b, c);
    result = func_0200e894(a, stack);
    func_0200e91c(stack);
    return result;
}

void func_ov003_02217440(unsigned short *r0)
{
    *r0 = 0;
    *(r0 + 1) = 0x20;
    *(int *) (r0 + 2) = -1;
}

void func_ov003_0221740c(void *p, void *message, int previous)
{
    func_020109a0(p, 0x63, 3, 0);
    func_ov003_02217440((unsigned short *) ((char *) p + 0x7d4));
    func_0200f328(p, 0x856);
    func_0200f27c(p, 9);
}

void func_ov003_02217400(int a, int b)
{
    func_ov003_02217450((void *) a, (void *) 6, (void *) b);
}

void func_ov003_022173e0(UnkStruct_022173e0 *self)
{
    if (self->unk_7D8 != -1) {
        func_0209129c(self->unk_7D8);
    }
}

void func_ov003_02217378(UnkStruct_02217378 *self)
{
    int loc[3];
    int *q;
    int a, b, c;
    func_02010f5c((void *) ((int) self));
    q = &self->unk_7D8;
    c = self->unk_634;
    b = self->unk_630;
    a = self->unk_62C;
    loc[0] = a;
    loc[1] = b;
    loc[2] = c;
    func_0203f7d0(loc, loc);
    if (self->unk_7D8 == -1) {
        *q = func_020912d4(0x33, loc, (char *) self + 0x8e, 0);
    } else {
        func_02091278(self->unk_7D8, loc, (char *) self + 0x8e, 0);
    }
}

void func_ov003_0221730c(void *self)
{
    if (func_02056f94((void *) ((char *) self + 0x2d0))) {
        *(unsigned int *) ((char *) self + 0x7fc) = func_02008258(self, *(unsigned int *) ((char *) self + 0x7f0));
        func_0200d4e8(self, 3, 1, -1);
    }
    if (((*(unsigned int *) ((char *) self + 0x2d8) << 4) >> 16) >= 14) {
        if (func_02073908(data_020ccf94, *(unsigned int *) ((char *) self + 0x800)) != 0) {
            func_ov003_0220d268(self);
        }
    }
}

void func_ov003_022172c4(void *arg)
{
    int result;
    func_ov003_02217378((UnkStruct_02217378 *) arg);
    result = func_02073908((void *) ((*(int *) &data_020ccf94)), ((UnkStruct_022172c4 *) arg)->unk_800);
    if (result != 0) {
        func_0201100c(arg);
    } else {
        func_0200f554(arg);
    }
    func_02010d64(arg);
    func_02010ca4(arg);
    func_ov003_0221730c(arg);
}

void func_ov003_022172bc(struct UnkStruct_022172bc *p, int a, int b, int c)
{
    p->a = a;
    p->b = b;
    p->c = (u8) c;
}

int func_ov003_02217234(UnkStruct_02217234 *self, int param1, int param2)
{
    char stack[0x1c];
    char *local2;
    int result;

    func_0200e92c(stack);
    local2 = stack + 0xc;
    func_0200e90c(stack, 0x46, (void *) param1, (void *) param2);

    if (self->unk_148 != 0) {
        func_ov003_022172bc((struct UnkStruct_022172bc *) local2, self->unk_158, self->unk_160, 1);
    } else {
        func_ov003_022172bc((struct UnkStruct_022172bc *) local2, self->unk_14C, self->unk_154, (self->unk_144 != 0) ? 1 : 0);
    }

    result = (int) func_0200e894(self, stack);
    func_0200e91c(stack);
    return result;
}
