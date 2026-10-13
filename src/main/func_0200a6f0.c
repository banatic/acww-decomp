/* func_0200a6f0 @ 0x0200a6f0, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0200a6f0(unsigned char *dest, unsigned int *src, unsigned char val)
{
    dest[1] = (unsigned char) src[0];
    dest[2] = (unsigned char) src[1];
    dest[0] = val;
}
