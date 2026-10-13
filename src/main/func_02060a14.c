/* func_02060a14 @ 0x02060a14, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02060a14(unsigned char *array, unsigned int bit)
{
    if (bit < 70) {
        array[bit >> 3] |= 1 << (bit & 7);
    }
}
