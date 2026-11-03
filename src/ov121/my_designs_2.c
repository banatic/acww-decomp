/* my_designs_2: 18 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_0229a170 @ 0x0229a170, 0x20 bytes, Thumb
 * func_ov121_0229a150 @ 0x0229a150, 0x20 bytes, Thumb
 * func_ov121_0229a130 @ 0x0229a130, 0x20 bytes, Thumb
 * func_ov121_0229a108 @ 0x0229a108, 0x28 bytes, Thumb
 * func_ov121_0229a0e0 @ 0x0229a0e0, 0x28 bytes, Thumb
 * func_ov121_0229a0b4 @ 0x0229a0b4, 0x2c bytes, Thumb
 * func_ov121_0229a074 @ 0x0229a074, 0x3e bytes, Thumb
 * func_ov121_0229a038 @ 0x0229a038, 0x3c bytes, Thumb
 * func_ov121_0229a00c @ 0x0229a00c, 0x2a bytes, Thumb
 * func_ov121_02299fe0 @ 0x02299fe0, 0x2a bytes, Thumb
 * func_ov121_02299fc8 @ 0x02299fc8, 0x16 bytes, Thumb
 * func_ov121_02299e80 @ 0x02299e80, 0x148 bytes, Thumb
 * func_ov121_02299e54 @ 0x02299e54, 0x2c bytes, Thumb
 * func_ov121_02299e34 @ 0x02299e34, 0x20 bytes, Thumb
 * func_ov121_02299d10 @ 0x02299d10, 0x124 bytes, Thumb
 * func_ov121_02299ccc @ 0x02299ccc, 0x44 bytes, Thumb
 * func_ov121_02299c88 @ 0x02299c88, 0x44 bytes, Thumb
 * func_ov121_02299c10 @ 0x02299c10, 0x78 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229a0b4 {
    char pad_00[0xa4];
    unsigned short unk_A4;
    unsigned short unk_A6;
};

struct UnkStruct_02299fc8 {
    unsigned char pad_00[0xb1];
    unsigned char data;
};

typedef struct ObjTag {
    unsigned char pad_00[0xb1];
    unsigned char state;
} UnkStruct_02299e80;

typedef struct {
    char pad_00[0xb1];
    volatile u8 unk_B1;
} UnkStruct_02299d10;

typedef struct {
    char pad_00[0xb1];
    unsigned char flag;
} UnkStruct_02299ccc;

typedef struct {
    unsigned char pad_00[0xb5];
    unsigned char b5;
    unsigned char b6;
} UnkStruct_02299c88;

typedef struct UnkStruct_02299c10 {
    unsigned char pad_00[0xB5];
    unsigned char unk_B5;
    unsigned char unk_B6;
} UnkStruct_02299c10;

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern void func_ov002_0220a164(void *);
extern void func_ov002_0220a374(void *p, int n);
extern void func_ov121_02299a3c(void *p, int n);
extern int func_ov002_02209f3c(void *);
extern int func_ov002_02209f14(void *);
extern void func_ov121_02299a4c(unsigned short *object, unsigned short mask);
extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088bc(int);
extern int func_ov121_02299a5c(UnkStruct_02299e80 *, int);
extern int func_ov002_02209f00(void *ptr);
extern int func_ov090_02298f84(int val);
extern void func_ov002_0220a254(void *ptr);
extern unsigned char data_ov121_0229c210[];
extern void func_ov002_0220a2b4(void *p);
extern int func_ov002_022088cc(void *p);
extern void func_ov121_0229af00(UnkStruct_02299c88 *p, unsigned char arg1, int arg2);

void func_ov121_0229a170(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x3a8);
    func_ov002_02208098(self, 7);
}

void func_ov121_0229a150(void *arg0)
{
    func_ov002_0220a164((char *) arg0 + 0x3a8);
    func_ov002_02208098(arg0, 8);
}

void func_ov121_0229a130(void *self)
{
    func_ov002_0220a374((char *) self + 0x3a8, 4);
    func_ov002_02208098(self, 9);
}

void func_ov121_0229a108(void *p)
{
    func_ov002_0220a374((char *) p + 0x3a8, 5);
    func_ov121_02299a3c(p, 0x80);
    func_ov002_02208098(p, 0xb);
}

void func_ov121_0229a0e0(void *self)
{
    func_ov002_0220a374((char *) self + 0x3a8, 5);
    func_ov121_02299a4c((unsigned short *) self, 0x80);
    func_ov002_02208098(self, 0xb);
}

void func_ov121_0229a0b4(struct UnkStruct_0229a0b4 *self)
{
    int tmp;
    int tmp2;

    tmp = func_ov002_02209f3c((char *) self + 0x3a8);
    self->unk_A4 = (unsigned short) (tmp - 3);
    tmp2 = func_ov002_02209f14((char *) self + 0x3a8);
    self->unk_A6 = (unsigned short) (tmp2 + 9);
}

int func_ov121_0229a074(char *self, unsigned int lo, unsigned int hi)
{
    unsigned char val = *(unsigned char *) (self + 0xb1);
    if (val >= lo && val <= hi) {
        if (val == hi) {
            func_ov121_02299a4c((unsigned short *) self, 0x40);
            *(unsigned char *) (self + 0xb1) = lo;
        } else {
            *(unsigned char *) (self + 0xb1) = *(volatile unsigned char *) (self + 0xb1) + 1;
        }
        return 1;
    }
    return 0;
}

int func_ov121_0229a038(char *self, unsigned int lo, unsigned int hi)
{
    unsigned char val = *(unsigned char *) (self + 0xb1);
    if (val >= lo && val <= hi) {
        if (val == lo) {
            *(unsigned char *) (self + 0xb1) = hi;
            func_ov121_02299a4c((unsigned short *) self, 0x20);
        } else {
            *(unsigned char *) (self + 0xb1) = *(volatile unsigned char *) (self + 0xb1) - 1;
        }
        return 1;
    }
    return 0;
}

int func_ov121_0229a00c(char *self, unsigned int lo, unsigned int hi, int r3)
{
    unsigned char val = *(unsigned char *) (self + 0xb1);
    if (val >= lo && val <= hi) {
        *(unsigned char *) (self + 0xb1) = *(volatile unsigned char *) (self + 0xb1) + (r3 - lo);
        return 1;
    }
    return 0;
}

int func_ov121_02299fe0(char *self, unsigned int lo, unsigned int hi, int r3)
{
    unsigned char val = *(unsigned char *) (self + 0xb1);
    if (val >= lo && val <= hi) {
        *(unsigned char *) (self + 0xb1) = *(volatile unsigned char *) (self + 0xb1) + (r3 - lo);
        return 1;
    }
    return 0;
}

int func_ov121_02299fc8(const struct UnkStruct_02299fc8 *p)
{
    unsigned char c = p->data;
    if (c >= 0x10 && c <= 0x17) {
        return c - 0x10;
    }
    return -1;
}

int func_ov121_02299e80(UnkStruct_02299e80 *self, int p1, int p2)
{
    if (func_ov002_022088ac(p1) != 0) {
        if (self->state == 8) {
            self->state = 7;
            func_ov121_02299a4c((unsigned short *) self, 0x20);
            goto tail;
        }
        if (self->state == 4 && p2 != 0) {
            self->state = 8;
            goto tail;
        }
        if (func_ov121_0229a038((char *) self, 0, 3) != 0) {
            goto tail;
        }
        if (func_ov121_0229a038((char *) self, 4, 7) != 0) {
            goto tail;
        }
        if (func_ov121_0229a038((char *) self, 9, 11) != 0) {
            goto tail;
        }
        if (func_ov121_0229a038((char *) self, 12, 15) != 0) {
            goto tail;
        }

        {
            unsigned char st = self->state;
            if (st > 0x10 && st <= 0x17) {
                (*(volatile unsigned char *) &self->state) = (unsigned char) ((*(volatile unsigned char *) &self->state) - 1);
            }
        }
        goto tail;
    } else {
        if (func_ov002_0220889c(p1) != 0) {
            if (self->state == 8) {
                self->state = 4;
                goto tail;
            }
            if (self->state == 7 && p2 != 0) {
                self->state = 8;
                func_ov121_02299a4c((unsigned short *) self, 0x40);
                goto tail;
            }
            if (self->state == 0xb && func_ov002_022088bc(p1) != 0) {
                self->state = 0xf;
                return 1;
            }
            if (func_ov121_0229a074((char *) self, 0, 3) != 0) {
                goto tail;
            }
            if (func_ov121_0229a074((char *) self, 4, 7) != 0) {
                goto tail;
            }
            if (func_ov121_0229a074((char *) self, 9, 11) != 0) {
                goto tail;
            }
            if (func_ov121_0229a074((char *) self, 12, 15) != 0) {
                goto tail;
            }

            {
                unsigned char st = self->state;
                if (st >= 0x10 && st < 0x17) {
                    (*(volatile unsigned char *) &self->state) =
                        (unsigned char) ((*(volatile unsigned char *) &self->state) + 1);
                }
            }
            goto tail;
        }
    }
tail:
    return func_ov121_02299a5c(self, 0x60);
}

void func_ov121_02299e54(char *self)
{
    self[0xb1] = (char) (func_ov090_02298f84(func_ov002_02209f00(self + 0x3a8)) + 0x10);
    func_ov002_0220a254(self + 0x3a8);
}

void func_ov121_02299e34(unsigned char *p, int idx)
{
    p[0xb1] = data_ov121_0229c210[idx];
    func_ov002_0220a2b4(p + 0x3a8);
}

void func_ov121_02299d10(UnkStruct_02299d10 *self, void *pad, int flag)
{
    u8 s;
    int r;

    if (func_ov002_022088cc(pad) != 0) {
        s = self->unk_B1;
        if (s == 8) {
            self->unk_B1 = 0;
            return;
        }
        if (s <= 3) {
            if (flag != 0) {
                self->unk_B1 = self->unk_B1 + 0xc;
            } else {
                func_ov121_02299e54((char *) self);
            }
            return;
        }
        if (func_ov121_0229a00c((char *) self, 4, 7, 0) != 0) {
            return;
        }
        s = self->unk_B1;
        if (s >= 9 && s <= 0xb) {
            if (flag != 0) {
                return;
            }
            func_ov121_02299e54((char *) self);
            return;
        }
        if (s < 0xc || s > 0xf) {
            return;
        }
        if (func_ov002_0220889c((int) pad) != 0) {
            self->unk_B1 = self->unk_B1 - 1;
        }
        self->unk_B1 = self->unk_B1 - 3;
        if (self->unk_B1 > 0xb) {
            self->unk_B1 = 0xb;
        }
        return;
    }
    if (func_ov002_022088bc((int) pad) == 0) {
        return;
    }
    if (func_ov121_02299fe0((char *) self, 0, 3, 4) != 0) {
        return;
    }
    r = func_ov121_02299fc8((const struct UnkStruct_02299fc8 *) self);
    if (r != -1) {
        func_ov121_02299e34((unsigned char *) self, r);
        return;
    }
    if (func_ov121_02299fe0((char *) self, 0xc, 0xf, 0) != 0) {
        return;
    }
    s = self->unk_B1;
    if (s < 9 || s > 0xb) {
        return;
    }
    if (func_ov002_022088ac((int) pad) != 0) {
        self->unk_B1 = self->unk_B1 + 1;
    }
    self->unk_B1 = self->unk_B1 + 3;
}

int func_ov121_02299ccc(UnkStruct_02299ccc *self, int arg1, int arg2)
{
    unsigned char old, new_val;
    old = self->flag;
    func_ov121_02299a3c((void *) self, 0x60);
    if (func_ov121_02299e80((UnkStruct_02299e80 *) self, arg1, arg2) == 0) {
        func_ov121_02299d10((UnkStruct_02299d10 *) self, (void *) arg1, arg2);
    }
    new_val = self->flag;
    return old != new_val;
}

void func_ov121_02299c88(UnkStruct_02299c88 *p, unsigned char q)
{
    if (func_ov121_02299a5c((UnkStruct_02299e80 *) p, 0x200) != 0) {
        func_ov121_0229af00(p, p->b5, 2);
    }
    p->b5 = q;
    p->b6 = 15;
    func_ov121_02299a4c((unsigned short *) p, 0x200);
}

void func_ov121_02299c10(UnkStruct_02299c10 *p)
{
    if (func_ov121_02299a5c((UnkStruct_02299e80 *) p, 0x200)) {
        if (p->unk_B6) {
            p->unk_B6--;
            switch (p->unk_B6 % 5) {
                case 0:
                    func_ov121_0229af00((UnkStruct_02299c88 *) p, p->unk_B5, 2);
                    break;
                case 3:
                    func_ov121_0229af00((UnkStruct_02299c88 *) p, p->unk_B5, 6);
                    break;
            }
        } else {
            func_ov121_02299a3c((void *) p, 0x200);
            func_ov121_0229af00((UnkStruct_02299c88 *) p, p->unk_B5, 2);
        }
    }
}
