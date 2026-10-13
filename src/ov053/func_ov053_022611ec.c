/* func_ov053_022611ec @ 0x022611ec, 0x44 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, unsigned short i, int j);
extern unsigned short data_020c80f8;

int func_ov053_022611ec(unsigned char *base)
{
    base[0x719] = 0;
    func_02019d0c(base + 0x564, 3, 1, 0, 0, 0, 0x4000, 0, 0, (unsigned short) data_020c80f8, 0);
    return 1;
}
