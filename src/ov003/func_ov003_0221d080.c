/* func_ov003_0221d080 @ 0x0221d080, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221cfc0(void *object);
extern int func_020edf70(int);

void func_ov003_0221d080(void)
{
    void *condition_value_8;
    condition_value_8 = (void *) (func_020edf70(0x2f0));
    if (condition_value_8 != 0) {
        func_ov003_0221cfc0(condition_value_8);
    }
}
