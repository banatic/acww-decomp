/* func_ov094_0229aeb8 @ 0x0229aeb8, 0x2e bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229ae54(int, int, int, int, int, int, int);

int func_ov094_0229aeb8(int a, int b, int c)
{
    if (c > 0x68) {
        return 0x23;
    }
    return func_ov094_0229ae54(a, b - 0x94, c - 0x74, b - 0x7c, c - 0x5c, 0xf, 0x1d);
}
