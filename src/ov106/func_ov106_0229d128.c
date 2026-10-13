/* func_ov106_0229d128 @ 0x0229d128, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d3a0(int a, int b);
extern int func_ov106_0229d390(int a, int b);
extern int func_ov106_0229d360(int a, int b);
extern int func_ov094_0229b328(int a, int b);

int func_ov106_0229d128(int a, int b)
{
    if (func_ov106_0229d3a0(a, b) != 0 || func_ov106_0229d390(a, b) != 0) {
        return func_ov094_0229b328(a + 0xb58, func_ov106_0229d360(a, b)) - 0x10;
    } else {
        if (b == 31) {
            return 0xb6;
        } else {
            return 0;
        }
    }
}
