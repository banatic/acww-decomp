/* func_0204ca64 @ 0x0204ca64, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204ca64(unsigned short *param)
{
    int flag = 0;
    if (*param >= 0x1518 && *param <= 0x151C) {
        flag = 1;
    }
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}
