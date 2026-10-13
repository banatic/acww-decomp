/* func_ov004_0224632c @ 0x0224632c, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

// The row base is computed inside the inner loop.
extern long *func_ov004_022468b0(void);
int func_ov004_0224632c(int a, int b)
{
    long *base = func_ov004_022468b0();
    int n = 0, y, x;
    long *row;
    for (y = 0; y < 0x10; y++) {
        for (x = 0; x < 0x10; x++) {
            row = (long *) ((char *) base + y * 0x40);
            if (row[x] == 0x22) {
                if (x == a && y == b) {
                    return n;
                }
                n++;
            }
        }
    }
    return -1;
}
