/* func_0204b208 @ 0x0204b208, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204b208(unsigned short *p)
{
    int flag = 0;
    unsigned int val = *p;
    if (val >= 0x1100 && val <= 0x1143) {
        flag = 1;
    }
    if (flag) {
        return 1;
    }
    return 0;
}
