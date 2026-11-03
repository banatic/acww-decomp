/* field_actor_47: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02217838 @ 0x02217838, 0x5c bytes, Thumb
 * func_ov003_0221781c @ 0x0221781c, 0x1c bytes, Thumb
 * func_ov003_022177f4 @ 0x022177f4, 0x28 bytes, Thumb
 * func_ov003_022177d0 @ 0x022177d0, 0x24 bytes, Thumb
 */

struct UnkStruct_0221781c {
    int unk_00;
    int unk_04;
    int unk_08;
    short unk_0C;
    char unk_0E;
};

struct UnkStruct_022177f4 {
    char data[5];
    char unk_05;
    char unk_06;
    char unk_07;
};

extern unsigned int func_0200e92c(char *p);
extern void func_0200e90c(char *p, int n, int m, short s);
extern void func_ov003_02217894(char *p, int a, int b, int c, int d, short e);
extern void func_0200f268(char *p, int n);
extern int func_0200e894(char *p, char *q);
extern int func_0200e91c(char *p);
extern void func_020779b8(void *s, int a, int b);
extern void func_02077910(char *p, short d);
extern void func_02077978(const unsigned char *a, int c, int d);
extern unsigned short func_020778f8(const unsigned char *s);

int func_ov003_02217838(char *p0, int p1, int p2, int p3, int p4, short p5, int p6, short p7)
{
    char buf1[12];
    char out[20];
    int ret;

    func_0200e92c(buf1);
    func_0200e90c(buf1, 0x3e, p6, p7);
    func_ov003_02217894(out, p1, p2, p3, p4, p5);
    func_0200f268(p0, 1);
    ret = func_0200e894(p0, buf1);
    func_0200e91c(buf1);
    return ret;
}

void func_ov003_0221781c(struct UnkStruct_0221781c *out, int a, char b, int c, int d, short e)
{
    out->unk_00 = a;
    out->unk_0E = b;
    out->unk_04 = c;
    out->unk_08 = d;
    out->unk_0C = e;
}

void func_ov003_022177f4(struct UnkStruct_022177f4 *s, char v, int a, int b, short d)
{
    s->unk_07 = v;
    func_020779b8(s, a, b);
    func_02077910(&s->unk_05, d);
}

unsigned short func_ov003_022177d0(const unsigned char *a, unsigned char *b, int c, int d, unsigned short *e)
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
