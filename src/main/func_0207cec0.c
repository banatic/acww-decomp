/* func_0207cec0 @ 0x0207cec0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf74(int);

int func_0207cec0(int param1, int param2)
{
    int result;
    int temp;

    result = 0;
    temp = param2;

    if (func_0207cf74(temp) != 0) {
        result = param1 + (param2 * 0x7ec);
    }

    return result;
}
