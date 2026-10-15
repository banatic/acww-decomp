/* func_ov003_0221fe10 @ 0x0221fe10, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221fd60(void *object);
extern int func_020edf70(int);

void func_ov003_0221fe10(void)
{
    void *condition_value_17;
    condition_value_17 = (void *) (func_020edf70(0x31c));
    if (condition_value_17 != 0) {
        func_ov003_0221fd60(condition_value_17);
    }
}
