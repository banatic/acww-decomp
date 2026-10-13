/* func_020e89dc @ 0x020e89dc, 0x5c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

int func_020e89dc(short *p, int a, short b)
{
    if (b != 0) {
        if (*p > a) {
            b = -b;
        }
        *p = (short) (*(volatile short *) p + b);
        if (b * (*p - a) < 0) {
            goto fail;
        }
        *p = (short) a;
        return 1;
    } else {
        if (*p == a) {
            return 1;
        }
    }
fail:
    return 0;
}
