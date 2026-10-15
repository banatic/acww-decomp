/* func_ov003_0221da10 @ 0x0221da10, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221d9c0(void *object);
extern int func_020edf70(int);

void func_ov003_0221da10(void)
{
    void *condition_value_10;
    condition_value_10 = (void *) (func_020edf70(0x38c));
    if (condition_value_10 != 0) {
        func_ov003_0221d9c0(condition_value_10);
    }
}
