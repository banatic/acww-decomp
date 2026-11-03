/* effect_kinds_10: 20 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020944d8 @ 0x020944d8, 0x28 bytes, Thumb
 * func_020944b0 @ 0x020944b0, 0x28 bytes, Thumb
 * func_0209446c @ 0x0209446c, 0x44 bytes, Thumb
 * func_0209445c @ 0x0209445c, 0x10 bytes, Thumb
 * func_0209444c @ 0x0209444c, 0x10 bytes, Thumb
 * func_02094404 @ 0x02094404, 0x48 bytes, Thumb
 * func_020943c0 @ 0x020943c0, 0x44 bytes, Thumb
 * func_020943ac @ 0x020943ac, 0x14 bytes, Thumb
 * func_02094364 @ 0x02094364, 0x48 bytes, Thumb
 * func_02094294 @ 0x02094294, 0xd0 bytes, Thumb
 * func_02094260 @ 0x02094260, 0x34 bytes, Thumb
 * func_02094250 @ 0x02094250, 0x10 bytes, Thumb
 * func_02094228 @ 0x02094228, 0x28 bytes, Thumb
 * func_0209418c @ 0x0209418c, 0x9c bytes, Thumb
 * func_02094168 @ 0x02094168, 0x24 bytes, Thumb
 * func_02094144 @ 0x02094144, 0x24 bytes, Thumb
 * func_020940d0 @ 0x020940d0, 0x74 bytes, Thumb
 * func_0209405c @ 0x0209405c, 0x74 bytes, Thumb
 * func_02094038 @ 0x02094038, 0x24 bytes, Thumb
 * func_02093fc4 @ 0x02093fc4, 0x74 bytes, Thumb
 */

typedef struct {
    char pad_00[52];
    int unk_34;
    char pad_38[12];
} UnkStruct_0209446c;

typedef struct {
    char pad_00[0x34];
    int unk_34;
    char pad_38[0x0c];
} UnkStruct_020943c0;

typedef struct {
    unsigned char pad_00[0x34];
    int unk_34;
    unsigned char pad_38[0x40 - 0x38];
} Big;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0209418c;

typedef struct {
    unsigned char pad_00[0x30];
    int unk_30;
    unsigned char pad_34[0x8];
    int unk_3C;
} LocalBuf;

typedef struct {
    unsigned char pad_00[0x39c];
    unsigned short unk_39C;
} Cfg;

extern int func_02094cf8(int, int, int, int, int, int);
extern unsigned char data_020e277c[];
extern unsigned char data_020e2814[];
extern int func_02034270(void *s, int b, int c, int d);
extern void func_0203423c(void *s);
extern void func_02094d48(void *param1, int param2, void *param3);
extern char data_020d181c[];
extern int data_020d17a4;
extern char data_020e28cc;
extern int data_020d1708;
extern int data_020d1780;
extern char data_020e2910;
extern int func_020ba4e4(void);
extern int func_020b6598(void);
extern unsigned short data_021d52d8[];
extern unsigned char data_020e289c[];
extern unsigned char data_020e28ec[];
extern char data_020e29dc[];
extern int func_020948b8(int, int, char *, int, char *, int, char *, int, int);
extern int func_02094840(int a, int b, void *c, int d, int e, void (*callback)(void *));
extern void func_020914dc(void *a);
extern unsigned char data_021d5658[];
extern unsigned char data_020e2834[];
extern int data_020e28f4;
extern void func_02091494(void *ctx, int hw, int a0, int a1, int a2, int a3, int minus1);
extern int func_02090ac4(int kind, int a1, int a2, void *tbl);
extern int data_020e2804;
extern int data_020e28e4;

void func_020944d8(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e277c;
    func_02094cf8(0x29, r0, r1, r2, sp[0], sp[1]);
}

void func_020944b0(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2814;
    func_02094cf8(0x2a, r0, r1, r2, sp[0], sp[1]);
}

int func_0209446c(int a, int b, int c, int d)
{
    UnkStruct_0209446c s;
    int sign;
    int result;

    func_02034270(&s, b, 0, 0);
    if (s.unk_34 == 19) {
        sign = 45;
    } else {
        sign = 43;
    }
    result = func_02094cf8(sign, a, b, c, d, 0);
    func_0203423c(&s);
    return result;
}

void func_0209445c(void *param0)
{
    func_02094d48(param0, 0, data_020d181c);
}

void func_0209444c(int a)
{
    func_02094d48((void *) a, 0, (void *) (&data_020d17a4));
}

int func_02094404(int a, int b, int c, int d)
{
    char buf[0x44];
    int value;

    func_02034270(buf, b, 0, 0);
    if (*(int *) (buf + 0x34) == 0x13) {
        value = 0x2e;
    } else {
        value = 0x2c;
    }
    value = func_02094cf8(value, a, b, c, d, (int) (&data_020e28cc));
    func_0203423c(buf);
    return value;
}

int func_020943c0(int a, int b, int c, int d)
{
    UnkStruct_020943c0 local;
    int sel;
    int result;

    func_02034270(&local, b, 0, 0);
    sel = (local.unk_34 == 0x13) ? 0x30 : 0x2f;
    result = func_02094cf8(sel, a, b, c, d, 0);
    func_0203423c(&local);
    return result;
}

void func_020943ac(int a)
{
    func_02094d48((void *) a, (int) (&data_020d1708), (void *) (&data_020d1780));
}

int func_02094364(int a, int b, int c, int d)
{
    char buf[0x44];
    int value;

    func_02034270(buf, b, 0, 0);
    if (*(int *) (buf + 0x34) == 0x13) {
        value = 0x32;
    } else {
        value = 0x31;
    }
    value = func_02094cf8(value, a, b, c, d, (int) (&data_020e2910));
    func_0203423c(buf);
    return value;
}

int func_02094294(void *a, void *b, void *c, void *d)
{
    Big big;
    int ret;
    int mode;
    unsigned char *tp;

    tp = (unsigned char *) data_021d52d8;
    func_02034270((void *) (&big), (int) b, 0, 0);
    mode = big.unk_34;
    ret = 3;
    if (func_020ba4e4() == 1) {
        func_02091494(((void * *) data_021d5658), *(unsigned short *) (tp + 0x39c), (int) a, (int) b, (int) c, (int) d, -1);
        if (func_02090ac4(0x36, (int) b, (int) c, data_020e289c) != 0) {
            ret = 2;
        }
    } else if (func_020b6598() != 0 && mode == 3) {
        func_02091494(((void * *) data_021d5658), *(unsigned short *) (tp + 0x39c), (int) a, (int) b, (int) c, 0, -1);
        if (func_02090ac4(0x35, (int) b, (int) c, data_020e28ec) != 0) {
            ret = 2;
        }
    } else {
        int k;
        if (mode == 0x13) {
            k = 0x34;
        } else {
            k = 0x33;
        }
        ret = func_02094cf8(k, (int) a, (int) b, (int) c, (int) d, 0);
    }
    func_0203423c((void *) (&big));
    return ret;
}

/* FAKEMATCH: copying the first word through the global and the next two through a char alias gives the base-plus-offset stores; plain field copies and a struct copy change the size */
void func_02094260(unsigned int *p, unsigned int v)
{
    unsigned int *q;
    unsigned short *s;
    char *ptr;
    ptr = (char *) (((unsigned int *) data_021d5658));
    q = p + 1;
    *q = (*(unsigned int *) data_021d5658);
    q[1] = *((unsigned int *) (ptr + 4));
    q[2] = *((unsigned int *) (ptr + 8));
    q = p + 4;
    *q = v;
    q[1] = v;
    q[2] = v;
    s = (unsigned short *) (p + 7);
    *s = 0;
    s[1] = 0;
    s[2] = 0;
}

void func_02094250(void *ptr)
{
    func_02094260((unsigned int *) ptr, 0x1000);
}

void func_02094228(int a)
{
    func_020948b8(a, 31, data_020e29dc, 30, data_020e29dc, 30, data_020e29dc, -1, 0);
}

int func_0209418c(int a0, UnkStruct_0209418c *a1, int a2, int a3, int a4, int a5, void (*callback)(void *))
{
    LocalBuf buf;
    unsigned short *p = data_021d52d8;
    int result;

    func_02034270(&buf, (int) a1, 0, 0);
    result = 3;
    if (buf.unk_30 != 0) {
        a1->unk_04 = buf.unk_3C;
    }
    if (func_02094cf8(0x4a, a0, (int) ((void *) a1), a2, a3, a5) < 3) {
        func_02094840(2, a0, (void *) a1, a2, a3, callback);
        func_02091494((void *) data_021d5658, (unsigned short) p[0x1ce], a0, (int) ((void *) a1), a2, a3, -1);
        if (func_02090ac4(0x45, (int) ((void *) a1), a2, (void *) a4) != 0) {
            result = 2;
        }
    }
    func_020914dc((void *) data_021d5658);
    func_0203423c(&buf);
    return result;
}

void func_02094168(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    func_0209418c(a, (UnkStruct_0209418c *) b, c, d, (unsigned int) data_020e2834, 0, func_02094250);
}

void func_02094144(int arg0)
{
    func_020948b8(arg0, 0x5F, (char *) (((int *) data_020e29dc)), -1, 0, -1, 0, -1, 0);
}

int func_020940d0(int a0, int a1, int a2, int a3)
{
    int ret;
    Cfg *cfg;

    cfg = ((Cfg *) data_021d52d8);
    ret = 3;
    if (func_02094cf8(0x37, a0, a1, a2, a3, 0) < 3) {
        func_02091494(((int *) data_021d5658), cfg->unk_39C, a0, a1, a2, a3, -1);
        if (func_02090ac4(0x5e, a1, a2, &data_020e28f4) != 0) {
            ret = 2;
        }
    }
    func_020914dc(((int *) data_021d5658));
    return ret;
}

int func_0209405c(int a0, int a1, int a2, int a3)
{
    int ret;
    Cfg *cfg;

    cfg = ((Cfg *) data_021d52d8);
    ret = 3;
    if (func_02094cf8(0x38, a0, a1, a2, a3, 0) < 3) {
        func_02091494(((int *) data_021d5658), cfg->unk_39C, a0, a1, a2, a3, -1);
        if (func_02090ac4(0x5e, a1, a2, &data_020e2804) != 0) {
            ret = 2;
        }
    }
    func_020914dc(((int *) data_021d5658));
    return ret;
}

void func_02094038(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = 0;
    func_02094cf8(0x3a, r0, r1, r2, sp[0], sp[1]);
}

int func_02093fc4(int a0, int a1, int a2, int a3)
{
    int ret;
    Cfg *cfg;

    cfg = ((Cfg *) data_021d52d8);
    ret = 3;
    if (func_02094cf8(0x3b, a0, a1, a2, a3, 0) < 3) {
        func_02091494(((int *) data_021d5658), cfg->unk_39C, a0, a1, a2, a3, -1);
        if (func_02090ac4(0x5e, a1, a2, &data_020e28e4) != 0) {
            ret = 2;
        }
    }
    func_020914dc(((int *) data_021d5658));
    return ret;
}
