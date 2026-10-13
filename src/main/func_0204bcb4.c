/* func_0204bcb4 @ 0x0204bcb4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b42c(void);

int func_0204bcb4(void)
{
    int result;
    int value;

    value = func_0204b42c();
    if (value == 0x0000f031) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
