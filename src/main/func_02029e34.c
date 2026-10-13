/* func_02029e34 @ 0x02029e34, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02029e34(unsigned short *p)
{
    int flag = 0;
    if ((*p >= 0x450cu) && (*p <= 0x45dbu)) {
        flag = 1;
    }
    if (flag) {
        return 1;
    }
    return 0;
}
