/* func_ov112_022a029c @ 0x022a029c, 0x58 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229bc00(unsigned char *a, unsigned char *b, int c, unsigned char *d, int e, int f, int g, int h, int i,
                               int j);
extern void func_ov112_0229f6d4(unsigned char *p, unsigned char b);

int func_ov112_022a029c(unsigned char *p, int a, int b)
{
    unsigned char c = p[0xbd];
    if (func_ov095_0229bc00(p + 0x384, p + 0xc4, a, &c, 0x60, 0x10, 6, 0xa0, 0, b)) {
        func_ov112_0229f6d4(p, c);
        return 1;
    }
    return 0;
}
