/* func_ov106_0229d170 @ 0x0229d170, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d3a0(void *p, int n);
extern int func_ov106_0229d390(void *p, int n);
extern int func_ov106_0229d360(void *p, int n);
extern int func_ov094_0229b384(void *p, int n);

int func_ov106_0229d170(void *p, int n)
{
    if (!(func_ov106_0229d3a0(p, n) == 0 && func_ov106_0229d390(p, n) == 0)) {
        return func_ov094_0229b384((char *) p + 0xb58, func_ov106_0229d360(p, n));
    }

    if (n == 0x1f) {
        return 0xbc;
    }
    return 0;
}
