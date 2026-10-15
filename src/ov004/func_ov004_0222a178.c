/* func_ov004_0222a178 @ 0x0222a178, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0222a20c(unsigned char *p, unsigned char *a, unsigned char *b);
extern int func_ov004_0222a23c(unsigned char *p, unsigned char a, unsigned char b, int n, int v);

void func_ov004_0222a178(unsigned char *p, int v)
{
    unsigned char buf[2];
    func_ov004_0222a20c(p + 0x8f0, &buf[0], &buf[1]);
    func_ov004_0222a23c(p, buf[0], buf[1], 5, v);
}
