/* func_02090000 @ 0x02090000, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02065ec0(void);

int func_02090000(void)
{
    int result;
    if (func_02065ec0() != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
