/* func_020b34e0 @ 0x020b34e0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020b34e0(signed char *base, int value)
{
    signed char *p = base + 4;
    while (p < base + 7) {
        if (*p == value) {
            return 1;
        }
        p++;
    }
    return 0;
}
