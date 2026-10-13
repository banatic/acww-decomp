/* func_02099834 @ 0x02099834, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02099834(unsigned char *base, unsigned int value)
{
    base[0x243c] = (unsigned char) ((base[0x243c] & ~0x0f) | (value & 0x0f));
}
