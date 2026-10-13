/* func_ov117_02299adc @ 0x02299adc, 0x2a bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov117_02299aa4(int a, unsigned int i, int mask);
extern int func_ov117_02299b40(int a, unsigned int i, int mask);

int func_ov117_02299adc(int a, int b)
{
    unsigned int i = 0;
    int mask = 3 & b;
    int result;
    for (; i < 4; i++) {
        result = func_ov117_02299b40(func_ov117_02299aa4(a, i, mask), i, mask);
    }
    return result;
}
