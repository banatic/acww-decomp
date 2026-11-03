/* field_collision: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02032d48 @ 0x02032d48, 0x44 bytes, Thumb
 * func_02032d38 @ 0x02032d38, 0x10 bytes, Thumb
 * func_02032d34 @ 0x02032d34, 0x2 bytes, Thumb
 * func_02032d10 @ 0x02032d10, 0x24 bytes, Thumb
 * func_02032cac @ 0x02032cac, 0x62 bytes, Thumb
 * func_02032c8c @ 0x02032c8c, 0x20 bytes, Thumb
 * func_02032c7c @ 0x02032c7c, 0x10 bytes, Thumb
 * func_02032c64 @ 0x02032c64, 0x18 bytes, Thumb
 * func_02032c50 @ 0x02032c50, 0x12 bytes, Thumb
 * func_02032aec @ 0x02032aec, 0x164 bytes, Thumb
 * func_02032adc @ 0x02032adc, 0x10 bytes, Thumb
 * func_02032acc @ 0x02032acc, 0x10 bytes, Thumb
 * func_02032aa8 @ 0x02032aa8, 0x22 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char data[36];
} Elem;

typedef struct {
    unsigned int count;
    Elem arr[1];
} UnkStruct_02032d48;

typedef struct {
    short key[2];
    unsigned char count;
    unsigned char pad_05[3];
    int a[2];
    int b[2];
} PairSet;

typedef struct {
    u8 pad_00[4];
    u32 unk_04;
    u8 pad_08[4];
    short a[2];
    u8 unk_10;
    u8 pad_11[0x1c - 0x11];
    int c[8];
} UnkStruct_02032aec;

typedef struct {
    unsigned char pad_00[4];
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned char unk_0C[16];
    unsigned int unk_1C;
    unsigned int unk_20;
} UnkStruct_02032aa8;

extern int func_02032fc0(Elem *a, int arg, Elem *b);
extern void func_020342a4(void *arg);
extern void func_02034294(void *receiver);
extern int func_02033678(unsigned int p1, unsigned int p2, void *p3, unsigned int p4, unsigned int p5, unsigned int p6);

void func_02032d10(unsigned char *p);

void func_02032d48(UnkStruct_02032d48 *self, int arg)
{
    unsigned int n = self->count;
    Elem *p = &self->arr[0];
    unsigned int i = 0;
    unsigned int start = 0;
    while (i < n) {
        Elem *q = &self->arr[0];
        unsigned int j = start;
        while (j < n) {
            func_02032fc0(p, arg, q);
            q++;
            j++;
        }
        p++;
        i++;
    }
}

int func_02032d38(int arg)
{
    func_02032d10((unsigned char *) arg);
    return arg;
}

void func_02032d34(void *object) {}

void func_02032d10(unsigned char *p)
{
    int *a = (int *) (p + 8);
    int *b = (int *) (p + 0x10);
    short *h = (short *) p;
    int i;
    p[4] = 0;
    for (i = 0; i < 2; i++) {
        *h = 0;
        *a++ = 0;
        *b++ = 0;
        h++;
    }
}

int func_02032cac(PairSet *s, short key, int val, int other)
{
    short *k = s->key;
    int *v = s->b;
    int i;

    for (i = 0; i < s->count; i++) {
        if (*k == key && *v == val) {
            return 0;
        }
        k++;
        v++;
    }
    if (s->count < 2) {
        s->key[s->count] = key;
        s->b[s->count] = val;
        s->a[s->count] = other;
        s->count++;
        return 1;
    }
    return 0;
}

int func_02032c8c(void *p)
{
    int value;

    func_02032d10((unsigned char *) ((char *) p + 0xc));
    *(int *) ((char *) p + 8) = 0;
    value = *(int *) ((char *) p + 4);
    *(int *) p = value;
    *(int *) ((char *) p + 4) = 0;
    *(int *) ((char *) p + 0x24) = 0;
    *(int *) ((char *) p + 0x28) = 0;
    *(int *) ((char *) p + 0x2c) = 0;
    return value;
}

void func_02032c7c(int *p)
{
    p[1] = 0;
    p[0] = 0;
    p[2] = 0;
    p[9] = 0;
    p[10] = 0;
    p[11] = 0;
}

void *func_02032c64(void *arg)
{
    func_02032d38((int) ((char *) arg + 12));
    func_02032c7c((int *) arg);
    return arg;
}

void *func_02032c50(void *obj)
{
    func_02032d34((void *) ((char *) obj + 0xC));
    return obj;
}

void func_02032aec(UnkStruct_02032aec *self, int ang)
{
    // DECLS
    int i;
    u32 d;
    int base;
    int t;
    int t2;
    int t3;
    // ENDDECLS

    base = ang;
    base = base + 0x8000;
    for (i = 0; i < self->unk_10; i++) {
        d = (u16) (self->a[i] - base);
        if (d < 0x2000 || d >= 0xe000) {
            if (self->c[i] == 2) {
                self->unk_04 |= 0x80;
                self->unk_04 |= 0x100;
            } else {
                self->unk_04 |= 4;
                self->unk_04 |= 8;
            }
        } else if (d < 0x6000) {
            if (self->c[i] == 2) {
                self->unk_04 |= 0x80;
                self->unk_04 |= 0x400;
            } else {
                self->unk_04 |= 4;
                self->unk_04 |= 0x20;
            }
        } else if (d < 0xa000) {
            if (self->c[i] == 2) {
                self->unk_04 |= 0x80;
                self->unk_04 |= 0x800;
            } else {
                self->unk_04 |= 4;
                self->unk_04 |= 0x40;
            }
        } else {
            if (self->c[i] == 2) {
                self->unk_04 |= 0x80;
                self->unk_04 |= 0x200;
            } else {
                self->unk_04 |= 4;
                self->unk_04 |= 0x10;
            }
        }
    }
    if (self->unk_10 == 2) {
        t = (short) ((self->a[0] + self->a[1]) >> 1);
        t2 = (short) (t + 0x7fff);
        t3 = ang - t2;
        if (t3 < 0) {
            t3 = -t3;
        }
        if (t3 < 0x2000) {
            self->unk_04 |= 0x1000;
        }
        if ((short) (self->a[0] + self->a[1]) == 0) {
            self->unk_04 |= 0x2000;
        }
    }
}

void *func_02032adc(void *arg)
{
    func_020342a4(arg);
    return arg;
}

int func_02032acc(int arg)
{
    func_02034294((void *) arg);
    return arg;
}

int func_02032aa8(UnkStruct_02032aa8 *arg1, unsigned int arg2)
{
    return func_02033678(arg2, arg1->unk_08, arg1->unk_0C, arg1->unk_1C, arg1->unk_04, arg1->unk_20);
}
