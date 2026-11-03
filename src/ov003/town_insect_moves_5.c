/* town_insect_moves_5: 13 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02233d68 @ 0x02233d68, 0xe4 bytes, Thumb
 * func_ov003_02233cb8 @ 0x02233cb8, 0xb0 bytes, Thumb
 * func_ov003_02233c70 @ 0x02233c70, 0x48 bytes, Thumb
 * func_ov003_02233a94 @ 0x02233a94, 0x1dc bytes, Thumb
 * func_ov003_02233a14 @ 0x02233a14, 0x80 bytes, Thumb
 * func_ov003_022339f0 @ 0x022339f0, 0x24 bytes, Thumb
 * func_ov003_022339bc @ 0x022339bc, 0x34 bytes, Thumb
 * func_ov003_02233930 @ 0x02233930, 0x8c bytes, Thumb
 * func_ov003_02233890 @ 0x02233890, 0xa0 bytes, Thumb
 * func_ov003_022337d8 @ 0x022337d8, 0xb8 bytes, Thumb
 * func_ov003_02233720 @ 0x02233720, 0xb8 bytes, Thumb
 * func_ov003_02233674 @ 0x02233674, 0xac bytes, Thumb
 * func_ov003_022335cc @ 0x022335cc, 0xa8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02233cb8;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02233a14;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02233720;

extern int func_ov003_02234d70(void *self);
extern void func_ov003_02235934(void *self, int a);
extern int func_ov003_02234030(void *self, int a);
extern void func_020550e4(void *p, int a);
extern UnkStruct_02233cb8 *data_020ccf94;
extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);
extern int func_020644cc(int a);
extern int func_02034270(int *ctx, Vec3 *p, int a, int b);
extern int func_020341c8(int *ctx, int a);
extern void func_0203423c(int *ctx);
extern int func_020310c8(int value);
extern short func_0200322c(Vec3 *a, Vec3 *b);
extern int func_020e908c(Vec3 *a, Vec3 *b, int c, int d, int e);
extern int func_020e8bb0(int *p, int a, int b, int c, int d);
extern int func_ov003_02235b54(unsigned char *self, int a, int b);
extern int func_ov003_02235454(unsigned char *self);
extern void func_ov003_02230f60(unsigned char *self);
extern int func_ov003_02232598(unsigned char *self, int n);
extern short func_ov003_0223418c(int a, int b);
extern void func_ov003_022353a4(void *a, int b, int c);
extern void func_ov068_02271960(void *a, void *b);
extern void func_ov068_02271a14(void *a, void *b);
extern void func_ov068_0227191c(void *a, void *b);
extern void func_ov003_02230e18(void *a, void *b);
extern void func_ov068_02270e80(void *a, void *b);
extern int func_020e8870(short *a, int b, int c);
extern void func_ov003_022319bc(void *self, short *p);
extern int func_ov003_022350cc(void *self);
extern int func_ov003_02235834(void *self, int a, int b);
extern void func_ov003_0222d518(void *self, int a);
extern void func_ov003_02234e28(void *self, short *t, int a, int b, int c, int d);
extern int FX_Div(int a, int b);
extern void func_ov003_02234dac(void *self, int a, int b, int c);
extern void func_ov068_02270b00(void *a);
extern void func_ov068_02270d54(void *a);
extern void func_ov068_02270d24(void *a, int b);
extern void func_ov068_02270890(void *a);
extern void func_ov003_02234cc4(void *a);
extern void func_ov003_022348dc(void *a, int b);
extern void func_ov068_02270df8(void *a);
extern void func_ov068_02271398(void *a);
extern void func_ov003_02231104(void *a);
extern void func_ov003_022355d4(void *a);

void func_ov003_02233cb8(char *self, short *out);
short func_ov003_02233c70(int a, int b);
void func_ov003_02233a94(unsigned char *self);
int func_ov003_02233a14(char *self, short *out);
void func_ov003_022339f0(char *self);
void func_ov003_022339bc(char *self);
void func_ov003_02233720(char *self);

void func_ov003_02233d68(char *self)
{
    short *p;
    u8 s;

    p = (short *) (self + 0x242);
    s = *(u8 *) (self + 0x251);
    if (s != 0xb && s != 9 && s != 4) {
        func_ov003_02234d70(self);
    }
    func_ov003_02235934(self, 4);
    switch (s) {
        case 3:
        case 0xf:
            func_ov003_02234030(self, 1);
            break;
        case 7:
            *(u8 *) (self + 0x251) = 0xf;
            *(int *) (self + 0x21c) |= 0xf00;
            func_ov003_02233a14((char *) self, p);
            break;
        case 9:
        case 0xb:
            *(char *) (self + 0x24a) = 1;
        case 4:
        case 0x11:
            func_ov003_02233a94((unsigned char *) self);
            break;
        case 0x13:
            func_ov003_022339bc((char *) self);
            if ((((unsigned int) *(int *) (self + 0xf4)) << 4) >> 16 != 0) {
                func_020550e4(self + 0x50, 0);
            }
            if (func_ov003_02233a14((char *) self, p) == 0) {
                func_ov003_02233cb8((char *) self, p);
                *(int *) (self + 0x21c) = 0;
            }
            break;
    }
}

void func_ov003_02233cb8(char *self, short *out)
{
    *out = *out + 1;
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() == 0) {
        int *s = (int *) (self + 0x204);
        int *d = (int *) (self + 0x1d4);
        if (s[0] != d[0] || s[2] != d[2]) {
            *(char *) (self + 0x251) = 4;
            *out = 0;
            *(char *) (self + 0x24c) = 1;
        }
    } else if (*out >= *(short *) (self + 0x232)) {
        int base = *(short *) (self + 0x23a);
        int t = (int) func_ov003_02233c70(0xc, 1);
        *(short *) (self + 0x240) = t + base;
        *(int *) (self + 0x21c) |= 0xf00;
        *(char *) (self + 0x251) = 3;
        *out = 0;
    }
}

short func_ov003_02233c70(int a, int b)
{
    unsigned char v = func_020644cc(a);
    if (v != 0) {
        if (b != 0) {
            if (func_020644cc(0x64) > 0x32) {
                return v * -0x38e;
            }
        }
        return v * 0x38e;
    }
    return 0;
}

void func_ov003_02233a94(unsigned char *self)
{
    int spd;
    int hit;
    int ctx[16];
    int state;
    Vec3 *prev;
    Vec3 *pos;
    int vy;
    int r;

    prev = (Vec3 *) (self + 0x1d4);
    pos = (Vec3 *) (self + 0x204);
    spd = 0x1000 / self[0x257];
    hit = 0;
    state = self[0x251];
    if (self[0x24a] != 0) {
        func_ov003_02234cc4((void *) self);
        func_ov003_022339f0((char *) self);
    }
    if (func_ov003_02235b54(self, 0x50, 0xe38) == 0) {
        if (func_020e908c(pos, prev, spd, 0x14000, 0x333) == 0) {
            hit = 1;
        } else {
            *(short *) (self + 0x23a) = func_0200322c(pos, prev);
        }
    } else {
        hit = 1;
        prev->x = pos->x;
        prev->y = pos->y;
        prev->z = pos->z;
    }
    if (self[0x24c] != 0) {
        if (func_020e8bb0(&pos->y, 0x1400, spd, 0x1000, 0xcd) == 0) {
            self[0x24c] = 0;
        }
    } else {
        func_02034270(ctx, pos, 0, 1);
        if (ctx[12] != 0) {
            vy = ctx[15];
            if (self[0x251] == 0x11) {
                func_ov003_02235454(self);
                *(short *) (self + 0x242) = 0;
                func_ov003_02230f60(self);
                func_0203423c(ctx);
                return;
            }
        } else {
            vy = func_020341c8(ctx, 1);
            if (vy > 0x4000) {
                vy = func_020310c8(0);
            } else {
                vy = vy + func_020310c8(0);
            }
        }
        if (func_020e8bb0(&pos->y, vy, spd, 0x1000, 0x266) == 0 && hit != 0 && state != 0xb && state != 9) {
            r = func_020644cc(9);
            *(short *) (self + 0x232) = (short) (0x14 * (r + 2));
            self[0x251] = 0x13;
            func_020550e4((void *) (self + 0x50), 0);
            if (vy < 0) {
                func_ov003_02235454(self);
                *(short *) (self + 0x242) = 0;
                func_ov003_02230f60(self);
            } else if (self[0x24a] != 0) {
                self[0x254] = (unsigned char) (self[0x255] - 0xa);
                self[0x24a] = 0;
            }
        }
        func_0203423c(ctx);
    }
    if (state == 9 || state == 0xb) {
        if (func_ov003_02232598(self, 1) != 0) {
            func_ov003_02230f60(self);
        }
    }
}

int func_ov003_02233a14(char *self, short *out)
{
    if (func_02073dd4((*(UnkStruct_02233a14 * *) &data_020ccf94), (*(UnkStruct_02233a14 * *) &data_020ccf94)->unk_64) == 0 || func_020a7278() != 0) {
        int r = func_ov003_02235b54((unsigned char *) self, 0x50, 0xe38);
        if (r != 0) {
            *out = 0;
            *(char *) (self + 0x251) = 0xf;
            *(short *) (self + 0x240) = func_ov003_0223418c(*(short *) (self + 0x23a), r);
            *(int *) (self + 0x21c) |= 0xf00;
            *(int *) (self + 0x21c) += 1;
        }
        return r;
    }
    return 0;
}

void func_ov003_022339f0(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0xc:
        case 0xd:
            func_ov003_022353a4(self, 0, 1);
    }
}

void func_ov003_022339bc(char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0x1b:
        case 0x1c:
        case 0x1d:
            if (*(unsigned char *) (self + 0x254) < 5) {
                func_ov003_022353a4(self, 0, 1);
            }
    }
}

void func_ov003_02233930(char *self)
{
    short *p = (short *) (self + 0x242);
    unsigned char *s = (unsigned char *) (self + 0x251);
    switch (*s) {
        case 3:
        case 0xf:
            func_ov068_02271960(self, p);
            break;
        case 4:
            func_ov068_02271a14(self, p);
            func_ov068_0227191c(self, p);
            break;
        case 0xb:
            func_ov003_02230e18(self, p);
            *p = (short) (*p + 1);
            break;
        case 0x13:
            if (*(short *) (self + 0x232) <= 0) {
                *s = 3;
            } else {
                *(short *) (self + 0x232) = (short) (*(short *) (self + 0x232) - 1);
            }
            break;
    }
}

void func_ov003_02233890(char *self)
{
    short *p = (short *) (self + 0x242);
    switch (*(unsigned char *) (self + 0x251)) {
        case 0:
            func_ov068_02270e80(self, p);
            break;
        case 0xf: {
            short h = *(short *) (self + 0x23a);
            if (func_020e8870(&h, *(short *) (self + 0x240), 0x5b0)) {
                *(char *) (self + 0x251) = 0;
            }
            func_ov003_022353a4(self, 0, 1);
            *(short *) (self + 0x23a) = h;
            break;
        }
        case 9:
        case 0xb:
            func_ov003_02230e18(self, p);
            *p = (short) (*p + 1);
            break;
        case 0x13:
            *(char *) (self + 0x251) = 0;
            break;
    }
}

void func_ov003_022337d8(char *self)
{
    short v;
    int *s;
    int *d;

    switch (*(u8 *) (self + 0x251)) {
        case 0:
            func_ov003_02233720((char *) self);
            break;
        case 9:
        case 0xb:
            if (*(short *) (self + 0x242) == 0) {
                func_ov003_022353a4(self, 1, 0);
            }
            func_ov003_022319bc(self, (short *) (self + 0x242));
            break;
        case 7:
            *(u8 *) (self + 0x251) = 0;
            *(short *) (self + 0x23a) = *(short *) (self + 0x23a) + *(short *) (self + 0x240);
            break;
        case 0x13:
            *(char *) (self + 0x24a) = 0;
            *(u8 *) (self + 0x251) = 0;
            v = *(short *) (self + 0x23a);
            func_ov003_02235834(self, v, func_ov003_022350cc(self));
            s = (int *) (self + 0x204);
            d = (int *) (self + 0x1c8);
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
            break;
    }
}

void func_ov003_02233720(char *self)
{
    short t;
    short *p;

    t = *(short *) (self + 0x23a);
    p = (short *) (self + 0x242);
    if (func_02073dd4((*(UnkStruct_02233720 * *) &data_020ccf94), (*(UnkStruct_02233720 * *) &data_020ccf94)->unk_64) == 0 || func_020a7278() != 0) {
        if (func_ov003_02234d70(self) == 2) {
            func_ov003_0222d518(self, 0x1000);
            *(char *) (self + 0x24a) = 0;
        }
    }
    func_ov003_02234e28(self, &t, 0x38e, 0x28, 0x50, *(u8 *) (self + 0x257) << 12);
    *p = *p + (short) FX_Div(0x2000, (func_020644cc(4) + 5) << 12);
    func_ov003_02234dac(self, *p, 0x1000, (func_020644cc(4) + 0xa) << 12);
}

void func_ov003_02233674(char *self)
{
    switch (*(unsigned char *) (self + 0x251)) {
        case 0:
            func_ov003_022353a4(self, 0, 1);
            func_ov068_02270b00(self);
            break;
        case 2:
            func_ov003_022353a4(self, 0, 1);
            func_ov068_02270d54(self);
            break;
        case 3:
        case 7:
        case 8:
            func_ov068_02270d24(self + 0x210, 0);
            func_ov068_02270890(self);
            break;
        case 0xb:
            func_ov003_022353a4(self, 0, 1);
            func_ov003_02234cc4(self);
            func_ov003_022348dc(self, 0x1333);
            break;
        case 4:
            func_ov068_02270df8(self);
            break;
        case 0x13:
            break;
    }
    *(char *) (self + 0x249) = 1;
}

void func_ov003_022335cc(char *self)
{
    switch (*(unsigned char *) (self + 0x251)) {
        case 0:
            func_ov068_02271398(self);
            break;
        case 6:
            func_ov003_02231104(self);
            func_ov003_022355d4(self);
            break;
        case 9:
        case 0xb:
            func_ov003_02234cc4(self);
            func_ov003_022353a4(self, 0, 1);
            func_ov003_022348dc(self, 0x1ccd);
            break;
        case 7:
            *(char *) (self + 0x251) = 0;
            if (*(unsigned char *) (self + 0x24a) != 0) {
                *(short *) (self + 0x23a) = (short) (*(short *) (self + 0x23a) + *(short *) (self + 0x240));
            }
            break;
        case 0x13:
            *(char *) (self + 0x24a) = 0;
            *(char *) (self + 0x251) = 0;
            break;
    }
}
