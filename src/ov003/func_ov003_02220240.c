/* func_ov003_02220240 @ 0x02220240, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02220150(void);
extern int data_ov003_0223cef0[];

int func_ov003_02220240(void)
{
    int result;
    int i;
    int val;

    result = func_ov003_02220150();
    i = 0;
    val = -1;
    if (result != val) {
        data_ov003_0223cef0[result] = i;
        return 1;
    }
    return i;
}
