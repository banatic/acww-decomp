/* func_ov078_02278ae0 @ 0x02278ae0, 0x20 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(int);

int func_ov078_02278ae0(int param)
{
    int result;
    int flag = 0;

    result = func_02014868(param + 0x618);
    if (result == 0) {
        flag = 1;
    }
    return flag;
}
