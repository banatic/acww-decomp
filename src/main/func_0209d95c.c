/* func_0209d95c @ 0x0209d95c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0209d95c(const unsigned char *data, int shift)
{
    if ((data[0] >> (shift & 3)) & 1) {
        return 1;
    } else {
        return 0;
    }
}
