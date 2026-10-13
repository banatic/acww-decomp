/* func_0200bdb0 @ 0x0200bdb0, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0200bdb0(unsigned char *dst, const unsigned int *src, unsigned int val)
{
    *dst = (unsigned char) *src;
    *(dst + 1) = (unsigned char) *(src + 1);
    *(unsigned int *) (dst + 4) = val;
}
