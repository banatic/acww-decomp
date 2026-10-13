/* func_02077b3c @ 0x02077b3c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02077b3c(unsigned char *out, int a, int b)
{
    *out = (unsigned char) (((b & 0x1F) << 2) | 0x80 | (a & 3));
}
