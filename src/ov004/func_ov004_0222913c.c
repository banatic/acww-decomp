/* func_ov004_0222913c @ 0x0222913c, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022291cc(char *src, int *b, int *c, int *a);
extern int func_ov004_0222920c(char *p, int *b, int *c, int *a, int p5, int p6);

void func_ov004_0222913c(char *p1, int p2)
{
    int a, b, c;
    func_ov004_022291cc(p1 + 0x8f0, &b, &c, &a);
    func_ov004_0222920c(p1, &b, &c, &a, 6, p2);
}
