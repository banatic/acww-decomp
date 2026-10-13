/* func_ov004_0222ae54 @ 0x0222ae54, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222af30(void *a, unsigned char *b, int *c, int *d);
extern void func_ov004_0222af6c(int self, int b, int c, int d, int e, int f, short g);

void func_ov004_0222ae54(char *self, short arg)
{
    unsigned char b;
    int c, d;

    if (*(int *) (self + 0x7f0) == 0xf) {
        *(short *) (self + 0xc84) = arg;
    } else {
        func_ov004_0222af30(self + 0x8f0, &b, &c, &d);
        func_ov004_0222af6c((int) self, b, c, d, 0, 6, arg);
    }
}
