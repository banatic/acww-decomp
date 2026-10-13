/* func_020e8870 @ 0x020e8870, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

int func_020e8870(short *p, int a, short b)
{
    if (b != 0) {
        if ((short) (*p - a) > 0) {
            b = -b;
        }
        *p = (short) (*(volatile short *) p + b);
        if ((int) b * (short) (*p - a) < 0) {
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
