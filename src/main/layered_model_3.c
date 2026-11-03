/* layered_model_3: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02054a98 @ 0x02054a98, 0x2 bytes, Thumb
 * func_02054a94 @ 0x02054a94, 0x2 bytes, Thumb
 * func_02054a64 @ 0x02054a64, 0x30 bytes, Thumb
 * func_02054a34 @ 0x02054a34, 0x30 bytes, Thumb
 * func_020549fc @ 0x020549fc, 0x38 bytes, Thumb
 * func_020549d8 @ 0x020549d8, 0x24 bytes, Thumb
 * func_02054988 @ 0x02054988, 0x50 bytes, Thumb
 * func_02054944 @ 0x02054944, 0x44 bytes, Thumb
 * func_0205490c @ 0x0205490c, 0x38 bytes, Thumb
 * func_020548cc @ 0x020548cc, 0x40 bytes, Thumb
 * func_02054860 @ 0x02054860, 0x6c bytes, Thumb
 * func_02054848 @ 0x02054848, 0x18 bytes, Thumb
 * func_02054828 @ 0x02054828, 0x1e bytes, Thumb
 * func_020547b0 @ 0x020547b0, 0x78 bytes, Thumb
 */

typedef struct {
    char pad_00[0x14c];
    unsigned int low;
    unsigned int high;
} Flags;

struct UnkStruct_02054988 {
    unsigned char arr[2];
};

struct UnkStruct_02054988_2 {
    struct UnkStruct_02054988 *inner;
};

struct BigStruct {
    unsigned char pad_00[0xb4];
    int unk_B4;
    unsigned char pad_B8[0x3c];
    int unk_F4;
};

typedef struct {
    unsigned char pad_00[0x5c];
    int unk_5C;
    unsigned char pad_60[0x94];
    int unk_F4;
} UnkStruct_020548cc;

typedef struct {
    char pad_00[0x04];
    unsigned short flags;        // 0x04
    char pad_06[0xf4 - 0x06];    // to 0xf4
    unsigned int *unk_F4;        // 0xf4
    char unk_F8;                 // 0xf8
    char pad_F9[0x100 - 0xf9];   // to 0x100
    unsigned int unk_100;        // 0x100
    char pad_104[0x110 - 0x104]; // to 0x110
    char unk_110;                // 0x110
    char pad_111[0x14c - 0x111]; // to 0x14c
    unsigned int unk_14C;        // 0x14c
    unsigned int unk_150;        // 0x150
} UnkStruct_02054860;

typedef struct UnkStruct_020547b0 {
    unsigned char pad_00[4];
    unsigned short flags;
    unsigned char pad_06[0x56];
    void *unk_5C;
    unsigned char pad_60[0x94];
    void *unk_F4;
    unsigned char unk_F8[0x18];
    unsigned char unk_110[0x10];
} UnkStruct_020547b0;

extern void func_02056aa0(void *addr, int arg);
extern int func_01ffcc10(struct BigStruct *a, struct UnkStruct_02054988_2 *b);
extern void func_02054a9c(struct BigStruct *a, int x);
extern void func_02054d80(struct BigStruct *a, struct UnkStruct_02054988_2 *b);
extern void func_02056b18(void *arg1, void *arg2);
extern void func_02054d14(void *p0, void *p1);
extern int func_02055140(void *a, int b);
extern int func_02056548(int a, void *b, int c);
extern int data_020dd030;
extern void func_02054cdc(void *p);
extern int func_02056e84(void *p);
extern void func_02054700(void *p);
extern void func_02056ffc(void *p);
extern void func_0205510c(void *, int);
extern void func_02054cac(int p1, int p2, int p3, int p4, int p5, unsigned int p6, unsigned int p7);
extern void func_02056e60(void *a, int b);
extern unsigned short func_020550b8(void *a, void *b);
extern void func_02056fcc(void *a, unsigned short b, void *c, int d, unsigned short e);
extern void NNS_G3dAnmObjInit(void *a, void *b, void *c, int d);

void func_02054a98(unsigned int object, unsigned int index) {}

void func_02054a94(unsigned int index, unsigned int item) {}

void func_02054a64(unsigned int *p, unsigned int bit)
{
    if (bit >= 32) {
        p[0x54] |= (1 << (bit - 32));
    } else {
        p[0x53] |= (1 << bit);
    }
}

void func_02054a34(unsigned int *p, unsigned int n)
{
    if (n >= 32) {
        *(unsigned int *) ((char *) p + 0x150) &= ~(1 << (n - 32));
    } else {
        *(unsigned int *) ((char *) p + 0x14c) &= ~(1 << n);
    }
}

int func_020549fc(Flags *flags, unsigned int index)
{
    if (index >= 32) {
        if (flags->high & (1 << (index - 32))) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (flags->low & (1 << index)) {
            return 1;
        } else {
            return 0;
        }
    }
}

void func_020549d8(void *self, int arg)
{
    if (*(int *) ((char *) self + 0x148) != 0) {
        func_02056aa0((char *) self + 0x110, arg);
    }
}

void func_02054988(struct BigStruct *a, struct UnkStruct_02054988_2 *b)
{
    if (func_01ffcc10(a, b) != 0) {
        return;
    }
    if (func_020549fc((Flags *) a, b->inner->arr[1]) != 0) {
        func_02054a9c(a, a->unk_F4);
        func_020549d8((void *) a, (int) b);
    } else {
        func_02054a9c(a, a->unk_B4);
        func_02054d80(a, b);
    }
}

void func_02054944(void *p0, void *p1)
{
    if ((*(int *) (*(void **) ((unsigned char *) p1 + 0xb4)) & 4) != 0) {
        *(int *) ((unsigned char *) (*(void **) ((unsigned char *) p1 + 0xb4)) + 0x4c) = 0;
        *(int *) ((unsigned char *) (*(void **) ((unsigned char *) p1 + 0xb4)) + 0x50) = 0;
        *(int *) ((unsigned char *) (*(void **) ((unsigned char *) p1 + 0xb4)) + 0x54) = 0;
    }
    if (*(int *) ((unsigned char *) p0 + 0x148) != 0) {
        func_02056b18((unsigned char *) p0 + 0x110, p1);
    }
}

void func_0205490c(void *arg0, void *arg1)
{
    int ret;
    unsigned char b;
    ret = func_01ffcc10((struct BigStruct *) arg0, (struct UnkStruct_02054988_2 *) arg1);
    if (ret != 0) {
        return;
    }
    b = ((unsigned char *) (*(void **) arg1))[1];
    if (func_020549fc((Flags *) arg0, (unsigned char) b) != 0) {
        func_02054944(arg0, arg1);
    } else {
        func_02054d14(arg0, arg1);
    }
}

int func_020548cc(UnkStruct_020548cc *a, int b)
{
    if (func_02055140(a, b) == 0) {
        return 0;
    }
    a->unk_F4 = func_02056548(a->unk_5C, &data_020dd030, b);
    if (a->unk_F4 != 0) {
        return 1;
    } else {
        return 0;
    }
}

void func_02054860(UnkStruct_02054860 *p)
{
    func_02054cdc(p);
    if (p->unk_14C != 0 || p->unk_150 != 0) {
        if (func_02056e84(&p->unk_110) != 0 && (p->flags & 0x4000) != 0) {
            func_02054700(p);
            p->flags &= ~0x4000;
        }
        func_02056ffc(&p->unk_F8);
        *p->unk_F4 = p->unk_100;
    }
}

void func_02054848(void *arg0, int argument1)
{
    void *r4;
    void *r1;

    r4 = arg0;
    func_0205510c(arg0, (int) argument1);
    r1 = *(void **) ((char *) r4 + 0xb4);
    func_02054a9c((struct BigStruct *) r4, (int) r1);
}

void func_02054828(int p1, int p2, int p3, int p4, int p5, unsigned short p6, unsigned short p7)
{
    func_02054cac(p1, p2, p3, p4, p5, p6, p7);
}

void func_020547b0(UnkStruct_020547b0 *s, void *p, int x, void *q, int z, unsigned short w, unsigned short v, int flag)
{
    func_02056e60(s->unk_110, x);
    if (v == 0) {
        v = func_020550b8(q, p);
    }
    func_02056fcc(s->unk_F8, v, q, z, w);
    NNS_G3dAnmObjInit(s->unk_F4, p, s->unk_5C, 0);
    if (flag) {
        s->flags |= 0x4000;
    } else {
        s->flags &= ~0x4000;
    }
}
