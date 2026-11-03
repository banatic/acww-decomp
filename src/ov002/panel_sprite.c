/* panel_sprite: 20 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220b3c4 @ 0x0220b3c4, 0x2c bytes, Thumb
 * func_ov002_0220b3a4 @ 0x0220b3a4, 0x20 bytes, Thumb
 * func_ov002_0220b37c @ 0x0220b37c, 0x28 bytes, Thumb
 * func_ov002_0220b36c @ 0x0220b36c, 0xe bytes, Thumb
 * func_ov002_0220b358 @ 0x0220b358, 0x14 bytes, Thumb
 * func_ov002_0220b338 @ 0x0220b338, 0x1e bytes, Thumb
 * func_ov002_0220b318 @ 0x0220b318, 0x1e bytes, Thumb
 * func_ov002_0220b2d0 @ 0x0220b2d0, 0x46 bytes, Thumb
 * func_ov002_0220b2bc @ 0x0220b2bc, 0x12 bytes, Thumb
 * func_ov002_0220b2ac @ 0x0220b2ac, 0xe bytes, Thumb
 * func_ov002_0220b29c @ 0x0220b29c, 0xe bytes, Thumb
 * func_ov002_0220b290 @ 0x0220b290, 0xc bytes, Thumb
 * func_ov002_0220b280 @ 0x0220b280, 0x10 bytes, Thumb
 * func_ov002_0220b1a4 @ 0x0220b1a4, 0xdc bytes, Thumb
 * func_ov002_0220b168 @ 0x0220b168, 0x3c bytes, Thumb
 * func_ov002_0220b15c @ 0x0220b15c, 0xc bytes, Thumb
 * func_ov002_0220b150 @ 0x0220b150, 0xc bytes, Thumb
 * func_ov002_0220b144 @ 0x0220b144, 0xc bytes, Thumb
 * func_ov002_0220b138 @ 0x0220b138, 0xc bytes, Thumb
 * func_ov002_0220b12c @ 0x0220b12c, 0xc bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0220b1a4 {
    u8 pad_00[0x70];
    char *unk_70;
    u8 pad_74[1];
    u8 unk_75;
    u8 unk_76;
};

struct UnkStruct_0220b168 {
    u8 pad_00[0x75];
    volatile u8 unk_75;
};

extern void *func_02070c08(void *);
extern void *data_ov002_0220bd18;
extern void func_02070b84(void *);
extern int **func_02070be8(void *);
extern void func_020edb3c(void *);
extern int func_0207094c(void *, int);
extern void func_02070a04(void *, int, int);
extern void func_02070adc(void *, int, int, int, int, int, int);
extern void *data_ov002_0220ba54;
extern void func_02088df8(int a0, char *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);

void func_ov002_0220b2d0(char *self, int a1, int a2);
void func_ov002_0220b2ac(char *self, int a1);
void func_ov002_0220b29c(char *self, int a1);

void *func_ov002_0220b3c4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bd18;
    func_02070c08(self + 0x4);
    *(void **) (self + 0x70) = 0x0;
    *(u8 *) (self + 0x75) = 0x0;
    *(u8 *) (self + 0x78) = 0x0;
    return self;
}

void *func_ov002_0220b3a4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bd18;
    func_02070b84(self + 0x4);
    func_02070be8(self + 0x4);
    return self;
}

void *func_ov002_0220b37c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bd18;
    func_02070b84(self + 0x4);
    func_02070be8(self + 0x4);
    func_020edb3c(self);
    return self;
}

void func_ov002_0220b36c(char *p, int a, u8 b, u8 c)
{
    *(int *) (p + 0x70) = a;
    *(u8 *) (p + 0x74) = b;
    *(u8 *) (p + 0x76) = c;
}

void func_ov002_0220b358(u8 *self, int v)
{
    self[0x77] = v;
    func_ov002_0220b2d0((char *) self, 0xf, 0);
}

void func_ov002_0220b338(char *self, int value)
{
    func_ov002_0220b358((u8 *) self, value);
    self[0x75] = 0;
    func_ov002_0220b29c(self, 1);
}

void func_ov002_0220b318(char *self, unsigned char value)
{
    func_ov002_0220b358((u8 *) self, value);
    *(u8 *) (self + 0x75) = 0;
    func_ov002_0220b2ac(self, 1);
}

void func_ov002_0220b2d0(char *self, int a1, int a2)
{
    // DECLS
    // ENDDECLS
    func_0207094c(self + 0x4, *(u8 *) (self + 0x77));
    func_02070adc(self + 0x4, 0x8, ((u32) (*(int *) ((char *) *(int *) (self + 0x70) + 0x4) << 22) >> 22),
                  *(u8 *) (self + 0x74), a1, a2, 0x0);
    func_02070a04(self + 0x4, 0x1, 0x0);
}

int func_ov002_0220b2bc(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    if ((*(u8 *) (self + 0x78) & a1) != 0x0) {
        return 0x1;
    }
    return 0x0;
}

void func_ov002_0220b2ac(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x78) = (*(u8 *) (self + 0x78) | a1);
}

void func_ov002_0220b29c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    *(u8 *) (self + 0x78) = (*(u8 *) (self + 0x78) & ~a1);
}

void func_ov002_0220b290(int arg)
{
    func_02070b84((void *) (arg + 4));
}

int func_ov002_0220b280(char *self)
{
    // DECLS
    // ENDDECLS
    return *(u8 *) ((char *) &data_ov002_0220ba54 + *(u8 *) (self + 0x75));
}

void func_ov002_0220b1a4(struct UnkStruct_0220b1a4 *self, int x, int y, int a)
{
    int base;
    int c;
    int px;
    int py;

    base = func_ov002_0220b280((char *) self);
    c = -1;
    if (func_ov002_0220b2bc((char *) self, 4)) {
        c = 2;
    }
    py = y + 0x60 + base;
    px = x + 0x80 + base;
    func_02088df8(1, self->unk_70, px, py, c, a, 0x1000, 0x1000, 0, -1, 0, 0);
    if (func_ov002_0220b2bc((char *) self, 2)) {
        func_02088df8(1, self->unk_70, px, py, -1, a, 0x1000, 0x1000, 0, 2, 0, 0);
    }
    if (!func_ov002_0220b2bc((char *) self, 1) && self->unk_75 + 1 != 3) {
        x += 0x83;
        y += 0x63;
        func_02088df8(1, self->unk_70 + self->unk_76 * 8, x, y, 1, a, 0x1000, 0x1000, 0, -1, 0, 0);
    }
}

int func_ov002_0220b168(struct UnkStruct_0220b168 *self)
{
    if (self->unk_75 == 0) {
        func_ov002_0220b2d0((char *) self, 0xe, 0);
    }
    if (self->unk_75 + 1 < 3) {
        self->unk_75 = self->unk_75 + 1;
    } else {
        return 0;
    }
    return 1;
}

void func_ov002_0220b15c(int a)
{
    func_ov002_0220b2ac((char *) a, 2);
}

void func_ov002_0220b150(int a)
{
    func_ov002_0220b29c((char *) a, 2);
}

void func_ov002_0220b144(int a)
{
    func_ov002_0220b2ac((char *) a, 4);
}

void func_ov002_0220b138(int a)
{
    func_ov002_0220b29c((char *) a, 4);
}

int func_ov002_0220b12c(int a)
{
    return func_ov002_0220b2bc((char *) a, 4);
}
