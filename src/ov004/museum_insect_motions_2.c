/* museum_insect_motions_2: 11 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02241b5c @ 0x02241b5c, 0x4c bytes, Thumb
 * func_ov004_022419f8 @ 0x022419f8, 0x164 bytes, Thumb
 * func_ov004_022419c4 @ 0x022419c4, 0x34 bytes, Thumb
 * func_ov004_0224193c @ 0x0224193c, 0x88 bytes, Thumb
 * func_ov004_02241894 @ 0x02241894, 0xa8 bytes, Thumb
 * func_ov004_022417f8 @ 0x022417f8, 0x9c bytes, Thumb
 * func_ov004_0224173c @ 0x0224173c, 0xbc bytes, Thumb
 * func_ov004_02241680 @ 0x02241680, 0xbc bytes, Thumb
 * func_ov004_02241588 @ 0x02241588, 0xf8 bytes, Thumb
 * func_ov004_022414a8 @ 0x022414a8, 0xe0 bytes, Thumb
 * func_ov004_02241350 @ 0x02241350, 0x158 bytes, Thumb
 */

#include "types.h"

typedef struct {
    long x, y, z;
} UnkStruct_02241b5c;

extern long FX_MulFunc(long, long);
extern int func_0209d088(void *);
extern void NNS_G3dMdlSetMdlAlpha(int, int, int);
extern int func_020644cc(int);
extern char *func_020961a8(int);
extern int func_020ea990(void *, void *);
extern u8 data_ov004_02259a24;
extern void func_02056fcc(void *, int, int, int, int);
extern int func_ov004_02244764(void *self);
extern int func_ov004_02244be0(void *self, int a);
extern void func_ov004_022411a4(void *, short *);
extern void func_ov004_02241084(void *);

int func_ov004_022419c4(char *self);
int func_ov004_0224193c(void *self, short *state);
void func_ov004_022417f8(char *self);
void func_ov004_0224173c(char *self, short *pc);
void func_ov004_02241680(char *self, short *pc);
void func_ov004_02241588(char *self, short *pc);

void func_ov004_02241b5c(UnkStruct_02241b5c *dst, UnkStruct_02241b5c *src, long s)
{
    long lim = FX_MulFunc(s << 12, 0x40);
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->y = 0;
    if (src->x > lim) {
        dst->x = lim;
    } else if (src->x < -lim) {
        dst->x = -lim;
    }
    if (src->z > lim) {
        dst->z = lim;
    } else if (src->z < -lim) {
        dst->z = -lim;
    }
}

void func_ov004_022419f8(unsigned char *self)
{
    short *timer = (short *) (self + 0x98);
    switch (*(short *) (self + 0x172)) {
        case 2:
            if (self[0x170]) {
                self[0x170] = 0;
                *(short *) (self + 0x194) = 91;
            } else {
                self[0x170] = 1;
                *(short *) (self + 0x194) = -91;
            }
            if (((*(unsigned int *) (self + 0x154) << 4) >> 16) == 56) {
                *(short *) (self + 0x172) = 25;
                *(short *) (self + 0x194) = 0;
                *(int *) (self + 0x2c8) = *(int *) (self + 0x4c);
                NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x288), 0, 0);
                *(short *) (self + 0x98) = (func_020644cc(4) + 3) * 20;
            }
            break;
        case 1:
            if (((*(unsigned int *) (self + 0x154) << 4) >> 16) == 32) {
                *(short *) (self + 0x98) = (func_020644cc(3) + 2) * 20;
                *(short *) (self + 0x172) = 18;
                *(short *) (self + 0x168) = 0;
            }
            break;
        case 18:
            if (func_ov004_0224193c(self, (short *) (self + 0x168)) && *timer <= 0) {
                *(short *) (self + 0x192) = 0;
                *(short *) (self + 0x172) = 2;
                func_02056fcc(self + 0x14c, 57, (unsigned char) 1, 0x1000, (unsigned short) 32);
            } else {
                --*timer;
            }
            break;
        default:
            if (func_ov004_022419c4((char *) self)) {
                if (*timer > 0) {
                    --*timer;
                } else {
                    *(short *) (self + 0x172) = 1;
                    *(short *) (self + 0x9c) = 0;
                    func_02056fcc(self + 0x14c, 33, (unsigned char) 1, 0x1000, 0);
                    NNS_G3dMdlSetMdlAlpha(func_0209d088(self + 0x288), 0, 31);
                }
            } else {
                self[0x160] = 1;
            }
            break;
    }
}

int func_ov004_022419c4(char *self)
{
    char *h = func_020961a8(4);
    if (h != 0) {
        if (func_020ea990(h + 0x5c, self + 0x2c8) < 0x4800) {
            return 1;
        }
    }
    return 0;
}

int func_ov004_0224193c(void *self, short *state)
{
    short ang = *(short *) ((char *) self + 0x192);

    if (state[0] == 0) {
        if (func_020644cc(0x64) > 0x32) {
            *(unsigned char *) ((char *) self + 0x170) = 0;
        } else {
            *(unsigned char *) ((char *) self + 0x170) = 1;
        }
    }

    if (*(unsigned char *) ((char *) self + 0x170) != 0) {
        if (ang > 0xaaa) {
            *(unsigned char *) ((char *) self + 0x170) = 0;
        }
    } else {
        if (ang < (short) 0xf556) {
            *(unsigned char *) ((char *) self + 0x170) = 1;
        }
    }

    if (*(unsigned char *) ((char *) self + 0x170) != 0) {
        *(short *) ((char *) self + 0x192) = ang + 0x222;
    } else {
        *(short *) ((char *) self + 0x192) = ang - 0x222;
    }

    state[0] = state[0] + 1;
    return 1;
}

void func_ov004_02241894(char *self)
{
    switch (*(short *) (self + 0x172)) {
        case 3:
            func_ov004_02241588((char *) self, (short *) (self + 0x168));
            return;
        case 2:
            func_ov004_0224173c((char *) self, (short *) (self + 0x168));
            return;
        case 1:
            func_ov004_02241680((char *) self, (short *) (self + 0x168));
            return;
    }

    if (*(signed char *) (self + 0x196) == 9) {
        func_ov004_022417f8((char *) self);
        return;
    }
    if (*(u8 *) (self + 0x22) != 0) {
        if ((int) data_ov004_02259a24 % 0x14 != 0) {
            return;
        }
        if (func_020644cc(0x64) < 0x46) {
            return;
        }
    } else {
        if ((int) data_ov004_02259a24 % 0x28 != 0) {
            return;
        }
        if (func_020644cc(0x64) < 0x55) {
            return;
        }
    }
    if (func_020644cc(0x64) < 0x32) {
        *(short *) (self + 0x172) = 3;
    } else {
        *(short *) (self + 0x172) = 2;
    }
}

void func_ov004_022417f8(char *self)
{
    unsigned int t = (unsigned int) (*(int *) (self + 0x154) << 4) >> 16;
    u8 g;
    if (t == 0xd || t < 9) {
        func_02056fcc(self + 0x14c, 9, 1, 0, 9);
    }
    g = data_ov004_02259a24;
    if (g > 0x50) {
        if (*(u8 *) (self + 0x22) != 0) {
            if (func_020644cc(0x64) > 0x5c && t < 0xa) {
                func_02056fcc(self + 0x14c, 0xe, 1, 0x1000, 9);
            }
        } else if (g % 5 == 0) {
            if (func_020644cc(0x64) > 0x5c && t < 0xa) {
                func_02056fcc(self + 0x14c, 0xe, 1, 0x1000, 9);
            }
        }
    }
}

void func_ov004_0224173c(char *self, short *pc)
{
    int lim = *(int *) (self + 0xa8) + 0x400;
    int *v = (int *) (self + 0x2c8);
    short s = *pc;
    if ((s >= 0 && s < 2) || (s >= 6 && s < 8)) {
        *pc += 1;
        *(short *) (self + 0x192) = (short) (*(short *) (self + 0x192) + 0x2aa);
        *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) + 0xaa);
        v[1] += 0x20;
    } else if (s >= 2 && s < 6) {
        *pc += 1;
        *(short *) (self + 0x192) = (short) (*(short *) (self + 0x192) - 0x2aa);
        *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) - 0xaa);
        v[1] += 0x20;
    } else if (func_020644cc(0x64) > 0x46) {
        *(short *) (self + 0x172) = 1;
        *pc = 0;
    } else if (*pc >= 8) {
        *pc = 0;
    }
    if (v[1] > lim) {
        v[1] = lim;
    }
}

void func_ov004_02241680(char *self, short *pc)
{
    int lim = *(int *) (self + 0xa8) - 0x100;
    int *v = (int *) (self + 0x2c8);
    short s = *pc;
    if ((s >= 0 && s < 2) || (s >= 6 && s < 8)) {
        *pc += 1;
        *(short *) (self + 0x192) = (short) (*(short *) (self + 0x192) + 0x2aa);
        *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) + 0xaa);
        v[1] -= 0x20;
    } else if (s >= 2 && s < 6) {
        *pc += 1;
        *(short *) (self + 0x192) = (short) (*(short *) (self + 0x192) - 0x2aa);
        *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) - 0xaa);
        v[1] -= 0x20;
    } else if (func_020644cc(0x64) > 0x46) {
        *(short *) (self + 0x172) = 0x19;
        *pc = 0;
    } else if (*pc >= 8) {
        *pc = 0;
    }
    if (v[1] < lim) {
        v[1] = lim;
    }
}

void func_ov004_02241588(char *self, short *pc)
{
    short a = *(short *) (self + 0x192);
    short d = *pc;
    if (d == 0) {
        if (func_020644cc(0x64) < 0x32) {
            *pc += 1;
        } else {
            *pc -= 1;
        }
    } else if ((d > 0 && d <= 6) || (d > 0x12 && d <= 0x18) || (d < ~5 && d >= ~0x11)) {
        if (d > 0) {
            *pc += 1;
            *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) + 0xb6);
        } else {
            *pc -= 1;
            *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) - 0xb6);
        }
        a = (short) (a + 0x16b);
    } else if ((d > 6 && d <= 0x12) || (d < 0 && d >= ~5) || (d < ~0x11 && d >= ~0x17)) {
        if (d > 0) {
            *pc += 1;
            *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) - 0xb6);
        } else {
            *pc -= 1;
            *(short *) (self + 0x190) = (short) (*(short *) (self + 0x190) + 0xb6);
        }
        a = (short) (a - 0x16b);
    } else {
        *pc = 0;
        *(short *) (self + 0x172) = 0x19;
    }
    *(short *) (self + 0x192) = a;
}

void func_ov004_022414a8(char *self)
{
    char *p;
    int q;
    func_ov004_02244764(self);
    if (*(signed char *) (self + 0x196) == 0x14) {
        p = self + 0xb0;
        if (*(short *) (self + 0x9c) >= *(short *) (self + 0x9e) || *(u8 *) (self + 0x50) != 0) {
            if (((unsigned int) (*(int *) (p + 0xa4) << 4) >> 16) == 0) {
                func_02056fcc(p + 0x9c, 4, 1, 0x1000, 0);
                *(u8 *) (self + 0x50) = 0x3c;
            } else if (*(u8 *) (self + 0x50) != 0) {
                *(u8 *) (self + 0x50) = (u8) (*(u8 *) (self + 0x50) - 1);
            }
        } else {
            q = *(int *) (p + 0xa4) >> 12;
            if ((u16) q != 0 || ((unsigned int) (*(int *) (p + 0xa0) << 4) >> 16) != 0) {
                func_02056fcc(p + 0x9c, 0, 3, 0x1000, (u16) q);
            }
        }
    }
    if (*(u8 *) (self + 0x22) != 0) {
        if (*(short *) (self + 0x9c) < *(short *) (self + 0x9e)) {
            if (*(u8 *) (self + 0x50) == 0) {
                func_ov004_02244be0(self, 0);
            } else {
                *(u8 *) (self + 0x50) = (u8) (*(u8 *) (self + 0x50) - 1);
            }
        } else {
            *(u8 *) (self + 0x50) = 0x3c;
        }
    }
}

void func_ov004_02241350(unsigned char *self)
{
    short *timer = (short *) (self + 0x168);
    func_ov004_022411a4(self, timer);
    ++*(short *) (self + 0x168);
    if (*(short *) (self + 0x172) == 4) {
        func_ov004_02241084(self);
        if (*(signed char *) (self + 0x196) == 26) {
            if (*timer > 320 || (*timer % 20 == 0 && func_020644cc(100) > 90 && *timer > 160)) {
                *(short *) (self + 0x172) = 25;
                *timer = 0;
            }
        } else {
            if (*timer > 160 || (*timer % 20 == 0 && func_020644cc(100) > 90 && *timer > 80)) {
                *(short *) (self + 0x172) = 25;
                *timer = 0;
            }
        }
    } else if (*(signed char *) (self + 0x196) == 26) {
        if (self[0x22] && ((*(unsigned int *) (self + 0x154) << 4) >> 16) == 2) {
            if (*timer > 160 || (*timer % 20 == 0 && func_020644cc(100) > 85 && *timer >= 40)) {
                *timer = 0;
                *(short *) (self + 0x172) = 4;
            }
        }
    } else if (self[0x22]) {
        if (*timer > 80 || (*timer % 20 == 0 && func_020644cc(100) > 85)) {
            *(short *) (self + 0x172) = 4;
            *timer = 0;
        }
    } else {
        if (*timer > 800 || (*timer % 100 == 0 && func_020644cc(100) > 90)) {
            *(short *) (self + 0x172) = 4;
            *timer = 0;
        }
    }
}
