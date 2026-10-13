/* func_02078a0c @ 0x02078a0c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02078a0c(unsigned char *p, int a, int b)
{
    *p = (unsigned char) (((a << 4) & 0xF0) | (b & 0x0F));
}
