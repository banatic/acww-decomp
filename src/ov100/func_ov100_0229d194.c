/* func_ov100_0229d194 @ 0x0229d194, 0x3a bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d630(char *a, int b);
extern int func_ov100_0229d620(char *a, int b);
extern int func_ov100_0229d5d4(char *a, int b);
extern int func_ov094_0229a8bc(char *a, int b);

int func_ov100_0229d194(char *a, int b)
{
    if (func_ov100_0229d630(a, b) || func_ov100_0229d620(a, b)) {
        int r = func_ov100_0229d5d4(a, b);
        return func_ov094_0229a8bc(a + 0xcc, r);
    } else {
        return 0;
    }
}
