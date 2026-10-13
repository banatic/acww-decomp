/* func_02077a54 @ 0x02077a54, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02077a54(unsigned char *out, unsigned char a, unsigned char b)
{
    *out = ((b << 6) & 0xC0) | (a & 0x3F);
}
