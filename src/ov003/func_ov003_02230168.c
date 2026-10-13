/* func_ov003_02230168 @ 0x02230168, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int size);
extern void func_ov003_02230120(void);

void func_ov003_02230168(void)
{
    if (func_020edf70(0xa0) != 0) {
        func_ov003_02230120();
    }
}
