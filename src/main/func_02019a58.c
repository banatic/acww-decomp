/* func_02019a58 @ 0x02019a58, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *MI_CpuCopy8(void *dest, const void *src, unsigned int n);

void func_02019a58(char *p, unsigned short a, unsigned short b, char c)
{
    MI_CpuCopy8(&a, p, 2);
    MI_CpuCopy8(&b, p + 2, 2);
    p[4] = c;
}
