/* music_264: 52 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020371ac @ 0x020371ac, 0x1c bytes, Thumb
 * func_02037190 @ 0x02037190, 0x1a bytes, Thumb
 * func_0203710c @ 0x0203710c, 0x84 bytes, Thumb
 * func_020370f0 @ 0x020370f0, 0x1c bytes, Thumb
 * func_020370e4 @ 0x020370e4, 0xc bytes, Thumb
 * func_020370cc @ 0x020370cc, 0x18 bytes, Thumb
 * func_020370bc @ 0x020370bc, 0x10 bytes, Thumb
 * func_020370b4 @ 0x020370b4, 0x8 bytes, Thumb
 * func_020370b0 @ 0x020370b0, 0x2 bytes, Thumb
 * func_0203709c @ 0x0203709c, 0x14 bytes, Thumb
 * func_02036fec @ 0x02036fec, 0xb0 bytes, Thumb
 * func_02036fd4 @ 0x02036fd4, 0x18 bytes, Thumb
 * func_02036fd0 @ 0x02036fd0, 0x4 bytes, Thumb
 * func_02036fb4 @ 0x02036fb4, 0x1c bytes, Thumb
 * func_02036f94 @ 0x02036f94, 0x20 bytes, Thumb
 * func_02036f6c @ 0x02036f6c, 0x28 bytes, Thumb
 * func_02036f60 @ 0x02036f60, 0xc bytes, Thumb
 * func_02036f48 @ 0x02036f48, 0x18 bytes, Thumb
 * func_02036f2c @ 0x02036f2c, 0x1c bytes, Thumb
 * func_02036f24 @ 0x02036f24, 0x8 bytes, Thumb
 * func_02036f08 @ 0x02036f08, 0x1a bytes, Thumb
 * func_02036ed4 @ 0x02036ed4, 0x34 bytes, Thumb
 * func_02036ec8 @ 0x02036ec8, 0xc bytes, Thumb
 * func_02036e90 @ 0x02036e90, 0x36 bytes, Thumb
 * func_02036e8c @ 0x02036e8c, 0x4 bytes, Thumb
 * func_02036ddc @ 0x02036ddc, 0xb0 bytes, Thumb
 * func_02036d24 @ 0x02036d24, 0xb6 bytes, Thumb
 * func_02036be4 @ 0x02036be4, 0x140 bytes, Thumb
 * func_02036bbc @ 0x02036bbc, 0x26 bytes, Thumb
 * func_02036ba4 @ 0x02036ba4, 0x18 bytes, Thumb
 * func_02036b88 @ 0x02036b88, 0x1c bytes, Thumb
 * func_02036b6c @ 0x02036b6c, 0x1c bytes, Thumb
 * func_02036b50 @ 0x02036b50, 0x1c bytes, Thumb
 * func_02036b34 @ 0x02036b34, 0x1c bytes, Thumb
 * func_02036b14 @ 0x02036b14, 0x20 bytes, Thumb
 * func_02036af4 @ 0x02036af4, 0x20 bytes, Thumb
 * func_02036ad4 @ 0x02036ad4, 0x20 bytes, Thumb
 * func_02036ab4 @ 0x02036ab4, 0x20 bytes, Thumb
 * func_02036a94 @ 0x02036a94, 0x20 bytes, Thumb
 * func_02036a78 @ 0x02036a78, 0x1c bytes, Thumb
 * func_02036a5c @ 0x02036a5c, 0x1a bytes, Thumb
 * func_02036a30 @ 0x02036a30, 0x2a bytes, Thumb
 * func_020369fc @ 0x020369fc, 0x34 bytes, Thumb
 * func_020369d0 @ 0x020369d0, 0x2c bytes, Thumb
 * func_020369a0 @ 0x020369a0, 0x30 bytes, Thumb
 * func_02036980 @ 0x02036980, 0x20 bytes, Thumb
 * func_02036960 @ 0x02036960, 0x1e bytes, Thumb
 * func_02036940 @ 0x02036940, 0x20 bytes, Thumb
 * func_02036920 @ 0x02036920, 0x20 bytes, Thumb
 * func_020368f0 @ 0x020368f0, 0x30 bytes, Thumb
 * func_020368c0 @ 0x020368c0, 0x30 bytes, Thumb
 * func_02036894 @ 0x02036894, 0x2a bytes, Thumb
 */

#include "types.h"

struct func_020371ac_data {
    unsigned char pad_00[0xe];
    unsigned char flag;
};

typedef struct {
    unsigned char pad_00[0xe];
    unsigned char flag;
} UnkStruct_02037190;

typedef struct {
    int *ptr;
    int val;
    unsigned short flags;
    unsigned char a;
    unsigned char b;
} func_020370f0_struct;

struct UnkStruct_02036fec {
    unsigned char pad_00[8];
    unsigned short h;
    unsigned char pad_0A;
    unsigned char b;
};

typedef struct {
    char pad_00[8];
    unsigned short unk_08;
} UnkStruct_02036f94;

typedef struct {
    void *ptr;
    int value;
    unsigned short arr[5];
    unsigned char flags[4];
} UnkStruct_02036f6c;

struct UnkStruct_02036f48 {
    void *vtable;
};

typedef struct {
    unsigned char pad_00[8];
    unsigned short arr[5];
    unsigned char bytes[4];
} UnkStruct_02036f2c;

struct UnkStruct_02036f08 {
    unsigned char pad_00[0x15];
    unsigned char flag;
};

typedef struct {
    unsigned char pad_00[0x14];
    unsigned char unk_14;
    unsigned char unk_15;
} UnkStruct_02036e90;

typedef struct {
    u8 pad_00[0x8];
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[5];
    u8 unk_13;
} UnkStruct_02036d24;

typedef struct UnkStruct_02036be4 UnkStruct_02036be4;

struct UnkStruct_02036be4 {
    char pad_00[0xe];
    unsigned short unk_0E;
};

typedef struct {
    unsigned char pad_00[0x10];
    unsigned short unk_10;
} UnkStruct_02036bbc;

struct UnkStruct_02036ba4 {
    unsigned char pad_00[8];
    unsigned short unk_08;
};

typedef struct {
    char pad_00[0xc];
    unsigned short unk_0C;
} UnkStruct_02036b6c;

struct UnkStruct_02036b50 {
    unsigned char pad_00[14];
    unsigned short unk_0E;
};

struct UnkStruct_02036b14 {
    char pad_00[8];
    unsigned short unk_08;
};

struct UnkStruct_02036af4 {
    unsigned char pad_00[0xa];
    unsigned short unk_0A;
};

struct unknown {
    char pad_00[12];
    unsigned short unk_0C;
};

struct UnkStruct_02036ab4 {
    unsigned char pad_00[0xe];
    unsigned short unk_0E;
};

struct UnkStruct_02036a94 {
    char pad_00[0x10];
    unsigned short unk_10;
};

typedef struct {
    unsigned char pad_00[0x12];
    unsigned char flag;
} UnkStruct_02036a78;

typedef struct {
    char pad_00[0x12];
    unsigned char unk_12;
} UnkStruct_02036a5c;

typedef struct {
    void *unk_00;
    void *unk_04;
    char pad_08[16];
    void *unk_18;
    char pad_1C[8];
    void *unk_24;
} UnkStruct_020369fc;

extern void func_02035684(int p1, int p2, int p3);
extern void func_02035624(int);
extern unsigned short data_020da24c;
extern unsigned short data_020da248;
extern unsigned short data_020da250;
extern int func_02036648(void);
extern int func_020373c8(int h, int a, int b, int c, int d);
extern char *func_02137550(short *p, int n);
extern int func_02037404(int h, short *a, short *b);
extern int data_020da324;
extern void func_020edb3c(void *);
extern void *func_020984e8(void);
extern int func_020b22b8(void);
extern int func_020b22dc(void);
extern int func_02099020(void *p, int n);
extern int func_02099640(void *p);
extern int func_0209ac04(int);
extern unsigned char data_020da2e4[];
extern int func_02041614(void);
extern void func_0209e474(void *buf);
extern int func_0203fc78(int id, void *ptr, int arg);
extern int func_02073d90(unsigned int val);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern unsigned int data_020ccf94;
extern int func_0203736c(int a, int b, int c, int d, int e, int f, int g);
extern void func_0203564c(int, int);
extern void func_020356c4(int, int, int, int);
extern void func_02035610(int);
extern void func_02035638(unsigned short value);
extern int func_0203734c(int x);
extern void func_020372f8(void *, unsigned int);
extern unsigned char data_020da304[];
extern void func_020372ec(void *);
extern void func_020372bc(void *);
extern void func_020372b4(void *);
extern void func_02037298(void *);
extern void func_02037278(void *);
extern int func_020b6660(void);
extern int func_020b6640(void);
extern void func_02037260(void *ptr);
extern int func_0203723c(void *);
extern void func_02037238(void *, int);

void func_0203709c(void *r0);
void func_02036fb4(unsigned char *r0, unsigned char *r1, unsigned short r2, int argument3);
void func_02036f94(UnkStruct_02036f94 *s);
void func_02036ed4(void *r0);
void func_02036ddc(void *self);
void func_02036d24(UnkStruct_02036d24 *self, int flag);
void func_02036be4(UnkStruct_02036be4 *p, int flag);
void func_02036bbc(UnkStruct_02036bbc *p, int flag);
void func_02036ba4(struct UnkStruct_02036ba4 *self, unsigned short value);
void func_02036b88(short *ptr, int value);
void func_02036b6c(UnkStruct_02036b6c *p, unsigned short val);
void func_02036b50(struct UnkStruct_02036b50 *arg0, int arg1);
void func_02036b34(int r0, int r1);
void func_02036b14(struct UnkStruct_02036b14 *p);
void func_02036af4(struct UnkStruct_02036af4 *ptr);
void func_02036ad4(struct unknown *data);
void func_02036ab4(struct UnkStruct_02036ab4 *p);
void func_02036a94(struct UnkStruct_02036a94 *s);
void func_02036a78(UnkStruct_02036a78 *s, int b);
void func_02036a5c(UnkStruct_02036a5c *s);
int func_02036a30(unsigned char *p);

void func_020371ac(struct func_020371ac_data *self, int arg2)
{
    if (self->flag == 0) {
        func_02035684(0x1b, arg2, 0);
        self->flag = 1;
    }
}

void func_02037190(UnkStruct_02037190 *s)
{
    if (s->flag) {
        func_02035624(27);
        s->flag = 0;
    }
}

void func_0203710c(void *self)
{
    int h;
    int ok;
    short x[2];
    short y[2];

    h = func_02036648();
    ok = func_020373c8(h, 0x3b, 0x32, 0, 0x10);
    x[0] = data_020da24c;
    x[1] = data_020da248;
    y[0] = data_020da250;
    func_02137550(&y[1], 2);
    if (func_02037404(h, &x[0], &y[0]) || func_02037404(h, &x[1], &y[1])) {
        ok = 0;
    }
    if (ok) {
        func_020371ac((struct func_020371ac_data *) self, 0xc8);
    } else {
        func_02037190((UnkStruct_02037190 *) self);
    }
}

void func_020370f0(func_020370f0_struct *obj, int value)
{
    obj->ptr = &data_020da324;
    obj->val = value;
    obj->flags = 0xffff;
    obj->a = 0;
    obj->b = 0;
}

void func_020370e4(int *ptr)
{
    *ptr = (int) &data_020da324;
}

void *func_020370cc(void *self)
{
    *(void **) self = ((char *) &data_020da324);
    func_020edb3c(self);
    return self;
}

void func_020370bc(unsigned char *r0)
{
    unsigned short *r0_8 = (unsigned short *) (r0 + 8);
    *r0_8 = 0x0000ffff;
    r0[0xa] = 0;
    r0[0xb] = 0;
}

void func_020370b4(void *argument0)
{
    func_0203709c((void *) argument0);
}

void func_020370b0(void *receiver) {}

void func_0203709c(void *r0)
{
    void *r4 = r0;
    func_02036f94((UnkStruct_02036f94 *) r4);
    ((unsigned char *) r4)[0xa] = 0;
    ((unsigned char *) r4)[0xb] = 0;
}

void func_02036fec(struct UnkStruct_02036fec *self)
{
    self->b = 1;
    if (self->h == 0xffff) {
        void *r5 = func_020984e8();
        if (func_020b22b8() != 0) {
            func_02035684(3, 0, 5);
            func_02036fb4((unsigned char *) self, (unsigned char *) 4, 0x45, 1);
            return;
        } else if (func_020b22dc() != 0) {
            func_02036fb4((unsigned char *) self, (unsigned char *) 0xd, 0x4a, 0);
            return;
        } else {
            if (r5 != 0) {
                if (func_02099020(r5, 0x23) != 0) {
                    goto call_1c;
                }
                if (func_02099020(r5, 1) == 0) {
                    goto label_72;
                }
                if (func_0209ac04((int) func_02099640(r5)) != 0) {
                    goto label_72;
                }
            call_1c:
                func_02036fb4((unsigned char *) self, (unsigned char *) 0x1c, 0x46, 0);
                return;
            }
        label_72:
            if (r5 != 0) {
                if (func_02099020(r5, 1) == 0) {
                    return;
                }
                func_02036fb4((unsigned char *) self, (unsigned char *) 0x1d, 0x48, 0);
            }
        }
    }
}

void func_02036fd4(void *arg0)
{
    unsigned char val;
    void *r4;

    r4 = arg0;
    val = *(unsigned char *) ((int) r4 + 0xa);
    if (val == 0) {
        func_02036f94((UnkStruct_02036f94 *) r4);
    }
    *(unsigned char *) ((int) r4 + 0xb) = 0;
}

void func_02036fd0(unsigned char *p0, int p1)
{
    p0[10] = p1;
}

void func_02036fb4(unsigned char *r0, unsigned char *r1, unsigned short r2, int argument3)
{
    unsigned char *r5 = r0;
    unsigned short r4 = r2;

    func_020356c4((int) r1, (int) ((unsigned char *) r4), 0x7f, (int) argument3);
    *(unsigned short *) (r5 + 8) = r4;
}

void func_02036f94(UnkStruct_02036f94 *s)
{
    if (s->unk_08 != 0xffff) {
        func_02035638(s->unk_08);
        s->unk_08 = 0xffff;
    }
}

void func_02036f6c(UnkStruct_02036f6c *self, int value)
{
    self->ptr = data_020da2e4;
    self->value = value;
    self->arr[0] = 0xffff;
    self->arr[1] = 0xffff;
    self->arr[2] = 0xffff;
    self->arr[3] = 0xffff;
    self->arr[4] = 0xffff;
    self->flags[0] = 0;
    self->flags[1] = 0;
    self->flags[2] = 0;
    self->flags[3] = 0;
}

void func_02036f60(int *ptr)
{
    *ptr = (int) ((int *) data_020da2e4);
}

struct UnkStruct_02036f48 *func_02036f48(struct UnkStruct_02036f48 *obj)
{
    obj->vtable = (void *) data_020da2e4;
    func_020edb3c((void *) obj);
    return obj;
}

void func_02036f2c(UnkStruct_02036f2c *p)
{
    p->arr[0] = 0xFFFF;
    p->arr[1] = 0xFFFF;
    p->arr[2] = 0xFFFF;
    p->arr[3] = 0xFFFF;
    p->arr[4] = 0xFFFF;
    p->bytes[0] = 0;
    p->bytes[1] = 0;
    p->bytes[2] = 0;
    p->bytes[3] = 0;
}

void func_02036f24(void *argument0)
{
    func_02036ed4((void *) argument0);
}

void func_02036f08(struct UnkStruct_02036f08 *arg)
{
    if (arg->flag) {
        func_02036a30((unsigned char *) arg);
        func_02036ddc((void *) arg);
    }
}

void func_02036ed4(void *r0)
{
    void *r4 = r0;
    func_02036b14((struct UnkStruct_02036b14 *) r4);
    func_02036af4((struct UnkStruct_02036af4 *) r4);
    func_02036ad4((struct unknown *) r4);
    func_02036ab4((struct UnkStruct_02036ab4 *) r4);
    func_02036a94((struct UnkStruct_02036a94 *) r4);
    func_02036a5c((UnkStruct_02036a5c *) r4);
    ((unsigned char *) r4)[0x13] = 0;
    ((unsigned char *) r4)[0x14] = 0;
    ((unsigned char *) r4)[0x15] = 0;
}

void func_02036ec8(void *arg0)
{
    unsigned char *ptr = (unsigned char *) arg0;
    ptr[0x15] = 1;
    func_02036ddc(arg0);
}

int func_02036e90(UnkStruct_02036e90 *obj)
{
    if (obj->unk_14 == 0) {
        func_02036b14((struct UnkStruct_02036b14 *) obj);
        func_02036af4((struct UnkStruct_02036af4 *) obj);
        func_02036ad4((struct unknown *) obj);
        func_02036ab4((struct UnkStruct_02036ab4 *) obj);
        func_02036a94((struct UnkStruct_02036a94 *) obj);
        func_02036a5c((UnkStruct_02036a5c *) obj);
    }
    obj->unk_15 = 0;
    return 0;
}

void func_02036e8c(unsigned char *p0, int p1)
{
    p0[20] = p1;
}

void func_02036ddc(void *self)
{
    int r5, r6, r7;
    struct {
        unsigned int a[2];
        unsigned int b[2];
        unsigned int c[2];
        unsigned int d[2];
    } s;

    r5 = func_02041614();

    s.a[0] = 0;
    s.a[1] = 0;
    func_0209e474(s.a);

    MI_CpuCopy8(s.a, s.b, 8);
    r6 = (func_0203fc78(0x13, s.b, 0) != 0) ? 1 : 0;

    r7 = 1;
    if (r5 != 0x12) {
        MI_CpuCopy8(s.a, s.c, 8);
        if (func_0203fc78(0x12, s.c, 0) != 3) {
            r7 = 0;
        }
    }

    if (func_02073d90(data_020ccf94) != 0) {
        MI_CpuCopy8(s.a, s.d, 8);
        r5 = func_0203fc78(0xf, s.d, 0);
    } else {
        r5 = (r5 == 0xf) ? 1 : 0;
    }

    func_02036d24((UnkStruct_02036d24 *) self, r6);
    func_02036be4((UnkStruct_02036be4 *) self, r7);
    func_02036bbc((UnkStruct_02036bbc *) self, (r5 != 0) ? 1 : 0);
}

void func_02036d24(UnkStruct_02036d24 *self, int flag)
{
    int a, b;
    if (flag != 0) {
        a = func_02036648();
        b = func_0203736c(a, 0, 0, 0, 2, 0, 0);
        a = func_0203736c(a, 2, 0, 0, 0, 0, 0);
        if (b != 0) {
            if (self->unk_13 != 0) {
                if (self->unk_08 != 0x35) {
                    func_02036b14((struct UnkStruct_02036b14 *) self);
                    func_02036ba4((struct UnkStruct_02036ba4 *) self, 0x35);
                }
                self->unk_13 = 0;
            }
            if (self->unk_0A != 0x36) {
                func_02036af4((struct UnkStruct_02036af4 *) self);
                func_02036b88((short *) self, 0x36);
            }
        } else {
            func_02036b14((struct UnkStruct_02036b14 *) self);
            func_02036af4((struct UnkStruct_02036af4 *) self);
        }
        if (a != 0) {
            if (self->unk_0C != 0x37) {
                func_02036ad4((struct unknown *) self);
                func_02036b6c((UnkStruct_02036b6c *) self, 0x37);
            }
        } else {
            func_02036ad4((struct unknown *) self);
        }
    } else {
        func_02036b14((struct UnkStruct_02036b14 *) self);
        func_02036af4((struct UnkStruct_02036af4 *) self);
        func_02036ad4((struct unknown *) self);
    }
}

void func_02036be4(UnkStruct_02036be4 *p, int flag)
{
    int a, sel;
    int res1, res2, res3, res4;
    int res5, res6, res7, res8;

    if (flag != 0) {
        a = func_02036648();
        sel = 0xffff;

        res1 = func_0203736c(a, 0x17, 0, 0, 0x17, 0x1e, 0);
        res2 = func_0203736c(a, 0x17, 0x1e, 0, 0x17, 0x32, 0);
        res3 = func_0203736c(a, 0x17, 0x32, 0, 0x17, 0x37, 0);
        res4 = func_0203736c(a, 0x17, 0x37, 0, 0, 0, 0);

        if (res1) {
            sel = 0x31;
        } else if (res2) {
            sel = 0x32;
        } else if (res3) {
            sel = 0x33;
        } else if (res4) {
            sel = 0x34;
        }

        if (sel != 0xffff) {
            if (p->unk_0E != sel) {
                func_02036ab4((struct UnkStruct_02036ab4 *) p);
                func_02036b50((struct UnkStruct_02036b50 *) p, sel);
            }
        } else {
            func_02036ab4((struct UnkStruct_02036ab4 *) p);
        }

        res5 = func_0203736c(a, 0x17, 0x1d, 0x32, 0x17, 0x1e, 0);
        res6 = func_0203736c(a, 0x17, 0x31, 0x32, 0x17, 0x32, 0);
        res7 = func_0203736c(a, 0x17, 0x36, 0x32, 0x17, 0x37, 0);
        res8 = func_0203736c(a, 0x17, 0x3a, 0x32, 0, 0, 0);

        if (res5 || res6 || res7 || res8) {
            func_02036a78((UnkStruct_02036a78 *) p, 0xc8);
        } else {
            func_02036a5c((UnkStruct_02036a5c *) p);
        }
    } else {
        func_02036ab4((struct UnkStruct_02036ab4 *) p);
        func_02036a5c((UnkStruct_02036a5c *) p);
    }
}

void func_02036bbc(UnkStruct_02036bbc *p, int flag)
{
    if (flag != 0) {
        if (p->unk_10 != 0x30) {
            func_02036a94((struct UnkStruct_02036a94 *) p);
            func_02036b34((int) p, 0x30);
        }
    } else {
        func_02036a94((struct UnkStruct_02036a94 *) p);
    }
}

void func_02036ba4(struct UnkStruct_02036ba4 *self, unsigned short value)
{
    func_0203564c(0x1f, value);
    self->unk_08 = value;
}

void func_02036b88(short *ptr, int value)
{
    short *p = ptr;
    int v = value;
    func_020356c4(0x20, v, 0x7f, 0);
    p[5] = (short) v;
}

void func_02036b6c(UnkStruct_02036b6c *p, unsigned short val)
{
    func_020356c4((unsigned short) 0x21, (unsigned short) val, (unsigned short) 0x7f, 0);
    p->unk_0C = val;
}

void func_02036b50(struct UnkStruct_02036b50 *arg0, int arg1)
{
    func_020356c4(0x22, arg1, 0x7f, 0);
    arg0->unk_0E = arg1;
}

void func_02036b34(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;
    func_020356c4(0x23, r4, 0x7f, 0);
    *(unsigned short *) (r5 + 0x10) = (unsigned short) r4;
}

void func_02036b14(struct UnkStruct_02036b14 *p)
{
    if (p->unk_08 != 0xffff) {
        func_02035610(p->unk_08);
        p->unk_08 = 0xffff;
    }
}

void func_02036af4(struct UnkStruct_02036af4 *ptr)
{
    if (ptr->unk_0A != 0xffff) {
        func_02035638(ptr->unk_0A);
        ptr->unk_0A = 0xffff;
    }
}

void func_02036ad4(struct unknown *data)
{
    if (data->unk_0C != 0xFFFF) {
        func_02035638(data->unk_0C);
        data->unk_0C = 0xFFFF;
    }
}

void func_02036ab4(struct UnkStruct_02036ab4 *p)
{
    if (p->unk_0E != 0xffff) {
        func_02035638(p->unk_0E);
        p->unk_0E = 0xffff;
    }
}

void func_02036a94(struct UnkStruct_02036a94 *s)
{
    if (s->unk_10 != 0xFFFF) {
        func_02035638(s->unk_10);
        s->unk_10 = 0xFFFF;
    }
}

void func_02036a78(UnkStruct_02036a78 *s, int b)
{
    if (s->flag == 0) {
        func_02035684(30, b, 0);
        s->flag = 1;
    }
}

void func_02036a5c(UnkStruct_02036a5c *s)
{
    if (s->unk_12) {
        func_02035624(30);
        s->unk_12 = 0;
    }
}

int func_02036a30(unsigned char *p)
{
    unsigned char *q = p + 0x13;
    int v = func_0203734c(func_02036648());
    int b = (p[0x13] | v) ? 1 : 0;
    *q = b;
    return b;
}

UnkStruct_020369fc *func_020369fc(UnkStruct_020369fc *param1, int param2)
{
    param1->unk_00 = (void *) data_020da304;
    func_020372f8(&param1->unk_04, param2);
    func_020370f0((func_020370f0_struct *) (&param1->unk_18), param2);
    func_02036f6c((UnkStruct_02036f6c *) (&param1->unk_24), param2);
    return param1;
}

void *func_020369d0(void *p)
{
    *(unsigned int *) p = (unsigned int) ((char *) data_020da304);
    func_02036f60((int *) ((char *) p + 0x24));
    func_020370e4((int *) ((char *) p + 0x18));
    func_020372ec((char *) p + 0x04);
    return p;
}

void *func_020369a0(void *self)
{
    *(int *) self = (unsigned int) data_020da304;
    func_02036f60((int *) ((char *) self + 0x24));
    func_020370e4((int *) ((char *) self + 0x18));
    func_020372ec((char *) self + 4);
    func_020edb3c(self);
    return self;
}

void func_02036980(void *arg0)
{
    void *r4 = arg0;
    func_020372bc((char *) r4 + 4);
    func_020370bc((unsigned char *) ((char *) r4 + 0x18));
    func_02036f2c((UnkStruct_02036f2c *) ((char *) r4 + 0x24));
}

void func_02036960(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_02036f24((char *) r4 + 0x24);
    func_020370b4((char *) r4 + 0x18);
    func_020372b4((char *) r4 + 4);
}

void func_02036940(void *arg0)
{
    void *r4 = arg0;
    func_02037298((void *) ((char *) r4 + 4));
    func_020370b0((void *) ((char *) r4 + 0x18));
    func_02036f08((struct UnkStruct_02036f08 *) ((void *) ((char *) r4 + 0x24)));
}

void func_02036920(void *arg0)
{
    void *r4 = arg0;
    func_02037278((void *) ((char *) r4 + 4));
    func_0203709c((void *) ((char *) r4 + 0x18));
    func_02036ed4((void *) ((char *) r4 + 0x24));
}

void func_020368f0(void *param)
{
    if (func_020b6660() != 0 || func_020b6640() != 0) {
        func_02037260((char *) param + 4);
        func_02036fec((struct UnkStruct_02036fec *) ((char *) param + 0x18));
        func_02036ec8((char *) param + 0x24);
    }
}

void func_020368c0(void *param)
{
    if (func_020b6660() == 0 && func_020b6640() == 0) {
        return;
    }
    func_02036e90((UnkStruct_02036e90 *) ((char *) param + 0x24));
    func_02036fd4((char *) param + 0x18);
    func_0203723c((char *) param + 4);
}

void func_02036894(void *param0, void *param1)
{
    func_02037238((char *) param0 + 4, (int) param1);
    func_02036fd0((unsigned char *) ((char *) param0 + 0x18), (int) param1);
    func_02036e8c((unsigned char *) ((char *) param0 + 0x24), (int) param1);
}
