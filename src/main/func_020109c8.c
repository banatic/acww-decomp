/* func_020109c8 @ 0x020109c8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010a24(unsigned int *a, int b, int c, int d, unsigned int e, unsigned int f, int g, int h);

void func_020109c8(unsigned int *a, int b, int c, int d)
{
    func_02010a24(a, b, c, 0, a[0x2e0 / 4], (a[0x2d8 / 4] << 4) >> 16, d, 0x137);
}
