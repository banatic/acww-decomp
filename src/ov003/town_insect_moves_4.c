/* town_insect_moves_4: 5 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0223345c @ 0x0223345c, 0x7c bytes, Thumb
 * func_ov003_022333b0 @ 0x022333b0, 0xac bytes, Thumb
 * func_ov003_02233178 @ 0x02233178, 0x238 bytes, Thumb
 * func_ov003_02232f78 @ 0x02232f78, 0x200 bytes, Thumb
 * func_ov003_02232e88 @ 0x02232e88, 0xf0 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02233178;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02232e88;

extern void func_ov003_022353a4(void *a, int b, int c);
extern void *func_ov003_022356ec(void *a);
extern int func_ov003_022353e0(void *a, void *b);
extern short func_0200322c(void *a, void *b);
extern void *func_0209d088(void *a);
extern void NNS_G3dMdlSetMdlAlpha(void *a, int b, int c);
extern int func_020ea990(void *a, void *b);
extern int func_02034270(int *ctx, Vec3 *p, int a, int b);
extern int func_020341c8(int *ctx, int a);
extern int func_02034184(int *ctx, int y);
extern void func_0203423c(int *ctx);
extern int func_020310c8(int a);
extern int func_02073dd4(UnkStruct_02233178 *p, int a);
extern int func_020a7278(void);
extern void func_020550e4(unsigned char *p, int a);
extern int FX_MulFunc(int a, int b);
extern void func_ov003_0223597c(Vec3 *d, int ang);
extern int func_ov003_02235b54(unsigned char *self, int a, int b);
extern void func_ov003_02230f60(unsigned char *self);
extern int func_ov003_02235454(unsigned char *self);
extern int func_ov003_02235834(unsigned char *self, int ang, int a);
extern UnkStruct_02233178 *data_020ccf94;
extern int func_ov003_02232598(unsigned char *self, int n);
extern int func_ov003_02232dd4(unsigned char *self);
extern int FX_Div(int a, int b);
extern int func_ov003_02232210(void *self);
extern int func_ov003_02232414(void *self);
extern void func_0204f818(int *x, int *y, int *p);
extern int func_02031acc(int x, int y);
extern int func_02090c2c(int a, int *p, int b, void *c);
extern int data_020e25d4;

void func_ov003_022333b0(char *self, short *out);
void func_ov003_02233178(unsigned char *self, short *p);
void func_ov003_02232f78(unsigned char *self, short *p);
void func_ov003_02232e88(char *self, short *pn);

void func_ov003_0223345c(char *self)
{
    char *p = self + 0x242;
    switch (*(unsigned char *) (self + 0x251)) {
        case 4:
        case 0x11:
            func_ov003_022353a4(self, 1, 1);
            func_ov003_02232e88((char *) self, (short *) p);
            break;
        case 5:
        case 0xb:
            func_ov003_02233178((unsigned char *) self, (short *) p);
            break;
        case 9:
            func_ov003_02232f78((unsigned char *) self, (short *) p);
            break;
        case 0x13:
            func_ov003_022333b0((char *) self, (short *) p);
            break;
    }
}

void func_ov003_022333b0(char *self, short *out)
{
    int *v = (int *) (self + 0x204);
    char *o = (char *) func_ov003_022356ec(v);
    if (func_ov003_022353e0(self, v)) {
        if (o != 0) {
            int h = func_0200322c(v, o + 0x5c);
            *(char *) (self + 0x251) = 5;
            NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, 0x1f);
            *(short *) (self + 0x23a) = (short) (h + 0x8000);
            *out = 0;
        }
    } else {
        int t;
        if (o != 0) {
            if (func_020ea990(v, o + 0x5c) < 0x5000) {
                *(char *) (self + 0x252) = 0x3c;
            }
        }
        t = *(unsigned char *) (self + 0x252);
        if (t > 0) {
            func_ov003_022353a4(self, 0, 1);
            *(char *) (self + 0x252) = (char) (t - 1);
        }
    }
}

void func_ov003_02233178(unsigned char *self, short *p)
{
    volatile Vec3 save;
    Vec3 d;
    int ctx[16];
    Vec3 *pos;
    int vy;
    int st;
    int k;
    int n;

    pos = (Vec3 *) (self + 0x204);
    save.x = pos->x;
    save.y = pos->y;
    save.z = pos->z;
    func_02034270(ctx, pos, 0, 1);
    if (*(signed char *) (self + 0x24d) == 0x35) {
        *(short *) (self + 0x23a) = 0;
        func_ov003_0223597c(&d, *(short *) (self + 0x23c));
    } else {
        func_ov003_0223597c(&d, *(short *) (self + 0x23a));
    }
    if (self[0x251] == 5 || func_ov003_02235b54(self, 0x50, 0xe38) == 0) {
        pos->x = pos->x + FX_MulFunc((self[0x257] + 2) << 12, d.x);
        pos->z = pos->z + FX_MulFunc((self[0x257] + 2) << 12, d.z);
    }
    st = self[0x251];
    if (st == 9 || st == 0xb) {
        switch (*(signed char *) (self + 0x24d)) {
            case 0x18:
            case 0x1f:
            case 0x35:
            case 0x36:
            case 0x37:
                n = *p;
                pos->y = pos->y - 0xa * n * n;
                break;
            default:
                n = *p;
                pos->y = pos->y + (0xa0 - 0xb * n) * n;
                break;
        }
    } else {
        n = *p;
        pos->y = pos->y + (0xc8 - 0xb * n) * n;
    }
    if (ctx[12] != 0) {
        vy = ctx[15];
    } else {
        vy = func_020341c8(ctx, 0);
        if (vy > 0x4000) {
            vy = 0;
            pos->x = save.x;
            pos->z = save.z;
        }
    }
    if (pos->y <= vy && *p > 0) {
        if (func_02034184(ctx, pos->y) != 0) {
            func_ov003_02230f60(self);
            func_ov003_02235454(self);
        } else {
            if (self[0x251] == 0xb) {
                k = *(signed char *) (self + 0x24d);
                if (k == 0x1f) {
                    self[0x257] = 4;
                } else if (k == 0x31) {
                    *(short *) (self + 0x232) = 0;
                    if ((unsigned) (*(int *) (self + 0xf4) << 4) >> 16 != 1) {
                        func_020550e4(self + 0x50, 1);
                    }
                }
                self[0x251] = 9;
            } else {
                self[0x251] = 4;
                if (*(signed char *) (self + 0x24d) == 0x31) {
                    func_020550e4(self + 0x50, 1);
                }
                k = *(signed char *) (self + 0x24d);
                if (k == 0x31 || k == 0x1e) {
                    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() != 0) {
                        func_ov003_02235834(self, *(short *) (self + 0x23a), 0xc000);
                    }
                }
            }
            self[0x254] = 0;
            *p = 0;
            pos->y = vy + func_020310c8(0);
            if (*(signed char *) (self + 0x24d) != 0x35) {
                *(short *) (self + 0x238) = 0;
            }
        }
    } else {
        *p = (short) (*p + 2);
    }
    func_0203423c(ctx);
}

void func_ov003_02232f78(unsigned char *self, short *p)
{
    Vec3 *pos;
    int speed;
    int kind;
    short ang;
    int n;
    Vec3 d;
    int ctx[16];

    pos = (Vec3 *) (self + 0x204);
    speed = 2;
    kind = *(signed char *) (self + 0x24d);
    func_02034270(ctx, pos, 0, 1);
    if (func_ov003_02232598(self, 1) != 0) {
        func_ov003_02230f60(self);
    }
    if (func_ov003_02232dd4(self) != 0) {
        func_0203423c(ctx);
        return;
    }
    if (ctx[12] != 0) {
        if (func_02034184(ctx, pos->y) != 0) {
            func_ov003_02230f60(self);
            func_ov003_02235454(self);
        } else {
            pos->y = pos->y - 0x100;
        }
        func_0203423c(ctx);
        return;
    }
    pos->y = pos->y - 0x200;
    if (kind == 0x35) {
        ang = *(short *) (self + 0x23c);
        func_ov003_0223597c(&d, ang);
    } else {
        if ((unsigned char) (signed char) (kind - 0x36) <= 1) {
            speed = 4;
        }
        ang = *(short *) (self + 0x23a);
        func_ov003_0223597c(&d, ang);
    }
    if (kind == 0x1f) {
        n = *p;
        if (n == 0) {
            ang = (short) (ang + FX_Div(0x2000, 0x6000));
        } else if (n % 0x10 == 0) {
            ang = (short) (ang + 0x71c);
        } else if (n % 8 == 0) {
            ang = (short) (ang - 0x71c);
        }
    } else {
        n = *p;
        if (n == 0) {
            ang = (short) (ang + FX_Div(0x2000, 0x6000));
        } else if (n % 4 == 0) {
            ang = (short) (ang + 0xaaa);
        } else if (n % 2 == 0) {
            ang = (short) (ang - 0xaaa);
        }
    }
    if (kind == 0x35) {
        *(short *) (self + 0x23c) = ang;
        *(short *) (self + 0x23a) = 0;
    } else {
        *(short *) (self + 0x23a) = ang;
    }
    if (kind == 0x1a) {
        pos->z = pos->z + FX_MulFunc(FX_MulFunc(self[0x257] << 12, d.z), 0x400);
        pos->x = pos->x + FX_MulFunc(FX_MulFunc(self[0x257] << 12, d.x), 0x400);
    } else {
        pos->x = pos->x + FX_MulFunc(d.x, (speed * self[0x257]) << 12);
        pos->z = pos->z + FX_MulFunc(d.z, (speed * self[0x257]) << 12);
    }
    *p = (short) (*p + 1);
    func_0203423c(ctx);
}

void func_ov003_02232e88(char *self, short *pn)
{
    short t;
    int x;
    int y;
    short n;
    int k;

    t = *(short *) (self + 0x232);
    if (func_02073dd4((UnkStruct_02233178 *) ((*(UnkStruct_02232e88 * *) &data_020ccf94)), (*(UnkStruct_02232e88 * *) &data_020ccf94)->unk_64) != 0) {
        if (func_ov003_02232210(self) != 0) {
            return;
        }
    } else if (func_ov003_02232414(self) == 0) {
        return;
    }
    *(short *) (self + 0x232) = t - 1;
    if (t == 5) {
        func_0204f818(&x, &y, (int *) (self + 0x204));
        if (func_02031acc(x, y) == 0 && func_02073dd4((UnkStruct_02233178 *) ((*(UnkStruct_02232e88 * *) &data_020ccf94)), (*(UnkStruct_02232e88 * *) &data_020ccf94)->unk_64) == 0) {
            func_02090c2c(0x80, (int *) (self + 0x204), 0, &data_020e25d4);
            return;
        }
        *(u8 *) (self + 0x251) = 9;
    } else if (t <= 0) {
        n = *pn;
        if (n < 2) {
            *(short *) (self + 0x23a) = *(short *) (self + 0x23a) - 0xaaa;
        } else {
            k = n + 1;
            if (k % 4 == 0) {
                *(short *) (self + 0x23a) = *(short *) (self + 0x23a) + 0xaaa;
            } else if (k % 2 == 0) {
                *(short *) (self + 0x23a) = *(short *) (self + 0x23a) - 0xaaa;
            }
        }
        *pn = 0;
        func_ov003_02230f60((unsigned char *) self);
    }
}
