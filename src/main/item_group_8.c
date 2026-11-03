/* item_group_8: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204c614 @ 0x0204c614, 0x28 bytes, Thumb
 * func_0204c5ec @ 0x0204c5ec, 0x28 bytes, Thumb
 * func_0204c5c4 @ 0x0204c5c4, 0x28 bytes, Thumb
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

int func_0204c5ec(const unsigned short *arg0)
{
    int ret = 0;
    if (arg0[0] >= 0x45dcu && arg0[0] <= 0x47d7u) {
        ret = 1;
    }
    if (ret) {
        return 1;
    }
    return 0;
}

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
