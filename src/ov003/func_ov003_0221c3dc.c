/* func_ov003_0221c3dc @ 0x0221c3dc, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221c3b8(void *object);
extern int func_020edf70(int);

void func_ov003_0221c3dc(void)
{
    void *condition_value_5;
    condition_value_5 = (void *) (func_020edf70(0x2b4));
    if (condition_value_5 != 0) {
        func_ov003_0221c3b8(condition_value_5);
    }
}
