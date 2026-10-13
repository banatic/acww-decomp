/* func_0204c3c8 @ 0x0204c3c8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0204c3c8(unsigned short *p)
{
    int flag = 0;
    unsigned short v = *p;
    if (v >= 0x12e8 && v <= 0x131f) {
        flag = 1;
    }
    return (flag != 0);
}
