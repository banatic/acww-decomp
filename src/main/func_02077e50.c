/* func_02077e50 @ 0x02077e50, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020eb04c(void);

int func_02077e50(void)
{
    int result;
    if (func_020eb04c() != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
