/* func_020b1a0c @ 0x020b1a0c, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *dest, const void *src, unsigned int size);

void *func_020b1a0c(void *a, void *b)
{
    MI_CpuCopy8(b, a, 0x4a);
    return a;
}
