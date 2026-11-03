/* field_actor_states_27: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200d4e8 @ 0x0200d4e8, 0x40 bytes, Thumb
 * func_0200d48c @ 0x0200d48c, 0x5c bytes, Thumb
 * func_0200d478 @ 0x0200d478, 0x14 bytes, Thumb
 * func_0200d44c @ 0x0200d44c, 0x2c bytes, Thumb
 * func_0200d3a4 @ 0x0200d3a4, 0xa6 bytes, Thumb
 * func_0200d2bc @ 0x0200d2bc, 0xe8 bytes, Thumb
 * func_0200d258 @ 0x0200d258, 0x64 bytes, Thumb
 * func_0200d1e4 @ 0x0200d1e4, 0x74 bytes, Thumb
 * func_0200d1e0 @ 0x0200d1e0, 0x4 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned int data[3];
} UnkStruct_0200d4e8;

typedef struct {
    unsigned int data[4];
} UnkStruct_0200d4e8_2;

struct UnkStruct_0200d44c {
    char pad_00[0x7f8];
    int unk_7F8;
    char pad_7FC[4];
    int unk_800;
};

typedef struct UnkStruct_0200d3a4 {
    u8 pad_00[0x5c];
    s32 unk_5C;
    u8 pad_60[4];
    s32 unk_64;
    u8 pad_68[0x26];
    s16 unk_8E;
} UnkStruct_0200d3a4;

typedef struct UnkStruct_0200d1e4 UnkStruct_0200d1e4;

struct UnkStruct_0200d1e4 {
    char data[0x7d4];
    char flag;
    char pad_7D5[0x800 - 0x7d4 - 1];
    int value;
};

extern unsigned int func_0200e92c(UnkStruct_0200d4e8 *);
extern void func_0200e90c(UnkStruct_0200d4e8 *, int, int, int);
extern void func_0200d528(UnkStruct_0200d4e8_2 *, int);
extern int func_0200e894(void *, UnkStruct_0200d4e8 *);
extern int func_0200e91c(UnkStruct_0200d4e8 *);
extern int func_0200f748(unsigned char *);
extern void func_020109fc(unsigned char *, int, int, int);
extern void func_0200eebc(unsigned char *);
extern void func_0200f268(unsigned char *, int);
extern int func_02095518(int, int, int);
extern int func_02073908(int, int);
extern int data_020ccf94;
extern int func_0200e9a8(void *self, void *loc, s32 *x, s32 *y, s16 *v);
extern int func_020b65c4(void);
extern int FX_MulFunc(s32 a, s32 b);
extern int func_0200e93c(void *self, s32 dx, s32 dy, s32 sum, s32 v, s16 *arr);
extern int func_020113bc(s16 *p, s32 v);
extern void func_020110a0(void *self, s16 *p);
extern void func_02011490(s32 *p, s32 val);
extern int func_02010718(char *);
extern int func_020b67d4(void);
extern unsigned char *func_0209626c(void);
extern int func_02008dc0(unsigned char *, short, int, int);
extern int func_0200d1a0(unsigned char *, unsigned char, int, int);
extern int func_02010538(unsigned char *);
extern int func_020912d4(int, unsigned char *, short *, int);
extern unsigned char data_021c75b8;
extern unsigned char data_ov004_02259a08;
extern int func_02096124(int a, int b);
extern int func_02096518(int *out, int a, int b);
extern int func_0201100c(UnkStruct_0200d1e4 *);
extern void func_02010f5c(UnkStruct_0200d1e4 *);
extern void func_02010d64(UnkStruct_0200d1e4 *);
extern int func_02010ca4(UnkStruct_0200d1e4 *);
extern void func_0200ef1c(UnkStruct_0200d1e4 *);

int func_0200d4e8(void *p, int n, int a, int b)
{
    UnkStruct_0200d4e8 s1;
    UnkStruct_0200d4e8_2 s2;
    int res;

    func_0200e92c(&s1);
    func_0200e90c(&s1, 2, a, b);
    func_0200d528(&s2, n);
    res = func_0200e894(p, &s1);
    func_0200e91c(&s1);
    return res;
}

void func_0200d48c(unsigned char *self, unsigned char *other, int flag)
{
    unsigned short val;

    if (func_0200f748(self)) {
        return;
    }

    val = *(unsigned short *) (other + 0xc);

    self[0x7d4] = (flag == 4) ? 1 : 0;

    func_020109fc(self, 0, val, val);
    func_0200eebc(self);
    func_0200f268(self, 9);

    *(unsigned int *) (self + 0x168) = 0;
    self[0x16c] = 0;

    func_02095518(0, 0, 4);
}

void func_0200d478(int a, int b)
{
    func_0200d4e8((void *) a, 3, 5, b);
}

void func_0200d44c(struct UnkStruct_0200d44c *s)
{
    if (func_02073908(data_020ccf94, s->unk_800) == 0) {
        s->unk_7F8 = 1;
    }
}

int func_0200d3a4(UnkStruct_0200d3a4 *self)
{
    struct {
        u8 id;
        u8 pad;
        s16 v;
        s16 arr[2];
        s32 x;
        s32 y;
    } loc;
    s32 dx, dy, sum, ret;

    if (func_0200e9a8(self, &loc, &loc.x, &loc.y, &loc.v) == 0) {
        return 0;
    }
    if (func_020b65c4() != loc.id) {
        return 0;
    }

    dx = loc.x - self->unk_5C;
    dy = loc.y - self->unk_64;
    sum = FX_MulFunc(dx, dx) + FX_MulFunc(dy, dy);

    ret = func_0200e93c(self, dx, dy, sum, loc.v, loc.arr);
    if (ret == 0) {
        loc.arr[1] = self->unk_8E;
        func_020113bc(&loc.arr[1], loc.v);
        func_020110a0(self, &loc.arr[1]);
        func_02011490(&self->unk_5C, loc.x);
        func_02011490(&self->unk_64, loc.y);
    }
    return ret;
}

void func_0200d2bc(unsigned char *self)
{
    int r4;
    int r6;

    r6 = func_02010718((char *) self);
    r4 = 0;

    if (func_020b67d4() != 0) {
        unsigned int ok;

        ok = (data_021c75b8 == 2);
        if (ok > 0) {
            if ((*func_0209626c() & 8) == 0) {
                if (data_ov004_02259a08 != 0) {
                    *func_0209626c() |= 8;
                    func_02008dc0(self, *(short *) (self + 0x8e), 6, -1);
                    return;
                }
            }
        }
    }

    if (r6 > 0) {
        unsigned char c;

        c = *(self + 0x7d4);
        if (r6 < 0x53f) {
            c = 0;
        }
        r4 = func_0200d1a0(self, c, 1, -1);
    }

    if (func_02010538(self) == 0) {
        r4 |= func_0200f748(self);
    } else {
        r4 = 1;
    }

    if (r4 != 0) {
        short v;
        short tmp;

        v = *(short *) (self + 0x8e);
        tmp = v + 0xaf0;
        func_020912d4(0x27, self + 0x6d4, &tmp, 0);
        tmp = v - 0xaf0;
        func_020912d4(0x27, self + 0x6c8, &tmp, 0);
    }
}

void func_0200d258(void *p, const unsigned char *q)
{
    int st;

    if (*q) {
        func_0200d1a0((unsigned char *) p, 0, 1, -1);
    }
    if (*(int *) ((char *) p + 0x7f8) == 0) {
        if (func_02096124(0x1b, 4)) {
            *(int *) ((char *) p + 0x7f8) = 1;
        } else if (func_02096518(&st, -1, *(int *) ((char *) p + 0x800))) {
            if (st == 2 || st == 0x40) {
                *(int *) ((char *) p + 0x7f8) = 1;
            }
        }
    }
}

void func_0200d1e4(UnkStruct_0200d1e4 *obj)
{
    char tmp;

    if (func_02073908(data_020ccf94, obj->value)) {
        func_0201100c(obj);
        func_02010f5c(obj);
        func_02010d64(obj);
        func_02010ca4(obj);
        func_0200d2bc((unsigned char *) obj);
    } else {
        tmp = (char) func_0200d3a4((UnkStruct_0200d3a4 *) obj);
        func_02010f5c(obj);
        func_0200ef1c(obj);
        func_02010ca4(obj);
        func_0200d258((void *) obj, (const unsigned char *) (&tmp));
    }
    obj->flag = 0;
}

void func_0200d1e0(unsigned char *p0, int p1)
{
    p0[0] = p1;
}
