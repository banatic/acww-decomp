/* func_020950ac @ 0x020950ac, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *dst, const void *src, unsigned int size);

void func_020950ac(void *a, void *b)
{
    void *dst = (char *) a + 0x10;
    MI_CpuCopy8(b, dst, 0xc);
}
