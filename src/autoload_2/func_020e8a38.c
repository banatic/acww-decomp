/* func_020e8a38 @ 0x020e8a38, 0x5c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

int func_020e8a38(unsigned char *p, int a, short b)
{
    short newval;
    if (b != 0) {
        if ((int) *p > a) {
            b = -b;
        }
        newval = (short) (*p + b);
        if (b * (newval - a) >= 0) {
            *p = (unsigned char) a;
            return 1;
        }
        *p = (unsigned char) newval;
        goto fail;
    } else {
        if (*p == a) {
            return 1;
        }
    }
fail:
    return 0;
}
