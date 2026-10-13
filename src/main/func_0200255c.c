/* func_0200255c @ 0x0200255c, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0200255c(int *src, int *dst, int n, int m)
{
    int outer;
    int k;
    int idx = 0;
    int rowbase = 0;

    for (outer = 0; outer < m; outer++) {
        int j;
        int pos = rowbase;
        for (j = 0; j < 8; j++) {
            int col = pos;
            for (k = 0; k < n; k++) {
                dst[col] = src[idx];
                idx++;
                col += 8;
            }
            pos++;
        }
        rowbase += n * 8;
    }
}
