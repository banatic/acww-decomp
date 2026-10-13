/* func_ov094_0229abb8 @ 0x0229abb8, 0x40 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229aaac(int a, int b);
extern int func_ov094_0229aa84(int a, int b);
extern void func_ov094_0229abf8(int a, int b, unsigned short *c, int d);

void func_ov094_0229abb8(int a, int b, int c)
{
    unsigned short x;
    int ret;

    ret = func_ov094_0229aaac(a, c);
    x = 0xfff1;
    x = (unsigned short) ret;
    if (x == 0xfff1) {
        return;
    }

    func_ov094_0229abf8(a, b, &x, func_ov094_0229aa84(a, c));
}
