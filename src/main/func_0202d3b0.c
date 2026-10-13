/* func_0202d3b0 @ 0x0202d3b0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0202d3b0(int val, int *ptr, int count)
{
    int i;
    if (ptr != 0) {
        for (i = 0; i < count; ptr++, i++) {
            if (*ptr == val) {
                return 1;
            }
        }
    }
    return 0;
}
