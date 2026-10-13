/* func_0204c0d8 @ 0x0204c0d8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204c0d8(unsigned short *p)
{
    int flag = 0;
    if (*p >= 0x1188u && *p <= 0x11A7u) {
        flag = 1;
    }
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}
