/* func_020b35e8 @ 0x020b35e8, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int NNS_G3dMdlSetMdlDiff(int a, signed char b, unsigned short c);

void func_020b35e8(signed char *p, int a, int y)
{
    signed char c;
    c = *p;
    if (c == -1) {
        return;
    }
    NNS_G3dMdlSetMdlDiff(a, c,
                         (unsigned short) (((unsigned char) ((y * 13) >> 12) << 10) |
                                           ((unsigned char) ((y * 31) >> 12) | ((unsigned char) ((y * 27) >> 12) << 5))));
}
