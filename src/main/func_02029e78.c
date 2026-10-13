/* func_02029e78 @ 0x02029e78, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02029e78(unsigned short *p)
{
    int flag;

    flag = 0;
    if (*p >= 0x11a8 && *p <= 0x12a7) {
        flag = 1;
    }
    if (flag) {
        return 1;
    }
    return 0;
}
