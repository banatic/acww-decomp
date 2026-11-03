/* insurer_talk: 12 functions, module ov071
 * mwccarm 1.2/base -O4,s
 * func_ov071_02279138 @ 0x02279138, 0x54 bytes, Thumb
 * func_ov071_02279128 @ 0x02279128, 0x10 bytes, Thumb
 * func_ov071_02279118 @ 0x02279118, 0x10 bytes, Thumb
 * func_ov071_022790f0 @ 0x022790f0, 0x28 bytes, Thumb
 * func_ov071_0227902c @ 0x0227902c, 0xc4 bytes, Thumb
 * func_ov071_02279024 @ 0x02279024, 0x8 bytes, Thumb
 * func_ov071_02279004 @ 0x02279004, 0x1e bytes, Thumb
 * func_ov071_02278fd0 @ 0x02278fd0, 0x34 bytes, Thumb
 * func_ov071_02278fb8 @ 0x02278fb8, 0x18 bytes, Thumb
 * func_ov071_02278fa0 @ 0x02278fa0, 0x18 bytes, Thumb
 * func_ov071_02278f80 @ 0x02278f80, 0x20 bytes, Thumb
 * func_ov071_02278f44 @ 0x02278f44, 0x3c bytes, Thumb
 */

#include "types.h"

struct Pair {
    int a;
    int b;
};

typedef struct UnkStruct_0227902c {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_0227902c;

typedef struct Msg {
    u8 b;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
} Msg;

typedef struct {
    unsigned int a;
    unsigned int b;
} Pair;

typedef struct {
    unsigned char pad_00[0xBC];
    Pair p1;
    Pair p2;
} UnkStruct_02278f44;

extern struct Pair data_ov071_0227a364[2];
extern struct Pair data_ov071_0227a170;
extern struct Pair data_ov071_0227a130;
extern int data_ov071_0227a344;
extern int func_0206fc6c(void);
extern int func_0206fc8c(void);
extern int func_0209a034(int a);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_020984e8(void);
extern int func_02099670(int a);
extern void func_02088a60(int a);
extern int func_02015330(UnkStruct_0227902c *self, u16 *p, int a, int b, int c);
extern void func_0209a050(int a);
extern int func_020155cc(UnkStruct_0227902c *self);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov071_0227a180;
extern int func_020644cc(int value);
extern void *func_0202eb70(void *self);
extern void *func_0202eb20(void *self);
extern unsigned char data_ov071_0227a1e8[];
extern void func_020edb3c(void *self);
extern Pair __ptmf_null;
extern void func_0201612c(void *);

void func_ov071_02279138(int arg0, struct Pair *out, int index)
{
    if ((data_ov071_0227a344 & 1) == 0) {
        data_ov071_0227a364[0] = data_ov071_0227a170;
        data_ov071_0227a364[1] = data_ov071_0227a130;
        data_ov071_0227a344 |= 1;
    }
    *out = data_ov071_0227a364[index];
}

void func_ov071_02279128(void *self, int other)
{
    func_ov071_02279138((int) self, (struct Pair *) ((char *) self + 0xbc), other);
}

void func_ov071_02279118(int a, int b)
{
    func_ov071_02279138(a, (struct Pair *) (a + 0xc4), b);
}

unsigned short func_ov071_022790f0(unsigned short *r0, int r1)
{
    unsigned short result;
    unsigned short value;

    if (r1 == 0) {
        result = 0;
        value = *r0;
        if (value >= 0x3934 && value <= 0x3983) {
            result = 1;
        }
        return result;
    }
    return 0;
}

void func_ov071_0227902c(UnkStruct_0227902c *self)
{
    Msg m;
    int h;
    int t;
    int r;
    int v;
    unsigned int ok;

    h = self->unk_40;
    m.b = 0x24;
    if (func_0206fc6c() != 0) {
        t = func_0206fc8c();
        m.unk_02 = (u16) func_0209a034(t);
        if (func_0204bcdc(&m.unk_02) != 0) {
            m.unk_04 = 0xfff1;
            r = func_0204bc64(&m.unk_02);
            ok = (r == func_0204bc64(&m.unk_04)) ? 1 : 0;
        } else {
            ok = (m.unk_02 == 0xfff1) ? 1 : 0;
        }
        if (ok == 0) {
            v = func_02099670(func_020984e8());
            m.b = 0x25;
            func_02088a60(v);
            func_02015330(self, &m.unk_02, 0, 4, 0);
            if (t >= 0) {
                func_0209a050(t);
            }
            func_ov071_02279118((int) self, 1);
        } else {
            func_020155cc(self);
        }
    } else {
        func_020155cc(self);
    }
    func_0206844c(h, &m.b, (int) &data_ov071_0227a180);
}

void func_ov071_02279024(int arg0)
{
    func_020155cc((UnkStruct_0227902c *) arg0);
}

int func_ov071_02279004(int arg0, const unsigned char *p, int n)
{
    int count = 0;
    int i = count;
    while (i < n) {
        if (*p == 0) {
            count++;
        }
        p++;
        i++;
    }
    return count;
}

int func_ov071_02278fd0(int a, unsigned char *p, int n)
{
    int r, result, m, i;

    r = func_ov071_02279004(a, (const unsigned char *) p, n);
    result = 0;
    m = func_020644cc(r);

    for (i = result; i < n; i++) {
        if (*p == 0) {
            if (m == 0) {
                result = i;
                break;
            }
            m--;
        }
        p++;
    }

    return result;
}

void *func_ov071_02278fb8(void *self)
{
    func_0202eb70(self);
    *(void **) self = ((unsigned char *) data_ov071_0227a1e8);
    return self;
}

void *func_ov071_02278fa0(void *self)
{
    ((void **) self)[0] = data_ov071_0227a1e8;
    func_0202eb20(self);
    return self;
}

void *func_ov071_02278f80(void *self)
{
    *(void **) self = (void *) data_ov071_0227a1e8;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}

void func_ov071_02278f44(UnkStruct_02278f44 *self)
{
    func_0201612c(self);
    {
        Pair v = __ptmf_null;
        self->p1 = v;
        self->p2 = v;
    }
}
