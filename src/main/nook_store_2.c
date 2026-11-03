/* nook_store_2: 18 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020af750 @ 0x020af750, 0x36 bytes, Thumb
 * func_020af674 @ 0x020af674, 0xdc bytes, Thumb
 * func_020af658 @ 0x020af658, 0x1c bytes, Thumb
 * func_020af648 @ 0x020af648, 0x10 bytes, Thumb
 * func_020af3a0 @ 0x020af3a0, 0x2a8 bytes, Thumb
 * func_020af31c @ 0x020af31c, 0x84 bytes, Thumb
 * func_020af2d0 @ 0x020af2d0, 0x4c bytes, Thumb
 * func_020af298 @ 0x020af298, 0x38 bytes, Thumb
 * func_020af28c @ 0x020af28c, 0xc bytes, Thumb
 * func_020af03c @ 0x020af03c, 0x250 bytes, Thumb
 * func_020af038 @ 0x020af038, 0x2 bytes, Thumb
 * func_020af028 @ 0x020af028, 0xe bytes, Thumb
 * func_020af004 @ 0x020af004, 0x24 bytes, Thumb
 * func_020aefec @ 0x020aefec, 0x18 bytes, Thumb
 * func_020aefd4 @ 0x020aefd4, 0x18 bytes, Thumb
 * func_020aefbc @ 0x020aefbc, 0x18 bytes, Thumb
 * func_020aefa4 @ 0x020aefa4, 0x18 bytes, Thumb
 * func_020aef8c @ 0x020aef8c, 0x18 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020af674 {
    u32 unk_00;
    u8 pad_04[0x58];
    u8 unk_5C[8];
};

typedef struct UnkStruct_020af3a0 {
    u16 unk_00;
    u16 unk_02;
    int a;
    int b;
} UnkStruct_020af3a0;

typedef struct UnkStruct_020af3a0_3 {
    char pad_00[4];
    u16 arr[0x25];
    char pad_4E[0x5a - 0x4e];
    u16 f5a : 5;
    u16 f5arest : 11;
} UnkStruct_020af3a0_3;

typedef struct UnkStruct_020af3a0_2 {
    int unk_00;
    int w1;
} UnkStruct_020af3a0_2;

struct UnkA {
    char pad_00[0x4e];
    unsigned char unk_4E;
    unsigned char unk_4F;
    unsigned char unk_50;
    unsigned char unk_51;
};

typedef struct {
    unsigned char pad_00[0x52];
    unsigned char unk_52;
    unsigned char unk_53;
    unsigned char unk_54;
    unsigned char unk_55;
} UnkStruct_020af03c;

typedef struct {
    unsigned short id;
    unsigned short unk_02;
    int unk_04;
    int unk_08;
} UnkStruct_020af03c_2;

typedef struct {
    unsigned char pad_00[0x5A];
    unsigned short : 9;
    unsigned short bf : 2;
    unsigned short : 5;
} BitFieldStruct;

extern unsigned int func_020af8e0(unsigned int *, unsigned int);
extern void func_020af788(unsigned int *);
extern int func_020af870(struct UnkStruct_020af674 *, u32);
extern u16 *func_020af854(struct UnkStruct_020af674 *, u32, int);
extern void func_0209f128(void *param1, int param2);
extern unsigned char data_021dc7a8[];
extern int func_0209f150(void *ptr, int value);
extern void func_020ae9c0(void *);
extern int func_020ad798(void);
extern void func_020ad78c(int);
extern int func_020b5e70(void);
extern int func_020b6744(unsigned int code);
extern int func_020b65c4(void);
extern void func_0209e474(int *);
extern void func_0209e140(int *, int);
extern int func_02073d90(int);
extern void func_020ade78(void);
extern int func_02098880(void *);
extern int func_020984e8(void);
extern int func_02099020(int, int);
extern int func_02098844(void *, int);
extern int func_02099a28(int);
extern u8 *func_020afad4(UnkStruct_020af3a0_3 *);
extern int func_02063cd4(void *, int);
extern void func_020afd58(u8);
extern int func_020afb48(UnkStruct_020af3a0_3 *, int *);
extern void func_02063ccc(void *, int, int);
extern void func_02063cc8(void *);
extern void __register_global_object(void *, void *, void *);
extern int func_0204bcdc(u16 *);
extern void func_020638d4(u16 *, void *, int, void *, int, int, int);
extern void func_020afd24(u16 *);
extern char data_021f3b44[];
extern int data_020ccf94;
extern char data_021dc7bc[];
extern char data_021f4a80[];
extern int data_021f4a08;
extern UnkStruct_020af3a0_2 data_021f4a0c;
extern char data_021f4a98[];
extern void func_020af880(void *object);
extern void func_02063ce0(void *object, unsigned char a, unsigned char b, unsigned char c);
extern void func_020aed60(void *object, unsigned int *counter);
extern void func_020aed38(void *object, int *counter);
extern void func_020aece8(void *object, unsigned int *counter);
extern void func_020aecb8(void *object, int *counter);
extern void func_020aec90(void *object, int *counter);
extern void func_020aec68(void *object, int *counter);
extern void func_020aec40(void *object, int *counter);
extern void func_020aebcc(void *object, int *counter);
extern void func_020aeb9c(void *object, int *counter);
extern void func_020aeb6c(void *object, int *counter);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern void func_0209f100(unsigned int *p, unsigned int bit);
extern void func_0209df64(void *out);
extern int func_0209dcdc(void *a, void *b);
extern int func_0209de88(int y, int m, int d);
extern void func_0209e29c(void *p, int n);
extern int func_0203fea0(void *arr, void *key);
extern int func_0209e3ac(void *a, void *b, int mode);
extern void func_020afd9c(int a, int b);
extern unsigned char data_020d1e20[];
extern unsigned char data_020d1e24[];
extern unsigned char data_020d1e28[];
extern unsigned char data_020d1e2c[];
extern unsigned char data_020d1e18[];

void func_020af658(int param1, int param2);
void func_020af31c(void *object, unsigned char a, unsigned char b, unsigned char c);
int func_020af2d0(struct UnkA *a, const unsigned char *b);
void func_020af298(unsigned char *a, const unsigned char *b);
void func_020af03c(UnkStruct_020af03c *self, void *src);
void func_020af038(void *object);
unsigned int func_020af028(unsigned short *s);

void func_020af750(unsigned int *ptr, unsigned int add, unsigned int other)
{
    unsigned int limit;

    limit = func_020af8e0(ptr, func_020af028((unsigned short *) ptr));
    *ptr += add;
    if (*ptr > limit) {
        *ptr = limit;
    }
    func_020af658((int) ptr, other);
    func_020af788(ptr);
}

int func_020af674(struct UnkStruct_020af674 *o, u32 idx, u32 delta, void *a3)
{
    u32 cap;
    unsigned int ok;
    unsigned int ok2;
    u16 v;
    u32 byteIdx;
    u32 bit;
    u16 *p;

    if (idx < 0x25) {
        cap = (u32) func_020af8e0((unsigned int *) o, (u32) func_020af028((unsigned short *) o));
        o->unk_00 = o->unk_00 + delta;
        if (o->unk_00 > cap) {
            o->unk_00 = cap;
        }
        if (func_020af870(o, idx) == 0) {
            byteIdx = idx >> 3;
            bit = idx & 7;
            p = func_020af854(o, idx, 0);
            ok = 0;
            v = *p;
            if (v >= 0x1000 && v <= 0x10ff) {
                ok = 1;
            }
            if (ok == 0) {
                p = func_020af854(o, idx, 0);
                ok2 = 0;
                v = *p;
                if (v >= 0x151f && v <= 0x151f) {
                    ok2 = 1;
                }
                if (ok2 == 0) {
                    o->unk_5C[byteIdx] |= 1 << bit;
                }
            }
        }
        func_020af658((int) o, (int) a3);
        func_020af788((unsigned int *) o);
        return 1;
    }
    cap = (u32) func_020af8e0((unsigned int *) o, (u32) func_020af028((unsigned short *) o));
    o->unk_00 = o->unk_00 + delta;
    if (o->unk_00 > cap) {
        o->unk_00 = cap;
    }
    func_020af658((int) o, (int) a3);
    func_020af788((unsigned int *) o);
    return 0;
}

void func_020af658(int param1, int param2)
{
    if (param2 == 0) {
        func_0209f128((void *) data_021dc7a8, 7);
    }
}

int func_020af648(void *object)
{
    return func_0209f150((void *) data_021dc7a8, 7);
}

void func_020af3a0(UnkStruct_020af3a0_3 *self, int arg1)
{
    UnkStruct_020af3a0 s;
    UnkStruct_020af3a0_2 o[3];
    int g;
    int p;
    int x;
    unsigned int v;
    unsigned int i;
    int j;
    int r6;
    int r7;
    int code;
    u16 *q;

    func_020ae9c0(data_021f3b44);
    if (func_020ad798() == 1) {
        func_020ad78c(2);
        return;
    }
    if (func_020b6744((unsigned int) func_020b5e70()) == 0) {
        v = func_020b65c4();
        if (v == 0x2c) {
            return;
        }
        if (v == 0x3f) {
            return;
        }
    }
    r6 = 1;
    s.a = 0;
    s.b = 0;
    func_0209e474(&s.a);
    if (((u8 *) &s)[6] < 6) {
        func_0209e140(&s.a, r6);
        r6 = 0;
    }
    if (arg1 == 0) {
        if (func_020af2d0((struct UnkA *) self, (const unsigned char *) (&s.a)) == 0) {
            return;
        }
    }
    self->f5a = 0;
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }
    func_020ade78();
    func_020af298((unsigned char *) self, (const unsigned char *) (&s.a));
    func_020af31c((void *) self, ((u8 *) &s)[9], ((u8 *) &s)[8], ((u8 *) &s)[7]);

    r7 = 1;
    x = func_02098880(data_021dc7bc);
    if (x != 0) {
        if (x == 1) {
            g = func_020984e8();
            if (g == 0 || func_02099020(g, r7) == 0) {
                r7 = 0;
            }
        } else {
            for (j = 0; j < 4; j++) {
                p = func_02098844(data_021dc7bc, j);
                if (p == 0) {
                    continue;
                }
                if (func_02099a28(p) == 0) {
                    continue;
                }
                if (func_02099020(p, 1) != 0) {
                    continue;
                }
                r7 = 0;
                break;
            }
        }
    }

    if (r7 == 0) {
        if (func_020afad4(self)[3] == 0) {
            func_020af03c((UnkStruct_020af03c *) self, (void *) (&s.a));
            if (func_02063cd4(data_021f4a80, 0xe) == 0) {
                v = func_02063cd4(data_021f4a80, 4);
                self->f5a = (u8) (v + 0x11);
                if (r6 != 0) {
                    func_020afd58((u8) self->f5a);
                }
            }
            if (self->f5a == 0) {
                if (func_020afb48(self, &s.a) == 0) {
                    if ((data_021f4a08 & 1) == 0) {
                        func_02063ccc(&data_021f4a0c, 0, 4);
                        __register_global_object((void *) (&data_021f4a0c), (((void *) func_02063cc8)),
                                                 (void *) (data_021f4a98));
                        data_021f4a08 |= 1;
                    }
                    if (func_02063cd4(data_021f4a80, 5) == 0) {
                        for (i = 0; i < 0x25; i++) {
                            u16 *e = &self->arr[i];
                            if (func_0204bcdc(e) != 0) {
                                o[1].unk_00 = data_021f4a0c.unk_00;
                                o[1].w1 = data_021f4a0c.w1;
                                func_020638d4(&s.unk_00, &o[1], 0, data_021f4a80, 0, 1, 0);
                                *e = s.unk_00;
                                func_02063cc8(&o[1]);
                                if (r6 != 0) {
                                    func_020afd24(e);
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    if (((u8 *) &s)[8] != 0xc) {
        return;
    }
    v = ((u8 *) &s)[7];
    code = 0x2e;
    if (v >= 0xa && v <= 0x18) {
        code = 0x2b;
    } else if (v >= 0x1a && v <= 0x1f) {
        code = 0x2c;
    }
    if (code == 0x2e) {
        return;
    }
    r7 = 0;
    for (i = 0; i < 0x25; i++) {
        if (func_0204bcdc(&self->arr[i]) != 0) {
            if (r7 == 1) {
                func_02063ccc(&o[0], 0, code);
                o[2].unk_00 = o[0].unk_00;
                o[2].w1 = o[0].w1;
                func_020638d4(&s.unk_02, &o[2], 0, data_021f4a80, 0, 1, 0);
                self->arr[i] = s.unk_02;
                func_02063cc8(&o[2]);
                func_02063cc8(&o[0]);
                break;
            }
            r7++;
        }
    }
}

void func_020af31c(void *object, unsigned char a, unsigned char b, unsigned char c)
{
    unsigned int counter;
    func_020af880(object);
    counter = 0;
    func_02063ce0(((unsigned char *) data_021f4a80), a, b, c);
    func_020aed60(object, &counter);
    func_020aed38(object, (int *) &counter);
    func_020aece8(object, &counter);
    func_020aecb8(object, (int *) &counter);
    func_020aec90(object, (int *) &counter);
    func_020aec68(object, (int *) &counter);
    func_020aec40(object, (int *) &counter);
    func_020aebcc(object, (int *) &counter);
    func_020aeb9c(object, (int *) &counter);
    func_020aeb6c(object, (int *) &counter);
    func_020af038(object);
}

int func_020af2d0(struct UnkA *a, const unsigned char *b)
{
    unsigned char buf[8];

    MI_CpuCopy8(b, buf, 8);
    if (a->unk_50 != buf[5] || a->unk_4F != buf[4] || a->unk_4E != buf[3] || a->unk_51 != 0) {
        return 1;
    }
    return 0;
}

void func_020af298(unsigned char *a, const unsigned char *b)
{
    unsigned char buf[8];
    MI_CpuCopy8(b, buf, 8);
    a[0x50] = buf[5];
    a[0x4f] = buf[4];
    a[0x4e] = buf[3];
    a[0x51] = 0;
}

int func_020af28c(int arg0)
{
    if (arg0 < 0x1c) {
        return 1;
    }
    return 0;
}

void func_020af03c(UnkStruct_020af03c *self, void *src)
{
    unsigned int a[2];
    unsigned char today[4];
    unsigned int c[2];
    unsigned int d[2];
    unsigned int e[2];
    unsigned int k[2];
    unsigned int k2[2];
    unsigned int f[2];
    unsigned int h[2];
    UnkStruct_020af03c_2 g1[7];
    UnkStruct_020af03c_2 g2[7];
    int v0;
    int d5;
    int e5;
    int cnt1;
    int cnt2;
    int d4;
    int d3;
    int e4;
    int e3;
    int x;
    int diff;
    int i;
    int n7;
    int n6;

    MI_CpuCopy8(src, a, 8);
    v0 = func_02063cd4(((unsigned char *) data_021f4a80), 2);
    if (func_0209f150((void *) (((unsigned int *) data_021dc7a8)), 5) != 0) {
        func_0209df64(today);
        x = func_0209dcdc(today, &self->unk_52);
        if (x >= 1) {
            func_0209f100(((unsigned int *) data_021dc7a8), 5);
        } else if (x <= -7) {
            func_0209f100(((unsigned int *) data_021dc7a8), 5);
        }
    }
    if (func_0209f150((void *) (((unsigned int *) data_021dc7a8)), 5) == 0) {
        MI_CpuCopy8(src, c, 8);
        x = func_0209de88(((unsigned char *) c)[5], ((unsigned char *) c)[4], ((unsigned char *) c)[3]);
        if (x == 6) {
            goto done;
        }
        if (x == 0) {
            goto done;
        }
        diff = 6 - x;
        if (diff < 0) {
            diff = -diff;
        }
        MI_CpuCopy8(c, d, 8);
        MI_CpuCopy8(c, e, 8);
        func_0209e29c(d, diff);
        func_0209e29c(e, diff + 1);
        d4 = ((unsigned char *) d)[4];
        d3 = ((unsigned char *) d)[3];
        d5 = ((unsigned char *) d)[5];
        e4 = ((unsigned char *) e)[4];
        e3 = ((unsigned char *) e)[3];
        e5 = ((unsigned char *) e)[5];
        MI_CpuCopy8(d, f, 8);
        cnt1 = func_0203fea0(g1, f);
        MI_CpuCopy8(e, h, 8);
        cnt2 = func_0203fea0(g2, h);
        i = n6 = n7 = 0;
        for (; i < cnt1; i++) {
            if (func_020af28c(g1[i].id) != 0) {
                n7++;
            }
        }
        for (i = 0; i < cnt2; i++) {
            if (func_020af28c(g2[i].id) != 0) {
                n6++;
            }
        }
        if (n7 != 0) {
            goto done;
        }
        if (n6 != 0) {
            goto done;
        }
        if (v0 == 0) {
            self->unk_54 = (unsigned char) d5;
            self->unk_53 = (unsigned char) d4;
            self->unk_52 = (unsigned char) d3;
            self->unk_55 = 0;
        } else {
            self->unk_54 = (unsigned char) e5;
            self->unk_53 = (unsigned char) e4;
            self->unk_52 = (unsigned char) e3;
            self->unk_55 = 0;
        }
        func_0209f100(((unsigned int *) data_021dc7a8), 6);
        func_0209f128((void *) (((unsigned int *) data_021dc7a8)), 5);
    }
done:
    if (func_0209f150((void *) (((unsigned int *) data_021dc7a8)), 5) != 0) {
        k[0] = 0;
        k[1] = 0;
        ((unsigned char *) k)[5] = self->unk_54;
        ((unsigned char *) k)[4] = self->unk_53;
        ((unsigned char *) k)[3] = self->unk_52;
        ((unsigned char *) k)[2] = 6;
        ((unsigned char *) k)[1] = 0;
        if (func_0209e3ac(k, a, 0x38) == -1) {
            func_0209f100(((unsigned int *) data_021dc7a8), 5);
        } else {
            MI_CpuCopy8(k, k2, 8);
            func_0209e140((int *) k2, 4);
            if (func_0209e3ac(k2, a, 0x38) == -1) {
                if (func_0209e3ac(a, k, 0x38) == -1) {
                    if (func_0209f150((void *) (((unsigned int *) data_021dc7a8)), 6) == 0) {
                        func_020afd9c(self->unk_53, self->unk_52);
                        func_0209f128((void *) (((unsigned int *) data_021dc7a8)), 6);
                    }
                }
            }
        }
    }
}

void func_020af038(void *object) {}

unsigned int func_020af028(unsigned short *s)
{
    return (((unsigned int) s[45] << 21) >> 30) & 3;
}

void func_020af004(BitFieldStruct *s, unsigned short val)
{
    unsigned short tmp = val & 3;
    s->bf = tmp;
}

int func_020aefec(unsigned short *argument0)
{
    int result;
    result = (int) func_020af028((unsigned short *) argument0);
    return data_020d1e20[result];
}

int func_020aefd4(unsigned short *argument0)
{
    int r0;
    r0 = (int) func_020af028((unsigned short *) argument0);
    return data_020d1e24[r0];
}

unsigned char func_020aefbc(unsigned short *argument0)
{
    unsigned char result;
    int index;

    index = (int) func_020af028((unsigned short *) argument0);
    result = data_020d1e28[index];
    return result;
}

int func_020aefa4(unsigned short *argument0)
{
    unsigned char result;
    int index;

    index = (int) func_020af028((unsigned short *) argument0);
    result = data_020d1e2c[index];
    return result;
}

unsigned char func_020aef8c(unsigned short *argument0)
{
    unsigned char result;
    int index;

    index = (int) func_020af028((unsigned short *) argument0);
    result = data_020d1e18[index];
    return result;
}
