/* func_ov095_0229c52c @ 0x0229c52c, 0x1c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

int func_ov095_0229c52c(int a, int b)
{
    if (b >= 0xf7 && b <= 0x10f) {
        b += 0xf;
        return b;
    }
    return -1;
}
