/* villager_talk: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201d4d8 @ 0x0201d4d8, 0x3c bytes, Thumb
 * func_0201d448 @ 0x0201d448, 0x90 bytes, Thumb
 * func_0201d430 @ 0x0201d430, 0x16 bytes, Thumb
 * func_0201d418 @ 0x0201d418, 0x16 bytes, Thumb
 * func_0201d3ec @ 0x0201d3ec, 0x2c bytes, Thumb
 * func_0201d398 @ 0x0201d398, 0x54 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
    unsigned char pad_44[0x124 - 0x40 - 4];
    unsigned short unk_124;
    unsigned char pad_126[0x1a0 - 0x124 - 2];
    unsigned int unk_1A0;
} UnkStruct_0201d4d8;

typedef struct {
    unsigned char pad_00[0x100];
    void *unk_100;
    unsigned char pad_104[0x98];
    unsigned short unk_19C;
    unsigned char unk_19E;
} TStruct;

struct UnkStruct_0201d3ec {
    int a;
    int b;
};

extern void func_02027170(unsigned short *out, unsigned int input);
extern int func_02015330(void *obj, unsigned short *field, int a, int b, int c);
extern void func_02068440(void *arg);
extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098eb8(int object);
extern int func_02098f0c(int, void *, int, int);
extern int func_020996ac(int);
extern int func_0203cd2c(int, void *, int, int);
extern int func_0207de70(void *, void *);
extern int func_020154b4(void *, void *, int, int, int);
extern void func_0203d480(int);
extern void func_0203d394(void);
extern struct UnkStruct_0201d3ec data_020d8e60;
extern void func_020157c8(void *, int, int);
extern int func_02015828(void *, int);
extern void func_0202dbf0(void *, struct UnkStruct_0201d3ec);
extern unsigned char *func_020992e4(void *p);
extern unsigned char func_02082274(unsigned char a, unsigned char b);
extern void func_02015ed0(void *p, unsigned char b, int c);
extern void func_02015ea0(void *p, unsigned char b, int c);
extern int func_02015dd4(void *p, int a, void *b, void *c, const void *end);
extern char data_020d9f48;

void func_0201d4d8(UnkStruct_0201d4d8 *self)
{
    unsigned short value;

    func_02027170(&value, self->unk_1A0);
    self->unk_124 = value;
    func_02015330(self, &self->unk_124, 0, 5, 0);
    func_02068440(self->unk_40);
}

int func_0201d448(TStruct *base)
{
    int r4, r6, r2;
    void *p, *q;

    if (base->unk_19C == 0xfff1) {
        goto fail;
    }

    r4 = func_020984e8();
    r6 = func_02099734(r4);
    r2 = func_02098eb8((int) r6);
    if (r2 < 0) {
        goto fail;
    }

    func_02098f0c(r6, &base->unk_19C, r2, 0);
    func_0203cd2c(func_020996ac(r4), &base->unk_19C, 0, 1);

    if (base->unk_19E == 1) {
        p = base->unk_100;
        q = *(void **) ((char *) p + 0x830);
        func_0207de70(q, &base->unk_19C);
    }

    func_020154b4(base, &base->unk_19C, 0, 5, 0);
    return 1;

fail:
    return 0;
}

int func_0201d430(void)
{
    func_0203d480(1);
    func_0203d394();
    return 1;
}

int func_0201d418(void)
{
    (func_0203d480(0), func_0203d394());
    return 1;
}

int func_0201d3ec(void *param)
{
    func_020157c8(param, 0x32, 0);
    func_02015828(param, 2);
    func_0202dbf0(param, data_020d8e60);
    return 1;
}

void func_0201d398(void *arg0)
{
    unsigned char *q;
    unsigned char x;
    unsigned char bytes[2];

    q = func_020992e4((void *) func_020984e8());
    x = func_02082274(q[1], q[0]);
    func_02015ed0(arg0, q[1], 0);
    func_02015ea0(arg0, q[0], 1);
    bytes[0] = x;
    bytes[1] = 0;
    func_02015dd4(arg0, 2, bytes, &data_020d9f48, bytes + 1);
}
