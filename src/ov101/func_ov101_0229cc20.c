/* func_ov101_0229cc20 @ 0x0229cc20, 0x2e bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229ce38(char *a, int b);
extern int func_ov101_0229ce1c(char *a, int b);
extern int func_ov094_0229a69c(char *a, int b);

int func_ov101_0229cc20(char *a, int b)
{
    if (func_ov101_0229ce38(a, b)) {
        return func_ov094_0229a69c(a + 0xf4, func_ov101_0229ce1c(a, b));
    }
    return 1;
}
