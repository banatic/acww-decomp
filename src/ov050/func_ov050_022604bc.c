/* func_ov050_022604bc @ 0x022604bc, 0x22 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov050_022604e0(int);
extern int func_ov050_022604f8(int);

int func_ov050_022604bc(int arg)
{
    if (func_ov050_022604e0(arg) || func_ov050_022604f8(arg)) {
        return 1;
    }
    return 0;
}
