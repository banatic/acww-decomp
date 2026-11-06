/* order_catalog_list_3: 29 functions, module ov142
 * mwccarm 1.2/base -O4,s
 * func_ov142_0229ae8c @ 0x0229ae8c, 0x38 bytes, Thumb
 * func_ov142_0229ae60 @ 0x0229ae60, 0x2c bytes, Thumb
 * func_ov142_0229ad74 @ 0x0229ad74, 0xec bytes, Thumb
 * func_ov142_0229ace4 @ 0x0229ace4, 0x90 bytes, Thumb
 * func_ov142_0229ac9c @ 0x0229ac9c, 0x48 bytes, Thumb
 * func_ov142_0229ac58 @ 0x0229ac58, 0x42 bytes, Thumb
 * func_ov142_0229ac38 @ 0x0229ac38, 0x20 bytes, Thumb
 * func_ov142_0229abfc @ 0x0229abfc, 0x3c bytes, Thumb
 * func_ov142_0229ab80 @ 0x0229ab80, 0x7c bytes, Thumb
 * func_ov142_0229ab68 @ 0x0229ab68, 0x18 bytes, Thumb
 * func_ov142_0229a9bc @ 0x0229a9bc, 0x1ac bytes, Thumb
 * func_ov142_0229a988 @ 0x0229a988, 0x34 bytes, Thumb
 * func_ov142_0229a954 @ 0x0229a954, 0x34 bytes, Thumb
 * func_ov142_0229a91c @ 0x0229a91c, 0x38 bytes, Thumb
 * func_ov142_0229a8e8 @ 0x0229a8e8, 0x34 bytes, Thumb
 * func_ov142_0229a8b4 @ 0x0229a8b4, 0x34 bytes, Thumb
 * func_ov142_0229a880 @ 0x0229a880, 0x34 bytes, Thumb
 * func_ov142_0229a84c @ 0x0229a84c, 0x34 bytes, Thumb
 * func_ov142_0229a7e0 @ 0x0229a7e0, 0x6c bytes, Thumb
 * func_ov142_0229a76c @ 0x0229a76c, 0x74 bytes, Thumb
 * func_ov142_0229a6f8 @ 0x0229a6f8, 0x74 bytes, Thumb
 * func_ov142_0229a6e8 @ 0x0229a6e8, 0x10 bytes, Thumb
 * func_ov142_0229a6d8 @ 0x0229a6d8, 0x10 bytes, Thumb
 * func_ov142_0229a644 @ 0x0229a644, 0x94 bytes, Thumb
 * func_ov142_0229a5cc @ 0x0229a5cc, 0x78 bytes, Thumb
 * func_ov142_0229a540 @ 0x0229a540, 0x8c bytes, Thumb
 * func_ov142_0229a4d4 @ 0x0229a4d4, 0x6c bytes, Thumb
 * func_ov142_0229a45c @ 0x0229a45c, 0x78 bytes, Thumb
 * func_ov142_0229a3c0 @ 0x0229a3c0, 0x9c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229ae8c {
    unsigned char pad_00[0xbb];
    unsigned char index;
};

typedef struct {
    char pad_00[0xb4];
    s16 unk_B4;
    char pad_B6[0x184e - 0xb6];
    u16 arr[9];
} UnkStruct_0229ad74;

typedef struct {
    int b[10];
} UnkStruct_0229ad74_2;

typedef struct {
    char pad_00[0xA0];
    int unk_A0;
    int unk_A4;
    char pad_A8[0x14];
    unsigned char bc;
    unsigned char bd;
} UnkStruct_0229ab80;

struct UnkStruct_0229ab68 {
    unsigned char pad_00[0xbd];
    unsigned char unk_BD;
    unsigned char pad_BE[4];
    unsigned char unk_C2;
};

typedef struct {
    char pad_00[0xc4];
    unsigned short c4;
    char pad_C6[0xd6 - 0xc6];
    short d6;
    char pad_D8[0x9d8 - 0xd8];
    unsigned short arr[1];
} UnkStruct_0229a9bc;

typedef struct {
    char pad_00[0xc6];
    unsigned short unk_C6;
    char pad_C8[0x10];
    unsigned short unk_D8;
} UnkStruct_0229a988;

typedef struct {
    char pad_00[0xC8];
    unsigned short unk_C8;
    char pad_CA[0x10];
    unsigned short unk_DA;
    char pad_DC[0x1184];
    char unk_1260;
} UnkStruct_0229a954;

typedef struct {
    char pad_00[0xd0];
    unsigned short unk_D0;
    char pad_D2[0x10];
    unsigned short unk_E2;
    char pad_E4[0x1584];
    char unk_1668;
} UnkStruct_0229a8b4;

typedef struct {
    char pad_00[0xd2];
    unsigned short unk_D2;
    char pad_D4[0x10];
    unsigned short unk_E4;
    char pad_E6[0x1602];
    char unk_16E8[1];
} UnkStruct_0229a880;

typedef struct {
    char pad_00[0xd4];
    unsigned short unk_D4;
    char pad_D6[0x10];
    unsigned short unk_E6;
} UnkStruct_0229a84c;

typedef struct {
    unsigned short id;
    unsigned short unk_02;
    int unk_04;
} Key;

struct UnkStruct_0229a6e8 {
    char pad_00[0xBC];
    unsigned char b;
};

struct UnkStruct_0229a5cc {
    char pad_00[0xB4];
    short unk_B4;
    char pad_B6[0x1860 - 0xB6];
    u8 unk_1860[0x800];
    u8 unk_2060[0x800];
};

struct UnkStruct_0229a4d4 {
    unsigned char pad_00[0x9c];
    int unk_9C;
    unsigned char pad_A0[4];
    int unk_A4;
    unsigned char pad_A8[0x0c];
    short unk_B4;
};

typedef struct {
    char pad_00[0x9C];
    int unk_9C;
    int unk_A0;
} UnkStruct_0229a45c;

extern void func_02070b84(void *);
extern void *func_02062fbc(UnkStruct_0229ad74_2 *c);
extern void func_020a8c1c(void *h);
extern int func_02062ea4(UnkStruct_0229ad74_2 *c, u16 *p);
extern void *func_020a8bb8(void *h, UnkStruct_0229ad74_2 *c);
extern void func_02070a04(void *h, int a, int b);
extern void *func_02062f4c(UnkStruct_0229ad74_2 *c);
extern int func_02070918(void *a, int b, int c, int d, int e, int f);
extern void func_02070a98(void *receiver, int p2, int p3, int p4, unsigned char p5, unsigned char p6, int flag);
extern void func_0207099c(void *a);
extern void func_02070adc(int a, int b, int c, int d, int e, int f, int g);
extern int func_0207094c(int a, int b);
extern void func_ov142_02299a54(void *self);
extern void func_ov142_022999ec(void *self);
extern void func_ov142_02299a08(void *self);
extern void func_ov142_02299ab8(void *self);
extern void func_ov142_02299658(void *self, int);
extern int func_020984e8(void);
extern int func_0204c2b4(volatile unsigned short *);
extern int func_020996ac(int);
extern int func_0203cdcc(int, volatile unsigned short *);
extern int data_ov142_0229c5e4;
extern void *data_ov142_0229c5ec[];
extern void MIi_CpuClear16(u16, void *, unsigned int);
extern void MIi_CpuCopy16(void *, void *, unsigned int);
extern int func_ov142_02299668(char *p, int a);
extern void func_ov142_02299648(char *p, int a);
extern int func_020b9bbc(char *p1, char *p2, int a, int b, int c);
extern void func_0200284c(int arg0, int arg1, int arg2);
extern void func_0206fdd4(char *a, int b, int c, int d, int e, int f);

int func_ov142_0229a76c(short *base, unsigned short *out, unsigned short step, int count, int index);
int func_ov142_0229a6f8(short *a, unsigned short *out, unsigned short id, int count, int base);
short func_ov142_0229a6e8(struct UnkStruct_0229a6e8 *p);
short func_ov142_0229a6d8(void *self);
void *func_ov142_0229a644(void *base, int idx);
void func_ov142_0229a4d4(struct UnkStruct_0229a4d4 *self, int value);
void func_ov142_0229a3c0(char *self);

void *func_ov142_0229ae8c(struct UnkStruct_0229ae8c *self)
{
    if (self->index >= 14) {
        return (char *) self + 0x8dc;
    } else {
        self->index++;
        return (char *) self + 0x360 + 108 * (self->index - 1);
    }
}

void func_ov142_0229ae60(void *arg0)
{
    int i;
    char *p;
    char *base;

    p = (char *) arg0 + 0xbb;
    *p = 0;
    base = (char *) arg0 + 0x360;
    for (i = 0; i < 14; i++) {
        func_02070b84(base + i * 0x6c);
    }
}

void func_ov142_0229ad74(UnkStruct_0229ad74 *self)
{
    UnkStruct_0229ad74_2 ctx;
    u16 tmp;
    int i;
    void *h;
    int limit;
    int row;
    int col;
    u16 *src;

    func_02062fbc(&ctx);
    row = self->unk_B4;
    src = (u16 *) func_ov142_0229a644((void *) self, row);
    col = (row + 9) % 9;
    limit = (int) func_ov142_0229a6d8((void *) self);
    for (i = 0; i < 9; i++) {
        h = 0;
        if (row < 0 || row >= limit) {
            self->arr[col] = 0xfff1;
            h = func_ov142_0229ae8c((struct UnkStruct_0229ae8c *) self);
            func_020a8c1c(h);
        } else {
            u16 *q = (u16 *) ((char *) self + col * 2 + 0x184e);
            u16 val = *src;
            if (val != *q) {
                *q = val;
                h = func_ov142_0229ae8c((struct UnkStruct_0229ae8c *) self);
                tmp = *src;
                func_02062ea4(&ctx, &tmp);
                func_020a8bb8(h, &ctx);
            }
            src++;
        }
        if (h != 0) {
            func_02070adc((int) h, 4, col * 0x1a + 0x52, 0xd, 0xf, 8, 0);
            func_02070a04(h, 0, 0);
        }
        row++;
        col++;
        if (col >= 9) {
            col = 0;
        }
    }
    func_02062f4c(&ctx);
}

void func_ov142_0229ace4(void *param)
{
    void *obj;
    int val;

    obj = func_ov142_0229ae8c((struct UnkStruct_0229ae8c *) param);
    val = (int) func_ov142_0229a6d8(param);
    func_02070918(obj, val, 3, 0, 0, 0);
    func_02070a98(obj, 6, 0x156, 3, 0xe, 4, 0);
    func_0207099c(obj);

    obj = func_ov142_0229ae8c((struct UnkStruct_0229ae8c *) param);
    val = (int) func_ov142_0229a6e8((struct UnkStruct_0229a6e8 *) param);
    func_02070918(obj, val, 3, 0, 0, 0);
    func_02070a98(obj, 6, 0x15a, 3, 0xe, 4, 0);
    func_02070a04(obj, 0, 0);
}

void func_ov142_0229ac9c(int a, int b)
{
    int ret;

    ret = (int) func_ov142_0229ae8c((struct UnkStruct_0229ae8c *) a);
    func_02070918((void *) ret, b, 8, 0, 0, 1);
    func_02070adc(ret, 6, 0x15d, 8, 0xe, 4, 1);
    func_0207099c((void *) ret);
}

void func_ov142_0229ac58(int a0, int a1, int a2, int a3, unsigned char a4, int a5)
{
    int t;
    t = (int) func_ov142_0229ae8c((struct UnkStruct_0229ae8c *) a0);
    func_0207094c(t, a1);
    func_02070adc(t, 6, a2, a3, a4, 4, 0);
    func_02070a04((void *) t, a5, 0);
}

void func_ov142_0229ac38(int a0)
{
    func_ov142_0229ac58(a0, 0x53, 0x15d, 8, 14, 1);
}

void func_ov142_0229abfc(void *object)
{
    int x;
    x = (int) func_ov142_0229ae8c((struct UnkStruct_0229ae8c *) object);
    func_020a8c1c((void *) x);
    func_02070adc(x, 6, 0x15d, 8, 14, 4, 0);
    func_02070a04((void *) x, 0, 0);
}

void func_ov142_0229ab80(UnkStruct_0229ab80 *self, unsigned char value)
{
    if (self->bc == value) {
        return;
    }
    self->bc = value;
    self->bd = value;
    self->unk_A4 = ((int) func_ov142_0229a6d8(self) - 8) << 4;
    if (self->unk_A4 < 0) {
        self->unk_A4 = 0;
    }
    func_ov142_0229a4d4((struct UnkStruct_0229a4d4 *) self, 0);
    self->unk_A0 = 0;
    func_ov142_02299a54(self);
    if (self->unk_A4 == 0) {
        func_ov142_022999ec(self);
    } else {
        func_ov142_02299a08(self);
    }
    func_ov142_02299ab8(self);
    func_ov142_02299658(self, 8);
}

void func_ov142_0229ab68(struct UnkStruct_0229ab68 *self, unsigned char val)
{
    if (val == self->unk_BD) {
        return;
    }
    self->unk_BD = val;
    self->unk_C2 = 1;
}

void func_ov142_0229a9bc(UnkStruct_0229a9bc *self)
{
    int i;
    unsigned int f1, f2, f3, f4, f5, f6, f7, f8, f9;
    volatile unsigned short v;
    unsigned short a, b;
    int ctx;
    int n;
    unsigned short id;

    n = 0;
    self->c4 = 0;
    self->d6 = 0;
    id = 0x3000;
    v = 0xfff1;
    ctx = func_020984e8();

    for (i = 0; i < 0x6e9; i++) {
        v = id;
        f1 = 0;
        a = v;
        b = v;
        if (b >= 0x45dc && a <= 0x47d7) {
            f1 = 1;
        }
        if (f1 == 0) {
            f2 = 0;
            if (a >= 0x4384 && a <= 0x4463) {
                f2 = 1;
            }
            if (f2 == 0) {
                f3 = 0;
                if (a >= 0x42a4 && a <= 0x4383) {
                    f3 = 1;
                }
                if (f3 == 0) {
                    f4 = 0;
                    if (a >= 0x3e24 && a <= 0x3ea3) {
                        f4 = 1;
                    }
                    if (f4 == 0) {
                        f5 = 0;
                        if (a >= 0x3984 && a <= 0x3d83) {
                            f5 = 1;
                        }
                        if (f5 == 0) {
                            f6 = 0;
                            if (a >= 0x450c && a <= 0x45db) {
                                f6 = 1;
                            }
                            if (f6 == 0) {
                                f7 = 0;
                                if (a >= 0x3fa4 && a <= 0x40a3) {
                                    f7 = 1;
                                }
                                if (f7 == 0) {
                                    f8 = 0;
                                    if (a >= 0x4124 && a <= 0x4223) {
                                        f8 = 1;
                                    }
                                    if (f8 == 0) {
                                        f9 = 0;
                                        if (a >= 0x40a4 && a <= 0x4123) {
                                            f9 = 1;
                                        }
                                        if (f9 == 0) {
                                            if (func_0204c2b4(&v) != 0) {
                                                self->d6 = (short) (self->d6 + 1);
                                                if (func_0203cdcc(func_020996ac(ctx), &v) != 0) {
                                                    self->arr[n] = id;
                                                    n++;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        id = id + 4;
    }
    self->c4 = n;
}

void func_ov142_0229a988(UnkStruct_0229a988 *p)
{
    p->unk_D8 = 0;
    p->unk_C6 = (unsigned short) func_ov142_0229a6f8((short *) p, (unsigned short *) ((char *) p + 0x11d8), 0x1100, 0x44, 1);
}

void func_ov142_0229a954(UnkStruct_0229a954 *self)
{
    self->unk_DA = 0;
    self->unk_C8 = (unsigned short) func_ov142_0229a6f8((short *) self, (unsigned short *) (&self->unk_1260), 0x1144, 0x44, 2);
}

void func_ov142_0229a91c(void *self)
{
    *(short *) ((char *) self + 0xDC) = 0;
    *(short *) ((char *) self + 0xCA) =
        func_ov142_0229a76c((short *) self, (unsigned short *) ((char *) self + 0x12E8), 0x3984, 0x100, 3);
}

void func_ov142_0229a8e8(char *self)
{
    *(unsigned short *) (self + 0xde) = 0;
    *(unsigned short *) (self + 0xcc) =
        (unsigned short) func_ov142_0229a76c((short *) self, (unsigned short *) (self + 0x14e8), 0x3e24, 0x20, 4);
}

void func_ov142_0229a8b4(UnkStruct_0229a8b4 *self)
{
    self->unk_E2 = 0;
    self->unk_D0 = (unsigned short) func_ov142_0229a76c((short *) self, (unsigned short *) (&self->unk_1668), 0x1003, 0x40, 6);
}

void func_ov142_0229a880(UnkStruct_0229a880 *obj)
{
    int ret;
    obj->unk_E4 = 0;
    ret = func_ov142_0229a76c((short *) obj, (unsigned short *) obj->unk_16E8, 0x45dc, 0x7f, 7);
    obj->unk_D2 = ret;
}

void func_ov142_0229a84c(UnkStruct_0229a84c *self)
{
    self->unk_E6 = 0;
    self->unk_D4 =
        (unsigned short) func_ov142_0229a76c((short *) self, (unsigned short *) ((char *) self + 0x17e6), 0x450c, 0x34, 8);
}

void func_ov142_0229a7e0(char *self)
{
    unsigned long total;
    unsigned long ret;

    *(unsigned short *) (self + 0xe0) = 0;

    ret = func_ov142_0229a76c((short *) self, (unsigned short *) (self + 0x1528), (unsigned long) 0x3fa4, (unsigned long) 0x40,
                              5);
    total = ret;
    ret = func_ov142_0229a76c((short *) self, (unsigned short *) (self + 0x1528 + total * 2), (unsigned long) 0x40a4,
                              (unsigned long) 0x20, 5);
    total += ret;
    ret = func_ov142_0229a76c((short *) self, (unsigned short *) (self + 0x1528 + total * 2), (unsigned long) 0x4124,
                              (unsigned long) 0x40, 5);
    total += ret;

    *(unsigned short *) (self + 0xce) = total;
}

int func_ov142_0229a76c(short *base, unsigned short *out, unsigned short step, int count, int index)
{
    int i = 0;
    int saved;
    unsigned short local;
    int j;
    short *p;

    saved = func_020984e8();
    local = 0xfff1;
    j = 0;
    p = base + index;

    while (j < count) {
        local = step;
        if (func_0204c2b4((volatile unsigned short *) (&local))) {
            p[0x6b] = p[0x6b] + 1;
            if (func_0203cdcc(func_020996ac(saved), (volatile unsigned short *) (&local))) {
                out[i] = step;
                i++;
            }
        }
        step = (unsigned short) (step + 4);
        j++;
    }
    return i;
}

int func_ov142_0229a6f8(short *a, unsigned short *out, unsigned short id, int count, int base)
{
    Key key;
    void *h;
    int n;
    int i;
    short *p;

    n = 0;
    key.id = 0xfff1;
    h = (void *) func_020984e8();
    i = 0;
    p = a + base;
    for (; i < count; i++) {
        key.id = id;
        if (func_0204c2b4((volatile unsigned short *) (&key)) != 0) {
            *(short *) ((char *) p + 0xd6) = (short) (*(short *) ((char *) p + 0xd6) + 1);
            if (func_0203cdcc((int) ((void *) func_020996ac((int) h)), (volatile unsigned short *) (&key)) != 0) {
                out[n] = id;
                n++;
            }
        }
        id = (unsigned short) (id + 1);
    }
    return n;
}

short func_ov142_0229a6e8(struct UnkStruct_0229a6e8 *p)
{
    return *(short *) ((char *) p + p->b * 2 + 0xD6);
}

short func_ov142_0229a6d8(void *self)
{
    unsigned char idx;
    short result;

    idx = ((unsigned char *) self)[0xbc];
    result = ((short *) ((char *) self + (idx << 1)))[0x62];
    return result;
}

void *func_ov142_0229a644(void *base, int idx)
{
    int type;
    if ((data_ov142_0229c5e4 & 1) == 0) {
        data_ov142_0229c5ec[0] = (void *) ((char *) base + 0x9d8);
        data_ov142_0229c5ec[1] = (void *) ((char *) base + 0x11d8);
        data_ov142_0229c5ec[2] = (void *) ((char *) base + 0x1260);
        data_ov142_0229c5ec[3] = (void *) ((char *) base + 0x12e8);
        data_ov142_0229c5ec[4] = (void *) ((char *) base + 0x14e8);
        data_ov142_0229c5ec[5] = (void *) ((char *) base + 0x1528);
        data_ov142_0229c5ec[6] = (void *) ((char *) base + 0x1668);
        data_ov142_0229c5ec[7] = (void *) ((char *) base + 0x16e8);
        data_ov142_0229c5ec[8] = (void *) ((char *) base + 0x17e6);
        data_ov142_0229c5e4 |= 1;
    }
    if (idx < 0) {
        idx = 0;
    }
    type = *(unsigned char *) ((char *) base + 0xbc);
    return (char *) data_ov142_0229c5ec[type] + 2 * idx;
}

void func_ov142_0229a5cc(struct UnkStruct_0229a5cc *p)
{
    int r4, r6, r7, zero;
    volatile u16 val;

    r4 = p->unk_B4;
    r6 = (r4 + 9) % 9;
    r4 &= 0xF;

    val = 0x10;
    MIi_CpuClear16(val, &p->unk_2060, 0x800);

    zero = 0;
    r7 = 0;
    do {
        MIi_CpuCopy16(&p->unk_1860[r6 * 128], &p->unk_2060[r4 * 128], 0x80);
        r6++;
        if (r6 >= 9) {
            r6 = zero;
        }
        r4++;
        r4 &= 0xF;
        r7++;
    } while (r7 < 9);

    func_ov142_02299658((void *) p, 2);
}

void func_ov142_0229a540(char *p)
{
    if (func_ov142_02299668(p, 2)) {
        func_ov142_0229a3c0(p);
    }
    if (func_ov142_02299668(p, 0x10)) {
        if (func_020b9bbc(p + 0x96c, p + 0x2860, 6, 0x800, 0)) {
            func_ov142_02299648(p, 0x10);
        }
    }
    if (func_ov142_02299668(p, 4)) {
        func_ov142_02299648(p, 4);
        func_ov142_0229ad74((UnkStruct_0229ad74 *) p);
    }
    if (func_ov142_02299668(p, 8)) {
        func_ov142_02299648(p, 8);
        func_ov142_0229ace4((void *) p);
    }
}

void func_ov142_0229a4d4(struct UnkStruct_0229a4d4 *self, int value)
{
    func_ov142_02299648((char *) self, 0x0C00);
    if (value <= 0) {
        func_ov142_02299658((void *) self, 0x400);
    }
    if (value >= self->unk_A4) {
        func_ov142_02299658((void *) self, 0x800);
    }
    self->unk_9C = value;
    func_0200284c(4, 0, self->unk_9C - 0x20);
    self->unk_B4 = (short) (value >> 4);
    func_ov142_0229a5cc((struct UnkStruct_0229a5cc *) self);
    func_ov142_02299658((void *) self, 4);
}

void func_ov142_0229a45c(UnkStruct_0229a45c *obj)
{
    if (obj->unk_9C == obj->unk_A0) {
        return;
    }
    if (obj->unk_9C > obj->unk_A0) {
        obj->unk_9C = obj->unk_9C - 6;
        if (obj->unk_9C < obj->unk_A0) {
            obj->unk_9C = obj->unk_A0;
        }
    } else {
        obj->unk_9C = obj->unk_9C + 6;
        if (obj->unk_9C > obj->unk_A0) {
            obj->unk_9C = obj->unk_A0;
        }
    }
    func_ov142_0229a4d4((struct UnkStruct_0229a4d4 *) obj, obj->unk_9C);
    func_ov142_02299a54((void *) obj);
}

void func_ov142_0229a3c0(char *self)
{
    int v;
    s16 a, b;
    int d, t;

    if (func_ov142_02299668(self, 0x200) != 0) {
        v = 5;
    } else {
        v = 3;
    }

    func_0206fdd4(self + 0x2060, 0, 0, 0x1f, 0x1f, v);

    if (*(u8 *) (self + 0xbc) == *(u8 *) (self + 0xbe)) {
        a = *(s16 *) (self + 0xb8);
        b = *(s16 *) (self + 0xb4);
        d = a - b;
        if (d >= 0 && d < 9) {
            t = (a & 0xf) << 1;
            func_0206fdd4(self + 0x2060, 0, t, 0x1f, t + 1, 4);
        }
    }

    if (func_020b9bbc(self + 0x948, self + 0x2060, 4, 0x800, 0) != 0) {
        func_ov142_02299648(self, 2);
    }
}
