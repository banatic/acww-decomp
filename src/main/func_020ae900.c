/* func_020ae900 @ 0x020ae900, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const unsigned char *src, unsigned char *dst, int len);

void func_020ae900(unsigned char *dest, const unsigned char *src)
{
    unsigned char buf[8];

    MI_CpuCopy8(src, buf, 8);
    dest[14] = buf[5];
    dest[13] = buf[4];
    dest[12] = buf[3];
    dest[15] = 0;
}
