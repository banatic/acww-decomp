/* func_02090140 @ 0x02090140, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02090140(unsigned char *addr, unsigned int value)
{
    addr[0x939] = (addr[0x939] & ~1) | (value & 1);
}
