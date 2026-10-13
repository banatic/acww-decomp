/* func_020642a8 @ 0x020642a8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *a, void *b, int c);

void func_020642a8(unsigned short *src, unsigned short *dst)
{
    unsigned short val;
    val = *src;
    *dst = val;
    MI_CpuCopy8(src + 1, dst + 1, 0xc);
}
