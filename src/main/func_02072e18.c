/* func_02072e18 @ 0x02072e18, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02072e18(unsigned char *buf, int val)
{
    buf[0x32] = (buf[0x32] & ~0xF) | ((unsigned char) val & 0x0F);
}
