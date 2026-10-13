/* func_020b97b4 @ 0x020b97b4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b97e4(int, unsigned short, int, unsigned int);

void func_020b97b4(unsigned short *a, int b, int c, ...)
{
    func_020b97e4(b, a[1], c, ((unsigned int) &c & ~3U) + 4U);
}
