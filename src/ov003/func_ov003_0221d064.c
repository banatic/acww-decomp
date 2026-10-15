/* func_ov003_0221d064 @ 0x0221d064, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221ca9c(int);
extern void *func_ov003_0221cb30(void *object);

void func_ov003_0221d064(void)
{
    void *condition_value_7;
    condition_value_7 = (void *) (func_ov003_0221ca9c(0x2dc));
    if (condition_value_7 != 0) {
        func_ov003_0221cb30(condition_value_7);
    }
}
