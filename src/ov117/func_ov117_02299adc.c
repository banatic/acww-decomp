/* func_ov117_02299adc @ 0x02299adc, 0x2a bytes, Thumb, module ov117
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov117_02299aa4(void *a, unsigned int i, unsigned int mask);
extern void func_ov117_02299b40(void *a, int i, int mask);
extern void *data_020da1a8;

void func_ov117_02299adc(int a, int b)
{
    unsigned int i = 0;
    unsigned int mask = b & 3;
    for (; i < 4; i++) {
        func_ov117_02299b40(func_ov117_02299aa4((void *) a, i, mask), i, mask);
    }
}
