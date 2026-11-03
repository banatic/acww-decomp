/* etc_museum: 11 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221b4e0 @ 0x0221b4e0, 0x4 bytes, Thumb
 * func_ov004_0221b4b0 @ 0x0221b4b0, 0x30 bytes, Thumb
 * func_ov004_0221b3ac @ 0x0221b3ac, 0x104 bytes, Thumb
 * func_ov004_0221b388 @ 0x0221b388, 0x24 bytes, Thumb
 * func_ov004_0221b384 @ 0x0221b384, 0x4 bytes, Thumb
 * func_ov004_0221b354 @ 0x0221b354, 0x30 bytes, Thumb
 * func_ov004_0221b2b8 @ 0x0221b2b8, 0x9c bytes, Thumb
 * func_ov004_0221b294 @ 0x0221b294, 0x24 bytes, Thumb
 * func_ov004_0221b27c @ 0x0221b27c, 0x18 bytes, Thumb
 * func_ov004_0221b224 @ 0x0221b224, 0x58 bytes, Thumb
 * func_ov004_0221b1cc @ 0x0221b1cc, 0x58 bytes, Thumb
 */

#include "types.h"

typedef struct {
    u16 a, b, c, d, e, unk_0A;
} UnkStruct_0221b3ac;

struct UnkInner {
    int unk_00;
    void *unk_04;
};

struct UnkOuter {
    char pad_00[0x12c];
    struct UnkInner *unk_12C;
};

struct UnkStruct_0221b354 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_0221b354_2 {
    char pad_00[0xec];
    char unk_EC[0x40];
    struct UnkStruct_0221b354 *unk_12C;
};

extern int func_0203e0a8(void *, int);
extern void func_020ee470(void *);
extern int func_ov004_0221b98c(void *);
extern void func_0203ee14(void *, void *);
extern void func_020a8164(void *, void *);
extern int func_02071298(void *, u16 *);
extern int func_020712b0(void *, u16 *);
extern int func_ov004_0221ba88(char *);
extern unsigned int func_ov004_0221b9f4(char *);
extern int data_021f38f8;
extern int data_ov004_022534cc;
extern int func_ov004_0221b570(void *obj, int mode);
extern void func_0203ee08(struct UnkStruct_0221b354_2 *obj, char *ptr);
extern int func_0203e020(struct UnkStruct_0221b354_2 *obj);
extern void *func_02094fd4(void *o);
extern int func_02070fe4(void *g, void *o, u16 *k);
extern void func_02068404(int h, int a, void *o);
extern void *func_02094fbc(void *o);
extern int data_ov004_0225797c[];
extern int data_ov004_02257914;
extern u16 data_ov004_0225337c;
extern int data_ov004_02257918;
extern int data_ov004_02257928;
extern int data_ov004_02257938;
extern int func_02003348(int a, int b, void *c, u16 *d, int e);
extern u8 data_ov004_02257904;
extern int data_021fbee8;

int func_ov004_0221b4e0(void *callbackObject)
{
    return 1;
}

void func_ov004_0221b4b0(char *self)
{
    // DECLS
    // ENDDECLS
    if (func_ov004_0221b98c(self) != 0x0) {
        if (*(u8 *) (self + 0x16c) == 0x0) {
            func_0203e0a8(self, 0x0);
        } else {
            func_020ee470(self);
        }
        return;
    }
}

int func_ov004_0221b3ac(char *self)
{
    // DECLS
    UnkStruct_0221b3ac s;
    void *p;
    unsigned int i;
    unsigned int t;
    unsigned int k;
    // ENDDECLS

    self[0x155] = 0;
    for (i = 0; i < *(unsigned int *) (self + 0x168); i++) {
        s.d = (*(u16 **) (self + 0x164))[i];
        if (func_02071298(&data_021f38f8, &s.d) != 0) {
            self[0x155] = (char) i;
            break;
        }
    }
    s.e = (*(u16 **) (self + 0x164))[(u8) self[0x155]];
    p = self;
    if (self != 0) {
        p = self + 0xec;
    }
    func_0203ee14(self, p);
    func_020a8164(self + 0xec, &data_ov004_022534cc);
    if (func_ov004_0221ba88(self) == 0) {
        self[0x10a] = 0;
    } else {
        t = *(unsigned int *) (self + 0x15c);
        if (t == 3) {
            if (*(unsigned int *) (self + 0x168) == 1) {
                self[0x10a] = 5;
            } else {
                self[0x10a] = (char) *(short *) (self + 0x160);
            }
        } else if (t <= 1) {
            k = func_ov004_0221b9f4(self);
            if (k > 3) {
                k = 3;
            }
            self[0x10a] = (char) ((k - 1) % 3 + 5);
        } else {
            if (func_020712b0(&data_021f38f8, &s.e) != 2) {
                self[0x10a] = 1;
            } else {
                self[0x10a] = 2;
            }
        }
    }
    *(int *) (*(char **) (self + 0x12c) + 8) = 1;
    return 1;
}

void func_ov004_0221b388(struct UnkOuter *obj)
{
    if (obj->unk_12C != 0 && obj->unk_12C->unk_04 != 0) {
        func_ov004_0221b570(obj, 2);
    }
}

int func_ov004_0221b384(void *callbackObject)
{
    return 1;
}

void func_ov004_0221b354(struct UnkStruct_0221b354_2 *obj)
{
    if (obj->unk_12C && obj->unk_12C->unk_04 == 0) {
        char *p = (char *) obj;
        if (p) {
            p += 0xec;
        }
        func_0203ee08(obj, p);
        func_0203e020(obj);
    }
}

int func_ov004_0221b2b8(char *s)
{
    u16 kk[2];
    char obj[0x20];
    char *q = s;
    void *g;
    if (s != 0) {
        q = q + 0xec;
    }
    func_0203ee14(s, q);
    func_020a8164(s + 0xec, &data_ov004_022534cc);
    kk[1] = 0x12e4;
    g = &data_021f38f8;
    if ((unsigned int) func_020712b0(g, &kk[1]) <= 1) {
        func_02094fd4(obj);
        if (func_02070fe4(g, obj, &kk[1]) != 0) {
            *(u8 *) (s + 0x10a) = 3;
            func_02068404(*(int *) (s + 0x12c), 0, obj);
        }
        func_02094fbc(obj);
    } else {
        *(u8 *) (s + 0x10a) = 4;
    }
    *(int *) (*(int *) (s + 0x12c) + 8) = 1;
    *(u8 *) (s + 0x16c) = (u8) (*(u8 *) (s + 0x16c) + 1);
    return 1;
}

void func_ov004_0221b294(struct UnkOuter *obj)
{
    if (obj->unk_12C != 0 && obj->unk_12C->unk_04 != 0) {
        func_ov004_0221b570(obj, 2);
    }
}

int func_ov004_0221b27c(int index)
{
    if (index >= 0 && (unsigned) index < 0x20) {
        return data_ov004_0225797c[index];
    }
    return 0;
}

void func_ov004_0221b224(int a0, void *a1, int a2, int a3, s16 a4, int a5, int a6)
{
    u16 v[3];

    data_ov004_02257914 = a0;
    data_ov004_0225337c = a4;
    data_ov004_02257918 = a5;
    data_ov004_02257928 = a6;
    data_ov004_02257938 = a3;
    v[0] = 0;
    v[1] = (u16) a2;
    v[2] = 0;
    func_02003348(0x19, 0, a1, v, 0);
}

int func_ov004_0221b1cc(void)
{
    if (data_ov004_02257904 == 0) {
        data_ov004_02257914 = 4;
        data_ov004_0225337c = 0;
        data_ov004_02257918 = 0;
        data_ov004_02257928 = 0;
        data_ov004_02257938 = 0;
        return func_02003348(0x19, 0, &data_021fbee8, 0, 0);
    }
    return 0;
}
