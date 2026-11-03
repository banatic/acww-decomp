/* etc_museum_2: 16 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221bcdc @ 0x0221bcdc, 0x4 bytes, Thumb
 * func_ov004_0221bcbc @ 0x0221bcbc, 0x20 bytes, Thumb
 * func_ov004_0221bc98 @ 0x0221bc98, 0x24 bytes, Thumb
 * func_ov004_0221bc44 @ 0x0221bc44, 0x54 bytes, Thumb
 * func_ov004_0221bbf8 @ 0x0221bbf8, 0x4c bytes, Thumb
 * func_ov004_0221bad0 @ 0x0221bad0, 0x128 bytes, Thumb
 * func_ov004_0221ba88 @ 0x0221ba88, 0x48 bytes, Thumb
 * func_ov004_0221ba40 @ 0x0221ba40, 0x48 bytes, Thumb
 * func_ov004_0221b9f4 @ 0x0221b9f4, 0x4c bytes, Thumb
 * func_ov004_0221b9a0 @ 0x0221b9a0, 0x54 bytes, Thumb
 * func_ov004_0221b98c @ 0x0221b98c, 0x14 bytes, Thumb
 * func_ov004_0221b938 @ 0x0221b938, 0x54 bytes, Thumb
 * func_ov004_0221b908 @ 0x0221b908, 0x2e bytes, Thumb
 * func_ov004_0221b808 @ 0x0221b808, 0x100 bytes, Thumb
 * func_ov004_0221b6d8 @ 0x0221b6d8, 0x130 bytes, Thumb
 * func_ov004_0221b60c @ 0x0221b60c, 0xcc bytes, Thumb
 */

#include "types.h"

#define DIALOGUE (*(void **) (self + 0x12c))

typedef struct {
    int w[10];
} T28;

typedef struct {
    int w[8];
} T20;

typedef struct {
    char unk_00, unk_01, unk_02, unk_03;
    u16 unk_04;
} UnkStruct_0221b60c;

extern void func_020e9898(void *p);
extern u8 data_ov004_02257908;
extern int data_ov004_0225797c[];
extern unsigned char data_ov004_02257904;
extern void *func_020e98b4(int size);
extern u8 *data_ov004_02257918;
extern char data_021f38f8[];
extern int func_02071298(void *a, unsigned short *v);
extern int func_020ea990(void *a, void *b);
extern int func_020e8b4c(int a, int b);
extern int func_ov004_0221b570(void *self, int k);
extern void *func_02062f90(T28 *t, u16 *h);
extern void *func_02062f4c(T28 *t);
extern void func_020683b4(void *a, unsigned int i, T28 *t, int k);
extern void *func_02094fd4(T20 *o);
extern void *func_02094fbc(T20 *o);
extern int func_02070fe4(void *a, T20 *o, u16 *h);
extern void func_02068404(void *a, int b, T20 *o);
extern void func_0206844c(void *, u8 *, int);
extern void *func_0206837c(void *);
extern void func_020ab670(void *, int, int);
extern void func_020ab628(void *, int, u8 *, int, void *, int, int);
extern void func_020ab5f8(void *);
extern void func_02068388(void *, int);
extern u8 data_021f43e8;
extern char data_021f43f8;
extern int func_020ab504(void *);
extern int func_020712b0(void *a, u16 *b);

int func_ov004_0221bbf8(char *self);
int func_ov004_0221b98c(char *self);

int func_ov004_0221bcdc(void)
{
    return 1;
}

int func_ov004_0221bcbc(char *self)
{
    void *p;
    func_ov004_0221bbf8(self);
    p = *(void **) (self + 0x164);
    if (p != 0) {
        func_020e9898(p);
    }
    return 1;
}

void func_ov004_0221bc98(void)
{
    unsigned int i;
    int z = 0;
    if (data_ov004_02257908 != 0) {
        return;
    }
    for (i = 0; i < 0x20; i++) {
        data_ov004_0225797c[i] = z;
    }
}

int func_ov004_0221bc44(void *self)
{
    unsigned char *p;

    if (func_ov004_0221b98c((char *) self) != 0) {
        *((unsigned char *) self + 0x154) = 0xff;
        data_ov004_02257904 = 1;
        return 1;
    }
    p = (unsigned char *) ((char *) self + 0x154);
    *p = (*(unsigned char *) &data_ov004_02257908);
    if (*p < 0x20) {
        ((void * *) data_ov004_0225797c)[*p] = self;
        (*(unsigned char *) &data_ov004_02257908) = (unsigned char) ((*(unsigned char *) &data_ov004_02257908) + 1);
        return 1;
    }
    return 0;
}

int func_ov004_0221bbf8(char *self)
{
    u8 *p;
    u8 v;
    if (func_ov004_0221b98c((char *) self) == 0) {
        p = (u8 *) (self + 0x154);
        v = *p;
        if (v < 0x20) {
            data_ov004_0225797c[v] = 0;
            data_ov004_02257908 = (u8) (data_ov004_02257908 - 1);
            *p = 0xff;
            return 1;
        }
    } else {
        (*(u8 *) &data_ov004_02257904) = 0;
    }
    return 0;
}

int func_ov004_0221bad0(char *self)
{
    unsigned i;
    int n;
    u8 *table;

    if (func_ov004_0221b98c((char *) self) == 0) {
        n = *(int *) (self + 0x168);
        *(u16 **) (self + 0x164) = (u16 *) func_020e98b4(n << 1);
        if (*(void **) (self + 0x164) != 0) {
            switch (*(int *) (self + 0x15c)) {
                case 0:
                    for (i = 0; i < *(unsigned *) (self + 0x168); i++) {
                        table = data_ov004_02257918;
                        (*(u16 **) (self + 0x164))[i] = (table[i] < 0x38) ? (u16) (table[i] + 0x12b0) : 0x12b0;
                    }
                    return 1;
                case 1:
                    for (i = 0; i < *(unsigned *) (self + 0x168); i++) {
                        table = data_ov004_02257918;
                        (*(u16 **) (self + 0x164))[i] = (table[i] < 0x38) ? (u16) (table[i] + 0x12e8) : 0x12e8;
                    }
                    return 1;
                case 2:
                    for (i = 0; i < *(unsigned *) (self + 0x168); i++) {
                        table = data_ov004_02257918;
                        (*(u16 **) (self + 0x164))[i] = (table[i] < 0x14) ? table[i] * 4 + 0x3894 : 0x3894;
                    }
                    return 1;
                case 3:
                    for (i = 0; i < *(unsigned *) (self + 0x168); i++) {
                        table = data_ov004_02257918;
                        (*(u16 **) (self + 0x164))[i] = (table[i] < 0x34) ? table[i] * 4 + 0x450c : 0x450c;
                    }
                    return 1;
                default:
                    return 0;
            }
        }
        return 0;
    }
    return 1;
}

int func_ov004_0221ba88(void *self)
{
    unsigned short v;
    unsigned int i;

    for (i = 0; i < *(unsigned int *) ((char *) self + 0x168); i++) {
        v = (*(unsigned short **) ((char *) self + 0x164))[i];
        if (func_02071298(data_021f38f8, &v) != 0) {
            return 1;
        }
    }
    return 0;
}

int func_ov004_0221ba40(char *self)
{
    unsigned i;
    u16 t;

    for (i = 0; i < *(unsigned *) (self + 0x168); i++) {
        t = (*(u16 **) (self + 0x164))[i];
        if (!func_02071298(((int *) data_021f38f8), (unsigned short *) (&t))) {
            return 0;
        }
    }
    return 1;
}

int func_ov004_0221b9f4(char *self)
{
    int n = 0;
    unsigned i = *(u8 *) (self + 0x155);
    u16 t;

    for (; i < *(unsigned *) (self + 0x168); i++) {
        t = (*(u16 **) (self + 0x164))[i];
        if (func_02071298(((int *) data_021f38f8), (unsigned short *) (&t))) {
            n++;
        }
    }
    return n;
}

void func_ov004_0221b9a0(void *self)
{
    unsigned short v;
    unsigned int i;

    i = *((unsigned char *) self + 0x155) + 1;
    for (; i < *(unsigned int *) ((char *) self + 0x168); i++) {
        v = (*(unsigned short **) ((char *) self + 0x164))[i];
        if (func_02071298(data_021f38f8, &v) != 0) {
            *((unsigned char *) self + 0x155) = (unsigned char) i;
            return;
        }
    }
    *((unsigned char *) self + 0x155) = (unsigned char) *(unsigned int *) ((char *) self + 0x168);
}

int func_ov004_0221b98c(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x15c) == 0x4) {
        return 0x1;
    }
    return 0x0;
}

int func_ov004_0221b938(char *self, char *other)
{
    if (other != 0 && func_020ea990(other + 0x5c, self + 0x5c) < 0x2333 &&
        func_020e8b4c((s16) (*(s16 *) (self + 0x8e) + 0x8000), *(s16 *) (other + 0x8e)) < *(int *) (self + 0x158)) {
        return 1;
    }
    return 0;
}

void func_ov004_0221b908(void *self, int k)
{
    switch (k) {
        case 1:
            func_ov004_0221b570(self, 3);
            break;
        case 0:
            func_ov004_0221b570(self, 1);
            break;
        case 8:
            func_ov004_0221b570(self, 0);
            break;
    }
}

void func_ov004_0221b808(char *self)
{
    // DECLS
    u16 h[2];
    T28 t1;
    T20 o;
    T28 t2;
    unsigned int n;
    unsigned int i;
    // ENDDECLS

    if (func_ov004_0221b98c(self) != 0) {
        return;
    }
    if (*(unsigned int *) (self + 0x15c) <= 1) {
        n = 0;
        switch (*(u8 *) (self + 0x10a)) {
            case 5:
                n = 1;
                break;
            case 6:
                n = 2;
                break;
            case 7:
                n = 3;
                break;
        }
        for (i = 0; i < n; i++) {
            h[0] = (*(u16 **) (self + 0x164))[*(u8 *) (self + 0x155)];
            func_02062f90(&t1, &h[0]);
            func_020683b4(*(void **) (self + 0x12c), i, &t1, 7);
            func_ov004_0221b9a0((void *) self);
            func_02062f4c(&t1);
        }
    } else if (*(u8 *) (self + 0x155) < *(unsigned int *) (self + 0x168)) {
        h[1] = (*(u16 **) (self + 0x164))[*(u8 *) (self + 0x155)];
        func_02094fd4(&o);
        func_02070fe4(((int *) data_021f38f8), &o, &h[1]);
        func_02068404(*(void **) (self + 0x12c), 0, &o);
        func_02062f90(&t2, &h[1]);
        func_020683b4(*(void **) (self + 0x12c), 0, &t2, 7);
        if (*(unsigned int *) (self + 0x15c) != 3) {
            func_ov004_0221b9a0((void *) self);
        }
        func_02062f4c(&t2);
        func_02094fbc(&o);
    }
}

void func_ov004_0221b6d8(char *self)
{
    if (func_ov004_0221b98c((char *) self)) {
        return;
    }
    if (*(int *) (self + 0x15c) == 3) {
        if (*(u8 *) (self + 0x10a) != 5) {
            if (func_ov004_0221ba40((char *) self)) {
                if (*(short *) (self + 0x160) == *(u8 *) (self + 0x10a)) {
                    u8 message = *(u8 *) (self + 0x10a) + 1;
                    func_0206844c(DIALOGUE, &message, 0);
                } else {
                    u8 message = data_021f43e8;
                    func_0206844c(DIALOGUE, &message, 0);
                }
            } else {
                u8 message = data_021f43e8;
                func_0206844c(DIALOGUE, &message, 0);
            }
        } else {
            u8 message = data_021f43e8;
            func_0206844c(DIALOGUE, &message, 0);
        }
    } else if (func_ov004_0221b9f4((char *) self)) {
        void *dialogue = func_0206837c(DIALOGUE);
        if (dialogue) {
            u8 first, second;
            func_020ab670(dialogue, 2, 1);
            first = 0xe5;
            func_020ab628(dialogue, 0, &first, 0, &data_021f43f8, 0, 0);
            second = 0xe6;
            func_020ab628(dialogue, 1, &second, 0, &data_021f43f8, 0, 0);
            func_020ab5f8(dialogue);
            func_02068388(DIALOGUE, 1);
        }
    } else {
        u8 message = data_021f43e8;
        func_0206844c(DIALOGUE, &message, 0);
    }
}

void func_ov004_0221b60c(char *self)
{
    // DECLS
    UnkStruct_0221b60c s;
    unsigned int k;
    // ENDDECLS

    if (func_ov004_0221b98c(self) != 0) {
        return;
    }
    if (func_020ab504((void *) (unsigned int) func_0206837c((void *) (*(int *) (self + 0x12c)))) == 0) {
        s.unk_04 = (*(u16 **) (self + 0x164))[(u8) self[0x155]];
        if (*(unsigned int *) (self + 0x15c) <= 1) {
            k = (unsigned int) func_ov004_0221b9f4(self);
            if (k > 3) {
                k = 3;
            }
            s.unk_00 = (char) ((k - 1) % 3 + 5);
            func_0206844c(*(void **) (self + 0x12c), (u8 *) (&s.unk_00), 0);
        } else if (func_020712b0(((int *) data_021f38f8), &s.unk_04) != 2) {
            s.unk_01 = 1;
            func_0206844c(*(void **) (self + 0x12c), (u8 *) (&s.unk_01), 0);
        } else {
            s.unk_02 = 2;
            func_0206844c(*(void **) (self + 0x12c), (u8 *) (&s.unk_02), 0);
        }
    } else {
        s.unk_03 = data_021f43e8;
        func_0206844c(*(void **) (self + 0x12c), (u8 *) (&s.unk_03), 0);
    }
}
