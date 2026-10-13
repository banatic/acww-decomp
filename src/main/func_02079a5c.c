/* func_02079a5c @ 0x02079a5c, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02080890(int);

int func_02079a5c(int param1, int param2, int param3)
{
    int result;
    int val;
    int val2;

    val = func_02080890(param2);
    val2 = func_02080890(param3);
    result = 0;
    if (val != 0 && val2 != 0) {
        result = 0x3f;
    }
    return result;
}
