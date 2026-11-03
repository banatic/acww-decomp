/* bbs_board_2: 29 functions, module ov113
 * mwccarm 1.2/base -O4,s
 * func_ov113_0229a390 @ 0x0229a390, 0x8 bytes, Thumb
 * func_ov113_0229a350 @ 0x0229a350, 0x40 bytes, Thumb
 * func_ov113_0229a32c @ 0x0229a32c, 0x24 bytes, Thumb
 * func_ov113_0229a2c4 @ 0x0229a2c4, 0x68 bytes, Thumb
 * func_ov113_0229a274 @ 0x0229a274, 0x50 bytes, Thumb
 * func_ov113_0229a1b8 @ 0x0229a1b8, 0xbc bytes, Thumb
 * func_ov113_0229a194 @ 0x0229a194, 0x24 bytes, Thumb
 * func_ov113_0229a148 @ 0x0229a148, 0x4c bytes, Thumb
 * func_ov113_0229a120 @ 0x0229a120, 0x28 bytes, Thumb
 * func_ov113_0229a108 @ 0x0229a108, 0x16 bytes, Thumb
 * func_ov113_0229a0ec @ 0x0229a0ec, 0x1c bytes, Thumb
 * func_ov113_0229a004 @ 0x0229a004, 0xe8 bytes, Thumb
 * func_ov113_02299f10 @ 0x02299f10, 0xf4 bytes, Thumb
 * func_ov113_02299e98 @ 0x02299e98, 0x78 bytes, Thumb
 * func_ov113_02299e20 @ 0x02299e20, 0x78 bytes, Thumb
 * func_ov113_02299df4 @ 0x02299df4, 0x2c bytes, Thumb
 * func_ov113_02299df0 @ 0x02299df0, 0x2 bytes, Thumb
 * func_ov113_02299db8 @ 0x02299db8, 0x38 bytes, Thumb
 * func_ov113_02299da4 @ 0x02299da4, 0x12 bytes, Thumb
 * func_ov113_02299d94 @ 0x02299d94, 0xe bytes, Thumb
 * func_ov113_02299d84 @ 0x02299d84, 0xe bytes, Thumb
 * func_ov113_02299cd0 @ 0x02299cd0, 0xb4 bytes, Thumb
 * func_ov113_02299c44 @ 0x02299c44, 0x8a bytes, Thumb
 * func_ov113_02299aa4 @ 0x02299aa4, 0x1a0 bytes, Thumb
 * func_ov113_02299a80 @ 0x02299a80, 0x24 bytes, Thumb
 * func_ov113_02299a44 @ 0x02299a44, 0x3c bytes, Thumb
 * func_ov113_02299a08 @ 0x02299a08, 0x3a bytes, Thumb
 * func_ov113_022999c4 @ 0x022999c4, 0x44 bytes, Thumb
 * func_ov113_022999a4 @ 0x022999a4, 0x20 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x9b];
    unsigned char unk_9B;
} UnkStruct_0229a1b8;

typedef struct {
    char pad_00[0x2b20];
    void *unk_2B20;
} UnkStruct_0229a120;

typedef struct UnkStruct_02299e20 {
    char pad_00[0xa0];
} UnkStruct_02299e20;

struct UnkStruct_02299d94 {
    char pad_00[0x98];
    unsigned short unk_98;
};

typedef struct UnkStruct_02299cd0 UnkStruct_02299cd0;

struct UnkStruct_02299cd0 {
    u8 unk_00[0x9b];
    u8 unk_9B;
    u8 p1;
    u8 unk_9D;
    u8 unk_9E;
};

typedef struct UnkStruct_02299c44 {
    char pad_00[0x9b];
    u8 unk_9B;
} UnkStruct_02299c44;

typedef struct {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[0xd];
    volatile unsigned char unk_9A;
    unsigned char unk_9B;
    unsigned char pad_9C;
    unsigned char unk_9D;
} UnkStruct_02299aa4;

struct UnkStruct_02299a80 {
    char pad_00[0x9d];
    unsigned char unk_9D;
    unsigned char unk_9E;
};

extern int func_020b9bbc(void *a, void *b, int c, int d, int e);
extern void func_02001c30(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern unsigned int data_021fbe94;
extern char data_ov113_0229ad18;
extern char data_ov113_0229ad2c;
extern char data_ov113_0229ad40;
extern int func_02002d14(const char *a, unsigned int b, int c, int d, int e, int f);
extern int func_02064af4(const char *a, void *b, int c);
extern int func_02002b40(void *a, int b, int c, int d);
extern int func_02002c6c(const char *a, unsigned int b, int c, int d, int e, int f);
extern int func_ov002_02208054(void *self, int flag);
extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_0229a1b8 *self);
extern int func_ov113_02299644(UnkStruct_0229a1b8 *self, int arg);
extern void func_ov113_0229990c(UnkStruct_0229a1b8 *self);
extern void func_ov113_022998ec(UnkStruct_0229a1b8 *self);
extern unsigned short data_021fbe40[2];
extern int func_ov002_02209f64(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char);
extern int func_0208e484(void *);
extern void func_ov113_02299980(void *);
extern void func_ov113_022998cc(void *);
extern void func_ov002_0220a164(void *);
extern void func_ov113_022998ac(void *ptr);
extern void *func_020781d0(unsigned char *, int index);
extern unsigned short *func_020782cc(void *record);
extern int func_0206de88(const unsigned short *, void *, void *, u32, u32, u32, u32);
extern void func_020a8c1c(void *);
extern void func_02070870(void *, const unsigned short *, u32, u32, u32);
extern void func_02070a54(void *, void *, u32, u32, u32);
extern void func_02070a04(void *, u32, u32);
extern int func_020b9c10(void *, void *, u32, u32, u32, u32);
extern unsigned char data_021eed68[];
extern int func_02078288(void *);
extern int func_02078290(void *);
extern int func_02078298(void *);
extern int _s32_div_f(int a, int b);
extern void func_020708e4(void *, void *, int);
extern int func_020984d4(void);
extern int func_02078268(int, int);
extern void func_0206fdd4(void *, int, int, int, int, int);
extern int func_02078234(int);
extern void func_02078248(int, int);
extern void func_02070a98(void *receiver, int p2, int p3, int p4, unsigned char p5, unsigned char p6, int flag);
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern void func_0200467c(int command);
extern unsigned char *func_ov002_022080a0(UnkStruct_02299aa4 *o, unsigned char value);
extern __arm void *func_020ee45c(UnkStruct_02299aa4 *o);
extern void func_ov092_02299324(void *p, int a, int b);
extern int func_02077ec4(void);
extern void func_ov002_0220a0b4(char *a0, int r1, int r2);
extern void func_ov002_0220a374(char *a0, int r1);

void func_ov113_0229a350(void *p);
void func_ov113_0229a108(int param);
void func_ov113_0229a0ec(void *r0);
void func_ov113_02299db8(void *p, int index, void *a2, void *a3, int arg5, int arg6);
int func_ov113_02299da4(unsigned char *ptr, unsigned short mask);
void func_ov113_02299d94(struct UnkStruct_02299d94 *self, unsigned short val);
void func_ov113_02299d84(void *r0, unsigned short r1);
int func_ov113_02299cd0(UnkStruct_02299cd0 *self);
int func_ov113_02299aa4(UnkStruct_02299aa4 *o);
void func_ov113_02299a80(struct UnkStruct_02299a80 *self);
void func_ov113_02299a44(char *a0);
int func_ov113_022999c4(int param);
unsigned char func_ov113_022999a4(unsigned char *p);

void func_ov113_0229a390(void *arg0)
{
    func_ov113_0229a350((void *) arg0);
}

void func_ov113_0229a350(void *p)
{
    if (func_ov113_02299da4((unsigned char *) p, 1)) {
        if (func_020b9bbc((char *) p + 0x26c4, (char *) p + 0xa0, 2, 0x800, 0)) {
            func_ov113_02299d84(p, 1);
        }
    }
}

void func_ov113_0229a32c(void)
{
    func_02001c30(0);
    func_020029e8(2, 1);
    func_020028bc(2, 0, 0, 0);
}

void func_ov113_0229a2c4(void *arg0)
{
    unsigned int temp;
    char *p;

    temp = data_021fbe94;
    p = (char *) arg0;

    func_02002d14(&data_ov113_0229ad18, temp, 2, 8, 8, 14);
    func_02064af4(&data_ov113_0229ad2c, p + 0xa0, 0x800);
    p += 0xa0;
    func_02002b40(p, 2, 0x800, 0);
    func_02002c6c(&data_ov113_0229ad40, temp, 2, 16, 16, 319);
}

void func_ov113_0229a274(void *self)
{
    unsigned int cond;

    if (func_ov002_02208054(self, 1)) {
        func_ov113_0229a0ec(self);
        return;
    }

    cond = (data_021fbdd8 && data_021fbddc) ? 1 : 0;
    if (cond > 0) {
        if (func_ov113_02299cd0((UnkStruct_02299cd0 *) self)) {
            func_ov113_02299aa4((UnkStruct_02299aa4 *) self);
        }
    }
}

void func_ov113_0229a1b8(UnkStruct_0229a1b8 *self)
{
    unsigned short v;

    if (func_ov002_02208014(self) != 0) {
        func_ov113_0229a108((int) self);
        return;
    }

    if (func_ov113_02299644(self, func_ov002_02208008(self)) != 0) {
        func_ov113_0229990c(self);
        return;
    }

    v = data_021fbe40[1];

    if (v & 1) {
        func_ov113_022998ec(self);
        return;
    }

    if (v & 2) {
        self->unk_9B = 3;
        func_ov113_02299980((void *) self);
        func_ov113_02299aa4((UnkStruct_02299aa4 *) self);
        return;
    }

    if (v & 0x200) {
        self->unk_9B = 5;
        if (func_ov113_02299aa4((UnkStruct_02299aa4 *) self) != 0) {
            func_ov113_02299980((void *) self);
        }
        return;
    }

    if (v & 0x100) {
        self->unk_9B = 4;
        if (func_ov113_02299aa4((UnkStruct_02299aa4 *) self) != 0) {
            func_ov113_02299980((void *) self);
        }
        return;
    }
}

void func_ov113_0229a194(void *arg0)
{
    if (!func_ov002_02209f64((char *) arg0 + 0x2b20)) {
        func_ov002_02208098(arg0, *(unsigned char *) ((char *) arg0 + 0x9c));
    }
}

void func_ov113_0229a148(void *arg)
{
    char *p = (char *) arg;
    if (func_0208e484(p + 0x2b20) != 0) {
        if (func_ov113_02299aa4((UnkStruct_02299aa4 *) p) != 0) {
            if ((unsigned char) (*(unsigned char *) (p + 0x9b) + 0xfe) <= 1) {
                func_ov113_02299980(p);
            } else {
                func_ov002_0220a164(p + 0x2b20);
            }
        } else {
            func_ov113_022998cc(p);
        }
    }
}

void func_ov113_0229a120(UnkStruct_0229a120 *self)
{
    if (func_0208e484(&self->unk_2B20)) {
        func_ov113_022998ac(self);
        func_ov002_02208098(self, 1);
    }
}

void func_ov113_0229a108(int param)
{
    func_ov113_02299980((void *) param);
    func_ov002_02208098((void *) param, 0);
}

void func_ov113_0229a0ec(void *r0)
{
    extern void func_ov002_02207fc0(void *);
    extern unsigned char *func_ov002_02208098(void *, unsigned char value);
    void *r4 = r0;
    func_ov113_02299a44((char *) r4);
    func_ov002_02207fc0(r4);
    func_ov002_02208098(r4, 1);
}

void func_ov113_0229a004(unsigned char *self, int index)
{
    void *a;
    u32 arr[7];
    u32 tmp;
    u32 zero1;
    u32 zero2;
    int i;
    a = func_020781d0(data_021eed68, index);
    func_0206de88(func_020782cc(a), arr, &tmp, 0x60, 0x10, 0xa0, 6);
    zero1 = 0;
    for (i = 0; i < 6; i++) {
        unsigned char *base1;
        unsigned char *p;
        u32 offset;
        u32 diff;
        unsigned short *t;
        diff = arr[i + 1] - arr[i];
        offset = i;
        offset = offset * 0x6c;
        base1 = self + 0x2898;
        p = base1;
        p = p + offset;
        func_020a8c1c(p);
        if (diff != 0) {
            t = func_020782cc(a);
            func_02070870(p, t + arr[i], diff, zero1, zero1);
        }
    }

    zero2 = 0;
    for (i = 0; i < 6; i++) {
        unsigned char *base1;
        unsigned char *base2;
        unsigned char *p;
        unsigned char *dst;
        base1 = self + 0x2898;
        base2 = self + 0x8a0;
        p = base1 + (i * 0x6c);
        dst = base2 + (i * 0x500);
        func_02070a54(p, dst, 0x14, 0xe, 0xd);
        func_02070a04(p, zero2, zero2);
    }

    func_020b9c10(self + 0x26a0, self + 0x8a0, 2, 0x11, 0x11, 0x100);
}

void func_ov113_02299f10(unsigned char *self, int arg1)
{
    void *r4;
    u16 arr[5];

    r4 = func_020781d0((unsigned char *) (((unsigned char *) data_021eed68)), arg1);
    arr[0] = 0xff12;
    arr[1] = 0xff10;
    arr[2] = _s32_div_f(func_02078288(r4), 10) + 0xff10;
    arr[3] = (func_02078288(r4) % 10) + 0xff10;
    arr[4] = 0;
    func_020708e4(self + 0x26e8, arr, 5);
    func_ov113_02299db8((void *) self, 0, (void *) 0x111, (void *) 4, 0, 1);
    arr[0] = _s32_div_f(func_02078290(r4), 10) + 0xff10;
    arr[1] = (func_02078290(r4) % 10) + 0xff10;
    arr[2] = _s32_div_f(func_02078298(r4), 10) + 0xff10;
    arr[3] = (func_02078298(r4) % 10) + 0xff10;
    func_020708e4(self + 0x2754, arr, 5);
    func_ov113_02299db8((void *) self, 1, (void *) 0x116, (void *) 4, 0, 1);
}

void func_ov113_02299e98(int arg0, int arg1)
{
    short local[3];

    if (arg1 + 1 >= 10) {
        local[0] = (arg1 + 1) / 10 + 0xff10;
        local[1] = (arg1 + 1) % 10 + 0xff10;
        local[2] = 0;
    } else {
        local[0] = arg1 + 0xff11;
        local[1] = 0;
    }

    func_020708e4((void *) (arg0 + 0x27c0), (void *) local, 3);
    func_ov113_02299db8((void *) arg0, 2, (void *) 0x11a, (void *) 2, 1, 0);
}

void func_ov113_02299e20(UnkStruct_02299e20 *p, int cond1)
{
    int ret1;
    int ret2;

    int cond2;
    int arg6;
    int arg6_2;

    ret1 = (int) func_020781d0((unsigned char *) (((int *) data_021eed68)), cond1);
    ret2 = func_020984d4();

    cond1 = func_02078268(ret1, ret2);
    if (cond1 != 0) {
        arg6 = 8;
    } else {
        arg6 = 10;
    }
    func_0206fdd4((char *) p + 0xa0, 0x10, 0, 0x12, 3, arg6);

    cond2 = func_02078234(ret1);
    if (cond2 != 0) {
        arg6_2 = 10;
    } else {
        arg6_2 = 8;
    }
    func_0206fdd4((char *) p + 0xa0, 6, 5, 0x19, 6, arg6_2);

    func_ov113_02299d94((struct UnkStruct_02299d94 *) p, 1);
    func_02078248(ret1, ret2);
}

void func_ov113_02299df4(void *a, int index)
{
    func_ov113_02299f10((unsigned char *) a, index);
    func_ov113_02299e98((int) a, index);
    func_ov113_0229a004((unsigned char *) a, index);
    func_ov113_02299e20((UnkStruct_02299e20 *) a, index);
}

void func_ov113_02299df0(void *self) {}

void func_ov113_02299db8(void *p, int index, void *a2, void *a3, int arg5, int arg6)
{
    void *obj = (void *) ((char *) p + 0x26e8 + index * 0x6c);
    func_02070a98(obj, 2, (int) a2, (int) a3, 15, 10, arg6);
    func_02070a04(obj, arg5, 0);
}

int func_ov113_02299da4(unsigned char *ptr, unsigned short mask)
{
    if (*(unsigned short *) (ptr + 0x98) & mask) {
        return 1;
    }
    return 0;
}

void func_ov113_02299d94(struct UnkStruct_02299d94 *self, unsigned short val)
{
    self->unk_98 |= val;
}

void func_ov113_02299d84(void *r0, unsigned short r1)
{
    unsigned short r2;
    r2 = *(unsigned short *) ((char *) r0 + 0x98);
    r2 &= ~r1;
    *(unsigned short *) ((char *) r0 + 0x98) = r2;
}

int func_ov113_02299cd0(UnkStruct_02299cd0 *self)
{
    int a, b, t;
    unsigned int v;

    a = data_021f6c58;
    b = data_021f6c54;
    if (b >= 0x54 && b <= 0x70) {
        if (a <= 0x18) {
            self->unk_9B = 5;
            return 1;
        }
        if (a >= 0xe8) {
            self->unk_9B = 4;
            return 1;
        }
        goto fail;
    }
    if (b >= 0xa4 && b <= 0xb4) {
        if (a < 0x20) {
            return 0;
        }
        if (a < 0x50) {
            self->unk_9B = 0;
            return 1;
        }
        if (a < 0x80) {
            self->unk_9B = 1;
            return 1;
        }
        if (a < 0xb0) {
            self->unk_9B = 2;
            return 1;
        }
        if (a < 0xe0) {
            self->unk_9B = 3;
            return 1;
        }
        goto fail;
    }
    if (b >= 0x92 && b <= 0x9e) {
        t = self->unk_9E + 0x44;
        if (a < t) {
            goto fail;
        }
        v = (u8) ((a - t) >> 3);
        if (v >= self->unk_9D) {
            return 0;
        }
        self->unk_9B = (u8) (v + 6);
        return 1;
    }
fail:
    return 0;
}

void func_ov113_02299c44(UnkStruct_02299c44 *o, int flag)
{
    u8 st = o->unk_9B;
    int a;
    int n;

    switch (st) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (flag) {
                a = 0xe;
            } else {
                a = 0xd;
            }
            n = st * 6 + 4;
            func_0206fdd4((char *) o + 0xa0, n, 0x14, n + 5, 0x16, a);
            func_ov113_02299d94((struct UnkStruct_02299d94 *) o, 1);
            break;
        default:
            if (st == 4) {
                if (flag) {
                    func_ov113_02299d94((struct UnkStruct_02299d94 *) o, 2);
                } else {
                    func_ov113_02299d84((void *) o, 2);
                }
            } else {
                if (flag) {
                    func_ov113_02299d94((struct UnkStruct_02299d94 *) o, 4);
                } else {
                    func_ov113_02299d84((void *) o, 4);
                }
            }
            break;
    }
}

int func_ov113_02299aa4(UnkStruct_02299aa4 *o)
{
    unsigned int v;
    unsigned int n;
    unsigned int cur;
    void *p;

    func_ov113_02299a80((struct UnkStruct_02299a80 *) o);
    v = o->unk_9B;
    switch (v) {
        case 2:
            func_0200467c(0x29);
        case 3:
            func_ov113_02299c44((UnkStruct_02299c44 *) o, 1);
            o->unk_8C = 3;
            func_ov002_022080a0(o, 1);
            p = func_020ee45c(o);
            if (o->unk_9B == 3) {
                func_ov092_02299324(p, 0x43, 0);
                func_0200467c(0x12);
            } else {
                func_ov092_02299324(p, 1, 1);
            }
            return 1;
        case 4:
            if (o->unk_9D > o->unk_9A + 1) {
                o->unk_9A = o->unk_9A + 1;
                func_ov113_02299c44((UnkStruct_02299c44 *) o, 1);
                o->unk_8C = 5;
                func_ov002_022080a0(o, 1);
                return 1;
            }
            break;
        case 5:
            if (o->unk_9A != 0) {
                o->unk_9A = o->unk_9A - 1;
                func_ov113_02299c44((UnkStruct_02299c44 *) o, 1);
                o->unk_8C = 5;
                func_ov002_022080a0(o, 1);
                return 1;
            }
            break;
        case 1:
            if (o->unk_9A != o->unk_9D - 1) {
                o->unk_9A = o->unk_9D - 1;
                func_ov113_02299c44((UnkStruct_02299c44 *) o, 1);
                o->unk_8C = 5;
                func_ov002_022080a0(o, 1);
                return 1;
            }
            break;
        case 0:
            if (o->unk_9A != 0) {
                o->unk_9A = 0;
                func_ov113_02299c44((UnkStruct_02299c44 *) o, 1);
                o->unk_8C = 5;
                func_ov002_022080a0(o, 1);
                return 1;
            }
            break;
    }
    if (v >= 6 && v <= 0x14) {
        n = (unsigned char) (v - 6);
        cur = o->unk_9A;
        if (n == cur) {
            return 0;
        }
        if (cur < n) {
            func_ov113_02299d94((struct UnkStruct_02299d94 *) o, 0x40);
        } else {
            func_ov113_02299d84((void *) o, 0x40);
        }
        o->unk_9A = n;
        o->unk_8C = 5;
        func_ov002_022080a0(o, 1);
        return 1;
    }
    return 0;
}

void func_ov113_02299a80(struct UnkStruct_02299a80 *self)
{
    self->unk_9D = func_02077ec4();
    self->unk_9E = (0xf - self->unk_9D) << 2;
}

void func_ov113_02299a44(char *a0)
{
    int r1 = func_ov113_022999c4((int) a0);
    int r2 = (int) func_ov113_022999a4((unsigned char *) a0);
    func_ov002_0220a0b4(a0 + 0x2b20, r1, r2);
    func_ov002_0220a374(a0 + 0x2b20, 1);
    func_ov113_022998ac((void *) a0);
}

int func_ov113_02299a08(unsigned char *p)
{
    unsigned char b = p[0x9b];
    if (b <= 3) {
        return 0x30 * b + 0x47;
    }
    if (b == 5) {
        return 0x10;
    }
    if (b == 4) {
        return 0xf0;
    }
    if (b <= 0x14) {
        return p[0x9e] + 0x48 + (b - 6) * 8;
    } else {
        return 0x80;
    }
}

int func_ov113_022999c4(int param)
{
    int r4;
    int r5 = param;
    r4 = func_ov113_02299a08((unsigned char *) param);
    if (func_ov113_02299da4((unsigned char *) r5, 0x10) != 0) {
        r4 -= 0x100;
    } else if (func_ov113_02299da4((unsigned char *) r5, 0x20) != 0) {
        r4 += 0x100;
    }
    func_ov113_02299d84((void *) r5, 0x30);
    return r4;
}

unsigned char func_ov113_022999a4(unsigned char *p)
{
    unsigned char v;
    v = p[0x9b];
    if (v <= 3) {
        return 0xaa;
    }
    if (v <= 5) {
        return 0x56;
    }
    if (v <= 0x14) {
        return 0x98;
    }
    return 0x60;
}
