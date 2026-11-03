/* town_day: 17 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204695c @ 0x0204695c, 0x98 bytes, Thumb
 * func_02046904 @ 0x02046904, 0x58 bytes, Thumb
 * func_02046830 @ 0x02046830, 0xd4 bytes, Thumb
 * func_020467cc @ 0x020467cc, 0x64 bytes, Thumb
 * func_020467ac @ 0x020467ac, 0x20 bytes, Thumb
 * func_0204678c @ 0x0204678c, 0x20 bytes, Thumb
 * func_02046784 @ 0x02046784, 0x8 bytes, Thumb
 * func_0204677c @ 0x0204677c, 0x8 bytes, Thumb
 * func_02046730 @ 0x02046730, 0x4c bytes, Thumb
 * func_020466e0 @ 0x020466e0, 0x50 bytes, Thumb
 * func_020466d8 @ 0x020466d8, 0x8 bytes, Thumb
 * func_020466a0 @ 0x020466a0, 0x38 bytes, Thumb
 * func_02046680 @ 0x02046680, 0x1e bytes, Thumb
 * func_02046650 @ 0x02046650, 0x30 bytes, Thumb
 * func_02046640 @ 0x02046640, 0x10 bytes, Thumb
 * func_02046620 @ 0x02046620, 0x20 bytes, Thumb
 * func_02046600 @ 0x02046600, 0x20 bytes, Thumb
 */

struct UnkStruct_0204695c {
    int pad_00;
    int unk_04;
};

union Stamp {
    int w[2];
    struct {
        unsigned short f0;
        unsigned char f2, f3, f4, f5, f6, f7;
    } unk_00;
};

struct Pair {
    union Stamp a;
    union Stamp b;
};

typedef struct {
    unsigned int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02046830;

typedef struct {
    int pad_00;
    int unk_04;
    int unk_08;
} UnkStruct_020467cc;

typedef struct {
    char pad_00[0x34];
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
} UnkStruct_02046730;

typedef struct Pair_020466e0 {
    int x;
    int y;
} Pair_020466e0;

extern int func_0204e414(void);
extern unsigned short *func_0204f5e0(int, int, int, int, int, int);
extern void func_0204f800(char *, char *, int, int, int, int);
extern int func_0206f7a4(void);
extern void func_0209e474(union Stamp *);
extern int func_0209e350(union Stamp *, union Stamp *);
extern const unsigned char data_021f39fc[3];
extern void func_0209dfa4(int);
extern void func_0204a848(char *addr, UnkStruct_02046830 *arg1, int x, int y);
extern void func_02046f14(char *a, UnkStruct_02046830 *b);
extern void func_02046bc8(void);
extern int func_02073d90(unsigned int);
extern void func_02046c2c(char *);
extern int func_020b65c4(void);
extern void func_0204763c(char *, int);
extern void func_02046a74(int);
extern void func_02042c40(char *);
extern void func_02045b3c(char *);
extern void func_02042c28(char *);
extern void func_02042f08(char *);
extern char data_021c7a08[];
extern char data_021c779c[];
extern char data_021c7c48[];
extern char data_021c7880[];
extern char data_021c7788[];
extern char data_021c80b4[];
extern unsigned int data_020ccf94;
extern int data_021c79c4[];
extern void func_0204a5d4(int *g, UnkStruct_020467cc *obj, int x, int y);
extern void func_02048418(int *g, UnkStruct_020467cc *obj, int x, int y);
extern void func_020483c4(int *g, UnkStruct_020467cc *obj, int x, int y);
extern void func_02048a80(int *g, UnkStruct_020467cc *obj, int x, int y);
extern void func_02048238(int *g, UnkStruct_020467cc *obj, int x, int y);
extern void func_0204226c(int);
extern void func_02045d74(void);
extern unsigned char data_021c776c[];
extern int func_0204a3cc(int *ptr, int val);
extern int data_021c79dc;
extern void func_0204f778(int, int, int, int, int);
extern int data_021c77c0;
extern void func_020481a0(int);
extern void func_020479e0(void *p0, void *p1);
extern void func_02042ce8(void *);
extern void func_02042cd8(void *);
extern void func_02042218(void *);

int func_0204678c(void);
int func_020466d8(void);
void func_02046680(void);
void func_02046650(void);

void func_0204695c(void)
{
    struct UnkStruct_0204695c *obj;
    char *p;
    int bound;
    int j, i, k;
    int zero = 0;
    unsigned short *q;

    obj = (struct UnkStruct_0204695c *) func_0204e414();
    func_02046680();
    if (obj != 0) {
        bound = obj->unk_04 - 2;
        p = (char *) func_020466d8();
        for (i = 0; i < 2; i++) {
            for (j = 0; j < bound; j++) {
                q = func_0204f5e0((int) obj, j + 1, i + 1, zero, zero, zero);
                for (k = 0; k < 256; k++) {
                    if (*q == 0x6d) {
                        func_0204f800(p, p + 4, j + 1, i + 1, k % 16, k / 16);
                        p += 8;
                    }
                    q++;
                }
            }
        }
    }
}

int func_02046904(void)
{
    int result;

    result = 0;
    if (func_0206f7a4() != 0) {
        result = 1;
    } else {
        struct Pair p;

        p.a.w[0] = 0;
        p.a.w[1] = 0;
        p.b.w[0] = 0;
        p.b.w[1] = 0;

        func_0209e474(&p.a);

        {
            unsigned char *dp = (unsigned char *) data_021f39fc;
            p.b.w[0] = 0;
            p.b.w[1] = 0;
            p.b.unk_00.f5 = dp[2];
            p.b.unk_00.f4 = dp[1];
            p.b.unk_00.f3 = dp[0];
            p.b.unk_00.f2 = 6;
        }

        if (func_0209e350(&p.a, &p.b) > 0) {
            result = 1;
        }
    }
    return result;
}

void func_02046830(void)
{
    UnkStruct_02046830 *r6;
    int width, height;
    char *p;
    int outer;
    int inner;
    int tmp;

    r6 = (UnkStruct_02046830 *) func_0204e414();
    func_0209dfa4(0);
    if (r6 != 0) {
        width = r6->unk_04 - 2;
        height = r6->unk_08 - 2;
        inner = 0;
        for (outer = 0; outer < width; outer++) {
            tmp = inner;
            p = (char *) data_021c7a08 + outer * 0x90;
            for (; tmp < height; tmp++) {
                func_0204a848(p + tmp * 0x24, r6, outer + 1, tmp + 1);
            }
        }
        func_02046f14(data_021c779c, r6);
    }
    func_0204695c();
    func_02046bc8();
    if (func_02073d90(data_020ccf94) == 0) {
        if (func_02046904() != 0) {
            func_02046c2c(data_021c779c);
        }
        if (func_020b65c4() == 0x3f) {
            func_0204763c(data_021c779c, 1);
        } else {
            func_02046a74(1);
        }
    }
    func_02042c40(data_021c7c48);
    func_02045b3c(data_021c7880);
    func_02042c28(data_021c7788);
    func_02042f08(data_021c80b4);
}

void func_020467cc(void)
{
    UnkStruct_020467cc *obj;
    int x, y;

    obj = (UnkStruct_020467cc *) func_0204e414();
    if (obj != 0) {
        x = obj->unk_04 - 2;
        y = obj->unk_08 - 2;
        func_0204a5d4(data_021c79c4, obj, x, y);
        func_02048418(((int *) data_021c779c), obj, x, y);
        func_020483c4(((int *) data_021c779c), obj, x, y);
        func_02048a80(((int *) data_021c779c), obj, x, y);
        func_02048238(((int *) data_021c779c), obj, x, y);
        func_02046650();
    }
}

void func_020467ac(void)
{
    func_0204678c();
    func_0204226c((unsigned int) data_021c776c);
    func_02046650();
    func_02045d74();
}

int func_0204678c(void)
{
    int r = func_0204e414();
    int ret = 5;
    if (r != 0) {
        ret = func_0204a3cc(((int *) data_021c79c4), r);
    }
    return ret;
}

int func_02046784(void)
{
    return (int) &data_021c79dc;
}

int func_0204677c(void)
{
    return (int) ((int *) data_021c779c);
}

int func_02046730(int param)
{
    int result = 0;
    int a = (*(UnkStruct_02046730 *) data_021c79c4).unk_34;
    int b = (*(UnkStruct_02046730 *) data_021c79c4).unk_38;
    int c = (*(UnkStruct_02046730 *) data_021c79c4).unk_3C;
    int d = (*(UnkStruct_02046730 *) data_021c79c4).unk_40;
    if (a != -1 && b != -1 && c != -1 && d != -1) {
        if (func_0204e414() != 0) {
            func_0204f778(param, a + 1, b + 1, c, d);
            result = 1;
        }
    }
    return result;
}

int func_020466e0(int a, int b)
{
    int idx = -1;
    if (func_02073d90((unsigned int) ((*(void * *) &data_020ccf94))) == 0) {
        Pair_020466e0 *p = (Pair_020466e0 *) func_020466d8();
        int i = 0;
        while (i < 24) {
            if (p->x == a && p->y == b) {
                idx = i;
                break;
            }
            p++;
            i++;
        }
    } else {
        idx = (a + b) % 24;
    }
    return idx;
}

int func_020466d8(void)
{
    return (int) &data_021c77c0;
}

void func_020466a0(unsigned int a, unsigned int b)
{
    unsigned int *p;
    int i;
    int mask;
    int zero;

    p = (unsigned int *) func_020466d8();
    i = 0;
    mask = ~i;
    zero = i;
    while (i < 24) {
        if (p[0] == ~zero && p[1] == mask) {
            p[0] = a;
            p[1] = b;
            break;
        }
        p += 2;
        i++;
    }
}

void func_02046680(void)
{
    int *p;
    int i;

    p = (void *) func_020466d8();
    for (i = 0; i < 24; i++) {
        p[0] = -1;
        p[1] = -1;
        p += 2;
    }
}

void func_02046650(void)
{
    int result;

    result = func_02073d90((*(int *) &data_020ccf94));
    if (result) {
        return;
    }
    func_02042c40((char *) (((unsigned char *) data_021c7c48)));
    func_020481a0((unsigned int) ((unsigned char *) data_021c779c));
}

void func_02046640(void *arg)
{
    func_020479e0((void *) ((unsigned char *) data_021c779c), arg);
}

void func_02046620(void)
{
    func_02042ce8((void *) ((unsigned char *) data_021c7c48));
    func_02045b3c((char *) ((void *) ((unsigned char *) data_021c7880)));
}

void func_02046600(void)
{
    func_02042cd8((void *) ((unsigned char *) data_021c7c48));
    func_02042218((void *) data_021c776c);
}
