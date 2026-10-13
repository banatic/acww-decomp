/* func_02084d9c @ 0x02084d9c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02084d9c(int unused, unsigned char *data)
{
    int result = 0;
    unsigned char v = data[0xf];
    if (v > 0 && v < 5) {
        result = 1;
    }
    return result;
}
