/* town_insect_moves_6: 9 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0223482c @ 0x0223482c, 0x14 bytes, Thumb
 * func_ov003_02234600 @ 0x02234600, 0x22c bytes, Thumb
 * func_ov003_022344c8 @ 0x022344c8, 0x138 bytes, Thumb
 * func_ov003_022343a8 @ 0x022343a8, 0x120 bytes, Thumb
 * func_ov003_022342f8 @ 0x022342f8, 0xb0 bytes, Thumb
 * func_ov003_02234264 @ 0x02234264, 0x94 bytes, Thumb
 * func_ov003_0223418c @ 0x0223418c, 0xd8 bytes, Thumb
 * func_ov003_02234030 @ 0x02234030, 0x15c bytes, Thumb
 * func_ov003_02233f48 @ 0x02233f48, 0xe8 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_02234600;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02234600_2;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_022344c8;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_022343a8;

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02234030;

extern int func_020644cc(int n);
extern void func_020550e4(unsigned char *p, int a);
extern void func_ov003_02234cc4(unsigned char *self);
extern int func_ov003_02234d70(unsigned char *self);
extern void func_ov003_02235934(unsigned char *self, int a);
extern void func_ov068_022717e0(unsigned char *self);
extern int func_ov003_02234984(unsigned char *self);
extern int func_ov068_02271b30(unsigned char *self);
extern UnkStruct_02234600_2 *data_020ccf94;
extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);
extern int func_ov003_02233c70(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_020e908c(int *p, int *d, int v, int w, int a);
extern int func_0200322c(int *p, int *d);
extern void func_0204f818(int *x, int *y, int *p);
extern int func_020e8bb0(int *p, int a, int v, int b, int c);
extern int FX_Div(int a, int b);
extern int func_ov003_02235b54(void *a, int b, int c);
extern void func_ov003_0223597c(int *v, int a);
extern int func_ov003_02232598(void *a, int b);
extern void func_ov003_02230f60(void *a);
extern int func_ov003_02235834(unsigned char *self, int ang, int k);
extern int func_020e8870(short *p, int ang, int step);
extern void *func_020961a8(int id);
extern int func_020ea990(int *a, int *b);

void func_ov003_022344c8(char *self, short *pn);
void func_ov003_022343a8(char *self);
void func_ov003_022342f8(char *self, short *out);
void func_ov003_02234264(char *self);
short func_ov003_0223418c(short a, int b);
int func_ov003_02234030(unsigned char *self, int b);

int func_ov003_0223482c(int x)
{
    if (x == 2) {
        return 0xf;
    }
    if (x == 3) {
        return 0xf;
    }
    return 0x3f;
}

void func_ov003_02234600(unsigned char *self)
{
    short *p242;
    int n;
    int flag;
    int r;
    UnkStruct_02234600 *src;
    UnkStruct_02234600 *dst;
    int x;

    p242 = (short *) (self + 0x242);
    n = (*(int *) (self + 0x21c) & 0xf0) >> 4;
    flag = 0;
    if (n > 0 && self[0x251] == 0x13) {
        if (self[0x24f] % 0x14 == 0) {
            r = func_020644cc(100);
            if ((unsigned) (*(int *) (self + 0xf4) << 4) >> 16 == 0 && r > 0x5c) {
                func_020550e4(self + 0x50, 2);
            } else if (r > 0x32) {
                func_020550e4(self + 0x50, 0);
            }
        } else if ((unsigned) (*(int *) (self + 0xf4) << 4) >> 16 != 0) {
            func_ov003_02234cc4(self);
        }
    } else {
        func_ov003_02234cc4(self);
    }
    if (self[0x251] != 0xb && self[0x251] != 9) {
        func_ov003_02234d70(self);
    }
    func_ov003_02235934(self, 5);
    switch (self[0x251]) {
        case 15:
            flag = 1;
        case 3:
            if (func_ov003_02234030(self, 0) != 0 && flag != 0) {
                self[0x251] = 0x12;
            }
            break;
        case 4:
            if (n > 0) {
                func_ov068_022717e0(self);
            } else {
                func_ov003_022343a8((char *) self);
            }
            func_ov003_02234264((char *) self);
            *p242 = 0;
            break;
        case 12:
        case 13:
        case 14:
            if (*(signed char *) (self + 0x24d) == 0x17) {
                *p242 = 0x64;
            }
            func_ov003_022344c8((char *) self, p242);
            break;
        case 7:
            self[0x251] = 3;
            src = (UnkStruct_02234600 *) (self + 0x204);
            dst = (UnkStruct_02234600 *) (self + 0x1d4);
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            *(int *) (self + 0x21c) = *(int *) (self + 0x21c) | 0xf00;
            break;
        case 9:
        case 11:
            func_ov003_022342f8((char *) self, p242);
            break;
        default:
            if (n > 0) {
                *p242 = (short) (*p242 + 1);
                if ((*p242 > 0x28 && *p242 % 0xa == 0 && func_020644cc(100) > 0x50) || *p242 > 0xc8) {
                    *(int *) (self + 0x21c) = *(int *) (self + 0x21c) & 0xff0f;
                    *p242 = 0;
                    self[0x251] = 0xc;
                    *(short *) (self + 0x244) = 0x64;
                }
            } else {
                x = func_ov003_02234984(self);
                *p242 = 0;
                if (self[0x24a] == 0 && x != 0 && func_02073dd4((void *) data_020ccf94, data_020ccf94->unk_64) == 0) {
                    func_ov068_02271b30(self);
                }
                if (self[0x251] == 0x12) {
                    self[0x251] = 4;
                } else {
                    self[0x24a] = 0;
                    self[0x251] = 0xc;
                    *(int *) (self + 0x21c) = *(int *) (self + 0x21c) & 0xfff0;
                }
            }
            break;
    }
}

void func_ov003_022344c8(char *self, short *pn)
{
    int *p;
    int r;
    short n;
    u8 s;
    int a;
    int base;
    int t;
    int *s2;
    int *d2;

    p = (int *) (self + 0x204);
    r = func_020644cc(0x64);
    if (func_02073dd4((*(UnkStruct_022344c8 **) &data_020ccf94), (*(UnkStruct_022344c8 **) &data_020ccf94)->unk_64) != 0 &&
        func_020a7278() == 0) {
        d2 = (int *) (self + 0x1d4);
        if (d2[0] != p[0] || d2[2] != p[2]) {
            *(u8 *) (self + 0x251) = 4;
            *pn = 0;
            return;
        }
    } else {
        n = *pn;
        if ((n == 0 && r > 0x5f) || (n == 0xa && r > 0x50) || ((n == 0x14 || n == 0x1e) && r > 0x32) || n >= 0x28) {
            s = *(u8 *) (self + 0x251);
            if (s != 0xd && s != 0xe) {
                a = *(s8 *) (self + 0x24d) == 0x17 ? 5 : 0xd;
                base = *(short *) (self + 0x23a);
                t = func_ov003_02233c70((u8) a, 1);
                *(short *) (self + 0x240) = t + base;
                s2 = (int *) (self + 0x204);
                d2 = (int *) (self + 0x1d4);
                d2[0] = s2[0];
                d2[1] = s2[1];
                d2[2] = s2[2];
            }
            *(u8 *) (self + 0x251) = 3;
            *(int *) (self + 0x21c) |= 0xf00;
            *pn = 0;
            return;
        }
    }
    if (*pn % 0xa < 5) {
        if (p[1] < *(int *) (self + 0x228) + 0x800) {
            p[1] = p[1] + 0x80;
        }
    } else {
        if (p[1] > *(int *) (self + 0x228) - 0x800) {
            p[1] = p[1] - 0x80;
        }
    }
    *pn = *pn + 1;
}

void func_ov003_022343a8(char *self)
{
    int v;
    int *d;
    int *p;
    s8 k;
    int a;
    int x;
    int y;

    d = (int *) (self + 0x1d4);
    p = (int *) (self + 0x204);
    v = 0x1000 / *(u8 *) (self + 0x257);
    k = *(s8 *) (self + 0x24d);
    switch (k) {
        case 0x15:
            a = 0xcd;
            break;
        case 0x16:
            a = 0x266;
            break;
        default:
            a = 0x385;
            break;
    }
    if (*(u8 *) (self + 0x24a) != 0) {
        a = FX_MulFunc(a, 0x2000);
    }
    if (func_020e908c(p, d, v, 0x1000, a) == 0) {
        *(u8 *) (self + 0x251) = 0x13;
    } else {
        *(short *) (self + 0x23a) = func_0200322c(p, d);
        if (func_02073dd4((*(UnkStruct_022343a8 **) &data_020ccf94), (*(UnkStruct_022343a8 **) &data_020ccf94)->unk_64) != 0 &&
            func_020a7278() == 0) {
            func_0204f818(&x, &y, p);
            if (x < 0x10 || x > 0x4f || y < 0x10) {
                *(u8 *) (self + 0x251) = 0x13;
            }
        }
    }
    if (*(u8 *) (self + 0x24c) != 0) {
        func_020e8bb0(p + 1, *(int *) (self + 0x228), v, 0x1ec, 0xcd);
    } else if (func_020e8bb0(p + 1, *(int *) (self + 0x228) - 0x1000, v, 0x333, 0xcd) == 0) {
        *(u8 *) (self + 0x24c) = 1;
    }
}

void func_ov003_022342f8(char *self, short *out)
{
    int t;
    int v[3];
    int *p;
    int m;

    p = (int *) (self + 0x204);
    if (*(unsigned char *) (self + 0x251) == 0xb) {
        if (func_ov003_02235b54(self, 0x50, 0xe38) == 0) {
            func_ov003_0223597c(v, *(short *) (self + 0x23a));
            p[0] += FX_MulFunc(v[0], 0x10000);
            p[2] += FX_MulFunc(v[2], 0x10000);
        }
    }
    t = *out << 12;
    m = FX_MulFunc(0x44000, t);
    p[1] += (m >> 12) + (FX_Div(FX_MulFunc(t, t), 0x2000) >> 12);
    *out = *out + 1;
    if (func_ov003_02232598(self, 1) != 0) {
        func_ov003_02230f60(self);
    }
}

void func_ov003_02234264(char *self)
{
    int r = func_ov003_02235b54(self, 0x50, 0xe38);
    if (r != 0) {
        int *d;
        int *s;
        if (*(unsigned char *) (self + 0x24a) != 0) {
            *(char *) (self + 0x251) = 0xf;
            *(int *) (self + 0x21c) |= 0xf00;
        } else {
            *(char *) (self + 0x251) = 0xd;
        }
        *(short *) (self + 0x240) = func_ov003_0223418c(*(short *) (self + 0x23a), r);
        *(int *) (self + 0x21c) += 1;
        *(short *) (self + 0x242) = 0;
        s = (int *) (self + 0x204);
        d = (int *) (self + 0x1d4);
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
    }
}

short func_ov003_0223418c(short a, int b)
{
    short a0;
    int t;

    a0 = a;
    if (b == 3) {
        t = func_020644cc(0x64);
        a = a + 0x8000;
        if (t < 5) {
            a = a + 0x2aaa;
        } else if (t < 0xa) {
            a = a - 0x2aaa;
        }
    } else if ((b == 1 && (a < -0x4000 || (a >= 0 && a < 0x4000))) || (b == 2 && (a > 0x4000 || (a <= 0 && a > -0x4000)))) {
        a = -a;
    } else if (a >= 0) {
        a = 0x8000 - a;
    } else {
        a = -0x8000 - a;
    }
    if (func_020644cc(0x64) < 0xa) {
        if (a >= 0) {
            a = a + 0xaaa;
        } else {
            a = a - 0xaaa;
        }
    }
    if (a == a0) {
        if (a >= 0) {
            a = a + 0xaaa;
        } else {
            a = a - 0xaaa;
        }
    }
    return a;
}

int func_ov003_02234030(unsigned char *self, int b)
{
    int ret;
    short ang;
    int f;
    unsigned char k;

    ret = 0;
    ang = *(short *) (self + 0x23a);
    if (self[0x251] != 0xb) {
        if (func_020a7278() == 0 && func_02073dd4((void *) ((*(UnkStruct_02234030 **) &data_020ccf94)),
                                                  (*(UnkStruct_02234030 **) &data_020ccf94)->unk_64) != 0) {
            if (*(int *) (self + 0x204) != *(int *) (self + 0x1d4) && *(int *) (self + 0x20c) != *(int *) (self + 0x1dc)) {
                self[0x251] = 4;
                self[0x24c] = (unsigned char) b;
            }
        } else {
            int *p = (int *) (self + 0x204);
            int *q = (int *) (self + 0x1d4);
            f = *(int *) (self + 0x21c);
            if ((p[0] == q[0] && p[2] == q[2]) || (f & 0xf00) != 0) {
                k = self[0x259];
                k = (unsigned char) (k + func_020644cc(3));
                if (self[0x24a] != 0) {
                    k = (unsigned char) (k + (unsigned char) (func_020644cc(2) + 2));
                }
                if (func_ov003_02235834(self, *(short *) (self + 0x240), k << 12) != 0) {
                    *(short *) (self + 0x240) = (short) func_0200322c((int *) (self + 0x204), (int *) (self + 0x1d4));
                    f = f & 0xf0ff;
                    *(int *) (self + 0x21c) = f;
                } else {
                    f = f & 0xf0ff;
                    *(int *) (self + 0x21c) = f;
                }
            }
            if (func_020e8870(&ang, *(short *) (self + 0x240), 0xe38) != 0) {
                self[0x251] = 4;
                self[0x24c] = (unsigned char) b;
                ret = 1;
            }
            *(short *) (self + 0x23a) = ang;
        }
    } else {
        func_ov003_02235834(self, *(short *) (self + 0x23a), (unsigned char) (self[0x259] * 2) << 12);
        self[0x24c] = (unsigned char) b;
    }
    return ret;
}

void func_ov003_02233f48(char *self, int *out, int *pv, u8 *pflag, u8 a5, u8 a6)
{
    void *o;
    short v;
    int lim;
    int w;
    int *s;
    int d;

    o = func_020961a8(a5);
    if (o != 0) {
        v = *(u8 *) (self + 0x254);
        lim = *(int *) (self + 0x224);
        w = *(int *) ((char *) o + 0x98);
        s = (int *) ((char *) o + 0x5c);
        out[0] = s[0];
        out[1] = s[1];
        out[2] = s[2];
        *pv = func_020ea990(out, (int *) (self + 0x204));
        if (a6 != 0) {
            *pflag = 0;
            d = *pv;
            if (d < 0x2000) {
                v = v + 0x19;
            } else if (d > lim || w == 0) {
                *pflag = 1;
            } else if (w <= 0x3e8) {
                v = v + 1;
            } else if (w <= 0x44c) {
                v = v + 3;
            } else if (w <= 0x490) {
                v = v + 5;
            } else if (w == 0x491) {
                v = v + 8;
            } else {
                v = v + 0xf;
            }
            if (v > 0xfe) {
                v = 0xfe;
            }
            *(u8 *) (self + 0x254) = (u8) v;
        }
    }
}
