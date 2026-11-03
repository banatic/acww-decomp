/* field_actor_room_states_10: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02228628 @ 0x02228628, 0x50 bytes, Thumb
 * func_ov004_02228610 @ 0x02228610, 0x18 bytes, Thumb
 * func_ov004_022285e8 @ 0x022285e8, 0x28 bytes, Thumb
 * func_ov004_022285c4 @ 0x022285c4, 0x24 bytes, Thumb
 */

struct UnkStruct_02228610 {
    int unk_00;
    int unk_04;
    short unk_08;
    char unk_0A;
};

struct UnkStruct_022285e8 {
    char data[5];
    char unk_05;
    char unk_06;
    char unk_07;
};

extern unsigned int func_0200e92c(void *p);
extern void func_0200e90c(void *p, int a, int b, int c);
extern void func_ov004_02228678(void *p, int a, int b, int c, int d);
extern int func_0200e894(int a, void *p);
extern int func_0200e91c(void *p);
extern void func_020779b8(void *s, int a, int b);
extern void func_02077910(char *p, short d);
extern void func_02077978(const unsigned char *a, int c, int d);
extern unsigned short func_020778f8(const unsigned char *s);

int func_ov004_02228628(int a, int b, int c, int d, short e, int f, short g)
{
    char buf0[12];
    char buf1[16];
    int res;

    func_0200e92c(buf0);
    func_0200e90c(buf0, 0x2d, f, g);
    func_ov004_02228678(buf1, b, c, d, e);
    res = func_0200e894(a, buf0);
    func_0200e91c(buf0);
    return res;
}

void func_ov004_02228610(struct UnkStruct_02228610 *out, char fA, int f0, int f4, short f8)
{
    out->unk_0A = fA;
    out->unk_00 = f0;
    out->unk_04 = f4;
    out->unk_08 = f8;
}

void func_ov004_022285e8(struct UnkStruct_022285e8 *s, char v, int a, int b, short d)
{
    s->unk_07 = v;
    func_020779b8(s, a, b);
    func_02077910(&s->unk_05, d);
}

unsigned short func_ov004_022285c4(const unsigned char *a, unsigned char *b, int c, int d, unsigned short *e)
{
    unsigned char t;
    unsigned short r;

    t = a[7];
    *b = t;
    func_02077978(a, c, d);
    r = func_020778f8(a + 5);
    *e = r;
    return r;
}
