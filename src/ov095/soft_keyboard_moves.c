/* soft_keyboard_moves: 19 functions, module ov095
 * mwccarm 1.2/base -O4,s
 * func_ov095_0229aaac @ 0x0229aaac, 0x34 bytes, Thumb
 * func_ov095_0229aa74 @ 0x0229aa74, 0x38 bytes, Thumb
 * func_ov095_0229aa3c @ 0x0229aa3c, 0x38 bytes, Thumb
 * func_ov095_0229a9d4 @ 0x0229a9d4, 0x68 bytes, Thumb
 * func_ov095_0229a720 @ 0x0229a720, 0x2b4 bytes, Thumb
 * func_ov095_0229a4d4 @ 0x0229a4d4, 0x24c bytes, Thumb
 * func_ov095_0229a2d8 @ 0x0229a2d8, 0x1fc bytes, Thumb
 * func_ov095_0229a280 @ 0x0229a280, 0x58 bytes, Thumb
 * func_ov095_0229a1ec @ 0x0229a1ec, 0x94 bytes, Thumb
 * func_ov095_0229a1d4 @ 0x0229a1d4, 0x16 bytes, Thumb
 * func_ov095_0229a184 @ 0x0229a184, 0x50 bytes, Thumb
 * func_ov095_0229a170 @ 0x0229a170, 0x14 bytes, Thumb
 * func_ov095_0229a154 @ 0x0229a154, 0x1a bytes, Thumb
 * func_ov095_0229a148 @ 0x0229a148, 0xc bytes, Thumb
 * func_ov095_0229a134 @ 0x0229a134, 0x14 bytes, Thumb
 * func_ov095_02299f3c @ 0x02299f3c, 0x1f8 bytes, Thumb
 * func_ov095_02299e80 @ 0x02299e80, 0xbc bytes, Thumb
 * func_ov095_02299cf8 @ 0x02299cf8, 0x188 bytes, Thumb
 * func_ov095_02299c14 @ 0x02299c14, 0xe4 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229aa3c {
    unsigned char pad_00[0x28];
    unsigned int x;
    unsigned char pad_2C[0x16];
    unsigned char b;
};

typedef struct UnkStruct_0229a9d4 {
    char pad_00[0x28];
    int unk_28;
    char pad_2C[0x16];
    unsigned char unk_42;
} UnkStruct_0229a9d4;

typedef struct {
    char pad_00[0x28];
    int unk_28;
    char pad_2C[0x17];
    u8 unk_43;
} UnkStruct_0229a720;

typedef struct {
    char pad_00[0x28];
    int unk_28;
    char pad_2C[0x43 - 0x2c];
    unsigned char unk_43;
} UnkStruct_0229a4d4;

typedef struct UnkStruct_0229a2d8 {
    u8 pad_00[0x28];
    int st;
    u8 pad_2C[0x43 - 0x2c];
    u8 flag;
} UnkStruct_0229a2d8;

typedef struct UnkStruct_0229a1ec {
    unsigned char unk_00[0x18];
    unsigned char unk_18;
    unsigned char pad_19[0x0F];
    int unk_28;
} UnkStruct_0229a1ec;

struct UnkStruct_0229a184 {
    char pad_00[0x16];
    unsigned char unk_16;
    char pad_17[0x11];
    int unk_28;
};

typedef struct {
    unsigned char pad_00[0x18];
    unsigned char unk_18;
    unsigned char pad_19[0xf];
    int unk_28;
    int unk_2C;
    unsigned char pad_30[0x13];
    unsigned char unk_43;
} UnkStruct_02299f3c;

typedef struct UnkStruct_02299e80 {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
} UnkStruct_02299e80;

typedef struct {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[0x11];
    int unk_28;
} UnkStruct_02299cf8;

typedef struct {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[0x11];
    unsigned int state;
    unsigned char pad_2C[0x16];
    unsigned char unk_42;
} UnkStruct_02299c14;

extern int func_ov095_0229ac2c(void *unused0);
extern unsigned char data_ov095_0229d020[];
extern unsigned char data_ov095_0229cff0[];
extern void func_ov095_0229ab68(void *unused0);
extern void func_ov095_0229aae0(void *unused0);
extern int func_ov095_022999b0(void *, int);
extern int data_ov095_0229e410[];
extern int data_ov095_0229e3e8[];
extern int func_ov095_02299bb4(UnkStruct_0229a720 *self, void *unused1);
extern int func_ov002_022088cc(void *p);
extern int func_ov002_022088ac(void *p);
extern int func_ov002_022088bc(void *p);
extern int func_ov002_0220889c(void *p);
extern int data_ov095_0229cfa0[6];
extern int data_ov095_0229cfb4[6];
extern void func_ov095_022999a8(void *self, int arg);
extern int func_ov095_0229ae5c(UnkStruct_0229a1ec *self, int index);
extern int func_ov095_0229ad90(UnkStruct_0229a1ec *self, int index);
extern int func_ov095_02299b7c(void *argument0);
extern int data_ov095_0229cfdc[];
extern int data_ov095_0229cf8c[];
extern int data_ov095_0229cfc8[];
extern int data_ov095_0229cf78[];
extern int _s32_div_f(int, int);
extern int func_ov090_02298f84(int a);
extern int func_ov095_0229cdf0(UnkStruct_02299e80 *self, int v);

void func_ov095_0229a1d4(int a);

void func_ov095_0229aaac(void *self)
{
    if (func_ov095_0229ac2c(self) == 0) {
        int v = *(int *) ((char *) self + 0x28);
        if (v >= 0xc9 && v <= 0xf6) {
            int idx = v - 0xc9;
            *(int *) ((char *) self + 0x2c) = data_ov095_0229d020[idx];
            *(int *) ((char *) self + 0x30) = data_ov095_0229cff0[idx];
        }
    }
}

void func_ov095_0229aa74(unsigned char *p0)
{
    switch (p0[0x16]) {
        case 0:
        case 3:
            break;
        case 1:
            func_ov095_0229ab68(p0);
            break;
        case 2:
            func_ov095_0229aae0(p0);
            break;
        case 4:
            func_ov095_0229aaac(p0);
            break;
    }
}

void func_ov095_0229aa3c(struct UnkStruct_0229aa3c *self)
{
    switch (self->b) {
        case 0:
        case 3:
            break;
        case 1:
        case 2:
            self->x = 0x104;
            break;
        case 4:
        case 5:
            self->x = 0x107;
            break;
        default:
            break;
    }
}

void func_ov095_0229a9d4(UnkStruct_0229a9d4 *p)
{
    unsigned char v = p->unk_42;
    switch (v) {
        case 0:
            break;
        case 1:
            if (func_ov095_022999b0(p, 8)) {
                p->unk_28 = 0x104;
            } else {
                p->unk_28 = 0x105;
            }
            break;
        case 2:
            p->unk_28 = 0x106;
            break;
        case 5:
            p->unk_28 = 0x108;
            break;
        case 4:
            p->unk_28 = 0x107;
            break;
    }
}

void func_ov095_0229a720(UnkStruct_0229a720 *self, void *pad)
{
    int mode;
    int lo;
    int hi;
    int lo2;
    int hi2;
    int *p;
    int *p2;

    if (func_ov095_02299bb4(self, pad) != 0) {
        return;
    }
    if (self->unk_28 >= 0x3b) {
        if (self->unk_28 <= 0x46) {
            mode = 0;
        } else if (self->unk_28 <= 0x51) {
            mode = 1;
            if (self->unk_28 == 0x51) {
                if (func_ov002_022088cc(pad)) {
                    if (func_ov002_022088ac(pad)) {
                        self->unk_28 = 0x45;
                    } else {
                        self->unk_28 = 0x46;
                    }
                    return;
                }
                if (func_ov002_022088bc(pad)) {
                    self->unk_28 = 0x5c;
                    return;
                }
            }
        } else if (self->unk_28 <= 0x5c) {
            mode = 2;
            if (self->unk_28 == 0x5c) {
                if (func_ov002_022088cc(pad)) {
                    if (func_ov002_022088ac(pad)) {
                        self->unk_28 = 0x50;
                    } else {
                        self->unk_28 = 0x51;
                    }
                    return;
                }
            }
        } else if (self->unk_28 <= 0x67) {
            mode = 3;
            if (func_ov002_022088bc(pad)) {
                if (func_ov002_022088ac(pad)) {
                    self->unk_28 = self->unk_28 - 1;
                }
                if (self->unk_28 < 0x5d) {
                    self->unk_28 = 0x5d;
                }
                if (self->unk_28 <= 0x5e) {
                    self->unk_28 = self->unk_28 + 0xb;
                } else if (self->unk_28 <= 0x65) {
                    self->unk_28 = 0x6b;
                } else {
                    self->unk_28 = self->unk_28 + 8;
                }
                return;
            }
        } else if (self->unk_28 <= 0x6f) {
            mode = 4;
            if (func_ov002_022088cc(pad)) {
                if (self->unk_28 == 0x6b) {
                    self->unk_28 = 0x63;
                    if (func_ov002_022088ac(pad)) {
                        self->unk_28 = self->unk_28 - 1;
                        return;
                    }
                    if (func_ov002_0220889c(pad) == 0) {
                        return;
                    }
                    self->unk_28 = self->unk_28 + 1;
                    return;
                } else if (self->unk_28 > 0x6b) {
                    self->unk_28 = self->unk_28 - 8;
                    if (func_ov002_0220889c(pad) == 0) {
                        return;
                    }
                    if (self->unk_28 < 0x67) {
                        self->unk_28 = self->unk_28 + 1;
                    }
                    return;
                }
            } else {
                if (func_ov002_022088bc(pad)) {
                    if (self->unk_28 < 0x6c) {
                        func_ov095_0229a9d4((UnkStruct_0229a9d4 *) self);
                    } else {
                        func_ov095_0229aa3c((struct UnkStruct_0229aa3c *) self);
                    }
                    return;
                }
            }
        } else {
            return;
        }
    }
    if (func_ov002_022088cc(pad)) {
        if (mode == 0) {
            func_ov095_0229a1d4((int) self);
            return;
        }
        lo = data_ov095_0229e410[mode - 1];
        hi = data_ov095_0229e3e8[mode - 1];
        p = &self->unk_28;
        self->unk_28 = self->unk_28 - (hi - lo + 1);
        if (mode == 2) {
            *p = *p - 1;
        }
        if (func_ov002_0220889c(pad)) {
            self->unk_28 = self->unk_28 + 1;
        }
        if (self->unk_28 < lo) {
            self->unk_28 = lo;
        } else if (self->unk_28 > hi) {
            self->unk_28 = hi;
        }
    } else if (func_ov002_022088bc(pad) && mode < 3) {
        lo2 = data_ov095_0229e410[mode + 1];
        hi2 = data_ov095_0229e3e8[mode + 1];
        self->unk_28 = self->unk_28 + (data_ov095_0229e3e8[mode] - data_ov095_0229e410[mode] + 1);
        p2 = &self->unk_28;
        if (mode == 1) {
            *p2 = *p2 + 1;
        }
        if (func_ov002_022088ac(pad)) {
            self->unk_28 = self->unk_28 - 1;
        }
        if (self->unk_28 > hi2) {
            self->unk_28 = hi2;
        } else if (self->unk_28 < lo2) {
            self->unk_28 = lo2;
        }
    } else {
        if (self->unk_28 == 0x6b) {
            if (func_ov002_022088ac(pad)) {
                self->unk_28 = 0x69;
                return;
            }
            if (func_ov002_0220889c(pad)) {
                self->unk_28 = 0x6e;
            }
            return;
        }
        if (func_ov002_022088ac(pad)) {
            if (self->unk_28 > data_ov095_0229e410[mode]) {
                self->unk_28 = self->unk_28 - 1;
            } else {
                self->unk_43 = 1;
                self->unk_28 = data_ov095_0229e3e8[mode];
            }
        } else if (func_ov002_0220889c(pad)) {
            if (self->unk_28 < data_ov095_0229e3e8[mode]) {
                self->unk_28 = self->unk_28 + 1;
            } else {
                self->unk_43 = 2;
                self->unk_28 = data_ov095_0229e410[mode];
            }
        }
        if (self->unk_28 == 0x6a || self->unk_28 == 0x6c || self->unk_28 == 0x6d) {
            self->unk_28 = 0x6b;
        }
    }
}

void func_ov095_0229a4d4(UnkStruct_0229a4d4 *self, void *pad)
{
    if (func_ov095_02299bb4((UnkStruct_0229a720 *) self, pad)) {
        return;
    }

    if (self->unk_28 < 0x70) {
        return;
    }

    if (self->unk_28 <= 0x8d) {
        int n = self->unk_28 - 0x70;
        int x = n % 10;
        int y = n / 10;

        if (func_ov002_022088cc(pad)) {
            if (y > 0) {
                y--;
                self->unk_28 = self->unk_28 - 10;
            } else {
                func_ov095_0229a1d4((int) self);
                return;
            }
        } else if (func_ov002_022088bc(pad)) {
            if (y < 2) {
                y++;
                self->unk_28 = self->unk_28 + 10;
            } else {
                self->unk_28 = 0x91;
                return;
            }
        }

        if (func_ov002_022088ac(pad)) {
            if (x > 0) {
                self->unk_28 = self->unk_28 - 1;
            } else {
                self->unk_43 = 1;
                if (y == 0) {
                    self->unk_28 = 0x8f;
                } else {
                    self->unk_28 = 0x90;
                }
            }
        } else if (func_ov002_0220889c(pad)) {
            if (x < 9) {
                self->unk_28 = self->unk_28 + 1;
            } else {
                if (y == 0) {
                    self->unk_28 = 0x8e;
                } else {
                    self->unk_28 = 0x90;
                }
            }
        }
        return;
    }

    switch (self->unk_28) {
        case 0x8e:
            if (func_ov002_022088cc(pad)) {
                func_ov095_0229a1d4((int) self);
            } else if (func_ov002_022088bc(pad)) {
                if (func_ov002_022088ac(pad)) {
                    self->unk_28 = 0x83;
                } else {
                    self->unk_28 = 0x90;
                }
            } else if (func_ov002_022088ac(pad)) {
                self->unk_28 = 0x79;
            } else if (func_ov002_0220889c(pad)) {
                self->unk_28 = 0x8f;
            }
            break;
        case 0x8f:
            if (func_ov002_022088cc(pad)) {
                func_ov095_0229a1d4((int) self);
            } else if (func_ov002_022088bc(pad)) {
                self->unk_28 = 0x90;
            } else if (func_ov002_022088ac(pad)) {
                self->unk_28 = 0x8e;
            } else if (func_ov002_0220889c(pad)) {
                self->unk_43 = 2;
                self->unk_28 = 0x70;
            }
            break;
        case 0x90:
            if (func_ov002_022088cc(pad)) {
                self->unk_28 = 0x8f;
                if (func_ov002_022088ac(pad)) {
                    self->unk_28 = self->unk_28 - 1;
                }
                break;
            }
            if (func_ov002_022088bc(pad)) {
                func_ov095_0229aa3c((struct UnkStruct_0229aa3c *) self);
                if (self->unk_28 != 0x90) {
                    break;
                }
            }
            if (func_ov002_022088ac(pad)) {
                if (func_ov002_022088bc(pad)) {
                    self->unk_28 = 0x8d;
                } else {
                    self->unk_28 = 0x83;
                }
            } else if (func_ov002_0220889c(pad)) {
                self->unk_43 = 2;
                if (func_ov002_022088bc(pad)) {
                    self->unk_28 = 0x84;
                } else {
                    self->unk_28 = 0x7a;
                }
            }
            break;
        case 0x91:
            if (func_ov002_022088cc(pad)) {
                self->unk_28 = 0x8a;
                if (func_ov002_022088ac(pad)) {
                    self->unk_28 = self->unk_28 - 1;
                }
            } else if (func_ov002_0220889c(pad)) {
                func_ov095_0229aa3c((struct UnkStruct_0229aa3c *) self);
            } else if (func_ov002_022088bc(pad)) {
                func_ov095_0229a9d4((UnkStruct_0229a9d4 *) self);
            }
            break;
    }
}

void func_ov095_0229a2d8(UnkStruct_0229a2d8 *self, void *evt)
{
    int phase;
    int state;
    int kind;
    int diff;

    if (func_ov095_02299bb4((UnkStruct_0229a720 *) self, evt)) {
        return;
    }

    state = self->st;
    if (state < 0xc9) {
        return;
    }
    if (state > 0xf6) {
        return;
    }

    for (phase = 0; phase < 5; phase++) {
        if (state <= data_ov095_0229cfb4[phase]) {
            kind = phase;
            diff = state - data_ov095_0229cfa0[phase];
            break;
        }
    }

    if (func_ov002_022088cc(evt)) {
        if (kind == 0) {
            func_ov095_0229a1d4((int) self);
            return;
        }
        if (kind == 4) {
            int s2 = self->st;
            if (s2 <= 0xf3) {
                if (func_ov002_0220889c(evt)) {
                    diff++;
                }
                self->st = diff + 0xe8;
                return;
            }
            if (s2 == 0xf4) {
                self->st = 0xec;
                if (func_ov002_0220889c(evt)) {
                    self->st = self->st + 1;
                    return;
                }
                if (!func_ov002_022088ac(evt)) {
                    return;
                }
                self->st = self->st - 1;
                return;
            }
            self->st = s2 - 6;
            if (!func_ov002_022088ac(evt)) {
                return;
            }
            self->st = self->st - 1;
            return;
        }
        if (self->st == 0xe7) {
            if (func_ov002_022088ac(evt)) {
                self->st = 0xe6;
                return;
            }
            self->st = 0xdd;
            return;
        }
        if (func_ov002_0220889c(evt)) {
            diff++;
        }
        self->st = diff + data_ov095_0229cfa0[kind - 1];
        if (self->st > data_ov095_0229cfb4[kind - 1]) {
            self->st = data_ov095_0229cfb4[kind - 1];
        }
        return;
    }

    if (func_ov002_022088bc(evt)) {
        if (kind == 4) {
            int s2 = self->st;
            if (s2 <= 0xf4) {
                func_ov095_0229a9d4((UnkStruct_0229a9d4 *) self);
                return;
            }
            func_ov095_0229aa3c((struct UnkStruct_0229aa3c *) self);
            return;
        }
        if (kind == 3) {
            int s2 = self->st;
            if (s2 <= 0xea) {
                if (func_ov002_022088ac(evt)) {
                    if (diff > 0) {
                        diff--;
                    }
                }
                self->st = diff + data_ov095_0229cfa0[kind + 1];
                return;
            }
            if (func_ov002_0220889c(evt)) {
                self->st = self->st + 1;
            }
            if (self->st <= 0xee) {
                self->st = 0xf4;
                return;
            }
            if (self->st == 0xef) {
                self->st = 0xf5;
                return;
            }
            self->st = 0xf6;
            return;
        }
        if (func_ov002_022088ac(evt)) {
            if (diff > 0) {
                diff--;
            }
        }
        self->st = diff + data_ov095_0229cfa0[kind + 1];
        if (self->st > data_ov095_0229cfb4[kind + 1]) {
            self->st = data_ov095_0229cfb4[kind + 1];
        }
        return;
    }

    if (func_ov002_022088ac(evt)) {
        self->st = self->st - 1;
        if (self->st < data_ov095_0229cfa0[kind]) {
            self->st = data_ov095_0229cfb4[kind];
            self->flag = 1;
        }
        return;
    }
    if (func_ov002_0220889c(evt)) {
        self->st = self->st + 1;
        if (self->st > data_ov095_0229cfb4[kind]) {
            self->st = data_ov095_0229cfa0[kind];
            self->flag = 2;
        }
    }
}

void func_ov095_0229a280(void *self)
{
    unsigned char c = ((unsigned char *) self)[0x42];

    switch (c) {
        case 0:
            if (*(unsigned int *) ((char *) self + 0x28) == 0x10a) {
                *(unsigned int *) ((char *) self + 0x28) = 0xf7;
            } else {
                func_ov095_022999a8(self, 0x10);
            }
            break;

        case 1:
        case 2:
            *(unsigned int *) ((char *) self + 0x28) = 0x103;
            break;

        case 3:
        case 4:
        case 5:
            func_ov095_022999a8(self, 0x10);
            break;
    }
}

void func_ov095_0229a1ec(UnkStruct_0229a1ec *self, int value)
{
    int best;
    int i;
    int diff;

    if (value < 0x80) {
        self->unk_28 = 0x109;
        best = value - 0x18;
    } else {
        self->unk_28 = 0x10a;
        best = value - 0xe8;
    }

    for (i = 0; i < 3; i++) {
        diff = value - func_ov095_0229ae5c(self, i + 0xf8);
        if (diff < 0) {
            diff = -diff;
        }
        if (diff < best) {
            best = diff;
            self->unk_28 = i + 0xf8;
        }
    }

    if (func_ov095_022999b0((void *) self, 4) != 0) {
        if (best < 0) {
            best = -best;
        }
        for (i = 0; i < self->unk_18; i++) {
            diff = value - func_ov095_0229ad90(self, i + 0x10c);
            if (diff < 0) {
                diff = -diff;
            }
            if (diff < best) {
                best = diff;
                self->unk_28 = i + 0x10c;
            }
        }
    }
}

void func_ov095_0229a1d4(int a)
{
    int b;
    b = func_ov095_02299b7c((void *) a);
    func_ov095_0229a1ec((UnkStruct_0229a1ec *) a, b);
}

void func_ov095_0229a184(struct UnkStruct_0229a184 *self, int val)
{
    int idx;
    int a1;
    int sum;
    int a3;

    idx = self->unk_16;
    a1 = data_ov095_0229cfdc[idx];
    if (val < a1) {
        val = a1;
    }
    sum = _s32_div_f(val - a1, 20);
    sum += data_ov095_0229cf8c[idx];
    a3 = data_ov095_0229cfc8[idx];
    if (sum > a3) {
        sum = data_ov095_0229cf78[idx];
    }
    self->unk_28 = sum;
    func_ov095_0229aa74((unsigned char *) self);
}

void func_ov095_0229a170(int param, int argument1)
{
    func_ov095_0229a1ec((UnkStruct_0229a1ec *) param, argument1);
    func_ov095_0229aa74((unsigned char *) param);
}

void func_ov095_0229a154(void *a, int b)
{
    int c;
    c = func_ov090_02298f84(b);
    c += 0xfb;
    *(int *) ((char *) a + 0x28) = c;
    func_ov095_0229aa74((unsigned char *) a);
}

void func_ov095_0229a148(void *r0)
{
    *(unsigned int *) ((char *) r0 + 0x28) = 0xf7;
    func_ov095_0229aa74((unsigned char *) r0);
}

void func_ov095_0229a134(int p, int argument1)
{
    func_ov095_0229a1ec((UnkStruct_0229a1ec *) p, argument1);
    func_ov095_0229aa74((unsigned char *) p);
}

int func_ov095_02299f3c(UnkStruct_02299f3c *o, void *in)
{
    switch (o->unk_28) {
        case 0xf8:
        case 0xf9:
        case 0xfa:
            if (func_ov002_0220889c(in) != 0) {
                if (o->unk_28 < 0xfa) {
                    o->unk_28 = o->unk_28 + 1;
                } else if (o->unk_18 != 0) {
                    o->unk_28 = 0x10c;
                } else {
                    o->unk_28 = 0x10a;
                }
                return 1;
            }
            if (func_ov002_022088ac(in) != 0) {
                if (o->unk_28 > 0xf8) {
                    o->unk_28 = o->unk_28 - 1;
                } else {
                    o->unk_28 = 0x109;
                }
                return 1;
            }
            if (func_ov002_022088bc(in) != 0) {
                func_ov095_0229a184((struct UnkStruct_0229a184 *) o, o->unk_2C);
            } else if (func_ov002_022088cc(in) != 0) {
                func_ov095_0229a280((void *) o);
            }
            return 1;
        case 0x109:
            if (func_ov002_022088cc(in) != 0) {
                func_ov095_0229a280((void *) o);
            } else if (func_ov002_022088bc(in) != 0) {
                func_ov095_0229a184((struct UnkStruct_0229a184 *) o, o->unk_2C);
            } else if (func_ov002_0220889c(in) != 0) {
                o->unk_28 = 0xf8;
            } else if (func_ov002_022088ac(in) != 0) {
                o->unk_28 = 0x10a;
                o->unk_43 = 1;
            }
            return 1;
        case 0x10a:
            if (func_ov002_022088cc(in) != 0) {
                func_ov095_0229a280((void *) o);
            } else if (func_ov002_022088bc(in) != 0) {
                func_ov095_0229a184((struct UnkStruct_0229a184 *) o, o->unk_2C);
            } else if (func_ov002_022088ac(in) != 0) {
                if (o->unk_18 != 0) {
                    o->unk_28 = o->unk_18 + 0x10b;
                } else {
                    o->unk_28 = 0xfa;
                }
            } else if (func_ov002_0220889c(in) != 0) {
                o->unk_28 = 0x109;
                o->unk_43 = 2;
            }
            return 1;
        case 0x10c:
        case 0x10d:
        case 0x10e:
        case 0x10f:
            if (func_ov002_022088cc(in) != 0) {
                func_ov095_0229a280((void *) o);
            } else if (func_ov002_022088bc(in) != 0) {
                func_ov095_0229a184((struct UnkStruct_0229a184 *) o, o->unk_2C);
            } else if (func_ov002_022088ac(in) != 0) {
                if (o->unk_28 > 0x10c) {
                    o->unk_28 = o->unk_28 - 1;
                } else {
                    o->unk_28 = 0xfa;
                }
            } else if (func_ov002_0220889c(in) != 0) {
                if (o->unk_28 < o->unk_18 + 0x10b) {
                    o->unk_28 = o->unk_28 + 1;
                } else {
                    o->unk_28 = 0x10a;
                }
            }
            return 1;
    }
    return 0;
}

int func_ov095_02299e80(UnkStruct_02299e80 *self, void *pad)
{
    int v;

    v = self->unk_28;
    if (v == 0xf7) {
        if (func_ov002_022088bc(pad) != 0) {
            self->unk_28 = 0x10a;
        } else if (func_ov002_022088cc(pad) != 0) {
            self->unk_28 = func_ov090_02298f84(self->unk_2C) + 0xfb;
        } else if (func_ov002_022088ac(pad) != 0) {
            func_ov095_022999a8((void *) self, 0x10);
        }
        return 1;
    }
    if (func_ov095_0229cdf0(self, v) == 0) {
        goto ret0;
    }
    if (func_ov002_022088bc(pad) != 0) {
        if (self->unk_28 >= 0x101) {
            self->unk_28 = 0xf7;
        } else {
            func_ov095_022999a8((void *) self, 0x10);
        }
        return 1;
    }
    if (func_ov002_0220889c(pad) != 0) {
        v = self->unk_28;
        if (v < 0x102) {
            self->unk_28 = v + 1;
        }
    } else if (func_ov002_022088ac(pad) != 0) {
        v = self->unk_28;
        if (v > 0xfb) {
            self->unk_28 = v - 1;
        }
    }
    return 1;
ret0:
    return 0;
}

int func_ov095_02299cf8(UnkStruct_02299cf8 *o, void *in)
{
    int v;

    v = o->unk_28;
    if (v == 0x103) {
        if (func_ov002_022088bc(in) != 0) {
            o->unk_28 = 0x10a;
        }
        return 1;
    }
    switch (v) {
        case 0x104:
            if (func_ov002_022088cc(in) != 0) {
                switch (o->unk_16) {
                    case 0:
                        o->unk_28 = 0x2c;
                        break;
                    case 1:
                        o->unk_28 = 0x6e;
                        break;
                    case 2:
                        o->unk_28 = 0x90;
                        break;
                    case 3:
                        o->unk_28 = 0xc8;
                        break;
                    case 4:
                        o->unk_28 = 0xf6;
                        break;
                }
            } else if (func_ov002_022088ac(in) != 0) {
                func_ov095_0229a9d4((UnkStruct_0229a9d4 *) o);
            }
            return 1;
        case 0x105:
            if (func_ov002_022088cc(in) != 0) {
                switch (o->unk_16) {
                    case 0:
                        o->unk_28 = 0xe;
                        break;
                    case 1:
                        o->unk_28 = 0x69;
                        break;
                    case 2:
                        o->unk_28 = 0x91;
                        break;
                    case 3:
                        o->unk_28 = 0xc0;
                        break;
                    case 4:
                        o->unk_28 = 0xf4;
                        break;
                }
            } else if (func_ov002_0220889c(in) != 0) {
                o->unk_28 = 0x104;
            }
            return 1;
        case 0x106:
            if (func_ov002_022088cc(in) != 0) {
                switch (o->unk_16) {
                    case 0:
                        o->unk_28 = 0x13;
                        break;
                    case 1:
                        o->unk_28 = 0x6b;
                        break;
                    case 2:
                        o->unk_28 = 0x91;
                        break;
                    case 3:
                        o->unk_28 = 0xc2;
                        break;
                    case 4:
                        o->unk_28 = 0xf4;
                        break;
                }
            } else if (func_ov002_0220889c(in) != 0) {
                o->unk_28 = 0x104;
            }
            return 1;
    }
    if (v == 0x105 || v == 0x106) {
        if (func_ov002_022088bc(in) != 0) {
            o->unk_28 = 0x103;
        } else if (func_ov002_0220889c(in) != 0) {
            o->unk_28 = 0x104;
        }
        return 1;
    }
    return 0;
}

int func_ov095_02299c14(UnkStruct_02299c14 *self, void *arg)
{
    unsigned int st = self->state;
    if (st == 0x107) {
        if (func_ov002_022088cc(arg)) {
            switch (self->unk_16) {
                case 0:
                    self->state = 0x2c;
                    break;
                case 1:
                    self->state = 0x6e;
                    break;
                case 2:
                    self->state = 0x90;
                    break;
                case 3:
                    self->state = 0xc8;
                    break;
                case 4:
                    self->state = 0xf6;
                    break;
            }
        } else if (self->unk_42 == 5 && func_ov002_022088ac(arg)) {
            self->state = 0x108;
        }
        return 1;
    } else if (st == 0x108) {
        if (func_ov002_022088cc(arg)) {
            switch (self->unk_16) {
                case 0:
                    self->state = 0x18;
                    break;
                case 1:
                    self->state = 0x6b;
                    break;
                case 2:
                    self->state = 0x91;
                    break;
                case 3:
                    self->state = 0xc3;
                    break;
                case 4:
                    self->state = 0xf4;
                    break;
            }
        } else if (func_ov002_0220889c(arg)) {
            self->state = 0x107;
        }
        return 1;
    }
    return 0;
}
