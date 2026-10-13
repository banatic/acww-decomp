/* func_ov101_0229cd08 @ 0x0229cd08, 0x36 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229ce38(void);
extern int func_ov101_0229ce1c(void *, int);
extern int func_ov094_0229aba4(void *, int);

int func_ov101_0229cd08(void *p, int n)
{
    if (func_ov101_0229ce38()) {
        int tmp = func_ov101_0229ce1c(p, n);
        p = (void *) ((char *) p + 0xf4);
        return func_ov094_0229aba4(p, tmp);
    } else {
        if (n == 0xf) {
            return 0xbc;
        } else {
            return 0;
        }
    }
}
