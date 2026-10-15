/* func_ov068_02272f5c @ 0x02272f5c, 0x1c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020edf70(int);
extern void *func_ov068_02272f38(void *object);

void func_ov068_02272f5c(void)
{
    void *condition_value_21;
    condition_value_21 = (void *) (func_020edf70(0x2e8));
    if (condition_value_21 != 0) {
        func_ov068_02272f38(condition_value_21);
    }
}
