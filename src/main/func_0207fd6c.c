/* func_0207fd6c @ 0x0207fd6c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0207fd6c(int unused, unsigned short *p)
{
    int flag = 0;
    unsigned short v = *p;
    if (v >= 0x12e8 && v <= 0x131f) {
        flag = 1;
    }
    if (flag) {
        return 1;
    }
    return 0;
}
