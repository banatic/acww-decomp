/* effect_kinds_8: 47 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02093d20 @ 0x02093d20, 0x28 bytes, Thumb
 * func_02093cac @ 0x02093cac, 0x74 bytes, Thumb
 * func_02093c9c @ 0x02093c9c, 0x10 bytes, Thumb
 * func_02093c94 @ 0x02093c94, 0x8 bytes, Thumb
 * func_02093c70 @ 0x02093c70, 0x24 bytes, Thumb
 * func_02093bf8 @ 0x02093bf8, 0x78 bytes, Thumb
 * func_02093be8 @ 0x02093be8, 0x10 bytes, Thumb
 * func_02093bd8 @ 0x02093bd8, 0x10 bytes, Thumb
 * func_02093bc0 @ 0x02093bc0, 0x18 bytes, Thumb
 * func_02093b48 @ 0x02093b48, 0x78 bytes, Thumb
 * func_02093b38 @ 0x02093b38, 0x10 bytes, Thumb
 * func_02093b28 @ 0x02093b28, 0x10 bytes, Thumb
 * func_02093ab0 @ 0x02093ab0, 0x78 bytes, Thumb
 * func_02093a98 @ 0x02093a98, 0x18 bytes, Thumb
 * func_02093a88 @ 0x02093a88, 0x10 bytes, Thumb
 * func_02093a78 @ 0x02093a78, 0x10 bytes, Thumb
 * func_02093a50 @ 0x02093a50, 0x28 bytes, Thumb
 * func_02093a38 @ 0x02093a38, 0x18 bytes, Thumb
 * func_02093a28 @ 0x02093a28, 0x10 bytes, Thumb
 * func_02093a18 @ 0x02093a18, 0x10 bytes, Thumb
 * func_020939f0 @ 0x020939f0, 0x28 bytes, Thumb
 * func_020939d8 @ 0x020939d8, 0x18 bytes, Thumb
 * func_020939c8 @ 0x020939c8, 0x10 bytes, Thumb
 * func_020939b8 @ 0x020939b8, 0x10 bytes, Thumb
 * func_02093990 @ 0x02093990, 0x28 bytes, Thumb
 * func_02093974 @ 0x02093974, 0x1c bytes, Thumb
 * func_0209394c @ 0x0209394c, 0x28 bytes, Thumb
 * func_02093930 @ 0x02093930, 0x1c bytes, Thumb
 * func_02093908 @ 0x02093908, 0x28 bytes, Thumb
 * func_020938ec @ 0x020938ec, 0x1c bytes, Thumb
 * func_020938c4 @ 0x020938c4, 0x28 bytes, Thumb
 * func_020938a8 @ 0x020938a8, 0x1c bytes, Thumb
 * func_02093880 @ 0x02093880, 0x28 bytes, Thumb
 * func_02093864 @ 0x02093864, 0x1c bytes, Thumb
 * func_0209383c @ 0x0209383c, 0x28 bytes, Thumb
 * func_02093820 @ 0x02093820, 0x1c bytes, Thumb
 * func_020937f8 @ 0x020937f8, 0x28 bytes, Thumb
 * func_020937d4 @ 0x020937d4, 0x24 bytes, Thumb
 * func_02093714 @ 0x02093714, 0xc0 bytes, Thumb
 * func_02093704 @ 0x02093704, 0x10 bytes, Thumb
 * func_020936bc @ 0x020936bc, 0x48 bytes, Thumb
 * func_020936ac @ 0x020936ac, 0x10 bytes, Thumb
 * func_02093678 @ 0x02093678, 0x34 bytes, Thumb
 * func_02093628 @ 0x02093628, 0x50 bytes, Thumb
 * func_020935fc @ 0x020935fc, 0x2c bytes, Thumb
 * func_020935d4 @ 0x020935d4, 0x28 bytes, Thumb
 * func_020935c4 @ 0x020935c4, 0x10 bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char pad_00[0x39c];
    unsigned short unk_39C;
} Cfg;

typedef struct UnkStruct_02093a38 UnkStruct_02093a38;

struct UnkStruct_02093a38 {
    char pad_00[0x50];
    unsigned int unk_50;
};

typedef struct UnkStruct_02093a38_2 UnkStruct_02093a38_2;

struct UnkStruct_02093a38_2 {
    char pad_00[0xc];
    UnkStruct_02093a38 *unk_0C;
};

struct UnkStructB {
    unsigned char pad_00[0x54];
    unsigned int unk_54;
};

struct UnkStructA {
    unsigned char pad_00[0xC];
    struct UnkStructB *unk_0C;
};

struct func_02093930_inner {
    char pad_00[0x54];
    unsigned int value;
};

struct func_02093930_outer {
    char pad_00[0xC];
    struct func_02093930_inner *inner;
};

struct UnkStruct_020938ec {
    char pad_00[0x54];
    unsigned int value;
};

struct UnkStruct_020938ec_2 {
    char pad_00[0xc];
    struct UnkStruct_020938ec *inner;
};

typedef struct {
    char pad_00[12];
    int *ptr;
} ArgType;

typedef struct UnkStruct_02093864 {
    char unk_00[0x54];
    unsigned int unk_54;
} UnkStruct_02093864;

typedef struct UnkStruct_02093864_2 {
    char unk_00[0xc];
    UnkStruct_02093864 *unk_0C;
} UnkStruct_02093864_2;

struct UnkStruct_02093820 {
    unsigned char pad_00[0x54];
    int unk_54;
};

struct UnkStruct_02093820_2 {
    unsigned char pad_00[0xc];
    struct UnkStruct_02093820 *unk_0C;
};

typedef struct {
    unsigned char pad_00[0x34];
    int type;
    unsigned char pad_38[0xc];
} UnkStruct_02093714;

struct Src {
    u32 a;
    u32 b;
    u32 c;
    s16 d;
};

struct UnkStruct_02093678 {
    u32 pad_00;
    u32 b;
    u32 c;
    u32 d;
    u32 e;
    u32 unk_14;
    u32 g;
    u16 h;
    s16 i;
    u16 j;
};

typedef struct Node Node;

struct Node {
    Node *next;               // 0x00
    unsigned char pad0[0x20]; // 0x04 - 0x23
    unsigned short unk_24;    // 0x24
    unsigned short unk_26;    // 0x26
};

typedef struct UnkStruct_020935fc {
    unsigned char pad0[0x8]; // 0x00 - 0x07
    Node *head;              // 0x08
} UnkStruct_020935fc;

typedef struct UnkStruct_020935fc_2 {
    unsigned char pad0[0xC];   // 0x00 - 0x0B
    UnkStruct_020935fc *inner; // 0x0C
} UnkStruct_020935fc_2;

extern int func_02094b58(int, int, int, int, int, int);
extern unsigned char data_020e29ac[];
extern Cfg data_021d52d8;
extern int data_021d5658;
extern int data_020e288c;
extern void func_02091494(void *ctx, int hw, int a0, int a1, int a2, int a3, int minus1);
extern int func_02090ac4(int kind, int a1, int a2, void *tbl);
extern void func_020914dc(void *ctx);
extern void func_02094e04(int a, int b);
extern void func_02094ef4(void *);
extern int func_020948b8(int a, int b, int *c, int d, int e, int f, int g, int h, int i);
extern int data_020e29dc[];
extern int data_020e28ac;
extern int data_020e2884;
extern int func_02094cf8(int kind, int a0, int a1, int a2, int a3, void *tbl);
extern int data_020e291c;
extern int data_020e28bc;
extern int data_020e2928;
extern int data_020e2824;
extern void func_02094bc0(void *);
extern void func_02094260(unsigned int *object, unsigned int value);
extern int func_0209418c(int, int, int, int, void *, void *, void (*)(void *));
extern unsigned char data_020e287c[];
extern unsigned char data_020e2784[];
extern char data_020e282c[];
extern char data_020e27c4[];
extern char data_020e28fc;
extern char data_020e279c;
extern void func_02094c38(void *, int, int);
extern unsigned char data_020e283c[];
extern unsigned char data_020e2844[];
extern unsigned char data_020e28b4[];
extern unsigned char data_020e2854[];
extern unsigned char data_020e27ec[];
extern unsigned char data_020e27e4[];
extern int func_02034270(void *, void *, int, int);
extern void func_0203423c(void *);
extern int func_020ba4e4(void);
extern int func_020b6598(void);
extern unsigned char data_020e54a8;
extern int data_020d17c8;
extern void func_02094d48(int, int, int);
extern unsigned char data_020e27cc[];
extern int data_020d17d4;
extern int func_02094840(int, int, int, int, int, void (*)(void *));
extern int data_020e2964;
extern int func_02094bcc(void *arg, int a, int b);
extern unsigned char data_020e2a64[];
extern char data_020d1750;

void func_02093d20(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e29ac;
    func_02094b58(0x3c, r0, r1, r2, sp[0], sp[1]);
}

int func_02093cac(int a0, int a1, int a2, int a3)
{
    int ret;
    Cfg *cfg;

    cfg = &data_021d52d8;
    ret = 3;
    if (func_02094cf8(0x46, a0, a1, a2, a3, 0) < 3) {
        func_02091494(&data_021d5658, cfg->unk_39C, a0, a1, a2, a3, -1);
        if (func_02090ac4(0x5e, a1, a2, &data_020e288c) != 0) {
            ret = 2;
        }
    }
    func_020914dc(&data_021d5658);
    return ret;
}

void func_02093c9c(int a)
{
    func_02094e04(a, 0x1ccd);
}

void func_02093c94(void *argument0)
{
    func_02094ef4((void *) argument0);
}

void func_02093c70(int a)
{
    func_020948b8(a, 0x5f, data_020e29dc, -1, 0, -1, 0, -1, 0);
}

int func_02093bf8(int a0, int a1, int a2, int a3)
{
    int ret;
    Cfg *cfg;

    cfg = &data_021d52d8;
    ret = 3;
    if (func_02094cf8(0x47, a0, a1, a2, a3, &data_020e28ac) < 3) {
        func_02091494(&data_021d5658, cfg->unk_39C, a0, a1, a2, a3, -1);
        if (func_02090ac4(0x75, a1, a2, &data_020e2884) != 0) {
            ret = 2;
        }
    }
    func_020914dc(&data_021d5658);
    return ret;
}

void func_02093be8(void *ptr)
{
    func_02094e04((int) ptr, 0x1800);
}

void func_02093bd8(int a)
{
    func_02094e04(a, 0x1333);
}

void func_02093bc0(void *arg0)
{
    unsigned int *ptr;
    void *r4 = arg0;

    func_02094bc0((void *) ((int) arg0));
    ptr = *(unsigned int **) ((char *) r4 + 0xc);
    *(unsigned int *) ((char *) ptr + 0x54) = 0x1333;
}

int func_02093b48(int a0, int a1, int a2, int a3)
{
    int ret;
    Cfg *cfg;

    cfg = &data_021d52d8;
    ret = 3;
    if (func_02094cf8(0x48, a0, a1, a2, a3, &data_020e291c) < 3) {
        func_02091494(&data_021d5658, cfg->unk_39C, a0, a1, a2, a3, -1);
        if (func_02090ac4(0x75, a1, a2, &data_020e28bc) != 0) {
            ret = 2;
        }
    }
    func_020914dc(&data_021d5658);
    return ret;
}

void func_02093b38(int a)
{
    func_02094e04(a, 0x2000);
}

void func_02093b28(int a)
{
    func_02094e04(a, 0x199a);
}

int func_02093ab0(int a0, int a1, int a2, int a3)
{
    int ret;
    Cfg *cfg;

    cfg = &data_021d52d8;
    ret = 3;
    if (func_02094cf8(0x49, a0, a1, a2, a3, &data_020e2928) < 3) {
        func_02091494(&data_021d5658, cfg->unk_39C, a0, a1, a2, a3, -1);
        if (func_02090ac4(0x75, a1, a2, &data_020e2824) != 0) {
            ret = 2;
        }
    }
    func_020914dc(&data_021d5658);
    return ret;
}

void func_02093a98(void *r0)
{
    void *r4;
    unsigned int r1;
    unsigned int *r0_2;

    r4 = r0;
    func_02094bc0(r4);
    r1 = 0x800;
    r0_2 = *(unsigned int **) ((char *) r4 + 0xc);
    r0_2[0x14] = r1;
}

void func_02093a88(int a)
{
    func_02094e04(a, 0x119a);
}

void func_02093a78(void *a)
{
    func_02094260((unsigned int *) a, 0xccd);
}

void func_02093a50(int a, int b, int c, int d)
{
    func_0209418c(a, b, c, d, &data_020e287c, &data_020e2784, func_02093a78);
}

void func_02093a38(UnkStruct_02093a38_2 *a)
{
    func_02094bc0((void *) a);
    a->unk_0C->unk_50 = 0x99a;
}

void func_02093a28(int a)
{
    func_02094e04(a, 0x14cd);
}

void func_02093a18(void *a)
{
    func_02094260((unsigned int *) a, 0x119a);
}

int func_020939f0(int a, int b, int c, int d)
{
    return func_0209418c(a, b, c, d, data_020e282c, data_020e27c4, func_02093a18);
}

void func_020939d8(void *param1)
{
    void *r4;
    unsigned int r0;
    unsigned int r1;

    r4 = param1;
    func_02094bc0(r4);
    r1 = 0x00000c00;
    r0 = *(unsigned int *) ((char *) r4 + 0xc);
    *(unsigned int *) ((char *) r0 + 0x50) = r1;
}

void func_020939c8(int a)
{
    func_02094e04(a, 0x1ccd);
}

void func_020939b8(void *a)
{
    func_02094260((unsigned int *) a, 0x14cd);
}

int func_02093990(int a, int b, int c, int d)
{
    return func_0209418c(a, b, c, d, &data_020e28fc, &data_020e279c, func_020939b8);
}

void func_02093974(struct UnkStructA *a)
{
    struct UnkStructB *b;
    unsigned int val;
    func_02094c38(a, 0, 0);
    val = 0x4CD;
    b = a->unk_0C;
    b->unk_54 = val;
}

void func_0209394c(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e283c;
    func_02094b58(0x73, r0, r1, r2, sp[0], sp[1]);
}

void func_02093930(struct func_02093930_outer *a)
{
    int zero = 0;
    func_02094c38((void *) a, zero, zero);
    a->inner->value = 0x666;
}

void func_02093908(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2844;
    func_02094b58(0x73, r0, r1, r2, sp[0], sp[1]);
}

void func_020938ec(struct UnkStruct_020938ec_2 *arg)
{
    int zero = 0;
    func_02094c38(arg, zero, zero);
    arg->inner->value = 0x800;
}

void func_020938c4(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e28b4;
    func_02094b58(0x73, r0, r1, r2, sp[0], sp[1]);
}

void func_020938a8(ArgType *arg)
{
    int zero = 0;
    func_02094c38(arg, zero, zero);
    arg->ptr[21] = 0x99a;
}

int func_02093880(int a, int b, int c, int d, int e)
{
    unsigned int local0;
    unsigned int local1;

    local0 = d;
    local1 = (unsigned int) data_020e2854;
    return func_02094b58(0x73, a, b, c, local0, local1);
}

void func_02093864(UnkStruct_02093864_2 *p)
{
    func_02094c38(p, 0, 0);
    p->unk_0C->unk_54 = 0xb33;
}

void func_0209383c(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e27ec;
    func_02094b58(0x73, r0, r1, r2, sp[0], sp[1]);
}

void func_02093820(struct UnkStruct_02093820_2 *outer)
{
    func_02094c38((void *) outer, 0, 0);
    outer->unk_0C->unk_54 = 0xccd;
}

void func_020937f8(int r0, int r1, int r2, int r3)
{
    int r6 = r0;
    int r5 = r1;
    int r4 = r2;
    int sp0 = r3;
    int sp4 = (unsigned int) data_020e27e4;

    func_02094b58(0x73, r6, r5, r4, sp0, sp4);
}

int func_020937d4(int a, int b, int c, int d)
{
    return func_02094b58(0x73, a, b, c, d, 0);
}

int func_02093714(void *a, void *b, int arg_c, void *d)
{
    int c = arg_c;
    int result;
    UnkStruct_02093714 local;
    int type;
    unsigned int cond;

    func_02034270(&local, b, 0, 0);
    type = local.type;
    result = 3;
    cond = (data_020e54a8 == 1) ? 1 : 0;

    if (cond > 0) {
        if (type == 9 || type == 3) {
            result = func_02094cf8(0x4b, (int) a, (int) b, c, (int) d, 0);
        }
    } else {
        if (type == 0x16 || func_020ba4e4() == 1) {
            result = func_02094cf8(0x4d, (int) a, (int) b, c, (int) d, 0);
        } else if (type == 3 && func_020b6598() != 0) {
            result = func_02094cf8(0x4e, (int) a, (int) b, c, (int) d, 0);
        } else {
            result = func_02094cf8((type == 0x13) ? 0x4c : 0x4b, (int) a, (int) b, c, (int) d, 0);
        }
    }

    func_0203423c(&local);
    return result;
}

void func_02093704(int p0)
{
    func_02094d48(p0, 0, (int) &data_020d17c8);
}

int func_020936bc(int a, int b, int c, int d)
{
    struct {
        unsigned char pad[52];
        unsigned int field;
        unsigned char pad2[12];
    } local;
    int code;
    int result;

    func_02034270(&local, (void *) b, 0, 0);
    if (local.field == 0x13) {
        code = 0x6f;
    } else {
        code = 0x6e;
    }
    result = func_02094cf8(code, a, b, c, d, data_020e27cc);
    func_0203423c(&local);
    return result;
}

void func_020936ac(int arg0)
{
    func_02094d48(arg0, 0, (int) (&data_020d17d4));
}

void func_02093678(struct UnkStruct_02093678 *self)
{
    u32 *src;
    u32 *p;
    u32 *q;

    src = (u32 *) ((struct Src *) &data_021d5658);
    p = &self->b;
    self->b = src[0];
    p[1] = src[1];
    p[2] = src[2];

    q = &self->e;
    self->e = 0x1000;
    q[1] = 0x1000;
    q[2] = 0x1000;

    self->h = 0;
    self->i = (s16) ((s16 *) src)[6];
    self->j = 0;
}

int func_02093628(int p0, int p1, int p2, int p3)
{
    int result = 3;
    if (func_02094cf8(0x59, p0, p1, p2, p3, (void *) ((int) &data_020e2964)) < 3) {
        func_02094840(3, p0, p1, p2, p3, (void (*)(void *)) func_02093678);
        result = 1;
    }
    return result;
}

int func_020935fc(UnkStruct_020935fc_2 *arg)
{
    Node *node;
    if (func_02094bcc(arg, 0, 0) == 0) {
        node = arg->inner->head;
        while (node) {
            node->unk_26 = node->unk_24;
            node = node->next;
        }
        return 0;
    }
    return 1;
}

void func_020935d4(int a, int b, int c, int d)
{
    int sp[2];
    sp[0] = d;
    sp[1] = (unsigned int) data_020e2a64;
    func_02094b58(0x5a, a, b, c, sp[0], sp[1]);
}

void func_020935c4(int a)
{
    func_02094c38((void *) a, 0, (int) (&data_020d1750));
}
