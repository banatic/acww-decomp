/* func_020683e4 @ 0x020683e4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b4a20(void *dst, const void *src, unsigned int size);

void func_020683e4(void *base, int index, const void *src, unsigned int size)
{
    unsigned char *dst;
    dst = (unsigned char *) base + 0x14b8 + index * 0x5c;
    func_020b4a20(dst, src, size);
}
