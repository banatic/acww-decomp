/* func_02097edc @ 0x02097edc, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02097edc(unsigned char *base, int bit)
{
    unsigned char *ptr;
    int byte_index;
    int bit_mask;

    ptr = base + 0x100;
    byte_index = bit >> 3;
    bit_mask = 1 << (bit & 7);
    ptr[byte_index] |= bit_mask;
}
