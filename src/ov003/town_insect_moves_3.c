/* town_insect_moves_3: 12 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02232d30 @ 0x02232d30, 0xa4 bytes, Thumb
 * func_ov003_02232c70 @ 0x02232c70, 0xc0 bytes, Thumb
 * func_ov003_02232b68 @ 0x02232b68, 0x108 bytes, Thumb
 * func_ov003_02232aa0 @ 0x02232aa0, 0xc8 bytes, Thumb
 * func_ov003_02232a44 @ 0x02232a44, 0x5c bytes, Thumb
 * func_ov003_02232874 @ 0x02232874, 0x1d0 bytes, Thumb
 * func_ov003_02232640 @ 0x02232640, 0x234 bytes, Thumb
 * func_ov003_022325d4 @ 0x022325d4, 0x6c bytes, Thumb
 * func_ov003_02232598 @ 0x02232598, 0x3c bytes, Thumb
 * func_ov003_02232414 @ 0x02232414, 0x184 bytes, Thumb
 * func_ov003_02232210 @ 0x02232210, 0x204 bytes, Thumb
 * func_ov003_022321b8 @ 0x022321b8, 0x58 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02232c70;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02232b68;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02232aa0;

extern void func_ov003_02233178(void *a, void *b);
extern void func_ov003_02232f78(void *a, void *b);
extern void func_020550e4(void *a, int b);
extern UnkStruct_02232c70 *data_020ccf94;
extern int func_ov003_022353e0(void *self, int *p);
extern int func_ov003_02233e4c(void *self, int *v);
extern int func_0200322c(int *p, int *v);
extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);
extern int func_ov003_02235834(void *self, int a, int b);
extern void func_ov003_02230f60(unsigned char *self);
extern int func_ov003_02219d04(int *p, int i);
extern char *func_ov003_022356ec(int *p);
extern void *func_0209d088(void *p);
extern void NNS_G3dMdlSetMdlAlpha(void *m, int a, int b);
extern void func_ov068_02271644(void *a);
extern void func_ov003_022348dc(void *a, int b);
extern void func_ov003_022349a0(void *a);
extern int func_02034270(int *ctx, Vec3 *p, int a, int b);
extern int func_020341c8(int *ctx, int a);
extern int func_02034184(int *ctx, int y);
extern void func_0203423c(int *ctx);
extern int func_020310c8(int a);
extern int func_020644cc(int n);
extern int FX_MulFunc(int a, int b);
extern void func_ov003_0223597c(Vec3 *d, int ang);
extern int func_ov003_02232dd4(unsigned char *self);
extern int func_ov003_02234984(unsigned char *self);
extern void func_ov003_0222e358(unsigned char *self, int n);
extern int func_ov003_02235454(unsigned char *self);
extern int func_02070070(void);
extern int func_ov003_02219604(void);
extern int func_ov068_02270680(unsigned char *self, short *p);
extern void func_ov068_02270750(unsigned char *self, short *p, int a);
extern void func_02056fcc(char *p, int a, int b, int c, int d);
extern void func_ov003_022353a4(unsigned char *self, int a, int b);
extern int func_020e8870(short *t, int a, int b);
extern int func_ov003_02233c70(int a, int b);
extern int FX_Div(int a, int b);
extern void func_ov068_02271160(void *a);
extern void func_ov068_02271358(void *a);
extern void func_ov003_022319bc(void *a, void *b);
extern int NNS_G3dMdlGetMdlAlpha(void *a, int b);
extern int func_020e908c(Vec3 *a, Vec3 *b, int c, int d, int e);
extern short FX_SinCosTable_[];

void func_ov003_02232c70(char *self);
void func_ov003_02232b68(unsigned char *self);
int func_ov003_02232aa0(char *self, short *out);
int func_ov003_02232598(char *self, int d);
int func_ov003_02232414(unsigned char *self);
int func_ov003_02232210(unsigned char *self);

void func_ov003_02232d30(char *self)
{
    short *p = (short *) (self + 0x242);
    switch (*(unsigned char *) (self + 0x251)) {
        case 4:
        case 0x11:
            func_ov003_02232b68((unsigned char *) self);
            break;
        case 0xb:
            if (((unsigned int) *(int *) (self + 0xf4) << 4) >> 16 == 1) {
                func_020550e4(self + 0x50, 0);
            }
            // falls through
        case 5:
            func_ov003_02233178(self, p);
            break;
        case 9:
            func_ov003_02232f78(self, p);
            break;
        case 7:
            func_ov003_02232c70((char *) self);
            break;
        case 0x13:
            func_ov003_02232aa0((char *) self, (short *) p);
            if (((unsigned int) *(int *) (self + 0xf4) << 4) >> 16 != 0) {
                func_020550e4(self + 0x50, 0);
            }
            break;
    }
}

void func_ov003_02232c70(char *self)
{
    int v[4];
    short n;
    int *p;

    n = *(short *) (self + 0x232);
    p = (int *) (self + 0x204);
    if (func_ov003_022353e0(self, p) != 0) {
        n = 1;
    }
    if (n <= 0) {
        if (func_ov003_02232598((char *) self, 1) != 0) {
            func_ov003_02230f60((unsigned char *) self);
        }
    } else {
        func_ov003_02233e4c(self, v);
        if (v[0] != 0) {
            *(short *) (self + 0x232) = n - 1;
            if (*(u8 *) (self + 0x254) < *(u8 *) (self + 0x255)) {
                *(u8 *) (self + 0x251) = 4;
                func_020550e4(self + 0x50, 1);
                *(short *) (self + 0x23a) = func_0200322c(p, v) + 0x8000;
                if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() != 0) {
                    func_ov003_02235834(self, *(short *) (self + 0x23a), 0xc000);
                }
            }
        }
    }
}

void func_ov003_02232b68(unsigned char *self)
{
    Vec3 *p;
    short w;
    Vec3 v;

    p = (Vec3 *) (self + 0x204);
    w = *(short *) (self + 0x232);
    if (func_02073dd4((void *) ((*(UnkStruct_02232b68 * *) &data_020ccf94)), (*(UnkStruct_02232b68 * *) &data_020ccf94)->unk_64) != 0) {
        if (func_ov003_02232210(self) != 0) {
            return;
        }
    } else {
        if (func_ov003_02232414(self) == 0) {
            return;
        }
    }
    func_ov003_02233e4c((void *) self, (int *) (&v));
    if (self[0x254] >= self[0x255] &&
        (func_02073dd4((void *) ((*(UnkStruct_02232b68 * *) &data_020ccf94)), (*(UnkStruct_02232b68 * *) &data_020ccf94)->unk_64) == 0 || func_020a7278() != 0 ||
         (*(int *) (self + 0x1d4) == *(int *) (self + 0x204) && *(int *) (self + 0x1dc) == *(int *) (self + 0x20c)))) {
        self[0x251] = 7;
        func_020550e4((void *) (self + 0x50), 0);
        if (func_02073dd4((void *) ((*(UnkStruct_02232b68 * *) &data_020ccf94)), (*(UnkStruct_02232b68 * *) &data_020ccf94)->unk_64) != 0 && func_020a7278() != 0) {
            Vec3 *s = (Vec3 *) (self + 0x204);
            Vec3 *d = (Vec3 *) (self + 0x1d4);
            d->x = s->x;
            d->y = s->y;
            d->z = s->z;
        }
    } else if (w <= 0) {
        if (func_ov003_02232598((char *) self, 1) != 0) {
            func_ov003_02230f60(self);
        }
    } else {
        if (func_ov003_022353e0((void *) self, (int *) p) != 0) {
            w = 1;
        }
        *(short *) (self + 0x232) = (short) (w - 1);
    }
}

int func_ov003_02232aa0(char *self, short *out)
{
    s8 *st;
    int *p;
    s8 i;
    char *q;
    int ang;

    st = (s8 *) (self + 0x24e);
    p = (int *) (self + 0x204);
    if (*st <= 0) {
        if (func_02073dd4((*(UnkStruct_02232aa0 * *) &data_020ccf94), (*(UnkStruct_02232aa0 * *) &data_020ccf94)->unk_64) != 0) {
            for (i = 0; i < 4; i++) {
                *st = (s8) func_ov003_02219d04(p, i);
                if (*st > 0) {
                    break;
                }
            }
        } else {
            *st = (s8) func_ov003_02219d04(p, 4);
        }
    }
    if (*st > 0) {
        *st = *st - 1;
        if (*st == 0) {
            q = func_ov003_022356ec(p);
            if (q != 0) {
                ang = func_0200322c(p, (int *) (q + 0x5c));
                *(u8 *) (self + 0x251) = 5;
                NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, 0x1f);
                *(short *) (self + 0x23a) = ang + 0x8000;
                *out = 0;
                return 1;
            }
        }
    }
    return 0;
}

void func_ov003_02232a44(char *self)
{
    // The address is written out at both uses. Case 9/0xB comes before case 7.
    switch (*(unsigned char *) (self + 0x251)) {
        case 0:
            func_ov068_02271644(self);
            break;
        case 9:
        case 0xb:
            func_ov003_022348dc(self, 0x1ccd);
            break;
        case 7:
            func_ov003_022349a0(self);
            break;
        case 0x13:
            *(char *) (self + 0x24a) = 0;
            *(char *) (self + 0x251) = 0;
            break;
    }
}

void func_ov003_02232874(unsigned char *self)
{
    int base;
    volatile Vec3 save;
    int ctx[16];
    Vec3 d;
    short *p242;
    Vec3 *pos;
    int y;
    int n;
    int kind;

    kind = self[0x251];
    switch (kind) {
        case 6:
            func_ov003_02232dd4(self);
            if (func_ov003_02234984(self) != 0) {
                self[0x251] = 0xb;
            }
            break;
        case 0xb:
            p242 = (short *) (self + 0x242);
            pos = (Vec3 *) (self + 0x204);
            save.x = pos->x;
            save.y = pos->y;
            save.z = pos->z;
            y = *(int *) (self + 0x228);
            func_02034270(ctx, pos, 0, 1);
            func_ov003_0222e358(self, 0xc8);
            if (func_ov003_02232dd4(self) == 0) {
                func_ov003_0223597c(&d, *(short *) (self + 0x23a));
                pos->x = pos->x + FX_MulFunc(self[0x257] << 12, d.x);
                pos->z = pos->z + FX_MulFunc(self[0x257] << 12, d.z);
            }
            if (y > 0x1000) {
                pos->y = y + FX_MulFunc(0x59a - FX_MulFunc(0xcd, *p242 << 12), *p242 << 12);
            } else {
                pos->y = y + FX_MulFunc(0x99a - FX_MulFunc(0xcd, *p242 << 12), *p242 << 12);
            }
            if (ctx[12] != 0) {
                y = ctx[15];
            } else {
                y = func_020341c8(ctx, 1);
                y = y + func_020310c8(0);
                if (y > 0x1000) {
                    if (y > 0x4000) {
                        y = func_020310c8(0);
                    } else {
                        pos->x = save.x;
                        pos->z = save.z;
                    }
                }
            }
            if (pos->y < y) {
                base = func_020644cc(3);
                *p242 = 0;
                pos->y = y;
                if (func_02034184(ctx, pos->y) != 0) {
                    func_ov003_02230f60(self);
                    func_ov003_02235454(self);
                } else {
                    self[0x251] = 6;
                    *(short *) (self + 0x244) = 4;
                    *(int *) (self + 0x228) = y;
                    if (func_020644cc(100) > 0x32 && *(int *) (self + 0x21c) - base > 0) {
                        self[0x257] = (unsigned char) (*(int *) (self + 0x21c) - base);
                    } else {
                        self[0x257] = (unsigned char) (base + *(int *) (self + 0x21c));
                    }
                }
            } else {
                *p242 = (short) (*p242 + 1);
            }
            if (func_ov003_02232598((char *) self, 1) != 0) {
                func_ov003_02230f60(self);
            }
            func_0203423c(ctx);
            break;
    }
}

void func_ov003_02232640(unsigned char *self)
{
    int flag;
    char *p;
    short t;
    int state;
    Vec3 *pos;
    short *p23e;
    unsigned v;
    int n;
    int h;

    flag = 0;
    state = self[0x251];
    pos = (Vec3 *) (self + 0x204);
    p23e = (short *) (self + 0x23e);
    p = (char *) self;
    p = (char *) ((int) p + 0x50);
    if (func_02070070() == 0) {
        if (func_ov003_02219604() != 0) {
            self[0x247] = 1;
        } else {
            self[0x247] = 0;
        }
    }
    if (self[0x24c] == 0 && state != 0xb && state != 9) {
        flag = func_ov068_02270680(self, (short *) (self + 0x236));
        if (self[0x251] != 5) {
            if (flag == 1) {
                return;
            }
            if (*(signed char *) (self + 0x24d) == 0x37 && flag == 0) {
                v = (unsigned) (*(int *) ((int) p + 0xa4) << 4) >> 16;
                if (v > 3) {
                    p = (char *) ((int) p + 0x9c);
                    func_02056fcc(p, 3, 3, 0x1000, v);
                } else if (v == 3) {
                    p = (char *) ((int) p + 0x9c);
                    func_02056fcc(p, 3, 0, 0x1000, 0);
                }
            }
        }
    }
    switch (state) {
        case 4:
        case 5:
        case 7:
            func_ov068_02270750(self, (short *) (self + 0x23e), flag);
            break;
        case 11:
            func_ov003_02233178((void *) self, (void *) ((short *) (self + 0x242)));
            break;
        case 9:
            func_ov003_022353a4(self, 0, 1);
            func_ov003_02232f78((void *) self, (void *) ((short *) (self + 0x242)));
            break;
        case 3:
            t = *(short *) (self + 0x23a);
            if (func_020e8870(&t, *(short *) (self + 0x240), 0x666) != 0) {
                self[0x251] = 4;
            }
            *(short *) (self + 0x23a) = t;
            break;
        case 0x13:
            if (self[0x24c] != 0) {
                n = *p23e;
                if (n == 0 || *(signed char *) (self + 0x24d) == 0x37) {
                    self[0x251] = 3;
                    *(short *) (self + 0x244) = 0x64;
                    h = *(short *) (self + 0x23a);
                    n = func_ov003_02233c70(8, 1);
                    *(short *) (self + 0x240) = (short) (n + h + 0x8000);
                    *p23e = 0;
                } else if (pos->y > 0 && *(signed char *) (self + 0x24d) == 0x36) {
                    pos->y = pos->y + (FX_MulFunc(FX_Div(0x1000, 0x12000), n << 12) + -10 * (n * n));
                    *p23e = (short) (*p23e + 3);
                    if (pos->y <= 0) {
                        *p23e = 0;
                    }
                }
            } else if (func_ov003_02234984(self) != 0) {
                self[0x251] = 3;
                *(short *) (self + 0x244) = (short) (0x14 * func_020644cc(3));
                h = *(short *) (self + 0x23a);
                n = func_ov003_02233c70(0x10, 1);
                *(short *) (self + 0x240) = (short) (n + h);
            }
            break;
    }
}

void func_ov003_022325d4(char *self)
{
    switch (*(unsigned char *) (self + 0x251)) {
        case 4:
            func_ov068_02271160(self);
            break;
        case 5:
            func_ov068_02271358(self);
            break;
        case 9:
        case 0xb:
            func_ov003_022319bc(self, self + 0x242);
            break;
        case 0x13:
            func_020550e4(self + 0x50, 3);
            *(char *) (self + 0x251) = 4;
            break;
    }
}

int func_ov003_02232598(char *self, int d)
{
    char *m = self + 0x130;
    int a = NNS_G3dMdlGetMdlAlpha(func_0209d088(m), 0);
    if (a > 7) {
        NNS_G3dMdlSetMdlAlpha(func_0209d088(m), 0, a - d);
    } else {
        return 1;
    }
    return 0;
}

int func_ov003_02232414(unsigned char *self)
{
    int ret;
    short *p242;
    Vec3 d;
    int ctx[16];
    Vec3 *pos;
    int speed;
    int k;
    int step;
    int a;
    int n;

    pos = (Vec3 *) (self + 0x204);
    p242 = (short *) (self + 0x242);
    speed = 2;
    ret = 1;
    func_02034270(ctx, pos, 0, ret);
    k = *(signed char *) (self + 0x24d);
    func_ov003_0223597c(&d, *(short *) (self + 0x23a));
    if (ctx[12] != 0) {
        if (func_02034184(ctx, pos->y) != 0) {
            func_ov003_02230f60(self);
            func_ov003_02235454(self);
            ret = 0;
        } else {
            pos->y = pos->y - 0x200;
        }
    } else {
        pos->y = pos->y - 0x200;
    }
    if (func_ov003_02232dd4(self) != 0) {
        self[0x24b] = 0;
        func_0203423c(ctx);
        return 1;
    }
    if ((unsigned char) (signed char) (k - 0x36) <= 1) {
        if (self[0x251] == 5) {
            if (*(short *) (self + 0x23e) > 0 && k != 0x37) {
                speed = 0xc;
            } else {
                speed = 7;
            }
        } else {
            speed = 4;
        }
    }
    if (*(signed char *) (self + 0x24d) == 0x37) {
        step = 0x71c;
    } else {
        step = 0xaaa;
    }
    n = *p242;
    if (n == 0) {
        a = *(short *) (self + 0x23a);
        *(short *) (self + 0x23a) = (short) (a + FX_Div(step, 0x2000));
    } else if (n % 4 == 0) {
        *(short *) (self + 0x23a) = (short) (step + *(short *) (self + 0x23a));
    } else if (n % 2 == 0) {
        *(short *) (self + 0x23a) = (short) (*(short *) (self + 0x23a) - step);
    }
    pos->x = pos->x + FX_MulFunc(d.x, (speed * self[0x257]) << 12);
    pos->z = pos->z + FX_MulFunc(d.z, (speed * self[0x257]) << 12);
    *p242 = (short) (*p242 + 1);
    self[0x24b] = 1;
    func_0203423c(ctx);
    return ret;
}

int func_ov003_02232210(unsigned char *self)
{
    Vec3 *pos;
    short *p242;
    int ret;
    short ang;
    Vec3 d;
    int ctx[16];
    Vec3 *prev;
    int n;
    int m;

    pos = (Vec3 *) (self + 0x204);
    p242 = (short *) (self + 0x242);
    ret = 0;
    func_02034270(ctx, pos, ret, 1);
    prev = (Vec3 *) (self + 0x1d4);
    func_ov003_0223597c(&d, *(short *) (self + 0x23a));
    if (func_020a7278() != 0 || self[0x251] == 0x11) {
        if (ctx[12] != 0) {
            if (func_02034184(ctx, pos->y) != 0) {
                func_ov003_02230f60(self);
                func_ov003_02235454(self);
                ret = 2;
            } else {
                pos->y = pos->y - 0x200;
                ret = 1;
            }
        }
    }
    if (func_ov003_02232dd4(self) != 0) {
        self[0x24b] = 0;
        n = *p242;
        if (n < 2) {
            ang = (short) (*(short *) (self + 0x23a) - 0xaaa);
        } else {
            m = n + 1;
            if (m % 4 == 0) {
                ang = (short) (*(short *) (self + 0x23a) + 0xaaa);
            } else if (m % 2 == 0) {
                ang = (short) (*(short *) (self + 0x23a) - 0xaaa);
            }
        }
        func_ov003_02235834((void *) self, ang, 0xc000);
        func_0203423c(ctx);
        return 0;
    }
    if (*(signed char *) (self + 0x24d) == 0x1e) {
        n = func_020e908c(pos, prev, 0x28, 0x1000, 0x19a);
    } else {
        n = func_020e908c(pos, prev, 8, 0x1000, 0x52);
    }
    if (n == 0) {
        if (func_020a7278() != 0 && func_ov003_02235834((void *) self, *(short *) (self + 0x23a), 0xc000) == 0) {
            prev->x = prev->x + FX_SinCosTable_[(*(unsigned short *) (self + 0x23a) >> 4) * 2];
            prev->z = prev->z + FX_SinCosTable_[(*(unsigned short *) (self + 0x23a) >> 4) * 2 + 1];
            func_0203423c(ctx);
            return 0;
        }
    } else {
        *(short *) (self + 0x23a) = (short) func_0200322c((int *) pos, (int *) prev);
    }
    n = *p242;
    if (n == 0) {
        n = *(short *) (self + 0x23a);
        *(short *) (self + 0x23a) = (short) (n + FX_Div(0x2000, 0x6000));
    } else if (n % 4 == 0) {
        *(short *) (self + 0x23a) = (short) (*(short *) (self + 0x23a) + 0xaaa);
    } else if (n % 2 == 0) {
        *(short *) (self + 0x23a) = (short) (*(short *) (self + 0x23a) - 0xaaa);
    }
    *p242 = (short) (*p242 + 1);
    self[0x24b] = 1;
    func_0203423c(ctx);
    return ret;
}

void func_ov003_022321b8(int *dst, const int *src, int t)
{
    int m = FX_Div(t << 12, 0x40000);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[1] = 0;
    if (src[0] >= 0) {
        if (src[0] > m) {
            dst[0] = m;
        }
    } else if (src[0] < -m) {
        dst[0] = -m;
    }
    if (src[2] >= 0) {
        if (src[2] > m) {
            dst[2] = m;
        }
    } else if (src[2] < -m) {
        dst[2] = -m;
    }
}
