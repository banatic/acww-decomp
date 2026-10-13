/* func_ov106_0229d24c @ 0x0229d24c, 0x50 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d3a0(int a, int b);
extern int func_ov106_0229d390(int a, int b);
extern int func_ov106_0229d360(int a, int b);
extern void func_ov094_0229b8b4(int addr, int val, int c);
extern void func_ov106_0229d1b8(int a, int c);

void func_ov106_0229d24c(int a, int b, int c)
{
    if (func_ov106_0229d3a0(a, b) || func_ov106_0229d390(a, b)) {
        int t = func_ov106_0229d360(a, b);
        func_ov094_0229b8b4(a + 0xb58, t, c);
        if (func_ov106_0229d3a0(a, b)) {
            func_ov106_0229d1b8(a, c);
        }
    }
}
