/* func_020609bc @ 0x020609bc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020609bc(unsigned char *bitmap, unsigned int bit_index)
{
    if (bit_index < 0x46) {
        unsigned int byte_index = bit_index >> 3;
        unsigned char value = bitmap[byte_index];
        value &= ~(1 << (bit_index & 7));
        bitmap[byte_index] = value;
    }
}
