/* func_ov003_0221c250 @ 0x0221c250, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221c22c(void *object);
extern int func_020edf70(int);

void func_ov003_0221c250(void)
{
    void *condition_value_4;
    condition_value_4 = (void *) (func_020edf70(0x2bc));
    if (condition_value_4 != 0) {
        func_ov003_0221c22c(condition_value_4);
    }
}
