/* func_020410ec @ 0x020410ec, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020410ec(int arg0, const unsigned char *str, unsigned char ch)
{
    int result = 0;
    int i = 0;
    const unsigned char *p = str;
    while (i <= 5) {
        if (*p != 'c' && *p == ch) {
            result = 1;
            break;
        }
        p++;
        i++;
    }
    return result;
}
