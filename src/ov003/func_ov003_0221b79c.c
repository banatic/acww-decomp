/* func_ov003_0221b79c @ 0x0221b79c, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221b5c0(int);
extern void *func_ov003_0221b6d4(void *object);

void func_ov003_0221b79c(void)
{
    void *condition_value_2;
    condition_value_2 = (void *) (func_ov003_0221b5c0(0x3a4));
    if (condition_value_2 != 0) {
        func_ov003_0221b6d4(condition_value_2);
    }
}
