/* func_0204b2c8 @ 0x0204b2c8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204b2c8(unsigned short *ptr)
{
    int flag;
    flag = 0;
    if (*ptr >= 0x11a8 && *ptr <= 0x12a7) {
        flag = 1;
    }
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}
