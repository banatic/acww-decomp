/* func_ov101_0229cdd0 @ 0x0229cdd0, 0x3a bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229aee8(int);
extern int func_ov094_0229a69c(int, int);
extern int func_ov101_0229ce0c(int, int);

int func_ov101_0229cdd0(int a, int b, int c, int d)
{
    int v;

    v = func_ov094_0229aee8(a + 0xf4);
    if (v == 0x23) {
        goto ret10;
    }
    if (d && func_ov094_0229a69c(a + 0xf4, v) != 0) {
        return 0x10;
    }
    return func_ov101_0229ce0c(a, v);
ret10:
    return 0x10;
}
