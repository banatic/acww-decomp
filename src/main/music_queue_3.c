/* music_queue_3: 44 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02035f50 @ 0x02035f50, 0x1c bytes, Thumb
 * func_02035f44 @ 0x02035f44, 0xc bytes, Thumb
 * func_02035f2c @ 0x02035f2c, 0x18 bytes, Thumb
 * func_02035e90 @ 0x02035e90, 0x9c bytes, Thumb
 * func_02035e7c @ 0x02035e7c, 0x14 bytes, Thumb
 * func_02035e68 @ 0x02035e68, 0x14 bytes, Thumb
 * func_02035e54 @ 0x02035e54, 0x14 bytes, Thumb
 * func_02035dcc @ 0x02035dcc, 0x88 bytes, Thumb
 * func_02035dc8 @ 0x02035dc8, 0x2 bytes, Thumb
 * func_02035dc0 @ 0x02035dc0, 0x8 bytes, Thumb
 * func_02035db8 @ 0x02035db8, 0x8 bytes, Thumb
 * func_02035d8c @ 0x02035d8c, 0x2c bytes, Thumb
 * func_02035c64 @ 0x02035c64, 0x128 bytes, Thumb
 * func_02035c1c @ 0x02035c1c, 0x48 bytes, Thumb
 * func_02035c10 @ 0x02035c10, 0xc bytes, Thumb
 * func_02035c08 @ 0x02035c08, 0x6 bytes, Thumb
 * func_02035bec @ 0x02035bec, 0x1a bytes, Thumb
 * func_02035bdc @ 0x02035bdc, 0xe bytes, Thumb
 * func_02035b38 @ 0x02035b38, 0xa4 bytes, Thumb
 * func_02035b20 @ 0x02035b20, 0x18 bytes, Thumb
 * func_02035b14 @ 0x02035b14, 0xc bytes, Thumb
 * func_02035afc @ 0x02035afc, 0x18 bytes, Thumb
 * func_02035ae8 @ 0x02035ae8, 0x14 bytes, Thumb
 * func_02035ac8 @ 0x02035ac8, 0x20 bytes, Thumb
 * func_02035ab4 @ 0x02035ab4, 0x14 bytes, Thumb
 * func_02035a70 @ 0x02035a70, 0x44 bytes, Thumb
 * func_02035a6c @ 0x02035a6c, 0x2 bytes, Thumb
 * func_02035a64 @ 0x02035a64, 0x8 bytes, Thumb
 * func_02035a60 @ 0x02035a60, 0x2 bytes, Thumb
 * func_02035a30 @ 0x02035a30, 0x30 bytes, Thumb
 * func_02035a24 @ 0x02035a24, 0xc bytes, Thumb
 * func_02035a18 @ 0x02035a18, 0xc bytes, Thumb
 * func_02035a00 @ 0x02035a00, 0x18 bytes, Thumb
 * func_02035930 @ 0x02035930, 0xce bytes, Thumb
 * func_02035864 @ 0x02035864, 0xcc bytes, Thumb
 * func_0203584c @ 0x0203584c, 0x18 bytes, Thumb
 * func_02035834 @ 0x02035834, 0x18 bytes, Thumb
 * func_02035820 @ 0x02035820, 0x12 bytes, Thumb
 * func_02035800 @ 0x02035800, 0x20 bytes, Thumb
 * func_02035750 @ 0x02035750, 0xb0 bytes, Thumb
 * func_020356fc @ 0x020356fc, 0x54 bytes, Thumb
 * func_020356c4 @ 0x020356c4, 0x38 bytes, Thumb
 * func_02035684 @ 0x02035684, 0x40 bytes, Thumb
 * func_0203564c @ 0x0203564c, 0x38 bytes, Thumb
 */

struct UnkStruct_02035f50 {
    void *unk_00;
    unsigned int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned int unk_0C;
    unsigned int unk_10;
};

typedef struct UnkStruct_02035e90 {
    unsigned char pad_00[8];
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    int unk_0C;
    int unk_10;
} UnkStruct_02035e90;

typedef struct EarlyStruct {
    unsigned char pad_00[12];
    unsigned short unk_0C;
} EarlyStruct;

typedef struct {
    char pad_00[8];
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    int unk_0C;
} UnkStruct_02035dcc;

typedef struct {
    unsigned char pad_00[8];
    unsigned char b0, b1, b2, b3;
    unsigned int w0;
    unsigned int w1;
} UnkStruct_02035d8c;

typedef struct {
    unsigned char pad_00[8];
    unsigned char unk_08;
    unsigned char pad_09[2];
    unsigned char unk_0B;
} UnkStruct_02035c1c;

typedef struct {
    unsigned char pad_00[10];
    unsigned char unk_0A;
} UnkStruct_02035c08;

typedef struct UnkStruct_02035b38 {
    int unk_00, unk_04, unk_08, unk_0C, unk_10;
} UnkStruct_02035b38;

typedef struct UnkStruct_02035b38_2 {
    unsigned short a;
    unsigned short b;
} UnkStruct_02035b38_2;

struct UnkStruct_02035b20 {
    char *unk_00;
    unsigned int unk_04;
    unsigned short unk_08;
    unsigned char unk_0A;
};

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned short unk_08;
} UnkStruct_02035ac8;

typedef struct {
    unsigned char pad_00[8];
    unsigned short unk_08;
    unsigned char unk_0A;
} UnkStruct_02035a30;

typedef struct {
    void *vtable;
} Object;

extern unsigned char data_020da2d4[];
extern void func_020edb3c(void *ptr);
extern void func_02035624(int);
extern int func_02036714(void);
extern void func_02036784(int, int);
extern void func_02036894(int, int);
extern EarlyStruct *data_021f42f4;
extern unsigned char data_021c526c[];
extern int func_02095f90(void);
extern int func_020b6660(void);
extern void *func_020351c4(void);
extern unsigned char data_020c9f14[];
extern unsigned char data_020e54a8;
extern void func_02095764(UnkStruct_02035b38_2 *p, int n);
extern int func_0204bcdc(UnkStruct_02035b38_2 *p);
extern int func_0204bc64(unsigned short *p);
extern unsigned char data_020da2b4[];
extern void func_02035638(int);
extern unsigned char data_020da314[];
extern int func_020b65c4(void);
extern int func_020b5e10(void);
extern int func_020b5e84(unsigned char *);
extern void func_0200423c(int);
extern int func_020b65b8(void);
extern void func_0200422c(int);
extern int func_020b6640(void);
extern int func_020ba4b8(void);
extern void func_020ba4c4(int *, int *);
extern void func_0200421c(int);
extern void *func_020374d0(void *p, int a, int b, int c, int w, int value);
extern void func_02035198(unsigned int val, void *p);
extern void func_020374cc(void *p);

int func_02035e7c(void);
unsigned int *func_02035e68(void);
int func_02035e54(void);
void func_02035d8c(UnkStruct_02035d8c *p);
void func_02035b38(UnkStruct_02035b38 *p);
void func_02035a30(UnkStruct_02035a30 *s);
void func_02035930(void);
void func_02035864(void);
void func_02035750(void);
void func_020356fc(int receiver);
void func_020356c4(int a, int b, int c, int d);
void func_02035684(int param0, int param1, int param2);

void func_02035f50(struct UnkStruct_02035f50 *self, unsigned int arg)
{
    self->unk_00 = (void *) data_020da2d4;
    self->unk_04 = arg;
    self->unk_08 = 0;
    self->unk_09 = 0;
    self->unk_0A = 0;
    self->unk_0B = 0;
    self->unk_0C = 0;
    self->unk_10 = 0;
}

void func_02035f44(int **p)
{
    *p = ((int *) data_020da2d4);
}

void *func_02035f2c(void *ptr)
{
    *(unsigned int *) ptr = (unsigned int) ((unsigned int *) data_020da2d4);
    func_020edb3c(ptr);
    return ptr;
}

void func_02035e90(UnkStruct_02035e90 *r4)
{
    unsigned char stage;

    if (data_021f42f4->unk_0C == 5) {
        return;
    }

    stage = r4->unk_0B;
    if (stage == 1) {
        func_02035684(8, 15, 0);
        r4->unk_0B = 2;
    } else if (stage == 3) {
        func_02035624(8);
        r4->unk_0B = 0;
    }

    r4->unk_09 = func_02036714();
    func_02036784(func_02035e54(), r4->unk_09);

    if (r4->unk_08 == 0 && r4->unk_09 == 0 && r4->unk_0A == 0) {
        if (r4->unk_0C != 0 || r4->unk_10 != 0) {
            func_02035624(7);
        }
        r4->unk_0C = -1;
        r4->unk_10 = 0;
        func_02035684(7, 15, 0);
    } else {
        func_02036894((int) func_02035e68(), 1);
        if (r4->unk_09 != 0) {
            func_02035e7c();
            func_02035930();
        }
    }
}

int func_02035e7c(void)
{
    return (*(int *) data_021c526c) + 0x2f0;
}

unsigned int *func_02035e68(void)
{
    unsigned int *ptr;
    unsigned int offset;

    ptr = *(unsigned int **) data_021c526c;
    offset = 0x264;
    return (unsigned int *) ((char *) ptr + offset);
}

int func_02035e54(void)
{
    return (*(int *) data_021c526c) + 0x2a0;
}

void func_02035dcc(UnkStruct_02035dcc *self)
{
    if (*(unsigned short *) ((char *) (*(void * *) &data_021f42f4) + 0xc) == 5) {
        return;
    }

    if (self->unk_0C < 0) {
        int x = func_02095f90();
        if (x == 0x3c) {
            // do nothing
        } else if (x == 0x8b) {
            self->unk_0C = 0x21;
        } else if (x == 0x8e) {
            self->unk_0C = 0x21;
        } else if (x == 0x43) {
            self->unk_0C = 0x21;
        } else if (x == 0x44) {
            self->unk_0C = 0x21;
        } else if (x == 0x02) {
            self->unk_0C = 0x19;
        } else {
            self->unk_0C = 0x14;
        }
    }

    if (self->unk_09 != 0) {
        func_02035e7c();
        func_02035864();
    }

    self->unk_08 = 0;
    self->unk_09 = 0;
    self->unk_0A = 0;

    func_02036894((int) func_02035e68(), 0);
    func_02036784(func_02035e54(), 0);
}

void func_02035dc8(void *receiver) {}

void func_02035dc0(void *argument0)
{
    func_02035d8c((UnkStruct_02035d8c *) ((void *) argument0));
}

void func_02035db8(void *argument0)
{
    func_02035b38((UnkStruct_02035b38 *) ((void *) argument0));
}

void func_02035d8c(UnkStruct_02035d8c *p)
{
    p->b0 = 0;
    p->b1 = 0;
    p->b2 = 0;
    p->b3 = 0;
    if (p->w0 != 0 || p->w1 != 0) {
        func_02035624(7);
        p->w0 = 0;
        p->w1 = 0;
    }
}

void func_02035c64(char *dst, int x, int y)
{
    int flag = 0;
    int r4 = 0;
    int a, b, c, d, e;
    int v;
    unsigned short hval;
    int f, g, h;
    void *p;

    if (func_020b6660() == 0) {
        goto zero_case;
    }

    a = (x == 0);
    b = (x == 1);
    c = (x == 2);
    d = (y == 9);
    e = (y == 6);

    p = func_020351c4();
    if (p) {
        hval = *(unsigned short *) ((char *) p + 4);
    } else {
        hval = 0xFFFF;
    }
    if (p) {
        v = *(int *) p;
    } else {
        v = 0x25;
    }

    f = (hval == 0xFFFF);
    g = (v == 0x24);
    h = (v == 0x1A);

    if (b) {
        if (e) {
            r4 = 1;
        } else if (d) {
            if (h || f) {
                r4 = 1;
            } else if (g && ((unsigned short) (hval + 0xFFD4) <= 1)) {
                r4 = 1;
            }
        } else {
            if (h || f) {
                r4 = 1;
            }
        }
    } else if (c) {
        if (e) {
            r4 = 1;
            flag = 1;
        } else if (d) {
            // empty
        } else {
            if (h || f) {
                r4 = 1;
            }
        }
    } else {
        if (a) {
            if (h || f) {
                r4 = 1;
            }
        }
    }
    goto done;

zero_case:
    r4 = 1;
    flag = 1;

done:
    if (r4 == 0) {
        dst[8] = 1;
    }
    if (flag != 0) {
        dst[0xb] = 1;
    }
}

void func_02035c1c(UnkStruct_02035c1c *s, int a, int b)
{
    if (s->unk_0B == 2) {
        s->unk_0B = 3;
        return;
    }
    {
        int flag0 = (a == 0);
        int flag1 = (a == 1);
        int flag2 = (a == 2 && b == 6);
        if (flag0 || flag1 || !flag2) {
            s->unk_08 = 1;
        }
    }
}

void func_02035c10(void *arg0, unsigned char arg1)
{
    unsigned char value;
    value = data_020c9f14[arg1];
    *(unsigned int *) ((char *) arg0 + 0xc) = value;
}

void func_02035c08(UnkStruct_02035c08 *p)
{
    p->unk_0A = 1;
}

int func_02035bec(unsigned char *p)
{
    return p[8] || p[9] || p[10];
}

int func_02035bdc(const unsigned char *ptr)
{
    if (ptr[0xb] != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_02035b38(UnkStruct_02035b38 *p)
{
    UnkStruct_02035b38_2 buf;
    int v;

    if (p->unk_0C > 0) {
        p->unk_0C = p->unk_0C - 1;
        if (p->unk_0C <= 0) {
            int on;
            v = 1;
            on = data_020e54a8 ? 0 : 1;
            if (on != 0 && func_020b6660()) {
                int ok;
                func_02095764(&buf, 4);
                if (func_0204bcdc(&buf)) {
                    buf.b = 0xfff1;
                    ok = func_0204bc64(&buf.a) == func_0204bc64(&buf.b) ? 1 : 0;
                } else {
                    ok = buf.a == 0xfff1 ? 1 : 0;
                }
                if (ok == 0) {
                    v = 0x14;
                }
            }
            p->unk_10 = v;
        }
    }
    if (p->unk_10 > 0) {
        p->unk_10 = p->unk_10 - 1;
        if (p->unk_10 <= 0) {
            func_02035624(7);
        }
    }
}

void func_02035b20(struct UnkStruct_02035b20 *this, unsigned int value)
{
    this->unk_00 = ((char *) data_020da2b4);
    this->unk_04 = value;
    this->unk_08 = 0xffff;
    this->unk_0A = 0;
}

void func_02035b14(int *ptr)
{
    *ptr = (int) ((int *) data_020da2b4);
}

void *func_02035afc(void *p)
{
    *(void **) p = (void *) data_020da2b4;
    func_020edb3c(p);
    return p;
}

int func_02035ae8(void)
{
    return (*(int *) data_021c526c) + 720;
}

void func_02035ac8(UnkStruct_02035ac8 *p)
{
    p->unk_08 = 0x41;
    func_020356c4(0xB, 0x41, 0x7F, 1);
    func_02035c08((UnkStruct_02035c08 *) ((void *) func_02035ae8()));
}

void func_02035ab4(void *obj)
{
    unsigned char *p = (unsigned char *) obj;
    p[0xa] = 1;
    func_02035684(0xa, 0xf, 0);
}

void func_02035a70(void *arg)
{
    unsigned short *p = (unsigned short *) arg;
    unsigned char *q = (unsigned char *) arg;
    if (p[4] != 0xffff) {
        func_02035684(10, 5, 5);
        func_02035638(p[4]);
        p[4] = 0xffff;
    }
    if (q[10] != 0) {
        func_02035624(10);
        func_02035684(10, 5, 5);
        q[10] = 0;
    }
}

void func_02035a6c(void *receiver) {}

void func_02035a64(void *argument0)
{
    func_02035a30((UnkStruct_02035a30 *) ((void *) argument0));
}

void func_02035a60(void *receiver) {}

void func_02035a30(UnkStruct_02035a30 *s)
{
    if (s->unk_08 != 0xffff) {
        func_02035638(s->unk_08);
        s->unk_08 = 0xffff;
    }
    if (s->unk_0A != 0) {
        func_02035624(10);
        s->unk_0A = 0;
    }
}

void func_02035a24(int **ptr)
{
    *ptr = ((int *) data_020da314);
}

void func_02035a18(int **p)
{
    *p = ((int *) data_020da314);
}

void *func_02035a00(Object *self)
{
    self->vtable = (void *) data_020da314;
    func_020edb3c(self);
    return self;
}

void func_02035930(void)
{
    int a, b;
    int a22, a25, a29;
    int b20, b22, b23, b25, b27, b29;
    int result;

    a = func_020b65c4();
    b = func_020b5e84((unsigned char *) func_020b5e10());

    a22 = (a == 0x22);
    a25 = (a == 0x25);
    a29 = (a == 0x29);

    b20 = (b == 0x20);
    b22 = (b == 0x22);
    b23 = (b == 0x23);
    b25 = (b == 0x25);
    b27 = (b == 0x27);
    b29 = (b == 0x29);

    result = 0;
    if (a == 0x20 && (b22 || b23 || b25 || b27 || b29)) {
        result = 1;
    } else if (a29 && b20) {
        result = 2;
    } else if (a25 && b20) {
        result = 3;
    } else if (a22 && b20) {
        result = 4;
    }
    if (result) {
        func_0200423c(result);
    }
}

void func_02035864(void)
{
    int a, b;
    int b20, b22, b23, b25, b27, b29;
    int c22, c25, c29;
    int result;

    a = func_020b65b8();
    b = func_020b65c4();

    b20 = (a == 0x20);
    b22 = (a == 0x22);
    b23 = (a == 0x23);
    b25 = (a == 0x25);
    b27 = (a == 0x27);
    b29 = (a == 0x29);

    c22 = (b == 0x22);
    c25 = (b == 0x25);
    c29 = (b == 0x29);

    result = 0;
    if (b == 0x20 && (b22 || b23 || b25 || b27 || b29)) {
        result = 1;
    } else if (c29 && b20) {
        result = 2;
    } else if (c25 && b20) {
        result = 3;
    } else if (c22 && b20) {
        result = 4;
    }
    if (result) {
        func_0200422c(result);
    }
}

void func_0203584c(void *receiver)
{
    int result;
    result = func_020b65c4();
    if (result == 0x22) {
        func_0200423c(5);
    }
}

void func_02035834(void *receiver)
{
    if (func_020b65c4() == 0x22) {
        func_0200422c(5);
    }
}

void func_02035820(int param1, int param2)
{
    if (param2 == 0x62) {
        func_02035750();
    }
}

void func_02035800(int param)
{
    if (func_020b6660() || func_020b6640()) {
        func_020356fc(param);
    }
}

void func_02035750(void)
{
    int status;
    int b23;
    int b22;
    int b24;
    int b25;
    int b26;
    int b27;
    int b28;
    int b29;
    int code;

    status = func_020b65c4();
    b22 = (status == 0x22);
    b23 = (status == 0x23);
    b24 = (status == 0x24);
    b25 = (status == 0x25);
    b26 = (status == 0x26);
    b27 = (status == 0x27);
    b28 = (status == 0x28);
    b29 = (status == 0x29);
    code = 0;

    if (status == 0x20) {
        code = 6;
    } else if (b23 || b24 || b27 || b28) {
        code = 0xb;
    } else if (b29) {
        code = 0xc;
    } else if (b25 || b26) {
        code = 0xd;
    } else if (b22) {
        code = 0xe;
    }

    if (code != 0) {
        func_0200423c(code);
    }
}

void func_020356fc(int receiver)
{
    int r4;
    int r2;
    int r1;
    int r0;
    int sp0;
    int sp4;

    r4 = func_020ba4b8();
    func_020ba4c4(&sp0, &sp4);
    r0 = sp4;
    if (r0 < 3) {
        r2 = 0;
    } else {
        r2 = 1;
    }
    r1 = 0;
    if (r2 != 0) {
        if (r4 == 1) {
            r1 = 1;
        }
    }
    r0 = 0;
    if (r2 != 0) {
        if (r4 == 2) {
            r0 = 1;
        }
    }
    if (r1 != 0) {
        r0 = 0xc;
    } else {
        if (r0 != 0) {
            r0 = 0xd;
        } else {
            r0 = 0xb;
        }
    }
    func_0200421c(r0);
}

void func_020356c4(int a, int b, int c, int d)
{
    unsigned char buf[32];

    func_020374d0(buf, a, b, c, 0, d);
    func_02035198((*(unsigned int *) data_021c526c), buf);
    func_020374cc(buf);
}

void func_02035684(int param0, int param1, int param2)
{
    int buf[7];
    func_020374d0(buf, param0, 0xffff, 0, param1, 0);
    if (param2 > 0) {
        buf[6] = param2;
    }
    func_02035198((unsigned int) ((*(void * *) data_021c526c)), buf);
    func_020374cc(buf);
}

void func_0203564c(int a, int b)
{
    unsigned char buf[0x1c];
    func_020374d0(buf, a, b, 0x7f, 0, 0);
    buf[0x11] = 1;
    func_02035198((*(int *) data_021c526c), buf);
    func_020374cc(buf);
}
