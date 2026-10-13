/* func_ov100_0229d6d8 @ 0x0229d6d8, 0x44 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d620(void);
extern int func_ov100_0229d67c(int);
extern int func_ov100_0229d630(void);
extern int func_ov100_0229d648(int);
extern void func_ov100_0229d71c(int, int, int);

void func_ov100_0229d6d8(int a, int b, int c)
{
    int r4 = 0x20;
    int r6 = b;
    int r5 = a;

    if (c >= 0x6c) {
        if (func_ov100_0229d620()) {
            r4 = func_ov100_0229d67c(r5);
        }
    } else {
        if (func_ov100_0229d630()) {
            r4 = func_ov100_0229d648(r5);
        }
    }

    if (r4 != 0x20) {
        r6 = r4;
    }

    func_ov100_0229d71c(r5, r6, 4);
}
