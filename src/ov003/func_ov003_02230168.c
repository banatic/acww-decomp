/* func_ov003_02230168 @ 0x02230168, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int size);
extern void *func_ov003_02230120(void *object);

void func_ov003_02230168(void)
{
    void *condition_value_18;
    condition_value_18 = (void *) (func_020edf70(0xa0));
    if (condition_value_18 != 0) {
        func_ov003_02230120(condition_value_18);
    }
}
