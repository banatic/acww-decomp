/* field_actor_states_22: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200c648 @ 0x0200c648, 0xc0 bytes, Thumb
 * func_0200c610 @ 0x0200c610, 0x38 bytes, Thumb
 * func_0200c5e0 @ 0x0200c5e0, 0x30 bytes, Thumb
 * func_0200c598 @ 0x0200c598, 0x48 bytes, Thumb
 * func_0200c4cc @ 0x0200c4cc, 0xcc bytes, Thumb
 * func_0200c47c @ 0x0200c47c, 0x50 bytes, Thumb
 * func_0200c41c @ 0x0200c41c, 0x60 bytes, Thumb
 * func_0200c3f4 @ 0x0200c3f4, 0x26 bytes, Thumb
 * func_0200c3f0 @ 0x0200c3f0, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0200c648;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char pad_5C[0x8e - 0x5c];
    short unk_8E;
    unsigned char pad_90[0x2d0 - 0x90];
    int unk_2D0;
    unsigned char pad_2D4[0x6c8 - 0x2d4];
    int fAx, fAy, fAz;
    int fBx, fBy, fBz;
} UnkStruct_0200c648_2;

typedef struct {
    unsigned short unk_00;
    unsigned char pad[10];
    unsigned char unk_0C;
} UnkStruct_0200c610;

typedef struct {
    char pad[0x7d4];
    UnkStruct_0200c610 sub;
} UnkStruct_0200c610_2;

typedef struct {
    unsigned short unk_00;
    unsigned char pad_02[10];
    unsigned char unk_0C;
} UnkStruct_0200c5e0;

typedef struct UnkStruct_0200c41c {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x50b];
    int unk_7DC;
    char pad_7E0[0x10];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
} UnkStruct_0200c41c;

extern void func_02010f5c(int);
extern int func_02056f28(void *flags, int bit);
extern int func_020912d4(int type, void *a, void *b, int c);
extern void func_02010680(void *p, unsigned short *val);
extern int func_0201063c(void *p);
extern int func_020103c0(void *base, unsigned short *local);
extern int func_020112e4(void *p);
extern int func_020112d0(void *p);
extern int func_020100e8(void *p, unsigned short *t, int a, int b, int c);
extern void func_0200f268(void *p, int n);
extern unsigned int *func_0200f27c(void *p, int n);
extern void *func_020984fc(u32 v);
extern void func_02099740(void *p, int n);
extern void *func_0209984c(void *p);
extern int func_0205dc94(void *p, void *v);
extern void func_02010bf0(void *p, const char *s, char *buf);
extern void func_02010bac(void *p, const char *s, char *buf);
extern void func_02079280(void);
extern unsigned char data_020d72fc[];
extern unsigned char data_020d7304[];
extern void func_020110a0(void *s, short *src);
extern int func_02056f94(const void *);
extern int func_02008258(UnkStruct_0200c41c *, int);
extern int func_0200c9a8(UnkStruct_0200c41c *, int, int, int);
extern int func_0200c3b0(UnkStruct_0200c41c *, int, int, int);
extern int func_02095bdc(void);
extern void func_02010d64(void *object);

void func_0200c648(UnkStruct_0200c648_2 *self)
{
    short h;
    UnkStruct_0200c648 v;
    short f8e;

    func_02010f5c((int) self);

    if (func_02056f28(&self->unk_2D0, 0xd)) {
        func_020912d4(0x22, (char *) self + 0x5c, 0, 0);
        return;
    }

    if (!func_02056f28(&self->unk_2D0, 3)) {
        return;
    }

    f8e = self->unk_8E;

    v.x = self->fBx;
    v.y = self->fBy;
    v.z = self->fBz;
    v.z = v.z + 0x266;
    h = f8e + 0xaf0;
    func_020912d4(0x27, &v, &h, 0);

    v.x = self->fAx;
    v.y = self->fAy;
    v.z = self->fAz;
    v.z = v.z + 0x266;
    h = f8e - 0xaf0;
    func_020912d4(0x27, &v, &h, 0);
}

void func_0200c610(UnkStruct_0200c610_2 *p)
{
    UnkStruct_0200c610 *q;
    unsigned short val;

    q = &p->sub;
    if (q->unk_0C == 0) {
        val = q->unk_00;
        func_02010680(p, &val);
        if (func_0201063c(p) != 0) {
            q->unk_0C = 1;
        }
    }
}

void func_0200c5e0(void *base)
{
    UnkStruct_0200c5e0 *p;
    unsigned short val;
    p = (UnkStruct_0200c5e0 *) ((char *) base + 0x7d4);
    if (p->unk_0C == 0) {
        val = p->unk_00;
        if (func_020103c0(base, &val)) {
            p->unk_0C = 1;
        }
    }
}

void func_0200c598(unsigned char *p)
{
    unsigned char *q = p + 0x7d4;
    if (q[0xc] == 0) {
        unsigned short t;
        int a;
        int b;
        t = *(unsigned short *) q;
        a = func_020112e4(p);
        b = func_020112d0(p);
        if (func_020100e8(p, &t, a, b, 0) != 0) {
            q[0xc] = 1;
        }
    }
}

void func_0200c4cc(u8 *self)
{
    char buf[2];
    u32 idx;
    void *p;
    void *q;

    func_0200f268(self, 0xf);
    if (!func_02056f28(self + 0x2d0, 8)) {
        return;
    }
    func_0200f27c(self, 0xf);

    idx = *(u32 *) (self + 0x7d8);
    switch (idx) {
        case 0:
            func_0200c610((UnkStruct_0200c610_2 *) self);
            break;
        case 1:
            func_0200c5e0(self);
            break;
        case 2:
            func_0200c598((unsigned char *) self);
            break;
        case 3:
            p = func_020984fc(*(u32 *) (self + 0x800));
            if (p == 0) {
                return;
            }
            func_02099740(p, 0);
            q = func_0209984c(p);
            func_0205dc94(self + 0x70d, q);
            buf[0] = *(u8 *) (self + 0x2e4);
            func_02010bf0(self, (const char *) data_020d72fc, buf);
            buf[1] = *(u8 *) (self + 0x2e4);
            func_02010bac(self, (const char *) data_020d7304, &buf[1]);
            func_02079280();
            break;
    }
}

void func_0200c47c(void *base)
{
    short local = *(short *) ((char *) base + 0x8e);
    short v2 = *(short *) ((char *) base + 0x7e2);
    if (local != 0) {
        int a = (local < 0) ? -local : local;
        int b = (v2 < 0) ? -v2 : v2;
        if (a < b) {
            local = 0;
        } else {
            local += v2;
        }
    }
    func_020110a0(base, &local);
}

void func_0200c41c(UnkStruct_0200c41c *p)
{
    if (func_02056f94(&p->unk_2D0)) {
        p->unk_7FC = func_02008258(p, p->unk_7F0);
        if (p->unk_7DC == 5) {
            func_0200c9a8(p, 0, 5, -1);
        } else if (p->unk_7DC == 0x10) {
            func_0200c3b0(p, 0, 5, -1);
        } else {
            func_02095bdc();
        }
    }
}

void func_0200c3f4(void *param)
{
    func_0200c648((UnkStruct_0200c648_2 *) param);
    func_0200c4cc((u8 *) param);
    func_0200c47c(param);
    func_02010d64(param);
    func_0200c41c((UnkStruct_0200c41c *) param);
}

void func_0200c3f0(unsigned short *p0, int p1)
{
    p0[0] = p1;
}
