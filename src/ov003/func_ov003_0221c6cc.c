/* func_ov003_0221c6cc @ 0x0221c6cc, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221c69c(void *object);
extern int func_020edf70(int);

void func_ov003_0221c6cc(void)
{
    void *condition_value_6;
    condition_value_6 = (void *) (func_020edf70(0x5a0));
    if (condition_value_6 != 0) {
        func_ov003_0221c69c(condition_value_6);
    }
}
