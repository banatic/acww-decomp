/* astro_talk: 13 functions, module ov046
 * mwccarm 1.2/base -O4,s
 * func_ov046_02260aa8 @ 0x02260aa8, 0x14 bytes, Thumb
 * func_ov046_02260914 @ 0x02260914, 0x194 bytes, Thumb
 * func_ov046_022608e4 @ 0x022608e4, 0x30 bytes, Thumb
 * func_ov046_022608a4 @ 0x022608a4, 0x3e bytes, Thumb
 * func_ov046_0226086c @ 0x0226086c, 0x38 bytes, Thumb
 * func_ov046_022607f0 @ 0x022607f0, 0x7c bytes, Thumb
 * func_ov046_0226077c @ 0x0226077c, 0x74 bytes, Thumb
 * func_ov046_02260720 @ 0x02260720, 0x5c bytes, Thumb
 * func_ov046_022606f4 @ 0x022606f4, 0x2c bytes, Thumb
 * func_ov046_022606e0 @ 0x022606e0, 0x14 bytes, Thumb
 * func_ov046_0226068c @ 0x0226068c, 0x54 bytes, Thumb
 * func_ov046_02260664 @ 0x02260664, 0x28 bytes, Thumb
 * func_ov046_02260644 @ 0x02260644, 0x1e bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 kind;
    u8 pad_01[3];
    int unk_04;
    int unk_08;
} Msg;

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x21];
    void *unk_40;
    char pad_44[0xc0 - 0x44];
    int unk_C0;
    u8 unk_C4;
    u8 unk_C5;
    u8 unk_C6;
    char pad_C7[1];
    int unk_C8[5];
    int unk_DC;
} Obj_ov046_0226204c;

typedef struct {
    char pad_00[0xdc];
    int unk_DC;
} UnkStruct_022608e4;

struct UnkStruct_022608a4 {
    char pad_00[0xc0];
    int c0;
    char c4;
    char c5;
    char pad_C6[0x16];
    int dc;
};

typedef struct {
    char pad_00[0xdc];
    int unk_DC;
} UnkStruct_0226086c;

struct UnkStruct_022607f0 {
    char pad_00[0xc4];
    unsigned char unk_C4;
    unsigned char unk_C5;
    unsigned char unk_C6;
    char pad_C7[0x15];
    int unk_DC;
};

typedef struct {
    unsigned char pad_00[0x40];
    int unk_40;
    unsigned char pad_44[0x7c];
    int unk_C0;
    unsigned char unk_C4;
    unsigned char unk_C5;
    unsigned char pad_C6[0x16];
    int unk_DC;
} UnkStruct_0226077c;

struct Func_ov046_022606f4_Struct {
    char pad_00[0xdc];
    int unk_DC;
};

typedef struct {
    char pad_00[0xC4];
    unsigned char unk_C4;
    unsigned char unk_C5;
    unsigned char unk_C6;
    char pad_C7[0xDC - 0xC7];
    int unk_DC;
} UnkStruct_0226068c;

extern char data_ov046_02262420[]; // data_02262420
extern void *func_020b1954(char *b);
extern int func_020b1394(char *b, int a);
extern void func_02068404(void *h, int a, char *b);
extern void func_020b12e0(int *d, int a);
extern void func_02015ed0(Obj_ov046_0226204c *self, int a, int b);
extern void func_02015ea0(Obj_ov046_0226204c *self, int a, int b);
extern void func_02015fb0(Obj_ov046_0226204c *self, int a, int b, int c, int d, int e);
extern int func_020683e4(void *h, int a, u8 *m, char *t);
extern void func_020157b0(Obj_ov046_0226204c *self, int a, int b, int c);
extern int func_02015828(Obj_ov046_0226204c *self, int a);
extern void func_ov046_02261508(Obj_ov046_0226204c *self, int a); // func_02261508
extern void *func_020b193c(char *b);
extern int func_ov046_022610fc(Obj_ov046_0226204c *self); // func_022610fc
extern int func_020b1558(void);
extern void func_020b14c0(int value);

void func_ov046_02260aa8(int param1, int param2)
{
    if (param2 == 0) {
        *(int *) ((char *) param1 + 0xdc) = 9;
    } else {
        *(int *) ((char *) param1 + 0xdc) = 0x23;
    }
}

void func_ov046_02260914(Obj_ov046_0226204c *self, int idx)
{
    Msg m;
    char buf[0x24];
    void *h;
    int mode;
    int v;
    int n;
    int k;

    h = self->unk_40;
    self->unk_C0 = self->unk_C8[idx];
    if (self->unk_C0 < 0) {
        goto neg;
    }
    func_020b1954(buf);
    func_020b1394(buf, self->unk_C0);
    func_02068404(self->unk_40, 6, buf);
    mode = self->unk_C6;
    if (mode == 0) {
        self->unk_DC = 0x19;
        self->unk_C4 = 0;
    } else if (mode == 1) {
        m.unk_04 = 0;
        m.unk_08 = 0;
        func_020b12e0(&m.unk_04, self->unk_C0);
        func_02015ed0(self, ((u8 *) &m)[8], 2);
        func_02015ea0(self, ((u8 *) &m)[7], 3);
        func_02015fb0(self, ((u8 *) &m)[5], 5, 2, 0, 0);
        v = ((u8 *) &m)[6];
        n = 0x19;
        if (v > 0xc) {
            n = 0x1a;
            v = v - 0xc;
        }
        m.kind = (u8) n;
        func_020683e4(h, 8, (u8 *) &m, data_ov046_02262420);
        func_02015fb0(self, v, 4, 2, 0, 0);
        self->unk_DC = 0x17;
    } else if (mode == 2) {
        func_020157b0(self, 0x2e, (u8) self->unk_C0, 0);
        func_02015828(self, 3);
        func_ov046_02261508(self, 3);
    }
    self->unk_C6 = 0;
    func_020b193c(buf);
    return;
neg:
    if (self->unk_C5 == 0) {
        self->unk_DC = func_ov046_022610fc(self);
        if ((u8) (self->unk_C6 + 0xff) <= 1) {
            if (func_020b1558() < 0x10) {
                if (self->unk_C6 == 1) {
                    self->unk_DC = 0x16;
                } else {
                    self->unk_DC = 0x1d;
                }
            }
        }
        self->unk_C6 = 0;
        return;
    }
    k = self->unk_1E;
    if (k == 0x15) {
        goto set3f;
    }
    if (k == 0x1e) {
        goto set3f;
    }
    if (k == 0x1f) {
    set3f:
        self->unk_DC = 0x3f;
        return;
    }
    if (k == 0x3f) {
        self->unk_DC = 0x40;
        return;
    }
    if (k == 0x40) {
        self->unk_DC = 0x41;
    }
    return;
}

void func_ov046_022608e4(UnkStruct_022608e4 *self, int flag)
{
    if (flag == 0) {
        self->unk_DC = 7;
    } else {
        if (func_020b1558() < 16) {
            self->unk_DC = 42;
        } else {
            self->unk_DC = func_ov046_022610fc((Obj_ov046_0226204c *) self);
        }
    }
}

void func_ov046_022608a4(struct UnkStruct_022608a4 *self, int flag)
{
    int x;

    if (flag == 0) {
        x = self->c0;
        if (x < 0) {
        } else {
            func_020b14c0(x);
        }
        self->c5 = (char) (16 - func_020b1558());
        self->c4 = 0;
        self->dc = 0x21;
    } else {
        self->dc = 9;
    }
}

void func_ov046_0226086c(UnkStruct_0226086c *p, int r1)
{
    if (r1 == 0) {
        int ret = func_020b1558();
        if (ret < 0x10) {
            p->unk_DC = 0x18;
        } else {
            p->unk_DC = 7;
        }
    } else if (r1 == 1) {
        p->unk_DC = 0x30;
    } else {
        p->unk_DC = 2;
    }
}

void func_ov046_022607f0(struct UnkStruct_022607f0 *a, int b)
{
    a->unk_C5 = 0x10 - func_020b1558();
    a->unk_C4 = 0;
    if (b == 0) {
        if (func_020b1558() < 0x10) {
            a->unk_DC = 0x18;
        } else {
            a->unk_DC = 7;
        }
    } else if (b == 1) {
        a->unk_DC = 0x35;
    } else if (b == 2) {
        a->unk_C5 = 0x10 - func_020b1558();
        a->unk_C4 = 0;
        a->unk_DC = 0x1f;
        a->unk_C6 = 0;
    } else {
        a->unk_DC = 2;
    }
}

void func_ov046_0226077c(UnkStruct_0226077c *obj, int flag)
{
    unsigned char buf[32];

    obj->unk_C4 = 0;
    if (flag == 0) {
        if (obj->unk_C0 >= 0) {
            func_020b1954((char *) buf);
            func_020b1394((char *) buf, obj->unk_C0);
            func_02068404((void *) obj->unk_40, 6, (char *) buf);
            func_020b14c0(obj->unk_C0);
            func_020b193c((char *) buf);
        }
        obj->unk_C5 = 16 - func_020b1558();
        obj->unk_C4 = 0;
        obj->unk_DC = 27;
    } else {
        obj->unk_DC = func_ov046_022610fc((Obj_ov046_0226204c *) obj);
    }
}

void func_ov046_02260720(unsigned char *r5, int r4)
{
    unsigned char *p;
    int t;

    t = 0x10 - func_020b1558();
    r5[0xc5] = (unsigned char) t;
    r5[0xc4] = 0;

    if (r4 == 0) {
        if (func_020b1558() == 0) {
            *(int *) (r5 + 0xdc) = 0x3e;
        } else {
            *(int *) (r5 + 0xdc) = 7;
        }
    } else if (r4 == 1) {
        r5[0xc6] = 2;
        *(int *) (r5 + 0xdc) = 0x1e;
    } else {
        *(int *) (r5 + 0xdc) = 0xc;
    }
}

void func_ov046_022606f4(struct Func_ov046_022606f4_Struct *param, int cond)
{
    if (cond == 0) {
        if (func_020b1558() < 0x10) {
            param->unk_DC = 0x35;
        } else {
            param->unk_DC = 0x30;
        }
    } else {
        param->unk_DC = 0x2;
    }
}

void func_ov046_022606e0(void *r0, int r1)
{
    if (r1 == 0) {
        *(int *) ((char *) r0 + 0xdc) = 7;
    } else {
        *(int *) ((char *) r0 + 0xdc) = 0xc;
    }
}

void func_ov046_0226068c(UnkStruct_0226068c *p, int cond)
{
    int x = func_020b1558();
    p->unk_C5 = 0x10 - x;
    p->unk_C4 = 0;
    if (cond == 0) {
        p->unk_C6 = 2;
        p->unk_DC = 0x1e;
    } else {
        int y = func_020b1558();
        if (y < 0x10) {
            p->unk_DC = 0x25;
        } else {
            p->unk_DC = func_ov046_022610fc((Obj_ov046_0226204c *) p);
        }
    }
}

void func_ov046_02260664(void *arg0, int arg1)
{
    if (arg1 == 0) {
        *(int *) ((char *) arg0 + 0xdc) = 0x30;
    } else if (arg1 == 1) {
        *(unsigned char *) ((char *) arg0 + 0xc6) = 1;
        *(int *) ((char *) arg0 + 0xdc) = 0x15;
    } else {
        *(int *) ((char *) arg0 + 0xdc) = 0x16;
    }
}

void func_ov046_02260644(int *param0, int param1)
{
    if (param1 == 0) {
        param0[55] = 0x3b;
    } else {
        param0[55] = func_ov046_022610fc((Obj_ov046_0226204c *) ((unsigned char *) param0));
    }
}
