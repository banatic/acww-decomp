/* item_group_6: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204c358 @ 0x0204c358, 0x28 bytes, Thumb
 * func_0204c330 @ 0x0204c330, 0x28 bytes, Thumb
 */

extern int func_0204b42c(int param);

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

int func_0204c330(int param)
{
    if (func_0204c358((void *) param) != 0) {
        return func_0204b42c(param) - 0x12b0;
    } else {
        return -1;
    }
}
