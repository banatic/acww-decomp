/* scene_motion_kinds_2: 9 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02018a3c @ 0x02018a3c, 0x50 bytes, Thumb
 * func_02018990 @ 0x02018990, 0xac bytes, Thumb
 * func_02018934 @ 0x02018934, 0x5c bytes, Thumb
 * func_02018844 @ 0x02018844, 0xf0 bytes, Thumb
 * func_020187b8 @ 0x020187b8, 0x8c bytes, Thumb
 * func_0201875c @ 0x0201875c, 0x5c bytes, Thumb
 * func_0201873c @ 0x0201873c, 0x20 bytes, Thumb
 * func_02018714 @ 0x02018714, 0x28 bytes, Thumb
 * func_020186b0 @ 0x020186b0, 0x64 bytes, Thumb
 */

struct UnkStruct_02018a3c {
    unsigned char pad_00[0x98];
    unsigned char unk_98;
};

struct UnkStruct_02018a3c_2 {
    unsigned char pad_00[0x18c];
    unsigned int unk_18C;
    unsigned int unk_190;
};

struct UnkStruct_02018934 {
    unsigned char pad_00[0x190];          // 0x000
    unsigned int unk_190;                 // 0x190
    unsigned char pad_194[0x19c - 0x194]; // 0x194
    unsigned char unk_19C;                // 0x19c
};

typedef struct {
    unsigned int low : 12;
    unsigned int mid : 16;
    unsigned int high : 4;
} Bitfield;

typedef struct {
    char pad_00[0x28];
    int unk_28;
} CFake;

typedef struct {
    char pad_00[0x190];
    unsigned int unk_190;
    char pad_194[0x380];
    char unk_514;
} BFake;

extern int func_02019de8(struct UnkStruct_02018a3c *p0);
extern int func_02019de4(void *a);
extern void func_0201b1a4(void *a, void *b, int c, int d, unsigned short e);
extern void func_0201b044(void *a, void *b);
extern void func_0201afd4(void *a, void *b);
extern void func_0201b350(void *a, int b);
extern void func_02016764(void *a, void *b, unsigned int c, unsigned short d, unsigned int e, unsigned int f, unsigned short g,
                          int h);
extern void func_02019a18(void *a, unsigned int b, unsigned char c, unsigned short d, unsigned short e);
extern void func_02019af0(void *a, int b);
extern unsigned char data_021fbee8[];
extern int func_020164cc(char *p, int);
extern volatile unsigned short data_020c80f8;
extern unsigned int data_020c8198[];
extern void func_02012444(unsigned int, unsigned short, int);
extern int func_02057d58(unsigned char *, unsigned int, unsigned char, unsigned int, unsigned char *, unsigned int);
extern int func_02057d0c(int, unsigned char *);
extern int func_02095a28(void);
extern int func_0200442c(void *ptr, int v1, int v2, int v3);
extern int func_02057d34(void *);
extern int func_02057bd4(void);
extern int func_02057bf0(int);
extern int func_02057b90(int, void *);
extern int func_02057c20(int);
extern int func_ov004_0222bf50(void);

void func_02018a3c(struct UnkStruct_02018a3c *p0, struct UnkStruct_02018a3c_2 *p1)
{
    unsigned int a;
    unsigned int b;

    if (p0->unk_98 < 1) {
        return;
    }
    if (func_02019de8(p0) != 0) {
        return;
    }
    a = (p1->unk_190 << 4) >> 16;
    b = (p1->unk_18C << 4) >> 16;
    if ((int) a < (int) (b - 0x1000)) {
        return;
    }
    func_02019af0((void *) p0, 1);
}

int func_02018990(void *a, void *b)
{
    void *r4;

    r4 = (void *) func_02019de4(a);
    func_0201b1a4((char *) b + 0x350, b, 0, 0, (*(unsigned short *) &data_020c80f8));
    func_0201b044((char *) b + 0x350, (void *) data_021fbee8);
    func_0201afd4((char *) b + 0x350, (void *) data_021fbee8);
    func_0201b350((char *) b + 0x3aa, -2);
    func_02016764((char *) b + 0x334, b, *(unsigned int *) r4, *(unsigned short *) ((char *) r4 + 0x1c),
                  *((unsigned char *) r4 + 0x20), 0x1000, *(unsigned short *) ((char *) r4 + 0x1e), 0);
    *((unsigned char *) a + 4) = (unsigned char) (*(unsigned int *) ((char *) a + 0x1c));
    *((unsigned char *) a + 5) = (unsigned char) (*(unsigned int *) ((char *) a + 0x14));
    func_02019a18((char *) a + 6, *(unsigned int *) r4, *((unsigned char *) r4 + 0x20),
                  *(unsigned short *) ((char *) r4 + 0x1c), *(unsigned short *) ((char *) r4 + 0x1e));
    func_02019af0(a, 0);
    return 1;
}

void func_02018934(void *self, struct UnkStruct_02018934 *st)
{
    int result = 0;
    unsigned char idx;

    idx = st->unk_19C;

    switch (idx) {
        case 0:
        case 2:
            if (((st->unk_190 << 4) >> 16) == 0) {
                result = 1;
            }
            break;
        case 1:
        case 3:
            result = func_020164cc((char *) st + 0x334, (int) st);
            break;
        default:
            break;
    }

    if (result != 0) {
        func_02019af0(self, 1);
    }
}

int func_02018844(unsigned char *param0, unsigned char *param1)
{
    unsigned char *r4;
    unsigned short saved;
    unsigned int fieldval;

    r4 = (unsigned char *) func_02019de4((void *) param0);
    func_0201b1a4((void *) (param1 + 0x350), (void *) param1, 0, 0, *(unsigned short *) (r4 + 0x1c));
    func_0201b044((void *) (param1 + 0x350), ((int *) data_021fbee8));
    func_0201afd4((void *) (param1 + 0x350), ((int *) data_021fbee8));
    func_0201b350((void *) (param1 + 0x3aa), 0xfffffffe);
    saved = data_020c80f8;

    func_02016764((void *) (param1 + 0x334), (void *) param1, data_020c8198[*(unsigned int *) (r4 + 0x30)], data_020c80f8, 1,
                  0x1000, 0, 0);

    fieldval = *(unsigned int *) (param1 + 0x628);
    if (fieldval != 0) {
        func_02012444(fieldval, saved, 0);
    }

    func_0200442c((void *) (param1 + 0x514), 0x4f, 0x7f, 0);

    func_02057d58(r4 + 0x22, *(unsigned int *) (r4 + 0x24), *(unsigned char *) (r4 + 0x2c), *(unsigned int *) (r4 + 0x30),
                  param1, *(unsigned int *) (r4 + 0x28));

    func_02057d0c(1, param1);

    func_02019af0((void *) param0, 0);

    if (*(unsigned int *) (r4 + 0x30) == 1) {
        param0[0x98] = 4;
    } else {
        param0[0x98] = 0;
    }

    return 1;
}

void func_020187b8(char *param0, char *param1)
{
    if (func_020164cc((char *) (param1 + 0x334), (int) param1) != 0) {
        if (func_02095a28() != 0) {
            unsigned short v = data_020c80f8;
            func_02016764(param1 + 0x334, param1, 0x23, data_020c80f8, 0, 0x1000, 0, 0);
            if (*(unsigned int *) (param1 + 0x628) != 0) {
                func_02012444(*(unsigned int *) (param1 + 0x628), v, 0);
            }
            *(unsigned char *) (param0 + 0x98) = 1;
        }
    } else {
        if (((Bitfield *) (param1 + 0x190))->mid == 8) {
            func_0200442c(param1 + 0x514, 0x63, 0x7f, 0);
        }
    }
}

void func_0201875c(unsigned char *param0, unsigned char *param1)
{
    unsigned short v;
    int field;

    if (func_02057d34(param1) != 0) {
        return;
    }

    v = data_020c80f8;

    func_02016764(param1 + 0x334, param1, 0, data_020c80f8, 0, 0x1000, 0, 0);

    field = *(int *) (param1 + 0x628);
    if (field != 0) {
        func_02012444(field, v, 0);
    }

    param0[0x98] = 2;
}

void func_0201873c(unsigned char *p, int event)
{
    int t;

    t = func_02057bd4();
    if (t) {
        return;
    }
    func_02019af0((void *) p, 1);
    p[0x98] = 5;
}

void func_02018714(unsigned char *p, unsigned int *q)
{
    unsigned int val;

    val = q[0x64];
    if (((val << 4) >> 16) == 0x17) {
        func_02057d0c(2, (unsigned char *) ((int) q));
        p[0x98] = 4;
    }
}

void func_020186b0(void *a, void *b)
{
    if (!func_02057bf0(1)) {
        CFake *c;
        int res;

        c = (CFake *) func_02019de4(a);
        func_02057b90(9, b);
        res = func_02057c20(c->unk_28);
        if (res != 0 && func_ov004_0222bf50() != 0) {
            *((unsigned char *) a + 0x98) = 2;
        }
    } else {
        BFake *bp = (BFake *) b;

        if (((bp->unk_190 << 4) >> 16) == 8) {
            func_0200442c(&bp->unk_514, 99, 127, 0);
        }
    }
}
