/* func_0204b1d8 @ 0x0204b1d8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204b1d8(unsigned short *ptr)
{
    int result = 0;
    if (*ptr >= 0x13a8 && *ptr <= 0x13c7) {
        result = 1;
    }
    if (result) {
        return 1;
    }
    return 0;
}
