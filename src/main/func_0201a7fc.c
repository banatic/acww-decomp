/* func_0201a7fc @ 0x0201a7fc, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0201a7fc(unsigned char *s)
{
    if (s[0x18] == 0) {
        s += 0x2a;
        if (*s == 1) {
            return 1;
        }
    }
    return 0;
}
