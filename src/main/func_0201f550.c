/* func_0201f550 @ 0x0201f550, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0201f550(unsigned short *p)
{
    int ret;
    unsigned int value;
    ret = 0;
    value = *p;
    if (value >= 0x1542 && value <= 0x1546) {
        ret = 1;
    }
    return ret;
}
