/* func_02037470 @ 0x02037470, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020374ac(void *);

void func_02037470(void *dst, const void *src)
{
    func_020374ac(dst);
    *(unsigned int *) ((char *) dst + 0) = *(const unsigned int *) ((const char *) src + 0);
    *(unsigned short *) ((char *) dst + 4) = *(const unsigned short *) ((const char *) src + 4);
    *(unsigned int *) ((char *) dst + 8) = *(const unsigned int *) ((const char *) src + 8);
    *(unsigned int *) ((char *) dst + 0xc) = *(const unsigned int *) ((const char *) src + 0xc);
    *(unsigned char *) ((char *) dst + 0x10) = *(const unsigned char *) ((const char *) src + 0x10);
    *(unsigned char *) ((char *) dst + 0x11) = *(const unsigned char *) ((const char *) src + 0x11);
    *(unsigned char *) ((char *) dst + 0x12) = *(const unsigned char *) ((const char *) src + 0x12);
    *(unsigned char *) ((char *) dst + 0x13) = *(const unsigned char *) ((const char *) src + 0x13);
    *(unsigned char *) ((char *) dst + 0x14) = *(const unsigned char *) ((const char *) src + 0x14);
    *(unsigned int *) ((char *) dst + 0x18) = *(const unsigned int *) ((const char *) src + 0x18);
}
