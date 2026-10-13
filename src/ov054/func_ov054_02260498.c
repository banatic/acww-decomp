/* func_ov054_02260498 @ 0x02260498, 0x38 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201a3e4(int);
extern int func_ov004_02225a14(void);

int func_ov054_02260498(int arg0)
{
    int val;
    int val2;

    val = func_0201a3e4(arg0 + 0x2ac);
    if (val == 0xba) {
        val2 = func_ov004_02225a14();
        if (val2 != 0) {
            val = *(int *) (*(int *) (arg0 + 0x698) + 4);
            if (val == 2) {
                return 1;
            }
        }
    }
    return 0;
}
