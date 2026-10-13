/* func_02077e38 @ 0x02077e38, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eb04c(void);

int func_02077e38(void)
{
    int result;
    if (func_020eb04c() == 2) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
