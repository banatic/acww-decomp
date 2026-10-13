/* func_0204c5c4 @ 0x0204c5c4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204c5c4(unsigned short *p)
{
    int flag = 0;
    unsigned short v = *p;
    if (v >= 0x3894 && v <= 0x38e3) {
        flag = 1;
    }
    if (flag) {
        return 1;
    }
    return 0;
}
