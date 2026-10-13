/* func_ov068_02266b6c @ 0x02266b6c, 0x3e bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_02266bac(int a, int b, int i, int c, int d);

int func_ov068_02266b6c(int a, int b, int *out, int c, int d)
{
    int i;
    int res;
    for (i = 0; i < 8; i++) {
        res = func_ov068_02266bac(a, b, i, c, d);
        if (res == -1) {
            continue;
        }
        *out = i;
        return res;
    }
    return -1;
}
