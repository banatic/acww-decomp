/* func_ov101_0229cbbc @ 0x0229cbbc, 0x2e bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229ce38(void *a, int b);
extern int func_ov101_0229ce1c(void *a, int b);
extern int func_ov094_0229aa84(char *addr, int val);

int func_ov101_0229cbbc(void *a, int b)
{
    if (func_ov101_0229ce38(a, b)) {
        return func_ov094_0229aa84((char *) a + 0xf4, func_ov101_0229ce1c(a, b));
    } else {
        return 0xf1;
    }
}
