/* func_ov003_022203dc @ 0x022203dc, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6598(void);
extern signed char data_ov003_0223666c[];

signed char func_ov003_022203dc(void)
{
    int index;
    signed char result;

    index = func_020b6598();
    result = data_ov003_0223666c[index];
    return result;
}
