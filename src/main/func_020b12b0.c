/* func_020b12b0 @ 0x020b12b0, 0x2e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020b12b0(int a, int b, int c, int d)
{
    if (d < b + 0x10 || d > b + 0x88) {
        return 0;
    }
    if (c < a + 0x40 || c > a + 0xc0) {
        return 0;
    }
    return 1;
}
