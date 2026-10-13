/* func_020025c4 @ 0x020025c4, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020025c4(int *src, int *dst, int n, int innerCount, int outerCount)
{
    int idx = 0;
    int outer;
    int k;
    int rowbase = n * 8;

    for (outer = 0; outer < outerCount; outer++) {
        int j;
        int pos = rowbase;
        for (j = 0; j < 8; j++) {
            int col = pos;
            for (k = 0; k < innerCount; k++) {
                dst[col] = src[idx];
                idx++;
                col += 8;
            }
            pos++;
        }
        rowbase += 0x100;
    }
}
