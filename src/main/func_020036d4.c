/* func_020036d4 @ 0x020036d4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned int func_020036d4(unsigned int x)
{
    unsigned int ret;
    ret = 2;
    if (x < 3) {
        ret = 0;
    } else if (x < 6) {
        ret = 1;
    }
    return ret;
}
