/* effect_kinds_6: 33 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02093318 @ 0x02093318, 0x14 bytes, Thumb
 * func_020932b4 @ 0x020932b4, 0x64 bytes, Thumb
 * func_02093298 @ 0x02093298, 0x1c bytes, Thumb
 * func_02093288 @ 0x02093288, 0x10 bytes, Thumb
 * func_0209326c @ 0x0209326c, 0x1c bytes, Thumb
 * func_0209325c @ 0x0209325c, 0x10 bytes, Thumb
 * func_0209324c @ 0x0209324c, 0x10 bytes, Thumb
 * func_02093208 @ 0x02093208, 0x44 bytes, Thumb
 * func_020931f8 @ 0x020931f8, 0x10 bytes, Thumb
 * func_020931e8 @ 0x020931e8, 0x10 bytes, Thumb
 * func_020931a4 @ 0x020931a4, 0x44 bytes, Thumb
 * func_02093194 @ 0x02093194, 0x10 bytes, Thumb
 * func_0209313c @ 0x0209313c, 0x58 bytes, Thumb
 * func_0209312c @ 0x0209312c, 0x10 bytes, Thumb
 * func_0209311c @ 0x0209311c, 0x10 bytes, Thumb
 * func_0209310c @ 0x0209310c, 0x10 bytes, Thumb
 * func_020930a0 @ 0x020930a0, 0x6c bytes, Thumb
 * func_0209308c @ 0x0209308c, 0x14 bytes, Thumb
 * func_02093078 @ 0x02093078, 0x14 bytes, Thumb
 * func_02093050 @ 0x02093050, 0x28 bytes, Thumb
 * func_02093040 @ 0x02093040, 0x10 bytes, Thumb
 * func_02093020 @ 0x02093020, 0x20 bytes, Thumb
 * func_02092ff8 @ 0x02092ff8, 0x28 bytes, Thumb
 * func_02092f48 @ 0x02092f48, 0xb0 bytes, Thumb
 * func_02092f20 @ 0x02092f20, 0x28 bytes, Thumb
 * func_02092f10 @ 0x02092f10, 0x10 bytes, Thumb
 * func_02092f00 @ 0x02092f00, 0x10 bytes, Thumb
 * func_02092ec8 @ 0x02092ec8, 0x38 bytes, Thumb
 * func_02092ea4 @ 0x02092ea4, 0x24 bytes, Thumb
 * func_02092e74 @ 0x02092e74, 0x30 bytes, Thumb
 * func_02092e5c @ 0x02092e5c, 0x18 bytes, Thumb
 * func_02092e44 @ 0x02092e44, 0x18 bytes, Thumb
 * func_02092e14 @ 0x02092e14, 0x30 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x34];
    int mode;
    char tail[0xc];
} UnkStruct_020932b4;

struct Bits {
    u16 b0 : 5;
    u16 b1 : 5;
    u16 b2 : 5;
    u16 b3 : 1;
};

struct Stack {
    u16 unk_00;
    union {
        u16 raw;
        struct Bits bits;
    } unk_02;
    union {
        u16 raw;
        struct Bits bits;
    } unk_04;
    u16 unk_06;
};

struct UnkStruct_02092f48 {
    u8 pad_00[0x5a];
    u16 unk_5A;
};

struct InnerStruct {
    char pad_00[0x4c];
    int unk_4C;
    int unk_50;
    char pad_54[0x68 - 0x54];
    char unk_68;
};

struct OuterStruct {
    char pad_00[0xc];
    struct InnerStruct *inner;
};

typedef struct {
    char pad_00[0xc];
    void *ptr;
} UnkStruct_02092e14;

extern unsigned char data_020d17e0[];
extern void func_0209332c(int a, void *b, int c);
extern int func_02034270(UnkStruct_020932b4 *obj, int a, int b, int c);
extern void func_0203423c(UnkStruct_020932b4 *obj);
extern int func_020b6598(void);
extern int func_02094cf8(int a0, int a1, int a2, int a3, int a4, int a5);
extern unsigned int data_020e278c;
extern unsigned char data_020d17ec[];
extern int data_020e27b4;
extern int data_020d17f8;
extern int data_020d1804;
extern unsigned char data_020e2780[];
extern unsigned char data_020e27ac[];
extern char data_020d16b4;
extern char data_020d16c0[];
extern int data_020e2790;
extern int data_020e27b8;
extern void func_02094d48(int a, int b, char *c);
extern char data_020d16fc[];
extern void func_02091494(int *, int, int, int, int, int, int);
extern int func_02090c2c(int, int, int, int *);
extern int data_021d5658;
extern int data_020e27c8;
extern int data_020e29fc;
extern int data_020d1714;
extern int data_020d1720[];
extern int data_020d1738;
extern void *data_020e2904[3];
extern int func_02094b58(int, int, int, int, int, int);
extern unsigned char data_020e28a4[];
extern void func_02094c38(int a, int b, void *c);
extern unsigned char data_020d1750[];
extern int func_02094bcc(int arg0, int arg1, int *arg2);
extern unsigned char data_020e27fc[];
extern void func_02094ef4(struct UnkStruct_02092f48 *);
extern u16 func_020bbf00(int);
extern unsigned char data_020e27a4[];
extern char data_020d1768;
extern int func_020ba4e4(void);
extern int data_020e28d4[];

void func_02093318(int a)
{
    func_0209332c(a, data_020d17e0, -30000);
}

int func_020932b4(int p0, int p1, int p2, int p3, int p4, int p5)
{
    UnkStruct_020932b4 obj;
    int mode;
    int result;

    func_02034270(&obj, p1, 0, 0);
    mode = obj.mode;
    result = -1;
    if (mode == 0x13 || (func_020b6598() && mode == 3)) {
        result = p4;
    }
    if (result != -1) {
        result = func_02094cf8(p4, p0, p1, p2, p3, p5);
        func_0203423c(&obj);
        return result;
    } else {
        func_0203423c(&obj);
        return 3;
    }
}

void func_02093298(int p1, int p2, int p3, int p4)
{
    func_020932b4(p1, p2, p3, p4, 0x58, (unsigned int) &data_020e278c);
}

void func_02093288(int arg)
{
    func_0209332c(arg, (void *) data_020d17ec, 0);
}

int func_0209326c(int a, int b, int c, int d)
{
    return func_020932b4(a, b, c, d, 0x58, (int) (&data_020e27b4));
}

void func_0209325c(int a)
{
    func_0209332c(a, (void *) (&data_020d17f8), 0);
}

void func_0209324c(int arg)
{
    func_0209332c(arg, (void *) (&data_020d1804), 0);
}

int func_02093208(int a, int b, int c, int d)
{
    if (func_020932b4(a, b, c, d, 0x57, (unsigned int) data_020e27ac) == 1) {
        return func_020932b4(a, b, c, d, 0x57, (unsigned int) data_020e2780);
    } else {
        return 3;
    }
}

void func_020931f8(int a)
{
    func_0209332c(a, &data_020d16b4, 0);
}

void func_020931e8(int a)
{
    func_0209332c(a, data_020d16c0, 0);
}

int func_020931a4(int a, int b, int c, int d)
{
    if (func_020932b4(a, b, c, d, 0x57, (int) (&data_020e2790)) == 1) {
        return func_020932b4(a, b, c, d, 0x57, (int) (&data_020e27b8));
    }
    return 3;
}

void func_02093194(int a)
{
    func_02094d48(a, 0, data_020d16fc);
}

int func_0209313c(int arg0, int arg1, int arg2, int arg3)
{
    int result = 3;
    func_02091494(&data_021d5658, -1, arg0, arg1, arg2, arg3, -1);
    if (func_02090c2c(0x76, arg1, arg2, &data_020e27c8) != 0 && func_02090c2c(0x54, arg1, arg2, &data_020e29fc) != 0) {
        result = 1;
    }
    return result;
}

void func_0209312c(int a)
{
    func_02094d48(a, (int) (&data_020d1714), 0);
}

void func_0209311c(void *a)
{
    func_02094d48((int) a, (int) data_020d1720, 0);
}

void func_0209310c(int a0)
{
    func_02094d48(a0, (int) (&data_020d1738), 0);
}

int func_020930a0(int a0, int a1, int a2, int a3, int a4)
{
    int i;
    void **p;
    func_02091494((int *) (&data_021d5658), -1, a0, a1, a2, a3, -1);
    if (func_02090c2c(a4, a1, a2, (int *) (((void **) &data_020e27c8))) == 0) {
        goto ret3;
    }
    i = 0;
    p = data_020e2904;
    for (; i < 3; i++) {
        if (func_02090c2c(0x54, a1, a2, (int *) (&p[i])) == 0) {
            return 3;
        }
    }
    return 1;
ret3:
    return 3;
}

void func_0209308c(int a, int b, int c, int d)
{
    func_020930a0(a, b, c, d, 0x77);
}

void func_02093078(int a, int b, int c, int d)
{
    func_020930a0(a, b, c, d, 120);
}

void func_02093050(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e28a4;
    func_02094b58(0x79, r0, r1, r2, sp[0], sp[1]);
}

void func_02093040(int a)
{
    func_02094c38(a, 0, data_020d1750);
}

void func_02093020(int param0)
{
    int local[3];
    local[0] = 0;
    local[1] = 0;
    local[2] = 0x1000;
    func_02094bcc(param0, 0, local);
}

void func_02092ff8(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e27fc;
    func_02094b58(0x7a, r0, r1, r2, sp[0], sp[1]);
}

void func_02092f48(struct UnkStruct_02092f48 *self)
{
    struct Stack s;

    func_02094ef4(self);

    s.unk_00 = func_020bbf00(3);
    s.unk_06 = s.unk_00;
    s.unk_02.raw = s.unk_06;
    s.unk_04.raw = 0x7fff;

    s.unk_02.bits.b0 = (s.unk_04.bits.b0 * s.unk_02.bits.b0) / 31;
    s.unk_02.bits.b1 = (s.unk_04.bits.b1 * s.unk_02.bits.b1) / 31;
    s.unk_02.bits.b2 = (s.unk_04.bits.b2 * s.unk_02.bits.b2) / 31;

    self->unk_5A = s.unk_02.raw;
}

void func_02092f20(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e27a4;
    func_02094cf8(0x63, r0, r1, r2, sp[0], sp[1]);
}

void func_02092f10(int arg0)
{
    func_02094c38(arg0, 0, &data_020d1768);
}

int func_02092f00(int a)
{
    return func_02094bcc(a, 0, (int *) (((int *) &data_020d1768)));
}

int func_02092ec8(int a, int b, int c, int d)
{
    if (func_020ba4e4() == 1) {
        return func_02094b58(0x74, a, b, c, d, (int) data_020e28d4);
    }
    return 3;
}

void func_02092ea4(int a1, int a2, int a3, int a4)
{
    func_02094b58(0x52, a1, a2, a3, a4, 0);
}

void func_02092e74(struct OuterStruct *s, char c, int a, int b)
{
    func_02094c38((int) s, 0, (void *) (((const unsigned char *) data_020d1750)));
    s->inner->unk_68 = c;
    s->inner->unk_4C = a;
    s->inner->unk_50 = b;
}

void func_02092e5c(int arg)
{

    func_02092e74((struct OuterStruct *) ((void *) arg), 5, 0xCD, 0x200);
}

void func_02092e44(int arg0)
{

    func_02092e74((struct OuterStruct *) ((void *) arg0), 5, 0xe1, 0x266);
}

void func_02092e14(UnkStruct_02092e14 *a)
{
    func_02094c38((int) a, 0, ((char *) data_020d1750));
    *((char *) a->ptr + 0x69) = 0;
    *((int *) ((char *) a->ptr + 0x4c)) = 0x3d;
    *((int *) ((char *) a->ptr + 0x50)) = 0x466;
}
