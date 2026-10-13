/* func_ov100_0229d014 @ 0x0229d014, 0x36 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d630(char *a, int b);
extern int func_ov100_0229d620(char *a, int b);
extern int func_ov100_0229d5d4(char *a, int b);
extern void func_ov094_0229aafc(char *a, int b);

void func_ov100_0229d014(char *a, int b)
{
    if (func_ov100_0229d630(a, b) || func_ov100_0229d620(a, b)) {
        func_ov094_0229aafc(a + 0xcc, func_ov100_0229d5d4(a, b));
    }
}
