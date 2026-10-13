/* func_02009484 @ 0x02009484, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02009484(unsigned char *src, unsigned char *dst1, unsigned char *dst2, unsigned char *dst3)
{
    *dst1 = *src;
    *dst2 = src[1];
    *dst3 = src[2];
}
