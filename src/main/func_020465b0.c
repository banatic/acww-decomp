/* func_020465b0 @ 0x020465b0, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020465b0(unsigned char *p)
{
    p[0] = (p[0] & ~7) | 7;
    *(unsigned short *) (p + 8) = 0xffff;
    *(unsigned short *) (p + 10) = 0xfff1;
    p[1] &= ~3;
    p[1] &= ~0x80;
    p[2] &= ~1;
    p[1] = (p[1] & ~0x1c) | 0x1c;
    p[2] &= ~2;
    ((signed char *) p)[2] = (((signed char *) p)[2] & ~0x3c) | 0x3c;
}
