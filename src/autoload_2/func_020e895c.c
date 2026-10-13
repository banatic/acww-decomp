/* func_020e895c @ 0x020e895c, 0x80 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

int func_020e895c(int *p, int v, int d)
{
    if (d != 0) {
        if (*p > v) {
            d = -d;
        }
        *p += d;
        if ((long long) d * (*p - v) >= 0) {
            *p = v;
            return 1;
        }
    } else {
        if (*p == v) {
            return 1;
        }
    }
    return 0;
}
