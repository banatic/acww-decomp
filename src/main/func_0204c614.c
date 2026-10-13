/* func_0204c614 @ 0x0204c614, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204c614(unsigned short *p)
{
    unsigned short val;
    int flag;

    flag = 0;
    val = *p;
    if (val >= 0x450c && val <= 0x45db) {
        flag = 1;
    }
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}
