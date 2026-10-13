/* func_02051bb4 @ 0x02051bb4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051ca8(const unsigned short *a, int b);

int func_02051bb4(const unsigned short *a, const unsigned short *b, int c)
{
    int len1;
    int len2;
    int i;

    len1 = func_02051ca8(a, c);
    len2 = func_02051ca8(b, c);
    if (len1 != len2) {
        return 0;
    }
    for (i = 0; i < len1; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}
