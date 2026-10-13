/* func_ov107_0229d31c @ 0x0229d31c, 0x40 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229aee8(int);
extern int func_ov094_0229a69c(int, int);
extern int func_ov107_0229d35c(int, int);

int func_ov107_0229d31c(int a, int b, int c, int d)
{
    int r6;

    r6 = func_ov094_0229aee8(a + 0x10c);
    if (r6 == 0x23) {
        goto ret10;
    }
    if (d == 0) {
        goto call3;
    }
    if (func_ov094_0229a69c(a + 0x10c, r6) == 0) {
        goto call3;
    }
    return 0x10;

call3:
    return func_ov107_0229d35c(a, r6);

ret10:
    return 0x10;
}
