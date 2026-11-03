/* villager_talk_4: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201dc58 @ 0x0201dc58, 0x64 bytes, Thumb
 * func_0201dbec @ 0x0201dbec, 0x6c bytes, Thumb
 * func_0201db88 @ 0x0201db88, 0x64 bytes, Thumb
 * func_0201db24 @ 0x0201db24, 0x64 bytes, Thumb
 * func_0201da98 @ 0x0201da98, 0x8c bytes, Thumb
 * func_0201da64 @ 0x0201da64, 0x34 bytes, Thumb
 * func_0201d9ec @ 0x0201d9ec, 0x78 bytes, Thumb
 * func_0201d9b8 @ 0x0201d9b8, 0x34 bytes, Thumb
 * func_0201d940 @ 0x0201d940, 0x78 bytes, Thumb
 * func_0201d8c0 @ 0x0201d8c0, 0x80 bytes, Thumb
 * func_0201d7dc @ 0x0201d7dc, 0xe4 bytes, Thumb
 * func_0201d7b8 @ 0x0201d7b8, 0x24 bytes, Thumb
 * func_0201d71c @ 0x0201d71c, 0x9c bytes, Thumb
 */

#include "types.h"

struct GlobalInfo {
    int unk_00;
    unsigned char unk_04;
};

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} Param;

struct UnkStruct_0201db88 {
    char pad_00[0x830];
    int value;
};

struct UnkStruct_0201db88_2 {
    char pad_00[0x100];
    struct UnkStruct_0201db88 *inner;
    char buf[0x1e];
    unsigned char flag;
};

struct UnkStruct_0201db88_3 {
    char *ptr;
    unsigned char byte;
};

struct Global {
    int word;
    unsigned char byte;
};

struct UnkStruct_0201db24 {
    char pad_00[0x830];
    unsigned int unk_830;
};

struct UnkStruct_0201db24_2 {
    char pad_00[0x100];
    struct UnkStruct_0201db24 *unk_100;
    unsigned char unk_104[30];
    unsigned char unk_122;
};

struct UnkStruct_0201db24_3 {
    unsigned char *field0;
    unsigned char unk_04;
};

struct UnkStruct_0201da98 {
    char pad_00[0x830];
    int value;
};

struct DataC {
    int unk_00;
    unsigned char unk_04;
};

struct Pair {
    int a;
    int b;
};

struct UnkStruct_0201da98_2 {
    char pad_00[0xc8];
    int unk_C8;
    int unk_CC;
    char pad_D0[0x100 - 0xd0];
    struct UnkStruct_0201da98 *unk_100;
    char unk_104;
    char pad_105[0x122 - 0x105];
    unsigned char unk_122;
    char pad_123[0x12c - 0x123];
    int unk_12C;
    char pad_130[0x13c - 0x130];
    unsigned char unk_13C;
};

struct UnkStruct_0201da98_3 {
    void *ptr;
    unsigned char byte;
};

struct UnkStruct_0201da64 {
    char unk_00[0x830];
    void *unk_830;
};

struct UnkStruct_0201da64_2 {
    char unk_00[0x100];
    struct UnkStruct_0201da64 *sub;
    char unk_104[0x24];
    int unk_128;
    int unk_12C;
};

typedef struct {
    int low;
    int high;
} Pair_0201d9ec;

typedef struct UnkStruct_0201d9ec_2 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0201d9ec_2;

typedef struct UnkStruct_0201d9ec {
    char pad_00[0xc8];
    Pair_0201d9ec unk_C8;
    char pad_D0[0x30];
    UnkStruct_0201d9ec_2 *ptr;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_0201d9ec;

typedef struct {
    char *unk_00;
    unsigned char unk_04;
} UnkStruct_0201d9ec_3;

typedef struct {
    int first;
    unsigned char second;
} UnkStruct_0201d9ec_4;

typedef struct {
    char pad_00[0xc8];
    int unk_C8;
    int unk_CC;
    char pad_D0[0x30];
    void *ptr;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_0201d940;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_0201d940_2;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Global1;

typedef struct {
    int unk_00;
    int unk_04;
} Global2;

typedef struct {
    u8 pad_00[0x124];
    u16 unk_124;
    u8 pad_126[0x19c - 0x126];
    u16 unk_19C;
} UnkStruct_0201d8c0;

struct UnkStruct_0201d7dc {
    char pad_00[0x830];
    int unk_830;
};

struct UnkStruct_0201d7dc_2 {
    char pad_00[0x100];
    struct UnkStruct_0201d7dc *unk_100;
    char pad_104[0x28];
    int unk_12C;
    char pad_130[0x8];
    int unk_138;
};

struct Big {
    unsigned char a[0x28];
    unsigned char b[0x34];
    unsigned char c[0x20];
    unsigned char d[0x98];
};

typedef struct {
    unsigned char pad_00[0x138];
    unsigned int _field_138;
} UnkStruct_0201d7b8;

typedef struct UnkStruct_0201d71c {
    unsigned char pad_00[0x124];
    unsigned short unk_124;
    unsigned char pad_126[0x19c - 0x124 - 2];
    unsigned short unk_19C;
    unsigned char pad_19E[0x1a0 - 0x19c - 2];
    int unk_1A0;
} UnkStruct_0201d71c;

typedef struct Pair_0201d71c {
    int a;
    int b;
} Pair_0201d71c;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern struct GlobalInfo data_020c8d18;
extern void func_0201cfb4(void *param, void *buf);
extern void func_0201cf90(void *param, void *buf, int index, int a, int b, void *data);
extern void func_0201cec8(void *param, void *buf);
extern void func_02068388(int value, int flag);
extern void func_0202da74(void *object, Pair value);
extern Pair data_020d91c8;
extern char data_021c22a4;
extern char data_021c22bc;
extern int func_0202da38(void *a0, void *a1, void *a2, int a3, int a4, int a5, int a6, int a7, int a8);
extern struct DataC data_020c89f8;
extern struct Pair data_020d8e50;
extern void func_0202d8f8(struct UnkStruct_0201da64_2 *a, void *b, void *c, void *d, int e);
extern UnkStruct_0201d9ec_4 data_020c8d68;
extern Pair_0201d9ec data_020d9110;
extern Global1 data_020c8be0;
extern Global2 data_020d8e18;
extern int func_020984e8(void);
extern int func_02099734(int a);
extern int func_02098eb8(int id);
extern int func_02098f0c(u16 *p0, u16 *p1, int p2, int p3);
extern int func_020996ac(int a);
extern s32 func_0203cd2c(int lockID, void *lockp, void *ctrlFuncp, BOOL b);
extern int func_020154b4(UnkStruct_0201d8c0 *s, u16 *p, unsigned int v2, unsigned char v3, unsigned int v4);
extern int func_020814f4(int);
extern int func_02081a14(void *);
extern void *func_0206daf8(unsigned char *);
extern void *func_0206da98(unsigned char *);
extern void *func_0206da38(unsigned char *);
extern void *func_02094fd4(unsigned char *);
extern int func_02003618(int, unsigned char *);
extern void func_0203d73c(unsigned char *);
extern void *func_02094fbc(unsigned char *);
extern int func_0203d930(unsigned char *, unsigned char *, unsigned char *, int *, unsigned char *, unsigned char *);
extern void func_02066198(unsigned char *, unsigned char *, unsigned char *, unsigned char *, int, unsigned char *, int, int);
extern void *func_0206da20(unsigned char *);
extern void *func_0206da80(unsigned char *);
extern void *func_0206dae0(unsigned char *);
extern void func_0201579c(struct UnkStruct_0201d7dc_2 *, void *, int);
extern int func_02015828(struct UnkStruct_0201d7dc_2 *, int);
extern unsigned char data_021c2604;
extern unsigned char data_020d9f5c;
extern unsigned char data_020d8d1c;
extern int func_02014bc0(void *, unsigned int);
extern int func_02099e9c(unsigned short *p);
extern void func_02098a24(int a, int b, int c);
extern void func_02027170(unsigned short *p, int v);
extern void func_0202dbf0(UnkStruct_0201d71c *s, Pair_0201d71c p);
extern Pair_0201d71c data_020d9060;

void func_0201dc58(unsigned char *p1, unsigned char *out)
{
    int arg5 = func_020036e8(func_0208150c(*(int *) ((unsigned char *) (*(int *) (p1 + 0x100)) + 0x830)));
    int arg6 = data_020c8d18.unk_00;
    int arg7 = 1;
    int arg8 = 2;
    int arg9 = data_020c8d18.unk_04;

    func_0202da38((void *) p1, (void *) (p1 + 0x104), (void *) (p1 + 0x122), 30, arg5, arg6, arg7, arg8, arg9);

    *(int *) out = (int) (p1 + 0x104);
    out[4] = p1[0x122];
}

void func_0201dbec(Param *param)
{
    char buf[40];

    func_0201cfb4(param, buf);
    func_0201cf90(param, buf, 0, 0x32, 0x32, (void *) &data_021c22a4);
    func_0201cf90(param, buf, 1, 0x33, 0x33, (void *) &data_021c22bc);
    buf[32] = 2;
    buf[33] = -1;
    func_0201cec8(param, buf);
    func_0202da74(param, data_020d91c8);
    func_02068388(param->unk_40, 1);
}

void func_0201db88(struct UnkStruct_0201db88_2 *self, struct UnkStruct_0201db88_3 *out)
{
    func_0202da38((void *) self, (void *) self->buf, (void *) (&self->flag), 0x1e, func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c(self->inner->value))), (*(struct Global *) &data_020c8d18).word, 1, 3, (*(struct Global *) &data_020c8d18).byte);
    out->ptr = self->buf;
    out->byte = self->flag;
}

unsigned char func_0201db24(struct UnkStruct_0201db24_2 *s, struct UnkStruct_0201db24_3 *out)
{
    unsigned char c;
    func_0202da38((void *) s, (void *) s->unk_104, (void *) (&s->unk_122), 0x1e, func_020036e8(func_0208150c(s->unk_100->unk_830)), (*(struct { unsigned int field0; unsigned char field4; } *) &data_020c8d18).field0, 1, 4, (*(struct { unsigned int field0; unsigned char field4; } *) &data_020c8d18).field4);
    out->field0 = s->unk_104;
    c = s->unk_122;
    out->unk_04 = c;
    return c;
}

void func_0201da98(struct UnkStruct_0201da98_2 *self, struct UnkStruct_0201da98_3 *out)
{
    int a, b, c, d, e;
    a = func_020036e8(func_0208150c(self->unk_100->value));
    b = data_020c89f8.unk_00;
    c = data_020c89f8.unk_04;
    d = 0;
    e = 0;
    func_0202da38(self, &self->unk_104, &self->unk_122, 30, a, b, c, d, e);
    out->ptr = &self->unk_104;
    out->byte = self->unk_122;
    if (self->unk_12C == 0) {
        self->unk_13C = 1;
    }
    *(struct Pair *) ((char *) self + 0xc8) = data_020d8e50;
}

void func_0201da64(struct UnkStruct_0201da64_2 *a, void *event)
{
    func_0202d8f8(a, &a->unk_12C, &a->unk_128, a->sub->unk_830, 0);
}

void func_0201d9ec(UnkStruct_0201d9ec *a, UnkStruct_0201d9ec_3 *out)
{
    func_0202da38(a, (void *) a->unk_104, &a->unk_122, 0x1e, func_020036e8(func_0208150c(a->ptr->unk_830)), data_020c8d68.first, data_020c8d68.second, 0, 0);

    out->unk_00 = a->unk_104;
    out->unk_04 = a->unk_122;

    a->unk_C8 = data_020d9110;
}

void func_0201d9b8(void *p, void *event)
{
    func_0202d8f8((struct UnkStruct_0201da64_2 *) p, (char *) p + 0x12c, (char *) p + 0x128, *(void **) ((char *) *(void **) ((char *) p + 0x100) + 0x830), 0);
}

void func_0201d940(UnkStruct_0201d940 *s, UnkStruct_0201d940_2 *out)
{
    int a;
    int b;
    int c;
    int d;
    int e;
    a = func_020036e8(func_0208150c(*((int *) (((char *) s->ptr) + 0x830))));
    b = data_020c8be0.unk_00;
    c = data_020c8be0.unk_04;
    d = 0;
    e = 0;
    func_0202da38(s, s->unk_104, &s->unk_122, 0x1e, a, b, c, d, e);
    out->ptr = s->unk_104;
    out->byte = s->unk_122;
    {
        int tmp0 = data_020d8e18.unk_00;
        int tmp1 = data_020d8e18.unk_04;
        if (data_020c8be0.unk_04) {
            s->unk_C8 = tmp0;
        } else {
            s->unk_C8 = tmp0;
        }
        s->unk_CC = tmp1;
    }
}

int func_0201d8c0(UnkStruct_0201d8c0 *self)
{
    u16 code = self->unk_124;

    if (self->unk_19C != 0xfff1) {
        code = self->unk_19C;
    }
    if (code == 0xfff1) {
        goto fail;
    }

    {
        int a = func_020984e8();
        int b = func_02099734(a);
        int slotIdx = func_02098eb8(b);

        if (slotIdx == -1) {
            goto fail;
        }

        func_02098f0c((u16 *) b, &code, slotIdx, 0);
        {
            int lockId = func_020996ac(a);
            func_0203cd2c(lockId, &code, 0, 1);
        }
        func_020154b4(self, &code, 0, 5, 0);
        return 1;
    }

fail:
    return 0;
}

int func_0201d7dc(struct UnkStruct_0201d7dc_2 *self)
{
    void *tested_value0;
    void *p;
    int a;
    int b;
    struct Big big;
    int result;
    unsigned char flag;

    if (self->unk_138 != 0) {
        p = (void *) func_020814f4(self->unk_100->unk_830);
    } else {
        a = func_0208150c(self->unk_100->unk_830);

        func_0206daf8(big.a);
        func_0206da98(big.d);
        func_0206da38(big.b);

        b = 0;
        p = &data_021c2604;
        if ((tested_value0 = (void *) (self->unk_12C)) != 0) {
            b = func_02081a14(tested_value0);
        }

        func_02094fd4(big.c);
        func_02003618(a, big.c);
        func_0203d73c(big.c);
        func_02094fbc(big.c);

        flag = (unsigned char) b;
        func_0203d930(big.a, big.d, big.b, &result, &flag, &data_020d9f5c);
        func_02066198(p, big.a, big.d, big.b, result, &data_020d8d1c, a, a);

        func_0206da20(big.b);
        func_0206da80(big.d);
        func_0206dae0(big.a);
    }

    func_0201579c(self, p, 0);
    func_02015828(self, 5);
    return 1;
}

int func_0201d7b8(UnkStruct_0201d7b8 *arg)
{
    unsigned int field = arg->_field_138;
    if (field != 0) {
        func_02014bc0(arg, field + 0x74);
        return 1;
    }
    return 0;
}

int func_0201d71c(UnkStruct_0201d71c *s)
{
    int ret;
    int status;
    unsigned short tmp[2];

    if (s->unk_1A0 <= 0) {
        goto fail;
    }
    if (s->unk_124 == 0xfff1) {
        goto fail;
    }

    ret = func_02099734((int) func_020984e8());
    status = func_02099e9c(&s->unk_124);
    if (status < 0) {
        goto fail;
    }

    tmp[0] = 0xfff1;
    func_02098f0c((u16 *) ret, (u16 *) tmp, status, 0);
    func_02098a24(ret, s->unk_1A0, 1);
    func_02027170(&tmp[1], s->unk_1A0);
    s->unk_19C = tmp[1];

    func_020154b4((UnkStruct_0201d8c0 *) s, (u16 *) (&s->unk_19C), 0, 5, 0);
    func_0202dbf0(s, data_020d9060);

    return 1;
fail:
    return 0;
}
