/* func_020e88dc @ 0x020e88dc, 0x80 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

int func_020e88dc(int *p, int a, int b)
{
    if (b != 0) {
        if (*p > a) {
            b = -b;
        }
        *p = *p + b;
        if ((long long) b * (*p - a) < 0) {
            goto fail;
        }
        *p = a;
        return 1;
    } else {
        if (*p == a) {
            return 1;
        }
    }
fail:
    return 0;
}
