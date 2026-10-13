/* func_0204c358 @ 0x0204c358, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204c358(void *arg0)
{
    unsigned short value;
    int flag;

    flag = 0;
    value = *(unsigned short *) arg0;
    if (value >= 0x12b0u && value <= 0x12e7u) {
        flag = 1;
    }
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}
