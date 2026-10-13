/* func_0204c7c8 @ 0x0204c7c8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204c7c8(unsigned short *p)
{
    unsigned short val;
    int flag;

    flag = 0;
    val = *p;
    if (val >= 0x1492 && val <= 0x14fd) {
        flag = 1;
    }
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}
