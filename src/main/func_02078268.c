/* func_02078268 @ 0x02078268, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02078268(unsigned char *ptr, int bit)
{
    if (bit < 0 || bit >= 4) {
        return 1;
    }
    return (ptr[0xc3] & (1 << bit)) ? 1 : 0;
}
