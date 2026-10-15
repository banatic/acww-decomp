/* func_0202da38 @ 0x0202da38, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200368c(int a, int b, int c, int d);
extern int func_020644cc(int a);

int func_0202da38(int p0, int p1, unsigned char *p2, int p3, int p4, int p5, int p6, int p7, int p8)
{
    int result;

    unsigned char product;
    unsigned char selected;
    product = (unsigned char) ((*(unsigned char *) &p6) * p7);
    selected = (*(unsigned char *) &p6);
    if ((*(unsigned char *) &p8)) {
        selected = (*(unsigned char *) &p8);
    }
    func_0200368c(p1, p3, p5, (*(unsigned char *) &p4));
    result = product + func_020644cc(selected);
    *p2 = (unsigned char) result;
    return result;
}
