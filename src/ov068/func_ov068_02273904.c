/* func_ov068_02273904 @ 0x02273904, 0x1c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_02273860(void *object);
extern int func_020edf70(int);

void func_ov068_02273904(void)
{
    void *condition_value_22;
    condition_value_22 = (void *) (func_020edf70(0x5a4));
    if (condition_value_22 != 0) {
        func_ov068_02273860(condition_value_22);
    }
}
