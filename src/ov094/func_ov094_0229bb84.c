/* func_ov094_0229bb84 @ 0x0229bb84, 0x20 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229bb04(int a, int b, int c, int d, int e);

int func_ov094_0229bb84(int a, int b, int c)
{
    if (b > 0xa0 || b < 0x60) {
        return 0x37;
    }
    return func_ov094_0229bb04(a, b, c, 0x2d, 0x36);
}
