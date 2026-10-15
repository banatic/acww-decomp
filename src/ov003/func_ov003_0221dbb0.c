/* func_ov003_0221dbb0 @ 0x0221dbb0, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221db54(void *object);
extern int func_020edf70(int);

void func_ov003_0221dbb0(void)
{
    void *condition_value_11;
    condition_value_11 = (void *) (func_020edf70(0x2b8));
    if (condition_value_11 != 0) {
        func_ov003_0221db54(condition_value_11);
    }
}
