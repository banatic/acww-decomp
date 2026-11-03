/* public_box_states_2: 15 functions, module ov110
 * mwccarm 1.2/base -O4,s
 * func_ov110_0229e368 @ 0x0229e368, 0x8 bytes, Thumb
 * func_ov110_0229e330 @ 0x0229e330, 0x38 bytes, Thumb
 * func_ov110_0229e2f8 @ 0x0229e2f8, 0x38 bytes, Thumb
 * func_ov110_0229e2c4 @ 0x0229e2c4, 0x32 bytes, Thumb
 * func_ov110_0229e2b0 @ 0x0229e2b0, 0x14 bytes, Thumb
 * func_ov110_0229e1dc @ 0x0229e1dc, 0xd4 bytes, Thumb
 * func_ov110_0229e1cc @ 0x0229e1cc, 0x10 bytes, Thumb
 * func_ov110_0229e14c @ 0x0229e14c, 0x80 bytes, Thumb
 * func_ov110_0229e0f8 @ 0x0229e0f8, 0x54 bytes, Thumb
 * func_ov110_0229e05c @ 0x0229e05c, 0x9c bytes, Thumb
 * func_ov110_0229df2c @ 0x0229df2c, 0x130 bytes, Thumb
 * func_ov110_0229ddb4 @ 0x0229ddb4, 0x178 bytes, Thumb
 * func_ov110_0229dcc0 @ 0x0229dcc0, 0xf4 bytes, Thumb
 * func_ov110_0229dc40 @ 0x0229dc40, 0x80 bytes, Thumb
 * func_ov110_0229dbf4 @ 0x0229dbf4, 0x4c bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_0229df2c UnkStruct_0229df2c;

typedef struct {
    char pad_00[0xF5];
    unsigned char unk_F5;
    char pad_F6[0x21F8 - 0xF5 - 1];
    void *unk_21F8;
} UnkStruct_0229ddb4;

typedef struct UnkStruct_0229dcc0 {
    unsigned char pad_00[0xf4];
    unsigned char unk_F4;
    unsigned char unk_F5;
    unsigned char pad_F6[0x21f8 - 0xf6];
    unsigned char sub[0x100];
} UnkStruct_0229dcc0;

struct Flags {
    unsigned short unk_00;
    unsigned short unk_02;
};

extern void func_ov110_0229d5f0(void *);
extern void func_ov110_0229c574(void *);
extern void func_ov094_0229a084(void *);
extern void func_ov094_0229af20(void *);
extern void func_ov094_0229bbc0(void *);
extern void func_ov110_0229cea8(void *);
extern void func_ov094_0229a05c(void *);
extern void func_ov002_022091cc(void *);
extern int func_ov002_02207d5c(void *);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov094_0229a29c(int a, int b);

// func_02002c6c and func_02002d14 take six arguments; the 4th and 5th are the same constant.

extern void *data_021fbe94;
extern u8 data_ov110_0229ed18[];
extern u8 data_ov110_0229ed3c[];
extern u8 data_ov110_0229ed5c[];
extern u8 data_ov110_0229ed74[];
extern u8 data_ov110_0229ed8c[];
extern u8 data_ov110_0229eda4[];
extern u8 data_ov110_0229edbc[];
extern u8 data_ov110_0229edd4[];
extern u8 data_ov110_0229edec[];
extern u8 data_ov110_0229ee04[];
extern int func_02002ca4(u8 *, void *, int);
extern int func_02002c6c(u8 *, void *, int, int, int, int);
extern int func_02002d14(u8 *, void *, int, int, int, int);
extern int func_0206fca4(void);
extern void func_ov110_0229c4f8(void *, int);
extern int func_ov094_0229a098(void *receiver);
extern int func_ov002_02208054(void *self, int a);
extern void func_ov110_0229d860(void *self);
extern u8 data_021fbddc;
extern u8 data_021f6c58;
extern u8 data_021f6c54;
extern int func_ov110_0229d504(void *self, int a, int b, int c);
extern void func_ov110_0229d7b8(void *self, int n);
extern void func_ov110_0229c3b8(void *self, int a);
extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_02207ce4(void *p, int size);
extern void func_ov002_02207d00(void *p);
extern int func_ov110_0229c2c8(void *p, int a);
extern int func_ov110_0229cf54(void *self);
extern void func_ov110_0229d770(void *p, unsigned char b);
extern int func_ov110_0229e7ac(void *receiver);
extern void func_ov110_0229c8f4(void *p);
extern int func_ov002_02208b00(void *p, int b1, int b2);
extern void func_ov002_02209114(void *p, int a, int b);
extern int func_ov110_0229cce8(UnkStruct_0229df2c *, int);
extern void func_ov110_0229cbe0(UnkStruct_0229df2c *);
extern int func_ov002_02207d24(void *, int);
extern void func_ov110_0229cde0(UnkStruct_0229df2c *);
extern void func_ov110_0229cfd4(UnkStruct_0229df2c *);
extern int func_ov110_0229d5d4(UnkStruct_0229df2c *, int);
extern int func_ov110_0229d5e4(UnkStruct_0229df2c *, int);
extern int func_ov110_0229d0b8(UnkStruct_0229df2c *, int);
extern int func_ov110_0229d13c(UnkStruct_0229df2c *, int);
extern int func_ov110_0229d680(UnkStruct_0229df2c *, int, void *);
extern int func_ov110_0229d4a8(UnkStruct_0229df2c *, int);
extern void func_ov094_022999d8(void);
extern void func_ov110_0229d840(UnkStruct_0229df2c *);
extern void func_ov110_0229cf98(UnkStruct_0229df2c *, int);
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(UnkStruct_0229ddb4 *s);
extern int func_ov110_0229c5a0(UnkStruct_0229ddb4 *s, int a, int b);
extern void func_ov110_0229d894(UnkStruct_0229ddb4 *s);
extern void func_ov110_0229ce44(UnkStruct_0229ddb4 *s);
extern void func_ov110_0229cb78(UnkStruct_0229ddb4 *s);
extern int func_ov110_0229d0fc(UnkStruct_0229ddb4 *s, unsigned char b);
extern void func_ov110_0229c9c8(UnkStruct_0229ddb4 *s);
extern int func_ov110_0229d5c8(UnkStruct_0229ddb4 *s, unsigned char b);
extern void func_ov110_0229ca08(UnkStruct_0229ddb4 *s);
extern int func_ov110_0229d600(UnkStruct_0229ddb4 *s);
extern unsigned char func_ov110_0229d628(void *receiver);
extern void func_ov110_0229d648(UnkStruct_0229ddb4 *s, unsigned char b, int v);
extern void func_ov110_0229c98c(UnkStruct_0229dcc0 *self, unsigned char b);
extern void func_ov110_0229c944(UnkStruct_0229dcc0 *self, unsigned char b);
extern void func_ov110_0229cdb4(UnkStruct_0229dcc0 *self);
extern unsigned short data_021fbe40[2];
extern int func_ov002_02209044(char *a, int b, char *c, int d);
extern void func_ov110_0229cb28(char *p);
extern void func_ov002_0220a1dc(char *p);
extern void func_ov110_0229cac8(char *p);
extern int func_0208e484(void *);

void func_ov110_0229e2f8(void *self);

void func_ov110_0229e368(void *argument0)
{
    func_ov110_0229e2f8(argument0);
}

void func_ov110_0229e330(void *self)
{
    func_ov110_0229d5f0(self);
    func_ov094_0229a084((char *) self + 0xbc0);
    func_ov094_0229af20((char *) self + 0x138);
    func_ov094_0229bbc0((char *) self + 0xb98);
    func_ov110_0229c574(self);
}

void func_ov110_0229e2f8(void *self)
{
    func_ov002_022091cc((char *) self + 0x2344);
    func_ov094_0229a05c((char *) self + 0xbc0);
    if (func_ov002_02207d5c((char *) self + 0x21f8)) {
        func_ov110_0229cea8(self);
    }
}

void func_ov110_0229e2c4(void)
{
    func_020029e8(6, 2);
    func_020028bc(6, 0, 0, 0);
    func_020029e8(4, 1);
    func_020028bc(4, 0, 0, 0);
}

void func_ov110_0229e2b0(int a)
{
    func_ov094_0229a29c(a + 0xbc0, 0);
}

void func_ov110_0229e1dc(void *o)
{
    void *p;
    u8 *a;
    u8 *b;
    int t;

    p = data_021fbe94;
    func_02002ca4(data_ov110_0229ed18, p, 4);
    func_02002c6c(data_ov110_0229ed3c, p, 4, 0x1b9, 0x1b9, 0x238);
    t = func_0206fca4();
    a = 0;
    b = a;
    switch (t) {
        case 0x1d:
            a = data_ov110_0229ed5c;
            b = data_ov110_0229ed74;
            break;
        case 0x1e:
            a = data_ov110_0229ed8c;
            b = data_ov110_0229eda4;
            break;
        case 0x1f:
            a = data_ov110_0229edbc;
            b = data_ov110_0229edd4;
            break;
        case 0x20:
            a = data_ov110_0229edec;
            b = data_ov110_0229ee04;
            break;
    }
    if (a != 0) {
        func_02002d14(a, p, 4, 3, 3, 5);
    }
    if (b != 0) {
        func_02002c6c(b, p, 4, 0x208, 0x208, 0x238);
    }
    func_ov110_0229c4f8(o, 0);
}

unsigned int func_ov110_0229e1cc(unsigned int r0)
{
    return func_ov094_0229a098((void *) (r0 + 0xbc0));
}

void func_ov110_0229e14c(char *self)
{
    unsigned int ok;
    int a;
    int b;
    int n;

    if (func_ov002_02208054(self, 1) != 0) {
        func_ov110_0229d860(self);
        return;
    }

    ok = ((*(u8 *) &data_021fbdd8) != 0 && data_021fbddc != 0) ? 1 : 0;
    if (ok == 0) {
        return;
    }

    a = data_021f6c58;
    b = data_021f6c54;
    n = func_ov110_0229d504(self, a, b, 1);
    if (n != 0x1f) {
        func_ov110_0229d7b8(self, n);
        return;
    }
    if (a < 0xc8) {
        return;
    }
    if (a > 0xf8) {
        return;
    }
    if (b < 0x60) {
        return;
    }
    if (b > 0x70) {
        return;
    }
    func_ov110_0229c3b8(self, 1);
}

void func_ov110_0229e0f8(void *p)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (p), 0);
        func_ov002_02207ce4((char *) p + 0x21f8, 0x3c);
    } else {
        if (func_ov110_0229c2c8(p, 4) != 0 && func_ov110_0229cf54(p) != 0) {
            func_ov110_0229d770(p, *(unsigned char *) ((char *) p + 0xf2));
        } else {
            func_ov002_02207d00((char *) p + 0x21f8);
        }
    }
}

void func_ov110_0229e05c(unsigned char *self)
{
    int ret;
    unsigned int flag;

    if (func_ov110_0229e7ac(self)) {
        func_ov110_0229c8f4(self);
        return;
    }
    if (func_ov002_02208054(self, 1)) {
        func_ov110_0229c8f4(self);
        return;
    }
    flag = (data_021fbdd8 && (*(unsigned char *) &data_021fbddc)) ? 1 : 0;
    if (flag > 0) {
        ret = func_ov002_02208b00(self + 0x2344, (*(unsigned char *) &data_021f6c58), (*(unsigned char *) &data_021f6c54));
        if (ret >= 0) {
            func_ov002_02209114(self + 0x2344, ret, 1);
            *(self + 0xf9) = *(self + ret + 0x2731);
            func_ov002_02208098((void *) (self), 0x12);
        }
    }
}

void func_ov110_0229df2c(UnkStruct_0229df2c *p)
{
    int r4;
    void *r6;
    void *ptr;

    if (func_ov110_0229e7ac(p) != 0) {
        func_ov110_0229cce8(p, *(unsigned char *) ((char *) p + 0xf4));
        func_ov110_0229cbe0(p);
        func_ov002_02207d24((char *) p + 0x21f8, 0);
        func_ov110_0229c3b8((void *) p, 0);
        return;
    }

    func_ov110_0229cde0(p);
    func_ov110_0229cfd4(p);
    r6 = (char *) (*(char **) ((char *) p + 0xac)) + 8;
    ptr = (char *) (*(char **) ((char *) p + 0xa8)) + 8;
    r4 = func_ov110_0229d504((void *) p, (int) ptr, (int) r6, 0);

    if (func_ov110_0229c2c8((void *) p, 0x200) == 0) {
        goto common;
    }

    if ((func_ov110_0229d5d4(p, r4) != 0) && (func_ov110_0229d5e4(p, *(unsigned char *) ((char *) p + 0xf4)) != 0)) {
        goto dfca;
    }
    if ((func_ov110_0229d5e4(p, r4) != 0) && (func_ov110_0229d5d4(p, *(unsigned char *) ((char *) p + 0xf4)) != 0)) {
        goto dfca;
    }
    goto common;

dfca:
    if (func_ov110_0229d0b8(p, r4) == 0xfff1) {
        goto common;
    }
    r4 = 0x1f;

common:
    if (r4 == 0x1f) {
        goto e030;
    }
    if (data_021fbdd8 != 0) {
        goto e026;
    }
    if (func_ov110_0229d13c(p, r4) != 0) {
        func_ov110_0229d680(p, *(unsigned char *) ((char *) p + 0xf4), r6);
        return;
    }
    if (func_ov110_0229d4a8(p, r4) != 0) {
        goto e01a;
    }
    func_ov110_0229d680(p, *(unsigned char *) ((char *) p + 0xf4), r6);
    return;

e01a:
    func_ov094_022999d8();
    func_ov110_0229d840(p);
    return;

e026:
    func_ov110_0229cf98(p, r4);
    return;

e030:
    if (data_021fbdd8 != 0) {
        return;
    }
    func_ov110_0229d680(p, *(unsigned char *) ((char *) p + 0xf4), r6);
    return;
}

void func_ov110_0229ddb4(UnkStruct_0229ddb4 *s)
{
    unsigned short val;
    int r;
    if (func_ov002_02208014(s) != 0) {
        func_ov110_0229d894(s);
        func_ov002_02207d24((char *) s + 0x21F8, 1);
        return;
    }
    if (func_ov110_0229c5a0(s, func_ov002_02208008(s), 0) != 0) {
        func_ov110_0229ce44(s);
        func_ov110_0229cb78(s);
        func_ov002_02207d24((char *) s + 0x21F8, 0);
        return;
    }
    if (func_ov110_0229d13c((UnkStruct_0229df2c *) s, (unsigned char) s->unk_F5) == 0) {
        val = (*(struct { char pad2[2]; unsigned short field; } *) data_021fbe40).field;
        if (val & 1) {
            if (func_ov110_0229d5e4((UnkStruct_0229df2c *) s, (unsigned char) s->unk_F5) != 0 || func_ov110_0229d5d4((UnkStruct_0229df2c *) s, (unsigned char) s->unk_F5) != 0) {
                if (func_ov110_0229d0fc(s, s->unk_F5) == 0) {
                    func_ov110_0229c9c8(s);
                }
            } else if (func_ov110_0229d5c8(s, s->unk_F5) != 0) {
                func_ov110_0229ca08(s);
            }
            return;
        }
        if (val & 0x800) {
            if (func_ov110_0229d5e4((UnkStruct_0229df2c *) s, (unsigned char) s->unk_F5) != 0 || func_ov110_0229d5d4((UnkStruct_0229df2c *) s, (unsigned char) s->unk_F5) != 0) {
                if (func_ov110_0229d0fc(s, s->unk_F5) == 0) {
                    if (func_ov110_0229d5e4((UnkStruct_0229df2c *) s, (unsigned char) s->unk_F5) != 0) {
                        r = func_ov110_0229d600(s);
                    } else {
                        r = func_ov110_0229d628((void *) s);
                    }
                    if (r != 0x1f) {
                        func_ov110_0229d648(s, s->unk_F5, r);
                        func_ov002_02207d24((char *) s + 0x21F8, 1);
                    }
                }
            }
            return;
        }
    }
    val = (*(struct { char pad2[2]; unsigned short field; } *) data_021fbe40).field;
    if ((val & 8) || (val & 2)) {
        func_ov110_0229cbe0((UnkStruct_0229df2c *) s);
        func_ov002_02207d24((char *) s + 0x21F8, 0);
        func_ov110_0229c3b8((void *) s, 1);
        return;
    }
    func_ov002_02207d00((char *) s + 0x21F8);
}

void func_ov110_0229dcc0(UnkStruct_0229dcc0 *self)
{
    unsigned short flags;
    void *res;

    if (func_ov110_0229e7ac(self) != 0) {
        func_ov110_0229cce8((UnkStruct_0229df2c *) self, (unsigned char) self->unk_F4);
        func_ov110_0229cbe0((UnkStruct_0229df2c *) self);
        func_ov002_02207d24(self->sub, 0);
        func_ov110_0229c3b8((void *) self, 0);
        return;
    }

    res = (void *) func_ov002_02208008((UnkStruct_0229ddb4 *) self);
    if (func_ov110_0229c5a0((UnkStruct_0229ddb4 *) self, (int) res, 1) != 0) {
        func_ov110_0229ce44((UnkStruct_0229ddb4 *) self);
        func_ov110_0229cb78((UnkStruct_0229ddb4 *) self);
        func_ov002_02207d24(self->sub, 0);
        return;
    }

    flags = data_021fbe40[1];
    if (flags & 1) {
        if (func_ov110_0229d5e4((UnkStruct_0229df2c *) self, (unsigned char) self->unk_F5) == 0) {
            if (func_ov110_0229d5d4((UnkStruct_0229df2c *) self, (unsigned char) self->unk_F5) == 0) {
                return;
            }
        }
        if (func_ov110_0229d13c((UnkStruct_0229df2c *) self, (unsigned char) self->unk_F5) != 0) {
            return;
        }
        if (func_ov110_0229d0fc((UnkStruct_0229ddb4 *) self, self->unk_F5) != 0) {
            func_ov110_0229c98c(self, self->unk_F5);
        } else {
            func_ov110_0229c944(self, self->unk_F5);
        }
        return;
    }

    if (flags & 2) {
        func_ov110_0229c98c(self, self->unk_F4);
        return;
    }

    func_ov110_0229cdb4(self);
    func_ov002_02207d00(self->sub);
}

void func_ov110_0229dc40(char *p)
{
    int v;
    unsigned short flags;
    if ((func_ov002_02208014(p) != 0) || (func_ov110_0229e7ac(p) != 0)) {
        func_ov110_0229c8f4((void *) p);
        return;
    }
    {
        v = func_ov002_02208008((UnkStruct_0229ddb4 *) p);
        if (func_ov002_02209044(p + 0x2344, v, p + 0xfa, 0) != 0) {
            func_ov110_0229cb28(p);
            return;
        }
        flags = (*(struct Flags *) data_021fbe40).unk_02;
        if ((flags & 1) != 0) {
            func_ov002_0220a1dc(p + 0x22e0);
            func_ov002_02208098((void *) (p), 7);
            return;
        } else if ((flags & 2) != 0) {
            func_ov110_0229cac8(p);
            return;
        }
    }
}

void func_ov110_0229dbf4(unsigned char *p)
{
    if (func_0208e484(p + 0x22e0) != 0) {
        func_ov002_02209114(p + 0x2344, p[0xfa], 1);
        {
            unsigned char *q = p + p[0xfa];
            p[0xf9] = q[0x2731];
        }
        func_ov002_02208098((void *) (p), 0x12);
    }
}
