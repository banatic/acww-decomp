/* func_020e8b0c @ 0x020e8b0c, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

int func_020e8b0c(int a, int b, int c)
{
    if (b < c) {
        int result = 0;
        if (a >= b) {
            result = (a <= c);
        }
        return result;
    } else {
        int result = 0;
        if (a >= c) {
            result = (a <= b);
        }
        return result;
    }
}
