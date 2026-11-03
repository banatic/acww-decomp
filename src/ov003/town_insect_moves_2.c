/* town_insect_moves_2: 10 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02231e24 @ 0x02231e24, 0xfc bytes, Thumb
 * func_ov003_02231d1c @ 0x02231d1c, 0x108 bytes, Thumb
 * func_ov003_02231c80 @ 0x02231c80, 0x9c bytes, Thumb
 * func_ov003_02231be4 @ 0x02231be4, 0x9c bytes, Thumb
 * func_ov003_02231af0 @ 0x02231af0, 0xf4 bytes, Thumb
 * func_ov003_022319bc @ 0x022319bc, 0x134 bytes, Thumb
 * func_ov003_0223189c @ 0x0223189c, 0x120 bytes, Thumb
 * func_ov003_02231818 @ 0x02231818, 0x84 bytes, Thumb
 * func_ov003_022316e0 @ 0x022316e0, 0x138 bytes, Thumb
 * func_ov003_022314fc @ 0x022314fc, 0x1e4 bytes, Thumb
 */

#include "types.h"

extern void func_ov003_02232f78(void *self, short *p);
extern void func_ov003_02233178(void *self, short *p);
extern int func_ov003_02232598(void *self, int a);
extern void func_ov003_02230f60(void *self);
extern void func_ov003_022353a4(void *self, int a, int b);
extern int func_020644cc(int n);
extern void func_02056fcc(void *p, int a, int b, int c, int d);
extern int FX_Div(int a, int b);
extern int FX_MulFunc(int a, int b);
extern void func_ov003_0223597c(int *v, int a);
extern int func_ov003_02235b54(void *self, int a, int b);
extern void VEC_Add(int *a, int *b, int *c);
extern void func_020550e4(void *p, int a);
extern void func_ov003_02234cc4(void *self);
extern int func_ov003_02233e4c(void *a, void *b);
extern void *func_0209d088(void *a);
extern void NNS_G3dMdlSetMdlAlpha(void *a, int b, int c);
extern void *func_020961a8(int n);
extern int func_0200322c(void *a, void *b);
extern void func_ov003_02231104(void *self);
extern void func_ov003_0223126c(void *self, short *t);
extern void func_ov003_02230e18(void *self, short *t);

void func_ov003_02231d1c(char *self, volatile short *pn);
void func_ov003_02231c80(char *self, short *ph);
void func_ov003_02231be4(char *self, short *ph);
void func_ov003_02231af0(char *self, volatile short *pn);
void func_ov003_022319bc(char *self, short *pn);
void func_ov003_0223189c(char *self, short *pn);
void func_ov003_02231818(char *self, short *out);
void func_ov003_022316e0(char *self, short *pn);

void func_ov003_02231e24(char *self)
{
    short *p;
    u8 s;

    p = (short *) (self + 0x242);
    s = *(u8 *) (self + 0x251);
    if (s != 0xb && s != 9 && s != 7) {
        if (*(signed char *) (self + 0x24d) == 0x1f) {
            func_ov003_02231818((char *) self, p);
        } else {
            func_ov003_022316e0((char *) self, p);
            *(char *) (self + 0x24a) = 0;
        }
    }
    switch (s) {
        case 3:
            func_ov003_02231af0((char *) self, (volatile short *) p);
            break;
        case 2:
            func_ov003_02231c80((char *) self, p);
            break;
        case 1:
            func_ov003_02231be4((char *) self, p);
            break;
        case 9:
            func_ov003_02232f78(self, p);
            *p = *p + 1;
            break;
        case 0xb:
            if (*(signed char *) (self + 0x24d) != 0x1f) {
                func_ov003_022319bc((char *) self, p);
            } else {
                func_ov003_02233178(self, p);
            }
            break;
        case 7:
            *(char *) (self + 0x24a) = 1;
            func_ov003_0223189c((char *) self, p);
            break;
        case 8:
            if (func_ov003_02232598(self, 2) != 0) {
                func_ov003_02230f60(self);
            }
            break;
        case 0x13:
            func_ov003_02231d1c((char *) self, (volatile short *) p);
            break;
    }
}

void func_ov003_02231d1c(char *self, volatile short *pn)
{
    signed char k;
    u8 f;
    u8 s;
    u8 rnd;
    u32 v;

    k = *(signed char *) (self + 0x24d);
    if ((u8) (signed char) (k - 0x10) <= 4) {
        f = *(u8 *) (self + 0x246);
        if (f != 0 && *(u8 *) (self + 0x254) < 0xa) {
            s = *(u8 *) (self + 0x252);
            if (s == 0 && f != 0) {
                func_ov003_022353a4(self, 0, 1);
            } else {
                *(u8 *) (self + 0x252) = s - 1;
            }
        } else {
            *(u8 *) (self + 0x252) = 0x3c;
        }
    } else {
        rnd = (u8) func_020644cc(0x64);
        if (*(signed char *) (self + 0x24d) == 9) {
            v = ((u32) * (int *) (self + 0xf4) << 4) >> 16;
            if (v == 0xd || v < 9) {
                func_02056fcc(self + 0xec, 9, 1, 0, 9);
            }
            if (*pn > 0x50) {
                if (rnd > 0x5c && v < 0xa) {
                    func_02056fcc(self + 0xec, 0xe, 1, 0x1000, 9);
                }
                if (*pn > 0xa0) {
                    *pn = 0;
                }
            }
            *pn = *pn + 1;
        } else if (rnd > 0x46) {
            *pn = *pn + 1;
            if (*pn % 0x14 == 0) {
                if (rnd < 0x55) {
                    *(u8 *) (self + 0x251) = 3;
                } else {
                    *(u8 *) (self + 0x251) = 2;
                }
                *pn = 0;
            }
        }
    }
}

void func_ov003_02231c80(char *self, short *ph)
{
    short a = *(short *) (self + 0x23a);
    int lim = *(int *) (self + 0x228) + 0x400;
    int *v = (int *) (self + 0x204);
    short t = *ph;
    if (t >= 8) {
        if (func_020644cc(0x64) > 0x46) {
            *(char *) (self + 0x251) = 1;
        }
        *ph = 0;
    } else {
        if (t >= 2 && t < 6) {
            a = (short) (a - 0x16b);
            *(short *) (self + 0x238) = (short) (*(short *) (self + 0x238) - 0xb6);
        } else {
            a = (short) (a + 0x16b);
            *(short *) (self + 0x238) = (short) (*(short *) (self + 0x238) + 0xb6);
        }
        v[1] += 0x20;
        *ph = (short) (*ph + 1);
        if (v[1] > lim) {
            v[1] = lim;
        }
    }
    *(short *) (self + 0x23a) = a;
}

void func_ov003_02231be4(char *self, short *ph)
{
    short a = *(short *) (self + 0x23a);
    int lim = *(int *) (self + 0x228) - 0x100;
    int *v = (int *) (self + 0x204);
    short t = *ph;
    if (t >= 8) {
        if (func_020644cc(0x64) > 0x46) {
            *(char *) (self + 0x251) = 0x13;
        }
        *ph = 0;
    } else {
        if (t >= 2 && t < 6) {
            a = (short) (a - 0x16b);
            *(short *) (self + 0x238) = (short) (*(short *) (self + 0x238) - 0xb6);
        } else {
            a = (short) (a + 0x16b);
            *(short *) (self + 0x238) = (short) (*(short *) (self + 0x238) + 0xb6);
        }
        v[1] -= 0x20;
        *ph = (short) (*ph + 1);
        if (v[1] < lim) {
            v[1] = lim;
        }
    }
    *(short *) (self + 0x23a) = a;
}

void func_ov003_02231af0(char *self, volatile short *pn)
{
    short h;
    short n;

    h = *(short *) (self + 0x23a);
    n = *pn;
    if (n == 0) {
        if (func_020644cc(0x64) < 0x32) {
            *pn = 1;
        } else {
            *pn = -1;
        }
    } else if ((n > 0 && n <= 6) || (n > 0x12 && n <= 0x18) || (n < -6 && n >= -0x12)) {
        if (n > 0) {
            *pn = *pn + 1;
            *(short *) (self + 0x238) = *(short *) (self + 0x238) + 0xb6;
        } else {
            *pn = *pn - 1;
            *(short *) (self + 0x238) = *(short *) (self + 0x238) - 0xb6;
        }
        h = h + 0x16b;
    } else if ((n > 6 && n <= 0x12) || (n < 0 && n >= -6) || (n < -0x12 && n >= -0x18)) {
        if (n > 0) {
            *pn = *pn + 1;
            *(short *) (self + 0x238) = *(short *) (self + 0x238) - 0xb6;
        } else {
            *pn = *pn - 1;
            *(short *) (self + 0x238) = *(short *) (self + 0x238) + 0xb6;
        }
        h = h - 0x16b;
    } else {
        *pn = 0;
        *(u8 *) (self + 0x251) = 0x13;
    }
    *(short *) (self + 0x23a) = h;
}

void func_ov003_022319bc(char *self, short *pn)
{

    s8 k;
    int t;
    int *p;
    int v[3];
    int fld;
    char *o;

    p = (int *) (self + 0x204);
    fld = ((u32) * (int *) (self + 0xf4) << 4) >> 16;
    k = *(s8 *) (self + 0x24d);
    t = FX_Div(*pn << 12, 0x4000);
    o = self + 0x50;
    func_ov003_0223597c(v, *(short *) (self + 0x23a));
    if (*pn == 0) {
        func_ov003_022353a4(self, 1, 0);
    }
    v[1] = FX_MulFunc(FX_MulFunc(0x100, t), t);
    if (func_ov003_02235b54(self, 0x50, 0xe38) == 0) {
        v[0] = v[0] << 4;
        v[2] = v[2] << 4;
    }
    VEC_Add(p, v, p);
    *pn = *pn + 1;
    if (k == 0x14) {
        if (((u32) * (int *) (o + 0xa0) << 4) >> 16 < 0x18) {
            func_02056fcc(o + 0x9c, 0x1a, 0, 0x1000, 0x18);
        } else if (((u32) * (int *) (o + 0xa4) << 4) >> 16 < 0x18) {
            *(int *) (o + 0xa4) = 0x18000;
        }
    } else if (*(s8 *) (self + 0x24d) == 9) {
        if (*(u8 *) (o + 0xb0) != 0) {
            func_02056fcc(o + 0x9c, 9, 0, 0x1000, 0);
        }
    } else {
        func_020550e4(o, (u16) (fld == 1 ? 2 : 1));
    }
    if (func_ov003_02232598(self, 1) != 0) {
        func_ov003_02230f60(self);
    }
}

void func_ov003_0223189c(char *self, short *pn)
{
    int *p;
    s8 k;
    int t;

    p = (int *) (self + 0x204);
    k = *(s8 *) (self + 0x24d);
    if (k != 0x10 && k != 0x11 && k != 0x12 && k != 0x13) {
        func_ov003_022353a4(self, 0, 1);
    }
    if (*(short *) (self + 0x23a) >= 0) {
        p[0] = p[0] + 0x200;
    } else {
        p[0] = p[0] - 0x200;
    }
    if (func_ov003_02232598(self, 1) != 0) {
        func_ov003_02230f60(self);
        return;
    }
    t = FX_Div(*pn << 12, 0x4000);
    p[1] = p[1] + FX_MulFunc(FX_MulFunc(0x100, t), t);
    *pn = *pn + 1;
    if (*(u8 *) (self + 0x251) == 0xb && (*(short *) (self + 0x23a) == 0x6001 || *(short *) (self + 0x23a) == -0x6001)) {
        p[2] = p[2] - 0x100;
    } else {
        p[2] = p[2] + 0x100;
    }
    if (k == 0x14) {
        if (((u32) * (int *) (self + 0xf0) << 4) >> 16 < 0x18) {
            func_02056fcc(self + 0xec, 0x1a, 0, 0x1000, 0x18);
        } else if (((u32) * (int *) (self + 0xf4) << 4) >> 16 < 0x18) {
            *(int *) (self + 0xf4) = 0x18000;
        }
    } else {
        func_ov003_02234cc4(self);
    }
}

void func_ov003_02231818(char *self, short *out)
{
    int t[4];
    if (*(unsigned char *) (self + 0x254) == 0xfe) {
        *(char *) (self + 0x251) = 8;
    } else {
        func_ov003_02233e4c(self, t);
        if (t[0] != 0) {
            int a = (short) (0x1f * (*(unsigned char *) (self + 0x255) - *(unsigned char *) (self + 0x254)) /
                             *(unsigned char *) (self + 0x255));
            if (a <= 0) {
                func_ov003_02230f60(self);
                *(char *) (self + 0x24a) = 1;
                *out = 0;
            } else {
                if (a > 0x1f) {
                    a = 0x1f;
                }
                NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x130), 0, a);
            }
        }
    }
}

void func_ov003_022316e0(char *self, short *pn)
{
    int v[4];
    int *p;
    u8 c;
    int lim;
    u8 *q;
    int h;

    p = (int *) (self + 0x204);
    c = *(u8 *) (self + 0x254);
    func_ov003_02233e4c(self, (void *) v);
    if (v[0] == 0) {
        return;
    }
    if (*(u8 *) (self + 0x24a) != 0) {
        return;
    }
    lim = *(u8 *) (self + 0x255);
    if (c >= lim) {
        *(short *) (self + 0x23a) = v[0] > p[0] ? -0x6aac : 0x6aac;
        *(short *) (self + 0x238) = 0xd55;
        *(u8 *) (self + 0x251) = 7;
        *(u8 *) (self + 0x24a) = 1;
        func_020550e4(self + 0x50, 1);
        *pn = 0;
        func_ov003_022353a4(self, 1, 0);
        if (*(s8 *) (self + 0x24d) == 9) {
            func_02056fcc(self + 0xec, 9, 0, 0x1000, 0);
        }
    } else if (*(s8 *) (self + 0x24d) == 0x14) {
        if (c * 2 >= lim || *(u8 *) (self + 0x252) != 0) {
            if (((u32) * (int *) (self + 0xf4) << 4) >> 16 == 0) {
                func_02056fcc(self + 0xec, 4, 1, 0x1000, 0);
                *(u8 *) (self + 0x252) = 0x3c;
            } else {
                if (*(u8 *) (self + 0x252) != 0) {
                    *(u8 *) (self + 0x252) = *(u8 *) (self + 0x252) - 1;
                }
            }
        } else {
            h = *(int *) (self + 0xf4) >> 12;
            if ((u16) h != 0 || ((u32) * (int *) (self + 0xf0) << 4) >> 16 != 0) {
                func_02056fcc(self + 0xec, 0, 3, 0x1000, (u16) h);
            }
        }
    }
}

void func_ov003_022314fc(char *self)
{
    short *t = (short *) (self + 0x242);
    void *p;

    if ((u8) (s8) (*(s8 *) (self + 0x24d) - 0xe) <= 1 && (u16) (*(int *) (self + 0xf4) >> 12) != 0 &&
        (*(u8 *) (self + 0x251) == 4 || *(u8 *) (self + 0x251) == 0x13)) {
        p = func_020961a8(4);
        if (p != 0) {
            *(u16 *) (self + 0x23a) = (u16) func_0200322c(self + 0x204, (char *) p + 0x5c);
        }
        *(u8 *) (self + 0x251) = 0x13;
    }

    switch (*(u8 *) (self + 0x251)) {
        case 4:
            func_ov003_02231104(self);
            if (*(s8 *) (self + 0x24d) == 0x1a) {
                if (*t > 0x140 || (*t % 0x14 == 0 && func_020644cc(0x64) > 0x5a && *t > 0xa0)) {
                    *(u8 *) (self + 0x251) = 0x13;
                    *t = 0;
                }
            } else {
                if (*t > 0xa0 || (*t % 0x14 == 0 && func_020644cc(0x64) > 0x5a && *t > 0x50)) {
                    *(u8 *) (self + 0x251) = 0x13;
                    *t = 0;
                }
            }
            func_ov003_0223126c(self, t);
            break;
        case 7:
            *(u8 *) (self + 0x251) = 9;
            *(u16 *) (self + 0x23a) = (u16) * (short *) (self + 0x240);
            *t = 0;
            // falls through
        case 9:
            func_ov003_02230e18(self, t);
            break;
        case 0xb:
            if (*(s8 *) (self + 0x24d) == 0x1a) {
                func_ov003_02233178(self, t);
            } else {
                func_ov003_02230e18(self, t);
            }
            break;
        case 0x13:
            if (*(s8 *) (self + 0x24d) == 0x1a) {
                if ((u16) (*(int *) (self + 0xf4) >> 12) == 2) {
                    if (*t > 0xa0 || (*t % 0x14 == 0 && func_020644cc(0x64) > 0x55 && *t >= 0x28)) {
                        *t = 0;
                        *(u8 *) (self + 0x251) = 4;
                    }
                }
            } else {
                if (*t > 0x38 || (*t % 5 == 0 && func_020644cc(0x64) > 0x55 && *t > 0)) {
                    *(u8 *) (self + 0x251) = 4;
                    *t = 0;
                }
            }
            func_ov003_0223126c(self, t);
            break;
    }
    *t = *t + 1;
}
