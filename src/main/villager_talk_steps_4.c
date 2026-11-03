/* villager_talk_steps_4: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02023d0c @ 0x02023d0c, 0x7c bytes, Thumb
 * func_02023ca8 @ 0x02023ca8, 0x64 bytes, Thumb
 * func_02023c44 @ 0x02023c44, 0x64 bytes, Thumb
 * func_02023be0 @ 0x02023be0, 0x64 bytes, Thumb
 * func_02023b70 @ 0x02023b70, 0x70 bytes, Thumb
 * func_02023ac0 @ 0x02023ac0, 0xb0 bytes, Thumb
 * func_02023a54 @ 0x02023a54, 0x6c bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02023d0c {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_02023d0c;

typedef struct UnkStruct_02023d0c_2 {
    char pad_00[0x100];
    UnkStruct_02023d0c *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02023d0c_2;

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_02023d0c_3;

struct UnkStruct_02023ca8 {
    char pad_00[0x830];
    void *arg;
};

struct UnkStruct_02023ca8_2 {
    char pad_00[0x100];
    struct UnkStruct_02023ca8 *inner;
    char buffer[30];
    unsigned char unk_122;
};

struct GlobalCtx {
    int word;
    unsigned char byte;
};

struct UnkStruct_02023ca8_3 {
    void *ptr;
    unsigned char byte;
};

typedef struct UnkStruct_02023c44_3 UnkStruct_02023c44_3;

typedef struct UnkStruct_02023c44 UnkStruct_02023c44;

typedef struct UnkStruct_02023c44_2 UnkStruct_02023c44_2;

typedef struct UnkStruct_02023c44_4 UnkStruct_02023c44_4;

struct UnkStruct_02023c44_3 {
    unsigned char pad_00[0x830];
    void *data;
};

struct UnkStruct_02023c44 {
    unsigned char pad_00[0x100];
    UnkStruct_02023c44_3 *sub;
    char buf[0x1e];
    unsigned char flag;
};

struct UnkStruct_02023c44_2 {
    int word;
    unsigned char byte;
};

struct UnkStruct_02023c44_4 {
    char *text;
    unsigned char flag;
};

struct UnkStruct_02023be0 {
    void *unk_00;
    unsigned char unk_04;
};

typedef struct {
    int n;
    unsigned char b;
} UnkStruct_02023b70;

typedef void (*Fn)(void *self, UnkStruct_02023b70 *out);

typedef struct {
    int fn;
    int adj;
} Pmf;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
} UnkStruct_02023b70_2;

typedef struct UnkStruct_02023ac0_2 {
    u8 pad_00[0x830];
    void *unk_830;
} UnkStruct_02023ac0_2;

typedef struct UnkStruct_02023ac0 {
    u8 pad_00[0x100];              // 0x000
    UnkStruct_02023ac0_2 *unk_100; // 0x100
    u8 unk_104[0x1e];              // 0x104
    u8 unk_122;                    // 0x122
    u8 pad_123[0x79];              // 0x123 - 0x19b
    u16 unk_19C;                   // 0x19c
} UnkStruct_02023ac0;

typedef struct UnkStruct_02023ac0_3 {
    void *ptr; // 0x00
    u8 byte;   // 0x04
} UnkStruct_02023ac0_3;

typedef struct {
    int a;
    int b;
} Pair;

extern int data_020c8c20;
extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern int func_0200368c(char *a, int n, int g, int v);
extern int func_0202d9c4(UnkStruct_02023d0c_2 *self);
extern int func_0209bc40(int x);
extern struct GlobalCtx data_020c8cd8;
extern UnkStruct_02023c44_2 data_020c8c18;
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern struct {
    int a;
    unsigned char b;
} data_020c8c08;
extern int data_021c2f74;
extern int data_021c2fa4;
extern int func_02099fe8(void);
extern void func_0202da88(UnkStruct_02023b70_2 *self, void *tbl);
extern void func_0206844c(int a, void *b, int c);
extern int func_020984e8(void);
extern void func_0202d5e4(void *buf, int val);
extern void func_02015de4(void *a, void *b, int c, int d);
extern struct {
    u32 a;
    u8 b;
} data_020c8c00;
extern int func_02099734(int);
extern int func_02098eb8(int);
extern int func_020154b4(void *, void *, int, int, int);
extern int func_02098f0c(int, void *, int, int);
extern int func_020996ac(int);
extern int func_0203cd2c(int, void *, int, int);
extern Pair data_020d90e0;
extern void func_0202dbf0(void *, Pair);

void func_02023d0c(UnkStruct_02023d0c_2 *self, UnkStruct_02023d0c_3 *out)
{
    func_0200368c(self->unk_104, 0x1e, data_020c8c20, func_020036e8(func_0208150c(self->unk_100->unk_830)));
    switch (func_0209bc40(func_0202d9c4(self))) {
        case 0xe:
            self->unk_122 = 0xb;
            break;
        case 0x10:
            self->unk_122 = 0xd;
            break;
        default:
            self->unk_122 = 0xe;
            break;
    }
    out->p = self->unk_104;
    out->b = self->unk_122;
}

void func_02023ca8(struct UnkStruct_02023ca8_2 *self, struct UnkStruct_02023ca8_3 *out)
{
    int a, b, c;

    a = func_020036e8(func_0208150c((int) self->inner->arg));
    b = data_020c8cd8.word;
    c = data_020c8cd8.byte;

    func_0202da38(self, (void *) self->buffer, (void *) (&self->unk_122), 0x1e, a, b, c, 0, 0);

    out->ptr = self->buffer;
    out->byte = self->unk_122;
}

void func_02023c44(UnkStruct_02023c44 *a, UnkStruct_02023c44_4 *out)
{
    int x;
    int p6;
    int p7;

    x = func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c((int) a->sub->data)));
    p6 = data_020c8c18.word;
    p7 = data_020c8c18.byte;

    func_0202da38((void *) a, a->buf, &a->flag, 0x1e, x, p6, p7, 0, 0);

    out->text = a->buf;
    out->flag = a->flag;
}

void func_02023be0(void *arg0, struct UnkStruct_02023be0 *out)
{
    func_0202da38(arg0, (char *) arg0 + 0x104, (char *) arg0 + 0x122, 30,
                  func_020036e8(func_0208150c(*(int *) ((char *) *(void **) ((char *) arg0 + 0x100) + 0x830))),
                  data_020c8c08.a, data_020c8c08.b, 0, 0);
    out->unk_00 = (char *) arg0 + 0x104;
    out->unk_04 = *(unsigned char *) ((char *) arg0 + 0x122);
}

void func_02023b70(UnkStruct_02023b70_2 *self)
{
    unsigned char arg;
    UnkStruct_02023b70 out;
    Fn f;

    if (func_02099fe8() != -1) {
        func_0202da88(self, &data_021c2f74);
    } else {
        func_0202da88(self, &data_021c2fa4);
    }
    if (((volatile Pmf *) &self->pmf)->fn != 0) {
        volatile Pmf *pm;
        int adj;
        char *t;

        pm = (volatile Pmf *) &self->pmf;
        adj = pm->adj;
        t = (char *) self + (adj >> 1);
        if (adj & 1) {
            f = (Fn) * (int *) (*(char **) t + pm->fn);
        } else {
            f = (Fn) pm->fn;
        }
        f(t, &out);
    }
    arg = out.b;
    func_0206844c(self->unk_40, &arg, out.n);
}

void func_02023ac0(UnkStruct_02023ac0 *self, UnkStruct_02023ac0_3 *out)
{
    u16 buf[2];
    int ret;

    func_0202d5e4(buf, func_020984e8());
    self->unk_19C = buf[0];

    if (self->unk_19C == 0xFFF1) {
        func_0202d5e4(buf + 1, 0);
        self->unk_19C = buf[1];
    }

    if (self->unk_19C != 0xFFF1) {
        func_02015de4(self, &self->unk_19C, 1, 7);
    }

    ret = func_020036e8((int) ((unsigned char *) (unsigned int) func_0208150c((int) self->unk_100->unk_830)));

    func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, ret, data_020c8c00.a, data_020c8c00.b, 0, 0);

    out->ptr = self->unk_104;
    out->byte = self->unk_122;
}

void func_02023a54(void *obj)
{
    int a;
    int b;
    int c;
    int d;

    a = func_020984e8();
    b = func_02099734(a);
    c = func_02098eb8(b);
    if (c == -1) {
        c = 0;
    }
    func_020154b4(obj, (char *) obj + 0x19c, 0, 5, 0);
    func_02098f0c(b, (char *) obj + 0x19c, c, 0);
    d = func_020996ac(a);
    func_0203cd2c(d, (char *) obj + 0x19c, 0, 1);
    func_0202dbf0(obj, data_020d90e0);
}
