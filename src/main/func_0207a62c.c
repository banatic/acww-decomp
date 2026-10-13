/* func_0207a62c @ 0x0207a62c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *dst, void *src, int size);

void func_0207a62c(void *a, void *b)
{
    MI_CpuCopy8(b, (char *) a + 0x404c, 4);
    *((unsigned char *) a + 0x404f) = 1;
}
