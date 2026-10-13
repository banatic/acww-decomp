/* func_0202da38 @ 0x0202da38, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200368c(int a, int b, int c, int d);
extern int func_020644cc(int a);

void func_0202da38(int p0, int p1, unsigned char *p2, int p3, unsigned char p4, int p5, unsigned char p6, int p7,
                   unsigned char p8)
{
    unsigned char product;
    unsigned char selected;
    product = (unsigned char) (p6 * p7);
    selected = p6;
    if (p8) {
        selected = p8;
    }
    func_0200368c(p1, p3, p5, p4);
    *p2 = (unsigned char) (product + func_020644cc(selected));
}
