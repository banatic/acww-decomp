/* func_02046518 @ 0x02046518, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02046518(unsigned char *p, unsigned int a1, unsigned short a2, unsigned int a3, unsigned short a4, unsigned char a5,
                  unsigned char a6, unsigned char a7, unsigned char a8, unsigned char a9, signed char a10)
{
    *p = (unsigned char) ((*p & ~0x07) | (a1 & 0x07));
    *(unsigned short *) (p + 8) = a2;
    *(unsigned short *) (p + 10) = a3;
    *(unsigned short *) (p + 12) = a4;
    *p = (unsigned char) ((*p & ~0xf8) | ((a5 & 0x1f) << 3));
    p[1] = (unsigned char) ((p[1] & ~0x03) | (a6 & 0x03));
    p[1] = (unsigned char) ((p[1] & ~0x60) | ((a7 & 0x03) << 5));
    p[1] = (unsigned char) ((p[1] & ~0x1c) | ((a8 & 0x07) << 2));
    p[2] = (unsigned char) ((p[2] & ~0x02) | ((a9 & 0x01) << 1));
    p[2] = (unsigned char) ((*((signed char *) (p + 2)) & ~0x3c) | ((a10 & 0x0f) << 2));
    {
        int flags = (p[2] & ~0x01) | 0x01;
        p[2] = (unsigned char) flags;
        return flags;
    }
}
