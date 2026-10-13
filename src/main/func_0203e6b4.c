/* func_0203e6b4 @ 0x0203e6b4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095bdc(void);

int func_0203e6b4(void)
{
    int result;
    if (func_02095bdc() != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
