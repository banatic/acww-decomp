/* func_0202eb94 @ 0x0202eb94, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned short func_0202eb94(const void *ptr)
{
    unsigned short value = *(const unsigned short *) ((const char *) ptr + 0xEA);
    if (((value & 0xF000) >> 12) == 0xD) {
        return (unsigned short) ((value & 0xFFF) + 0xC8);
    } else {
        return 0xFFFF;
    }
}
