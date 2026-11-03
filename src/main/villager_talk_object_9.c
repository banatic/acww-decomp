/* villager_talk_object_9: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020262fc @ 0x020262fc, 0xb4 bytes, Thumb
 * func_02026268 @ 0x02026268, 0x94 bytes, Thumb
 * func_02026250 @ 0x02026250, 0x16 bytes, Thumb
 * func_020261f8 @ 0x020261f8, 0x58 bytes, Thumb
 * func_020261b0 @ 0x020261b0, 0x48 bytes, Thumb
 * func_02026058 @ 0x02026058, 0x158 bytes, Thumb
 */

#include "types.h"

typedef void (*func_type)(unsigned short *, int, int);

struct UnkStruct_02026058 {
    char pad_00[0x124];
    u16 unk_124;
    char pad_126[0x3e];
    int unk_164;
};

struct Loc {
    u8 unk_00;
    u8 unk_01;
    u16 h1;
    u16 h2;
};

struct Pair {
    int a;
    int b;
};

extern void func_02063414(volatile unsigned short *, int, int, int, int, int, int, int, int, int);
extern void *func_020984e8(void);
extern int func_020644cc(int);
extern int func_020535f0(u16 *w);
extern unsigned int func_0209b8bc(int);
extern unsigned int func_0207ff00(int);
extern unsigned int func_0209b7ac(unsigned int, unsigned int);
extern void func_0209b8a4(int, unsigned int);
extern void func_02078624(int, unsigned int);
extern void func_0209b750(unsigned short *, unsigned int, int);
extern int func_0207f1c8(int);
extern int func_0209b5e8(int);
extern func_type data_020c8f24[5];
extern int data_020d9f94;
extern struct Pair data_020d9388;
extern void func_0202db48(struct UnkStruct_02026058 *a, struct Pair p);
extern int func_0209b91c(int a);
extern int func_0209bd44(int a);
extern int func_0209b914(int a);
extern void func_0209e474(void *p);
extern void *func_0202d9c4(struct UnkStruct_02026058 *a);
extern int func_0209bc40(void *a);
extern void func_02015de4(struct UnkStruct_02026058 *a, void *b, int c, int d);
extern void func_020263b0(u16 *out, struct UnkStruct_02026058 *a, int v);
extern int func_0209b850(int);
extern int func_02015dd4(struct UnkStruct_02026058 *a, int b, void *c, void *d, void *e);

void func_020262fc(unsigned short *out, int value, int object)
{
    volatile unsigned short h[2];
    unsigned short v0, v1;
    unsigned int hit;

    func_02063414(&h[0], 0x450c, 0x34, 0, 0, 0, 1, 0xa, 0, 1);
    func_02063414(&h[1], 0x450c, 0x34, 0, 0, (int) func_020984e8(), 0, 0xa, 0, 1);
    *out = 0xfff1;
    hit = 0;
    v0 = h[0];
    v1 = h[0];
    if (v1 >= 0x450c && v0 <= 0x45db) {
        hit = 1;
    }
    if (hit > 0) {
        hit = 0;
        v0 = h[1];
        v1 = h[1];
        if (v1 >= 0x450c && v0 <= 0x45db) {
            hit = 1;
        }
        if (hit > 0 && (func_020644cc(0xa) & 1) != 0) {
            *out = h[1];
        } else {
            *out = h[0];
        }
    } else {
        *out = h[1];
    }
}

int func_02026268(u16 *p, int comp)
{
    unsigned int ok = 0;
    int r5;
    unsigned int i;
    int j;
    int r;
    u16 w;

    if (p[0] >= 0x450c && p[0] <= 0x45db) {
        ok = 1;
    }
    if (ok > 0) {
        w = 0xfff1;
        r5 = (p[0] >= 0x450c && p[0] <= 0x45db) ? (int) (p[0] - 0x450c) >> 2 : -1;
        for (i = 0; i < 0x34; i++) {
            w = (i < 0x34) ? 0x450c + i * 4 : 0x450c;
            r = func_020535f0(&w);
            if (comp == r) {
                for (j = 0; j < 3; j++) {
                    if (r5 == j + i) {
                        return j;
                    }
                }
                break;
            }
        }
    }
    return -1;
}

int func_02026250(int x)
{
    return func_02026268((u16 *) x, func_020535f0((u16 *) x));
}

void func_020261f8(unsigned short *p1, int p2, int p3)
{
    unsigned int r4;

    r4 = func_0209b8bc(p2);
    if (r4 == 0x18) {
        r4 = (unsigned char) func_0209b7ac(func_0207ff00(p3), 0xA);
        func_0209b8a4(p2, r4);
        func_02078624(p3, r4);
    }
    if (r4 < 0x18) {
        func_0209b750(p1, r4, 0);
    } else {
        *p1 = 0xFFF1;
    }
}

void func_020261b0(unsigned short *out, void *src, unsigned int c)
{
    if (c < 5) {
        func_type fp = data_020c8f24[c];
        if (fp != 0) {
            void *p = *(void **) ((char *) src + 0x100);
            int x = *(int *) ((char *) p + 0x830);
            int z = func_0209b5e8(func_0207f1c8(x));
            fp(out, z, x);
            return;
        }
    }
    *out = 0xfff1;
}

void func_02026058(struct UnkStruct_02026058 *self)
{
    struct Loc loc;
    int buf[2];
    int v;
    int n;
    int f;
    int x;

    v = 0;
    buf[0] = v;
    buf[1] = v;
    if (func_0209bd44(func_0209b91c(self->unk_164)) != 0) {
        v = func_0209b914(self->unk_164);
    }
    func_0209e474(buf);
    switch (func_0209bc40(func_0202d9c4(self))) {
        case 0:
            if (self->unk_124 != 0xfff1) {
                func_02015de4(self, &self->unk_124, 0, 7);
            }
            break;
        case 1:
            if (self->unk_124 != 0xfff1) {
                func_02015de4(self, &self->unk_124, 0, 7);
            }
            break;
        case 2:
            if (self->unk_124 == 0xfff1) {
                func_020261b0((unsigned short *) (&loc.h1), (void *) self, v);
                self->unk_124 = loc.h1;
            }
            if (v < 2) {
                break;
            }
            n = (int) func_0209b8bc(self->unk_164);
            if (n >= 0x18) {
                f = 0;
                if (self->unk_124 >= 0x450c && self->unk_124 <= 0x45db) {
                    f = 1;
                }
                if (f != 0) {
                    n = func_020535f0(&self->unk_124);
                }
            }
            if (n < 0x18) {
                x = func_0209b850(n);
                if (x != -1) {
                    loc.unk_00 = x;
                    loc.unk_01 = 0;
                    func_02015dd4(self, 0, &loc, &data_020d9f94, &loc.unk_01);
                }
            }
            break;
        case 3:
            if (self->unk_124 == 0xfff1) {
                func_020263b0(&loc.h2, self, v);
                self->unk_124 = loc.h2;
            }
            if (self->unk_124 != 0xfff1) {
                func_02015de4(self, &self->unk_124, 0, 7);
            }
            break;
        case 4:
            break;
    }
    func_0202db48(self, data_020d9388);
}
