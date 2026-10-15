/* func_ov100_0229d4f4 @ 0x0229d4f4, 0x5c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d630(unsigned char *a, int b);
extern int func_ov100_0229d620(unsigned char *a, int b);
extern int func_ov100_0229d118(unsigned char *a, int b);
extern int func_ov100_0229d0dc(unsigned char *a, int b);
extern void func_ov100_0229d4a8(unsigned char *a, int b, int c, int d);
extern void func_ov100_0229cd4c(unsigned char *a, int b);

int func_ov100_0229d4f4(unsigned char *a, int b)
{
    if (func_ov100_0229d630(a, b) != 0 || func_ov100_0229d620(a, b) != 0) {
        int v1 = func_ov100_0229d118(a, b);
        if (v1 != 0xFFF1) {
            int v2 = func_ov100_0229d0dc(a, b);
            func_ov100_0229d4a8(a, a[0x2920], v1, v2);
        }
        func_ov100_0229cd4c(a, b);
        return 1;
    }
    return 0;
}
