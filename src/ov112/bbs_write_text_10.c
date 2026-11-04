/* bbs_write_text_10: 2 functions, module ov112
 * mwccarm 1.2/base -O4,s
 * func_ov112_0229f89c @ 0x0229f89c, 0x48 bytes, Thumb
 * func_ov112_0229f84c @ 0x0229f84c, 0x50 bytes, Thumb
 */

extern int func_ov095_0229bbc0(unsigned char *, unsigned char *, unsigned char, unsigned char, int);
extern void func_ov112_0229f6d4(void *, unsigned char);
extern void func_ov112_0229f8e4(void *);
extern int func_ov095_0229bb34(void *p1, void *p2, int p3, int p4, int p5, void *p6);

void func_ov112_0229f89c(unsigned char *self)
{
    unsigned char a = self[0xBF];
    unsigned char b = self[0xBE];
    unsigned char min, max, v;

    if (b > a) {
        min = a;
        max = b;
    } else {
        min = b;
        max = a;
    }

    v = (unsigned char) func_ov095_0229bbc0(self + 0x384, self + 0xC4, min, max, 0x60);
    func_ov112_0229f6d4(self, v);
    func_ov112_0229f8e4(self);
}

unsigned char func_ov112_0229f84c(unsigned char *a, int b, int *c)
{
    int val;
    unsigned char buf;
    int i;

    i = *(int *) (a + (b << 2) + 0x6c50);
    val = (unsigned char) (*c - 0x30);
    *c = func_ov095_0229bb34(a + 0x384, a + 0xc4 + (i << 1), 0x60 - i, 0xa0, val, &buf) + 0x30;
    return (unsigned char) (buf + i);
}
