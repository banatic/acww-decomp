/* func_0203eda4 @ 0x0203eda4, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203ed78(int param1, int param2);

int func_0203eda4(int param1)
{
    int result;

    if (func_0203ed78(param1, 1) != 0) {
        result = 0;
    } else if (func_0203ed78(param1, 2) != 0) {
        result = 1;
    } else {
        result = 2;
    }
    return result;
}
