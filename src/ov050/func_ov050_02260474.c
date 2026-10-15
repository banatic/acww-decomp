/* func_ov050_02260474 @ 0x02260474, 0x24 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov050_022604bc(int unused0);
extern int func_ov050_022609f0(int);

int func_ov050_02260474(int param)
{
    int result;
    if (func_ov050_022604bc(param) != 0) {
        func_ov050_022609f0(param);
        result = 0x4000;
    } else {
        result = 0x4000;
    }
    return result;
}
