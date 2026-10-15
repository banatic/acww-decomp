/* func_ov003_0221edf4 @ 0x0221edf4, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221edd0(void *object);
extern int func_020edf70(int);

void func_ov003_0221edf4(void)
{
    void *condition_value_16;
    condition_value_16 = (void *) (func_020edf70(0x2b8));
    if (condition_value_16 != 0) {
        func_ov003_0221edd0(condition_value_16);
    }
}
