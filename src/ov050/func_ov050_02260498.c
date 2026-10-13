/* func_ov050_02260498 @ 0x02260498, 0x24 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov050_022604bc(void);
extern int func_ov050_022609f0(int);

int func_ov050_02260498(int param)
{
    int result;
    int r4;
    r4 = param;
    if (func_ov050_022604bc() != 0) {
        func_ov050_022609f0(r4);
        result = 0x3000;
    } else {
        result = 0x3000;
    }
    return result;
}
