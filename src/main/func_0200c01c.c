/* func_0200c01c @ 0x0200c01c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200c0c8(unsigned char *p, unsigned char *a, unsigned char *b);
extern void func_0200c0dc(unsigned char *p, unsigned char a, unsigned char b, int n, int v);

void func_0200c01c(unsigned char *p, int v)
{
    unsigned char buf[2];
    func_0200c0c8(p + 0x8f0, &buf[0], &buf[1]);
    func_0200c0dc(p, buf[0], buf[1], 5, v);
}
