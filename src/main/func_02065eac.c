/* func_02065eac @ 0x02065eac, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02065eac(unsigned char *p, unsigned char x)
{
    *(p + 0xfa) = (*(p + 0xfa) & 0xc0) | x;
}
