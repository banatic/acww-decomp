/* func_ov074_02278adc @ 0x02278adc, 0x1a bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203cfa8(unsigned int *data);

int func_ov074_02278adc(void *arg)
{
    int result = 0;
    unsigned int *data;
    if ((data = *(unsigned int **) arg) != 0) {
        result = func_0203cfa8(data);
    }
    return result;
}
