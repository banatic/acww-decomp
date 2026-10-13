/* func_02097cbc @ 0x02097cbc, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02097cbc(unsigned char *p, unsigned char value)
{
    value |= (p[3] & 0x80);
    p[3] = value;
}
