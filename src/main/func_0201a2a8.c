/* func_0201a2a8 @ 0x0201a2a8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0201a2a8(int unused, int a, int b, int c)
{
    int ret = 0;
    if (a == 0) {
        if (b == 5) {
            ret = 1;
        }
    } else if (b >= c - 0x1000) {
        ret = 1;
    }
    return ret;
}
