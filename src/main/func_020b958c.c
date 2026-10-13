/* func_020b958c @ 0x020b958c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020b95f4(unsigned int size);
unsigned int func_020b958c(unsigned int p)
{
    unsigned int v;
    p = (p + 7) & ~7;
    v = func_020b95f4(p);
    return ((p >> 3) << 16) | ((v >> 3) & 0xffff);
}
