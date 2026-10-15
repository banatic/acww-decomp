/* func_ov003_02213a90 @ 0x02213a90, 0x22 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov003_02213a80(unsigned char *src);

void func_ov003_02213a90(unsigned char *src, unsigned char *d0, unsigned char *d1, unsigned char *d2, unsigned char *d3,
                         unsigned short *res)
{
    unsigned char b3;
    *d0 = src[0];
    *d1 = src[1];
    *d2 = src[2];
    b3 = src[3];
    *d3 = b3;
    *res = func_ov003_02213a80(src);
}
