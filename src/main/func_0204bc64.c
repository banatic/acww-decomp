/* func_0204bc64 @ 0x0204bc64, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b42c(void);

int func_0204bc64(void)
{
    int result;
    result = func_0204b42c();
    result -= 0x3000;
    return result >> 2;
}
