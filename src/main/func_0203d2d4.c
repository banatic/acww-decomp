/* func_0203d2d4 @ 0x0203d2d4, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0203d2d4(unsigned char *p, unsigned int value)
{
    *p = (*p & ~0x0C) | (((unsigned char) value & 3) << 2);
}
