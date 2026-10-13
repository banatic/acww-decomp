/* func_ov088_0227913c @ 0x0227913c, 0x1e bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

int func_ov088_0227913c(int unused, unsigned char *p, int n)
{
    int c = 0;
    int i = 0;
    while (i < n) {
        if (*p == 0) {
            c++;
        }
        p++;
        i++;
    }
    return c;
}
