/* func_ov052_0226118c @ 0x0226118c, 0x1e bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

int func_ov052_0226118c(int unused, const unsigned char *s, int n)
{
    int count = 0;
    int i = count;
    while (i < n) {
        if (*s == 0) {
            count++;
        }
        s++;
        i++;
    }
    return count;
}
