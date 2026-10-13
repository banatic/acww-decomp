/* func_0207ec50 @ 0x0207ec50, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207af30(void);

int func_0207ec50(void)
{
    int result;
    if (func_0207af30() == 0xb) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}
