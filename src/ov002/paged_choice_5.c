/* paged_choice_5: 13 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_02209910 @ 0x02209910, 0x44 bytes, Thumb
 * func_ov002_02209908 @ 0x02209908, 0x8 bytes, Thumb
 * func_ov002_022098ec @ 0x022098ec, 0x1c bytes, Thumb
 * func_ov002_02209874 @ 0x02209874, 0x78 bytes, Thumb
 * func_ov002_02209868 @ 0x02209868, 0xc bytes, Thumb
 * func_ov002_0220984c @ 0x0220984c, 0x1a bytes, Thumb
 * func_ov002_02209804 @ 0x02209804, 0x48 bytes, Thumb
 * func_ov002_022097b8 @ 0x022097b8, 0x4c bytes, Thumb
 * func_ov002_02209770 @ 0x02209770, 0x48 bytes, Thumb
 * func_ov002_02209740 @ 0x02209740, 0x2e bytes, Thumb
 * func_ov002_0220970c @ 0x0220970c, 0x34 bytes, Thumb
 * func_ov002_022096d8 @ 0x022096d8, 0x34 bytes, Thumb
 * func_ov002_0220968c @ 0x0220968c, 0x4a bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02209910 {
    u8 pad_00[0x19];
    u8 unk_19;
};

struct UnkStruct_02209874 {
    u8 pad_00[0x19];
    u8 unk_19;
};

struct UnkStruct_022097b8 {
    u8 pad_00[0x1a];
    u8 unk_1A;
};

struct UnkStruct_02209770 {
    u8 pad_00[0x1a];
    u8 unk_1A;
};

struct UnkStruct_022096d8 {
    u8 pad_00[0x17];
    u8 unk_17;
};

struct UnkStruct_0220968c {
    u8 pad_00[0x16];
    u8 unk_16;
    u8 pad_17;
    u8 unk_18;
};

extern int func_ov002_02209324(struct UnkStruct_02209910 *self);
extern int func_ov002_02209318(void *self);
extern int func_0208a808(void *w);
extern int func_0208a804(void *w);
extern int func_0208a7f0(void *w);
extern void func_0200284c(int, int parameter1, int parameter2);
extern int func_02002d14(const void *d, void *g, int i, int a, int b, int c);
extern int func_02002c6c(const void *d, void *g, int i, int a, int b, int c);
extern void *data_021fbe94;
extern const char data_ov002_0220bbe0[];
extern const char data_ov002_0220bbfc[];
extern const char data_ov002_0220bbb8[];
extern const char data_ov002_0220bbcc[];
extern void func_ov002_02208b74(void *self, int *px);
extern void func_ov002_02209954(void *self, int x, int y);
extern void func_0200277c(int);
extern void func_0200467c(int);
extern void func_ov002_02208a04(void *, int);
extern void func_ov002_02208a0c(void *, int);
extern int func_ov002_02208a14(struct UnkStruct_022096d8 *self, int bit);

int func_ov002_0220984c(char *self, int a1, int a2);
void func_ov002_02209804(void *self, int x, int y);
void func_ov002_0220970c(char *self, int a1);

void func_ov002_02209910(struct UnkStruct_02209910 *self, int x, int y)
{
    int w;
    int h;
    int nx;
    int ny;

    w = func_ov002_02209324(self);
    h = func_ov002_02209318((void *) self);
    nx = x - w + 0x20;
    if (nx > 0) {
        self->unk_19 = 1;
    } else {
        nx = x - 0x10;
        self->unk_19 = 0;
    }
    ny = y - h - 4;
    if (ny < 0xa) {
        ny = 0xa;
    }
    func_ov002_0220984c((char *) self, nx, ny);
}

void func_ov002_02209908(void *arg0, int arg1, int arg2)
{
    func_ov002_02209804((void *) arg0, arg1, arg2);
}

void func_ov002_022098ec(void *self, int x, int y)
{
    int ny = y - func_ov002_02209318(self);

    func_ov002_02209804(self, x, ny);
}

void func_ov002_02209874(struct UnkStruct_02209874 *self, void *w)
{
    int px;
    int py;
    int h;
    int hw;
    int t;

    self->unk_19 = 0;
    px = func_0208a808(w) + 0x80;
    py = func_0208a804(w) + 0x60;
    h = func_ov002_02209318((void *) self);
    hw = func_0208a7f0(w) >> 1;
    t = px + hw;
    if (t > 0x100) {
        px -= t - 0x100;
    } else {
        t = px - hw;
        if (t < 0) {
            px -= t;
        }
    }
    px -= 2;
    px -= func_ov002_02209324((struct UnkStruct_02209910 *) self) >> 1;
    t = py - h;
    if (t < 0xa) {
        py += 0x10;
    } else {
        py = t;
    }
    func_ov002_02209804((void *) self, px, py);
}

void func_ov002_02209868(char *self, int arg1, int arg2)
{
    // DECLS
    // ENDDECLS
    func_0200284c(*(u8 *) (self + 0x1a), arg1, arg2);
}

int func_ov002_0220984c(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    func_ov002_02209868((char *) self, a1, a2);
    *(int *) (self + 0x8) = -a1;
    *(int *) (self + 0xc) = -a2;
    return -a2;
}

void func_ov002_02209804(void *self, int x, int y)
{
    int w;
    int h;

    w = func_ov002_02209324((struct UnkStruct_02209910 *) self);
    h = func_ov002_02209318(self);
    if (x < 0) {
        x = 0;
    }
    if (y < 0xa) {
        y = 0xa;
    }
    if (x + w > 0xff) {
        x = 0xff - w;
    }
    if (y + h > 0xb6) {
        y = 0xb6 - h;
    }
    func_ov002_0220984c((char *) self, x, y);
}

void func_ov002_022097b8(struct UnkStruct_022097b8 *self)
{
    void *g = data_021fbe94;

    func_02002d14(data_ov002_0220bbe0, g, self->unk_1A, 0, 3, 3);
    func_02002c6c(data_ov002_0220bbfc, g, self->unk_1A, 0x242, 0x242, 0x2d7);
}

int func_ov002_02209770(struct UnkStruct_02209770 *self)
{
    void *g = data_021fbe94;

    func_02002d14(data_ov002_0220bbb8, g, self->unk_1A, 0xe, 0xe, 0xe);
    return func_02002c6c(data_ov002_0220bbcc, g, self->unk_1A, 0x26e, 0x26e, 0x27d);
}

void func_ov002_02209740(void *self, int x, int y)
{
    func_ov002_02208b74(self, &x);
    func_ov002_02209954(self, 0, -0xc);
    func_ov002_0220970c((char *) self, y);
}

void func_ov002_0220970c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x17) = 0x1;
    func_0200277c(*(u8 *) (self + 0x1a));
    if (a1 != 0x0) {
        func_ov002_02208a0c(self, 0x2);
    }
    func_0200467c(0x13);
    func_ov002_02208a04(self, 0x10);
}

void func_ov002_022096d8(struct UnkStruct_022096d8 *self, int flag)
{
    self->unk_17 = 2;
    if (flag) {
        func_ov002_02208a0c((void *) self, 4);
    }
    if (func_ov002_02208a14(self, 0x10)) {
        func_ov002_02208a04((void *) self, 0x10);
    } else {
        func_0200467c(0x14);
    }
}

void func_ov002_0220968c(struct UnkStruct_0220968c *self, int mode)
{
    if (func_ov002_02208a14((struct UnkStruct_022096d8 *) self, 2) && mode == 1) {
        mode = 2;
        func_ov002_02208a04((void *) self, mode);
    } else if (func_ov002_02208a14((struct UnkStruct_022096d8 *) self, 4) && mode == 4) {
        mode = 5;
        func_ov002_02208a04((void *) self, 4);
    }
    self->unk_16 = mode;
    self->unk_18 = 0;
}
