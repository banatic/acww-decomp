/* func_0209645c @ 0x0209645c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0209645c(unsigned char *out, unsigned int a, unsigned int b)
{
    *out = (unsigned char) (((b << 4) & 0x70) | (a & 0x0f));
}
