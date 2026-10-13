/* func_ov003_022119d8 @ 0x022119d8, 0x18 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022119d8(void *dst, const void *src, unsigned short a, unsigned char b);

void func_ov003_022119d8(void *dst, const void *src, unsigned short a, unsigned char b)
{
    *(unsigned int *) dst = *(const unsigned int *) src;
    *(unsigned int *) ((char *) dst + 4) = *(const unsigned int *) ((const char *) src + 4);
    *(unsigned int *) ((char *) dst + 8) = *(const unsigned int *) ((const char *) src + 8);
    *(unsigned short *) ((char *) dst + 0xc) = a;
    *(unsigned char *) ((char *) dst + 0xe) = b;
}
