/* func_0209a498 @ 0x0209a498, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0209a498(unsigned char value, const unsigned char *array, int len)
{
    int i;
    const unsigned char *p = array;

    for (i = 0; i < len; i++) {
        if (value >= *p) {
            return i;
        }
        p++;
    }
    return len;
}
