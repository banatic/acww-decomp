/* func_ov004_0222ac74 @ 0x0222ac74, 0xc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void func_ov004_0222ac74(unsigned char *dst, const unsigned int *src, unsigned int val)
{
    *dst = (unsigned char) *src;
    *(dst + 1) = (unsigned char) *(src + 1);
    *(unsigned int *) (dst + 4) = val;
}
