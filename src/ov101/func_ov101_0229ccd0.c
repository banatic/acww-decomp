/* func_ov101_0229ccd0 @ 0x0229ccd0, 0x38 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229ce38(void);
extern int func_ov101_0229ce1c(int, int);
extern int func_ov094_0229ab90(int, int);

int func_ov101_0229ccd0(int a, int b)
{
    int result;
    if (func_ov101_0229ce38()) {
        result = func_ov094_0229ab90(a + 0xf4, func_ov101_0229ce1c(a, b)) - 0x10;
    } else if (b == 0xf) {
        result = 0xb6;
    } else {
        result = 0;
    }
    return result;
}
