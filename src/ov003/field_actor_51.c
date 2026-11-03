/* field_actor_51: 14 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02218524 @ 0x02218524, 0x8c bytes, Thumb
 * func_ov003_022184e8 @ 0x022184e8, 0x3c bytes, Thumb
 * func_ov003_02218474 @ 0x02218474, 0x74 bytes, Thumb
 * func_ov003_0221844c @ 0x0221844c, 0x28 bytes, Thumb
 * func_ov003_0221842c @ 0x0221842c, 0x20 bytes, Thumb
 * func_ov003_022183f4 @ 0x022183f4, 0x36 bytes, Thumb
 * func_ov003_022183d8 @ 0x022183d8, 0x1c bytes, Thumb
 * func_ov003_022183cc @ 0x022183cc, 0xc bytes, Thumb
 * func_ov003_022183c8 @ 0x022183c8, 0x2 bytes, Thumb
 * func_ov003_02218388 @ 0x02218388, 0x3e bytes, Thumb
 * func_ov003_02218344 @ 0x02218344, 0x42 bytes, Thumb
 * func_ov003_0221833c @ 0x0221833c, 0x6 bytes, Thumb
 * func_ov003_02218330 @ 0x02218330, 0xa bytes, Thumb
 * func_ov003_02218210 @ 0x02218210, 0x120 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned int unk_60;
    unsigned int unk_64;
    char pad_68[0x8e - 0x68];
    unsigned short unk_8E;
    char pad_90[0x7f0 - 0x90];
    unsigned int unk_7F0;
    char pad_7F4[0x800 - 0x7f4];
    unsigned int unk_800;
    char pad_804[0x8f0 - 0x804];
    char unk_8F0;
    char pad_8F1[0xc84 - (0x8f0 + 1)];
    unsigned short unk_C84;
} BigStruct;

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    short unk_02;
} LocalBuf;

typedef struct {
    int a;
    int b;
    short c;
    unsigned char d;
    unsigned char cnt;
} UnkStruct_022184e8;

typedef struct {
    char pad_00[0x2d8];
    unsigned int unk_2D8;
    char pad_2DC[0x704 - 0x2d8 - 4];
    unsigned int unk_704;
} Stru_02218474;

struct UnkStruct_022183d8 {
    char pad_00[0x7f8];
    int unk_7F8;
};

struct UnkStruct_02218344 {
    char data[0x1c];
};

typedef struct {
    unsigned char pad_00[0xc];
    unsigned char byte0;
    unsigned char byte1;
} B_ov003_big;

typedef struct {
    unsigned char pad_00[0x7d4];
    unsigned char dbyte0;
    unsigned char dbyte1;
    unsigned char pad_7D6[0x7f8 - 0x7d6];
    int flagfield;
    unsigned char pad_7FC[0x800 - 0x7fc];
    int fieldBig;
    unsigned char pad_804[0x8f0 - 0x804];
    unsigned char unk_8F0[1];
} Self_ov003_big;

extern void func_ov003_02218664(void *a, void *b, void *c, void *d, void *e);
extern int func_02096614(unsigned char *a, int *b, int *c, int d, int e);
extern int func_ov003_022186cc(void *obj, unsigned char b, unsigned int v18, unsigned int v20, int shortval, int six,
                               int arg1);
extern void func_020109a0(void *, int b, int c, unsigned short d);
extern void func_0200fbc4(void *, int, int, int);
extern void func_02010f5c(int argument0);
extern void func_0200f888(Stru_02218474 *);
extern int func_02056f94(void *);
extern void func_02010d64(void *self);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e91c(void *);
extern void func_0200f268(void *obj, int value);
extern int func_0200e894(int, void *);
extern void *data_020ccf94;
extern int func_02073908(void *a, int b);
extern int func_ov003_022203ac(void);
extern void *func_020984e8(void);
extern int func_020b65c4(void);
extern int func_02099020(void *d, int a);
extern void *func_020b65b8(void);
extern int func_020b67e8(void *g);
extern void *func_0208602c(void);
extern int func_02086108(void *i, int a);
extern int func_020b29c0(void *p);
extern void func_020109fc(Self_ov003_big *self, int a, int b, int c);
extern int func_ov003_02220368(Self_ov003_big *self);

int func_ov003_022183f4(void *a, int b, int c);

void func_ov003_02218524(BigStruct *obj, int arg1)
{
    LocalBuf buf;
    int val;
    int val2;
    int val3;
    volatile int local_c;
    int val4;

    if ((obj->unk_7F0 - 0x38) <= 2) {
        obj->unk_C84 = (unsigned short) arg1;
        return;
    }

    func_ov003_02218664(&obj->unk_8F0, &buf, &val3, &val4, &buf.unk_02);

    local_c = obj->unk_60;

    if (func_02096614(&buf.unk_01, &val, &val2, -1, obj->unk_800) != 0) {
        obj->unk_5C = val;
        obj->unk_64 = val2;
    }

    obj->unk_8E = (unsigned short) buf.unk_02;
    func_ov003_022186cc(obj, buf.unk_00, val3, val4, buf.unk_02, 6, arg1);
}

void func_ov003_022184e8(void *p)
{
    UnkStruct_022184e8 *s = (UnkStruct_022184e8 *) ((char *) p + 0x7d4);
    unsigned char *q = &s->cnt;
    if (s->cnt != 0) {
        *q = (unsigned char) (s->cnt - 1);
        if (*q == 0) {
            func_020109a0(p, 0x33, 3, 0);
        }
    } else {
        func_0200fbc4(p, s->a, s->b, s->c);
    }
}

void func_ov003_02218474(Stru_02218474 *p)
{
    int v;

    func_02010f5c((int) p);

    if (p->unk_704 == 0x32) {
        v = (p->unk_2D8 << 4) >> 16;
        switch (v) {
            case 8:
            case 12:
            case 22:
            case 27:
            case 34:
                func_0200f888(p);
                break;
        }
    } else if (p->unk_704 == 0x33) {
        v = (p->unk_2D8 << 4) >> 16;
        switch (v) {
            case 9:
            case 17:
            case 26:
                func_0200f888(p);
                break;
        }
    }
}

void func_ov003_0221844c(void *arg0)
{
    if (func_02056f94((char *) arg0 + 0x2d0) == 0) {
        return;
    }
    func_ov003_022183f4(arg0, 6, -1);
}

void func_ov003_0221842c(void *r0)
{
    func_ov003_022184e8(r0);
    func_ov003_02218474((Stru_02218474 *) r0);
    func_02010d64(r0);
    func_ov003_0221844c(r0);
}

int func_ov003_022183f4(void *a, int b, int c)
{
    char buf[0x20];
    int ret;
    func_0200e92c(buf);
    func_0200e90c(buf, 0x3a, b, c);
    ret = func_0200e894((int) a, buf);
    func_0200e91c(buf);
    return ret;
}

void func_ov003_022183d8(struct UnkStruct_022183d8 *self, void *message, int previous)
{
    func_0200f268(self, 0);
    self->unk_7F8 = 0;
}

void func_ov003_022183cc(int a, int b)
{
    func_ov003_022183f4((void *) a, 6, b);
}

void func_ov003_022183c8(void *receiver) {}

int func_ov003_02218388(int p1, int p2, int p3)
{
    char local[0x1c];
    char *p;
    int ret;

    func_0200e92c(local);
    p = &local[0xc];
    func_0200e90c(local, 0x3b, p2, p3);
    p[0] = 0;
    p[1] = 0;
    ret = func_0200e894(p1, local);
    func_0200e91c(local);
    return ret;
}

int func_ov003_02218344(int a, int b, int c, int d, short e)
{
    struct UnkStruct_02218344 local;
    char *p;
    int result;

    func_0200e92c(&local);
    func_0200e90c(&local, 0x3b, d, e);
    p = &local.data[0xc];
    p[0] = (char) b;
    p[1] = (char) c;
    result = func_0200e894(a, &local);
    func_0200e91c(&local);
    return result;
}

void func_ov003_0221833c(u8 *p, int a, int b)
{
    p[0] = (u8) a;
    p[1] = (u8) b;
}

void func_ov003_02218330(u8 *p, u8 *a, u8 *b)
{
    *a = p[0];
    *b = p[1];
}

void func_ov003_02218210(Self_ov003_big *self, B_ov003_big *b, int previous)
{
    int local0;
    void *gv;
    int kind;
    int caseResult;
    void *dres, *gres, *ires;
    unsigned char *destp;
    unsigned char *bsub;

    func_0200f268((void *) self, 0);

    bsub = &b->byte0;
    destp = &self->dbyte0;
    kind = 0;
    gv = data_020ccf94;

    if (func_02073908(gv, self->fieldBig)) {
        local0 = func_ov003_022203ac();
    } else {
        local0 = bsub[0];
    }

    if (func_02073908(gv, self->fieldBig)) {
        dres = func_020984e8();
        if (func_020b65c4() != 0) {
            goto L_else;
        }
        if (dres == 0) {
            goto L_else;
        }
        if (func_02099020(dres, 0x23) == 0) {
            goto L_else;
        }
        gres = func_020b65b8();
        if (func_020b67e8(gres) != 0) {
            goto L_kind1;
        }
        if ((int) func_020b65b8() != 6) {
            goto L_else;
        }
    L_kind1:
        kind = 1;
        goto L_after;

    L_else:
        ires = func_0208602c();
        if (func_02086108(ires, 0) != 0) {
            kind = 2;
            goto L_after;
        }
        ires = func_0208602c();
        if (func_02086108(ires, 5) != 0) {
            kind = 3;
        }
    L_after:;
    } else {
        kind = bsub[1];
    }

    if (local0 != 0) {
        func_020109a0((void *) self, 0x34, 0, 0);
        caseResult = 0;
        self->flagfield = 1;
    } else {
        int lres = func_020b29c0((unsigned char *) self + 0x5c);
        caseResult = (unsigned char) lres;
        if ((unsigned int) caseResult <= 1) {
            func_020109a0((void *) self, 0x35, 0, 0);
        } else {
            func_020109fc(self, 0x36, 0, 0);
        }
        self->flagfield = 1;
    }

    destp[1] = (unsigned char) caseResult;
    destp[0] = (unsigned char) kind;
    func_ov003_0221833c((u8 *) ((unsigned char *) self + 0x8f0), local0, kind);

    self = (Self_ov003_big *) ((unsigned char *) self + 0x5c);
    func_ov003_02220368(self);
}
