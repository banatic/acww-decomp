/* func_ov003_0221d254 @ 0x0221d254, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov003_0221d230(void *object);
extern int func_020edf70(int);

void func_ov003_0221d254(void)
{
    void *condition_value_9;
    condition_value_9 = (void *) (func_020edf70(0x2b8));
    if (condition_value_9 != 0) {
        func_ov003_0221d230(condition_value_9);
    }
}
