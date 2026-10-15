/* func_ov050_02260718 @ 0x02260718, 0x20 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov050_02260738(void *argument0);
extern int func_0203e0a8(int, int);

int func_ov050_02260718(int param)
{
    int result;
    if (func_ov050_02260738((void *) param) != 0) {
        func_0203e0a8(param, 0);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
