/* func_ov004_0222b0b8 @ 0x0222b0b8, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0222b0b8 {
    unsigned char b;
    unsigned char pad_01;
    short e;
};

extern void func_ov004_0222b1b4(const unsigned char *a, int *c, int *d, unsigned short *e, unsigned char *b);
extern int func_ov004_0222b214(int self, int c, int d, short e, int b, int f, short g);

int func_ov004_0222b0b8(char *self, short arg)
{
    struct UnkStruct_0222b0b8 t;
    int c, d;

    func_ov004_0222b1b4((const unsigned char *) (self + 0x8f0), &c, &d, (unsigned short *) &t.e, &t.b);
    return func_ov004_0222b214((int) self, c, d, t.e, t.b, 6, arg);
}
