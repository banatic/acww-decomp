/* state_flags_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206fe60 @ 0x0206fe60, 0x1a bytes, Thumb
 * func_0206fe54 @ 0x0206fe54, 0xc bytes, Thumb
 */

extern int func_0206fec8(int);

int func_0206fe60(void)
{
    int result;
    if (func_0206fec8(2) == 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_0206fe54(void)
{
    return func_0206fec8(2);
}
