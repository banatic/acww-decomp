/* effect_kinds: 30 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020921a0 @ 0x020921a0, 0x58 bytes, Thumb
 * func_02092144 @ 0x02092144, 0x5c bytes, Thumb
 * func_02092110 @ 0x02092110, 0x34 bytes, Thumb
 * func_020920e4 @ 0x020920e4, 0x2c bytes, Thumb
 * func_020920bc @ 0x020920bc, 0x28 bytes, Thumb
 * func_02092064 @ 0x02092064, 0x58 bytes, Thumb
 * func_02092054 @ 0x02092054, 0x10 bytes, Thumb
 * func_02092044 @ 0x02092044, 0x10 bytes, Thumb
 * func_0209201c @ 0x0209201c, 0x28 bytes, Thumb
 * func_0209200c @ 0x0209200c, 0x10 bytes, Thumb
 * func_02091ffc @ 0x02091ffc, 0x10 bytes, Thumb
 * func_02091fec @ 0x02091fec, 0x10 bytes, Thumb
 * func_02091fdc @ 0x02091fdc, 0x10 bytes, Thumb
 * func_02091fcc @ 0x02091fcc, 0x10 bytes, Thumb
 * func_02091fbc @ 0x02091fbc, 0x10 bytes, Thumb
 * func_02091f94 @ 0x02091f94, 0x28 bytes, Thumb
 * func_02091f6c @ 0x02091f6c, 0x28 bytes, Thumb
 * func_02091f48 @ 0x02091f48, 0x22 bytes, Thumb
 * func_02091f24 @ 0x02091f24, 0x24 bytes, Thumb
 * func_02091f00 @ 0x02091f00, 0x24 bytes, Thumb
 * func_02091edc @ 0x02091edc, 0x24 bytes, Thumb
 * func_02091eb8 @ 0x02091eb8, 0x24 bytes, Thumb
 * func_02091e90 @ 0x02091e90, 0x28 bytes, Thumb
 * func_02091e80 @ 0x02091e80, 0x10 bytes, Thumb
 * func_02091e70 @ 0x02091e70, 0x10 bytes, Thumb
 * func_02091e48 @ 0x02091e48, 0x28 bytes, Thumb
 * func_02091e38 @ 0x02091e38, 0x10 bytes, Thumb
 * func_02091e28 @ 0x02091e28, 0x10 bytes, Thumb
 * func_02091e00 @ 0x02091e00, 0x28 bytes, Thumb
 * func_02091dd8 @ 0x02091dd8, 0x28 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xc];
    void *sub;
} UnkStruct_02092144;

typedef struct {
    unsigned char pad_00[0x44];
    int unk_44;
    unsigned char pad_48[8];
    int unk_50;
} UnkStruct_02092144_2;

struct Global {
    char pad_00[0x10];
    short unk_10;
};

struct Glob {
    char pad_00[0x10];
    short unk_10;
};

extern char data_020e2794[];
extern char data_020e27a0[];
extern int FX_MulFunc(int a, int b);
extern void func_02094bc0(void *self);
extern short data_021d5658[];
extern void func_02094e04(int, int);
extern void func_02094260(unsigned int *object, unsigned int value);
extern int func_020948b8(int, int, int, int, int, int, int, int, int);
extern unsigned int data_020e29dc;
extern int FX_Div(int, int);
extern int data_020e28dc;
extern int data_020e27b0;
extern int func_0209418c(int, int, int, short *, int *, int *, void (*)(void *));
extern void func_02094c38(int arg0, void *arg1, int arg2);
extern int func_02094bcc(int a, int b, int c);
extern unsigned char data_020d16a8[];
extern int func_02094b58(int, int, int, int, int, int);
extern unsigned char data_020e27d4[];
extern char data_020d16e4[];
extern unsigned char data_020d172c[];
extern char data_020d16cc[];
extern unsigned char data_020e2994[];
extern int func_02094cf8(int, int, int, int, int, int);
extern unsigned char data_020e2b04[];
extern int data_020d1774;
extern unsigned char data_020e281c[];
extern unsigned char data_020d1750[];
extern unsigned char data_020e2894[];

int func_020921a0(int a, int b, int c, int d)
{
    int ret = 3;
    if (d != 0) {
        int i = 0;
        func_02094cf8(0x6c, a, b, c, d, (int) data_020e2794);
        if (((short *) d)[i] >= 0xc00) {
            func_02094cf8(0x6d, a, b, c, d, (int) data_020e27a0);
        }
        ret = 1;
    }
    return ret;
}

void func_02092144(UnkStruct_02092144 *self)
{
    short x = data_021d5658[8];
    short v1 = (short) ((short) FX_MulFunc(0x1333, x) + 0x4cd);
    short v2 = (short) ((short) FX_MulFunc(0x3ae, x) + 0x800);
    func_02094bc0(self);
    ((UnkStruct_02092144_2 *) self->sub)->unk_44 = v1;
    ((UnkStruct_02092144_2 *) self->sub)->unk_50 = v2;
}

void func_02092110(int param)
{
    short s = (short) FX_MulFunc(0x1e66, (*(struct Global *) data_021d5658).unk_10);
    s = (short) (s + 0xb33);
    func_02094e04(param, s);
}

void func_020920e4(void *arg)
{
    int sum = FX_MulFunc(0x2000, (*(struct Glob *) data_021d5658).unk_10) + 0x99a;
    func_02094260((unsigned int *) arg, sum);
}

int func_020920bc(int a)
{
    return func_020948b8(a, 31, (int) &data_020e29dc, 30, (int) &data_020e29dc, 30, (int) &data_020e29dc, -1, 0);
}

int func_02092064(int a0, int a1, int a2, short *ptr)
{
    if (ptr) {
        short s = (short) (FX_Div((int) *ptr - 0x600, 0x1200));
        return func_0209418c(a0, a1, a2, &s, &data_020e28dc, &data_020e27b0, func_020920e4);
    } else {
        return 3;
    }
}

void func_02092054(int param)
{
    func_02094c38(param, ((int *) data_020d16a8), 0);
}

void func_02092044(int a)
{
    func_02094bcc(a, (unsigned int) data_020d16a8, 0);
}

void func_0209201c(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e27d4;
    func_02094b58(0x95, r0, r1, r2, sp[0], sp[1]);
}

void func_0209200c(int arg0)
{
    func_02094c38(arg0, ((unsigned char *) data_020d16cc), 0);
}

void func_02091ffc(int a)
{
    func_02094c38(a, data_020d16e4, 0);
}

void func_02091fec(void *param1)
{
    func_02094c38((int) param1, data_020d172c, 0);
}

void func_02091fdc(void *arg0)
{
    func_02094bcc((int) arg0, (int) data_020d16cc, 0);
}

void func_02091fcc(int arg)
{
    func_02094bcc(arg, (int) (((unsigned char *) data_020d16e4)), 0);
}

void func_02091fbc(int param)
{
    func_02094bcc(param, (int) (((const char *) data_020d172c)), 0);
}

void func_02091f94(int a, int b, int c, int d)
{
    func_02094b58(0x96, a, b, c, d, (unsigned int) data_020e2994);
}

int func_02091f6c(int a1, int a2, int a3, int a4)
{
    return func_02094b58(0x97, a1, a2, a3, a4, (unsigned int) data_020e2994);
}

void func_02091f48(int a, int b, int c, int d)
{
    func_02094cf8(0, a, b, c, d, 0);
}

void func_02091f24(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = 0;
    func_02094b58(1, r0, r1, r2, sp[0], sp[1]);
}

void func_02091f00(int r0, int r1, int r2, int r3)
{
    int sp0 = r3;
    int sp4 = 0;
    func_02094cf8(3, r0, r1, r2, sp0, sp4);
}

int func_02091edc(int a, int b, int c, int d)
{
    return func_02094cf8(4, a, b, c, d, 0);
}

void func_02091eb8(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = 0;
    func_02094cf8(5, r0, r1, r2, sp[0], sp[1]);
}

void func_02091e90(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2b04;
    func_02094b58(6, r0, r1, r2, sp[0], sp[1]);
}

void func_02091e80(int param)
{
    func_02094c38(param, &data_020d1774, 0);
}

void func_02091e70(int arg0)
{
    func_02094bcc(arg0, (int) (&data_020d1774), 0);
}

void func_02091e48(int a1, int a2, int a3, int a4)
{
    int sp[2];
    sp[0] = a4;
    sp[1] = (unsigned int) data_020e281c;
    func_02094b58(7, a1, a2, a3, sp[0], sp[1]);
}

void func_02091e38(int a)
{
    func_02094c38(a, (void *) ((unsigned int) data_020d1750), 0);
}

void func_02091e28(int a)
{
    func_02094bcc(a, (int) (((char *) data_020d1750)), 0);
}

void func_02091e00(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2894;
    func_02094b58(0x5b, r0, r1, r2, sp[0], sp[1]);
}

void func_02091dd8(int r0, int r1, int r2, int r3)
{
    int sp[2];
    sp[0] = r3;
    sp[1] = (unsigned int) data_020e2894;
    func_02094b58(0x5c, r0, r1, r2, sp[0], sp[1]);
}
