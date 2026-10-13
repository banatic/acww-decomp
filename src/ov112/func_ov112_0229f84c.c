/* func_ov112_0229f84c @ 0x0229f84c, 0x50 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229bb34(void *p1, void *p2, int p3, int p4, int p5, void *p6);

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
