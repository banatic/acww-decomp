/* func_ov100_0229d158 @ 0x0229d158, 0x3a bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d630(int a, int b);
extern int func_ov100_0229d620(int a, int b);
extern int func_ov100_0229d5d4(int a, int b);
extern int func_ov094_0229a69c(int a, int b);

int func_ov100_0229d158(int p1, int p2)
{
    if (func_ov100_0229d630(p1, p2) != 0 || func_ov100_0229d620(p1, p2) != 0) {
        int r = func_ov100_0229d5d4(p1, p2);
        return func_ov094_0229a69c(p1 + 0xcc, r);
    } else {
        return 1;
    }
}
