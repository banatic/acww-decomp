/* func_ov088_02278adc @ 0x02278adc, 0x20 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

int func_ov088_02278adc(int param1);

extern int func_02014868(int param1);

int func_ov088_02278adc(int param1)
{
    int result = 0;
    if (func_02014868(param1 + 0x618) == 0) {
        result = 1;
    }
    return result;
}
