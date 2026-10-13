/* func_0200ac8c @ 0x0200ac8c, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_02077898(const unsigned char *);

void func_0200ac8c(const unsigned char *src, unsigned int *dst, unsigned short *dst2, unsigned char *dst3)
{
    dst[0] = src[3];
    dst[1] = src[4];
    *dst2 = func_02077898(src + 1);
    *dst3 = src[0];
}
