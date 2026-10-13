/* func_0204b328 @ 0x0204b328, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204b328(unsigned short *p)
{
    unsigned short value;
    int flag;

    flag = 0;
    value = *p;
    if (value >= 0x13c8u && value <= 0x1407u) {
        flag = 1;
    }
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}
