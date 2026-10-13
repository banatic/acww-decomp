/* func_0204bd08 @ 0x0204bd08, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcf8(void);

int func_0204bd08(void)
{
    int result;
    if (func_0204bcf8() == 1) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
