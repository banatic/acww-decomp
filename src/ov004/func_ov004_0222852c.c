/* func_ov004_0222852c @ 0x0222852c, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222852c {
    unsigned char b;
    unsigned char pad_01;
    short e;
};

extern unsigned short func_ov004_022285c4(const unsigned char *a, unsigned char *b, int *c, int *d, unsigned short *e);
extern int func_ov004_02228628(int a, int b, int c, int d, short e, int f, short g);

int func_ov004_0222852c(char *self, short arg)
{
    struct UnkStruct_0222852c t;
    int c, d;

    func_ov004_022285c4((const unsigned char *) (self + 0x8f0), &t.b, &c, &d, (unsigned short *) &t.e);
    return func_ov004_02228628((int) self, t.b, c, d, t.e, 6, arg);
}
