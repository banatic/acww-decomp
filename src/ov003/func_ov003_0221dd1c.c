/* func_ov003_0221dd1c @ 0x0221dd1c, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02220174(int);
extern void func_ov009_022632c8(void *object);

int func_ov003_0221dd1c(void)
{
    void *condition_value_12;
    condition_value_12 = (void *) (func_ov003_02220174(0x501d));
    if (condition_value_12 != 0) {
        func_ov009_022632c8(condition_value_12);
    }
    return 1;
}
