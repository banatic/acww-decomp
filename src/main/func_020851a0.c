/* func_020851a0 @ 0x020851a0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020853b0(unsigned short *p, int a, int b, int c, int d, int e);
extern int func_02085278(unsigned short *p, int a, int b, int c, int d, int e);
int func_020851a0(unsigned short *p, int a, int b, int c, int d, int e)
{
    int nibble = (*p & 0xF000) >> 12;
    if (nibble == 14) {
        return func_020853b0(p, a, b, c, d, e);
    }
    if (nibble == 13) {
        return func_02085278(p, a, b, c, d, e);
    }
    return 0;
}
