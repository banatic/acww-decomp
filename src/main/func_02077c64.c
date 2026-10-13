/* func_02077c64 @ 0x02077c64, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *dst, const void *src, int size);
void *func_02077c64(void *a, void *b)
{
    MI_CpuCopy8(b, a, 0x24);
    return a;
}
