/* func_020b671c @ 0x020b671c, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020b671c(unsigned int c)
{
    if (c >= 0x20 && c <= 0x29) {
        return c - 0x20;
    } else {
        return -1;
    }
}
