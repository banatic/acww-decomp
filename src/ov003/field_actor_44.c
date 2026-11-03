/* field_actor_44: 19 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02217070 @ 0x02217070, 0x34 bytes, Thumb
 * func_ov003_02217060 @ 0x02217060, 0x10 bytes, Thumb
 * func_ov003_02217020 @ 0x02217020, 0x40 bytes, Thumb
 * func_ov003_02216fec @ 0x02216fec, 0x34 bytes, Thumb
 * func_ov003_02216fb0 @ 0x02216fb0, 0x3c bytes, Thumb
 * func_ov003_02216eec @ 0x02216eec, 0xc4 bytes, Thumb
 * func_ov003_02216eb4 @ 0x02216eb4, 0x36 bytes, Thumb
 * func_ov003_02216ea0 @ 0x02216ea0, 0x14 bytes, Thumb
 * func_ov003_02216e94 @ 0x02216e94, 0xc bytes, Thumb
 * func_ov003_02216e5c @ 0x02216e5c, 0x38 bytes, Thumb
 * func_ov003_02216c9c @ 0x02216c9c, 0x1c0 bytes, Thumb
 * func_ov003_02216bfc @ 0x02216bfc, 0xa0 bytes, Thumb
 * func_ov003_02216bc4 @ 0x02216bc4, 0x36 bytes, Thumb
 * func_ov003_02216bb0 @ 0x02216bb0, 0x14 bytes, Thumb
 * func_ov003_02216ba4 @ 0x02216ba4, 0xc bytes, Thumb
 * func_ov003_02216b74 @ 0x02216b74, 0x30 bytes, Thumb
 * func_ov003_02216b34 @ 0x02216b34, 0x40 bytes, Thumb
 * func_ov003_02216b18 @ 0x02216b18, 0x1a bytes, Thumb
 * func_ov003_02216b08 @ 0x02216b08, 0xe bytes, Thumb
 */

#include "types.h"

struct Triple {
    int a, b, c;
};

struct UnkStruct_02217020 {
    char pad_00[0x1c4];
    int sub;
    char pad_1C8[0x60c];
    struct Triple triple;
};

typedef struct UnkStruct_02216fb0 {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x7f0 - 0x2d0 - 1];
    unsigned int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    unsigned int unk_7FC;
} UnkStruct_02216fb0;

struct Work {
    u8 pad_00[0x5c];
    u8 unk_5C[0x32];
    u8 unk_8E[0xa];
    void *unk_98;
    u8 pad_9C[0x764];
    u32 unk_800;
};

typedef char *va_list;

typedef struct {
    int a;
    int b;
} Pair;

struct UnkStruct_02216c9c {
    int pad_00[0x98 / 4];
    int unk_98;
    int pad_9C[(0x7f0 - 0x9c) / 4];
    int unk_7F0;
    int pad_7F4[2];
    int unk_7FC;
    int unk_800;
};

typedef struct {
    unsigned char pad_00[0x98];
    int unk_98;
    unsigned char pad_9C[0x7f0 - 0x9c];
    int unk_7F0;
    unsigned char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
} UnkStruct_02216bfc;

typedef struct UnkStruct_02216b34 {
    char pad_00[0x2d0];
    int unk_2D0;
    char pad_2D4[0x7f0 - 0x2d0 - 4];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    int unk_7FC;
} UnkStruct_02216b34;

extern void func_ov003_022171ac(char *src, int *b, int *c, int *a);
extern int func_ov003_022171ec(char *p, int *b, int *c, int *a, int p5, int p6);
extern void func_0200fb34(void *self, short value);
extern void func_02010d88(void *p, void *q, int a, int b);
extern void func_02089fc8(void *p);
extern int func_02056f94(void *);
extern int func_02008258(void *self, int value);
extern void *data_020ccf94;
extern int func_02073908(void *, u32);
extern void func_02010f5c(struct Work *);
extern int func_0201100c(struct Work *);
extern void func_02010d64(struct Work *);
extern int func_020113a4(void *, int, int);
extern void func_0201107c(struct Work *, int *);
extern int func_0200f554(struct Work *);
extern int func_020912d4(int, void *, void *, int);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_020109fc(int, int, int, int);
extern void func_0200fa6c(void *dst, void *src);
extern int func_0200fc90(struct UnkStruct_02216c9c *self);
extern int func_0200f290(struct UnkStruct_02216c9c *self, int k);
extern int func_ov003_0220d040(struct UnkStruct_02216c9c *self, va_list ap, u8 *mode, Pair *p);
extern int func_ov003_02216410(struct UnkStruct_02216c9c *self, int b, Pair *c, int d, short e);
extern int func_ov003_02216698(struct UnkStruct_02216c9c *self, int b, int c, Pair *d, int e, short f);
extern int func_ov003_02216ab8(struct UnkStruct_02216c9c *self, int b, int c, Pair *d, int e, short f);
extern int func_0200d4e8(struct UnkStruct_02216c9c *self, int a, int b, int c);
int func_02011398(int, int);
extern void func_020109a0(int, int b, int c, unsigned short d);
extern int func_02056f28(const char *, int);
extern int func_0200f328(char *, int);

int func_ov003_02216eb4(void *a0, void *a1, void *a2);
int func_ov003_02216c9c(struct UnkStruct_02216c9c *self, int a1);
int func_ov003_02216bc4(void *a0, int a1, int a2);

void func_ov003_02217070(char *p1, int p2)
{
    int a, b, c;
    func_ov003_022171ac(p1 + 0x8f0, &b, &c, &a);
    func_ov003_022171ec(p1, &b, &c, &a, 6, p2);
}

void func_ov003_02217060(void *self)
{
    func_0200fb34(self, *(short *) ((char *) self + 0x7e0));
}

void func_ov003_02217020(struct UnkStruct_02217020 *s)
{
    struct Triple *p = &s->triple;
    struct Triple local;
    local.a = p->a;
    local.b = p->b;
    local.c = p->c;
    func_02010d88(s, &local, 0xf33, 0x1000);
    func_02089fc8(&s->sub);
}

void func_ov003_02216fec(void *p)
{
    if (func_02056f94((char *) p + 0x2d0)) {
        if (!func_ov003_02216c9c((struct UnkStruct_02216c9c *) p, 1)) {
            func_ov003_02216eb4(p, (void *) 6, (void *) (-1));
        }
    }
}

void func_ov003_02216fb0(UnkStruct_02216fb0 *self)
{
    self->unk_7FC = func_02008258(self, self->unk_7F0);
    if (func_02056f94(&self->unk_2D0) != 0) {
        func_ov003_02216eb4(self, (void *) 6, (void *) (-1));
    }
}

void func_ov003_02216eec(struct Work *self)
{
    void *orig = self->unk_98;
    int res[2];

    if (func_02073908(data_020ccf94, self->unk_800)) {
        func_ov003_02217060((void *) self);
        func_02010f5c(self);
        func_0201100c(self);
        func_02010d64(self);

        res[0] = func_020113a4(self->unk_98, 0, 0x171);
        func_0201107c(self, &res[0]);

        func_ov003_02216fec((void *) self);
        func_ov003_02217020((struct UnkStruct_02217020 *) self);
    } else {
        func_02010f5c(self);

        if (func_0200f554(self)) {
            func_0201100c(self);
        }

        func_02010d64(self);

        res[1] = func_020113a4(self->unk_98, 0, 0x171);
        func_0201107c(self, &res[1]);

        func_ov003_02216fb0((UnkStruct_02216fb0 *) self);
    }

    if (orig != 0 && self->unk_98 == 0) {
        func_020912d4(0x2c, &self->unk_5C, &self->unk_8E, 0);
    }
}

int func_ov003_02216eb4(void *a0, void *a1, void *a2)
{
    char buf[0x20];
    int ret;
    func_0200e92c(buf);
    func_0200e90c(buf, 0x47, a1, a2);
    ret = func_0200e894(a0, buf);
    func_0200e91c(buf);
    return ret;
}

void func_ov003_02216ea0(int a0, void *message, int previous)
{
    func_020109fc(a0, 0x43, 3, 0);
}

void func_ov003_02216e94(int a, int b)
{
    func_ov003_02216eb4((void *) a, (void *) 6, (void *) b);
}

void func_ov003_02216e5c(void *src)
{
    char buf[16];
    func_0200fa6c(buf, src);
    func_02010d88(src, buf, 0xf33, 0x1000);
    func_02089fc8((char *) src + 0x1c4);
}

int func_ov003_02216c9c(struct UnkStruct_02216c9c *self, int a1)
{
    va_list ap;
    int st;
    u8 mode;
    Pair pair;

    if (self->unk_98 != 0) {
        return -1;
    }

    st = func_0200fc90(self);
    mode = 0;
    if (st != 0xb) {
        if (func_0200f290(self, 0x14) != 0) {
            if (st != 0xa) {
                mode = 1;
            } else {
                mode = 2;
            }
        }
    }

    pair.a = 0;
    pair.b = 0;
    ap = (va_list) &a1;
    st = func_ov003_0220d040(self, ap, &mode, &pair);

    if (func_02073908(data_020ccf94, self->unk_800) == 0) {
        mode = 0;
    }

    switch (st) {
        case 0:
            break;
        case 1:
            func_ov003_02216bc4((void *) self, 6, -1);
            break;
        case 2:
        case 3:
            if (mode == 2) {
                Pair t;
                t.a = pair.a;
                t.b = pair.b;
                func_ov003_02216410(self, 1, &t, 6, -1);
            } else {
                Pair t;
                t.a = pair.a;
                t.b = pair.b;
                func_ov003_02216698(self, mode != 0, st == 3, &t, 6, -1);
            }
            break;
        case 4:
            if (mode == 2) {
                Pair t;
                t.a = pair.a;
                t.b = pair.b;
                func_ov003_02216410(self, 0, &t, 6, -1);
            } else {
                Pair t;
                t.a = pair.a;
                t.b = pair.b;
                func_ov003_02216ab8(self, mode != 0, 0, &t, 6, -1);
            }
            break;
        case 5:
            self->unk_7FC = func_02008258((void *) self, self->unk_7F0);
            func_0200d4e8(self, 3, 1, -1);
            break;
        case 6:
            if (mode == 2) {
                Pair t;
                t.a = pair.a;
                t.b = pair.b;
                func_ov003_02216410(self, 1, &t, 6, -1);
            } else {
                Pair t;
                t.a = pair.a;
                t.b = pair.b;
                func_ov003_02216ab8(self, mode != 0, 1, &t, 6, -1);
            }
            break;
    }
    return st;
}

void func_ov003_02216bfc(UnkStruct_02216bfc *self)
{
    int a;
    int b;

    func_02010f5c((struct Work *) self);
    if (func_02073908((void *) ((*(int *) &data_020ccf94)), self->unk_800)) {
        func_0201100c((struct Work *) self);
        func_02010d64((struct Work *) self);
        a = func_02011398(self->unk_98, 0);
        func_0201107c((struct Work *) self, &a);
        func_ov003_02216c9c((struct UnkStruct_02216c9c *) self, 0);
    } else {
        if (func_0200f554((struct Work *) self)) {
            func_0201100c((struct Work *) self);
        }
        func_02010d64((struct Work *) self);
        b = func_02011398(self->unk_98, 0);
        func_0201107c((struct Work *) self, &b);
        self->unk_7FC = func_02008258((void *) self, self->unk_7F0);
    }
    func_ov003_02216e5c((void *) self);
}

int func_ov003_02216bc4(void *a0, int a1, int a2)
{
    char buf[0x20];
    int ret;
    func_0200e92c(buf);
    func_0200e90c(buf, 0x48, (void *) a1, (void *) a2);
    ret = func_0200e894(a0, buf);
    func_0200e91c(buf);
    return ret;
}

void func_ov003_02216bb0(int a, void *message, int previous)
{
    func_020109a0(a, 0x46, 3, 0);
}

void func_ov003_02216ba4(int a, int b)
{
    func_ov003_02216bc4((void *) a, 6, b);
}

void func_ov003_02216b74(char *a)
{
    if (func_02056f28(a + 0x2d0, 6) != 0) {
        func_0200f328(a, 0x83d);
    }
    func_02010f5c((struct Work *) a);
}

void func_ov003_02216b34(UnkStruct_02216b34 *self)
{
    if (func_02056f94(&self->unk_2D0) != 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200d4e8((struct UnkStruct_02216c9c *) self, 3, 1, -1);
    }
}

void func_ov003_02216b18(void *p)
{
    func_ov003_02216b74((char *) p);
    func_02010d64((struct Work *) p);
    func_ov003_02216b34((UnkStruct_02216b34 *) p);
}

void func_ov003_02216b08(unsigned char *r0, unsigned char r1, unsigned char r2, unsigned int *r3)
{
    r0[2] = r1;
    r0[3] = r2;
    r0[0] = (unsigned char) r3[0];
    r0[1] = (unsigned char) r3[1];
}
