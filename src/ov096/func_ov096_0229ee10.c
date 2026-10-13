/* func_ov096_0229ee10 @ 0x0229ee10, 0x28 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229e170(int, int);

int func_ov096_0229ee10(int param1, int param2)
{
    int result;
    int ret;

    if (param2 == 2) {
        result = 0;
    } else if (param2 == 0) {
        result = 1;
    } else if (param2 == 1) {
        ret = func_ov096_0229e170(param1, 0);
        result = ret;
    } else {
        result = 0;
    }
    return result;
}
