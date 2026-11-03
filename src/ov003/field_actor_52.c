/* field_actor_52: 4 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022186cc @ 0x022186cc, 0x50 bytes, Thumb
 * func_ov003_022186b0 @ 0x022186b0, 0x1c bytes, Thumb
 * func_ov003_02218688 @ 0x02218688, 0x28 bytes, Thumb
 * func_ov003_02218664 @ 0x02218664, 0x24 bytes, Thumb
 */

struct UnkStruct_022186b0 {
    int a;
    int b;
    short c;
    char d;
    char e;
};

struct UnkStruct_02218688 {
    char pad_00[5];
    char data[2];
    char flag;
};

extern unsigned int func_0200e92c(void *p);
extern void func_0200e90c(void *p, int a, int b, int c);
extern void func_ov003_0221871c(void *p, int a, int b, int c, int d);
extern int func_0200e894(int a, void *p);
extern int func_0200e91c(void *p);
extern void func_020779b8(void *, int, int);
extern void func_02077910(void *, short);
extern void func_02077978(void *a, int b, int c);
extern unsigned short func_020778f8(void *p);

int func_ov003_022186cc(int a, int b, int c, int d, short e, int f, short g)
{
    char buf0[12];
    char buf1[16];
    int res;

    func_0200e92c(buf0);
    func_0200e90c(buf0, 0x39, f, g);
    func_ov003_0221871c(buf1, b, c, d, e);
    res = func_0200e894(a, buf0);
    func_0200e91c(buf0);
    return res;
}

void func_ov003_022186b0(struct UnkStruct_022186b0 *out, char a, int b, int c, short d, unsigned char e)
{
    out->d = a;
    out->a = b;
    out->b = c;
    out->c = d;
    out->e = e;
}

void func_ov003_02218688(struct UnkStruct_02218688 *self, char byte, int a, int b, short s)
{
    self->flag = byte;
    func_020779b8(self, a, b);
    func_02077910(self->data, s);
}

void func_ov003_02218664(unsigned char *a0, unsigned char *a1, int a2, int a3, unsigned short *a4)
{
    *a1 = a0[7];
    func_02077978(a0, a2, a3);
    *a4 = func_020778f8(a0 + 5);
}
