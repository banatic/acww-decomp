/* func_0206fbc0 @ 0x0206fbc0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02070094(void);

int func_0206fbc0(void)
{
    int result;
    if (func_02070094() != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
