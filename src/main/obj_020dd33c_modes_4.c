/* obj_020dd33c_modes_4: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02059270 @ 0x02059270, 0xc bytes, Thumb
 * func_0205915c @ 0x0205915c, 0x114 bytes, Thumb
 * func_020590f8 @ 0x020590f8, 0x62 bytes, Thumb
 * func_02058ffc @ 0x02058ffc, 0xfc bytes, Thumb
 * func_02058f54 @ 0x02058f54, 0xa6 bytes, Thumb
 * func_02058f0c @ 0x02058f0c, 0x46 bytes, Thumb
 * func_02058eec @ 0x02058eec, 0x20 bytes, Thumb
 * func_02058e0c @ 0x02058e0c, 0xe0 bytes, Thumb
 * func_02058d2c @ 0x02058d2c, 0xe0 bytes, Thumb
 * func_02058d28 @ 0x02058d28, 0x2 bytes, Thumb
 * func_02058d24 @ 0x02058d24, 0x2 bytes, Thumb
 * func_02058cdc @ 0x02058cdc, 0x46 bytes, Thumb
 * func_02058c90 @ 0x02058c90, 0x4a bytes, Thumb
 * func_02058c60 @ 0x02058c60, 0x2e bytes, Thumb
 * func_02058c2c @ 0x02058c2c, 0x32 bytes, Thumb
 * func_02058be0 @ 0x02058be0, 0x4c bytes, Thumb
 * func_02058b5c @ 0x02058b5c, 0x84 bytes, Thumb
 * func_02058ac8 @ 0x02058ac8, 0x94 bytes, Thumb
 */

#include "types.h"

struct Vec {
    int x, y, z;
};

struct This {
    u8 pad_00[0x50];
    u16 unk_50;
    u8 pad_52[0x60 - 0x52];
    int unk_60, unk_64, unk_68;
    int unk_6C, unk_70, unk_74;
    u8 pad_78[0x90 - 0x78];
    int unk_90, unk_94, unk_98;
    int unk_9C, unk_A0, unk_A4;
    u8 pad_A8[0xcc - 0xa8];
    void *unk_CC;
    u8 pad_D0[0xd6 - 0xd0];
    u16 unk_D6;
};

struct UnkStruct_020590f8 {
    char pad_00[0x60];
    char unk_60[4];
    char unk_64[4];
    char unk_68[4];
    int unk_6C;
    int unk_70;
    int unk_74;
    char pad_78[0x18];
    int unk_90;
    int unk_94;
    int unk_98;
    char pad_9C[0x3a];
    unsigned short unk_D6;
};

typedef struct UnkStruct_02058ffc {
    u8 pad_00[0x50];
    u16 unk_50;
    u8 pad_52[0x0e];
    u32 unk_60;
    u8 pad_64[0x04]; // extra 4 bytes to align unk_68 at 0x68
    u32 unk_68;
    u32 unk_6C;
    u32 unk_70;
    u32 unk_74;
    u8 pad_78[0x18];
    u32 unk_90;
    u32 unk_94;
    u32 unk_98;
    u32 unk_9C;
    u32 unk_A0;
    u32 unk_A4;
    u8 pad_A8[0x24];
    void *unk_CC;
    u8 pad_D0[0x06];
    u16 unk_D6;
} UnkStruct_02058ffc;

typedef struct {
    char pad_00[0x60];
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
    int unk_74;
    char pad_78[0x84 - 0x78];
    int unk_84;
    int unk_88;
    int unk_8C;
    int unk_90;
    char pad_94[0x98 - 0x94];
    int unk_98;
    char pad_9C[0xd6 - 0x9c];
    u16 count;
} UnkStruct_02058f54;

struct UnkCC {
    u8 pad_00[0x8e];
    s16 unk_8E;
};

struct Unit {
    u8 pad_00[0x6c];
    u32 unk_6C;
    u32 unk_70;
    u32 unk_74;
    u32 unk_78;
    u32 unk_7C;
    u32 unk_80;
    s32 unk_84;
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
    u8 pad_9C[0x0c];
    s32 unk_A8;
    u8 pad_AC[0x14];
    s32 unk_C0;
    u8 pad_C4[0x8];
    struct UnkCC *unk_CC;
    u8 pad_D0[0x4];
    u8 unk_D4;
    u8 pad_D5[0x1];
    u16 unk_D6;
};

struct UnkStruct_02058d2c {
    u8 pad_00[0x8e];
    s16 unk_8E;
};

typedef struct UnkStruct_02058d2c_2 {
    u8 pad_00[0x60];
    u8 unk_60[0x18];
    int unk_78;
    int unk_7C;
    int unk_80;
    int unk_84;
    int unk_88;
    int unk_8C;
    int unk_90;
    int unk_94;
    int unk_98;
    u8 pad_9C[0xa8 - 0x9c];
    int unk_A8;
    int unk_AC;
    int unk_B0;
    u8 pad_B4[0xc0 - 0xb4];
    unsigned int unk_C0;
    u8 pad_C4[0xcc - 0xc4];
    struct UnkStruct_02058d2c *unk_CC;
    u8 pad_D0[0xd6 - 0xd0];
    u16 unk_D6;
} UnkStruct_02058d2c_2;

typedef struct UnkStruct_02058cdc {
    unsigned char pad_00[12];
    int unk_0C;
    int unk_10;
    int unk_14;
} UnkStruct_02058cdc;

typedef struct UnkStruct_02058cdc_2 {
    unsigned char pad_00[0x60];
    int unk_60;
    unsigned char pad_64[0x20];
    int unk_84;
    int unk_88;
    int unk_8C;
    unsigned char pad_90[0x46];
    short unk_D6;
} UnkStruct_02058cdc_2;

typedef struct {
    char pad_00[0x60];
    char unk_60;
    char pad_61[0x84 - 0x60 - 1];
    char unk_84;
    char pad_85[0xD6 - 0x84 - 1];
    unsigned short unk_D6;
} UnkStruct_02058c90;

typedef struct {
    char pad_00[0x54];
    unsigned int unk_54;
    char pad_58[8];
    char unk_60;
    char pad_61[0x75];
    unsigned short unk_D6;
} UnkStruct_02058c60;

typedef struct {
    char pad_00[0xD6];
    unsigned short unk_D6;
} UnkStruct_02058c2c;

typedef struct {
    char pad_00[12];
    int a;
    int b;
    int c;
} UnkStruct_02058be0;

typedef struct {
    char pad_00[0x60];
    char src[0x24];
    int unk_84;
    int unk_88;
    int unk_8C;
    char pad_90[0x44];
    char d4;
    char pad_D5;
    short d6;
} UnkStruct_02058be0_2;

struct UnkStruct_02058b5c {
    char pad_00[0x60];
    char unk_60[0x24];
    char unk_84[0x24];
    unsigned int unk_A8;
    char pad_AC[0x14];
    int unk_C0;
    char pad_C4[0x10];
    unsigned char unk_D4;
    char pad_D5;
    unsigned short unk_D6;
};

typedef struct UnkStruct_02058ac8 {
    unsigned char pad_00[0x60];
    unsigned char unk_60[0x24];
    unsigned char unk_84[0x24];
    unsigned int unk_A8;
    unsigned int unk_AC;
    unsigned int unk_B0;
    unsigned char pad_B4[0xC];
    unsigned int unk_C0;
    unsigned char pad_C4[0x10];
    unsigned char unk_D4;
    unsigned char pad_D5;
    unsigned short unk_D6;
} UnkStruct_02058ac8;

extern struct Vec data_021c939c;
extern int func_0204fd3c(int);
extern void *func_02059cc4(void *, int);
extern void func_02059598(struct Vec *, struct This *, int);
extern void func_020595fc(struct This *, int *, struct Vec *, int);
extern int func_020e895c(void *, int, int);
extern void func_02059674(void *, int);
extern u32 data_021c93e4[3];
extern int func_02059cf8(void *p, int x);
extern void VEC_Add(void *a, void *b, void *c);
extern void func_0205967c(void *p, void *buf);
extern void func_020eaca0(void *out, void *src, void *tmp);
extern void func_020ea6e0(s32 *dst, s16 val);
extern int func_02091254(int, void *, int, int);
extern unsigned char data_020cbaec[];
extern unsigned char data_021c933c[];

void func_02059270(int p0)
{
    func_02059674((void *) p0, 1);
}

void func_0205915c(struct This *t)
{
    struct Vec a;
    struct Vec b;
    struct Vec c;
    int ok;
    u16 h;
    int tx, ty, tz;

    func_0205967c((void *) t, (void *) (&a));
    ok = 0;
    t->unk_9C = 0;
    t->unk_A0 = 0;
    t->unk_A4 = 0;
    b.x = data_021c939c.x;
    b.y = data_021c939c.y;
    b.z = data_021c939c.z;
    h = t->unk_50;
    if (h >= 0x12e8 && h <= 0x131f) {
        ok = 1;
    }
    if (ok) {
        VEC_Add((void *) (&b), (void *) (func_02059cc4(t->unk_CC, func_0204fd3c(h - 0x12e8))), (void *) (&b));
    }
    func_02059598(&c, t, 0);
    VEC_Add((void *) (&b), (void *) (&c), (void *) (&b));
    func_020595fc(t, &t->unk_9C, &b, 0);
    t->unk_6C = t->unk_9C;
    t->unk_70 = a.y + t->unk_A0;
    t->unk_74 = t->unk_A4;
    tz = (t->unk_74 - t->unk_68) / 2;
    if (tz < 0) {
        tz = -tz;
    }
    ty = (t->unk_70 - t->unk_64) / 2;
    if (ty < 0) {
        ty = -ty;
    }
    tx = (t->unk_6C - t->unk_60) / 2;
    if (tx < 0) {
        tx = -tx;
    }
    t->unk_90 = tx;
    t->unk_94 = ty;
    t->unk_98 = tz;
    t->unk_D6 = 0;
    func_02059674((void *) t, 1);
}

void func_020590f8(struct UnkStruct_020590f8 *self)
{
    if ((int) self->unk_D6 >= 2) {
        return;
    }

    func_020e895c(&self->unk_60, self->unk_6C, self->unk_90);
    func_020e895c(&self->unk_64, self->unk_70, self->unk_94);
    func_020e895c(&self->unk_68, self->unk_74, self->unk_98);

    self->unk_D6 += 1;

    if ((int) self->unk_D6 >= 2) {
        func_02059674(self, 0);
    }
}

void func_02058ffc(UnkStruct_02058ffc *self)
{
    u8 local0[12];
    u32 buf[3];
    u32 buf2[3];
    unsigned int flag;
    int t, delta1, delta2;

    func_0205967c((void *) self, (void *) local0);

    flag = 0;
    self->unk_9C = flag;
    self->unk_A0 = flag;
    self->unk_A4 = flag;

    buf[0] = data_021c93e4[0];
    buf[1] = data_021c93e4[1];
    buf[2] = data_021c93e4[2];

    if ((u32) self->unk_50 >= 0x12e8 && (u32) self->unk_50 <= 0x131f) {
        flag = 1;
    }

    if (flag != 0) {
        t = func_0204fd3c((int) (self->unk_50 - 0x12e8));
        t = func_02059cf8(self->unk_CC, t);
        VEC_Add(buf, (void *) t, buf);
    }

    func_02059598((struct Vec *) buf2, (struct This *) self, 0);
    VEC_Add(buf, buf2, buf);

    func_020595fc((struct This *) self, (int *) (&self->unk_9C), (struct Vec *) buf, 0);

    self->unk_6C = self->unk_9C;
    self->unk_70 = self->unk_A0;
    self->unk_74 = self->unk_A4;

    delta1 = (int) (self->unk_74 - self->unk_68) / 2;
    if (delta1 < 0) {
        delta1 = -delta1;
    }
    delta2 = (int) (self->unk_6C - self->unk_60) / 2;
    if (delta2 < 0) {
        delta2 = -delta2;
    }

    self->unk_90 = delta2;
    self->unk_94 = 0;
    self->unk_98 = delta1;
    self->unk_D6 = 0;

    func_02059674((void *) self, 1);
}

void func_02058f54(UnkStruct_02058f54 *self)
{
    int a[3];
    int b[3];

    if ((int) self->count < 9) {
        func_0205967c((void *) self, a);
        func_020e895c((void *) (&self->unk_60), self->unk_6C, self->unk_90);
        self->unk_64 = a[1] + self->unk_70;
        func_020e895c((void *) (&self->unk_68), self->unk_74, self->unk_98);
        self->count++;
        if ((int) self->count >= 9) {
            func_020eaca0((void *) b, (void *) (&self->unk_60), (void *) a);
            self->unk_84 = b[0];
            self->unk_88 = b[1];
            self->unk_8C = b[2];
            func_02059674((void *) self, 0);
        }
    } else if ((int) self->count == 9) {
        func_0205967c((void *) self, &self->unk_60);
        VEC_Add((void *) (&self->unk_60), (void *) (&self->unk_84), (void *) (&self->unk_60));
    }
}

void func_02058f0c(void *self)
{
    int tmp[3];
    int out[3];

    func_02059674(self, 0);
    func_0205967c(self, tmp);
    func_020eaca0(out, (char *) self + 0x60, tmp);

    ((int *) ((char *) self + 0x84))[0] = out[0];
    ((int *) ((char *) self + 0x88))[0] = out[1];
    ((int *) ((char *) self + 0x8c))[0] = out[2];

    *(short *) ((char *) self + 0xd6) = 0;
}

void func_02058eec(char *p)
{
    func_0205967c(p, p + 0x60);
    VEC_Add(p + 0x60, p + 0x84, p + 0x60);
}

void func_02058e0c(struct Unit *unit)
{
    int tmp1[3];
    int tmp2[3];
    int r4, r6, abs84;
    s16 val;

    unit->unk_6C = 0;
    unit->unk_70 = 0;
    unit->unk_74 = 0;
    func_0205967c(unit, tmp1);
    func_020eaca0(tmp2, (char *) unit + 0x60, tmp1);
    unit->unk_84 = tmp2[0];
    unit->unk_88 = tmp2[1];
    unit->unk_8C = tmp2[2];

    if (unit->unk_CC != 0) {
        val = (s16) (-unit->unk_CC->unk_8E);
        func_020ea6e0(&unit->unk_84, val);
    }

    unit->unk_78 = 0;
    unit->unk_7C = 0;
    unit->unk_80 = 0;

    r6 = unit->unk_8C / 8;
    if (r6 < 0) {
        r6 = -r6;
    }
    r4 = unit->unk_88 / 8;
    if (r4 < 0) {
        r4 = -r4;
    }
    abs84 = unit->unk_84 / 8;
    if (abs84 < 0) {
        abs84 = -abs84;
    }

    unit->unk_90 = abs84;
    unit->unk_94 = r4;
    unit->unk_98 = r6;

    abs84 = unit->unk_A8 / 8;
    if (abs84 < 0) {
        abs84 = -abs84;
    }
    unit->unk_C0 = abs84;

    func_02059674(unit, 1);

    unit->unk_D6 = 0;
    unit->unk_D4 = 0;
}

void func_02058d2c(UnkStruct_02058d2c_2 *p)
{
    int tmp;
    int v;

    tmp = p->unk_A8;
    if ((int) p->unk_D6 >= 8) {
        return;
    }

    func_0205967c((void *) p, &p->unk_60[0]);
    func_020e895c(&tmp, 0, p->unk_C0);
    v = tmp;
    p->unk_A8 = v;
    p->unk_AC = v;
    p->unk_B0 = v;
    func_020e895c(&p->unk_84, 0, p->unk_90);
    func_020e895c(&p->unk_88, 0, p->unk_94);
    func_020e895c(&p->unk_8C, 0, p->unk_98);
    if (p->unk_CC) {
        p->unk_78 = p->unk_84;
        p->unk_7C = p->unk_88;
        p->unk_80 = p->unk_8C;
        func_020ea6e0((s32 *) (&p->unk_78), p->unk_CC->unk_8E);
    }
    VEC_Add(&p->unk_60[0], &p->unk_78, &p->unk_60[0]);
    p->unk_D6++;
    if ((int) p->unk_D6 >= 8) {
        func_02059674((void *) p, 0);
    }
}

void func_02058d28(void) {}

void func_02058d24(void) {}

void func_02058cdc(UnkStruct_02058cdc_2 *self)
{
    UnkStruct_02058cdc local;
    func_0205967c(self, &local);
    func_020eaca0(&local.unk_0C, &self->unk_60, &local);
    self->unk_84 = local.unk_0C;
    self->unk_88 = local.unk_10;
    self->unk_8C = local.unk_14;
    func_02059674(self, 1);
    self->unk_D6 = 0;
}

void func_02058c90(UnkStruct_02058c90 *s)
{
    if ((int) s->unk_D6 >= 9) {
        return;
    }
    func_0205967c(s, (void *) (&s->unk_60));
    VEC_Add((void *) (&s->unk_60), (void *) (&s->unk_84), (void *) (&s->unk_60));
    s->unk_D6++;
    if ((int) s->unk_D6 < 9) {
        return;
    }
    func_02059674(s, 0);
}

void func_02058c60(UnkStruct_02058c60 *param)
{
    int zero = 0;
    func_02059674(param, 1);
    param->unk_D6 = 0;
    if (param->unk_54 == 2) {
        param->unk_54 = 0;
    }
    func_02091254(0x93, &param->unk_60, zero, zero);
}

void func_02058c2c(UnkStruct_02058c2c *p)
{
    if ((int) p->unk_D6 < 10) {
        p->unk_D6++;
        if ((int) p->unk_D6 >= 10) {
            func_02059674((void *) p, 0);
        }
    }
}

void func_02058be0(UnkStruct_02058be0_2 *self)
{
    UnkStruct_02058be0 tmp;
    func_02059674(self, 1);
    func_0205967c(self, &tmp);
    func_020eaca0(&tmp.a, self->src, &tmp);
    self->unk_84 = tmp.a;
    self->unk_88 = tmp.b;
    self->unk_8C = tmp.c;
    self->d6 = 0;
    self->d4 = 0;
}

void func_02058b5c(struct UnkStruct_02058b5c *s)
{
    if (s->unk_D6 < data_020cbaec[s->unk_D4]) {
        func_0205967c(s, s->unk_60);
        VEC_Add(s->unk_60, s->unk_84, s->unk_60);
        s->unk_D6++;
        if (s->unk_D6 >= data_020cbaec[s->unk_D4]) {
            int res = (int) s->unk_A8 / data_021c933c[s->unk_D4];
            if (res < 0) {
                res = -res;
            }
            s->unk_C0 = res;
            s->unk_D4++;
        }
    }
}

void func_02058ac8(UnkStruct_02058ac8 *self)
{
    if (self->unk_D6 < data_020cbaec[self->unk_D4]) {
        unsigned int temp = self->unk_A8;
        unsigned int val;

        func_020e895c((void *) (&temp), 0, self->unk_C0);
        val = temp;
        self->unk_A8 = val;
        self->unk_AC = val;
        self->unk_B0 = val;

        func_0205967c(self, (unsigned char *) self + 0x60);
        VEC_Add((unsigned char *) self + 0x60, (unsigned char *) self + 0x84, (unsigned char *) self + 0x60);

        self->unk_D6++;
        if (self->unk_D6 >= data_020cbaec[self->unk_D4]) {
            self->unk_D4++;
        }
    }
}
