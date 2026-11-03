/* music_list_input: 7 functions, module ov144
 * mwccarm 1.2/base -O4,s
 * func_ov144_02299ac4 @ 0x02299ac4, 0x84 bytes, Thumb
 * func_ov144_02299a30 @ 0x02299a30, 0x94 bytes, Thumb
 * func_ov144_02299a00 @ 0x02299a00, 0x2e bytes, Thumb
 * func_ov144_02299968 @ 0x02299968, 0x98 bytes, Thumb
 * func_ov144_0229993c @ 0x0229993c, 0x2a bytes, Thumb
 * func_ov144_02299924 @ 0x02299924, 0x18 bytes, Thumb
 * func_ov144_022996d4 @ 0x022996d4, 0x250 bytes, Thumb
 */

struct UnkStruct_02299a30 {
    char pad_00[0xa0];
    int unk_A0;
    char pad_A4[0xb8 - 0xa4];
    signed short unk_B8;
    char pad_BA[0x170 - 0xba];
    int unk_170;
};

struct UnkStruct_02299968 {
    char pad_00[0xA0];
    unsigned int p;
    char pad_A4[0x14];
    short d;
    char pad_BA[0x07];
    unsigned char b;
    char pad_C2[0x02];
    unsigned int q;
};

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    char pad_A8[0x19];
    unsigned char unk_C1;
} UnkStruct_0229993c;

typedef struct {
    char pad_00[0xa0];
    int unk_A0;
    int unk_A4;
    char pad_A8[0xb8 - 0xa8];
    short unk_B8;
    char pad_BA[0xc1 - 0xba];
    volatile unsigned char unk_C1;
} UnkStruct_022996d4;

extern void func_ov144_0229a798(void *self);
extern int func_ov144_0229a71c(void *self);
extern int func_ov144_0229a5f4(void *self);
extern void func_ov144_0229a5bc(void *self);
extern int func_ov144_02299b48(void *self, unsigned int x);
extern void func_ov002_0220a574(void *p);
extern void func_ov002_0220a4bc(void *receiver);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void func_0200467c(unsigned int cmd);
extern int func_ov002_0220a784(void *ptr, int arg);
extern int func_ov002_02209eec(void *p);
extern int func_ov002_022088cc(void *);
extern int func_ov002_022088bc(void *);
extern int func_ov002_022088ac(void *);
extern int func_ov002_0220889c(void *);

int func_ov144_02299ac4(unsigned char *self, unsigned int cmd)
{
    if (cmd <= 8) {
        short k = *(short *) (self + 0xb6);
        if (func_ov144_02299b48(self, cmd + k)) {
            func_0200467c(0x29);
        }
        return 0;
    } else {
        switch (cmd - 9) {
            case 0:
                func_ov144_0229a798(self);
                return 1;
            case 2:
                return func_ov144_0229a71c(self);
            case 3:
                return func_ov144_0229a5f4(self);
            case 4:
                func_ov144_0229a5bc(self);
                return 1;
            case 1:
                func_ov002_0220a574(self + 0x128);
                func_ov002_0220a4bc((void *) ((char *) self + 0x128));
                func_ov002_02208098(self, 4);
                return 1;
        }
        return 0;
    }
}

int func_ov144_02299a30(struct UnkStruct_02299a30 *self, int x, int y)
{
    if (func_ov002_0220a784(&self->unk_170, 6) != 0) {
        return 9;
    }

    if ((x >= 0x10 && x <= 0x30 && y >= 0x20 && y <= 0x40)) {
        return 0xb;
    }

    if ((x >= 0x10 && x <= 0x30 && y >= 0x78 && y <= 0x88)) {
        return 0xc;
    }

    if ((x >= 0x10 && x <= 0x30 && y >= 0x60 && y <= 0x70)) {
        return 0xd;
    }

    if (x >= 0x40 && x <= 0xc0 && y >= 0x18 && y < 0x98) {
        int res = (y - (0x18 - (self->unk_A0 & 0xf))) >> 4;
        if (res >= self->unk_B8) {
            goto fail;
        }
        return (unsigned char) res;
    }
fail:
    return 0xe;
}

void func_ov144_02299a00(char *obj)
{
    int val = func_ov002_02209eec(obj + 0xc4);
    if (val < 76) {
        obj[0xc1] = 11;
    } else if (val < 116) {
        obj[0xc1] = 13;
    } else {
        obj[0xc1] = 12;
    }
}

int func_ov144_02299968(struct UnkStruct_02299968 *s)
{
    int n;
    int v;
    int tmp;
    int x;

    n = s->d;
    if (n == 0) {
        return 0;
    }
    if (n > 9) {
        n = 9;
    }

    v = func_ov002_02209eec((void *) (&s->q));
    if (v < 0x20) {
        v = 0x20;
    }
    if (v >= 0xA0) {
        v = 0x9F;
    }

    tmp = s->p & 0xF;
    x = (v - (0x20 - tmp)) >> 4;
    if (x >= n) {
        x = n - 1;
    }
    s->b = (unsigned char) x;

    if (tmp != 0) {
        if (x == 0) {
            s->p -= (unsigned int) tmp;
        } else if (x == n - 1) {
            s->b = (unsigned char) (s->b - 1);
            s->p += 0x10u - (s->p & 0xF);
        }
    }

    return 1;
}

void func_ov144_0229993c(UnkStruct_0229993c *self)
{
    if (func_ov144_02299968((struct UnkStruct_02299968 *) self) == 0) {
        if (self->unk_A4 > 0) {
            self->unk_C1 = 10;
        } else {
            self->unk_C1 = 9;
        }
    }
}

void func_ov144_02299924(int arg)
{
    if (func_ov144_02299968((struct UnkStruct_02299968 *) arg) == 0) {
        func_ov144_02299a00((char *) arg);
    }
}

int func_ov144_022996d4(UnkStruct_022996d4 *self, void *pad)
{
    unsigned char old = self->unk_C1;

    if (pad == 0) {
        return 0;
    }

    if (old <= 8) {
        if (func_ov002_022088ac(pad)) {
            func_ov144_02299a00((char *) self);
        } else if (func_ov002_0220889c(pad)) {
            if (self->unk_A4 > 0) {
                self->unk_C1 = 10;
            } else {
                self->unk_C1 = 9;
            }
        } else if (func_ov002_022088cc(pad)) {
            if (self->unk_C1 != 0) {
                self->unk_C1 = self->unk_C1 - 1;
                if (self->unk_C1 == 0) {
                    int t = self->unk_A0 & 0xf;
                    if (t != 0) {
                        self->unk_A0 = self->unk_A0 - t;
                    }
                }
            } else {
                if (self->unk_A0 >= 0x10) {
                    self->unk_A0 = self->unk_A0 - 0x10;
                    return 1;
                }
            }
        } else if (func_ov002_022088bc(pad)) {
            if (self->unk_A4 == 0) {
                if (self->unk_C1 < self->unk_B8 - 1) {
                    self->unk_C1 = self->unk_C1 + 1;
                }
            } else {
                if (self->unk_C1 < 7) {
                    self->unk_C1 = self->unk_C1 + 1;
                } else {
                    int a = self->unk_A0;
                    int t = a & 0xf;
                    if (t != 0) {
                        self->unk_A0 = self->unk_A0 + (0x10 - t);
                        return 1;
                    }
                    if (a <= self->unk_A4 - 0x10) {
                        self->unk_A0 = self->unk_A0 + 0x10;
                        return 1;
                    }
                }
            }
        }
    }

    switch (self->unk_C1) {
        case 9:
            if (func_ov002_022088ac(pad)) {
                func_ov144_02299924((int) self);
            } else if (func_ov002_022088cc(pad)) {
                if (self->unk_A4 > 0) {
                    self->unk_C1 = 10;
                }
            }
            break;
        case 10:
            if (func_ov002_022088bc(pad)) {
                self->unk_C1 = 9;
            } else if (func_ov002_022088ac(pad)) {
                func_ov144_02299924((int) self);
            }
            break;
        case 11:
            if (func_ov002_022088bc(pad)) {
                self->unk_C1 = 13;
            } else if (func_ov002_0220889c(pad)) {
                func_ov144_0229993c((UnkStruct_0229993c *) self);
            }
            break;
        case 12:
            if (func_ov002_022088cc(pad)) {
                self->unk_C1 = 13;
            } else if (func_ov002_0220889c(pad)) {
                func_ov144_0229993c((UnkStruct_0229993c *) self);
            }
            break;
        case 13:
            if (func_ov002_022088cc(pad)) {
                self->unk_C1 = 11;
            } else if (func_ov002_022088bc(pad)) {
                self->unk_C1 = 12;
            } else if (func_ov002_0220889c(pad)) {
                func_ov144_0229993c((UnkStruct_0229993c *) self);
            }
            break;
    }

    if (old != self->unk_C1) {
        return 1;
    }
    return 0;
}
