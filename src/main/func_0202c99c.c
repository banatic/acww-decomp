/* func_0202c99c @ 0x0202c99c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0202c99c(int target, const signed char *s, int n)
{
    int i = 0;
    int offset = 0;
    while (i < n) {
        int ch = s[offset];
        if (ch == target) {
            return target;
        }
        s++;
        i++;
    }
    return -1;
}
