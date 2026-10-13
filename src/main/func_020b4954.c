/* func_020b4954 @ 0x020b4954, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020b4954(char *s, unsigned int len, int arg2, unsigned int i)
{
    do {
        if (s[i] == 0) {
            if (s[i + 1] == 0) {
                break;
            }
        }
        i += 2;
    } while (i < len);
    return i;
}
