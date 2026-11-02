/* clock_setter_draw: 23 functions, module ov134
 * mwccarm 1.2/base -O4,s
 * func_ov134_0229bbe8 @ 0x0229bbe8, 0xc4 bytes, Thumb
 * func_ov134_0229bbdc @ 0x0229bbdc, 0xc bytes, Thumb
 * func_ov134_0229bbbc @ 0x0229bbbc, 0x20 bytes, Thumb
 * func_ov134_0229baec @ 0x0229baec, 0xd0 bytes, Thumb
 * func_ov134_0229ba10 @ 0x0229ba10, 0xdc bytes, Thumb
 * func_ov134_0229b954 @ 0x0229b954, 0xbc bytes, Thumb
 * func_ov134_0229b908 @ 0x0229b908, 0x4c bytes, Thumb
 * func_ov134_0229b8dc @ 0x0229b8dc, 0x2c bytes, Thumb
 * func_ov134_0229b890 @ 0x0229b890, 0x4a bytes, Thumb
 * func_ov134_0229b884 @ 0x0229b884, 0xc bytes, Thumb
 * func_ov134_0229b848 @ 0x0229b848, 0x3a bytes, Thumb
 * func_ov134_0229b808 @ 0x0229b808, 0x40 bytes, Thumb
 * func_ov134_0229b7d4 @ 0x0229b7d4, 0x34 bytes, Thumb
 * func_ov134_0229b7a8 @ 0x0229b7a8, 0x2c bytes, Thumb
 * func_ov134_0229b77c @ 0x0229b77c, 0x2c bytes, Thumb
 * func_ov134_0229b750 @ 0x0229b750, 0x2c bytes, Thumb
 * func_ov134_0229b724 @ 0x0229b724, 0x2c bytes, Thumb
 * func_ov134_0229b6dc @ 0x0229b6dc, 0x48 bytes, Thumb
 * func_ov134_0229b6b4 @ 0x0229b6b4, 0x26 bytes, Thumb
 * func_ov134_0229b680 @ 0x0229b680, 0x34 bytes, Thumb
 * func_ov134_0229b63c @ 0x0229b63c, 0x44 bytes, Thumb
 * func_ov134_0229b5f4 @ 0x0229b5f4, 0x46 bytes, Thumb
 * func_ov134_0229b5ac @ 0x0229b5ac, 0x46 bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229bbe8 UnkStruct_0229bbe8;

struct UnkStruct_0229bbe8 {
    char pad_00[0x18];
    char unk_18[0xa3 - 0x18];
    unsigned char unk_A3;
    unsigned char unk_A4;
    char pad_A5[0xb7 - 0xa4 - 1];
    signed char sbyte_b7;
    char pad_B8[0x804 - 0xb7 - 1];
    char unk_804[0x24];
    char unk_828[0x48];
    char unk_870[1];
    char pad_871[0x2070 - 0x870 - 1];
    char unk_2070[1];
};

typedef struct {
    unsigned char pad_00[0xa2];
    unsigned char unk_A2;
    unsigned char unk_A3;
} UnkStruct_0229ba10;

typedef struct {
    u8 pad_00[0xa1];
    u8 b;
} Params;

struct S_0229b884 {
    char pad_00[0xb8];
    int unk_B8;
};

typedef struct {
    unsigned char pad_00[0xa3];
    unsigned char unk_A3;
    unsigned char pad_A4[0x18];
    unsigned char unk_BC;
} UnkStruct_0229b7a8;

struct UnkStruct_0229b77c {
    char pad_00[0xA3];
    unsigned char unk_A3;
    char pad_A4[0x17];
    unsigned char unk_BB;
};

struct unknown {
    char pad_00[0xA3];
    unsigned char unk_A3;
    char pad_A4[0xBA - 0xA3 - 1];
    unsigned char unk_BA;
};

struct Context {
    char pad_00[0x9f];
    volatile unsigned char count;
    char pad_A0[0x38];
};

extern void func_ov134_022996b4(UnkStruct_0229bbe8 *);
extern void func_ov002_0220a544(void *);
extern int func_ov134_022995c0(UnkStruct_0229bbe8 *, int);
extern int func_020b9bbc(void *, void *, unsigned char, int, int);
extern void func_ov134_022995a0(UnkStruct_0229bbe8 *, int);
extern unsigned short data_021fbe40;
extern void MI_CpuCopy8(int, int, int);
extern int func_0209e3ac(void *a, void *b, int n);
extern void *data_021fbe94;
extern void *data_ov134_0229c05c[];
extern void *data_ov134_0229c02c[];
extern unsigned char data_ov134_0229c44c[];
extern unsigned char data_ov134_0229c464[];
extern unsigned char data_ov134_0229c47c[];
extern unsigned char data_ov134_0229c490[];
extern unsigned char data_ov134_0229c4ac[];
extern int func_02002c6c(void *a, void *b, int c, int d, int e, int f);
extern int func_02002d14(void *a, void *b, int c, int d, int e, int f);
extern int func_02002ca4(void *a, void *b, int c);
extern int func_02064af4(void *a, void *b, int c);
extern void func_ov134_0229a8e8(void *self);
extern u8 data_ov134_0229c3f4[];
extern u8 data_ov134_0229c410[];
extern u8 data_ov134_0229c42c[];
extern u32 data_ov134_0229c020[];
extern u32 func_02064b2c(u32 val, void *obj, int mask, u32 *out);
extern u64 _s32_div_f(int a, int b);
extern int func_02002a88(u32 addr, int a, int b, int c, int d);
extern void func_020e993c(void *obj, u32 val);
extern int func_02002cd8(void *data, void *obj, int a, int b, int c);
extern int func_0209de88(int year, int month, int day);
extern unsigned char data_ov134_0229bf6c[];
extern struct UnkStruct_0229b77c;
extern void func_02070b84(void *p);
extern int func_0207094c(int a, int b);
extern void func_02070adc(int a, int b, int c, int d, int e, int f, int g);
extern void func_02070a04(int a, int b, int c);
extern void func_020709c4(int a0, int a1, int a2);
extern int func_02070918(void *, int, int, int, int, int);
extern void func_0207099c(void *);

void func_ov134_0229b8dc(void *param);
int func_ov134_0229b848(int a, unsigned int k, u8 *p);
void func_ov134_0229b7d4(void *p);
void func_ov134_0229b7a8(UnkStruct_0229b7a8 *self);
void func_ov134_0229b77c(struct UnkStruct_0229b77c *p);
void func_ov134_0229b750(struct unknown *p);
void func_ov134_0229b724(void *obj);
void func_ov134_0229b63c(int p0, int p1, int p2, int p3, unsigned char p4, int p5, unsigned char p6, unsigned char p7);
void func_ov134_0229b5ac(int arg0, int arg1, int arg2, int arg3, int arg4, unsigned char arg5, unsigned char arg6);

void func_ov134_0229bbe8(UnkStruct_0229bbe8 *self)
{
    func_ov134_022996b4(self);
    func_ov002_0220a544(self->unk_18);
    if (func_ov134_022995c0(self, 2) != 0) {
        if (func_020b9bbc(self->unk_804, self->unk_870, self->unk_A3, 0x800, 0) != 0) {
            func_ov134_022995a0(self, 2);
        }
    }
    if (func_ov134_022995c0(self, 1) != 0) {
        if (func_020b9bbc(self->unk_828, self->unk_2070, self->unk_A4, 0x800, 0) != 0) {
            func_ov134_022995a0(self, 1);
        }
    }
    if (self->sbyte_b7 > 0) {
        if (data_021fbe40 & 0x40) {
            self->sbyte_b7 = 0;
        }
    } else if (self->sbyte_b7 < 0) {
        if (data_021fbe40 & 0x80) {
            self->sbyte_b7 = 0;
        }
    }
}

void func_ov134_0229bbdc(int p0, int p1)
{
    MI_CpuCopy8((p0 + 184), p1, 8);
}

int func_ov134_0229bbbc(char *param)
{
    if (func_0209e3ac(param + 0xc8, param + 0xb8, 0x3f) == 1) {
        return 1;
    }
    return 0;
}

int func_ov134_0229baec(unsigned char *self)
{
    void *p = data_021fbe94;

    func_02002c6c(data_ov134_0229c44c, p, self[0xa2], 0x10, 0x10, 0x80);
    func_02002d14(data_ov134_0229c464, p, self[0xa2], 1, 1, 0xa);
    func_02002d14(data_ov134_0229c05c[self[0xa0]], p, self[0xa2], 1, 1, 2);
    func_02002ca4(data_ov134_0229c47c, p, self[0xa2]);
    func_02064af4(data_ov134_0229c02c[self[0xa0]], self + 0x870, 0x800);
    func_ov134_0229a8e8(self);
    func_02064af4(data_ov134_0229c490, self + 0x1070, 0x800);
    return func_02064af4(data_ov134_0229c4ac, self + 0x2870, 0x20);
}

void func_ov134_0229ba10(UnkStruct_0229ba10 *self, unsigned char param)
{
    func_ov134_0229b63c((int) self, (unsigned char) self->unk_A3, 0x18a, 3, 0xb2, 0, 0xf, 0);
    func_ov134_0229b63c((int) self, (unsigned char) self->unk_A3, 0x196, 3, 0xb3, 0, 0xf, 0);
    func_ov134_0229b63c((int) self, (unsigned char) self->unk_A3, 0x1a2, 3, 0xb4, 0, 0xf, 0);
    func_ov134_0229b63c((int) self, (unsigned char) self->unk_A3, 0x1bc, 3, 0xb5, 0, 0xf, 0);
    func_ov134_0229b63c((int) self, (unsigned char) self->unk_A3, 0x1c8, 3, 0xb6, 0, 0xf, 0);
    func_ov134_0229b8dc(self);
    func_ov134_0229b63c((int) self, (unsigned char) self->unk_A2, 0x54, 0x10, param, 1, 0xf, 0xe);
}

int func_ov134_0229b954(Params *p)
{
    u32 prev;
    u32 unused;
    u32 addr;
    u32 offset;
    int i;
    u8 byte;
    void *obj;
    long long q;
    u32 hi;
    obj = data_021fbe94;
    func_02002d14(data_ov134_0229c3f4, obj, 8, 4, 4, 10);
    func_02002c6c(data_ov134_0229c410, obj, 8, 0xc0, 0xc0, 0x1df);
    byte = p->b;
    prev = func_02064b2c(data_ov134_0229c020[((unsigned int) byte) >> 2], obj, -4, &unused);
    q = _s32_div_f(byte, 4);
    hi = (u32) (q >> 32);
    addr = prev;
    addr = addr + (hi << 8);
    offset = 0xc0;
    i = 0;
    for (; i < 8; i++) {
        func_02002a88(addr, 8, offset, offset, offset + 7);
        addr += 0x400;
        offset += 0x20 ^ 0;
    }

    func_020e993c(obj, prev);
    return func_02002cd8(data_ov134_0229c42c, obj, 8, p->b, 4);
}

void func_ov134_0229b908(unsigned char *X)
{
    int local0;
    local0 = data_ov134_0229bf6c[func_0209de88(X[0xBD], X[0xBC], X[0xBB])];
    func_ov134_0229b63c((int) X, (unsigned char) X[0xA3], 424, 7, local0, 1, 15, 0);
}

void func_ov134_0229b8dc(void *param)
{
    func_ov134_0229b7d4(param);
    func_ov134_0229b7a8((UnkStruct_0229b7a8 *) param);
    func_ov134_0229b77c((struct UnkStruct_0229b77c *) param);
    func_ov134_0229b750((struct unknown *) param);
    func_ov134_0229b724(param);
    func_ov134_0229b908((unsigned char *) param);
}

void func_ov134_0229b890(int arg, unsigned int mode)
{
    switch (mode) {
        case 0:
            func_ov134_0229b7d4((void *) arg);
            break;
        case 1:
            func_ov134_0229b7a8((UnkStruct_0229b7a8 *) arg);
            break;
        case 2:
            func_ov134_0229b77c((struct UnkStruct_0229b77c *) arg);
            break;
        case 3:
            func_ov134_0229b750((struct unknown *) arg);
            break;
        case 4:
            func_ov134_0229b724((void *) arg);
            break;
        case 5:
            func_ov134_0229b908((unsigned char *) arg);
            break;
    }
}

int func_ov134_0229b884(struct S_0229b884 *s, int b)
{
    return func_ov134_0229b848((int) s, b, (u8 *) (&s->unk_B8));
}

int func_ov134_0229b848(int a, unsigned int k, u8 *p)
{
    switch (k) {
        case 0:
            return p[5];
        case 1:
            return p[4];
        case 2:
            return p[3];
        case 3:
            return p[2];
        case 4:
            return p[1];
        case 5:
            return 0;
    }
    return 0xff;
}

void func_ov134_0229b808(u8 *self, unsigned int k, int v)
{
    switch (k) {
        case 0:
            self[0xbd] = (u8) v;
            break;
        case 1:
            self[0xbc] = (u8) (v + 1);
            break;
        case 2:
            self[0xbb] = (u8) (v + 1);
            break;
        case 3:
            self[0xba] = (u8) v;
            break;
        case 4:
            self[0xb9] = (u8) v;
            break;
        case 5:
            break;
    }
}

void func_ov134_0229b7d4(void *p)
{
    int tmp = *(unsigned char *) ((char *) p + 0xbd) + 0x7d0;
    func_ov134_0229b5ac((int) p, *(unsigned char *) ((char *) p + 0xa3), 0x180, 5, tmp, 0xf, 0);
}

void func_ov134_0229b7a8(UnkStruct_0229b7a8 *self)
{
    func_ov134_0229b5ac((int) self, (unsigned char) self->unk_A3, 0x190, 3, (unsigned char) self->unk_BC, 15, 0);
}

void func_ov134_0229b77c(struct UnkStruct_0229b77c *p)
{
    func_ov134_0229b5ac((int) p, (unsigned char) p->unk_A3, 0x19c, 3, (unsigned char) p->unk_BB, 15, 0);
}

void func_ov134_0229b750(struct unknown *p)
{
    func_ov134_0229b5ac((int) p, (unsigned char) p->unk_A3, 0x1B6, 3, (unsigned char) p->unk_BA, 0xF, 0);
}

void func_ov134_0229b724(void *obj)
{
    int b9 = ((unsigned char *) obj)[0xb9];
    int a3 = ((unsigned char *) obj)[0xa3];
    func_ov134_0229b5ac((int) obj, a3, 0x1c2, 3, b9, 15, 0);
}

void func_ov134_0229b6dc(unsigned char *p)
{
    int r3 = 3;
    int val = p[0xad];
    int idx = p[0xa5];
    switch (idx) {
        case 0:
            r3 = 5;
            val += 0x7d0;
            break;
        case 1:
        case 2:
            val += 1;
            break;
        default:
            break;
    }
    func_ov134_0229b5ac((int) p, 8, 0xcb, r3, val, 0xf, 0);
}

void func_ov134_0229b6b4(void *p)
{
    int i;
    char *q;
    char *r;

    q = (char *) p + 0x9f;
    *q = 0;
    r = (char *) p + 0xd8;
    for (i = 0; i < 17; i++) {
        func_02070b84(r + i * 0x6c);
    }
}

void *func_ov134_0229b680(struct Context *self)
{
    if (self->count >= 0x11) {
        return (char *) self + 0x798;
    }
    self->count = self->count + 1;
    return (char *) self + 0xd8 + 0x6c * (self->count - 1);
}

void func_ov134_0229b63c(int p0, int p1, int p2, int p3, unsigned char p4, int p5, unsigned char p6, unsigned char p7)
{
    int result;

    result = (int) func_ov134_0229b680((struct Context *) p0);
    func_0207094c(result, p4);
    func_02070adc(result, p1, p2, p3, p6, p7, 0);
    func_02070a04(result, p5, 0);
}

void func_ov134_0229b5f4(int a0, int a1, int a2, int a3, unsigned char a4, int a5)
{
    int tmp;
    tmp = (int) func_ov134_0229b680((struct Context *) a0);
    func_0207094c(tmp, (unsigned char) a4);
    func_02070adc(tmp, a1, a2, a3, 15, 0, 0);
    func_020709c4(tmp, 1, -((a3 - a5) << 2));
}

void func_ov134_0229b5ac(int arg0, int arg1, int arg2, int arg3, int arg4, unsigned char arg5, unsigned char arg6)
{
    void *obj;
    int tmp1;
    int tmp2;
    int tmp3;

    obj = func_ov134_0229b680((struct Context *) arg0);
    tmp1 = 0;
    tmp2 = 0;
    func_02070918(obj, arg4, 4, 0, tmp1, tmp2);
    tmp1 = arg5;
    tmp2 = arg6;
    tmp3 = 0;
    func_02070adc((int) obj, arg1, arg2, arg3, tmp1, tmp2, tmp3);
    func_0207099c(obj);
}
