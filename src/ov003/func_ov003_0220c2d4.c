/* func_ov003_0220c2d4 @ 0x0220c2d4, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0220c29c(void *object);
extern int func_020edf70(int);

void func_ov003_0220c2d4(void)
{
    void *condition_value_0;
    condition_value_0 = (void *) (func_020edf70(0x154));
    if (condition_value_0 != 0) {
        func_ov003_0220c29c(condition_value_0);
    }
}
