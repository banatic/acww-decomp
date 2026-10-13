/* func_02065ef4 @ 0x02065ef4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02065ef4(unsigned char *base, unsigned int value)
{
    unsigned char *p = base + 0xFA;
    *p = (*p & 0x3F) | (value << 6);
}
