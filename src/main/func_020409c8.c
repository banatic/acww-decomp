/* func_020409c8 @ 0x020409c8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void *func_020409c8(void *base, int n)
{
    void *ret = 0;
    if (n >= 0 && n <= 6 && n != 0 && n != 6) {
        ret = ((char *) base + 20) + (6 * (n - 1));
    }
    return ret;
}
