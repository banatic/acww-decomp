/* func_ov106_0229d0d0 @ 0x0229d0d0, 0x34 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d3a0(int, int);
extern int func_ov106_0229d360(int, int);
extern int func_ov094_0229b788(int, int);

int func_ov106_0229d0d0(int a0, int a1)
{
    if (func_ov106_0229d3a0(a0, a1)) {
        return func_ov094_0229b788(a0 + 0xb58, func_ov106_0229d360(a0, a1));
    }
    return 0;
}
