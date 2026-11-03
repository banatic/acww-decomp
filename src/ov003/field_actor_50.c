/* field_actor_50: 9 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02218108 @ 0x02218108, 0xc0 bytes, Thumb
 * func_ov003_02217e30 @ 0x02217e30, 0x2d8 bytes, Thumb
 * func_ov003_02217e14 @ 0x02217e14, 0x1a bytes, Thumb
 * func_ov003_02217ddc @ 0x02217ddc, 0x36 bytes, Thumb
 * func_ov003_02217d60 @ 0x02217d60, 0x7c bytes, Thumb
 * func_ov003_02217d54 @ 0x02217d54, 0xc bytes, Thumb
 * func_ov003_02217d3c @ 0x02217d3c, 0x18 bytes, Thumb
 * func_ov003_02217d38 @ 0x02217d38, 0x2 bytes, Thumb
 * func_ov003_02217d1c @ 0x02217d1c, 0x1c bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x2d8];
    unsigned int unk_2D8;
    char pad_2DC[0x704 - 0x2dc];
    int unk_704;
    char pad_708[0x7d5 - 0x708];
    unsigned char unk_7D5;
} UnkStruct_02218108;

typedef struct UnkStruct_02217e30 {
    u8 pad_00[0x2d0];
    u8 sub_2d0[0x7d4 - 0x2d0];
    u8 unk_7D4;
    u8 pad_7D5[0x7f0 - 0x7d5];
    int unk_7F0;
    u8 pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
} UnkStruct_02217e30;

struct UnkStruct_02217d60 {
    char pad_00[0x7f8];
    int unk_7F8;
    char pad_7FC[0x4];
    int unk_800;
};

typedef struct {
    int a;
    int c;
    int d;
    short e;
    char b;
} UnkStruct_02217d1c;

extern void func_02010f5c(void *self);
extern void func_020109a0(void *self, int b, int c, unsigned short d);
extern void func_0200f888(void *self);
extern void *data_020ccf94;
extern int func_02056f94(void *p);
extern void func_0200f3e8(UnkStruct_02217e30 *self);
extern int func_02008258(UnkStruct_02217e30 *self, int a);
extern void func_020110c4(volatile u16 *out, UnkStruct_02217e30 *self);
extern void func_0200f268(UnkStruct_02217e30 *self, int a);
extern unsigned int *func_0200f27c(UnkStruct_02217e30 *self, int a);
extern int func_0200f290(UnkStruct_02217e30 *self, int a);
extern int func_0204bcdc(volatile u16 *p);
extern int func_0204bc64(volatile u16 *p);
extern int func_020b22dc(void);
extern int func_02073908(void *g, int a);
extern int func_ov003_02217c5c(UnkStruct_02217e30 *self, int a, int b, int c, int d, int e, int f, int g);
extern void *func_020094a0(UnkStruct_02217e30 *self, int a, int b, int c, int d, int e);
extern int func_0203e110(void);
extern int func_0200d4e8(UnkStruct_02217e30 *self, int a, int b, int c);
extern int func_0208602c(void);
extern void func_020860d4(int h, int a);
extern int func_020984e8(void);
extern void func_02098fd0(int h, int a);
extern void func_02042500(void);
extern void func_02010d64(int arg);
extern unsigned int func_0200e92c(void *p);
extern void func_0200e90c(void *p, int x, int y, int z);
extern int func_0200e894(int a, void *p);
extern int func_0200e91c(void *p);
extern int func_ov003_022203ac(void);
extern int func_02086108(int a, int b);
extern void func_02035684(int a, int b, int c);

void func_ov003_02218108(UnkStruct_02218108 *self)
{
    unsigned char *p = &self->unk_7D5;
    int v;
    unsigned char c;

    func_02010f5c(self);
    c = self->unk_7D5;
    if (c != 0) {
        *p = (unsigned char) (c - 1);
        if (*p == 0) {
            if (self->unk_704 == 0x36) {
                func_020109a0(self, 0x35, 5, 0);
            }
        }
    } else {
        if (self->unk_704 == 0x34) {
            v = (int) ((self->unk_2D8 << 4) >> 16);
            switch (v) {
                case 0xd:
                case 0x11:
                case 0x17:
                case 0x1c:
                case 0x25:
                case 0x28:
                    func_0200f888(self);
                    break;
            }
        } else if (self->unk_704 == 0x35) {
            v = (int) ((self->unk_2D8 << 4) >> 16);
            switch (v) {
                case 4:
                case 9:
                case 0xe:
                case 0x14:
                    func_0200f888(self);
                    break;
            }
        }
    }
}

void func_ov003_02217e30(UnkStruct_02217e30 *self)
{
    volatile u16 a;
    volatile u16 b;
    volatile u16 t1;
    volatile u16 t2;
    volatile u16 t3;
    volatile u16 t4;
    u8 *st;
    u8 state;
    void *g;
    int c;

    if (func_02056f94(self->sub_2d0) == 0) {
        return;
    }

    func_0200f3e8(self);
    self->unk_7FC = func_02008258(self, self->unk_7F0);
    st = &self->unk_7D4;
    state = *st;
    func_020110c4(&a, self);

    if (state <= 1) {
        int ok = 0;
        u16 x = a;
        u16 y = a;
        if (y >= 0x1380 && x <= 0x139f) {
            ok = 1;
        }
        if (ok != 0 || (x >= 0x13a0 && x <= 0x13a7)) {
            func_0200f268(self, 0x1d);
        }
    }

    switch (*st) {
        case 0:
            if (func_0204bcdc(&a) != 0) {
                t4 = 0xfff1;
                if (func_0204bc64(&a) == func_0204bc64(&t4)) {
                    c = 1;
                } else {
                    c = 0;
                }
            } else {
                if (a == 0xfff1) {
                    c = 1;
                } else {
                    c = 0;
                }
            }
            if (c == 0 && func_020b22dc() == 0 && func_0200f290(self, 0x1d) == 0) {
                func_ov003_02217c5c(self, 2, 2, 0, 0, 0, 6, -1);
                break;
            }
            if (func_02073908(data_020ccf94, self->unk_800) != 0) {
                if (func_0204bcdc(&a) != 0) {
                    t1 = 0xfff1;
                    if (func_0204bc64(&a) == func_0204bc64(&t1)) {
                        c = 1;
                    } else {
                        c = 0;
                    }
                } else {
                    if (a == 0xfff1) {
                        c = 1;
                    } else {
                        c = 0;
                    }
                }
                if (c != 0) {
                    func_0200f27c(self, 0);
                }
            }
            // fall through
        case 1:
            if (func_0204bcdc(&a) != 0) {
                t2 = 0xfff1;
                if (func_0204bc64(&a) == func_0204bc64(&t2)) {
                    c = 1;
                } else {
                    c = 0;
                }
            } else {
                if (a == 0xfff1) {
                    c = 1;
                } else {
                    c = 0;
                }
            }
            if (c != 0) {
                func_0200f27c(self, 0);
            }
            func_0203e110();
            func_0200f268(self, 0x1d);
            func_0200d4e8(self, 3, 1, -1);
            break;
        case 2:
            g = data_020ccf94;
            if (func_02073908(g, self->unk_800) != 0) {
                func_020860d4(func_0208602c(), 0);
            }
            if (func_020b22dc() == 0) {
                func_020094a0(self, 2, 0, 0, 6, -1);
                break;
            }
            func_0203e110();
            if (func_02073908(g, self->unk_800) != 0) {
                goto notify;
            }
            func_020110c4(&b, self);
            if (func_0204bcdc(&b) != 0) {
                t3 = 0xfff1;
                if (func_0204bc64(&b) == func_0204bc64(&t3)) {
                    c = 1;
                } else {
                    c = 0;
                }
            } else {
                if (b == 0xfff1) {
                    c = 1;
                } else {
                    c = 0;
                }
            }
            if (c == 0) {
                goto done;
            }
        notify:
            func_0200f27c(self, 0);
        done:
            func_0200f268(self, 0x1d);
            func_0200d4e8(self, 3, 1, -1);
            break;
        case 3:
            if (func_02073908(data_020ccf94, self->unk_800) != 0) {
                func_020860d4(func_0208602c(), 5);
                func_02098fd0(func_020984e8(), 1);
                func_02042500();
            }
            func_020094a0(self, 3, 0, 0, 6, -1);
            break;
    }
}

void func_ov003_02217e14(int arg)
{
    func_ov003_02218108((UnkStruct_02218108 *) arg);
    func_02010d64(arg);
    func_ov003_02217e30((UnkStruct_02217e30 *) arg);
}

int func_ov003_02217ddc(int a, int b, int c)
{
    char buffer[32];
    int result;
    func_0200e92c(buffer);
    func_0200e90c(buffer, 0x3c, b, c);
    result = func_0200e894(a, buffer);
    func_0200e91c(buffer);
    return result;
}

void func_ov003_02217d60(struct UnkStruct_02217d60 *p, void *message, int previous)
{
    int zero = 0;

    if (((void) (func_0200f268((UnkStruct_02217e30 *) p, 0)), func_ov003_022203ac()) != 0) {
        func_020109a0(p, 0x34, zero, zero);
    } else {
        func_020109a0(p, 0x35, zero, zero);
    }

    p->unk_7F8 = 0;

    if (func_02086108(func_0208602c(), 0) != 0 || func_02086108(func_0208602c(), 5) != 0) {
        if (func_02073908(data_020ccf94, p->unk_800) != 0) {
            func_02035684(0x12, 0xf, 0);
        }
    }
}

void func_ov003_02217d54(void *a, int b)
{
    func_ov003_02217ddc((int) a, 1, b);
}

void func_ov003_02217d3c(int a, int b)
{
    if (b == 0x3b || b == 0x3d) {
        return;
    }
    func_0200f27c((UnkStruct_02217e30 *) a, 0);
}

void func_ov003_02217d38(void *receiver) {}

void func_ov003_02217d1c(UnkStruct_02217d1c *self, int a, char b, int c, int d, short e)
{
    self->a = a;
    self->b = b;
    self->c = c;
    self->d = d;
    self->e = e;
}
