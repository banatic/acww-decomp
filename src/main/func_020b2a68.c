/* func_020b2a68 @ 0x020b2a68, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020b2a68(void *dst, const void *src)
{
    unsigned short s;
    unsigned char c;
    signed char sc;

    s = *(const unsigned short *) src;
    *(unsigned short *) dst = s;
    c = *(const unsigned char *) ((const char *) src + 2);
    *((unsigned char *) dst + 2) = c;
    c = *(const unsigned char *) ((const char *) src + 3);
    *((unsigned char *) dst + 3) = c;
    sc = *(const signed char *) ((const char *) src + 4);
    *((unsigned char *) dst + 4) = (unsigned char) sc;
    c = *(const unsigned char *) ((const char *) src + 5);
    *((unsigned char *) dst + 5) = c;
    c = *(const unsigned char *) ((const char *) src + 6);
    *((unsigned char *) dst + 6) = c;
    c = *(const unsigned char *) ((const char *) src + 7);
    *((unsigned char *) dst + 7) = c;
    c = *(const unsigned char *) ((const char *) src + 8);
    *((unsigned char *) dst + 8) = c;
    c = *(const unsigned char *) ((const char *) src + 9);
    *((unsigned char *) dst + 9) = c;
}
