/* func_020b6774 @ 0x020b6774, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020b6774(unsigned int param)
{
    if (param >= 0x1a && param <= 0x1f) {
        return param - 0x1a;
    } else {
        return -1;
    }
}
