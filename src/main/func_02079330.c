/* func_02079330 @ 0x02079330, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020793b4(int);

int func_02079330(int param1, int param2)
{
    int result;
    int temp;

    result = 0;
    temp = param2;
    if (func_020793b4(temp) != 0) {
        result = param1 + (param2 * 0x2c);
    }
    return result;
}
