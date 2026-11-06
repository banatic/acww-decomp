/* paged_choice_2: 17 functions, module ov002
 * mwccarm 1.2/base -O4,s
 * func_ov002_0220909c @ 0x0220909c, 0x12 bytes, Thumb
 * func_ov002_02209044 @ 0x02209044, 0x58 bytes, Thumb
 * func_ov002_02209018 @ 0x02209018, 0x2c bytes, Thumb
 * func_ov002_02208ff8 @ 0x02208ff8, 0x20 bytes, Thumb
 * func_ov002_02208fcc @ 0x02208fcc, 0x2c bytes, Thumb
 * func_ov002_02208fac @ 0x02208fac, 0x20 bytes, Thumb
 * func_ov002_02208f58 @ 0x02208f58, 0x52 bytes, Thumb
 * func_ov002_02208e38 @ 0x02208e38, 0x120 bytes, Thumb
 * func_ov002_02208e28 @ 0x02208e28, 0xe bytes, Thumb
 * func_ov002_02208e18 @ 0x02208e18, 0xe bytes, Thumb
 * func_ov002_02208df8 @ 0x02208df8, 0x20 bytes, Thumb
 * func_ov002_02208dd0 @ 0x02208dd0, 0x28 bytes, Thumb
 * func_ov002_02208d74 @ 0x02208d74, 0x5a bytes, Thumb
 * func_ov002_02208d4c @ 0x02208d4c, 0x28 bytes, Thumb
 * func_ov002_02208d30 @ 0x02208d30, 0x1c bytes, Thumb
 * func_ov002_02208d18 @ 0x02208d18, 0x18 bytes, Thumb
 * func_ov002_02208ccc @ 0x02208ccc, 0x4c bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02209044 {
    u8 pad_00[0x1c];
    u8 unk_1C;
};

struct UnkStruct_02208d74 {
    u8 pad_00[0x1c];
    u8 unk_1C;
};

extern int func_ov002_022088cc(void *pad);
extern int func_ov002_022088bc(void *pad);
extern int func_02094fbc(void *);
extern void *func_02094fd4(void *);
extern void *func_02095074(int, void *);
extern void *func_020a8bb8(void *, void *);
extern int func_02098844(void *, int parameter1);
extern int func_02099870(int);
extern int func_02003618(int, void *);
extern int func_0207cec0(void *, int parameter1);
extern int func_0208150c(int);
extern void func_ov002_022089ec(void *self, void *a, int code);
extern void *func_020984e8(void);
extern int func_0209871c(void *tbl, void *x);
extern int func_020988a4(void *tbl, int t);
extern int func_0207cee4(void *tbl, int t);
extern int func_020807a8(void *e, void *x);
extern char data_021dc7bc[];
extern char data_021e5a2c[];
extern void func_02070b84(void *ptr);
extern void func_ov002_02209b94(void *, int);
extern int func_ov002_02208a14(struct UnkStruct_02208d74 *self, int bit);
extern void func_02070a04(char *p, int a, int b);

int func_ov002_0220909c(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x1e) != 0x0) {
        *(u8 *) (self + 0x1e) = (*(u8 *) (self + 0x1e) - 0x1);
        return 0x0;
    }
    return 0x1;
}

int func_ov002_02209044(struct UnkStruct_02209044 *self, void *pad, u8 *cur, u8 limit)
{
    if (pad != 0) {
        if (func_ov002_022088cc(pad)) {
            if (*cur > limit) {
                *cur = *cur - 1;
            } else {
                *cur = self->unk_1C - 1;
            }
            return 1;
        }
        if (func_ov002_022088bc(pad)) {
            if (*cur + 1 < self->unk_1C) {
                *cur = *cur + 1;
            } else {
                *cur = limit;
            }
            return 1;
        }
    }
    return 0;
}

int func_ov002_02209018(char *self, int a1)
{
    // DECLS
    char frame[0x24];
    // ENDDECLS
    func_02094fd4(frame);
    func_02095074(a1, frame);
    func_020a8bb8(self, frame);
    return func_02094fbc(frame);
}

int func_ov002_02208ff8(char *self, int arg1)
{
    // DECLS
    // ENDDECLS
    return func_ov002_02209018((char *) self, func_02099870(func_02098844(((void **) data_021dc7bc), arg1)));
}

int func_ov002_02208fcc(char *self, int a1)
{
    // DECLS
    char frame[0x24];
    // ENDDECLS
    func_02094fd4(frame);
    func_02003618(a1, frame);
    func_020a8bb8(self, frame);
    return func_02094fbc(frame);
}

int func_ov002_02208fac(char *self, int arg1)
{
    // DECLS
    // ENDDECLS
    return func_ov002_02208fcc((char *) self, func_0208150c(func_0207cec0(((void **) data_021e5a2c), arg1)));
}

void func_ov002_02208f58(void *self, void *a, unsigned int k)
{
    if (k >= 1 && k < 5) {
        func_ov002_02208ff8((char *) a, k - 1);
    } else if (k >= 5 && k < 0xd) {
        func_ov002_02208fac((char *) a, k - 5);
    } else {
        switch (k) {
            case 0xd:
                func_ov002_022089ec(self, a, 0x25);
                break;
            case 0xe:
                func_ov002_022089ec(self, a, 0x1e);
                break;
            case 0xf:
                func_ov002_022089ec(self, a, 0x27);
                break;
        }
    }
}

void func_ov002_02208e38(u8 *self)
{
    void *x;
    int n;
    int i;
    int j;
    int t;
    int k;

    self[0x1d] = 0;
    for (i = 0; i < 0x19; i++) {
        u8 *p = self + i;

        p[0x3cc] = 0;
    }
    x = (void *) func_02099870((int) (func_020984e8()));
    n = func_0209871c(data_021dc7bc, x);
    k = 0;
    for (j = 1, t = k; j < 5; j++, t++) {
        if (n != t && func_020988a4(data_021dc7bc, t)) {
            u8 *p = self + k;

            p[0x3cc] = j;
            k++;
        }
    }
    if (k % 5 == 4) {
        u8 *p = self + k;

        p[0x3cc] = 0xe;
        k++;
    }
    for (j = 5, t = 0; j < 0xd; j++, t++) {
        if (func_0207cee4(data_021e5a2c, t) && func_020807a8((void *) func_0207cec0(data_021e5a2c, t), x)) {
            u8 *p = self + k;

            p[0x3cc] = j;
            k++;
        }
        if (k % 5 == 4) {
            u8 *p = self + k;

            p[0x3cc] = 0xe;
            k++;
        }
    }
    if (k % 5 != 0) {
        u8 *p = self + k;

        p[0x3cc] = 0xe;
        k++;
    }
    while (k % 5 != 0) {
        u8 *p = self + k;

        p[0x3cc] = 0;
        k++;
    }
    {
        u8 *p = self + k;

        p[0x3cc] = 0xd;
    }
    {
        u8 *p = self + (k + 1);

        p[0x3cc] = 0xf;
    }
    k += 2;
    if (k > 2) {
        u8 *p = self + k;

        p[0x3cc] = 0xe;
        k++;
    }
    self[0x1d] = (k + 4) / 5;
}

int func_ov002_02208e28(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x16) == 0x3) {
        return 0x1;
    }
    return 0x0;
}

int func_ov002_02208e18(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(u8 *) (self + 0x16) == 0x0) {
        return 0x1;
    }
    return 0x0;
}

void func_ov002_02208df8(void *p)
{
    int i;
    char *base;
    int stride;

    i = 0;
    base = (char *) p;
    base += 0x28;
    stride = 116;

    do {
        func_02070b84(base + i * stride);
        i++;
    } while (i < 5);
}

void func_ov002_02208dd0(char *self)
{
    // DECLS
    int i;
    // ENDDECLS
    for (i = 0; i < 0x5; i++) {
        func_ov002_02209b94(self + 0x28 + (0x74 * i), -0x1);
    }
}

void func_ov002_02208d74(struct UnkStruct_02208d74 *self)
{
    int i;

    func_ov002_02208dd0((char *) self);
    for (i = 0; i < self->unk_1C; i++) {
        if (i == 0 && func_ov002_02208a14(self, 0x20)) {
            func_02070a04((char *) self + 0x28 + i * 0x74, 0, 0);
        } else {
            func_02070a04((char *) self + 0x28 + i * 0x74, 0, 1);
        }
    }
}

int func_ov002_02208d4c(u8 *p, u8 a, u8 b)
{
    int i;

    for (i = 0; i < 5; i++) {
        u8 *q = p + i;
        if (p[i] == 0xff) {
            *q = a;
            q[5] = b;
            return 1;
        }
    }
    return 0;
}

void func_ov002_02208d30(u8 *p, u8 v)
{
    int i;

    for (i = 0; i < 5; i++) {
        u8 *q = p + i;
        p[i] = 0xff;
        q[5] = v;
    }
    p[0xa] = 0;
}

int func_ov002_02208d18(u8 *p)
{
    int i;

    for (i = 0; i < 5; i++) {
        if (p[i] == 0xff) {
            return i;
        }
    }
    return i;
}

int func_ov002_02208ccc(char *base, unsigned char *slots, int param, unsigned char val)
{
    long i;

    for (i = 0; i < 5; i++) {
        if (slots[i] == 0xff) {
            func_020a8bb8(base + 0x28 + i * 116, (void *) param);
            slots[i + 5] = val;
            slots[10] |= 1 << i;
            slots[i] = 0xfe;
            return 1;
        }
    }
    return 0;
}
