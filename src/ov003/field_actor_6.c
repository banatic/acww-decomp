/* field_actor_6: 6 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0220d4f8 @ 0x0220d4f8, 0xe0 bytes, Thumb
 * func_ov003_0220d4dc @ 0x0220d4dc, 0x1a bytes, Thumb
 * func_ov003_0220d498 @ 0x0220d498, 0x44 bytes, Thumb
 * func_ov003_0220d490 @ 0x0220d490, 0x6 bytes, Thumb
 * func_ov003_0220d484 @ 0x0220d484, 0xa bytes, Thumb
 * func_ov003_0220d444 @ 0x0220d444, 0x40 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned int unk_60;
    unsigned int unk_64;
    unsigned char pad_68[0x8e - 0x68];
    short unk_8E;
    unsigned char pad_90[0x704 - 0x90];
    unsigned int unk_704;
    unsigned char pad_708[0x7f0 - 0x708];
    unsigned int unk_7F0;
    unsigned char pad_7F4[0x8];
    unsigned int unk_7FC;
    unsigned int unk_800;
} TestStruct;

struct UnkStruct_0220d498 {
    unsigned char pad_00[12];
    unsigned char b0;
    unsigned char b1;
    unsigned char pad_0E[14];
};

typedef struct {
    unsigned char x;
    unsigned char y;
} Pair;

typedef struct {
    char pad_00[0xc];
    unsigned char x;
    unsigned char y;
} UnkStruct_0220d444;

extern int func_02056f94(void *);
extern void func_020109fc(void *, int, int, int);
extern int func_ov003_0222c364(unsigned int);
extern int func_02095518(int, int, int);
extern unsigned int func_02008258(void *, unsigned int);
extern int func_0200c9a8(void *, int, int, int);
extern unsigned int *func_ov003_0222c1f4(unsigned int);
extern int func_020e8ed8(int, int);
extern int func_020ea990(unsigned int *, unsigned int *);
extern int func_020113e0(short *, int);
extern void func_020110a0(void *object, short *values);
extern void func_ov003_0220d5d8(void *p);
extern void func_02010d64(void *p);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

void func_ov003_0220d4f8(TestStruct *p)
{
    short s;
    unsigned int local1[3];
    unsigned int local2[3];
    unsigned int *q;
    unsigned int *base;
    int xdiff, zdiff, ydiff, c, d, e;

    if (func_02056f94((unsigned char *) p + 0x2d0)) {
        func_020109fc(p, 0, 3, 3);
        return;
    }
    if (p->unk_704 != 0) {
        return;
    }
    if (func_ov003_0222c364(p->unk_800) == 0) {
        func_02095518(0, 0, 4);
        p->unk_7FC = func_02008258(p, p->unk_7F0);
        func_0200c9a8(p, 3, 5, -1);
        return;
    } else {
        q = func_ov003_0222c1f4(p->unk_800);
        local1[0] = q[0];
        local1[1] = q[1];
        local1[2] = q[2];
        base = (unsigned int *) ((unsigned char *) p + 0x5c);
        local2[0] = base[0];
        local2[1] = base[1];
        local2[2] = base[2];
        xdiff = local1[0] - local2[0];
        zdiff = local1[2] - local2[2];
        c = func_020e8ed8(xdiff, zdiff);
        d = func_020ea990(local1, local2);
        ydiff = local1[1] - local2[1];
        e = func_020e8ed8(ydiff, d);
        if (e > 0) {
            e = 0;
        }
        func_02095518(e, 0, 4);
        s = p->unk_8E;
        func_020113e0(&s, c);
        func_020110a0((void *) (p), (short *) (&s));
        return;
    }
}

void func_ov003_0220d4dc(void *p)
{
    func_ov003_0220d5d8(p);
    func_02010d64(p);
    func_ov003_0220d4f8((TestStruct *) p);
}

int func_ov003_0220d498(void *a0, unsigned char *a1, int a2, int a3, short a4)
{
    struct UnkStruct_0220d498 local;
    unsigned char *p;
    int res;

    p = &local.b0;
    func_0200e92c(&local);
    func_0200e90c(&local, 0x8f, a3, a4);
    *p = *a1;
    *(p + 1) = (unsigned char) a2;
    res = func_0200e894(a0, &local);
    func_0200e91c(&local);
    return res;
}

void func_ov003_0220d490(u8 *p, int a, int b)
{
    p[0] = (u8) a;
    p[1] = (u8) b;
}

void func_ov003_0220d484(u8 *p, u8 *a, u8 *b)
{
    *a = p[0];
    *b = p[1];
}

void func_ov003_0220d444(void *p, UnkStruct_0220d444 *b, int previous)
{
    Pair *s = (Pair *) ((char *) b + 0xc);
    Pair *d = (Pair *) ((char *) p + 0x7d4);
    unsigned char a = s->x;
    unsigned char c = s->y;
    if (c == 0) {
        func_020109fc(p, 0, 3, 3);
    }
    d->x = a;
    d->y = c;
    func_ov003_0220d490((u8 *) ((char *) p + 0x8f0), a, c);
}
