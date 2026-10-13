/* func_ov101_0229cc50 @ 0x0229cc50, 0x2e bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229ce38(void *a, int b);
extern int func_ov101_0229ce1c(void *a, int b);
extern int func_ov094_0229a8bc(char *a, int b);

int func_ov101_0229cc50(void *a, int b)
{
    if (func_ov101_0229ce38(a, b)) {
        int r = func_ov101_0229ce1c(a, b);
        return func_ov094_0229a8bc((char *) a + 0xf4, r);
    }
    return 0;
}
