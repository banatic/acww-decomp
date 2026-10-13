/* func_0204b238 @ 0x0204b238, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204b238(unsigned short *p)
{
    int result;
    result = 0;
    if (*p >= 0x1380 && *p <= 0x139f) {
        result = 1;
    }
    if (result) {
        return 1;
    }
    return 0;
}
