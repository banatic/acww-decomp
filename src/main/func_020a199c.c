/* func_020a199c @ 0x020a199c, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020a199c(int unused, const unsigned char *a, const unsigned char *b, int n)
{
    while (n != 0) {
        if (*a != *b) {
            return 0;
        }
        a++;
        b++;
        n--;
    }
    return 1;
}
