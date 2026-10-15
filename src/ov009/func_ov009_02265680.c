/* func_ov009_02265680 @ 0x02265680, 0x1c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov009_022654c0(void *object);
extern int func_020edf70(int);

void func_ov009_02265680(void)
{
    void *condition_value_19;
    condition_value_19 = (void *) (func_020edf70(0x2b4));
    if (condition_value_19 != 0) {
        func_ov009_022654c0(condition_value_19);
    }
}
