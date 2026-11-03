/* item_group_7: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204c3c8 @ 0x0204c3c8, 0x28 bytes, Thumb
 * func_0204c3a0 @ 0x0204c3a0, 0x28 bytes, Thumb
 */

extern int func_0204b42c(int param);

int func_0204c3c8(unsigned short *p)
{
    int flag = 0;
    unsigned short v = *p;
    if (v >= 0x12e8 && v <= 0x131f) {
        flag = 1;
    }
    return (flag != 0);
}

int func_0204c3a0(int param)
{
    int result;
    int temp;

    if (func_0204c3c8((unsigned short *) param) != 0) {
        temp = func_0204b42c(param);
        result = temp - 0x12e8;
    } else {
        result = -1;
    }
    return result;
}
