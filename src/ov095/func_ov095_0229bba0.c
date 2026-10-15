/* func_ov095_0229bba0 @ 0x0229bba0, 0x20 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_022999c0(int a, int b);

int func_ov095_0229bba0(int a, unsigned short *b, int c, int d)
{
    if (d == 0) {
        return 0;
    }
    b[d - 1] = c;
    func_ov095_022999c0(a, c);
    return 1;
}
