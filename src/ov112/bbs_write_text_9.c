/* bbs_write_text_9: 14 functions, module ov112
 * mwccarm 1.2/base -O4,s
 * func_ov112_0229fe70 @ 0x0229fe70, 0x12 bytes, Thumb
 * func_ov112_0229fe60 @ 0x0229fe60, 0xe bytes, Thumb
 * func_ov112_0229fe50 @ 0x0229fe50, 0xe bytes, Thumb
 * func_ov112_0229fd20 @ 0x0229fd20, 0x130 bytes, Thumb
 * func_ov112_0229fcd4 @ 0x0229fcd4, 0x4a bytes, Thumb
 * func_ov112_0229fc48 @ 0x0229fc48, 0x8c bytes, Thumb
 * func_ov112_0229fc18 @ 0x0229fc18, 0x30 bytes, Thumb
 * func_ov112_0229fbf4 @ 0x0229fbf4, 0x24 bytes, Thumb
 * func_ov112_0229fbf0 @ 0x0229fbf0, 0x2 bytes, Thumb
 * func_ov112_0229fbc0 @ 0x0229fbc0, 0x30 bytes, Thumb
 * func_ov112_0229fb8c @ 0x0229fb8c, 0x34 bytes, Thumb
 * func_ov112_0229fb7c @ 0x0229fb7c, 0x10 bytes, Thumb
 * func_ov112_0229fb70 @ 0x0229fb70, 0xc bytes, Thumb
 * func_ov112_0229fae8 @ 0x0229fae8, 0x88 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229fe60 {
    unsigned char pad_00[0xac];
    unsigned int flags;
};

struct UnkStruct_0229fe50 {
    char pad_00[0xac];
    unsigned int unk_AC;
};

typedef struct {
    unsigned char pad_00[0xb6];
    unsigned char b6;
    unsigned char b7;
    unsigned char b8;
} UnkStruct_0229fb8c;

struct UnkStruct_0229fb7c {
    char pad_00[0xb7];
    char unk_B7;
};

typedef struct {
    char pad_00[0xb6];
    unsigned char b6;
    unsigned char b7;
    unsigned char b8;
} UnkStruct_0229fae8;

extern int func_0206de88(void *a, void *b, void *c, int d, int e, int f, int g);
extern void func_020a8c1c(void *q);
extern void func_02070870(void *q, void *p, int d, int t, int u);
extern void func_02070a54(void *a, void *b, int c, int d, int e);
extern void func_ov112_0229f488(u8 *self);
extern int func_ov112_0229f900(void *p);
extern void func_02070854(u8 *p, int a, int b, unsigned int off, unsigned int n);
extern void func_02070a04(void *ptr, int a, int b);
extern void func_02070b84(void *ptr);
extern int func_020b9c10(int, int, int, int, int, int);
extern int _s32_div_f(int, int);

void func_ov112_0229fcd4(void *p);
void func_ov112_0229fc48(u8 *base, int a1, int a2, unsigned int pos, unsigned int rem);

int func_ov112_0229fe70(int *a, int b)
{
    if (a[0x2b] & b) {
        return 1;
    }
    return 0;
}

void func_ov112_0229fe60(struct UnkStruct_0229fe60 *self, unsigned int mask)
{
    self->flags |= mask;
}

void func_ov112_0229fe50(struct UnkStruct_0229fe50 *s, unsigned int mask)
{
    unsigned int temp;
    temp = s->unk_AC;
    temp &= ~mask;
    s->unk_AC = temp;
}

void func_ov112_0229fd20(u8 *self)
{
    u16 buf[0x10];
    int *pa;
    u8 *q;
    int i;
    int flag;
    int d;
    int t, u;

    func_0206de88(self + 0xc4, self + 0x6c50, self + 0x94, 0x60, 0x10, 0xa0, 6);
    if (func_ov112_0229fe70((int *) self, 0x10) != 0) {
        flag = 0;
    } else if (func_ov112_0229fe70((int *) self, 0x400) != 0) {
        flag = 0;
    } else {
        flag = 1;
    }
    buf[0] = 0;
    for (i = 0; i < 6; i++) {
        pa = (int *) (self + i * 4 + 0x6c50);
        d = *(int *) (self + (i + 1) * 4 + 0x6c50) - *(int *) (self + i * 4 + 0x6c50);
        q = self + 0x3fac + i * 0x6c;
        func_020a8c1c(q);
        if (d != 0) {
            if (i == 0) {
                t = 0;
            } else {
                t = flag;
            }
            if (i == *(int *) (self + 0x94)) {
                u = 1;
            } else {
                u = 0;
            }
            func_02070870(q, self + 0xc4 + *pa * 2, d, t, u);
        } else if (flag != 0 && i == *(int *) (self + 0x94)) {
            func_02070870(q, buf, 1, flag, 1);
        }
    }
    for (i = 0; i < 6; i++) {
        func_02070a54(self + 0x3fac + i * 0x6c, self + 0x4e50 + i * 0x500, 0x14, 0xe, 0xd);
    }
    func_ov112_0229fcd4((void *) self);
    func_ov112_0229fe60((struct UnkStruct_0229fe60 *) self, 4);
    func_ov112_0229f488(self);
}

void func_ov112_0229fcd4(void *p)
{
    unsigned char b0, b1, min;
    int diff;
    int a1, a2;

    if (func_ov112_0229f900(p)) {
        b1 = ((unsigned char *) p)[0xbf];
        b0 = ((unsigned char *) p)[0xbe];
        if (b0 > b1) {
            min = b1;
            diff = b0 - b1;
        } else {
            min = b0;
            diff = b1 - b0;
        }
        a1 = 13;
        a2 = 14;
    } else {
        diff = 0;
    }

    if (diff != 0) {
        func_ov112_0229fc48((u8 *) p, a1, a2, (unsigned char) min, diff);
    }
}

void func_ov112_0229fc48(u8 *base, int a1, int a2, unsigned int pos, unsigned int rem)
{
    int i;
    unsigned int acc;
    int len;
    unsigned int take;
    unsigned int end;

    acc = 0;
    for (i = 0; i < 6; i++) {
        len = *(int *) (base + (i + 1) * 4 + 0x6c50) - *(int *) (base + i * 4 + 0x6c50);
        if (len == 0) {
            return;
        }
        if (pos >= acc) {
            end = acc + len;
            if (pos < end) {
                if (end > pos + rem) {
                    take = rem;
                } else {
                    take = len - (pos - acc);
                }
                func_02070854(base + 0x3fac + i * 0x6c, a1, a2, pos - acc, take);
                pos = (u8) end;
                rem -= take;
                if (rem == 0) {
                    return;
                }
            }
        }
        acc += len;
    }
}

void func_ov112_0229fc18(void *p)
{
    int i = 0;
    char *base = (char *) p + 0x3fac;
    int zero = i;

    for (; i < 6; i++) {
        func_02070a04(base + i * 108, zero, zero);
    }
}

void func_ov112_0229fbf4(void *arg)
{
    int i = 0;
    char *base = (char *) arg + 0x3fac;
    do {
        func_02070b84(base + i * 0x6c);
        i++;
    } while (i < 6);
}

void func_ov112_0229fbf0(void *receiver) {}

void func_ov112_0229fbc0(int param)
{
    func_020b9c10(param + 0x360, param + 0x4e50, 4, 17, 17, 0x100);
}

void func_ov112_0229fb8c(UnkStruct_0229fb8c *self, unsigned char param)
{
    self->b6 = param;
    self->b7 = self->b6;
    func_ov112_0229fe60((struct UnkStruct_0229fe60 *) self, 0x20);
    self->b8 = _s32_div_f(self->b6 * 2, 3);
}

void func_ov112_0229fb7c(struct UnkStruct_0229fb7c *p, char c)
{
    p->unk_B7 = c;
    func_ov112_0229fe60((struct UnkStruct_0229fe60 *) p, 0x20);
}

int func_ov112_0229fb70(int a)
{
    return func_ov112_0229fe70((int *) a, 0x20);
}

void func_ov112_0229fae8(UnkStruct_0229fae8 *self)
{
    if (self->b6 == self->b7) {
        func_ov112_0229fe50((struct UnkStruct_0229fe50 *) self, 0x20);
    } else if (self->b6 < self->b7) {
        self->b6 += 8;
        if (self->b6 > self->b7) {
            self->b6 = self->b7;
        }
    } else {
        if (self->b6 < 8) {
            self->b6 = self->b7;
        } else {
            self->b6 -= 8;
            if (self->b6 < self->b7) {
                self->b6 = self->b7;
            }
        }
    }
    self->b8 = (unsigned char) _s32_div_f(self->b6 << 1, 3);
}
